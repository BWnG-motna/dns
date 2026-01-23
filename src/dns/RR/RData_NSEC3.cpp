#include "dns/RR/RData_NSEC3.h"
#include "dns/QType.h"
#include "baseEncoding/Base32Hex.h"

#include <sstream>
#include <iomanip>
#include <iostream>


daniel::dns::RR::RData_NSEC3::RData_NSEC3()
	: RData( nullptr ) , hashAlgo( SECHashAlgo::INVALID ) , flags( 0 ) , iterations( 0 ) , saltLength( 0 ) , ownerNameLen( 0 )
{
	for( uint8_t pos = 0 ; pos < 255 ; ++pos )
	{
		salt[ pos ] = 0 ;
	}

	for( uint8_t pos = 0 ; pos < 50 ; ++pos )
	{
		ownerName[ pos ] = 0 ;
	}
}


uint16_t daniel::dns::RR::RData_NSEC3::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	std::stringstream ss ;

	ss << static_cast< uint16_t >( hashAlgo ) << '\t'
	   << static_cast< uint16_t >( IsOptOut() ? 1 : 0 ) << '\t'
	   << static_cast< uint16_t >( iterations ) << '\t' ;

	/* salt */
	for( uint8_t pos = 0 ; pos < saltLength ; ++pos )
	{
		ss << std::setw( 2 ) << std::setfill( '0' ) << std::hex << static_cast< uint16_t >( salt[ pos ] ) ;
	}

	ss << ( ( 1 > saltLength ) ? "(salt: none)\t" : "\t" ) ;

	/* next owner name */
	char     base32hex[ 100 ] ;
	uint16_t hexlen = 0 ;
	baseEncoding::Base32Hex conv ;
	conv.Encode( base32hex , 100 , ownerName , ownerNameLen , false , & hexlen ) ;

	ss << hexlen << " - ( " ;
	for( uint8_t pos = 0 ; pos < hexlen ; ++pos )
	{
		ss << base32hex[ pos ] ;
	}

	/* types */
	uint16_t typeCount = GetTypeCount() ;
	uint16_t const * types = GetTypes() ;
	for( uint16_t pos = 0 ; pos < typeCount ; ++pos )
	{
		if( 0 == pos )
		{
			ss << " " ;
		}
		ss << " " << ToString( enumFromUint16< dns::QType >( types[ pos ] ) ) ;
	}

	/* output */
	std::string str = ss.str() ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;
	
	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less  ;
}


bool daniel::dns::RR::RData_NSEC3::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 5 > length )
	{
		return false ;
	}

	if( false == IsValidHashAlgo( pData[ 0 ] ) )
	{
		return false ;
	}
	else
	{
		hashAlgo = daniel::enumFromUint8< SECHashAlgo >( pData[ 0 ] ) ;
	}

	flags = pData[ 1 ] ;

	iterations 
		= ( ( pData[ 2 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	saltLength = pData[ 4 ] ;

	if( 5 + saltLength > length ) 
	{
		return false ;
	}

	uint8_t saltPos = 0 ;
	for( uint8_t pos = 0 ; pos < saltLength ; ++pos )
	{
		salt[ saltPos++ ] = pData[ 5 + pos ] ;
	}

	uint16_t hashLen = daniel::dns::RR::GetHashAlgoLen( hashAlgo ) ;

#if 0
	ownerNameLen = static_cast< uint8_t >( ( ( hashLen * 8 ) + 4 ) / 5 ) ;
#else
	ownerNameLen = pData[ 5 + saltLength ] ;
#endif

	if( hashLen != ownerNameLen )
	{
		return false ;
	}

	if( ownerNameLen > sizeof( ownerName ) )
	{
		return false ;
	}

	if( ( 6 + saltLength + ownerNameLen ) > length )
	{
		return false ;
	}

	for( uint8_t pos = 0 ; pos < ownerNameLen ; ++pos )
	{
		ownerName[ pos ] = pData[ pos + 6 + saltLength ] ;
	}

	uint16_t pos = 6 + saltLength + ownerNameLen ;

	while( ( pos + 2 ) <= length  )
	{
		uint8_t window   = pData[ pos++ ] ;
		uint8_t blockLen = pData[ pos++ ] ;

		if( 32 < blockLen || ( pos + blockLen ) > length )
		{
			return false ;
		}

		for( uint8_t arrPos = 0 ; arrPos < blockLen ; ++arrPos )
		{
			for( uint8_t bitPos = 0 ; bitPos < 8 ; ++bitPos )
			{
				if( 0 < ( pData[ pos + arrPos ] & ( 0x01U << bitPos ) ) )
				{
					uint16_t type = ( window * 256 ) + ( arrPos * 8 ) + bitPos ;
					tbm[ window ].SetBit( type ) ;
				}
			} 
		}

		pos += blockLen ;

	}

	return true ;
}


daniel::dns::RR::SECHashAlgo daniel::dns::RR::RData_NSEC3::GetHashAlgo() const 
{
	return hashAlgo ;
}


uint8_t daniel::dns::RR::RData_NSEC3::GetFlags() const
{
	return flags ;
}


uint16_t daniel::dns::RR::RData_NSEC3::GetIterations() const 
{
	return iterations ;
}


uint8_t daniel::dns::RR::RData_NSEC3::GetSaltLength() const 
{
	return saltLength ;
}


uint8_t daniel::dns::RR::RData_NSEC3::GetOwnerNameLength() const 
{
	return ownerNameLen ;
}


uint16_t daniel::dns::RR::RData_NSEC3::GetTypeCount() const
{
	uint16_t typeCount = 0 ;

	for( uint16_t pos = 0 ; pos < 256 ; ++pos )
	{
		if( true == tbm[ pos ].IsSet() )
		{
			typeCount += tbm[ pos ].GetSetCount() ;
		}
	}

	return typeCount ;
}


bool daniel::dns::RR::RData_NSEC3::IsOptOut() const
{
	return ( 0 < ( flags & 0x80 ) ) ? true : false ; 
}


uint8_t const * daniel::dns::RR::RData_NSEC3::GetSalt() const
{
	return salt ;
}


uint8_t const * daniel::dns::RR::RData_NSEC3::GetOwnerName() const 
{
	return ownerName ;
}


uint16_t const * daniel::dns::RR::RData_NSEC3::GetTypes() const 
{
	uint16_t typesPos = 0 ;
	for( uint16_t pos = 0 ; pos < 256 ; ++pos )
	{
		if( true == tbm[ pos ].IsSet() )
		{
			uint8_t  count = tbm[ pos ].GetSetCount() ;
			uint16_t const * tArr = tbm[ pos ].GetTypes() ;

			for( uint16_t tPos = 0 ; tPos < count ; ++tPos )
			{
				if( 512 > typesPos )
				{
					types[ typesPos++ ] = tArr[ tPos ] ; 
				}
			}
		}
	}

	return types ;
}