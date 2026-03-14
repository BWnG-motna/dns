#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace CERT
{


enum class CertType : uint16_t
{
	RESERVED   =     0 ,

	PKIX       =     1 ,
	SPKI       =     2 ,
	PGP        =     3 ,
	IPKIX      =     4 ,
	ISPKI      =     5 ,
	IPGP       =     6 ,
	ACPKIX     =     7 ,
	IACPKIX    =     8 ,

	URI        =   253 ,
	OID        =   254 ,

} ; // enum class CertType


bool IsValidCertType( uint16_t const & certTypeNo ) ;


}   // namespace CERT

}   // namespace RR

}   // namespace dns

}   // namespace daniel