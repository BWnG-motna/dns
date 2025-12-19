
#include "dns/Header.h"
#include "dns/Question.h"
#include "dns/Resource.h"

#include "net/net.h"
#include "view/HexView.h"

#include <iostream>
#include <random>


void Run( char const * qname , char const * qtype ) ;

uint16_t MakeQuery ( uint8_t * pBuf , char const * qname , char const * qytpe ) ;
uint16_t MakeId() ;

void ViewHeader  ( daniel::dns::Header   const & h ) ;
void ViewQuestion( daniel::dns::Question const & q ) ;
void ViewResource( daniel::dns::Resource const & r ) ;


int main( int argc , char * argv[] )
{
	if( 1 == argc )
	{
		Run( "." , "ns" ) ;
	}
	else if( 2 == argc )
	{
		Run( argv[ 1 ] , "ns" ) ;
	}
	else if( 3 >= argc )
	{
		Run( argv[ 1 ] , argv[ 2 ] ) ;
	}

	return 0 ;
}


void Run( char const * qname , char const * sqtype )
{
	uint8_t  sbuf[ 512 ] ;
	uint16_t slen = MakeQuery( sbuf , qname , sqtype ) ;

	uint8_t  rbuf[ 1500 ] ;
	int tLen = daniel::net::RequestOnUdp( rbuf , 1500 , sbuf , slen ) ;

	if( 12 > tLen )
	{
		std::cerr << "response error - length of received datagram is less than 12" << std::endl ;
		return ;
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
		ViewResource( r ) ;	

		len  = len  - adLen ;
		sPos = sPos + adLen ;
	}

	std::cout << std::endl ;
}


uint16_t MakeQuery( uint8_t * pBuf , char const * qname , char const * sqtype )
{
	daniel::dns::QType qtype = ( nullptr == sqtype ) ? daniel::dns::QType::A : daniel::dns::StrToQType( sqtype )  ;

	daniel::dns::Header h ;
	h.SetId( MakeId() ) ;
	h.SetQR( daniel::dns::QR::Query ) ;
	h.SetQdCount( 1 ) ;
	h.SetRD( true ) ;

	daniel::dns::Question q ;
	q.SetName ( qname , strlen( qname ) ) ;
	q.SetType ( qtype ) ;
	q.SetClass( daniel::dns::QClass::IN ) ;

	uint16_t hslen = 0 ;
	uint16_t qslen = 0 ;

	hslen = h.Save( pBuf , 512 ) ;
	qslen = q.Save( & ( pBuf[ hslen ] ) , 512 - hslen ) ;

	return hslen + qslen ;
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