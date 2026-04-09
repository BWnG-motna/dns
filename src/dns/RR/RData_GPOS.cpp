#include "dns/RR/RData_GPOS.h"


#include <sstream>


daniel::dns::RR::RData_GPOS::RData_GPOS()
	: RData( nullptr ) , pLong( nullptr ) , pLat( nullptr ) , pAlt( nullptr ) 
{

}


daniel::dns::RR::RData_GPOS::~RData_GPOS()
{
	Initialize() ;
}


void daniel::dns::RR::RData_GPOS::Initialize()
{
	if( nullptr != pLong )
	{
		delete [] pLong ;
		pLong = nullptr ;
	}

	if( nullptr != pLat )
	{
		delete [] pLat ;
		pLat = nullptr ;
	}

	if( nullptr != pAlt )
	{
		delete [] pAlt ;
		pAlt = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_GPOS::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pLong || nullptr == pLat || nullptr == pAlt )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << reinterpret_cast< char const * >( pLong ) << " "
	   << reinterpret_cast< char const * >( pLat  ) << " "
	   << reinterpret_cast< char const * >( pAlt  ) ;

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


bool daniel::dns::RR::RData_GPOS::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	uint8_t  step = 0 ;
	uint16_t pos  = 0 ;

	Initialize() ;

	while( step < 3 )
	{
		if( length <= pos )
		{
			Initialize() ;
			return false ;
		}


		uint8_t len = pData[ pos ] ;
		++pos ;

		if( length < ( static_cast< uint32_t >( pos ) + static_cast< uint32_t >( len ) ) )
		{
			Initialize() ;
			return false ;
		}

		uint8_t * p = new ( std::nothrow ) uint8_t [ len + 1 ] ;
		if( nullptr == p )
		{
			Initialize() ;
			return false ;
		}

		for( uint8_t dPos = 0 ; dPos < len ; ++dPos )
		{
			p[ dPos ] = pData[ pos + dPos ] ;
		}

		p[ len ] = '\0' ;

		/**/ if( 0 == step )
		{
			pLong = p ;
		}
		else if( 1 == step )
		{
			pLat  = p ;
		}
		else if( 2 == step )
		{
			pAlt  = p ;
		}
		else
		{
			Initialize() ;
			return false ;
		}

		++step ;
		pos = pos + len ;
	}

	return true ;
}


uint8_t const * daniel::dns::RR::RData_GPOS::GetLongitude() const
{
	return pLong ;
}


uint8_t const * daniel::dns::RR::RData_GPOS::GetLatitude() const
{
	return pLat ;
}


uint8_t const * daniel::dns::RR::RData_GPOS::GetAltitude() const
{
	return pAlt ;
}