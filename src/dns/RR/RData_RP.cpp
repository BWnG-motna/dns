#include "dns/RR/RData_RP.h"


#include <string>
#include <memory>


daniel::dns::RR::RData_RP::RData_RP( uint8_t const * pRef )
	: RData( pRef ) , pMboxDName( nullptr ) , pTxtDName( nullptr )
{

}


daniel::dns::RR::RData_RP::~RData_RP()
{
	Initalize() ;
}


void daniel::dns::RR::RData_RP::Initalize()
{
	if( nullptr != pMboxDName )
	{
		delete [] pMboxDName ;
		pMboxDName = nullptr ;
	}

	if( nullptr !=  pTxtDName )
	{
		delete [] pTxtDName ;
		pTxtDName = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_RP::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pMboxDName || nullptr == pTxtDName )
	{
		return 0 ;
	}

	std::string strBox( reinterpret_cast< char const * >( pMboxDName ) ) ;
	std::string strTxt( reinterpret_cast< char const * >(  pTxtDName ) ) ;

	uint16_t mboxlen = static_cast< uint16_t >( strBox.length() ) ;
	uint16_t  txtlen = static_cast< uint16_t >( strTxt.length() ) ;

	uint16_t len = mboxlen + txtlen + 1 ;

	if( length <= len )
	{
		return 0 ;
	}

	uint16_t pos = 0 ;
	for( uint16_t bPos = 0 ; bPos < mboxlen ; ++bPos )
	{
		pStr[ pos++ ] = pMboxDName[ bPos ] ;
	}

	pStr[ pos++ ] = ' ' ;

	for( uint16_t bPos = 0 ; bPos <  txtlen ; ++bPos )
	{
		pStr[ pos++ ] =  pTxtDName[ bPos ] ;
	}

	pStr[ pos ] = '\0' ;

	return pos ;
}


bool daniel::dns::RR::RData_RP::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}


	uint16_t len[ 3 ] = { 0 , 0 , 0 } ;

	len[ 0 ] = SkipDName( pData , length ) ; 
	if( 1 > len[ 0 ] )
	{
		return false ;
	}


	len[ 1 ] = GetDNDataLen( & pData[      0   ] ) ;
	if( 1 > len[ 1 ] )
	{
		return false ;
	}


	len[ 2 ] = GetDNDataLen( & pData[ len[ 0 ] ] ) ;
	if( 1 > len[ 2 ] )
	{
		return false ;
	}

	Initalize() ;

	pMboxDName = new ( std::nothrow ) uint8_t [ len[ 1 ] + 1 ] ;
	 pTxtDName = new ( std::nothrow ) uint8_t [ len[ 2 ] + 1 ] ;

	if( nullptr == pMboxDName || nullptr == pTxtDName )
	{
		Initalize() ;
		return false ;
	}

	len[ 1 ] = GetDNData( pMboxDName , len[ 1 ] + 1 , & pData[        0 ] ) ;
	len[ 2 ] = GetDNData(  pTxtDName , len[ 2 ] + 1 , & pData[ len[ 0 ] ] ) ;

	return true ;
}


uint8_t const * daniel::dns::RR::RData_RP::GetMBoxDName() const
{
	return pMboxDName ;
}


uint8_t const * daniel::dns::RR::RData_RP::GetTxtDName()  const
{
	return pTxtDName ;
}
