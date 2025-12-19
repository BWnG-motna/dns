#include "dns/Question.h"
#include "view/HexView.h"


daniel::dns::Question::Question()
	: qname( "\0" ) , qnameLen( 0 ) , qtype( QType::A ) , qclass( QClass::IN )
{
	qname[ 0 ] = 0 ;
}


bool daniel::dns::Question::SetName( char const * pBuf , uint16_t const & length )
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}

	uint16_t len    = 0 ;
	uint16_t qPos   = 1 ; // qname
	uint16_t bPos   = 0 ; // pBuf
	uint16_t lenPos = 0 ;
	
	for( bPos = 0 ; bPos < ( length + 1 ) && bPos < qnameMaxLen ; ++bPos )
	{
		if( '.' == pBuf[ bPos ] )
		{
			if( 63 < len )
			{
				qnameLen = 0 ;
				return false ;
			}

			qname[ lenPos ] = len ;
			lenPos = qPos ;
			len = 0 ;
			++qPos ;
		}
		else
		{
			if( 255 <= qPos )
			{
				qnameLen = 0 ;
				return false ;
			}
			qname[ qPos++ ] = pBuf[ bPos ] ;
			len = ( '\0' != pBuf[ bPos ] ) ? len + 1 : len ;
		}
	}

	if( 63 < len )
	{
		qnameLen = 0 ;
		return false ;
	}

	qname[ lenPos ] = len ;
	qnameLen = qPos ;

	return true ;
}


void daniel::dns::Question::SetType( QType const & _qtype )
{
	qtype = _qtype ;
}


void daniel::dns::Question::SetClass( QClass const & _qclass )
{
	qclass = _qclass ;
}


uint16_t daniel::dns::Question::Load( uint8_t const * pBuf , uint16_t const & length )
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}


	int32_t nullPos = -1 ;
	for( uint16_t pos = 0 ; pos < length ; ++pos , ++nullPos )
	{
		if( '\0' == pBuf[ pos ] )
		{
			nullPos = pos ;
			break ;
		}
	}

	if( -1 == nullPos )
	{
		return 0 ;
	}

	if( ( nullPos + 4 ) >= length || 256 < nullPos )
	{
		return 0 ;
	}

	for( uint16_t pos = 0 ; pos < nullPos + 1 ; ++pos )
	{
		qname[ pos ] = pBuf[ pos ] ;
	}

	uint16_t qtypeValue
		= ( ( pBuf[ nullPos + 1 ] << 8 ) & 0xFF00 )
	    | ( ( pBuf[ nullPos + 2 ] << 0 ) & 0x00FF ) ;

	uint16_t qclassValue
		= ( ( pBuf[ nullPos + 3 ] << 8 ) & 0xFF00 )
	    | ( ( pBuf[ nullPos + 4 ] << 0 ) & 0x00FF ) ;

	qtype  = daniel::enumFromUint16< QType  >(  qtypeValue ) ;
	qclass = daniel::enumFromUint16< QClass >( qclassValue ) ; 

	return nullPos + 5 ;
}


uint16_t daniel::dns::Question::Save( uint8_t * pBuf , uint16_t const & length )
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}


	bool     hasNull = false ;
	uint16_t nullPos = 0 ;
	
	for( uint16_t pos = 0 ; pos < qnameMaxLen + 1 ; ++pos , ++nullPos )
	{
		if( '\0' == qname[ pos ] )
		{
			hasNull = true ;
			nullPos = pos ;
			break ;
		}
	}

	if( false == hasNull )
	{
		return 0 ;
	}

	if( nullPos + 4 > length )
	{
		return 0 ;
	}

	for( uint16_t pos = 0 ; pos < nullPos + 1 ; ++pos )
	{
		pBuf[ pos ] = qname[ pos ] ;
	}

	pBuf[ nullPos + 1 ] = ( daniel::underlying( qtype  ) >> 8 ) & 0x00FF ;
	pBuf[ nullPos + 2 ] = ( daniel::underlying( qtype  ) >> 0 ) & 0x00FF ;

	pBuf[ nullPos + 3 ] = ( daniel::underlying( qclass ) >> 8 ) & 0x00FF ;
	pBuf[ nullPos + 4 ] = ( daniel::underlying( qclass ) >> 0 ) & 0x00FF ;

	return nullPos + 5 ;
}


bool daniel::dns::Question::GetName( uint8_t * pBuf , uint16_t const & length ) const
{
	if( 1 > length || nullptr == pBuf )
	{
		return false ;
	}

	
	if( 1 > qnameLen )
	{
		pBuf[ 0 ] = '\0' ;
		return true ;
	}

	uint16_t qPos = 0 ;
	uint16_t bPos = 0 ;

	while( '\0' != qname[ qPos ] && qPos < qnameLen )
	{
		uint8_t len = qname[ qPos++ ] ;

		for( uint8_t lPos = 0 ; lPos < len ; ++lPos )
		{
			if( bPos >= length - 1 )
			{
				return false ;
			}

			pBuf[ bPos++ ] = qname[ qPos++ ] ;
		}

		if( bPos >= length )
		{
			return false ;
		}

		if( '\0' != qname[ qPos ] )
		{
			pBuf[ bPos++ ] = '.' ;
		} 
	}

	pBuf[ bPos ] = '\0' ;

	return true ;
}


daniel::dns::QType daniel::dns::Question::GetType() const
{
	return qtype ;
}


daniel::dns::QClass daniel::dns::Question::GetClass() const
{
	return qclass ;
}