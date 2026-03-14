#include "view/HexView.h"

#include <iostream>
#include <iomanip>
#include <cctype>
#include <array>


void daniel::view::HexView::View( uint8_t const * pBuf , uint32_t const & length , uint8_t const & blockCount )
{
	if( 1 > length || nullptr == pBuf )
	{
		return ;
	}


	uint8_t const   bCnt   = ( 1 > blockCount || 4 < blockCount ) ? 2 : blockCount ;

	std::cout << std::endl << prefix << length << " byte(s)" << std::endl ;
	std::cout << std::endl << prefix ;

	std::array< uint8_t , 32 > valArray {} ;
	uint8_t valPos = 0 ;

	for( uint32_t pos = 0 ; pos < length ; ++pos )
	{
		bool isNewBlock = ( 0 != pos ) && ( 0 == ( pos % (        8 ) ) ) ;
		bool isNewLine  = ( 0 != pos ) && ( 0 == ( pos % ( bCnt * 8 ) ) ) ;

		/**/ if( !isNewLine && isNewBlock )
		{
			std::cout << divbar ;
		}
		else if(  isNewLine ) 
		{
			ViewValues( valArray , valPos ) ;
			valPos = 0 ;
			
			std::cout << std::endl << prefix ;
		}

		std::cout << std::hex 
		          << std::nouppercase 
		          << std::setw( 2 ) 
		          << std::setfill( '0' ) 
		          << static_cast< int >( pBuf[ pos ] ) 
		          << " " ;

		valArray[ valPos++ ] = std::isprint( pBuf[ pos ] ) ? pBuf[ pos ] : '.' ;
	}
	
	AddPadding( length , blockCount ) ;
	ViewValues( valArray , valPos ) ;
	
	std::cout << std::endl << std::endl ;
}


void daniel::view::HexView::AddPadding( uint32_t const & length , uint8_t const & blockCount )
{
	std::cout << std::dec << std::nouppercase << std::setw( 0 ) << std::setfill( ' ' ) ;

	uint32_t const extra   = ( length % ( blockCount * 8 ) ) ;
	uint32_t const extraSp = ( blockCount * 8 ) - extra ;

	if( 0 < extra )
	{
		for( uint32_t pos = 0 ; pos < extraSp ; ++pos )
		{
			uint32_t   rPos = extra + pos ;
			bool isNewBlock = ( 0 != rPos ) && ( 0 == ( rPos % 8 ) ) ;
			
			if( isNewBlock )
			{
				std::cout << divbar ; 
			}

			std::cout << "__ " ;
		}
	}
}


void daniel::view::HexView::ViewValues( std::array< uint8_t , 32 > const & valArray , uint8_t const size )
{
	std::cout << divbar ;
	for( uint8_t pos = 0 ; pos < size ; ++pos )
	{
		std::cout << std::dec << std::nouppercase << std::setw( 0 ) << std::setfill( ' ' ) ;
		std::cout << static_cast< uint8_t >( valArray[ pos ] ) ;
	}
}