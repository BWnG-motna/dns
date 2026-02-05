#pragma once

#include "Common.h"
#include "RData.h"


namespace daniel
{

namespace dns
{

namespace RR
{


class RData_LOC : public RData
{

private :
	uint8_t  version ;
	uint8_t  size ;
	uint8_t  horiz_prec ;
	uint8_t  verti_prec ;
	uint32_t  latitude ;
	uint32_t longitude ;
	uint32_t  altitude ; 

private :
	uint64_t DecodeCM( uint8_t const & cm ) const ;
	uint64_t SpreadBits ( uint32_t const & value ) const ;
	uint32_t CompactBits( uint64_t const value ) const ;

private :
	void Initalize() override ;

public :
	uint16_t ToNullStr( uint8_t * pStr , uint16_t const & length ) const override ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) override ;

public :
	uint8_t  GetVersion()    const ;

	uint8_t  GetSize()       const ; // 10^exponent x mantissa  MSB 4bit - mantissa  /  LSB 4bit - exponent
	uint8_t  GetHorizPrec()  const ; // 10^exponent x mantissa  MSB 4bit - mantissa  /  LSB 4bit - exponent
	uint8_t  GetVertiPrec()  const ; // 10^exponent x mantissa  MSB 4bit - mantissa  /  LSB 4bit - exponent

	uint64_t GetRealSize()      const ;
	uint64_t GetRealHorizPrec() const ;
	uint64_t GetRealVertiPrec() const ;

	uint32_t GetLatitude()   const ;
	uint32_t GetLongitude()  const ;
	uint32_t GetAltitude()   const ;

	  double GetLatitudeDegrees()  const ;
	  double GetLongitudeDegrees() const ;
	  double GetAltitudeMeters()   const ;

	  double GetRealSizeMeters()       const ;
	  double GetRealHorizPrecMeters()  const ;
	  double GetRealVertiPrecMeters()  const ;

public :
	int32_t  GetLatitudeINT()  const ;
	int32_t  GetLongitudeINT() const ;
	int32_t  GetAltitudeINT()  const ;

public :
	uint64_t Interleave() const ;
	uint64_t Interleave( uint32_t const & x , uint32_t const & y ) const ;
	uint32_t DeinterleaveX( uint64_t const & value ) const ;
	uint32_t DeinterleaveY( uint64_t const & value ) const ;

public :
	 RData_LOC() ;
	~RData_LOC() ;

} ; // class RData_LOC

	
}   // name RR

}   // namespace dns
	
}   // namespace daniel