#include "dns/RR/RData_NSEC3.h"
#include "dns/QType.h"
#include "baseEncoding/Base32Hex.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_NSEC3::RData_NSEC3()
	: RData( nullptr )  , hashAlgo( SEC::SECHashAlgo::INVALID )   , 
	  flags( 0 )        , iterations( 0 )       , saltLength( 0 ) , 
	  pSalt( nullptr )  , pOwnerName( nullptr ) , pTbm( nullptr ) ,
	  ownerNameLen( 0 ) , pTypes( nullptr ) 
{

}


daniel::dns::RR::RData_NSEC3::~RData_NSEC3()
{
	Initalize() ;
}


void daniel::dns::RR::RData_NSEC3::Initalize()
{
	if( nullptr != pSalt )
	{
		delete [] pSalt ;
		pSalt = nullptr ;
	}

	if( nullptr != pOwnerName )
	{
		delete [] pOwnerName ;
		pOwnerName = nullptr ;
	}

	if( nullptr != pTbm )
	{
		delete pTbm ;
		pTbm = nullptr ;
	}

	hashAlgo = SEC::SECHashAlgo::INVALID ;

	flags        = 0 ;
	iterations   = 0 ;
	saltLength   = 0 ;
	ownerNameLen = 0 ;
}


uint16_t daniel::dns::RR::RData_NSEC3::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( 0 < saltLength && nullptr == pSalt )
	{
		return 0 ;
	}

	if( nullptr == pOwnerName || nullptr == pTbm )
	{
		return 0 ;
	}



	std::stringstream ss ;

	ss << static_cast< uint16_t >( hashAlgo ) << '\t'
	   << static_cast< uint16_t >( IsOptOut() ? 1 : 0 ) << '\t'
	   << static_cast< uint16_t >( iterations ) << '\t' ;

	/* salt */
	for( uint8_t pos = 0 ; pos < saltLength ; ++pos )
	{
		ss << std::setw( 2 ) << std::setfill( '0' ) << std::hex << static_cast< uint16_t >( pSalt[ pos ] ) ;
	}

	ss << ( ( 1 > saltLength ) ? "(salt: none)\t" : "\t" ) ;

	/* next owner name */
	char     base32hex[ 100 ] ;
	uint16_t hexlen = 0 ;
	baseEncoding::Base32Hex conv ;
	conv.Encode( base32hex , 100 , pOwnerName , ownerNameLen , false , & hexlen ) ;

	ss << " ( " ;
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

	ss << " )" ;

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

	Initalize() ;

	if( false == SEC::IsValidHashAlgo( pData[ 0 ] ) )
	{
		Initalize() ;
		return false ;
	}
	else
	{
		hashAlgo = daniel::enumFromUint8< SEC::SECHashAlgo >( pData[ 0 ] ) ;
	}

	flags = pData[ 1 ] ;

	iterations 
		= ( ( pData[ 2 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	saltLength = pData[ 4 ] ;

	if( 5 + saltLength > length ) 
	{
		Initalize() ;
		return false ;
	}

	if( 0 < saltLength )
	{
		pSalt = new ( std::nothrow ) uint8_t [ saltLength ] ;
		if( nullptr == pSalt )
		{
			Initalize() ;
			return false ;
		}
	}

	uint8_t saltPos = 0 ;
	for( uint8_t pos = 0 ; pos < saltLength ; ++pos )
	{
		pSalt[ saltPos++ ] = pData[ 5 + pos ] ;
	}

	uint16_t hashLen = daniel::dns::RR::SEC::GetHashAlgoLen( hashAlgo ) ;

#if 0
	ownerNameLen = static_cast< uint8_t >( ( ( hashLen * 8 ) + 4 ) / 5 ) ;
#else
	ownerNameLen = pData[ 5 + saltLength ] ;
#endif

	if( hashLen != ownerNameLen )
	{
		Initalize() ;
		return false ;
	}

	if( ( 6 + saltLength + ownerNameLen ) > length )
	{
		Initalize() ;
		return false ;
	}

	pOwnerName = new ( std::nothrow ) uint8_t [ ownerNameLen ] ;
	if( nullptr == pOwnerName )
	{
		Initalize() ;
		return false ;
	}

	for( uint8_t pos = 0 ; pos < ownerNameLen ; ++pos )
	{
		pOwnerName[ pos ] = pData[ pos + 6 + saltLength ] ;
	}

	uint16_t pos = 6 + saltLength + ownerNameLen ;

	while( ( pos + 2 ) <= length  )
	{
		uint8_t window   = pData[ pos++ ] ;
		uint8_t blockLen = pData[ pos++ ] ;

		if( 32 < blockLen || ( pos + blockLen ) > length )
		{
			Initalize() ;
			return false ;
		}

		for( uint8_t arrPos = 0 ; arrPos < blockLen ; ++arrPos )
		{
			for( uint8_t bitPos = 0 ; bitPos < 8 ; ++bitPos )
			{
				if( 0 < ( pData[ pos + arrPos ] & ( 0x01U << bitPos ) ) )
				{
					uint16_t type = ( window * 256 ) + ( arrPos * 8 ) + bitPos ;
					bool is = SetType( window , type ) ;
					if( false == is )
					{
						Initalize() ;
						return is ;
					}
				}
			} 
		}

		pos += blockLen ;

	}

	return true ;
}




bool daniel::dns::RR::RData_NSEC3::SetType( uint8_t const & window , uint8_t const & type )
{
	if( nullptr == pTbm )
	{
		pTbm = new ( std::nothrow ) ds::LinkedList< SEC::TypeBitMap >() ;
		if( nullptr == pTbm )
		{

			return false ;
		}
	}

	ds::LinkedList< SEC::TypeBitMap >::iterator posIter = pTbm->begin() ;
	ds::LinkedList< SEC::TypeBitMap >::iterator endIter = pTbm->end() ;

	while( posIter != endIter )
	{
		SEC::TypeBitMap const & tbm = *posIter ;
		if( true == tbm.IsSet() && window == tbm.GetNo() )
		{
			break ;
		} 

		++posIter ;
	}

	if( posIter != endIter )
	{
		( *posIter ).SetBit( type ) ;
		return true ;
	}

	SEC::TypeBitMap * p = new ( std::nothrow ) SEC::TypeBitMap() ;
	if( nullptr == p )
	{
		return false ;
	}

	p->SetBit( type ) ;

	pTbm->Insert( p ) ;

	return true ;
}


daniel::dns::RR::SEC::SECHashAlgo daniel::dns::RR::RData_NSEC3::GetHashAlgo() const 
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
	if( nullptr == pTbm )
	{
		return 0 ;
	}

	ds::LinkedList< SEC::TypeBitMap >::const_iterator posIter = pTbm->begin() ;
	ds::LinkedList< SEC::TypeBitMap >::const_iterator endIter = pTbm->end() ;


	uint16_t typeCount = 0;

	while( posIter != endIter )
	{
		SEC::TypeBitMap const & p = *posIter ;

		if( true == p.IsSet() )
		{
			typeCount += p.GetSetCount() ;
		}

		++posIter ;
	}

	return typeCount ;
}


bool daniel::dns::RR::RData_NSEC3::IsOptOut() const
{
	return ( 0 < ( flags & 0x80 ) ) ? true : false ; 
}


uint8_t const * daniel::dns::RR::RData_NSEC3::GetSalt() const
{
	return pSalt ;
}


uint8_t const * daniel::dns::RR::RData_NSEC3::GetOwnerName() const 
{
	return pOwnerName ;
}


uint16_t const * daniel::dns::RR::RData_NSEC3::GetTypes() const 
{
	uint16_t typeCount = GetTypeCount() ;
	if( 1 > typeCount )
	{
		return nullptr ;
	}

	ds::LinkedList< SEC::TypeBitMap >::const_iterator posIter = pTbm->begin() ;
	ds::LinkedList< SEC::TypeBitMap >::const_iterator endIter = pTbm->end() ;

	if( nullptr != pTypes )
	{
		delete [] pTypes ;
		pTypes = nullptr ;
	}

	pTypes = new ( std::nothrow ) uint16_t [ typeCount ] ;
	if( nullptr == pTypes )
	{
		return nullptr ;
	}

	uint16_t typePos = 0 ;
	while( posIter != endIter )
	{
		SEC::TypeBitMap const & tbm = *posIter ;

		if( true != tbm.IsSet() )
		{
			++posIter ;
			continue ; 
		}

		uint8_t  count = tbm.GetSetCount() ;
		uint16_t const * tArr = tbm.GetTypes() ;

		for( uint16_t tPos = 0 ; tPos < count ; ++tPos )
		{
			pTypes[ typePos++ ] = tArr[ tPos ] ;
		}

		++posIter ;
	}

	return pTypes ;
}