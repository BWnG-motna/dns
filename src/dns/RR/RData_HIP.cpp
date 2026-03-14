#include "dns/RR/RData_HIP.h"


#include <sstream>
#include <iomanip>
#include <memory>

#include <iostream>


daniel::dns::RR::RData_HIP::RData_HIP()
	: RData( nullptr ) , hitLen( 0 ) , pkAlgo( 0 ) , pkLen( 0 ) , pHit( nullptr ) , pKey( nullptr ) , pRvsList( nullptr )
{

}


daniel::dns::RR::RData_HIP::~RData_HIP()
{
	Initialize() ;
}


void daniel::dns::RR::RData_HIP::Initialize()
{
	if( nullptr != pHit )
	{
		delete [] pHit ;
		pHit = nullptr ;
	}

	if( nullptr != pKey )
	{
		delete [] pKey ;
		pKey = nullptr ;
	}

	if( nullptr != pRvsList )
	{
		delete pRvsList ;
		pRvsList = nullptr ;
	}

	hitLen = 0 ;
	pkAlgo = 0 ;
	pkLen  = 0 ;
}


uint16_t daniel::dns::RR::RData_HIP::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pHit || nullptr == pKey )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( pkAlgo ) << " "
	   << static_cast< uint16_t >( pkLen  ) << " " 
	   << static_cast< uint16_t >( hitLen ) << " " ;

	for( uint8_t pos = 0 ; pos < hitLen ; ++pos ) 
	{
		if( 0 != pos && 0 == ( pos % 2 ) && ( 0 == ( hitLen % 2 ) ) )
		{
			ss << ":" ;
		}

		ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( pHit[ pos ] ) ;
	}

	ss << std::dec << std::setw( 0 ) ;

	if( nullptr != pRvsList )
	{
		ds::LinkedList< HIP::RVS >::const_iterator posIter = pRvsList->begin() ;
		ds::LinkedList< HIP::RVS >::const_iterator endIter = pRvsList->end() ;

		while( posIter != endIter )
		{
			HIP::RVS const & rvs = *posIter++ ;
			uint8_t  const * p   = rvs.Get() ;
			
			ss << " " << reinterpret_cast< char const * >( p ) ;
		}
	}


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


bool daniel::dns::RR::RData_HIP::Load( uint8_t const * pData , uint16_t const & length )
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


	hitLen = pData[ 0 ] ;
	pkAlgo = pData[ 1 ] ;
	pkLen  = ( ( pData[ 2 ] << 8 ) & 0xFF00 )
	       | ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	if( ( 4 + hitLen + static_cast< uint32_t >( pkLen ) ) > length )
	{
		Initialize() ;
		return false ;
	}

	pHit = new ( std::nothrow ) uint8_t [ hitLen ] ;
	pKey = new ( std::nothrow ) uint8_t [ pkLen  ] ;

	if( nullptr == pHit || nullptr == pKey )
	{
		Initialize() ;
		return false ;
	}

	for(  uint8_t pos = 0 ; pos < hitLen ; ++pos )
	{
		pHit[ pos ] = pData[ 4 + pos ] ;
	}

	for( uint16_t pos = 0 ; pos < pkLen  ; ++pos )
	{
		pKey[ pos ] = pData[ 4 + hitLen + pos ] ;
	}

	uint32_t pos = static_cast< uint32_t >( 4 + hitLen + static_cast< uint32_t >( pkLen ) ) ;
	if( pos == length )
	{
		return true ;
	}

	uint16_t next = 0 ;

	do
	{
		uint16_t len  = 0 ;

		len = GetDNDataLen( & ( pData[ pos ] ) , true ) ;
		if( 1 > len )
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

		len = GetDNData( p , len + 1 , &( pData[ pos ] ) , true ) ;
		
		if( nullptr == pRvsList )
		{
			pRvsList = new ( std::nothrow ) ds::LinkedList< HIP::RVS >() ;
			if( nullptr == pRvsList )
			{
				delete [] p ;
				Initialize() ;

				return false ;
			}
		}

		HIP::RVS * pRvs = new ( std::nothrow ) HIP::RVS() ;

		pRvs->Set( p , len ) ;
		pRvsList->Insert( pRvs ) ;

		next = SkipDName( &( pData[ pos ] ) , length - pos ) ;
		pos  = pos + next ;

	} while( pos < length ) ;

	return true ;
}


uint8_t daniel::dns::RR::RData_HIP::GetHitLen() const
{
	return hitLen ;
}


uint8_t daniel::dns::RR::RData_HIP::GetPkAlgo() const
{
	return pkAlgo ;
}


uint16_t daniel::dns::RR::RData_HIP::GetPkLen() const
{
	return pkLen ;
}


uint8_t const * daniel::dns::RR::RData_HIP::GetHit() const
{
	return pHit ;

}


uint8_t const * daniel::dns::RR::RData_HIP::GetPKey() const
{
	return pKey ;
}