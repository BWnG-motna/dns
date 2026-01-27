#pragma once

#include "Common.h"
#include "RData.h"
#include "SvcParam.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_HTTPS : public RData
{

private :
	static constexpr uint16_t const targetMaxLen  = 512 ;
	static constexpr uint16_t const paramMaxCount =  32 ;

private :
	uint16_t priority ;
	uint8_t  targetName[ targetMaxLen ] ;

	SvcParam param[ paramMaxCount ] ;

private :
	uint16_t paramCount = 0 ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	bool IsAliasMode() const ;

public :
	uint16_t GetParamCount() const ;
	uint16_t GetPriority()   const ;
	uint8_t const * GetTargetname() const ;

public :
	RData_HTTPS( uint8_t const * pRef ) ;


} ; // class RData_HTTPS


}   // namespace RR

}   // namespace dns

}   // namespace daniel