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


enum class Algorithm : uint8_t
{
	RESERVED  =   0 ,
	RSA       =   1 ,
	DSA       =   2 ,
	ECDSA     =   3 ,
	ED25519   =   4 ,
	ED448     =   6 ,

} ; // enum class Algorithm


bool IsValidAlgorithm( uint8_t const & algorithmNumber ) ;


}   // namespace SSHFP

}   // namespace RR

}   // namespace dns

}   // namespace daniel