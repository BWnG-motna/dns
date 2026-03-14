#pragma once


#include "Common.h"


namespace daniel
{

namespace dns
{

class DNpointer
{

private :
	uint8_t const * pDataGram ;

public :
	uint16_t GetDNData   ( uint8_t       * pBuf , uint16_t const & length  , uint8_t const * pRef , bool const & fqdn = true ) const ;
	uint16_t SkipDName   ( uint8_t const * pBuf , uint16_t const & length  ) const ;
	uint16_t GetDNDataLen( uint8_t const * pRef , bool const & fqdn = true ) const ;
	void     SetDataGram ( uint8_t const * pRef ) ;

public :
	uint8_t const * GetDataGram() const ;

public :
	 DNpointer() ;
	 DNpointer( uint8_t const * pRef ) ;
	~DNpointer() ;

	
} ; // class DNpointer

}  // namespace dns
	
}  // namespace daniel