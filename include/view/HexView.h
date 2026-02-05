#pragma once

#include "Common.h"
#include <array>


namespace daniel
{
	
namespace view
{
	

class HexView
{

private :
	static constexpr char const * prefix = "  " ;
	static constexpr char const * divbar = "  " ;

private :
	static void AddPadding( uint32_t const & length , uint8_t const & blockCount ) ;
	static void ViewValues( std::array< uint8_t , 32 > const & array , uint8_t const size ) ;

public :
	static void View( uint8_t const * pbuf , uint32_t const & length , uint8_t const & blockCnt = 1 ) ;

} ; // class HexView


}   // namespace view

}   // namespace daniel