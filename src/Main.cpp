
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


#define DUMP_TEST ( 0 )


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
#define EDNS0_DAU         ( 0 )
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

#if ( !DUMP_TEST )

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

#else

	uint8_t const dns_packet[] = {
	    // ==================== DNS Header (12 bytes) ====================
	    0xAB , 0xCD ,           // ID: 0xABCD (임의의 식별자)
	    0x85 , 0x00 ,           // Flags: QR=1(응답) , Opcode=0 , AA=1(권위 있는 응답) , 
	                            //        TC=0 , RD=1 , RA=0 , Z=0 , RCODE=0(No error)
	    0x00 , 0x01 ,           // QDCOUNT: 질문 섹션 개수 = 1
	    0x00 , 0x01 ,           // ANCOUNT: 답변 RR 개수 = 1
	    0x00 , 0x00 ,           // NSCOUNT: 권한 RR 개수 = 0
	    0x00 , 0x00 ,           // ARCOUNT: 추가 RR 개수 = 0

	    // ==================== Question Section ====================
	    0x04 , 0x74 , 0x65 , 0x73 , 0x74 ,  // label: "test" (길이 4)
	    0x07 , 0x65 , 0x78 , 0x61 , 0x6D , 
	    0x70 , 0x6C , 0x65 ,                // label: "example" (길이 7)
	    0x03 , 0x63 , 0x6F , 0x6D ,         // label: "com" (길이 3)
	    0x00 ,                              // root label (도메인 이름 종료)

	    0x01 , 0x07 ,                       // QTYPE: 263 (0x0107) → CLA 레코드 타입
	    0x00 , 0x01 ,                       // QCLASS: 1 (IN , Internet 클래스)

	    // ==================== Answer Resource Record ====================
	    0xC0 , 0x0C ,                       // NAME: 압축 포인터 (0xC00C → offset 12 , Question의 이름 참조)

	    0x01 , 0x07 ,                       // TYPE: 263 (CLA)
	    0x00 , 0x01 ,                       // CLASS: 1 (IN)

	    0x00 , 0x00 , 0x0E , 0x10 ,         // TTL: 3600 초 (0x00000E10)

	    0x00 , 0x14 ,                       // RDLENGTH: 20 바이트 (아래 RDATA의 정확한 길이)

	    // ==================== RDATA (CLA 레코드 데이터) ====================
	    // RDATA는 하나 이상의 character-string으로 구성 (draft-johnson-dns-ipn-cla-07 규정)
	    // 각 character-string = 1바이트 길이 + 문자열 내용

	    // 첫 번째 CLA label
	    0x09 , 0x54 , 0x43 , 0x50 , 0x2D , 0x56 , 0x34 , 0x2D , 0x56 , 0x36 ,  // "TCP-V4-V6" (길이 9)

	    // 두 번째 CLA label
	    0x09 , 0x55 , 0x44 , 0x50 , 0x2D , 0x56 , 0x36 , 0x2D , 0x56 , 0x37    // "UDP-V6-V7" (길이 9)
	} ;

	tLen = sizeof( dns_packet ) ;
	for( uint16_t pos = 0 ; pos < tLen ; ++pos )
	{
		rbuf[ pos ] = dns_packet[ pos ] ;
	}

#endif


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

	uint8_t rdataBuf[ 512 ] ;

	r.GetRData( rdataBuf , 512 ) ;

	std::cout << "  "
	          << reinterpret_cast< char const * >( r.GetName() ) << "\t" 
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