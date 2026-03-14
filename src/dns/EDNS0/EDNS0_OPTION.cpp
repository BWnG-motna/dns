#include "dns/EDNS0/EDNS0_OPTION.h"


#include <memory>


daniel::dns::EDNS0_OPTION::EDNS0_OPTION()
	: code( EDNS0_OptCode::RESERVED ) , len( 0 ) , pDat( nullptr )
{
	
}


daniel::dns::EDNS0_OPTION::EDNS0_OPTION( EDNS0_OptCode const & _code , uint16_t const & _len , uint8_t const * _pDat )
	: code( _code ) , len( _len )
{
	if( nullptr == _pDat || 1 > _len )
	{
		pDat = nullptr ;
		return ;
	}

	pDat = new ( std::nothrow ) uint8_t[ len ] ;
	if( nullptr == pDat )
	{
		len = 0 ;
		return ;
	}

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pDat[ pos ] = _pDat[ pos ] ;
	}
}


daniel::dns::EDNS0_OPTION::~EDNS0_OPTION()
{
	if( nullptr != pDat )
	{
		delete [] pDat ;
		pDat = nullptr ;
	}
}


void daniel::dns::EDNS0_OPTION::SetCode( EDNS0_OptCode const & _code )
{
	code = _code ;
}


void daniel::dns::EDNS0_OPTION::SetCode( uint16_t const & _code )
{
	if( false == IsValidEDNS0_OptCode( _code ) )
	{
		return ;
	} 

	code = enumFromUint16< EDNS0_OptCode >( _code ) ;
}


void daniel::dns::EDNS0_OPTION::SetData( uint8_t const * _pDat , uint16_t const & _len ) 
{
	bool isEqual = true ;

	if( len != _len )
	{
		isEqual = false ;
	}

	if( true == isEqual )
	{
		for( uint16_t pos = 0 ; pos < len ; ++pos )
		{
			if( pDat[ pos ] != _pDat[ pos ] )
			{
				isEqual = false ;
				break ;
			}
		}
	}

	if( true == isEqual )
	{
		return ;
	}

	if( len < _len )
	{
		delete [] pDat ;
		pDat = new ( std::nothrow ) uint8_t[ _len ] ;
	}

	len = _len ;

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pDat[ pos ] = _pDat[ pos ] ;
	}
}


daniel::dns::EDNS0_OptCode daniel::dns::EDNS0_OPTION::GetCode() const 
{
	return code ;
}


uint16_t daniel::dns::EDNS0_OPTION::GetLen() const 
{
	return len ;
}


uint8_t const * daniel::dns::EDNS0_OPTION::GetData() const 
{
	return pDat ;
}


	