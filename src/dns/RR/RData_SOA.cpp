#include "dns/RR/RData_SOA.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_SOA::RData_SOA( uint8_t const * pRef )
	: RData( pRef ) , pMname( nullptr ) , pRname( nullptr ) , serial( 0 ) , refresh( 0 ) , retry( 0 ) , expire( 0 ) , minimum( 0 )
{

}


daniel::dns::RR::RData_SOA::~RData_SOA()
{
	Initalize() ;
}


void daniel::dns::RR::RData_SOA::Initalize()
{
	if( nullptr != pMname )
	{
		delete [] pMname ;
		pMname = nullptr ;
	}

	if( nullptr != pRname )
	{
		delete [] pRname ;
		pRname = nullptr ;
	}

	serial  = 0 ;
	refresh = 0 ;
	retry   = 0 ;
	expire  = 0 ;
	minimum = 0 ;
}


uint16_t daniel::dns::RR::RData_SOA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pMname || nullptr == pRname )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << reinterpret_cast< char const * >( pMname ) << " " 
       << reinterpret_cast< char const * >( pRname ) << " " 
       << serial  << " " 
       << refresh << " " 
       << retry   << " " 
       << expire  << " " 
       << minimum ;

	std::string str = ss.str() ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos ) 
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_SOA::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}


	uint16_t slen[ 2 ] = { 0 , 0 } ;
	uint16_t blen[ 2 ] = { 0 , 0 } ;

	slen[ 0 ] = SkipDName( & ( pData[         0 ] ) , length ) ; 
	slen[ 1 ] = SkipDName( & ( pData[ slen[ 0 ] ] ) , length - slen[ 0 ] ) ;

	blen[ 0 ] = GetDNDataLen( & pData[       0   ] ) ;
	blen[ 1 ] = GetDNDataLen( & pData[ slen[ 0 ] ] ) ;

	if( 1 > blen[ 0 ] || 1 > blen[ 1 ] )
	{
		return false ;
	}


	Initalize() ;

	pMname = new ( std::nothrow ) uint8_t [ blen[ 0 ] + 1 ] ;
	pRname = new ( std::nothrow ) uint8_t [ blen[ 1 ] + 1 ] ;

	if( nullptr == pMname || nullptr == pRname )
	{
		Initalize() ;
		return false ;
	} 

	blen[ 0 ] = GetDNData( pMname , blen[ 0 ] + 1 , & pData[       0   ] ) ;
	blen[ 1 ] = GetDNData( pRname , blen[ 1 ] + 1 , & pData[ slen[ 0 ] ] ) ;


	uint16_t pos = slen[ 0 ] + slen[ 1 ] ;

	serial
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	refresh
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	retry
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	expire
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	pos += 4 ;

	minimum
		= ( ( pData[ pos + 0 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ pos + 1 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ pos + 2 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ pos + 3 ] <<  0 ) & 0x000000FF ) ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_SOA::GetMName() const
{
	return pMname ;
}


uint8_t const * daniel::dns::RR::RData_SOA::GetRName() const
{
	return pRname ;
}


uint32_t daniel::dns::RR::RData_SOA::GetSerial() const
{
	return serial ;
}


uint32_t daniel::dns::RR::RData_SOA::GetRefresh() const
{
	return refresh ;
}


uint32_t daniel::dns::RR::RData_SOA::GetRetry() const
{
	return retry ;
}


uint32_t daniel::dns::RR::RData_SOA::GetExpire() const
{
	return expire ;
}


uint32_t daniel::dns::RR::RData_SOA::GetMinimum() const
{
	return minimum ;
}