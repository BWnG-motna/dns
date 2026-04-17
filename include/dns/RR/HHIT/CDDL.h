#pragma once

#include "Common.h"

#include "EntityType.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace HHIT
{


class CDDL
{

private :
	EntityType   type  ;
	uint8_t    * pAbb  ; // maximum - 15 + NULL
	uint8_t    * pCert ; // X.509 DER certificate

private :
	uint16_t certlen ;

private :
	void Initialize() ;

public :
	bool Load( uint8_t const * pData , uint16_t const & length ) ;

public :
	EntityType GetType() const ;
	uint16_t GetCertLen() const ;

	uint8_t const * GetAbb()  const ;
	uint8_t const * GetCert() const ;

public :
	void SetType( EntityType const & type ) ;
	void SetAbb ( uint8_t const * pAbb  , uint16_t const & len ) ;
	void SetCert( uint8_t const * pCert , uint16_t const & len ) ;

public :
	 CDDL() ;
	~CDDL() ;

} ; // class CDDL


}   // namespace HHIT

}   // namespace RR

}   // namespace dns

}   // namespace daniel