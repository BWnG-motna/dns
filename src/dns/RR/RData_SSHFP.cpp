#include "dns/RR/RData_SSHFP.h"


#include <sstream>
#include <iomanip> 


daniel::dns::RR::RData_SSHFP::RData_SSHFP()
	: RData( nullptr ) , 
	  algorithmNumber( SSHFP::Algorithm::RESERVED ) , 
	  fingerprintType( SSHFP::FingerprintType::RESERVED ) , 
	  fingerprintLen( 0 ) ,
	  pFP( nullptr )
{

}


daniel::dns::RR::RData_SSHFP::~RData_SSHFP()
{
	Initalize() ;
}


void daniel::dns::RR::RData_SSHFP::Initalize()
{
	if( nullptr != pFP )
	{
		delete [] pFP ;
		pFP = nullptr ;
	}

	algorithmNumber = SSHFP::Algorithm::RESERVED ;
	fingerprintType = SSHFP::FingerprintType::RESERVED ;
	fingerprintLen  = 0 ;
}


uint16_t daniel::dns::RR::RData_SSHFP::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pFP )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t >( algorithmNumber ) << " "
	   << static_cast< uint16_t >( fingerprintType ) << " " ;

	for( uint16_t pos = 0 ; pos < fingerprintLen ; ++pos )
	{
		ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( pFP[ pos ] ) ;
	}

	std::string s = ss.str() ;
	uint16_t len  = static_cast< uint16_t >( s.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_SSHFP::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	
	if( 3 > length )
	{
		return false ;
	}

	Initalize() ;

	if( true == SSHFP::IsValidAlgorithm( pData[ 0 ] ) )
	{
		algorithmNumber = enumFromUint8< SSHFP::Algorithm >( pData[ 0 ] ) ;
	}
	else
	{
		Initalize() ;
		return false ;
	}

	if( true == SSHFP::IsValidFingerprintType( pData[ 1 ] ) )
	{
		fingerprintType = enumFromUint8< SSHFP::FingerprintType >( pData[ 1 ] ) ;
	}
	else
	{
		Initalize() ;
		return false ;
	}
		

	fingerprintLen = length - 2 ;

	
	pFP = new ( std::nothrow ) uint8_t [ fingerprintLen + 1 ] ;
	if( nullptr == pFP )
	{
		Initalize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < fingerprintLen ; ++pos )
	{
		pFP[ pos ] = pData[ 2 + pos ] ;
	}

	return true ;
}


daniel::dns::RR::SSHFP::Algorithm daniel::dns::RR::RData_SSHFP::GetAlgorithm() const
{
	return algorithmNumber ;
}


daniel::dns::RR::SSHFP::FingerprintType daniel::dns::RR::RData_SSHFP::GetFingerprintType() const
{
	return fingerprintType ;
}


uint8_t const * daniel::dns::RR::RData_SSHFP::GetFingerprint() const
{
	return pFP ;
}


uint16_t daniel::dns::RR::RData_SSHFP::GetFingerprintLen() const
{
	return fingerprintLen ;
}