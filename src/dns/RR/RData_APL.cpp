#include "dns/RR/RData_APL.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_APL::RData_APL()
	: RData( nullptr ) , pItem( nullptr )
{

}


daniel::dns::RR::RData_APL::~RData_APL()
{
	Initialize() ;
}


void daniel::dns::RR::RData_APL::Initialize()
{
	if( nullptr != pItem )
	{
		delete pItem ;
		pItem = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_APL::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	pStr[ 0 ] = '\0' ;


	if( nullptr == pItem )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ds::LinkedList< APL::APItem >::const_iterator posIter = pItem->begin() ;
	ds::LinkedList< APL::APItem >::const_iterator endIter = pItem->end()   ;

	while( posIter != endIter )
	{
		using AF = APL::AddressFamily ;

		APL::APItem const & apItem = * posIter ;

		AF      const af           = apItem.GetAddressFamily() ;
		bool    const isInvalid    = apItem.IsInvalid()  ;
		bool    const isNegation   = apItem.IsNegation() ;
		uint8_t const * pAddr      = apItem.GetAddress() ;
		uint8_t const prefix       = apItem.GetPrefix()  ;

		if( true == isInvalid )
		{
			++posIter ;
			continue ;
		}

		if( pItem->cbegin() != posIter )
		{
			ss << " " ;
		}

		ss << ( isNegation ? "!" : "" ) ;
		ss << ( static_cast< uint16_t >( af ) ) << ":" ;

		/**/ if( APL::AddressFamily::IPv4 == af )
		{
			for( uint8_t pos = 0 ; pos < 4 ; ++pos )
			{
				if( 0 != pos )
				{
					ss << "." ;
				}

				ss << static_cast< uint16_t >( pAddr[ pos ] ) ;
			}
		}
		else if( APL::AddressFamily::IPv6 == af )
		{
			uint8_t  addrPos = 0 ;
			uint16_t addr[ 8 ] ;
			uint8_t  addrStr[ 60 ] ;

			for( uint8_t pos = 0 ; pos < 16 ; pos += 2 )
			{
				addr[ addrPos++ ] 
					= ( ( pAddr[ pos + 0 ] << 8 ) & 0xFF00 ) 
					| ( ( pAddr[ pos + 1 ] << 0 ) & 0x00FF ) ;
			}

			GetCompressedIPv6( addrStr , 60 , addr ) ;

			ss << reinterpret_cast< char const * >( addrStr ) ;
		}

		ss << "/" << static_cast< uint16_t >( prefix ) ;

		++posIter ;
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


bool daniel::dns::RR::RData_APL::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	Initialize() ;
	
	uint16_t pos = 0 ;

	while( ( pos + 4 ) < length )
	{
		APL::APItem * p = new ( std::nothrow ) APL::APItem() ;
		if( nullptr == p )
		{
			Initialize() ;
			return false ;
		}

		uint16_t addrFamily 
			= ( ( pData[ pos + 0 ] << 8 ) & 0xFF00 )
			| ( ( pData[ pos + 1 ] << 0 ) & 0x00FF ) ;

		uint8_t  prefix = pData[ pos + 2 ] ;
		uint8_t     len = pData[ pos + 3 ] ; 

		if( ( pos + 4 + len ) >= length )
		{
			delete p ;

			Initialize() ;
			return false ;
		}

		p->SetAddressFamily( addrFamily ) ;
		p->SetPrefix( prefix ) ;
		p->SetAddress( & ( pData[ pos + 4 ] ) , len ) ;

		if( nullptr == pItem )
		{
			pItem = new ( std::nothrow ) ds::LinkedList< APL::APItem >() ;
			if( nullptr == pItem )
			{
				delete p ;

				Initialize() ;
				return false ;
			}
		}

		if( false == pItem->Insert( p ) )
		{
			delete p ;
			
			Initialize() ;
			return false ;
		}

		pos = pos + 4 + len ;
	}

	return true ;
}