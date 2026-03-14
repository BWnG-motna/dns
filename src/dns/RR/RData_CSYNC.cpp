#include "dns/RR/RData_CSYNC.h"
#include "dns/QType.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_CSYNC::RData_CSYNC()
	: RData( nullptr ) , serial( 0 ) , flags( 0 ) , isImmediate( false ) , pTbm( nullptr ) , pTypes( nullptr )
{

}


daniel::dns::RR::RData_CSYNC::~RData_CSYNC()
{
	Initialize() ;
}


void daniel::dns::RR::RData_CSYNC::Initialize()
{
	if( nullptr != pTbm )
	{
		delete pTbm ;
		pTbm = nullptr ;
	}

	if( nullptr != pTypes )
	{
		delete [] pTypes ;
		pTypes = nullptr ;
	}

	serial = 0 ;
	flags  = 0 ;

	isImmediate = false ;
}


uint16_t daniel::dns::RR::RData_CSYNC::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << serial << " " ;
	ss << flags ;
	
	/* types */
	uint16_t typeCount = GetTypeCount() ;
	uint16_t const * types = GetTypes() ;

	for( uint16_t pos = 0 ; pos < typeCount ; ++pos )
	{
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


bool daniel::dns::RR::RData_CSYNC::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 7 > length )
	{
		return false ;
	}

	Initialize() ;

	serial = ( ( pData[ 0 ] << 24 ) & 0xFF000000 )
	       | ( ( pData[ 1 ] << 16 ) & 0x00FF0000 )
	       | ( ( pData[ 2 ] <<  8 ) & 0x0000FF00 )
	       | ( ( pData[ 3 ] <<  0 ) & 0x000000FF ) ;

	flags  = ( ( pData[ 4 ] <<  8 ) & 0xFF00 )
	       | ( ( pData[ 5 ] <<  0 ) & 0x00FF ) ; 

	uint16_t pos = 6 ;
	while( ( pos + 2 ) <= length  )
	{
		uint8_t window   = pData[ pos++ ] ;
		uint8_t blockLen = pData[ pos++ ] ;

		if( 32 < blockLen || ( pos + blockLen ) > length )
		{
			Initialize() ;
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
						Initialize() ;
						return is ;
					}
				}
			} 
		}

		pos += blockLen ;

	}

	return true ;
}


bool daniel::dns::RR::RData_CSYNC::SetType( uint8_t const & window , uint8_t const & type )
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

	if( false == pTbm->Insert( p ) )
	{
		delete p ;
		return false ;
	}

	return true ;
}


uint32_t daniel::dns::RR::RData_CSYNC::GetSerial() const 
{
	return serial ;
}


uint16_t daniel::dns::RR::RData_CSYNC::GetFlags() const 
{
	return flags ;
}


uint16_t daniel::dns::RR::RData_CSYNC::GetTypeCount() const
{
	if( nullptr == pTbm )
	{
		return 0 ;
	}

	ds::LinkedList< SEC::TypeBitMap >::const_iterator posIter = pTbm->begin() ;
	ds::LinkedList< SEC::TypeBitMap >::const_iterator endIter = pTbm->end() ;


	uint16_t typeCount = 0 ;

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


uint16_t const * daniel::dns::RR::RData_CSYNC::GetTypes() const 
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