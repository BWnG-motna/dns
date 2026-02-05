#include "dns/RR/RData_CNAME.h"


daniel::dns::RR::RData_CNAME::RData_CNAME( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


daniel::dns::RR::RData_CNAME::~RData_CNAME()
{
	Initalize() ;
}


void daniel::dns::RR::RData_CNAME::Initalize()
{

}


uint8_t const * daniel::dns::RR::RData_CNAME::GetCNAME() const
{
	return GetName() ;
}