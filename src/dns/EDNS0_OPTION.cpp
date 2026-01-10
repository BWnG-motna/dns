#include "dns/EDNS0_OPTION.h"


daniel::dns::EDNS0_OPTION::EDNS0_OPTION()
	: code( 0 ) , len( 0 ) , pDat( nullptr )
{
	
}


void daniel::dns::EDNS0_OPTION::SetCode( uint16_t const & _code )
{
	code = _code ;
}


void daniel::dns::EDNS0_OPTION::SetLen ( uint16_t const & _len ) 
{
	len = _len ;
}


void daniel::dns::EDNS0_OPTION::SetData( uint8_t * _pDat ) 
{
	pDat = _pDat ;
}


uint16_t daniel::dns::EDNS0_OPTION::GetCode() const 
{
	return code ;
}


uint16_t daniel::dns::EDNS0_OPTION::GetLen() const 
{
	return len ;
}


uint8_t * daniel::dns::EDNS0_OPTION::GetData() const 
{
	return pDat ;
}


	