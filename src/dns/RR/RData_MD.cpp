#include "dns/RR/RData_MD.h"


daniel::dns::RR::RData_MD::RData_MD( uint8_t const * pRef )
	: RData_DNAME( pRef )
{
	
}


uint8_t const * daniel::dns::RR::RData_MD::GetMadName() const
{
	return GetDName() ;
}