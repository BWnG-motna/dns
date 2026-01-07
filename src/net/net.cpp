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


int daniel::net::RequestOnTcp(
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
	tvRecv.tv_sec  = 2 ;
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

	int len = recv( sockid , prBuf , rbufMaxLen , 0 ) ;
	close( sockid ) ;

	return ( 0 <= len ) ? len : -1 ;
}


int daniel::net::RequestOnUdp( 
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

	sendto( sockid , psBuf , sbufLen , 0 , ( struct sockaddr * ) & addr , sizeof( addr ) ) ;
	int len = recvfrom( sockid , prBuf , rbufMaxLen , 0 , ( struct sockaddr * ) & addr , ( socklen_t * ) & addrlen ) ;

	close( sockid ) ;

	return len ;
}