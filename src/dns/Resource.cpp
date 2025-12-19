#include "dns/Resource.h"
#include "view/HexView.h"


#include "dns/RR/RData_A.h"
#include "dns/RR/RData_AAAA.h"
#include "dns/RR/RData_CNAME.h"
#include "dns/RR/RData_HINFO.h"
#include "dns/RR/RData_MB.h"
#include "dns/RR/RData_MD.h"
#include "dns/RR/RData_MF.h"
#include "dns/RR/RData_MG.h"
#include "dns/RR/RData_MINFO.h"
#include "dns/RR/RData_MR.h"
#include "dns/RR/RData_MX.h"
#include "dns/RR/RData_NS.h"
#include "dns/RR/RData_NULL.h"
#include "dns/RR/RData_PTR.h"
#include "dns/RR/RData_RP.h"
#include "dns/RR/RData_SOA.h"
#include "dns/RR/RData_TXT.h"


#undef NULL


daniel::dns::Resource::Resource()
	: nameLen( 0 ) , qtype( QType::A ) , qclass( QClass::IN ) , ttl( 0 ) , rdlength( 0 ) , pRDat( nullptr )
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


uint16_t daniel::dns::Resource::Load( uint8_t const * pBuf , uint16_t const & length , uint8_t * pRef )
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}

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

	pDataGram = pRef ;

	return bPos + 10 + rdlength ;
}


#if 0
uint16_t daniel::dns::Resource::Save( uint8_t * pBuf , uint16_t const & length )
{
	return 0 ;
}
#endif


void daniel::dns::Resource::MakeRData( uint8_t const * pBuf , uint32_t const & length )
{
	if( nullptr == pBuf ) 
	{
		pRDat = nullptr ;
		return ;
	}

	switch( qtype )
	{
		case QType::A :
			pRDat = new RR::RData_A() ;
			break ;

		case QType::AAAA :
			pRDat = new RR::RData_AAAA() ;
			break ;

		case QType::CNAME :
			pRDat = new RR::RData_CNAME( pDataGram ) ;
			break ;

		case QType::HINFO :
			pRDat = new RR::RData_HINFO( pDataGram ) ;
			break ;

		case QType::MB :
			pRDat = new RR::RData_MB( pDataGram ) ;
			break ;

		case QType::MD :
			pRDat = new RR::RData_MD( pDataGram ) ;
			break ;

		case QType::MF :
			pRDat = new RR::RData_MF( pDataGram ) ;
			break ;

		case QType::MG :
			pRDat = new RR::RData_MG( pDataGram ) ;
			break ;

		case QType::MINFO :
			pRDat = new RR::RData_MINFO( pDataGram ) ;
			break ;

		case QType::MR :
			pRDat = new RR::RData_MR( pDataGram ) ;
			break ;

		case QType::MX :
			pRDat = new RR::RData_MX( pDataGram ) ;
			break ;

		case QType::NS :
			pRDat = new RR::RData_NS( pDataGram ) ;
			break ;

		case QType::NULL :
			pRDat = new RR::RData_NULL() ;
			break ;

		case QType::PTR :
			pRDat = new RR::RData_PTR( pDataGram ) ;
			break ;

		case QType::RP :
			pRDat = new RR::RData_RP( pDataGram ) ;
			break ;

		case QType::SOA :
			pRDat = new RR::RData_SOA( pDataGram ) ;
			break ;

		case QType::TXT :
			pRDat = new RR::RData_TXT() ;
			break ;

		case QType::A6  :
		case QType::WKS :

		default :
			pRDat = nullptr ;
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
		pBuf[ 0 ] = '\0' ;
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
