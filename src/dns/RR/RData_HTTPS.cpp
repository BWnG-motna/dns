#include "dns/RR/RData_HTTPS.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_HTTPS::RData_HTTPS( uint8_t const * pRef ) 
	: RData( pRef ) , priority( 0 ) , pTargetName( nullptr ) , pParam( nullptr )
{

}


daniel::dns::RR::RData_HTTPS::~RData_HTTPS() 
{
	Initalize() ;
}


void daniel::dns::RR::RData_HTTPS::Initalize()
{
	if( nullptr != pTargetName )
	{
		delete [] pTargetName ;
		pTargetName = nullptr ;
	}

	if( nullptr != pParam )
	{
		delete pParam ;
		pParam = nullptr ;
	}

	priority = 0 ;
}


uint16_t daniel::dns::RR::RData_HTTPS::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pTargetName )
	{
		return 0 ;
	}


	std::stringstream ss ;
	ss << priority   << '\t' 
	   << reinterpret_cast< char const * >( pTargetName ) ;

	if( nullptr != pParam && 0 < pParam->GetCount() )
	{
		ds::LinkedList< SVC::SvcParam >::const_iterator posIter = pParam->begin() ;
		ds::LinkedList< SVC::SvcParam >::const_iterator endIter = pParam->end() ;

		while( posIter != endIter )
		{
			SVC::SvcParam const & p = *posIter ;
			ss << '\t' << p.ToStr() ;

			++posIter ; 
		}
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



bool daniel::dns::RR::RData_HTTPS::Load( uint8_t const * pData , uint16_t const & length )
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

	priority
		= ( ( pData[ 0 ] << 8 ) & 0xFF00 )
		| ( ( pData[ 1 ] << 0 ) & 0x00FF ) ;


	uint16_t dnlen = 0 ;
	uint16_t spent = 0 ;

	if( 0 == pData[ 2 ] ) // if '.' case
	{
		pTargetName = new ( std::nothrow ) uint8_t [ 2 ] ;
		if( nullptr == pTargetName )
		{
			Initalize() ;
			return false ;
		}

		pTargetName[ 0 ] = '.' ;
		pTargetName[ 1 ] = '\0' ;
		dnlen = 1 ;
		spent = 1 ;

	}
	else
	{
		dnlen = GetDNDataLen( & ( pData[ 2 ] ) ) ;

		pTargetName = new ( std::nothrow ) uint8_t [ dnlen + 1 ] ;
		if( nullptr == pTargetName )
		{
			Initalize() ;
			return false ;
		}

		dnlen = GetDNData( pTargetName , dnlen + 1 , & ( pData[ 2 ] ) ) ;
		spent = SkipDName( & ( pData[ 2 ] ) , length - 2 ) ;
	}

	if( 1 > dnlen )
	{
		Initalize() ;
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
		Initalize() ;
		return false ;
	}
	else if( svcParamBegin > length )
	{
		Initalize() ;
		return false ;
	}

	uint16_t pos     = svcParamBegin ;
	uint16_t prevKey = 0 ;

	bool isBegin = true ;

	while( pos < length && ( pos + 4 ) <= length )
	{
		uint16_t key
			= ( ( pData[ pos + 0 ] << 8 ) & 0xFF00 )
			| ( ( pData[ pos + 1 ] << 0 ) & 0x00FF ) ;

		uint16_t len
			= ( ( pData[ pos + 2 ] << 8 ) & 0xFF00 )
			| ( ( pData[ pos + 3 ] << 0 ) & 0x00FF ) ;

		if( false == SVC::IsValidSvcKey( key ) )
		{
			Initalize() ;
			return false ;
		}

		if( false == isBegin && prevKey >= key )
		{
			Initalize() ;
			return false ;
		}

		if( ( pos + 4 + len ) > length ) 
		{
			Initalize() ;
			return false ;
		}

		if( nullptr == pParam )
		{
			pParam = new ( std::nothrow ) ds::LinkedList< SVC::SvcParam >() ;
			if( nullptr == pParam )
			{
				Initalize() ;
				return false ;
			}
		}

		SVC::SvcParam * p = new ( std::nothrow ) SVC::SvcParam() ;
		if( nullptr == p )
		{
			Initalize() ;
			return false ;
		}

		p->SetKey( key ) ;
		p->SetValue( & ( pData[ pos + 4 ] ) , len ) ;

		if( false == p->IsSet() )
		{
			Initalize() ;
			return false ;
		}

		pParam->Insert( p ) ;

		pos += 4 + len ;
		prevKey = key ;

		isBegin = false ;
	}

	if( length != pos )
	{
		Initalize() ;
		return false ;
	}

	return true ;
}



bool daniel::dns::RR::RData_HTTPS::IsAliasMode() const
{
	return ( 0 == priority ) ? true : false ;
}


uint32_t daniel::dns::RR::RData_HTTPS::GetParamCount() const
{
	if( nullptr == pParam )
	{
		return 0 ;
	}

	return pParam->GetCount() ;
}


uint16_t daniel::dns::RR::RData_HTTPS::GetPriority() const
{
	return priority ;
}


uint8_t const * daniel::dns::RR::RData_HTTPS::GetTargetname() const
{
	return pTargetName ;
}