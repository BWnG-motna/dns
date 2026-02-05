#include "Common.h"

#include <sstream>
#include <iomanip>


bool daniel::GetCompressedIPv6( uint8_t * pBuf , uint16_t const & length , uint16_t const ( & addr )[ 8 ] )
{
    uint16_t ipv6[ 8 ][ 3 ] ;
    for( uint8_t pos = 0 ; pos < 8 ; ++pos )
    {
        ipv6[ pos ][ 0 ] = addr[ pos ] ;
        ipv6[ pos ][ 1 ] = 0 ;
        ipv6[ pos ][ 2 ] = 0 ;
    }

    ipv6[ 7 ][ 1 ] = ( 0 == ipv6[ 7 ][ 0 ] ) ? 1 : 0 ;

    for( int8_t pos = 6 ; pos >= 0 ; --pos )
    {
        ipv6[ pos ][ 1 ] = ( 0 == ipv6[ pos ][ 0 ] ) ? ( ipv6[ pos + 1 ][ 1 ] + 1 ) : 0 ;
    }

    uint16_t max    = 0 ;
    uint16_t maxPos = 0 ;
    for( uint8_t pos = 0 ; pos < 8 ; ++pos )
    {
        if( max < ipv6[ pos ][ 1 ] )
        {
            max    = ipv6[ pos ][ 1 ] ;
            maxPos = pos ;
        }
    }

    if( 1 < ipv6[ maxPos ][ 1 ] )
    {

#if 0
        ipv6[ maxPos ][ 2 ] = 1 ;
        
        for( uint8_t pos = maxPos + 1 ; pos < 8 ; ++pos )
        {
            if( 0 == ipv6[ pos ][ 1 ] )
            {
                break ;
            }

            ipv6[ pos ][ 2 ] = 1 ;
        }
#else
        for( uint16_t pos = maxPos ; pos < 8 && 0 < ipv6[ pos ][ 1 ] ; ++pos )
        {
            ipv6[ pos ][ 2 ] = 1 ;
        }
#endif

    }

    std::stringstream ss ;

    bool skipped = false ;
    bool emitted = false ;

    for( uint8_t pos = 0 ; pos < 8 ; ++pos )
    {
        if( 1 == ipv6[ pos ][ 2 ] )
        {
            if( false == skipped )
            {
                ss << "::" ;

                skipped = true  ;
                emitted = false ;
            }

            continue ;
        }

        if( emitted )
        {
            ss << ":" ;
        }

        ss << std::hex << std::setfill( ' ' ) << std::setw( 0 ) << ipv6[ pos ][ 0 ]  ; 
        emitted = true ;
    }
    ss << std::dec << std::setfill( ' ' ) << std::setw( 0 ) ;

    std::string dStr = ss.str() ;
    char const * p = dStr.c_str() ;
    uint16_t len = static_cast< uint16_t >( dStr.length() ) ;

    for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
    {
        pBuf[ pos ] = p[ pos ] ;
    }

    uint16_t lessPos = ( len < length ) ? len : length ;
    pBuf[ lessPos ] = '\0' ;

    return true ;
}