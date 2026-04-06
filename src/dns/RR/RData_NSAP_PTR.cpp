#include "dns/RR/RData_NSAP_PTR.h"


daniel::dns::RR::RData_NSAP_PTR::RData_NSAP_PTR( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


daniel::dns::RR::RData_NSAP_PTR::~RData_NSAP_PTR()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NSAP_PTR::Initialize()
{

}


uint8_t const * daniel::dns::RR::RData_NSAP_PTR::GetPTRDName() const
{
	return GetName() ;
}