#include "dns/RR/RData_ISDN.h"


#include <sstream>
#include <memory>

#include <iostream>


daniel::dns::RR::RData_ISDN::RData_ISDN()
	: RData( nullptr ) , pAddr( nullptr ) , pSA( nullptr )
{

}


daniel::dns::RR::RData_ISDN::~RData_ISDN()
{
	Initialize() ;
}


void daniel::dns::RR::RData_ISDN::Initialize()
{
	if( nullptr != pAddr )
	{
		delete [] pAddr ;
		pAddr = nullptr ;
	}

	if( nullptr != pSA )
	{
		delete [] pSA ;
		pSA = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_ISDN::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pAddr )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << reinterpret_cast< char const * >( pAddr ) ;

	if( nullptr != pSA )
	{
		ss << " " << reinterpret_cast< char const * >( pSA ) ;
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


bool daniel::dns::RR::RData_ISDN::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	

	/// address 

	uint8_t addrLen = pData[ 0 ] ;

	if( 0 == addrLen )
	{
		return false ;
	}

	for( uint8_t pos = 0 ; pos < addrLen ; ++pos )
	{
		uint8_t const & ch = pData[ 1 + pos ] ;
		if( '0' > ch || '9' < ch )
		{
			return false ;
		}
	}

	pAddr = new ( std::nothrow ) uint8_t [ addrLen + 1 ] ;
	if( nullptr == pAddr )
	{
		Initialize() ;
		return false ;
	}

	for( uint8_t pos = 0 ; pos < addrLen ; ++pos )
	{
		pAddr[ pos ] = pData[ 1 + pos ] ;
	}

	pAddr[ addrLen ] = '\0' ;


	/// sa

	uint8_t saLen = 0 ;
	if( ( 1 + addrLen ) != length )
	{
		saLen = pData[ 1 + addrLen ] ;
	}

	for( uint8_t pos = 0 ; pos < saLen ; ++pos )
	{
		uint8_t const & ch = pData[ 1 + addrLen + 1 + pos ] ;
		if( '0' > ch || '9' < ch )
		{
			Initialize() ;
			return false ;
		}
	}

	pSA = new ( std::nothrow ) uint8_t [ saLen + 1 ] ;
	if( nullptr == pSA )
	{
		Initialize() ;
		return false ;
	}

	for( uint8_t pos = 0 ; pos < saLen ; ++pos )
	{
		pSA[ pos ] = pData[ 1 + addrLen + 1 + pos ] ;
	}

	pSA[ saLen ] = '\0' ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_ISDN::GetAddress() const
{
	return pAddr ;
}


uint8_t const * daniel::dns::RR::RData_ISDN::GetSA() const
{
	return pSA ;
}