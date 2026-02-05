#include "dns/RR/SVC/SvcParam.h"
#include "dns/QType.h"

#include "baseEncoding/Base64.h"


#include <sstream>


daniel::dns::RR::SVC::SvcParam::SvcParam()
	: key( SVC::SvcKey::reserved ) , len( 0 ) , isSet( false )
{
	value[ 0 ] = '\0' ;
}


daniel::dns::RR::SVC::SvcParam::SvcParam( uint16_t const & _key , uint8_t const * pDat , uint16_t const & _len )
	: key( enumFromUint16< SvcKey >( _key ) ) , len( _len ) , isSet( false )
{
	if( nullptr == pDat )
	{
		return ;
	}

	if( false == IsValidValue() )
	{
		isSet = false ;
		return ;
	}

	for( uint8_t pos = 0 ; pos < len ; ++pos )
	{
		value[ pos ] = pDat[ pos ] ;
	}

	isSet = true ;
}


daniel::dns::RR::SVC::SvcParam::SvcParam( SvcKey const & _key , uint8_t const * pDat , uint16_t const & _len )
	: key( _key ) , len( _len ) , isSet( false )
{
	if( nullptr == pDat )
	{
		return ;
	}

	if( false == IsValidValue() )
	{
		isSet = false ;
		return ;
	}

	for( uint8_t pos = 0 ; pos < len ; ++pos )
	{
		value[ pos ] = pDat[ pos ] ;
	}

	isSet = true ;
}


bool daniel::dns::RR::SVC::SvcParam::IsSet() const
{
	return isSet ;
}


void daniel::dns::RR::SVC::SvcParam::UnSet()
{
	isSet = false ;
	key   = SvcKey::reserved ;
	len   = 0 ;
}


void daniel::dns::RR::SVC::SvcParam::SetKey( uint16_t const & _key )
{
	key = enumFromUint16< SvcKey >( _key ) ;
}


void daniel::dns::RR::SVC::SvcParam::SetKey( SvcKey const & _key )
{
	key = _key ;
}


void daniel::dns::RR::SVC::SvcParam::SetValue( uint8_t const * pDat , uint16_t const & _len )
{
	if( nullptr == pDat )
	{
		return ;
	}

	len = _len ;

	if( false == IsValidValue() )
	{
		isSet = false ;
		return ;
	}

	for( uint8_t pos = 0 ; pos < len ; ++pos )
	{
		value[ pos ] = pDat[ pos ] ;
	}

	isSet = true ;
}


daniel::dns::RR::SVC::SvcKey daniel::dns::RR::SVC::SvcParam::GetKey() const
{
	return key ;
}


uint16_t daniel::dns::RR::SVC::SvcParam::GetLen() const
{
	return len ;
}


uint8_t const * daniel::dns::RR::SVC::SvcParam::GetValue() const
{
	return value ;
}


bool daniel::dns::RR::SVC::SvcParam::IsValidValue() const
{
	switch( key )
	{
		case SvcKey::mandatory :
			return ( 0 == ( len % 2 ) ) ;

		case SvcKey::alpn :
			return true ;

		case SvcKey::no_default_alpn :
			return ( 0 == len ) ;

		case SvcKey::port :
			return ( 2 == len ) ;

		case SvcKey::ech :
			return ( 0 < len ) ;

		case SvcKey::ipv4hint :
			return ( 0 == ( len %  4 ) ) ;

		case SvcKey::ipv6hint :
			return ( 0 == ( len % 16 ) ) ;

		case SvcKey::reserved :
			return false ;

		default :
			return true ;
	}
}


std::string daniel::dns::RR::SVC::SvcParam::ToStr() const
{
	std::string str = "" ;

	if( false == IsValidValue() )
	{
		return str ;
	}

	switch( key )
	{
		case SvcKey::mandatory :
			return str += "mandatory=" + MandatoryToStr() ;

		case SvcKey::alpn :
			return str += "alpn=" + AlpnToStr() ;

		case SvcKey::no_default_alpn :
			return str += "no_default_alpn" ;

		case SvcKey::port :
			return str += "port=" + PortToStr() ;

		case SvcKey::ech :
			return str += "ech=" + EchToStr() ;

		case SvcKey::ipv4hint :
			return str += "ipv4hint=" + Ipv4HintToStr() ;

		case SvcKey::ipv6hint :
			return str += "ipv6hint=" + Ipv6HintToStr() ;

		default :
			return str ;
	}
}


std::string daniel::dns::RR::SVC::SvcParam::MandatoryToStr() const
{
	std::string str = "" ;

	if( false == IsValidValue() || SvcKey::mandatory != key )
	{
		return str ;
	}

	for( uint16_t pos = 0 ; pos < len ; pos +=2 )
	{
		uint16_t type 
			= ( ( value[ pos + 0 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos + 1 ] << 0 ) & 0x00FF ) ;

		if( 0 != pos )
		{
			str += " " ;
		}

		str += ToString( enumFromUint16< dns::QType >( type ) ) ;
	}

	return str ;
}


std::string daniel::dns::RR::SVC::SvcParam::AlpnToStr() const
{
	if( false == IsValidValue() || SvcKey::alpn != key )
	{
		return "" ;
	}

	uint16_t pos = 0 ;
	bool isBegin = true ;

	std::string str = "" ;
	while( pos < len )
	{
		if( ( pos + 1 ) > len )
		{
			return "" ;
		}

		uint8_t alpnlen = value[ pos++ ] ;

		if( ( pos + alpnlen ) > len )
		{
			return "" ;
		}

		if( false == isBegin )
		{
			str += "," ;
		}

		for( uint8_t dcnt = 0 ; dcnt < alpnlen ; ++dcnt )
		{
			str += value[ pos++ ] ;
		}

		isBegin = false ;
	}

	return str ;
}


std::string daniel::dns::RR::SVC::SvcParam::PortToStr() const
{
	if( false == IsValidValue() || SvcKey::port != key )
	{
		return "" ;
	}

	uint16_t port 
		= ( ( value[ 0 ] << 8 ) & 0xFF00 )
		| ( ( value[ 1 ] << 0 ) & 0x00FF ) ;

	return std::to_string( port ) ;
}


std::string daniel::dns::RR::SVC::SvcParam::EchToStr() const
{
	if( false == IsValidValue() || SvcKey::ech != key || 0 == len )
	{
		return "" ;
	}

	char     enc[ 65535 ] ;
	uint16_t wBytes = 0 ;

	baseEncoding::Base64 base64 ;
	if( false == base64.Encode( enc , 65535 , value , len , true , & wBytes ) )
	{
		return "" ;
	}

	if( 1 > wBytes )
	{
		return "" ;
	}

	if( 65535 > wBytes )
	{
		enc[ wBytes ] = '\0' ;
	}
	else
	{
		enc[ 65535 - 1 ] = '\0' ;
	}

	return std::string( enc ) ;
}


std::string daniel::dns::RR::SVC::SvcParam::Ipv4HintToStr() const
{
	if( false == IsValidValue() || SvcKey::ipv4hint != key )
	{
		return "" ;
	}

	std::stringstream ss  ;
	std::string       str ;

	for( uint16_t pos = 0 ; pos < len ; pos += 4 )
	{
		ss << static_cast< uint16_t >( value[ pos + 0 ] ) << "."
		   << static_cast< uint16_t >( value[ pos + 1 ] ) << "."
		   << static_cast< uint16_t >( value[ pos + 2 ] ) << "."
		   << static_cast< uint16_t >( value[ pos + 3 ] ) ;

		if( 0 != pos )
		{
			str += ',' ;
		}

		str += ss.str() ;
		ss.str( "" ) ;
		ss.clear() ;
	}

	return str ;
}


std::string daniel::dns::RR::SVC::SvcParam::Ipv6HintToStr() const
{
	if( false == IsValidValue() || SvcKey::ipv6hint != key )
	{
		return "" ;
	}

	std::string str ;

	uint16_t addr[ 8 ] ;
	uint8_t  addrStr[ 40 ] = { 0 , } ;
	for( uint16_t pos = 0 ; pos < len ; pos += 16 )
	{
		addr[ 0 ]
			= ( ( value[ pos +  0 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos +  1 ] << 0 ) & 0x00FF ) ;

		addr[ 1 ]
			= ( ( value[ pos +  2 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos +  3 ] << 0 ) & 0x00FF ) ;

		addr[ 2 ]
			= ( ( value[ pos +  4 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos +  5 ] << 0 ) & 0x00FF ) ;

		addr[ 3 ]
			= ( ( value[ pos +  6 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos +  7 ] << 0 ) & 0x00FF ) ;

		addr[ 4 ]
			= ( ( value[ pos +  8 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos +  9 ] << 0 ) & 0x00FF ) ;

		addr[ 5 ]
			= ( ( value[ pos + 10 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos + 11 ] << 0 ) & 0x00FF ) ;

		addr[ 6 ]
			= ( ( value[ pos + 12 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos + 13 ] << 0 ) & 0x00FF ) ;

		addr[ 7 ]
			= ( ( value[ pos + 14 ] << 8 ) & 0xFF00 )
			| ( ( value[ pos + 15 ] << 0 ) & 0x00FF ) ;

		if( false == GetCompressedIPv6( addrStr , 40 , addr ) )
		{
			return "" ;
		}

		if( 0 != pos )
		{
			str += ',' ;
		}

		str += std::string( reinterpret_cast< char const * >( addrStr ) ) ;
	}

	return str ;
}