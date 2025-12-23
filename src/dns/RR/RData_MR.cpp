#include "dns/RR/RData_MR.h"


daniel::dns::RR::RData_MR::RData_MR( uint8_t const * pRef )
	: RData_DNAME( pRef )
{
	
}


uint8_t const * daniel::dns::RR::RData_MR::GetNewName() const
{
	return GetDName() ;
}