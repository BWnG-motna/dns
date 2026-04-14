#pragma once

#include "Common.h"
#include "RData.h"

#include "dns/QType.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_DSYNC : public RData
{

private :
	QType     type ;
	uint8_t   scheme ;
	uint16_t  port ;
	uint8_t * pTarget ;

private :
	void Initialize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	QType    GetType()   const ;
	uint8_t  GetScheme() const ;
	uint16_t GetPort()   const ;

	uint8_t const * GetTarget() const ;

public :
	 RData_DSYNC() ;
	~RData_DSYNC() ;

} ; // class RData_DSYNC
	
	
}   // name RR

}   // namespace dns
	
}   // namespace daniel