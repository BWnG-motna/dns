#include "dns/RR/RData_MG.h"


daniel::dns::RR::RData_MG::RData_MG( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


uint8_t const * daniel::dns::RR::RData_MG::GetMgmName() const
{
	return GetName() ;
}