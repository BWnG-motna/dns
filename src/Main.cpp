
#include "dns/Header.h"
#include "dns/Question.h"
#include "dns/Resource.h"
#include "dns/EDNS0.h"

#include "net/net.h"
#include "view/HexView.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <random>


#include "ds/LinkedList.h"


namespace daniel::dns
{

constexpr char     const * dname   = "."  ;
constexpr char     const * qtype   = "ns" ;
constexpr char     const * svrIp   = "8.8.8.8" ;
constexpr uint16_t const   svrPort = 53 ;

} // namespace daniel::dns // server information


void Run( char const * qname , char const * qtype , char const * svrIp , uint16_t const & port ) ;


uint16_t MakeQuery( uint8_t * pBuf , uint16_t const & bufMaxLen , char const * qname , char const * qytpe , bool const & isTcp ) ;
uint16_t MakeId() ;


void ViewHeader  ( daniel::dns::Header   const & h ) ;
void ViewQuestion( daniel::dns::Question const & q ) ;
void ViewResource( daniel::dns::Resource const & r ) ;
void ViewResource( daniel::dns::EDNS0    const & e ) ;


#define EDNS0_OPT_PADDING ( 0 )
#define EDNS0_DAU_        ( 0 )
#define EDNS0_COOKIE      ( 1 )


int main( int argc , char * argv[] )
{
	/**/ if( 1 >= argc )
	{
		Run( daniel::dns::dname   ,
			 daniel::dns::qtype   , 
			 daniel::dns::svrIp   ,
			 daniel::dns::svrPort ) ;
	}
	else if( 2 == argc )
	{
		Run( argv[ 1 ] ,
			 daniel::dns::qtype   , 
			 daniel::dns::svrIp   ,
			 daniel::dns::svrPort ) ;
	}
	else if( 3 == argc )
	{
		Run( argv[ 1 ] , 
			 argv[ 2 ] , 
			 daniel::dns::svrIp   , 
			 daniel::dns::svrPort ) ;
	}
	else if( 4 == argc )
	{
		Run( argv[ 1 ] , 
			 argv[ 2 ] , 
			 argv[ 3 ] ,
			 daniel::dns::svrPort ) ;
	}
	else
	{
		Run( argv[ 1 ] , 
			 argv[ 2 ] , 
			 argv[ 3 ] ,
			 std::stoi( argv[ 4 ] ) ) ;
	}

	return 0 ;
}


void Run( char const * qname , char const * sqtype , char const * svrIp , uint16_t const & port )
{
	uint8_t  sbuf[ 1500 + 1 ] ;
	uint8_t  rbuf[ 4096 + 1 ] ;

	bool isTcp = false ;
	int  tLen  = 0 ;

	uint16_t slen = 0 ;


DNS_QUERY :

	if( true == isTcp )
	{
		slen = MakeQuery( sbuf , 1500 , qname , sqtype , true  ) ;
		tLen = daniel::net::RequestOnTcp( rbuf , 4096 , sbuf , slen , svrIp , port ) ;
	}
	else
	{
		slen = MakeQuery( sbuf , 1500 , qname , sqtype , false ) ;
		tLen = daniel::net::RequestOnUdp( rbuf , 1500 , sbuf , slen , svrIp , port ) ;	
	}

	/**/ if(  0 > tLen )
	{
		std::cerr << "reponse error - no reponse" << std::endl ;
	}
	else if( 12 > tLen )
	{
		std::cerr << "response error - length of received datagram is less than 12" << std::endl ;
		return ;
	}
	else if( false == isTcp && 1500 < tLen )
	{
		std::cerr << "processing error - length of received datagram is greater than 1500. tcp-fallback will be operated" << std::endl ;
		isTcp = true ;

		goto DNS_QUERY ;
	}
	else if(  true == isTcp && 4096 < tLen )
	{
		std::cerr << "processing error - length of received datagram is greater than 4096. quit" << std::endl ;
		return ;
	}


	{
		daniel::dns::Header h ;
		h.Load( rbuf , tLen ) ;

		/**/ if( false == isTcp && 0 != h.GetTC() )
		{
			std::cout << "TC = 1 , so tcp-fallback is operated" << std::endl ;
			isTcp = true ;
			
			goto DNS_QUERY ;
		}
		else if(  true == isTcp && 0 != h.GetTC() )
		{
			std::cerr << "response error - TC is set with 1 even if tcp-fallback is operated" << std::endl ;
			return ;
		}
	}

	daniel::view::HexView::View( sbuf , slen , 2 ) ;
	daniel::view::HexView::View( rbuf , tLen , 2 ) ;

	daniel::dns::Header h ;
	int hLen = h.Load( rbuf , tLen ) ;

	std::cout << "[ Header     ]" << std::endl ;
	ViewHeader( h ) ;

	std::cout << std::endl ;

	uint16_t len  = hLen ;
	uint16_t sPos = hLen ;

	std::cout << "[ Question   ]" << std::endl ;

	daniel::dns::Question q ;
	for( uint16_t pos = 0 ; pos < h.GetQdCount() ; ++pos )
	{
		int qLen = q.Load( &( rbuf[ sPos ] ) , tLen - len ) ;
		ViewQuestion( q ) ;		

		len  = len  - qLen ;
		sPos = sPos + qLen ;
	}

	std::cout << std::endl ;


	daniel::dns::Resource r ;
	daniel::dns::EDNS0    e ;

	std::cout << "[ Answer     ]" << std::endl ;
	for( uint16_t pos = 0 ; pos < h.GetAnCount() ; ++pos )
	{
		int anLen = r.Load( & ( rbuf[ sPos ] ) , tLen - len , rbuf ) ;
		ViewResource( r ) ;	

		len  = len  - anLen ;
		sPos = sPos + anLen ;
	}

	std::cout << std::endl ;

	std::cout << "[ Authority  ]" << std::endl ;
	for( uint16_t pos = 0 ; pos < h.GetNsCount() ; ++pos )
	{
		int auLen = r.Load( & ( rbuf[ sPos ] ) , tLen - len , rbuf ) ;
		ViewResource( r ) ;	

		len  = len  - auLen ;
		sPos = sPos + auLen ;
	}

	std::cout << std::endl ;

	std::cout << "[ Additional ]" << std::endl ;
	for( uint16_t pos = 0 ; pos < h.GetArCount() ; ++pos )
	{
		int adLen = r.Load( & ( rbuf[ sPos ] ) , tLen - len , rbuf ) ;
		
		if( daniel::dns::QType::OPT == r.GetType() )
		{
			adLen = e.Load( & ( rbuf[ sPos ] ) , tLen - len , rbuf ) ;
			ViewResource( e ) ;
		}
		else
		{
			ViewResource( r ) ;	
		}

		len  = len  - adLen ;
		sPos = sPos + adLen ;
	}

	std::cout << std::endl ;
}


uint16_t MakeQuery( uint8_t * pBuf , uint16_t const & bufMaxLen , char const * qname , char const * sqtype , bool const & isTcp )
{
	daniel::dns::QType qtype = ( nullptr == sqtype ) ? daniel::dns::QType::A : daniel::dns::StrToQType( sqtype )  ;

	daniel::dns::Header h ;
	h.SetId( MakeId() ) ;
	h.SetQR( daniel::dns::QR::Query ) ;
	h.SetQdCount( 1 ) ;
	h.SetArCount( 1 ) ;
	h.SetRD( 1 ) ;

	daniel::dns::Question q ;
	q.SetName ( qname , strlen( qname ) ) ;
	q.SetType ( qtype ) ;
	q.SetClass( daniel::dns::QClass::IN ) ;

	daniel::dns::EDNS0 e ;
	e.SetPayloadSize( 1232 ) ;
	e.SetVersion ( 0 ) ;
	e.SetExtRCode( 0 ) ;
	e.SetDNSSecOk( true ) ;

#if ( EDNS0_PADDING )

	uint8_t padding[ 5 ] = { 0x01 , 0x02 , 0x03 , 0x04 , 0x05 } ;

	bool is = e.InsertOptPadding( padding , 5 ) ;
	if( false == is )
	{
		std::cout << "EDNS0_OptCode insertion ( padding ) has error" << std::endl ;
	}

#endif

#if ( EDNS0_DAU )

	bool is = e.InsertOptDAU() ;
	if( false == is ) 
	{
		std::cout << "EDNS0_OptCode insertion ( DAU ) has error" << std::endl ;
	}

#endif


#if ( EDNS0_COOKIE )

	uint8_t cookie[ 16 ] = 
		{ 0xef , 0x13 , 0x33 , 0xa1 , 0xb5 , 0x55 , 0xf3 , 0x3f ,
	      0xf3 , 0x3f , 0x55 , 0x5b , 0x1a , 0x33 , 0x31 , 0xfe } ;

	bool is = e.InsertOptCookie( cookie , 16 ) ;
	if( false == is )
	{
		std::cout << "EDNS0_OptCode insertion ( Cookie ) has error" << std::endl ;
	}

#endif

	uint16_t hslen = 0 ;
	uint16_t qslen = 0 ;
	uint16_t eslen = 0 ;

	uint16_t const beginPos = ( true == isTcp ) ? 2 : 0 ; 

	hslen = h.Save( & ( pBuf[ beginPos + 0             ] ) , bufMaxLen - beginPos ) ;
	qslen = q.Save( & ( pBuf[ beginPos + hslen         ] ) , bufMaxLen - beginPos - hslen ) ;
	eslen = e.Save( & ( pBuf[ beginPos + hslen + qslen ] ) , bufMaxLen - beginPos - hslen - qslen ) ;

	uint16_t totalLen = hslen + qslen + eslen ;

	if( true == isTcp )
	{
		pBuf[ 0 ] = ( totalLen >> 8 ) & 0x00FF ;
		pBuf[ 1 ] = ( totalLen >> 0 ) & 0x00FF ;
	}

	return ( true == isTcp ) ? ( totalLen + 2 ) : totalLen ;
}


uint16_t MakeId()
{
	std::random_device rd ;
	std::mt19937 gen( rd() ) ;
	std::uniform_int_distribution< uint16_t > dis( 0 , 65535 ) ;

	return dis( gen ) ;
}


void ViewHeader( daniel::dns::Header const & h )
{
	std::cout << "  ID      : " << h.GetID()      << std::endl ;
	std::cout << std::endl ;

	std::cout << "  QR      : " << h.GetQR()      << "    " ;
	std::cout << "  OpCode  : " << h.GetOpcode()  << "    " ;
	std::cout << "  AA      : " << h.GetAA()      << std::endl ;
	std::cout << "  TC      : " << h.GetTC()      << "    " ;
	std::cout << "  RD      : " << h.GetRD()      << "    " ;
	std::cout << "  RA      : " << h.GetRA()      << std::endl ;
	std::cout << "  Z       : " << h.GetZ()       << "    " ;
	std::cout << "  AD      : " << h.GetAD()      << "    " ;
	std::cout << "  CD      : " << h.GetCD()      << std::endl ;
	std::cout << "  RCODE   : " << h.GetRCode()   << std::endl ;
	std::cout << std::endl ;

	std::cout << "  QdCount : " << h.GetQdCount() << std::endl ;
	std::cout << "  AnCount : " << h.GetAnCount() << std::endl ;
	std::cout << "  NsCount : " << h.GetNsCount() << std::endl ;
	std::cout << "  ArCount : " << h.GetArCount() << std::endl ;
}


void ViewQuestion( daniel::dns::Question const & q )
{
	uint8_t nameBuf[ 512 ] ;
	q.GetName( nameBuf, 512 ) ;
	std::cout << "  " 
			  << nameBuf << "\t" 
			  << daniel::dns::ToString( q.GetType()  ) << "\t"
			  << daniel::dns::ToString( q.GetClass() ) << std::endl ;
}


void ViewResource( daniel::dns::Resource const & r )
{
	if( daniel::dns::QType::OPT == r.GetType() )
	{
		return ;
	}

	uint8_t  nameBuf[ 512 ] ;
	uint8_t rdataBuf[ 512 ] ;

	r.GetName (  nameBuf , 512 ) ;
	r.GetRData( rdataBuf , 512 ) ;

	std::cout << "  "
	          << nameBuf  << "\t" 
	          << daniel::dns::ToString( r.GetType()  ) << "\t"
			  << daniel::dns::ToString( r.GetClass() ) << "\t"
			  << r.GetTTL()   << "\t"
			  << r.GetRdLen() << "\t"
			  << rdataBuf << std::endl ;
}


void ViewResource( daniel::dns::EDNS0 const & e )
{
	if( daniel::dns::QType::OPT != e.GetType() )
	{
		return ;
	}

	std::cout << "  "
	          << daniel::dns::ToString( e.GetType() ) << "\t"
	          << "Payload size  : " << static_cast< uint16_t >( e.GetPayloadSize() ) << std::endl << "        "
	          << "Extended RCode: " << static_cast< uint16_t >( e.GetExtRCode()    ) << std::endl << "        "
	          << "Version       : " << static_cast< uint16_t >( e.GetVersion()     ) << std::endl << "        "
	          << "Option Count  : " << e.GetOptCount() << std::endl ;
}