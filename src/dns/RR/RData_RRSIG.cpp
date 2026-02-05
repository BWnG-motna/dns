#include "dns/RR/RData_RRSIG.h"


#include <sstream>
#include <iomanip>
#include <memory>


daniel::dns::RR::RData_RRSIG::RData_RRSIG( uint8_t const * pRef )
	: RData( pRef )    , typeCovered( QType::NS )   , algorithm( SEC::SECAlgo::INVALID ) , 
	  labels( 0 )      , ttl( 0 ) , expiration( 0 ) , inception( 0 ) , keyTag( 0 )  ,
	  pName( nullptr ) , pSign( nullptr ) , signLen( 0 )
{

}


daniel::dns::RR::RData_RRSIG::~RData_RRSIG()
{
	Initalize() ;
}


void daniel::dns::RR::RData_RRSIG::Initalize()
{
	if( nullptr != pName )
	{
		delete [] pName ;
		pName = nullptr ;
	}

	if( nullptr != pSign )
	{
		delete [] pSign ;
		pSign = nullptr ;
	}


	typeCovered = QType::NS ;
	algorithm   = SEC::SECAlgo::INVALID ;
	labels      = 0 ;
	ttl         = 0 ;
	expiration  = 0 ;
	inception   = 0 ;
	keyTag      = 0 ;
	signLen     = 0 ;
}


uint16_t daniel::dns::RR::RData_RRSIG::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pName || nullptr == pSign )
	{
		return 0 ;
	}
	

	std::stringstream ss ;

	ss << daniel::dns::ToString( typeCovered ) << "\t"
	   << static_cast< uint16_t >( algorithm ) << "\t" //<< "(" << daniel::dns::RR::ToString( algorithm ) << ")\t"
	   << static_cast< uint16_t >( labels )    << "\t"
	   << ttl        << "\t"
	   << expiration << "\t"
	   << inception  << "\t"
	   << "0x"       << std::hex << std::setw( 4 ) << std::setfill( '0' ) << keyTag << "\t"
	   << reinterpret_cast< char const * >( pName ) << "\t"
	   << std::dec   << std::setw( 0 ) << std::setfill( ' ' ) 
	   << static_cast< uint16_t >( signLen )       << " bytes - signature" ;

	std::string str = ss.str() ;

	uint16_t len = static_cast< uint16_t >( str.length() ) ;
	for( uint16_t pos = 0 ; pos < len && pos < length ; ++pos )
	{
		pStr[ pos ] = str[ pos ] ;
	}

	uint16_t less = len < ( length - 1 ) ? len : ( length - 1 ) ;
	pStr[ less ] = '\0' ;

	return less  ;
}


bool daniel::dns::RR::RData_RRSIG::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 18 > length )
	{
		return false ;
	}

	Initalize() ;
	
	uint16_t type
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;

	typeCovered = daniel::enumFromUint16< QType >( type ) ;

	if( false == SEC::IsValidAlgo( pData[ 2 ] ) )
	{
		Initalize() ;
		return false ;
	}
	else
	{
		algorithm = daniel::enumFromUint8< SEC::SECAlgo >( pData[ 2 ] ) ;
	}

	labels = pData[ 3 ] ;

	ttl
		= ( ( pData[  4 ] << 24 ) & 0xFF000000 )
		| ( ( pData[  5 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[  6 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[  7 ] <<  0 ) & 0x000000FF ) ;

	expiration
		= ( ( pData[  8 ] << 24 ) & 0xFF000000 )
		| ( ( pData[  9 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ 10 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ 11 ] <<  0 ) & 0x000000FF ) ;

	inception
		= ( ( pData[ 12 ] << 24 ) & 0xFF000000 )
		| ( ( pData[ 13 ] << 16 ) & 0x00FF0000 )
		| ( ( pData[ 14 ] <<  8 ) & 0x0000FF00 )
		| ( ( pData[ 15 ] <<  0 ) & 0x000000FF ) ;

	keyTag
		= ( ( pData[ 16 ] <<  8 ) & 0xFF00 )
		| ( ( pData[ 17 ] <<  0 ) & 0x00FF ) ;

	uint16_t len = 0 ;

	len = GetDNDataLen( & ( pData[ 18 ] ) ) ;

	if( 1 > len )
	{
		Initalize() ;
		return false ;
	}

	pName = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pName )
	{
		Initalize() ;
		return false ;
	}


	len = GetDNData( pName , len + 1 , & ( pData[ 18 ] ) ) ; 
	len = SkipDName( & ( pData[ 18 ] ) , length - 18 ) ;

	signLen = length - ( 18 + len ) ;

	pSign = new ( std::nothrow ) uint8_t [ signLen ] ;

	for( uint16_t pos = 0 ; pos < signLen ; ++pos )
	{
		pSign[ pos ] = pData[ 18 + len + pos ] ;
	}

	return true ;
}


daniel::dns::QType daniel::dns::RR::RData_RRSIG::GetTypeCovered() const
{
	return typeCovered ;
}


daniel::dns::RR::SEC::SECAlgo daniel::dns::RR::RData_RRSIG::GetAlgorithm() const
{
	return algorithm ;
}


uint8_t daniel::dns::RR::RData_RRSIG::GetLabels() const
{
	return labels ;
}


uint32_t daniel::dns::RR::RData_RRSIG::GetTTL() const
{
	return ttl ;
}


uint32_t daniel::dns::RR::RData_RRSIG::GetExpiration() const
{
	return expiration ;
}


uint32_t daniel::dns::RR::RData_RRSIG::GetInception() const
{
	return inception ;
}


uint16_t daniel::dns::RR::RData_RRSIG::GetKeyTag() const
{
	return keyTag ;
}


uint8_t const * daniel::dns::RR::RData_RRSIG::GetName() const
{
	return pName ;
}


uint8_t const * daniel::dns::RR::RData_RRSIG::GetSign() const
{
	return pSign ;
}


uint16_t daniel::dns::RR::RData_RRSIG::GtetSignLen() const
{
	return signLen ;
}