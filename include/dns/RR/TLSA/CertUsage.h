#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{


enum class CertUsage : uint8_t
{
	PKIX_TA  =   0 , // CA Constraint
	PKIX_EE  =   1 , // Service Cerificate Constraint
	DANE_TA  =   2 , // Trust Anchor Assertion
	DANE_EE  =   3 , // Domain Issued Certificate

} ; // enum class CertUsage 


bool IsValidCertUsage( uint8_t const & certUsageNo ) ;


}   // namespace RR

}   // namespace dns

}   // namespace daniel