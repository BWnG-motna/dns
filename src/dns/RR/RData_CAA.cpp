#include "dns/RR/RData_CAA.h"


#include <sstream>
#include <cctype>


daniel::dns::RR::RData_CAA::RData_CAA()
	: RData( nullptr ) , flags( 0 ) , taglen( 0 ) , valuelen( 0 )
{
	  tag[ 0 ] = '\0' ;
	value[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_CAA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	std::stringstream ss ;

	ss << static_cast< uint16_t>( flags  )        << ' '
	   << reinterpret_cast< char const * >( tag ) << ' ' ;

	if( 0 < valuelen )
	{
		ss << "\"" ;
	}
	for( uint16_t pos = 0 ; pos < valuelen ; ++pos )
	{
		if( true == static_cast< bool >( std::isprint( value[ pos ] ) ) )
		{
			ss << value[ pos ] ;
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

	flags  = pData[ 0 ] ;
	taglen = pData[ 1 ] ;

	if( ( 2 + taglen ) > length )
	{
		return false ;
	}

	uint16_t calValLen = length - ( 2 + taglen ) ;

	if( valMaxLen < calValLen )
	{
		return false ;
	}

	for( uint8_t pos = 0 ; pos < taglen ; ++pos )
	{
		tag[ pos ] = pData[ 2 + pos ] ;
	}

	tag[ taglen ] = '\0' ;

	uint16_t valuePos = 0 ;
	for( uint16_t pos = 2 + taglen ; pos < length ; ++pos )
	{
		value[ valuePos++ ] = pData[ pos ] ;

	}

	valuelen = valuePos ;
	
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
	return tag ;
}


uint8_t const * daniel::dns::RR::RData_CAA::GetValue() const
{
	return value ;
}