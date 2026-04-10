#include "dns/RR/RData_DNAME.h"


daniel::dns::RR::RData_DNAME::RData_DNAME( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


daniel::dns::RR::RData_DNAME::~RData_DNAME()
{
	Initialize() ;
}


void daniel::dns::RR::RData_DNAME::Initialize()
{

}


uint8_t const * daniel::dns::RR::RData_DNAME::GetTarget() const
{
	return GetName() ;
}