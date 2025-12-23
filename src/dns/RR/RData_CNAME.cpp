#include "dns/RR/RData_CNAME.h"


daniel::dns::RR::RData_CNAME::RData_CNAME( uint8_t const * pRef )
	: RData_DNAME( pRef )
{
	
}


uint8_t const * daniel::dns::RR::RData_CNAME::GetCNAME() const
{
	return GetDName() ;
}