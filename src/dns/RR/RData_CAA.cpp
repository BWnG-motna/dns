#include "dns/RR/RData_CAA.h"


#include <sstream>
#include <cctype>
#include <memory>


daniel::dns::RR::RData_CAA::RData_CAA()
	: RData( nullptr ) , flags( 0 ) , 
	  taglen  ( 0 ) , pTag  ( nullptr ) , 
	  valuelen( 0 ) , pValue( nullptr )
{

}


daniel::dns::RR::RData_CAA::~RData_CAA()
{
	Initalize() ;
}


void daniel::dns::RR::RData_CAA::Initalize()
{
	if( nullptr != pTag )
	{
		delete [] pTag ;
		pTag = nullptr ;
	}

	if( nullptr != pValue )
	{
		delete [] pValue ;
		pValue = nullptr ;
	}

	flags    = 0 ;
	taglen   = 0 ;
	valuelen = 0 ;
}


uint16_t daniel::dns::RR::RData_CAA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}
	
	if( nullptr == pTag || nullptr == pValue )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t>( flags  )         << ' '
	   << reinterpret_cast< char const * >( pTag ) << ' ' ;

	if( 0 < valuelen )
	{
		ss << "\"" ;
	}
	for( uint16_t pos = 0 ; pos < valuelen ; ++pos )
	{
		if( true == static_cast< bool >( std::isprint( pValue[ pos ] ) ) )
		{
			ss << pValue[ pos ] ;
		}
		else
		{
			ss << "." ;
		}
	}
	if( 0 < valuelen )
	{
		ss << "\"" ;
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


bool daniel::dns::RR::RData_CAA::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 2 > length )
	{
		return false ;
	}

	if( 1 > pData[ 1 ] )
	{
		return false ;
	}

	Initalize() ;

	flags  = pData[ 0 ] ;
	taglen = pData[ 1 ] ;

	if( ( 2 + taglen ) > length )
	{
		Initalize() ;
		return false ;
	}

	valuelen = length - ( 2 + taglen ) ;

	pTag   = new ( std::nothrow ) uint8_t [ taglen + 1 ] ;
	pValue = new ( std::nothrow ) uint8_t [ valuelen   ] ;

	if( nullptr == pTag || nullptr == pValue )
	{
		Initalize() ;
		return false ;
	}

	for( uint8_t pos = 0 ; pos < taglen ; ++pos )
	{
		pTag[ pos ] = pData[ 2 + pos ] ;
	}

	pTag[ taglen ] = '\0' ;

	uint16_t valuePos = 0 ;
	for( uint16_t pos = 2 + taglen ; pos < length ; ++pos )
	{
		pValue[ valuePos++ ] = pData[ pos ] ;

	}
	
	return true ;
}


bool daniel::dns::RR::RData_CAA::IsCritical() const
{
	return ( 0 < ( flags & 0x80 ) ) ? true : false ;
}


uint8_t daniel::dns::RR::RData_CAA::GetFlags() const
{
	return flags ;
}


uint8_t daniel::dns::RR::RData_CAA::GetTagLen() const
{
	return taglen ;
}


uint16_t daniel::dns::RR::RData_CAA::GetValueLen() const
{
	return valuelen ;
}


uint8_t const * daniel::dns::RR::RData_CAA::GetTag() const
{
	return pTag ;
}


uint8_t const * daniel::dns::RR::RData_CAA::GetValue() const
{
	return pValue ;
}