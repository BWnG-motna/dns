#include "dns/Resource.h"

#include "dns/RR/RData_A.h"
#include "dns/RR/RData_NS.h"
#include "dns/RR/RData_MD.h"
#include "dns/RR/RData_MF.h"
#include "dns/RR/RData_CNAME.h"
#include "dns/RR/RData_SOA.h"
#include "dns/RR/RData_MB.h"
#include "dns/RR/RData_MG.h"
#include "dns/RR/RData_MR.h"
#include "dns/RR/RData_NULL.h"
#include "dns/RR/RData_WKS.h"
#include "dns/RR/RData_PTR.h"
#include "dns/RR/RData_HINFO.h"
#include "dns/RR/RData_MINFO.h"
#include "dns/RR/RData_MX.h"
#include "dns/RR/RData_TXT.h"
#include "dns/RR/RData_RP.h"
#include "dns/RR/RData_AFSDB.h"
#include "dns/RR/RData_X25.h"
#include "dns/RR/RData_ISDN.h"
#include "dns/RR/RData_RT.h"
#include "dns/RR/RData_NSAP.h"

#include "dns/RR/RData_SIG.h"

#include "dns/RR/RData_AAAA.h"
#include "dns/RR/RData_LOC.h"

#include "dns/RR/RData_SRV.h"
#include "dns/RR/RData_NAPTR.h"
#include "dns/RR/RData_KX.h"
#include "dns/RR/RData_CERT.h"
#include "dns/RR/RData_A6.h"

#include "dns/RR/RData_APL.h"
#include "dns/RR/RData_DS.h"
#include "dns/RR/RData_SSHFP.h"
#include "dns/RR/RData_IPSECKEY.h"
#include "dns/RR/RData_RRSIG.h"
#include "dns/RR/RData_NSEC.h"
#include "dns/RR/RData_DNSKEY.h"
#include "dns/RR/RData_DHCID.h"
#include "dns/RR/RData_NSEC3.h"
#include "dns/RR/RData_NSEC3PARAM.h"

#include "dns/RR/RData_TLSA.h"
#include "dns/RR/RData_SMIMEA.h"
#include "dns/RR/RData_HIP.h"

#include "dns/RR/RData_CDS.h"
#include "dns/RR/RData_CDNSKEY.h"
#include "dns/RR/RData_OPENPGPKEY.h"
#include "dns/RR/RData_CSYNC.h"
#include "dns/RR/RData_ZONEMD.h"
#include "dns/RR/RData_SVCB.h"
#include "dns/RR/RData_HTTPS.h"

#include "dns/RR/RData_SPF.h"

#include "dns/RR/RData_EUI48.h"
#include "dns/RR/RData_EUI64.h"

#include "dns/RR/RData_URI.h"
#include "dns/RR/RData_CAA.h"

#include "dns/RR/RData_TA.h"



#undef NULL


daniel::dns::Resource::Resource()
	: pName( nullptr ) , qtype( QType::A ) , qclass( QClass::IN ) , ttl( 0 ) , rdlength( 0 ) , pRDat( nullptr )
{

}


daniel::dns::Resource::~Resource()
{
	if( nullptr != pRDat )
	{
		delete pRDat ;
		pRDat = nullptr ;
	}

	if( nullptr != pName )
	{
		delete pName ;
		pName = nullptr ;
	}
}


uint16_t daniel::dns::Resource::Load( uint8_t const * pBuf , uint16_t const & length , uint8_t const * pRef )
{
	if( 1 > length || nullptr == pBuf || nullptr == pRef  )
	{
		return 0 ;
	}

	SetDataGram( pRef ) ;

	if( nullptr != pName )
	{
		delete [] pName ;
		pName = nullptr ;
	}

	uint16_t nameLen   = GetDNDataLen( pBuf , length ) ;
	uint16_t allocSize = ( 0 < nameLen ) ? ( nameLen + 1 ) : 2 ;

	pName = new ( std::nothrow ) uint8_t [ allocSize ] ;
	if( nullptr == pName )
	{
		return 0 ;
	}

	if( 0 < nameLen )
	{
		GetDNData( pName , allocSize , pBuf ) ;
	}
	else
	{
		pName[ 0 ] = '.'  ;
		pName[ 1 ] = '\0' ;
	}

	uint16_t bPos = SkipDName( pBuf , length ) ;

	uint16_t qtypeValue
		= ( ( pBuf[ bPos + 0 ] << 8 ) & 0xFF00 )
	    | ( ( pBuf[ bPos + 1 ] << 0 ) & 0x00FF ) ;

	uint16_t qclassValue
		= ( ( pBuf[ bPos + 2 ] << 8 ) & 0xFF00 )
	    | ( ( pBuf[ bPos + 3 ] << 0 ) & 0x00FF ) ;

	qtype  = daniel::enumFromUint16< QType  >(  qtypeValue ) ;
	qclass = daniel::enumFromUint16< QClass >( qclassValue ) ; 

	ttl 
		= ( ( pBuf[ bPos + 4 ] << 24 ) & 0xFF000000 )
	    | ( ( pBuf[ bPos + 5 ] << 16 ) & 0x00FF0000 )
	    | ( ( pBuf[ bPos + 6 ] <<  8 ) & 0x0000FF00 )
	    | ( ( pBuf[ bPos + 7 ] <<  0 ) & 0x000000FF ) ;

	rdlength
		= ( ( pBuf[ bPos + 8 ] << 8 ) & 0xFF00 )
	    | ( ( pBuf[ bPos + 9 ] << 0 ) & 0x00FF ) ;

	if( nullptr != pRDat )
	{
		delete pRDat ;
		pRDat = nullptr ;
	}

	MakeRData( & ( pBuf[ bPos + 10 ] ) , rdlength ) ;

	return bPos + 10 + rdlength ;
}


#if 0
uint16_t daniel::dns::Resource::Save( uint8_t * pBuf , uint16_t const & length )
{
	return 0 ;
}
#endif


void daniel::dns::Resource::MakeRData( uint8_t const * pBuf , uint32_t const & length ) noexcept
{
	if( nullptr == pBuf || 1 > length ) 
	{
		pRDat = nullptr ;
		return ;
	}

	uint8_t const * pDatagram = GetDataGram() ;

	switch( qtype )
	{
		case QType::A :
			pRDat = new ( std::nothrow ) RR::RData_A() ;
			break ;

		case QType::NS :
			pRDat = new ( std::nothrow ) RR::RData_NS( pDatagram ) ;
			break ;

		case QType::MD :
			pRDat = new ( std::nothrow ) RR::RData_MD( pDatagram ) ;
			break ;

		case QType::MF :
			pRDat = new ( std::nothrow ) RR::RData_MF( pDatagram ) ;
			break ;

		case QType::CNAME :
			pRDat = new ( std::nothrow ) RR::RData_CNAME( pDatagram ) ;
			break ;

		case QType::SOA :
			pRDat = new ( std::nothrow ) RR::RData_SOA( pDatagram ) ;
			break ;

		case QType::MB :
			pRDat = new ( std::nothrow ) RR::RData_MB( pDatagram ) ;
			break ;

		case QType::MG :
			pRDat = new ( std::nothrow ) RR::RData_MG( pDatagram ) ;
			break ;

		case QType::MR :
			pRDat = new ( std::nothrow ) RR::RData_MR( pDatagram ) ;
			break ;

		case QType::NULL :
			pRDat = new ( std::nothrow ) RR::RData_NULL() ;
			break ;

		case QType::WKS :
			pRDat = new ( std::nothrow ) RR::RData_WKS() ;
			break ;

		case QType::PTR :
			pRDat = new ( std::nothrow ) RR::RData_PTR( pDatagram ) ;
			break ;

		case QType::HINFO :
			pRDat = new ( std::nothrow ) RR::RData_HINFO( pDatagram ) ;
			break ;

		case QType::MINFO :
			pRDat = new ( std::nothrow ) RR::RData_MINFO( pDatagram ) ;
			break ;

		case QType::MX :
			pRDat = new ( std::nothrow ) RR::RData_MX( pDatagram ) ;
			break ;

		case QType::TXT :
			pRDat = new ( std::nothrow ) RR::RData_TXT() ;
			break ;

		case QType::RP :
			pRDat = new ( std::nothrow ) RR::RData_RP( pDatagram ) ;
			break ;

		case QType::AFSDB :
			pRDat = new ( std::nothrow ) RR::RData_AFSDB( pDatagram ) ;
			break ;

		case QType::X25 :
			pRDat = new ( std::nothrow ) RR::RData_X25() ;
			break ;

		case QType::ISDN :
			pRDat = new ( std::nothrow ) RR::RData_ISDN() ;
			break ;

		case QType::RT :
			pRDat = new ( std::nothrow ) RR::RData_RT( pDatagram ) ;
			break ;

		case QType::NSAP :
			pRDat = new ( std::nothrow ) RR::RData_NSAP() ;
			break ;

		case QType::SIG :
			pRDat = new ( std::nothrow ) RR::RData_SIG( pDatagram ) ;
			break ;

		case QType::AAAA :
			pRDat = new ( std::nothrow ) RR::RData_AAAA() ;
			break ;

		case QType::LOC :
			pRDat = new ( std::nothrow ) RR::RData_LOC() ;
			break ;

		case QType::SRV :
			pRDat = new ( std::nothrow ) RR::RData_SRV( pDatagram ) ;
			break ;

		case QType::NAPTR :
			pRDat = new ( std::nothrow ) RR::RData_NAPTR( pDatagram ) ;
			break ;

		case QType::KX :
			pRDat = new ( std::nothrow ) RR::RData_KX( pDatagram ) ;
			break ;

		case QType::CERT :
			pRDat = new ( std::nothrow ) RR::RData_CERT() ;
			break ;

		case QType::A6 :
			pRDat = new ( std::nothrow ) RR::RData_A6() ;
			break ;

		case QType::APL :
			pRDat = new ( std::nothrow ) RR::RData_APL() ;
			break ;

		case QType::DS :
			pRDat = new ( std::nothrow ) RR::RData_DS() ;
			break ;

		case QType::SSHFP :
			pRDat = new ( std::nothrow ) RR::RData_SSHFP() ;
			break ;

		case QType::IPSECKEY :
			pRDat = new ( std::nothrow ) RR::RData_IPSECKEY() ;
			break ;

		case QType::RRSIG :
			pRDat = new ( std::nothrow ) RR::RData_RRSIG( pDatagram ) ;
			break ;

		case QType::NSEC :
			pRDat = new ( std::nothrow ) RR::RData_NSEC() ;
			break ;

		case QType::DNSKEY :
			pRDat = new ( std::nothrow ) RR::RData_DNSKEY() ;
			break ;

		case QType::DHCID :
			pRDat = new ( std::nothrow ) RR::RData_DHCID() ;
			break ;

		case QType::NSEC3 :
			pRDat = new ( std::nothrow ) RR::RData_NSEC3() ;
			break ;

		case QType::NSEC3PARAM :
			pRDat = new ( std::nothrow ) RR::RData_NSEC3PARAM() ;
			break ;

		case QType::TLSA :
			pRDat = new ( std::nothrow ) RR::RData_TLSA() ;
			break ;

		case QType::SMIMEA :
			pRDat = new ( std::nothrow ) RR::RData_SMIMEA() ;
			break ;

		case QType::HIP :
			pRDat = new ( std::nothrow ) RR::RData_HIP() ;
			break ;

		case QType::CDS :
			pRDat = new ( std::nothrow ) RR::RData_CDS() ;
			break ;

		case QType::CDNSKEY :
			pRDat = new ( std::nothrow ) RR::RData_CDNSKEY() ;
			break ;

		case QType::OPENPGPKEY :
			pRDat = new ( std::nothrow ) RR::RData_OPENPGPKEY() ;
			break ;

		case QType::CSYNC :
			pRDat = new ( std::nothrow ) RR::RData_CSYNC() ;
			break ;

		case QType::ZONEMD :
			pRDat = new ( std::nothrow ) RR::RData_ZONEMD() ;
			break ;

		case QType::SVCB :
			pRDat = new ( std::nothrow ) RR::RData_SVCB( pDatagram ) ;
			break ;

		case QType::HTTPS :
			pRDat = new ( std::nothrow ) RR::RData_HTTPS( pDatagram ) ;
			break ;

		case QType::SPF :
			pRDat = new ( std::nothrow ) RR::RData_SPF() ;
			break ;

		case QType::EUI48 :
			pRDat = new ( std::nothrow ) RR::RData_EUI48() ;
			break ;

		case QType::EUI64 :
			pRDat = new ( std::nothrow ) RR::RData_EUI64() ;
			break ;

		case QType::URI :
			pRDat = new ( std::nothrow ) RR::RData_URI() ;
			break ;

		case QType::CAA :
			pRDat = new ( std::nothrow ) RR::RData_CAA() ;
			break ;

		case QType::TA :
			pRDat = new ( std::nothrow ) RR::RData_TA() ;
			break ;

		default :
			pRDat = new ( std::nothrow ) RR::RData_NULL() ;
			break ;
	}

	if( nullptr != pRDat )
	{
		pRDat->Load( pBuf , length ) ;
	}
}


uint8_t const * daniel::dns::Resource::GetName() const
{
	return pName ;
}


uint16_t daniel::dns::Resource::GetRData( uint8_t * pBuf , uint16_t const & length ) const
{
	if( 1 > length || nullptr == pBuf ) 
	{
		return 0 ;
	}

	if( nullptr == pRDat )
	{
		return 0 ;
	}

	return pRDat->ToNullStr( pBuf , length ) ;
}


daniel::dns::QType daniel::dns::Resource::GetType() const
{
	return qtype ;
}


daniel::dns::QClass daniel::dns::Resource::GetClass() const
{
	return qclass ;
}


int32_t daniel::dns::Resource::GetTTL() const
{
	return ttl ;
}


uint16_t daniel::dns::Resource::GetRdLen() const
{
	return rdlength ;
}


daniel::dns::RR::RData const * daniel::dns::Resource::GetRData() const
{
	return pRDat ;
}