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

		case QType::AFSDB :
			return "AFSDB" ;

		case QType::X25 :
			return "X25" ;

		case QType::ISDN :
			return "ISDN" ;

		case QType::RT :
			return "RT" ;

		case QType::NSAP :
			return "NSAP" ;

		case QType::NSAP_PTR :
			return "NSAP_PTR" ;

		case QType::SIG :
			return "SIG" ;

		case QType::KEY :
			return "KEY" ;

		case QType::PX :
			return "PX" ;

		case QType::GPOS :
			return "GPOS" ;

		case QType::AAAA :
			return "AAAA" ;

		case QType::LOC :
			return "LOC" ;

		case QType::NXT :
			return "NXT" ;

		case QType::EID :
			return "EID" ;

		case QType::NIMLOC :
			return "NIMLOC" ;

		case QType::SRV :
			return "SRV" ;

		case QType::ATMA :
			return "ATMA" ;

		case QType::NAPTR :
			return "NAPTR" ;

		case QType::KX :
			return "KX" ;

		case QType::CERT :
			return "CERT" ;

		case QType::A6 :
			return "A6" ;

		case QType::DNAME :
			return "DNAME" ;

		case QType::SINK :
			return "SINK" ;

		case QType::OPT :
			return "OPT" ;

		case QType::APL :
			return "APL" ;

		case QType::DS :
			return "DS" ;

		case QType::SSHFP :
			return "SSHFP" ;

		case QType::IPSECKEY :
			return "IPSECKEY" ;

		case QType::RRSIG :
			return "RRSIG" ;

		case QType::NSEC :
			return "NSEC" ;

		case QType::DNSKEY :
			return "DNSKEY" ;

		case QType::DHCID :
			return "DHCID" ;

		case QType::NSEC3 :
			return "NSEC3" ;

		case QType::NSEC3PARAM :
			return "NSEC3PARAM" ;

		case QType::TLSA : 
			return "TLSA" ;

		case QType::SMIMEA :
			return "SMIMEA" ;

		case QType::HIP :
			return "HIP" ;

		case QType::NINFO :
			return "NINFO" ;

		case QType::RKEY :
			return "RKEY" ;

		case QType::TALINK :
			return "TALINK" ;

		case QType::CDS :
			return "CDS" ;

		case QType::CDNSKEY :
			return "CDNSKEY" ;

		case QType::OPENPGPKEY :
			return "OPENPGPKEY" ;

		case QType::CSYNC :
			return "CSYNC" ;

		case QType::ZONEMD :
			return "ZONEMD" ;

		case QType::SVCB :
			return "SVCB" ;

		case QType::HTTPS :
			return "HTTPS" ;

		case QType::DSYNC :
			return "DSYNC" ;

		case QType::HHIT :
			return "HHIT" ;

		case QType::BRID :
			return "BRID" ;

		case QType::SPF :
			return "SPF" ;

		case QType::UINFO :
			return "UINFO" ;

		case QType::UID :
			return "UID" ;

		case QType::GID :
			return "GID" ;

		case QType::UNSPEC :
			return "UNSPEC" ;

		case QType::NID :
			return "NID" ;

		case QType::L32 :
			return "L32" ;

		case QType::L64 :
			return "L64" ;

		case QType::LP :
			return "LP" ;

		case QType::EUI48 :
			return "EUI48" ;

		case QType::EUI64 :
			return "EUI64" ;

		case QType::NXNAME :
			return "NXNAME" ;

		case QType::TKEY :
			return "TKEY" ;

		case QType::TSIG :
			return "TSIG" ;

		case QType::IXFR :
			return "IXFR" ;

		case QType::AXFR :
			return "AXFR" ;

		case QType::MAILB :
			return "MAILB" ;

		case QType::MAILA :
			return "MAILA" ;

		case QType::ALL :
			return "*" ;

		case QType::URI :
			return "URI" ;

		case QType::CAA :
			return "CAA" ;

		case QType::AVC :
			return "AVC" ;

		case QType::DOA :
			return "DOA" ;

		case QType::AMTRELAY :
			return "AMTRELAY" ;

		case QType::RESINFO :
			return "RESINFO" ;

		case QType::WALLET :
			return "WALLET" ;

		case QType::CLA :
			return "CLA" ;

		case QType::IPN :
			return "IPN" ;

		case QType::TA :
			return "TA" ;

		case QType::DDLV :
			return "DDLV" ;

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

		case hash( "AFSDB" ) :
			return QType::AFSDB ;

		case hash( "X25" ) :
			return QType::X25 ;

		case hash( "ISDN" ) :
			return QType::ISDN ;

		case hash( "RT" ) :
			return QType::RT ;

		case hash( "NSAP" ) :
			return QType::NSAP ;

		case hash( "NSAP_PTR" ) :
			return QType::NSAP_PTR ;

		case hash( "SIG" ) :
			return QType::SIG ;

		case hash( "KEY" ) :
			return QType::KEY ;

		case hash( "PX" ) :
			return QType::PX ;

		case hash( "GPOS" ) :
			return QType::GPOS ;

		case hash( "AAAA" ) :
			return QType::AAAA ;

		case hash( "LOC" ) :
			return QType::LOC ;

		case hash( "NXT" ) :
			return QType::NXT ;

		case hash( "EID" ) :
			return QType::EID ;

		case hash( "NIMLOC" ) :
			return QType::NIMLOC ;

		case hash( "SRV" ) :
			return QType::SRV ;

		case hash( "ATMA" ) :
			return QType::ATMA ;

		case hash( "NAPTR" ) :
			return QType::NAPTR ;

		case hash( "KX" ) :
			return QType::KX ;

		case hash( "CERT" ) :
			return QType::CERT ;

		case hash( "A6" ) :
			return QType::A6 ;

		case hash( "DNAME" ) :
			return QType::DNAME ;

		case hash( "SINK" ) :
			return QType::SINK ;

		case hash( "OPT" ) :
			return QType::OPT ; 

		case hash( "APL" ) :
			return QType::APL ;

		case hash( "DS" ) :
			return QType::DS ;

		case hash( "SSHFP" ) :
			return QType::SSHFP ;

		case hash( "IPSECKEY" ) :
			return QType::IPSECKEY ;

		case hash( "RRSIG" ) :
			return QType::RRSIG ;

		case hash( "NSEC" ) :
			return QType::NSEC ;

		case hash( "DNSKEY" ) :
			return QType::DNSKEY ;

		case hash( "DHCID" ) :
			return QType::DHCID ;

		case hash( "NSEC3" ) :
			return QType::NSEC3 ;

		case hash( "NSEC3PARAM" ) :
			return QType::NSEC3PARAM ;

		case hash( "TLSA" ) :
			return QType::TLSA ;

		case hash( "SMIMEA" ) :
			return QType::SMIMEA ;

		case hash( "HIP" ) :
			return QType::HIP ;

		case hash( "NINFO" ) :
			return QType::NINFO ;

		case hash( "RKEY" ) :
			return QType::RKEY ;

		case hash( "TALINK" ) :
			return QType::TALINK ;

		case hash( "CDS" ) :
			return QType::CDS ;

		case hash( "CDNSKEY" ) :
			return QType::CDNSKEY ;

		case hash( "OPENPGPKEY" ) :
			return QType::OPENPGPKEY ;

		case hash( "CSYNC" ) :
			return QType::CSYNC ;

		case hash( "ZONEMD" ) :
			return QType::ZONEMD ;

		case hash( "SVCB" ) :
			return QType::SVCB ;

		case hash( "HTTPS" ) :
			return QType::HTTPS ;

		case hash( "DSYNC" ) :
			return QType::DSYNC ;

		case hash( "HHIT" ) :
			return QType::HHIT ;

		case hash( "BRID" ) :
			return QType::BRID ;

		case hash( "SPF" ) :
			return QType::SPF ;

		case hash( "UINFO" ) :
			return QType::UINFO ;

		case hash( "UID" ) :
			return QType::UID ;

		case hash( "GID" ) :
			return QType::GID ;

		case hash( "UNSPEC" ) :
			return QType::UNSPEC ;

		case hash( "NID" ) :
			return QType::NID ;

		case hash( "L32" ) :
			return QType::L32 ;

		case hash( "L64" ) :
			return QType::L64 ;

		case hash( "LP" ) :
			return QType::LP ;

		case hash( "EUI48" ) :
			return QType::EUI48 ;

		case hash( "EUI64" ) :
			return QType::EUI64 ;

		case hash( "NXNAME" ) :
			return QType::NXNAME ;

		case hash( "TKEY" ) :
			return QType::TKEY ;

		case hash( "TSIG" ) :
			return QType::TSIG ;

		case hash( "IXFR" ) :
			return QType::IXFR ;

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

		case hash( "URI" ) :
			return QType::URI ;

		case hash( "CAA" ) :
			return QType::CAA ;

		case hash( "AVC" ) :
			return QType::AVC ;

		case hash( "DOA" ) :
			return QType::DOA ;

		case hash( "AMTRELAY" ) :
			return QType::AMTRELAY ;

		case hash( "RESINFO" ) :
			return QType::RESINFO ;

		case hash( "WALLET" ) :
			return QType::WALLET ;

		case hash( "CLA" ) :
			return QType::CLA ;

		case hash( "IPN" ) :
			return QType::IPN ;

		case hash( "TA" ) :
			return QType::TA ;

		case hash( "DDLV" ) :
			return QType::DDLV ;

		default :
			return QType::UNKNOWN ;
	}
}