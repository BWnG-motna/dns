#include "dns/Header.h"


daniel::dns::Header::Header()
	: id( 0 ) , 
	
	  qr( 0 ) , opcode( 0 ) , aa    ( 0 ) , tc( 0 ) , rd( 0 ) ,  // one byte 
	  ra( 0 ) , z     ( 0 ) , rcode ( 0 ) ,                      // one byte

	  qdcount( 0 ) , ancount( 0 ) , nscount( 0 ) , arcount( 0 ) 
{

}


uint16_t daniel::dns::Header::Load( uint8_t const * pBuf , uint16_t const & length )
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}

	if( slen > length )
	{
		return 0 ;
	}

	id      = ( ( pBuf[  0 ] << 8 ) & 0xFF00 )
            | ( ( pBuf[  1 ] << 0 ) & 0x00FF ) ;

    qr      =   ( pBuf[  2 ] >> 7 ) & 0x01 ;

    opcode  =   ( pBuf[  2 ] >> 3 ) & 0x07 ;

    aa      =   ( pBuf[  2 ] >> 2 ) & 0x01 ;

    tc      =   ( pBuf[  2 ] >> 1 ) & 0x01 ;

    rd      =   ( pBuf[  2 ] >> 0 ) & 0x01 ;

    ra      =   ( pBuf[  3 ] >> 7 ) & 0x01 ;

    z       =   ( pBuf[  3 ] >> 6 ) & 0x01 ;

    ad      =   ( pBuf[  3 ] >> 5 ) & 0x01 ;

    cd      =   ( pBuf[  3 ] >> 4 ) & 0x01 ;

    rcode   =   ( pBuf[  3 ] >> 0 ) & 0x0F ;

    qdcount = ( ( pBuf[  4 ] << 8 ) & 0xFF00 )
            | ( ( pBuf[  5 ] << 0 ) & 0x00FF ) ;

    ancount = ( ( pBuf[  6 ] << 8 ) & 0xFF00 )
            | ( ( pBuf[  7 ] << 0 ) & 0x00FF ) ;

    nscount = ( ( pBuf[  8 ] << 8 ) & 0xFF00 )
            | ( ( pBuf[  9 ] << 0 ) & 0x00FF ) ;

    arcount = ( ( pBuf[ 10 ] << 8 ) & 0xFF00 )
            | ( ( pBuf[ 11 ] << 0 ) & 0x00FF ) ;

    return slen ;
}


uint16_t daniel::dns::Header::Save( uint8_t * pBuf , uint16_t const & length ) const
{
	if( 1 > length || nullptr == pBuf )
	{
		return 0 ;
	}
	
	if( slen > length )
	{
		return 0 ;
	}

	pBuf[  0 ] =   ( id      >> 8 ) & 0x00FF ;
	pBuf[  1 ] =   ( id      >> 0 ) & 0x00FF ;

	pBuf[  2 ] = ( ( qr      << 7 ) & 0x80 )
		       | ( ( opcode  << 3 ) & 0x78 )
		       | ( ( aa      << 2 ) & 0x04 )
		       | ( ( tc      << 1 ) & 0x02 )
		       | ( ( rd      << 0 ) & 0x01 ) ;

	pBuf[  3 ] = ( ( ra      << 7 ) & 0x80 )
	           | ( ( z       << 6 ) & 0x40 )
	           | ( ( ad      << 5 ) & 0x20 )
	           | ( ( cd      << 4 ) & 0x10 )
	           | ( ( rcode   << 0 ) & 0x0F ) ;

	pBuf[  4 ] =   ( qdcount >> 8 ) & 0x00FF ;
	pBuf[  5 ] =   ( qdcount >> 0 ) & 0x00FF ;

	pBuf[  6 ] =   ( ancount >> 8 ) & 0x00FF ;
	pBuf[  7 ] =   ( ancount >> 0 ) & 0x00FF ;

	pBuf[  8 ] =   ( nscount >> 8 ) & 0x00FF ;
	pBuf[  9 ] =   ( nscount >> 0 ) & 0x00FF ;

	pBuf[ 10 ] =   ( arcount >> 8 ) & 0x00FF ;
	pBuf[ 11 ] =   ( arcount >> 0 ) & 0x00FF ;

	return slen ;
}


void daniel::dns::Header::SetId( uint16_t const & _id )
{
	id = _id ;
}


void daniel::dns::Header::SetQR( QR const & _qr )
{
	if( QR::Query == _qr )
	{
		qr     = 0 ;
		opcode = 0 ;
		aa     = 0 ;
		tc     = 0 ;
		rd     = 0 ;
		ra     = 0 ;
		z      = 0 ;
		ad     = 0 ;
		cd     = 0 ;
		rcode  = 0 ;
	}
	else
	{
		qr     = 1 ;
	}
}


void daniel::dns::Header::SetOpCode( uint16_t const & opCode )
{
	opcode = opCode ;
}


void daniel::dns::Header::SetRCode ( uint16_t const &  rCode )
{
	rcode = rCode ;
}


void daniel::dns::Header::SetQdCount( uint16_t const & count )
{
	qdcount = count ;
}


void daniel::dns::Header::SetAnCount( uint16_t const & count )
{
	ancount = count ;
}


void daniel::dns::Header::SetNsCount( uint16_t const & count )
{
	nscount = count ;
}


void daniel::dns::Header::SetArCount( uint16_t const & count )
{
	arcount = count ;
}


void daniel::dns::Header::SetAA( bool const & isSet )
{
	aa = ( true == isSet ) ? 1 : 0 ;
}


void daniel::dns::Header::SetTC( bool const & isSet )
{
	tc = ( true == isSet ) ? 1 : 0 ;
}	


void daniel::dns::Header::SetRD( bool const & isSet )
{
	rd = ( true == isSet ) ? 1 : 0 ;
}


void daniel::dns::Header::SetRA( bool const & isSet )
{
	ra = ( true == isSet ) ? 1 : 0 ;
}


void daniel::dns::Header::SetAD( bool const & isSet )
{
	ad = ( true == isSet ) ? 1 : 0 ;
}


void daniel::dns::Header::SetCD( bool const & isSet )
{
	cd = ( true == isSet ) ? 1 : 0 ;
}


uint16_t daniel::dns::Header::GetID() const
{
	return id ;
}


uint16_t daniel::dns::Header::GetQR() const
{
	return qr ;
}


uint16_t daniel::dns::Header::GetOpcode() const
{
	return opcode ;
}


uint16_t daniel::dns::Header::GetAA() const
{
	return aa ;
}


uint16_t daniel::dns::Header::GetTC() const
{
	return tc ;
}


uint16_t daniel::dns::Header::GetRD() const
{
	return rd ;
}


uint16_t daniel::dns::Header::GetRA() const
{
	return ra ;
}


uint16_t daniel::dns::Header::GetZ()  const
{
	return z ;
}


uint16_t daniel::dns::Header::GetAD()  const
{
	return ad ;
}


uint16_t daniel::dns::Header::GetCD()  const
{
	return cd ;
}


uint16_t daniel::dns::Header::GetRCode() const
{
	return rcode ;
}


uint16_t daniel::dns::Header::GetQdCount() const
{
	return qdcount ;
}


uint16_t daniel::dns::Header::GetAnCount() const
{
	return ancount ;
}


uint16_t daniel::dns::Header::GetNsCount() const
{
	return nscount ;
}


uint16_t daniel::dns::Header::GetArCount() const
{
	return arcount ;
}