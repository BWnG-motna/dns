#include "dns/RR/RData_LOC.h"


#include <sstream>
#include <iomanip>
#include <cmath>


daniel::dns::RR::RData_LOC::RData_LOC()
	: RData( nullptr ) , version( 0 )    , size( 0 ) , 
	  horiz_prec( 0 )  , verti_prec( 0 ) , 
	  latitude( 0 )    , longitude( 0 )  , altitude( 0 ) 
{
	
}


daniel::dns::RR::RData_LOC::~RData_LOC()
{
	Initalize() ;
}


void daniel::dns::RR::RData_LOC::Initalize()
{
	version    = 0 ;
	size       = 0 ;
	horiz_prec = 0 ;
	verti_prec = 0 ;
	latitude   = 0 ;
	longitude  = 0 ;
	altitude   = 0 ;
}


uint16_t daniel::dns::RR::RData_LOC::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	 double lat     = GetLatitudeDegrees() ;
    char   latDir  = ( 0.0 <= lat ) ? 'N' : 'S' ;
    double latAbs  = std::abs( lat ) ;

    int    latDeg  = static_cast< int >( latAbs  ) ;
    double latMinF = ( latAbs  - latDeg ) * 60.0 ;
    int    latMin  = static_cast< int >( latMinF ) ;
    double latSec  = ( latMinF - latMin ) * 60.0 ;

    double lon     = GetLongitudeDegrees() ;
    char   lonDir  = ( 0.0 <= lon ) ? 'E' : 'W';
    double lonAbs  = std::abs( lon );

    int    lonDeg  = static_cast< int >( lonAbs  ) ;
    double lonMinF = ( lonAbs  - lonDeg ) * 60.0 ;
    int    lonMin  = static_cast< int >( lonMinF ) ;
    double lonSec  = ( lonMinF - lonMin ) * 60.0 ;

    std::stringstream ss ;

    ss << std::fixed 
       << latDeg << " " << latMin << " " << std::setprecision( 3 ) << latSec << " " << latDir << " " 
       << lonDeg << " " << lonMin << " " << std::setprecision( 3 ) << lonSec << " " << lonDir << " "
       << std::setprecision( 2 ) 
       << GetAltitudeMeters()      << "m "
       << GetRealSizeMeters()      << "m "
       << GetRealHorizPrecMeters() << "m "
       << GetRealVertiPrecMeters() << "m "
       << "( "
       << std::setprecision( 6 ) << GetLatitudeDegrees()  << " , "
       << std::setprecision( 6 ) << GetLongitudeDegrees() << " ) " 
       << "( "
       << GetLatitudeINT()  << " , " 
       << GetLongitudeINT() << " - "
       << Interleave()      << " )" ;

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


bool daniel::dns::RR::RData_LOC::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 16 != length )
	{
		return false ;
	}

	Initalize() ;

	version    = pData[ 0 ] ;
	size       = pData[ 1 ] ;
	horiz_prec = pData[ 2 ] ;
	verti_prec = pData[ 3 ] ;

	latitude
		= ( ( pData[  4 ] << 24 ) & 0xFF000000U )
		| ( ( pData[  5 ] << 16 ) & 0x00FF0000U )
		| ( ( pData[  6 ] <<  8 ) & 0x0000FF00U )
		| ( ( pData[  7 ] <<  0 ) & 0x000000FFU ) ;

	longitude
		= ( ( pData[  8 ] << 24 ) & 0xFF000000U )
		| ( ( pData[  9 ] << 16 ) & 0x00FF0000U )
		| ( ( pData[ 10 ] <<  8 ) & 0x0000FF00U )
		| ( ( pData[ 11 ] <<  0 ) & 0x000000FFU ) ;

	altitude
		= ( ( pData[ 12 ] << 24 ) & 0xFF000000U )
		| ( ( pData[ 13 ] << 16 ) & 0x00FF0000U )
		| ( ( pData[ 14 ] <<  8 ) & 0x0000FF00U )
		| ( ( pData[ 15 ] <<  0 ) & 0x000000FFU ) ;

	return true ;
}


uint8_t daniel::dns::RR::RData_LOC::GetVersion() const
{
	return version ;
}


uint8_t daniel::dns::RR::RData_LOC::GetSize() const
{
	return size ;
}


uint8_t daniel::dns::RR::RData_LOC::GetHorizPrec() const
{
	return horiz_prec ;
}


uint8_t daniel::dns::RR::RData_LOC::GetVertiPrec() const
{
	return verti_prec ;
}


uint64_t daniel::dns::RR::RData_LOC::DecodeCM( uint8_t const & cm ) const
{
	if( 0 == cm )
	{
		return 0 ;
	}


	uint8_t mantissa = ( cm >> 4 ) & 0x0F ;
	uint8_t exponent = ( cm >> 0 ) & 0x0F ;

	if( 0 == mantissa )
	{
		return 0 ;
	}

	uint64_t value = mantissa ;
	for( uint8_t pos = 0 ; pos < exponent ; ++pos )
	{
		value *= 10 ;
	}

	return value ;
}


uint64_t daniel::dns::RR::RData_LOC::GetRealSize() const
{
	return DecodeCM( size ) ;
}


uint64_t daniel::dns::RR::RData_LOC::GetRealHorizPrec() const
{
	return DecodeCM( horiz_prec ) ;
}


uint64_t daniel::dns::RR::RData_LOC::GetRealVertiPrec() const
{
	return DecodeCM( verti_prec ) ;
}


uint32_t daniel::dns::RR::RData_LOC::GetLatitude() const
{
	return latitude ;
}


uint32_t daniel::dns::RR::RData_LOC::GetLongitude() const 
{
	return longitude ;
}


uint32_t daniel::dns::RR::RData_LOC::GetAltitude() const
{
	return altitude ;
}


double daniel::dns::RR::RData_LOC::GetLatitudeDegrees() const
{
	return static_cast< double >( latitude - 0x80000000LL ) / 3600000.0 ;
}


double daniel::dns::RR::RData_LOC::GetLongitudeDegrees() const
{
	return static_cast< double >( longitude - 0x80000000LL ) / 3600000.0 ;
}


double daniel::dns::RR::RData_LOC::GetAltitudeMeters() const
{
	return static_cast< double >(  altitude - 10000000 ) / 100.0 ;
}


double daniel::dns::RR::RData_LOC::GetRealSizeMeters() const
{
	return DecodeCM( size ) / 100.0 ;
}


double daniel::dns::RR::RData_LOC::GetRealHorizPrecMeters() const
{
	return DecodeCM( horiz_prec ) / 100.0 ;
}


double daniel::dns::RR::RData_LOC::GetRealVertiPrecMeters() const
{
	return DecodeCM( verti_prec ) / 100.0 ;
}


int32_t daniel::dns::RR::RData_LOC::GetLatitudeINT() const
{
	return latitude - 0x80000000LL ;
}


int32_t daniel::dns::RR::RData_LOC::GetLongitudeINT() const
{
	return longitude - 0x80000000LL ;
}


int32_t daniel::dns::RR::RData_LOC::GetAltitudeINT() const
{
	return altitude - 10000000 ;
}


uint64_t daniel::dns::RR::RData_LOC::SpreadBits( uint32_t const & value ) const
{
	uint64_t x = value ;

	x = ( x ^ ( x << 16 ) ) & 0x0000FFFF0000FFFFULL ;
	x = ( x ^ ( x <<  8 ) ) & 0x00FF00FF00FF00FFULL ;
	x = ( x ^ ( x <<  4 ) ) & 0x0F0F0F0F0F0F0F0FULL ;
	x = ( x ^ ( x <<  2 ) ) & 0x3333333333333333ULL ;
	x = ( x ^ ( x <<  1 ) ) & 0x5555555555555555ULL ;

   return x ;
}


uint32_t daniel::dns::RR::RData_LOC::CompactBits( uint64_t const value ) const
{
	uint64_t x = value ;

    x = ( x ^ ( x >>  1 ) ) & 0x3333333333333333ULL ;
    x = ( x ^ ( x >>  2 ) ) & 0x0F0F0F0F0F0F0F0FULL ;
    x = ( x ^ ( x >>  4 ) ) & 0x00FF00FF00FF00FFULL ;
    x = ( x ^ ( x >>  8 ) ) & 0x0000FFFF0000FFFFULL ;
    x = ( x ^ ( x >> 16 ) ) & 0x00000000FFFFFFFFULL ;

    return static_cast< uint32_t >( x ) ;
}


uint64_t daniel::dns::RR::RData_LOC::Interleave() const
{
	uint32_t x = static_cast< uint32_t >( GetLatitudeINT()  ) ;
	uint32_t y = static_cast< uint32_t >( GetLongitudeINT() ) ;

	return SpreadBits( x ) | ( SpreadBits( y ) << 1 ) ;
}


uint64_t daniel::dns::RR::RData_LOC::Interleave( uint32_t const & x , uint32_t const & y ) const
{
	return SpreadBits( x ) | ( SpreadBits( y ) << 1 ) ;
}


uint32_t daniel::dns::RR::RData_LOC::DeinterleaveX( uint64_t const & value ) const
{
	uint64_t x = value & 0x5555555555555555ULL ;

	return static_cast< uint32_t >( CompactBits( x ) ) ;
}


uint32_t daniel::dns::RR::RData_LOC::DeinterleaveY( uint64_t const & value ) const
{
	uint64_t x = ( value >> 1 ) & 0x5555555555555555ULL ;

	return static_cast< uint32_t >( CompactBits( x ) ) ;
}