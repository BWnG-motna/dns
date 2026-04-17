#include "dns/RR/HHIT/COBLHeader.h"


daniel::dns::RR::HHIT::COBLHeader::COBLHeader()
	: majorType( 0 ) , bytes( 0 ) , extraBytes( 0 ) , data( 0 ) , isError( false )
{

}

bool daniel::dns::RR::HHIT::COBLHeader::Load( uint8_t const * p , uint16_t const & len )
{
	if( nullptr == p || 1 > len ) 
	{
		return false ;
	}

	isError   = false ;
	majorType = ( p[ 0 ] >> 5 ) & 0x07 ;
	bytes     = ( p[ 0 ] >> 0 ) & 0x1f ;

	if( bytes < 24 )
	{
		extraBytes = 0 ;
		data       = bytes ;
	}
	else if( bytes == 24 && 2 >  len )
	{
		extraBytes = 1 ; 
		data       = 0 ;
		isError    = true ;
	}
	else if( bytes == 24 && 2 <= len )
	{
		extraBytes = 1 ;
		data       = p[ 1 ] ;
	}
	else if( bytes == 25 && 3 >  len )
	{
		extraBytes = 2 ;
		data       = 0 ;
		isError    = true ;
	}
	else if( bytes == 25 && 3 <= len )
	{
		extraBytes = 2 ;
		data       = ( ( p[ 1 ] << 8 ) & 0xFF00 )
		           | ( ( p[ 2 ] << 0 ) & 0x00FF ) ;
	}
	else if( bytes == 26 && 5 >  len )
	{
		extraBytes = 4 ;
		data       = 0 ;
		isError    = true ;
	}
	else if( bytes == 26 && 5 <= len )
	{
		extraBytes = 4 ;
		data       = ( ( p[ 1 ] << 24 ) & 0xFF000000 )
		           | ( ( p[ 2 ] << 16 ) & 0x00FF0000 )
		           | ( ( p[ 3 ] <<  8 ) & 0x0000FF00 )
		           | ( ( p[ 4 ] <<  0 ) & 0x000000FF ) ;
	}
	else if( bytes < 30 ) 
	{
		extraBytes = 0 ;
		isError    = true ;
	}
	else
	{
		extraBytes = 0 ; ; // it means infinite ( break 0xFF )
		isError    = true ;
	}

	return true ;
}


uint8_t daniel::dns::RR::HHIT::COBLHeader::GetMajorType() const
{
	return majorType ;
}


uint8_t daniel::dns::RR::HHIT::COBLHeader::GetBytes() const
{
	return bytes ;
}


uint8_t daniel::dns::RR::HHIT::COBLHeader::GetExtraBytes() const
{
	return extraBytes ;
}


uint32_t daniel::dns::RR::HHIT::COBLHeader::GetData() const
{
	return data ;
}


bool daniel::dns::RR::HHIT::COBLHeader::IsError() const
{
	return isError ;
}