#include "dns/RR/APL/APItem.h"


daniel::dns::RR::APL::APItem::APItem()
	: addrFamily( AddressFamily::Invalid ) , prefix( 0 ) , afdLen( 0 )
{
	for( uint8_t pos = 0 ; pos < 16 ; ++pos )
	{
		address[ pos ] = 0 ;
	}
}


daniel::dns::RR::APL::APItem::~APItem()
{

}


void daniel::dns::RR::APL::APItem::SetAddressFamily( AddressFamily const & f )
{
	addrFamily = f ;
}


void daniel::dns::RR::APL::APItem::SetAddressFamily( uint16_t const & f )
{
	if( true == IsValidAddressFamily( f ) )
	{
		addrFamily = enumFromUint16< AddressFamily >( f ) ;
	}
	else
	{
		addrFamily = AddressFamily::Invalid ;
	}
}


void daniel::dns::RR::APL::APItem::SetPrefix( uint8_t const & n )
{
	prefix = n ;
}


void daniel::dns::RR::APL::APItem::SetAddress( uint8_t const * pAddr , uint8_t const & len )
{
	if( AddressFamily::Invalid == addrFamily )
	{
		return ;
	}
	else if( AddressFamily::IPv4 == addrFamily &&  4 < len )
	{
		return ;
	}
	else if( AddressFamily::IPv6 == addrFamily && 16 < len )
	{
		return ;
	}


	afdLen = len ;

	uint8_t pos = 0 ;
	for( pos = 0 ; pos < len ; ++pos )
	{
		address[ pos ] = pAddr[ pos ] ;
	}

	for(  ; pos < 16 ; ++pos )
	{
		address[ pos ] = 0 ;
	}
}


daniel::dns::RR::APL::AddressFamily daniel::dns::RR::APL::APItem::GetAddressFamily() const
{
	return addrFamily ;
}


uint8_t daniel::dns::RR::APL::APItem::GetPrefix() const
{
	return ( prefix & 0x7F ) ;
}


uint8_t daniel::dns::RR::APL::APItem::GetAFDLen() const
{
	return afdLen ;
}


uint8_t const * daniel::dns::RR::APL::APItem::GetAddress() const
{
	return address ;
}


bool daniel::dns::RR::APL::APItem::IsNegation() const
{
	return ( 0 < ( prefix & 0x80 ) ) ? true : false ;
}


bool daniel::dns::RR::APL::APItem::IsInvalid() const
{
	uint8_t val = prefix & 0x7F ;

	/**/ if( AddressFamily::Invalid == addrFamily )
	{
		return true ;
	}
	else if( AddressFamily::IPv4 == addrFamily &&  32 < val )
	{
		return true ;
	}
	else if( AddressFamily::IPv6 == addrFamily && 128 < val )
	{
		return true ;
	}
	else if( AddressFamily::IPv4 == addrFamily &&   4 < afdLen )
	{
		return true ;
	}
	else if( AddressFamily::IPv6 == addrFamily &&  16 < afdLen )
	{
		return true ;
	}

	return false ;
}