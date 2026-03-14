#include "dns/RR/HIP/RVS.h"


#include <iostream>


daniel::dns::RR::HIP::RVS::RVS()
	: pDat( nullptr ) , len( 0 )
{

}


daniel::dns::RR::HIP::RVS::~RVS()
{
	if( nullptr != pDat )
	{
		delete [] pDat ;
		pDat = nullptr ;
	}
	
	len  = 0 ;
}


void daniel::dns::RR::HIP::RVS::Set( uint8_t const * p , uint16_t const & _len )
{
	if( nullptr == p || 1 > _len )
	{
		return ;
	}

	pDat = p ;
	len  = _len ;
}


uint8_t const * daniel::dns::RR::HIP::RVS::Get() const
{
	return pDat ;
}


uint16_t daniel::dns::RR::HIP::RVS::GetLen() const
{
	return len ;
}