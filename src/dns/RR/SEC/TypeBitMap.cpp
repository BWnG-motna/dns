#include "dns/RR/SEC/TypeBitMap.h"


daniel::dns::RR::SEC::TypeBitMap::TypeBitMap()
	: winNo( 0 ) , len( 0 ) , isSet( false ) , typeCount( 0 )
{
	for( uint8_t pos = 0 ; pos < 32 ; ++pos )
	{
		bitmap[ pos ] = 0 ;
	}
}


void daniel::dns::RR::SEC::TypeBitMap::SetBit( uint16_t const & qtype , bool const & _isSet ) 
{
	if( false == isSet && true == _isSet )
	{
		isSet = true ;
		winNo = static_cast< uint8_t >( qtype / 256 ) ;
	}

	uint8_t no = static_cast< uint8_t >( qtype / 256 ) ;
	if( no != winNo )
	{
		return ;
	}

	uint8_t widPos = static_cast< uint8_t >( qtype  % 256 ) ;
	uint8_t arrInx = static_cast< uint8_t >( widPos /   8 ) ;
	uint8_t bitPos = static_cast< uint8_t >( widPos %   8 ) ;

	if( 32 <= arrInx )
	{
		return ;
	}

	if( true == _isSet )
	{
		bitmap[ arrInx ] |=  ( 0x01U << bitPos ) ;
		len = ( len < arrInx + 1 ) ? ( arrInx + 1 ) : len ;
	}
	else
	{
		bitmap[ arrInx ] &= ~( 0x01U << bitPos ) ;
		while( 0 < len && 0 == bitmap[ len - 1 ] )
		{
			--len ;
		}
	}

	bool isAny = false ;
	for( uint8_t pos = 0 ; pos < len ; ++pos )
	{
		if( 0 != bitmap[ pos ] )
		{
			isAny = true ;
			break ;
		}
	}

	if( false == isAny )
	{
		len   = 0 ;
		isSet = false ;
		typeCount = 0 ;
		return ;
	}

	typeCount = 0 ;
	for( uint8_t arrPos = 0 ; arrPos < len ; ++arrPos )
	{
		for( uint8_t pos = 0 ; pos < 8 ; ++pos )
		{
			if( 0 < ( bitmap[ arrPos ] & ( 0x01U << pos ) ) )
			{
				types[ typeCount++ ] = ( winNo * 256 )+ ( arrPos * 8 ) + pos ;
			}
		}
	}
}


bool daniel::dns::RR::SEC::TypeBitMap::IsSet() const
{
	return isSet ;
}


uint8_t daniel::dns::RR::SEC::TypeBitMap::GetNo() const
{
	return winNo ;
}


uint8_t daniel::dns::RR::SEC::TypeBitMap::GetLen() const
{
	return len ;
}


bool daniel::dns::RR::SEC::TypeBitMap::GetBit( uint16_t const & qtype ) const
{
	uint8_t no = static_cast< uint8_t >( qtype / 256 ) ;

	if( no != winNo )
	{
		return false ;
	}

	uint8_t widPos = static_cast< uint8_t >( qtype  % 256 ) ;
	uint8_t arrInx = static_cast< uint8_t >( widPos /   8 ) ;
	uint8_t bitPos = static_cast< uint8_t >( widPos %   8 ) ;

	if( len <= arrInx )
	{
		return false ;
	}

	return 0 < ( bitmap[ arrInx ] & ( 0x01U << bitPos ) ) ? true : false ;
}


uint8_t daniel::dns::RR::SEC::TypeBitMap::GetSetCount() const
{
	return typeCount ;
}


uint16_t const * daniel::dns::RR::SEC::TypeBitMap::GetTypes() const
{
	return types ;
}