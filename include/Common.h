#pragma once

#include <cstdint>
#include <type_traits>


namespace daniel
{

	

template< typename E >
constexpr auto underlying( E e ) -> typename std::underlying_type< E >::type 
{
   return static_cast< typename std::underlying_type< E >::type >( e ) ;
}


template < typename Enum >
constexpr Enum enumFromUint16( std::uint16_t value ) noexcept
{
    static_assert( std::is_enum_v< Enum > , "Enum must be an enum type" ) ;
    static_assert( std::is_same_v< std::underlying_type_t< Enum > , std::uint16_t > , "Underlying type of Enum must be uint16_t" ) ;

    return static_cast< Enum >( value ) ;
}



} // namespace daniel