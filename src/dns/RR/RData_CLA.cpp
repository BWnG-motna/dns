#include "dns/RR/RData_CLA.h"


#include <sstream>
#include <memory>


daniel::dns::RR::RData_CLA::RData_CLA()
	: RData( nullptr ) , pLabelList( nullptr )
{

}


daniel::dns::RR::RData_CLA::~RData_CLA()
{
	Initialize() ;
}


void daniel::dns::RR::RData_CLA::Initialize()
{
	if( nullptr != pLabelList )
	{
		delete pLabelList ;
		pLabelList = nullptr ;
	}
}


uint16_t daniel::dns::RR::RData_CLA::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	if( nullptr == pLabelList )
	{
		return 0 ;
	}

	ds::LinkedList< CLA::Label >::const_iterator posIter = pLabelList->begin() ;
	ds::LinkedList< CLA::Label >::const_iterator endIter = pLabelList->end() ;

	std::stringstream ss ;

	while( posIter != endIter )
	{
		CLA::Label const & label = *posIter ;

		if( pLabelList->cbegin() != posIter )
		{
			ss << " " ;
		}
		ss << label.GetLabel() ;

		++posIter ;
	}

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


bool daniel::dns::RR::RData_CLA::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}

	Initialize() ;

	uint16_t pos = 0 ;

	while( pos < length )
	{
		uint8_t len = pData[ pos++ ] ;

		CLA::Label * pLabel = new ( std::nothrow ) CLA::Label() ;
		if( nullptr == pLabel )
		{
			Initialize() ;
			return false ;
		}

		bool is = pLabel->Load( & pData[ pos ] , len ) ;
		if( false == is )
		{
			delete pLabel ;

			Initialize() ;
			return false ;
		}

		if( nullptr == pLabelList )
		{
			pLabelList = new ( std::nothrow ) ds::LinkedList< CLA::Label >() ;
			if( nullptr == pLabelList )
			{
				delete pLabel ;

				Initialize() ;
				return false ;
			}
		}

		pLabelList->Insert( pLabel ) ;

		pos = pos + len ;
	}

	return true ;
}