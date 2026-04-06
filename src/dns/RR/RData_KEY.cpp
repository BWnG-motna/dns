#include "dns/RR/RData_KEY.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_KEY::RData_KEY()
	: RData( nullptr ) , noAuth( false ) , noConf( false ) , extflg( false ) , zoneKey( false ) ,
	  sgnfield( 0 ) , flags( 0 ) , protocol( 0 ) , algorithm( SEC::SECAlgo::INVALID ) , pklen( 0 ) , pk( nullptr )
{

}


daniel::dns::RR::RData_KEY::~RData_KEY()
{
	Initialize() ;
}


void daniel::dns::RR::RData_KEY::Initialize()
{
	if( nullptr != pk )
	{
		delete [] pk ;
		pk = nullptr ;
	}

	noAuth   = false ;
	noConf   = false ;
	extflg   = false ;
	zoneKey  = false ;

	sgnfield = 0 ;
	pklen    = 0 ;
	flags    = 0 ;
	protocol = 0 ;

	algorithm = SEC::SECAlgo::INVALID ;
}


uint16_t daniel::dns::RR::RData_KEY::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pk )
	{
		return 0 ;
	}


	std::stringstream ss ;

	ss << "flag: " << std::hex << std::setw( 4 ) << std::setfill( '0' ) << flags << "\t"
	   << std::dec << std::setw( 0 ) << std::setfill( ' ' )
	   << "protocol: "   << static_cast< uint16_t >( protocol )  << "\t"
	   << "algorithm: "  << static_cast< uint16_t >( algorithm ) << "\t"
	   << "public key: " << static_cast< uint16_t >( pklen )     << " byte(s)" ;

	std::string str = ss.str() ;

	uint16_t len = static_cast< uint16_t >( str.length() ) ;
	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;
	
	return less ;
}


bool daniel::dns::RR::RData_KEY::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 4 > length )
	{
		return false ;
	}

	Initialize() ;

	flags 
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	noAuth  = ( 0 < ( flags & 0x8000 ) ) ? true : false ;
	noConf  = ( 0 < ( flags & 0x4000 ) ) ? true : false ;
	extflg  = ( 0 < ( flags & 0x1000 ) ) ? true : false ;
	zoneKey = ( 0 < ( flags & 0x0100 ) ) ? true : false ;

	sgnfield = static_cast< uint8_t >( flags & 0x000F ) ;

	if( true == extflg )
	{
		Initialize() ;
		return false ;
	}

	protocol  = pData[ 2 ] ;
	algorithm = daniel::enumFromUint8< SEC::SECAlgo >( pData[ 3 ] ) ;
	pklen     = length - 4 ;

	pk = new ( std::nothrow ) uint8_t [ pklen ] ;
	if( nullptr == pk )
	{
		Initialize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < pklen ; ++pos )
	{
		pk[ pos ] = pData[ 4 + pos ] ;
	}

	return true ;
}


bool daniel::dns::RR::RData_KEY::IsNoAuth()  const
{
	return noAuth ;
}


bool daniel::dns::RR::RData_KEY::IsNoConf()  const
{
	return noConf ;
}


bool daniel::dns::RR::RData_KEY::IsZoneKey() const
{
	return zoneKey ;
}


uint8_t daniel::dns::RR::RData_KEY::GetSignField() const
{
	return sgnfield ;	
}


daniel::dns::RR::SEC::SECAlgo daniel::dns::RR::RData_KEY::GetAlgorithm() const
{
	return algorithm ;
}


uint8_t const * daniel::dns::RR::RData_KEY::GetPublicKey() const
{
	return pk ;
}


uint16_t daniel::dns::RR::RData_KEY::GetFlags() const
{
	return flags ;
}


uint16_t daniel::dns::RR::RData_KEY::GetPublicKeyLength() const
{
	return pklen ;
}