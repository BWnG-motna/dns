#include "net/net.h"


int daniel::net::RequestOnUdp( uint8_t * prBuf , uint16_t const & rbufMaxLen , uint8_t const * psBuf , uint16_t const & sbufLen )
{
	int sockid = socket( AF_INET , SOCK_DGRAM , 0 ) ;
	if( 0 > sockid )
	{
		return 0 ;
	}

	struct sockaddr_in addr ;
	memset( ( char * ) & addr , 0 , sizeof( addr ) ) ;

	addr.sin_family      = AF_INET ;
	addr.sin_addr.s_addr = inet_addr( "8.8.8.8" ) ;
	addr.sin_port        = htons( 53 ) ;

	socklen_t addrlen = sizeof( addr ) ;

	sendto( sockid , psBuf , sbufLen , 0 , ( struct sockaddr * ) & addr , sizeof( addr ) ) ;
	int len = recvfrom( sockid , prBuf , rbufMaxLen , 0 , ( struct sockaddr * ) & addr , ( socklen_t * ) & addrlen ) ;

	close( sockid ) ;

	return len ;
}