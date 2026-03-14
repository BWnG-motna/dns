#include "dns/RR/RData_MR.h"


daniel::dns::RR::RData_MR::RData_MR( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


daniel::dns::RR::RData_MR::~RData_MR()
{
	Initialize() ;
}



void daniel::dns::RR::RData_MR::Initialize()
{

}


uint8_t const * daniel::dns::RR::RData_MR::GetNewName() const
{
	return GetName() ;
}