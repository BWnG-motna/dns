#include "dns/RR/RData_MINFO.h"


#include <string>
#include <memory>


daniel::dns::RR::RData_MINFO::RData_MINFO( uint8_t const * pRef )
	: RData( pRef ) , pRmailbx( nullptr ) , pEmailbx( nullptr )
{

}


daniel::dns::RR::RData_MINFO::~RData_MINFO()
{
	Initalize() ;
}


void daniel::dns::RR::RData_MINFO::Initalize()
{
	if( nullptr != pRmailbx )
	{
		delete [] pRmailbx ;
		pRmailbx = nullptr ; 
	}

	if( nullptr != pEmailbx )
	{
		pEmailbx = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_MINFO::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pRmailbx || nullptr == pEmailbx )
	{
		return 0 ;
	}

	std::string strRmailbx( reinterpret_cast< char const * >( pRmailbx ) ) ;
	std::string strEmailbx( reinterpret_cast< char const * >( pEmailbx ) ) ;

	uint16_t rmbxlen = static_cast< uint16_t >( strRmailbx.length() ) ;
	uint16_t embxlen = static_cast< uint16_t >( strEmailbx.length() ) ;
	uint16_t len     = rmbxlen + embxlen + 1 ;

	if( length <= len )
	{
		return 0 ;
	}

	uint16_t pos = 0 ;
	for( uint16_t bPos = 0 ; bPos < rmbxlen ; ++bPos )
	{
		pStr[ pos++ ] = pRmailbx[ bPos ] ;
	}

	pStr[ pos++ ] = ' ' ;

	for( uint16_t bPos = 0 ; bPos < embxlen ; ++bPos )
	{
		pStr[ pos++ ] = pEmailbx[ bPos ] ;
	}

	pStr[ pos ] = '\0' ;

	return pos ;
}


bool daniel::dns::RR::RData_MINFO::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	uint16_t len[ 3 ] = { 0 , 0 , 0 } ;

	len[ 0 ] = SkipDName( pData , length ) ; 
	if( 1 > len [ 0 ] )
	{
		return false ;
	}

	len[ 1 ] = GetDNDataLen( & pData[      0 ]   ) ;
	len[ 2 ] = GetDNDataLen( & pData[ len[ 0 ] ] ) ;
	if( 1 > len[ 1 ] || 1 > len[ 2 ] )
	{
		return false ;
	}

	Initalize() ;

	pRmailbx = new ( std::nothrow ) uint8_t [ len[ 1 ] + 1 ] ;
	pEmailbx = new ( std::nothrow ) uint8_t [ len[ 2 ] + 1 ] ;
	
	if( nullptr == pRmailbx || nullptr == pEmailbx )
	{
		Initalize() ;
		return false ;
	}

	len[ 1 ] = GetDNData( pRmailbx , len[ 1 ] + 1 , & pData[        0 ] ) ;
	len[ 2 ] = GetDNData( pEmailbx , len[ 2 ] + 1 , & pData[ len[ 0 ] ] ) ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_MINFO::GetRMailBx() const
{
	return pRmailbx ;
}


uint8_t const * daniel::dns::RR::RData_MINFO::GetEMailBx() const
{
	return pEmailbx ;
}