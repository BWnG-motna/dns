#include "net/net.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <cstring>

#include <fcntl.h>
#include <errno.h>


int daniel::net::RequestOnTcpV4(
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    )
{
	int sockid = socket( AF_INET , SOCK_STREAM , 0 ) ;
	if( 0 > sockid )
	{
		return 0 ;
	}

	int res = 0 ;

	struct timeval tvRecv ;
	tvRecv.tv_sec  = 5 ;
	tvRecv.tv_usec = 0 ;

	res = setsockopt( sockid , SOL_SOCKET , SO_RCVTIMEO , & tvRecv , sizeof( tvRecv ) ) ;
	if( 0 > res ) 
	{
		close( sockid ) ;
		return -1 ;
	}

	struct sockaddr_in addr ;
	memset( ( char * ) & addr , 0 , sizeof( addr ) ) ;

	addr.sin_family      = AF_INET ;
	addr.sin_addr.s_addr = inet_addr( svrIp ) ;
	addr.sin_port        = htons( svrPort ) ;

	fd_set fds ;
	FD_ZERO( & fds ) ;
	FD_SET ( sockid , & fds ) ;

	int flags = fcntl( sockid , F_GETFL , 0 ) ;
	res = fcntl( sockid , F_SETFL , flags | O_NONBLOCK ) ;
	if( 0 > res )
	{
		close( sockid ) ;
		return -1 ;
	}

	res = connect( sockid , ( sockaddr * ) & addr , sizeof( addr ) ) ;
	if( 0 > res && EINPROGRESS != errno ) 
	{
		close( sockid ) ;
		return -1 ;
	}

	if( 0 > res ) 
	{
		FD_ZERO( & fds ) ;
		FD_SET ( sockid , & fds ) ;

		struct timeval tvConn ;
		tvConn.tv_sec  = 3 ;
		tvConn.tv_usec = 0 ;

		res = select( sockid + 1 , NULL , & fds , NULL , & tvConn ) ;
		if( 0 >= res )
		{
			close( sockid ) ;
			return -1 ;
		}

		int soError = 0 ;
		socklen_t len = sizeof( soError ) ;
		res = getsockopt( sockid , SOL_SOCKET , SO_ERROR , & soError , & len ) ;
		if( 0 > res || 0 != soError )
		{
			close( sockid ) ;
			return -1 ;
		}
	}

	fcntl( sockid , F_SETFL , flags ) ;

	res = send( sockid , psBuf , sbufLen , 0 ) ;
	if( ( ssize_t ) sbufLen > res )
	{
		close( sockid ) ;
		return -1 ;
	}

	uint8_t tmp[ 65535 + 2 ] ;

	ssize_t acclen = 0 ;
	while( 2 > acclen )
	{
		ssize_t len = recv( sockid , & tmp[ acclen ] , sizeof( tmp ) - acclen , 0 ) ;
		
		if( 0 >= len )
		{
			close( sockid ) ;
			return -1 ;
		}

		acclen += len ;
	}

	uint16_t msglen 
		= ( ( tmp[ 0 ] << 8 ) & 0xFF00 ) 
		| ( ( tmp[ 1 ] << 0 ) & 0x00FF ) ;

	if( 0 == msglen || rbufMaxLen < msglen )
	{
		close( sockid ) ;
		return -1 ;
	}

	if( 0 < ( acclen - 2 ) )
	{
		for( ssize_t pos = 0 ; pos < ( acclen - 2 ) ; ++pos )
		{
			prBuf[ pos ] = tmp[ 2 + pos ] ;
		}
	}

	uint16_t recvlen = acclen - 2 ;
	while( recvlen < msglen )
	{
		ssize_t len = recv( sockid , & prBuf[ recvlen ] , rbufMaxLen - recvlen , 0 ) ;

		if( 0 >= len )
		{
			close( sockid ) ;
			return -1 ;
		}

		recvlen += len ;
	}

	close( sockid ) ;

	return recvlen ;
}


int daniel::net::RequestOnUdpV4( 
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    )
{
	int sockid = socket( AF_INET , SOCK_DGRAM , 0 ) ;
	if( 0 > sockid )
	{
		return 0 ;
	}

	int res = 0 ;

	struct timeval tv ;
	tv.tv_sec  = 2 ;
	tv.tv_usec = 0 ;

	res = setsockopt( sockid , SOL_SOCKET , SO_RCVTIMEO , & tv , sizeof( tv ) ) ;
	if( 0 > res ) 
	{
		close( sockid ) ;
		return -1 ;
	}

	struct sockaddr_in addr ;
	memset( ( char * ) & addr , 0 , sizeof( addr ) ) ;

	addr.sin_family      = AF_INET ;
	addr.sin_addr.s_addr = inet_addr( svrIp ) ;
	addr.sin_port        = htons( svrPort ) ;

	socklen_t addrlen = sizeof( addr ) ;

	ssize_t sent = sendto( sockid , psBuf , sbufLen , 0 , ( struct sockaddr * ) & addr , sizeof( addr ) ) ;
	if( sent < 0 )
	{
		close( sockid ) ;
		return -1 ;
	}
	int len = recvfrom( sockid , prBuf , rbufMaxLen , 0 , ( struct sockaddr * ) & addr , ( socklen_t * ) & addrlen ) ;

	close( sockid ) ;

	return len ;
}



int daniel::net::RequestOnTcpV6(
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    )
{
	int sockid = socket( AF_INET6 , SOCK_STREAM , 0 ) ;
	if( 0 > sockid )
	{
		return 0 ;
	}

	int res = 0 ;

	struct timeval tvRecv ;
	tvRecv.tv_sec  = 5 ;
	tvRecv.tv_usec = 0 ;

	res = setsockopt( sockid , SOL_SOCKET , SO_RCVTIMEO , & tvRecv , sizeof( tvRecv ) ) ;
	if( 0 > res ) 
	{
		close( sockid ) ;
		return -1 ;
	}

	struct sockaddr_in6 addr ;
	memset( & addr , 0 , sizeof( struct sockaddr_in6 ) ) ;

	addr.sin6_family   = AF_INET6 ;
	addr.sin6_port     = htons( svrPort ) ;
	addr.sin6_flowinfo = 0 ;
	addr.sin6_scope_id = 0 ;

	if( 0 >= inet_pton( AF_INET6 , svrIp , & addr.sin6_addr ) )
	{
		close( sockid ) ;
		return -1 ;
	}

	fd_set fds ;
	FD_ZERO( & fds ) ;
	FD_SET ( sockid , & fds ) ;

	int flags = fcntl( sockid , F_GETFL , 0 ) ;
	res = fcntl( sockid , F_SETFL , flags | O_NONBLOCK ) ;
	if( 0 > res )
	{
		close( sockid ) ;
		return -1 ;
	}

	res = connect( sockid , ( struct sockaddr * ) & addr , sizeof( struct sockaddr_in6 ) ) ;
	if( 0 > res && EINPROGRESS != errno ) 
	{
		close( sockid ) ;
		return -1 ;
	}

	if( 0 > res ) 
	{
		FD_ZERO( & fds ) ;
		FD_SET ( sockid , & fds ) ;

		struct timeval tvConn ;
		tvConn.tv_sec  = 3 ;
		tvConn.tv_usec = 0 ;

		res = select( sockid + 1 , NULL , & fds , NULL , & tvConn ) ;
		if( 0 >= res )
		{
			close( sockid ) ;
			return -1 ;
		}

		int soError = 0 ;
		socklen_t len = sizeof( soError ) ;
		res = getsockopt( sockid , SOL_SOCKET , SO_ERROR , & soError , & len ) ;
		if( 0 > res || 0 != soError )
		{
			close( sockid ) ;
			return -1 ;
		}
	}

	fcntl( sockid , F_SETFL , flags ) ;

	res = send( sockid , psBuf , sbufLen , 0 ) ;
	if( ( ssize_t ) sbufLen > res )
	{
		close( sockid ) ;
		return -1 ;
	}

	uint8_t tmp[ 65535 + 2 ] ;

	ssize_t acclen = 0 ;
	while( 2 > acclen )
	{
		ssize_t len = recv( sockid , & tmp[ acclen ] , sizeof( tmp ) - acclen , 0 ) ;
		
		if( 0 >= len )
		{
			close( sockid ) ;
			return -1 ;
		}

		acclen += len ;
	}

	uint16_t msglen 
		= ( ( tmp[ 0 ] << 8 ) & 0xFF00 ) 
		| ( ( tmp[ 1 ] << 0 ) & 0x00FF ) ;

	if( 0 == msglen || rbufMaxLen < msglen )
	{
		close( sockid ) ;
		return -1 ;
	}

	if( 0 < ( acclen - 2 ) )
	{
		for( ssize_t pos = 0 ; pos < ( acclen - 2 ) ; ++pos )
		{
			prBuf[ pos ] = tmp[ 2 + pos ] ;
		}
	}

	uint16_t recvlen = acclen - 2 ;
	while( recvlen < msglen )
	{
		ssize_t len = recv( sockid , & prBuf[ recvlen ] , rbufMaxLen - recvlen , 0 ) ;

		if( 0 >= len )
		{
			close( sockid ) ;
			return -1 ;
		}

		recvlen += len ;
	}

	close( sockid ) ;

	return recvlen ;
}



int daniel::net::RequestOnUdpV6( 
	uint8_t       * prBuf , uint16_t const & rbufMaxLen , 
	uint8_t const * psBuf , uint16_t const & sbufLen    ,
	char    const * svrIp , uint16_t const & svrPort    )
{
	int sockid = socket( AF_INET6 , SOCK_DGRAM , 0 ) ;
	if( 0 > sockid )
	{
		return 0 ;
	}

	int res = 0 ;

	struct timeval tv ;
	tv.tv_sec  = 2 ;
	tv.tv_usec = 0 ;

	res = setsockopt( sockid , SOL_SOCKET , SO_RCVTIMEO , & tv , sizeof( tv ) ) ;
	if( 0 > res ) 
	{
		close( sockid ) ;
		return -1 ;
	}

	struct sockaddr_in6 addr ;
	memset( & addr , 0 , sizeof( addr ) ) ;

	addr.sin6_family = AF_INET6 ;
	addr.sin6_port   = htons( svrPort ) ;

	if( 0 >= inet_pton( AF_INET6 , svrIp , & addr.sin6_addr ) )
	{
		close( sockid ) ;
		return -1 ;
	}

	socklen_t addrlen = sizeof( addr ) ;

	ssize_t sent = sendto( sockid , psBuf , sbufLen , 0 , ( struct sockaddr * ) & addr , addrlen ) ;
	if( sent < 0 )
	{
		close( sockid ) ;
		return -1 ;
	}

	int len = recvfrom( sockid , prBuf , rbufMaxLen , 0 , ( struct sockaddr * ) & addr , ( socklen_t * ) & addrlen ) ;

	close( sockid ) ;

	return len ;
}