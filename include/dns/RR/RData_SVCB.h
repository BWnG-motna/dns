#pragma once

#include "Common.h"
#include "RData.h"
#include "SVC/SvcParam.h"
#include "ds/LinkedList.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_SVCB : public RData
{

private :
	uint16_t priority ;
	uint8_t * pTargetName ;

	ds::LinkedList< SVC::SvcParam > * pParam ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	bool IsAliasMode() const ;

public :
	uint32_t GetParamCount() const ;
	uint16_t GetPriority()   const ;
	uint8_t const * GetTargetname() const ;

public :
	 RData_SVCB( uint8_t const * pRef ) ;
	~RData_SVCB() ;


} ; // class RData_SVCB


}   // namespace RR

}   // namespace dns

}   // namespace daniel