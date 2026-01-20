#include "dns/RR/RData_PTR.h"


daniel::dns::RR::RData_PTR::RData_PTR( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


uint8_t const * daniel::dns::RR::RData_PTR::GetPTRDName() const
{
	return GetName() ;
}