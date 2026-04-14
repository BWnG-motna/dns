#include "dns/RR/RData_DSYNC.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_DSYNC::RData_DSYNC()
	: RData( nullptr ) , type( QType::UNKNOWN ) , scheme( 0 ) , port( 0 ) , pTarget( nullptr )
{

}


daniel::dns::RR::RData_DSYNC::~RData_DSYNC()
{
	Initialize() ;
}


void daniel::dns::RR::RData_DSYNC::Initialize()
{
	if( nullptr != pTarget )
	{
		delete [] pTarget ;
		pTarget = nullptr ;
	}

	type   = QType::UNKNOWN ;
	scheme = 0 ;
	port   = 0 ;
}


uint16_t daniel::dns::RR::RData_DSYNC::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << ToString( type )                  << " " 
	   << static_cast< uint16_t >( scheme ) << " "
	   << static_cast< uint16_t >( port   ) << " "
	   << reinterpret_cast< char const * >( pTarget ) ;

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


bool daniel::dns::RR::RData_DSYNC::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 6 > length )
	{
		return false ;
	}

	Initialize() ;


	uint16_t val 
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	if( true == IsValidQType( val ) )
	{
		type = enumFromUint16< QType >( val ) ;
	}
	else
	{
		type = QType::UNKNOWN ;
	}

	scheme = pData[ 2 ] ; 

	port
		= ( ( pData[ 3 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 4 ] << 0 ) & 0x00FF ) ;

	uint16_t len = GetDNDataLen( & ( pData[ 5 ] ) ) ;

	uint16_t allocSize = ( 0 < len ) ? ( len + 1 ) : 2 ;
	pTarget = new ( std::nothrow ) uint8_t [ allocSize ] ;
	if( nullptr == pTarget )
	{
		Initialize() ;
	}

	if( 0 < len )
	{ 
		len = GetDNData( pTarget , len + 1 , & ( pData[ 5 ] ) ) ; 
	}
	else
	{
		pTarget[ 0 ] = '.' ;
		pTarget[ 1 ] = '\0' ;
	}

	return true ;
}


daniel::dns::QType daniel::dns::RR::RData_DSYNC::GetType() const
{
	return type ;
}


uint8_t  daniel::dns::RR::RData_DSYNC::GetScheme() const
{
	return scheme ;
}


uint16_t daniel::dns::RR::RData_DSYNC::GetPort() const
{
	return port ;
}


uint8_t const * daniel::dns::RR::RData_DSYNC::GetTarget() const
{
	return pTarget ;
}