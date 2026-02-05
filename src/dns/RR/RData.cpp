#include "dns/RR/RData.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData::RData( uint8_t const * pRef )
	: pDataGram( pRef ) 
{

}


uint16_t daniel::dns::RR::RData::GetDNData( 
	uint8_t        * pBuf   , 
	uint16_t const & length , 
	uint8_t  const * pRef   ,
	bool     const & fqdn   ) const
{
	if( 1 > length || nullptr == pBuf || nullptr == pRef )
	{
		return 0 ;
	}

	uint8_t const * p  = pRef ;
	uint16_t len  = 0 ;
	uint16_t bPos = 0 ;

	while( '\0' != *p )
	{
		if( 0xC0 <= ( *p & 0xC0 ) )
		{
			uint16_t offset
				= ( ( ( 0x3F & *( p + 0 ) ) << 8 ) & 0xFF00 ) 
				| ( ( ( 0xFF & *( p + 1 ) ) << 0 ) & 0x00FF ) ;

			p = pDataGram + offset ;

			continue ;
		}

		len = ( *p++ ) ;

		if( 1 == len && 0x00 == *p )
		{
			++p ;
		}
		else
		{
			for( uint8_t pos = 0 ; pos < len ; ++pos ) 
			{
				if( length <= bPos )
				{
					return bPos ;
				}

				pBuf[ bPos++ ] = *p++ ;
			}
		}

		if( ( true == fqdn || '\0' != *p ) && ( length <= bPos ) )
		{
			return bPos ;
		}

		if( true == fqdn )
		{
			pBuf[ bPos++ ] = '.' ;
		}
		else if( '\0' != *p )
		{
			pBuf[ bPos++ ] = '.' ;
		}
	}

	pBuf[ bPos ] = '\0' ;
	
	return bPos ;
}


uint16_t daniel::dns::RR::RData::SkipDName( uint8_t const * pBuf , uint16_t const & length ) const
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}

	uint16_t bPos = 0 ;

	while( '\0' != pBuf[ bPos ] && bPos < length )
	{
		if( 0xC0 <= ( pBuf[ bPos ] & 0xC0 ) )
		{
			if( length <= bPos + 1 )
			{
				return 0 ;
			}
			else
			{
				return bPos + 2 ;
			}
		}

		uint8_t len = pBuf[ bPos ] ;
		bPos += 1 + len ;
		if( length < bPos )
		{
			return 0 ;
		} 
	}

	if( '\0' == pBuf[ bPos ] && bPos < length )
	{
		++bPos ;
	}

	return bPos ;
}


uint16_t daniel::dns::RR::RData::GetDNDataLen( uint8_t const * pRef , bool const & fqdn ) const
{
	if( nullptr == pRef )
	{
		return 0 ;
	}

	uint8_t const * p  = pRef ;
	uint16_t len  = 0 ;
	uint16_t bPos = 0 ;

	while( '\0' != *p )
	{
		if( 0xC0 <= ( *p & 0xC0 ) )
		{
			uint16_t offset
				= ( ( ( 0x3F & *( p + 0 ) ) << 8 ) & 0xFF00 ) 
				| ( ( ( 0xFF & *( p + 1 ) ) << 0 ) & 0x00FF ) ;

			p = pDataGram + offset ;

			continue ;
		}

		len = ( *p++ ) ;

		if( 1 == len && 0x00 == *p )
		{
			++p ;
		}
		else
		{
			for( uint8_t pos = 0 ; pos < len ; ++pos ) 
			{
				++bPos ;
				++p ;
			}
		}

		if( true == fqdn )
		{
			++bPos ;
		}
		else if( '\0' != *p )
		{
			++bPos ;
		}
	}
	
	return bPos ;
}