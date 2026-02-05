#include "dns/RR/RData_HINFO.h"


#include <string>
#include <memory>


daniel::dns::RR::RData_HINFO::RData_HINFO( uint8_t const * pRef )
	: RData( pRef ) , pCPU( nullptr ) , pOS( nullptr )
{

}


daniel::dns::RR::RData_HINFO::~RData_HINFO()
{
	Initalize() ;
}


void daniel::dns::RR::RData_HINFO::Initalize()
{
	if( nullptr != pCPU )
	{
		delete [] pCPU ;
		pCPU = nullptr ;
	}

	if( nullptr != pOS )
	{
		delete [] pOS ;
		pOS = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_HINFO::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pCPU || nullptr == pOS )
	{
		return 0 ;
	}

	std::string cpuStr( reinterpret_cast< char const * >( pCPU ) ) ;
	std::string  osStr( reinterpret_cast< char const * >( pOS  ) ) ;

	uint16_t cpulen = static_cast< uint16_t >( cpuStr.length() ) ;
	uint16_t  oslen = static_cast< uint16_t >(  osStr.length() ) ;
	uint16_t    len = cpulen + oslen + 1 ;

	if( length <= len )
	{
		return 0 ;
	}

	uint16_t pos = 0 ;
	for( uint16_t bPos = 0 ; bPos < cpulen ; ++bPos )
	{
		pStr[ pos++ ] = pCPU[ bPos ] ;
	}

	pStr[ pos++ ] = ' ' ;

	for( uint16_t bPos = 0 ; bPos <  oslen ; ++bPos )
	{
		pStr[ pos++ ] =  pOS[ bPos ] ;
	}

	pStr[ pos ] = '\0' ;

	return pos ;
}


bool daniel::dns::RR::RData_HINFO::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	bool isExisted = false ;
	uint16_t sPos = 0 ;
	for( sPos = 0 ; sPos < length ; ++sPos )
	{
		if( true == static_cast< bool >( std::isspace( pData[ sPos ] ) ) )
		{
			isExisted = true ;
			break ;
		}
	}

	if( false == isExisted || ( true == isExisted && sPos == ( length - 1 ) ) )
	{
		return false ;
	}

	Initalize() ;

	pCPU = new ( std::nothrow ) uint8_t [ sPos ] ;
	pOS  = new ( std::nothrow ) uint8_t [ length - sPos + 1 ] ;
	if( nullptr == pCPU || nullptr == pOS )
	{
		Initalize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < sPos ; ++pos )
	{
		pCPU[ pos ] = pData[ pos ] ;
	}

	pCPU[ sPos ] = '\0' ;

	for( uint16_t pos = 0 ; pos < ( length - sPos ) ; ++pos )
	{
		pOS[ pos ] = pData[ sPos + 1 + pos ] ;
	}

	pOS[ length - sPos + 1 ] = '\0' ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_HINFO::GetCPUInfo() const
{
	return pCPU ;
}


uint8_t const * daniel::dns::RR::RData_HINFO::GetOSInfo() const
{
	return pOS ;
}