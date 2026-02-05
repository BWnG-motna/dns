#include "dns/RR/RData_SRV.h"


#include <sstream>


daniel::dns::RR::RData_SRV::RData_SRV( uint8_t const * pRef )
	: RData( pRef ) , priority( 0 ) , weight( 0 ) , port( 0 ) , pTarget( nullptr )
{

}


daniel::dns::RR::RData_SRV::~RData_SRV()
{
	Initalize() ;
}


void daniel::dns::RR::RData_SRV::Initalize()
{
	if( nullptr != pTarget )
	{
		delete [] pTarget ;
		pTarget = nullptr ;
	}

	priority = 0 ;
	weight   = 0 ;
	port     = 0 ;
}


uint16_t daniel::dns::RR::RData_SRV::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pTarget )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << static_cast< uint16_t>( priority ) << '\t'
	   << static_cast< uint16_t>( weight   ) << '\t'
	   << static_cast< uint16_t>( port     ) << '\t'
	   << reinterpret_cast< char const * >( pTarget ) ;

	std::string s = ss.str() ;
	uint16_t len  = static_cast< uint16_t >( s.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < length ? len : length ;
	pStr[ less ] = '\0' ;

	return less ;
}


bool daniel::dns::RR::RData_SRV::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}


	if( 7 > length )
	{
		return false ;
	}

	Initalize() ;

	priority
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	weight
		= ( ( pData[ 2 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 3 ] << 0 ) & 0x00FF ) ;

	port
		= ( ( pData[ 4 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 5 ] << 0 ) & 0x00FF ) ;

	uint16_t len = GetDNDataLen( & ( pData[ 6 ] ) ) ;
	if( 1 > len )
	{
		Initalize() ;
		return false ;
	}

	

	pTarget = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pTarget )
	{
		Initalize() ;
		return false ;
	}

	len = GetDNData( pTarget , len + 1 , & ( pData[ 6 ] ) ) ;

	return true ;
}


uint16_t daniel::dns::RR::RData_SRV::GetPriority() const
{
	return priority ;
}


uint16_t daniel::dns::RR::RData_SRV::GetWeight() const
{
	return weight ;
}


uint16_t daniel::dns::RR::RData_SRV::GetPort() const
{
	return port ;
}


uint8_t const * daniel::dns::RR::RData_SRV::GetTarget() const
{
	return pTarget ;
}