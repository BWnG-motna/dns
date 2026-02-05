#include "dns/RR/RData_MF.h"


daniel::dns::RR::RData_MF::RData_MF( uint8_t const * pRef )
	: RData_NAME( pRef )
{
	
}


daniel::dns::RR::RData_MF::~RData_MF()
{
	Initalize() ;
}


void daniel::dns::RR::RData_MF::Initalize()
{

}


uint8_t const * daniel::dns::RR::RData_MF::GetMadName() const
{
	return GetName() ;
}