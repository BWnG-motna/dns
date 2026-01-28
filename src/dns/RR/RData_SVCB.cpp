#include "dns/RR/RData_SVCB.h"


#include <sstream>


daniel::dns::RR::RData_SVCB::RData_SVCB( uint8_t const * pRef ) 
	: RData( pRef ) , priority( 0 ) , paramCount( 0 )
{
	targetName[ 0 ] = '\0' ;
}


uint16_t daniel::dns::RR::RData_SVCB::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	std::stringstream ss ;
	ss << priority   << '\t' 
	   << targetName ;

	for( uint16_t pos = 0 ; pos < paramCount ; ++pos )
	{
		ss << '\t' ;
		ss << param[ pos ].ToStr() ;
	}

	std::string s = ss.str() ;
	uint16_t len  = static_cast< uint16_t >( s.length() ) ;

	for( uint16_t pos = 0 ; pos < length && pos < len ; ++pos )
	{
		pStr[ pos ] = s[ pos ] ;
	}

	uint16_t less = len < length ? len : length ;
	pStr[ less ] = '\0' ;

	return 0 ;
}



bool daniel::dns::RR::RData_SVCB::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	if( 3 > length )
	{
		return false ;
	}

	priority
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;


	uint16_t dnlen = 0 ;
	uint16_t spent = 0 ;
	if( 0 == pData[ 2 ] ) // if '.' case
	{
		targetName[ 0 ] = '.' ;
		targetName[ 1 ] = '\0' ;
		dnlen = 1 ;
		spent = 1 ;

	}
	else
	{
		dnlen = GetDNData( targetName , targetMaxLen , & ( pData[ 2 ] ) ) ;
		spent = SkipDName( & ( pData[ 2 ] ) , length - 2 ) ;
	}

	if( 1 > dnlen )
	{
		return false ;
	}

	// from here, svcParam - pData[ 2 + spent ]
	uint16_t const svcParamBegin = 2 + spent ;

	if( 0 == priority && svcParamBegin == length )
	{
		// svcParam is none
		return true ;
	}
	else if( 0 == priority && svcParamBegin != length )
	{
		return false ;
	}
	else if( svcParamBegin > length )
	{
		return false ;
	}

	uint16_t pos        = svcParamBegin ;
	uint16_t paramPos   = 0 ;
	
	paramCount = 0 ;

	uint16_t prevKey = 0 ;

	while( pos < length && ( pos + 4 ) <= length && paramPos < paramMaxCount )
	{
		uint16_t key
			= ( ( pData[ pos + 0 ] << 8 ) & 0xFF00 )
			| ( ( pData[ pos + 1 ] << 0 ) & 0x00FF ) ;

		uint16_t len
			= ( ( pData[ pos + 2 ] << 8 ) & 0xFF00 )
			| ( ( pData[ pos + 3 ] << 0 ) & 0x00FF ) ;

		if( false == IsValidSvcKey( key ) )
		{
			return false ;
		}

		if( 0 != paramPos && prevKey >= key )
		{
			return false ;
		}

		if( ( pos + 4 + len ) > length ) 
		{
			return false ;
		}

		param[ paramPos ].SetKey( key ) ;
		param[ paramPos ].SetValue( & ( pData[ pos + 4 ] ) , len ) ;

		if( false == param[ paramPos ].IsSet() )
		{
			return false ;
		}

		pos += 4 + len ;
		++paramPos   ;
		++paramCount ;

		prevKey = key ;
	}

	if( length != pos )
	{
		return false ;
	}

	return true ;
}



bool daniel::dns::RR::RData_SVCB::IsAliasMode() const
{
	return ( 0 == priority ) ? true : false ;
}


uint16_t daniel::dns::RR::RData_SVCB::GetParamCount() const
{
	return paramCount ;
}


uint16_t daniel::dns::RR::RData_SVCB::GetPriority() const
{
	return priority ;
}


uint8_t const * daniel::dns::RR::RData_SVCB::GetTargetname() const
{
	return targetName ;
}