#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace SSHFP
{


enum class FingerprintType : uint8_t
{
	RESERVED  =   0 ,
	SHA1      =   1 ,
	SHA256    =   2 ,
	
} ; // enum class Fingerprint


bool IsValidFingerprintType( uint8_t const & algorithmNumber ) ;


}   // namespace SSHFP

}   // namespace RR

}   // namespace dns

}   // namespace daniel