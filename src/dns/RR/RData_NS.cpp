#include "dns/RR/RData_NS.h"


daniel::dns::RR::RData_NS::RData_NS( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


daniel::dns::RR::RData_NS::~RData_NS()
{
	Initialize() ;
}


void daniel::dns::RR::RData_NS::Initialize()
{

}


uint8_t const * daniel::dns::RR::RData_NS::GetNSDName() const
{
	return GetName() ;
}