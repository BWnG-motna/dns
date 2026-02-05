#include "dns/RR/RData_DNSKEY.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_DNSKEY::RData_DNSKEY()
	: RData( nullptr ) , zsk( false ) , sep( false ) , flags( 0 ) , protocol( 0 ) , algorithm( SEC::SECAlgo::INVALID ) , pklen( 0 ) , pk( nullptr )
{

}


daniel::dns::RR::RData_DNSKEY::~RData_DNSKEY()
{
	Initalize() ;
}


void daniel::dns::RR::RData_DNSKEY::Initalize()
{
	if( nullptr != pk )
	{
		delete [] pk ;
		pk = nullptr ;
	}

	pklen = 0 ;

	zsk = false ;
	sep = false ;

	flags    = 0 ;
	protocol = 0 ;

	algorithm = SEC::SECAlgo::INVALID ;
}


uint16_t daniel::dns::RR::RData_DNSKEY::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
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

	ss << "zsk: "  << ( true == zsk ? 1 : 0 )    << "\t"
	   << "sep: "  << ( true == sep ? 1 : 0 )    << "\t"
	   << "flag: " << std::hex << std::setw( 4 ) << std::setfill( '0' ) << flags << "\t"
	   << std::dec << std::setw( 0 ) << std::setfill( ' ' )
	   << static_cast< uint16_t >( protocol )  << "\t"
	   << static_cast< uint16_t >( algorithm ) << "\t"
	   << static_cast< uint16_t >( pklen )     << " bytes - publickey" ;

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


bool daniel::dns::RR::RData_DNSKEY::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 4 > length )
	{
		return false ;
	}

	Initalize() ;

	flags 
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	zsk = ( 0 < ( pData[ 0 ] & 0x01 ) ) ? true : false ;
	sep = ( 0 < ( pData[ 1 ] & 0x01 ) ) ? true : false ;

	protocol  = pData[ 2 ] ;
	algorithm = daniel::enumFromUint8< SEC::SECAlgo >( pData[ 3 ] ) ;
	pklen     = length - 4 ;

	pk = new ( std::nothrow ) uint8_t [ pklen ] ;
	if( nullptr == pk )
	{
		Initalize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < pklen ; ++pos )
	{
		pk[ pos ] = pData[ 4 + pos ] ;
	}

	return true ;
}


bool daniel::dns::RR::RData_DNSKEY::IsSetZSK() const
{
	return zsk ;
}


bool daniel::dns::RR::RData_DNSKEY::IsSetSEP() const
{
	return sep ;
}


daniel::dns::RR::SEC::SECAlgo daniel::dns::RR::RData_DNSKEY::GetAlgorithm() const
{
	return algorithm ;
}


uint8_t const * daniel::dns::RR::RData_DNSKEY::GetPublicKey() const
{
	return pk ;
}


uint16_t daniel::dns::RR::RData_DNSKEY::GetFlags() const
{
	return flags ;
}


uint16_t daniel::dns::RR::RData_DNSKEY::GetPublicKeyLength() const
{
	return pklen ;
}