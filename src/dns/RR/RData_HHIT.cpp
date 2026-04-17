#include "dns/RR/RData_HHIT.h"


#include <sstream>
#include <iomanip>


daniel::dns::RR::RData_HHIT::RData_HHIT()
	: RData( nullptr ) 
{

}


daniel::dns::RR::RData_HHIT::~RData_HHIT()
{
	Initialize() ;
}


void daniel::dns::RR::RData_HHIT::Initialize()
{
	
}


uint16_t daniel::dns::RR::RData_HHIT::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << "["
	   << static_cast< uint16_t >( cddl.GetType() ) << ", \""
	   << reinterpret_cast< char const * >( cddl.GetAbb() ) <<"\", h\'" ;

	uint16_t      certlen = cddl.GetCertLen() ;
	uint8_t const * pCert = cddl.GetCert() ;

	for( uint16_t pos = 0 ; pos < certlen ; ++pos )
	{
		ss << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast< uint16_t >( pCert[ pos ] ) ;
	}

	ss << std::dec << std::setw( 1 ) << ']' ;

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


bool daniel::dns::RR::RData_HHIT::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 0x83 != pData[ 0 ] )
	{
		return false ;
	}

	if( false == cddl.Load( & pData[ 1 ] , length - 1 ) )
	{
		return false ;
	}

	return true ;
}