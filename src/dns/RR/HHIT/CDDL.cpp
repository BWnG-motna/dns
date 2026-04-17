#include "dns/RR/HHIT/CDDL.h"
#include "dns/RR/HHIT/COBLHeader.h"


#include <memory>


daniel::dns::RR::HHIT::CDDL::CDDL()
	: type( EntityType::NotDefined ) , pAbb( nullptr ) , pCert( nullptr )
{

}


daniel::dns::RR::HHIT::CDDL::~CDDL()
{
	Initialize() ;
}


void daniel::dns::RR::HHIT::CDDL::Initialize()
{
	if( nullptr != pAbb )
	{
		delete [] pAbb ;
		pAbb = nullptr ;
	}

	if( nullptr != pCert )
	{
		delete [] pCert ;
		pCert = nullptr ;
	}

	certlen = 0 ;
	type    = EntityType::NotDefined ;
}


bool daniel::dns::RR::HHIT::CDDL::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}


	Initialize() ;

	//
	// type -------------------------- major type 0 / uint
	//

	COBLHeader header ;
	header.Load( & pData[ 0 ] , length ) ;

	if( true == header.IsError() || 0 != header.GetMajorType() )  // uint's major type must be 0
	{
		return false ;
	}

	uint32_t dat = header.GetData() ;
	if( true == IsValidEntityType( static_cast< uint8_t >( dat ) ) )
	{
		type = enumFromUint8< EntityType >( dat ) ;
	}
	else
	{
		type = EntityType::NotDefined ;
	}

	uint8_t skip = 1 + header.GetExtraBytes() ;


	//
	// Abb  -------------------------- major type 3 / text-string
	//

	if( skip + 1 > length )
	{
		Initialize() ;
		return false ;
	}

	header.Load( & pData[ skip ] , length - skip ) ;
	if( true == header.IsError() || 3 != header.GetMajorType() )
	{
		Initialize() ;
		return false ;
	}

	dat = header.GetData() ;
	uint8_t len = static_cast< uint8_t >( dat ) ;
	if( ( 15 < len ) || ( length < ( skip + len ) ) )
	{
		Initialize() ;
		return false ;
	}

	skip = skip + 1 + header.GetExtraBytes() ;

	pAbb = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	for( uint8_t pos = 0 ; pos < len ; ++pos )
	{
		pAbb[ pos ] = pData[ skip + pos ] ;
	}

	pAbb[ len ] = '\0' ;


	//
	// Cert  -------------------------- major type 2 / binary
	//

	skip = skip + len ;
	header.Load( & pData[ skip ] , length - skip ) ;

	if( true == header.IsError() || 2 != header.GetMajorType() )
	{
		Initialize() ;
		return false ;
	}

	dat = header.GetData() ;

	if( ( skip + 1 + header.GetExtraBytes() + dat ) != length )
	{
		Initialize() ;
		return false ;
	}

	pCert = new ( std::nothrow ) uint8_t [ dat ] ;
	if( nullptr == pCert )
	{
		Initialize() ;
		return false ;
	}

	for( uint16_t pos = 0 ; pos < dat ; ++pos )
	{
		pCert[ pos ] = pData[ skip + 1 + header.GetExtraBytes() + pos ] ;
	}

	certlen = dat ;

	return true ;
}


daniel::dns::RR::HHIT::EntityType daniel::dns::RR::HHIT::CDDL::GetType() const
{
	return type ;
}


uint16_t daniel::dns::RR::HHIT::CDDL::GetCertLen() const
{
	return certlen ;
}


uint8_t const * daniel::dns::RR::HHIT::CDDL::GetAbb() const
{
	return pAbb ;
}


uint8_t const * daniel::dns::RR::HHIT::CDDL::GetCert() const
{
	return pCert ;
}


void daniel::dns::RR::HHIT::CDDL::SetType( EntityType const & _type ) 
{
	type = _type ;
}


void daniel::dns::RR::HHIT::CDDL::SetAbb( uint8_t const * _pAbb , uint16_t const & len )
{
	if( nullptr != pAbb )
	{
		delete [] pAbb ;
		pAbb = nullptr ;
	}

	pAbb = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pAbb )
	{
		return ;
	}

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pAbb[ pos ] = _pAbb[ pos ] ;
	}

	pAbb[ len ] = '\0' ;
}


void daniel::dns::RR::HHIT::CDDL::SetCert( uint8_t const * _pCert , uint16_t const & len )
{
	if( nullptr != pCert )
	{
		delete [] pCert ;
		pCert = nullptr ;
	}

	pCert = new ( std::nothrow ) uint8_t [ len ] ;
	if( nullptr == pCert )
	{
		return ;
	}

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pCert[ pos ] = _pCert[ pos ] ;
	}

	certlen = len ;
}