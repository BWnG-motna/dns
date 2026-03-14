#include "dns/RR/RData_MB.h"


daniel::dns::RR::RData_MB::RData_MB( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


daniel::dns::RR::RData_MB::~RData_MB()
{
	Initialize() ;
}


void daniel::dns::RR::RData_MB::Initialize()
{

}


uint8_t const * daniel::dns::RR::RData_MB::GetMadName() const
{
	return GetName() ;
}