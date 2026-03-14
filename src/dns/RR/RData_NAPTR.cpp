#include "dns/RR/RData_NAPTR.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_NAPTR::RData_NAPTR( uint8_t const * pRef )
	: RData( pRef ) , order( 0 ) , preference( 0 ) , pFlags( nullptr ) , pServices( nullptr ) , pRegexp( nullptr ) , pReplacement( nullptr )
{

}


daniel::dns::RR::RData_NAPTR::~RData_NAPTR()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NAPTR::Initialize()
{
	if( nullptr != pFlags )
	{
		delete [] pFlags ;
		pFlags = nullptr ;
	}

	if( nullptr != pServices )
	{
		delete [] pServices ;
		pServices = nullptr ;
	}

	if( nullptr != pRegexp )
	{
		delete [] pRegexp ;
		pRegexp = nullptr ;
	}

	if( nullptr != pReplacement )
	{
		delete [] pReplacement ;
		pReplacement = nullptr ;
	}

	order      = 0 ;
	preference = 0 ;
}


uint16_t daniel::dns::RR::RData_NAPTR::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pReplacement )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << order      << " "
	   << preference << " " ;

	if( nullptr != pFlags )
	{
		ss << reinterpret_cast< char const * >( pFlags    ) << " " ;
	}

	if( nullptr != pServices )
	{
		ss << reinterpret_cast< char const * >( pServices ) << " " ;
	}

	if( nullptr != pRegexp )
	{
		ss << reinterpret_cast< char const * >( pRegexp   ) << " " ;
	}

	ss << reinterpret_cast< char const * >( pReplacement ) ;
	
	std::string s = ss.str() ;
	uint16_t len  = static_cast< uint16_t >( s.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_NAPTR::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 5 > length )
	{
		return false ;
	}

	Initialize() ;

	order 
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;
	
	preference
		= ( ( pData[ 2 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	uint16_t pos = 0 ;
	uint8_t  len = 0 ;

	pos = 4 ;
	
	uint8_t ** p[ 3 ] = { & pFlags , & pServices , & pRegexp } ;

	for( uint8_t cnt = 0 ; cnt < 3 ; ++cnt )
	{
		len = pData[ pos++ ] ;

		if( length < ( pos + len ) )
		{
			Initialize() ;
			return false ;
		}

		if( 0 < len ) 
		{
			uint8_t * & ptr = *p[ cnt ] ;
			ptr = new ( std::nothrow ) uint8_t [ len + 1 ] ;
			if( nullptr == p[ cnt ] )
			{
				Initialize() ;
				return false ;
			}

			uint16_t datPos = 0 ;
			for( datPos = 0 ; datPos < len ; ++datPos )
			{
				ptr[ datPos ] = pData[ pos++ ] ;
			}

			ptr[ datPos ] = '\0' ;
		}
	}

	uint16_t    replen = GetDNDataLen( & ( pData[ pos ] ) ) ;
	uint16_t allocSize = ( 0 < replen ) ? ( replen + 1 ) : 2 ;

	if( length < ( replen + pos ) )
	{
		Initialize() ;
		return false ;
	}

	pReplacement = new ( std::nothrow ) uint8_t [ allocSize ] ;
	if( nullptr == pReplacement )
	{
		Initialize() ;
		return false ;
	}

	if( 0 < replen )
	{
		len = GetDNData( pReplacement , replen , & ( pData[ pos ] ) ) ;
	}
	else
	{
		pReplacement[ 0 ] = '.'  ;
		pReplacement[ 1 ] = '\0' ;
	}

	return true ;
}


uint16_t daniel::dns::RR::RData_NAPTR::GetOrder() const
{
	return order ;
}


uint16_t daniel::dns::RR::RData_NAPTR::GetPreference() const
{
	return preference ;
}


uint8_t const * daniel::dns::RR::RData_NAPTR::GetFlags() const
{
	return pFlags ;
}


uint8_t const * daniel::dns::RR::RData_NAPTR::GetServices() const
{
	return pServices ;
}


uint8_t const * daniel::dns::RR::RData_NAPTR::GetRegexp() const
{
	return pRegexp ;
}


uint8_t const * daniel::dns::RR::RData_NAPTR::GetReplacement() const
{
	return pReplacement ;
}