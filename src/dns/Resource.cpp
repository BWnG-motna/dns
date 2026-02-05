#include "dns/Resource.h"
#include "view/HexView.h"

#include <cstring>


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
// WKS
#include "dns/RR/RData_PTR.h"
#include "dns/RR/RData_HINFO.h"
#include "dns/RR/RData_MINFO.h"
#include "dns/RR/RData_MX.h"
#include "dns/RR/RData_TXT.h"
#include "dns/RR/RData_RP.h"

#include "dns/RR/RData_AAAA.h"
#include "dns/RR/RData_LOC.h"

#include "dns/RR/RData_SRV.h"

#include "dns/RR/RData_DS.h"
#include "dns/RR/RData_SSHFP.h"
#include "dns/RR/RData_RRSIG.h"
#include "dns/RR/RData_NSEC.h"
#include "dns/RR/RData_DNSKEY.h"
#include "dns/RR/RData_NSEC3.h"

#include "dns/RR/RData_TLSA.h"
#include "dns/RR/RData_SMIMEA.h"

#include "dns/RR/RData_OPENPGPKEY.h"

#include "dns/RR/RData_SVCB.h"
#include "dns/RR/RData_HTTPS.h"

#include "dns/RR/RData_CAA.h"



#undef NULL


daniel::dns::Resource::Resource()
	: pDataGram( nullptr ) , nameLen( 0 ) , qtype( QType::A ) , qclass( QClass::IN ) , ttl( 0 ) , rdlength( 0 ) , pRDat( nullptr )
{
	name[ 0 ] = '\0' ;
}


daniel::dns::Resource::~Resource()
{
	if( nullptr != pRDat )
	{
		delete pRDat ;
		pRDat = nullptr ;
	}
}


uint16_t daniel::dns::Resource::Load( uint8_t const * pBuf , uint16_t const & length , uint8_t const * pRef )
{
	if( 1 > length || nullptr == pBuf || nullptr == pRef  )
	{
		return 0 ;
	}

	pDataGram = pRef ;

	uint16_t bPos = 0 ;
	uint16_t nPos = 0 ;

	bool isCompressed = false ;

	while( '\0' != pBuf[ bPos ] && bPos < length )
	{
		if( 0xC0 <= ( pBuf[ bPos ] & 0xC0 ) )
		{
			if( nameMaxLen < ( nPos + 2 ) )
			{
				return 0 ;
			}

			name[ nPos++ ] = pBuf[ bPos++ ] ;
			name[ nPos++ ] = pBuf[ bPos++ ] ;

			isCompressed = true ;
			break ;
		}

		if( nameMaxLen <= nPos )
		{
			return 0 ;
		}

		name[ nPos++ ] = pBuf[ bPos++ ] ;
	}

	if( bPos >= length )
	{
		return 0 ;
	}

	if( false == isCompressed && '\0' == pBuf[ bPos ] )
	{
		++bPos ;
	}

	name[ nPos ] = '\0' ;
	nameLen = nPos ;

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

	switch( qtype )
	{
		case QType::A :
			pRDat = new ( std::nothrow ) RR::RData_A() ;
			break ;

		case QType::NS :
			pRDat = new ( std::nothrow ) RR::RData_NS( pDataGram ) ;
			break ;

		case QType::MD :
			pRDat = new ( std::nothrow ) RR::RData_MD( pDataGram ) ;
			break ;

		case QType::MF :
			pRDat = new ( std::nothrow ) RR::RData_MF( pDataGram ) ;
			break ;

		case QType::CNAME :
			pRDat = new ( std::nothrow ) RR::RData_CNAME( pDataGram ) ;
			break ;

		case QType::SOA :
			pRDat = new ( std::nothrow ) RR::RData_SOA( pDataGram ) ;
			break ;

		case QType::MB :
			pRDat = new ( std::nothrow ) RR::RData_MB( pDataGram ) ;
			break ;

		case QType::MG :
			pRDat = new ( std::nothrow ) RR::RData_MG( pDataGram ) ;
			break ;

		case QType::MR :
			pRDat = new ( std::nothrow ) RR::RData_MR( pDataGram ) ;
			break ;

		case QType::NULL :
			pRDat = new ( std::nothrow ) RR::RData_NULL() ;
			break ;

		case QType::PTR :
			pRDat = new ( std::nothrow ) RR::RData_PTR( pDataGram ) ;
			break ;

		case QType::HINFO :
			pRDat = new ( std::nothrow ) RR::RData_HINFO( pDataGram ) ;
			break ;

		case QType::MINFO :
			pRDat = new ( std::nothrow ) RR::RData_MINFO( pDataGram ) ;
			break ;

		case QType::MX :
			pRDat = new ( std::nothrow ) RR::RData_MX( pDataGram ) ;
			break ;

		case QType::TXT :
			pRDat = new ( std::nothrow ) RR::RData_TXT() ;
			break ;

		case QType::RP :
			pRDat = new ( std::nothrow ) RR::RData_RP( pDataGram ) ;
			break ;

		case QType::AAAA :
			pRDat = new ( std::nothrow ) RR::RData_AAAA() ;
			break ;

		case QType::LOC :
			pRDat = new ( std::nothrow ) RR::RData_LOC() ;
			break ;

		case QType::SRV :
			pRDat = new ( std::nothrow ) RR::RData_SRV( pDataGram ) ;
			break ;

		case QType::DS :
			pRDat = new ( std::nothrow ) RR::RData_DS() ;
			break ;

		case QType::SSHFP :
			pRDat = new ( std::nothrow ) RR::RData_SSHFP() ;
			break ;

		case QType::RRSIG :
			pRDat = new ( std::nothrow ) RR::RData_RRSIG( pDataGram ) ;
			break ;

		case QType::NSEC :
			pRDat = new ( std::nothrow ) RR::RData_NSEC() ;
			break ;

		case QType::DNSKEY :
			pRDat = new ( std::nothrow ) RR::RData_DNSKEY() ;
			break ;

		case QType::NSEC3 :
			pRDat = new ( std::nothrow ) RR::RData_NSEC3() ;
			break ;

		case QType::OPENPGPKEY :
			pRDat = new ( std::nothrow ) RR::RData_OPENPGPKEY() ;
			break ;

		case QType::TLSA :
			pRDat = new ( std::nothrow ) RR::RData_TLSA() ;
			break ;

		case QType::SMIMEA :
			pRDat = new ( std::nothrow ) RR::RData_SMIMEA() ;
			break ;

		case QType::SVCB :
			pRDat = new ( std::nothrow ) RR::RData_SVCB( pDataGram ) ;
			break ;

		case QType::HTTPS :
			pRDat = new ( std::nothrow ) RR::RData_HTTPS( pDataGram ) ;
			break ;

		case QType::CAA :
			pRDat = new ( std::nothrow ) RR::RData_CAA() ;
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


uint16_t daniel::dns::Resource::GetDNData( 
	uint8_t        * pBuf   , 
	uint16_t const & length , 
	uint8_t  const * pRef   ,
	bool     const & fqdn   ) const
{
	if( 1 > length || nullptr == pBuf || nullptr == pRef )
	{
		return 0 ;
	}

	uint8_t const * p  = pRef ;
	uint16_t len  = 0 ;
	uint16_t bPos = 0 ;

	while( '\0' != *p )
	{
		if( 0xC0 <= ( *p & 0xC0 ) )
		{
			uint16_t offset
				= ( ( ( 0x3F & *( p + 0 ) ) << 8 ) & 0xFF00 ) 
				| ( ( ( 0xFF & *( p + 1 ) ) << 0 ) & 0x00FF ) ;

			p = pDataGram + offset ;

			continue ;
		}

		len = ( *p++ ) ;

		for( uint8_t pos = 0 ; pos < len ; ++pos ) 
		{
			if( length <= bPos )
			{
				return bPos ;
			}
			pBuf[ bPos++ ] = *p++ ;
		}

		if( ( true == fqdn || '\0' != *p ) && ( length <= bPos ) )
		{
			return bPos ;
		}

		if( true == fqdn )
		{
			pBuf[ bPos++ ] = '.' ;
		}
		else if( '\0' != *p )
		{
			pBuf[ bPos++ ] = '.' ;
		}
	}

	pBuf[ bPos ] = '\0' ;
	
	return bPos ;
}


uint16_t daniel::dns::Resource::GetName( uint8_t * pBuf , uint16_t const & length ) const
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}

	return GetDNData( pBuf , length , name , false ) ;
}


uint16_t daniel::dns::Resource::GetRData( uint8_t * pBuf , uint16_t const & length ) const
{
	if( 1 > length || nullptr == pBuf ) 
	{
		return 0 ;
	}

	if( nullptr == pRDat )
	{

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