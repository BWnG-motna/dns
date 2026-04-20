#include "dns/RR/CLA/Label.h"


#include <sstream>
#include <string>
#include <memory>


daniel::dns::RR::CLA::Label::Label()
	: pProtocol( nullptr ) , pIpVer( nullptr ) , pBpVer( nullptr ) , pRs( nullptr )
{

}


daniel::dns::RR::CLA::Label::~Label()
{
	Initialize() ;
}


void daniel::dns::RR::CLA::Label::Initialize()
{
	if( nullptr != pProtocol )
	{
		delete [] pProtocol ;
		pProtocol = nullptr ;
	}

	if( nullptr != pIpVer )
	{
		delete [] pIpVer ;
		pIpVer = nullptr ;
	}

	if( nullptr != pBpVer )
	{
		delete [] pBpVer ;
		pBpVer = nullptr ;
	}

	if( nullptr != pRs )
	{
		delete [] pRs ;
		pRs = nullptr ;
	}
}


bool daniel::dns::RR::CLA::Label::Load( uint8_t const * pStr , uint16_t const & length )
{
	if( nullptr == pStr || 1 > length )
	{
		return false ;
	}

	uint16_t spos = 0 ;
	uint16_t epos = 0 ;
	uint8_t  step = 1 ;

	uint8_t * p = nullptr ;

	while( epos <= length && step < 4 )
	{
		if( '-' != pStr[ epos ] && epos != length )
		{
			++epos ;
			continue ;
		}

		p = new ( std::nothrow ) uint8_t [ epos - spos + 1 ] ;
		if( nullptr == p )
		{
			Initialize() ;
			return false ;
		}

		uint16_t bPos = 0 ;
		for( uint16_t pos = spos ; pos < epos ; ++pos )
		{
			p[ bPos++ ] = pStr[ pos ] ;
		}

		p[ epos - spos ] = '\0' ;

		/**/ if( 1 == step )
		{
			pProtocol = p ;
		}
		else if( 2 == step )
		{
			pIpVer = p ;
		}
		else if( 3 == step )
		{
			pBpVer = p ;
		}
		else
		{
			// UNKOWN error
		}

		spos = epos + 1 ;
		epos = epos + 1 ;

		++step ;
	}

	return true ;
}



bool daniel::dns::RR::CLA::Label::SetProtocol( uint8_t const * pStr , uint16_t const & len )
{
	if( nullptr == pStr || 1 > len )
	{
		return false ;
	}

	if( nullptr != pProtocol )
	{
		delete [] pProtocol ;
		pProtocol = nullptr ;
	}

	pProtocol = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pProtocol )
	{
		return false ;
	}

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pProtocol[ pos ] = pStr[ pos ] ;
	}

	pProtocol[ len ] = '\0' ;

	return true ;
}


bool daniel::dns::RR::CLA::Label::SetIpVer( uint8_t const * pStr , uint16_t const & len )
{
	if( nullptr == pStr || 1 > len )
	{
		return false ;
	}

	if( nullptr != pIpVer )
	{
		delete [] pIpVer ;
		pIpVer = nullptr ;
	}

	pIpVer = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pIpVer )
	{
		return false ;
	}

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pIpVer[ pos ] = pStr[ pos ] ;
	}

	pIpVer[ len ] = '\0' ;

	return true ;
}


bool daniel::dns::RR::CLA::Label::SetBpVer( uint8_t const * pStr , uint16_t const & len )
{
	if( nullptr == pStr || 1 > len )
	{
		return false ;
	}

	if( nullptr != pBpVer )
	{
		delete [] pBpVer ;
		pBpVer = nullptr ;
	}

	pBpVer = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pBpVer )
	{
		return false ;
	}

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pBpVer[ pos ] = pStr[ pos ] ;
	}

	pBpVer[ len ] = '\0' ;

	return true ;
}


uint8_t const * daniel::dns::RR::CLA::Label::GetProtocol() const
{
	return pProtocol ;
}


uint8_t const * daniel::dns::RR::CLA::Label::GetIpVer() const
{
	return pIpVer ;
}


uint8_t const * daniel::dns::RR::CLA::Label::GetBpVer() const
{
	return pBpVer ;
}


uint8_t const * daniel::dns::RR::CLA::Label::GetLabel() const
{
	if( nullptr == pProtocol || nullptr == pIpVer || nullptr == pBpVer )
	{
		return nullptr ;
	}

	std::stringstream ss ;

	ss << reinterpret_cast< char const * >( pProtocol ) << "-" 
	   << reinterpret_cast< char const * >( pIpVer    ) << "-" 
	   << reinterpret_cast< char const * >( pBpVer    ) ;

	std::string str = ss.str() ;
	uint16_t len = static_cast< uint16_t >( str.length() ) ;

	if( nullptr != pRs )
	{
		delete [] pRs ;
		pRs = nullptr ;
	}

	pRs = new ( std::nothrow ) uint8_t [ len + 1 ] ;
	if( nullptr == pRs )
	{
		return nullptr ;
	}

	for( uint16_t pos = 0 ; pos < len ; ++pos )
	{
		pRs[ pos ] = str[ pos ] ;
	}

	pRs[ len ] = '\0' ;

	return pRs ;
}