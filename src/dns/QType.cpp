#include "dns/QType.h"

#include <string>
#include <algorithm>
#include <cctype>


#undef NULL


char const * daniel::dns::ToString( QType const & type )
{
	switch( type )
	{
		case QType::A :
			return "A" ;

		case QType::NS :
			return "NS" ;

		case QType::MD :
			return "MD" ;

		case QType::MF :
			return "MF" ;

		case QType::CNAME :
			return "CNAME" ;

		case QType::SOA :
			return "SOA" ;
	
		case QType::MB :
			return "MB" ;

		case QType::MG :
			return "MG" ;

		case QType::MR :
			return "MR" ;

		case QType::NULL :
			return "NULL" ;

		case QType::WKS :
			return "WKS" ;

		case QType::PTR :
			return "PTR" ;

		case QType::HINFO :
			return "HINFO" ;

		case QType::MINFO :
			return "MINFO" ;

		case QType::MX :
			return "MX" ;

		case QType::TXT :
			return "TXT" ;

		case QType::RP :
			return "RP" ;

#if 0
		case QType::AFSDB :
			return "AFXDB" ;
#endif

		case QType::AAAA :
			return "AAAA" ;

		case QType::A6 :
			return "A6" ;

		case QType::OPT :
			return "OPT" ;

		case QType::RRSIG :
			return "RRSIG" ;

		case QType::AXFR :
			return "AXFR" ;

		case QType::MAILB :
			return "MAILB" ;

		case QType::MAILA :
			return "MAILA" ;

		case QType::ALL :
			return "*" ;

		default :
			return "UNKNOWN" ;
	}
}


namespace
{

constexpr uint64_t hash( char const * pStr )
{
	if( nullptr == pStr )
	{
		return 0 ;
	}


	uint64_t h = 0x100 ;
	while( * pStr )
	{
		h = h * 101 + *pStr++ ;
	}

	return h ;
}

}


daniel::dns::QType daniel::dns::StrToQType( char const * pStr )
{
	if( nullptr == pStr )
	{
		return QType::UNKNOWN ;
	}


	std::string s( pStr ) ;
	std::transform( s.begin() , s.end() , s.begin() , []( unsigned char c ) { return std::toupper( c ) ; } ) ;

	switch( hash( s.c_str() ) )
	{
		case hash( "A" ) :
			return QType::A ;

		case hash( "NS" ) :
			return QType::NS ;

		case hash( "MD" ) :
			return QType::MD ;

		case hash( "MF" ) :
			return QType::MF ;

		case hash( "CNAME" ) :
			return QType::CNAME ;

		case hash( "SOA" ) :
			return QType::SOA ;

		case hash( "MB" ) :
			return QType::MB ;

		case hash( "MG" ) :
			return QType::MG ;

		case hash( "MR" ) :
			return QType::MR ;

		case hash( "NULL" ) :
			return QType::NULL ;

		case hash( "WKS" ) :
			return QType::WKS ;

		case hash( "PTR" ) :
			return QType::PTR ;

		case hash( "HINFO" ) :
			return QType::HINFO ;

		case hash( "MINFO" ) :
			return QType::MINFO ;

		case hash( "MX" ) :
			return QType::MX ;

		case hash( "TXT" ) :
			return QType::TXT ;

		case hash( "RP" ) :
			return QType::RP ;

#if 0
		case hash( "AFSDB" ) :
			return QType::AFSDB ;
#endif

		case hash( "AAAA" ) :
			return QType::AAAA ;

		case hash( "A6" ) :
			return QType::A6 ;

		case hash( "OPT" ) :
			return QType::OPT ; 

		case hash( "RRSIG" ) :
			return QType::RRSIG ;

		case hash( "AXFR" ) :
			return QType::AXFR ;

		case hash( "MAILB" ) :
			return QType::MAILB ;

		case hash( "MAILA" ) :
			return QType::MAILA ;

		case hash( "*"   ) :
		case hash( "ALL" ) :
		case hash( "ANY" ) :
			return QType::ALL ;

		default :
			return QType::UNKNOWN ;
	}
}