#include "dns/RR/RData_WKS.h"


#include <sstream>
#include <unordered_map>
#include <string>


daniel::dns::RR::RData_WKS::RData_WKS()
	: RData( nullptr ) , address( 0 ) , protocol( 0 ) , pPorts( nullptr )
{

}


daniel::dns::RR::RData_WKS::~RData_WKS()
{
	Initialize() ;
}


char const * daniel::dns::RR::RData_WKS::GetServiceName( uint16_t const & port ) const
{
	static const std::unordered_map< uint16_t, std::string > serviceMap = 
	{
		{   1 , "tcpmux"          } , {   7 , "echo"            } , {   9 , "discard"         } , {  11 , "active"          } , {  13 , "daytime"         } ,
		{  17 , "qotd"            } , {  18 , "message send"    } , {  19 , "chargen"         } , {  20 , "ftp-data"        } , {  21 , "ftp"             } ,
        {  22 , "ssh"             } , {  23 , "telnet"          } , {  24 , "lmtp"            } , {  25 , "smtp"            } , {  37 , "time"            } ,
        {  43 , "whois"           } , {  49 , "tacacs"          } , {  53 , "dns"             } , {  67 , "dhcp/bootp"      } , {  68 , "dhcp/bootp"      } ,
        {  70 , "gopher"          } , {  71 , "netrjs"          } , {  72 , "netrjs"          } , {  73 , "netrjs"          } , {  74 , "netrjs"          } ,
        {  80 , "http"            } , {  88 , "kerberos"        } , {  95 , "supdup"          } , { 101 , "nic"             } , { 102 , "tsap"            } ,
        { 104 , "dicom"           } , { 105 , "ccso ns"         } , { 107 , "rtelnet"         } , { 108 , "sna"             } , { 109 , "pop2"            } ,
        { 110 , "pop3"            } , { 111 , "onc rpc"         } , { 112 , "mcidas"          } , { 113 , "auth"            } , { 115 , "sftp"            } ,
        { 117 , "uucp"            } , { 118 , "sql"             } , { 119 , "nntp"            } , { 123 , "ntp"             } , { 126 , "unisys"          } ,
        { 135 , "dce/ms ep"       } , { 137 , "netbios"         } , { 138 , "netbios"         } , { 139 , "netbios"         } , { 143 , "imap"            } ,
        { 152 , "bftp"            } , { 156 , "sql"             } , { 161 , "snmp"            } , { 162 , "snmp"            } , { 170 , "postscript"      } ,
        { 175 , "vmnet"           } , { 179 , "bgp"             } , { 194 , "irc"             } , { 199 , "smux"            } , { 201 , "appletalk"       } ,
        { 210 , "ansi z39.50"     } , { 213 , "ipx"             } , { 218 , "mpp"             } , { 220 , "imapv3"          } , { 259 , "esro"            } ,
        { 262 , "arcisdms"        } , { 264 , "bgmp"            } , { 280 , "http-mgmt"       } , { 308 , "novastor"        } , { 311 , "macOS server"    } ,
        { 318 , "pkix tsp"        } , { 319 , "ptp event"       } , { 320 , "ptp msg"         } , { 350 , "matip a"         } , { 351 , "matip b"         } ,
        { 356 , "cloanto-net-1"   } , { 366 , "odmr"            } , { 369 , "rpc2portmap"     } , { 370 , "codaauth2"       } , { 376 , "aenip"           } ,
        { 383 , "hp data alarm"   } , { 384 , "rnss"            } , { 387 , "aurp"            } , { 388 , "unidata ldm"     } , { 389 , "ldap"            } ,
        { 401 , "ups"             } , { 427 , "slp"             } , { 433 , "nntp"            } , { 434 , "mobile ip"       } , { 443 , "https"           } ,
        { 444 , "snpp"            } , { 445 , "smb"             } , { 464 , "kerbero pass"    } , { 465 , "msg submission"  } , { 475 , "tcpnethasprv"    } ,
        { 497 , "retrospect"      } , { 500 , "isakmp/ike"      } , { 502 , "modbus"          } , { 504 , "citadel"         } , { 510 , "fcp"             } ,
        { 512 , "rexec"           } , { 513 , "rlogin"          } , { 514 , "syslog"          } , { 515 , "lpd"             } , { 517 , "talk"            } ,
        { 518 , "ntalk"           } , { 520 , "efs/rip"         } , { 525 , "timed"           } , { 530 , "rpc"             } , { 540 , "uucp"            } ,
        { 542 , "commerce"        } , { 543 , "kerbero login"   } , { 544 , "kerberos shell"  } , { 546 , "dhcpv6"          } , { 547 , "dhcpv6"          } ,
        { 548 , "afp(s)"          } , { 550 , "new-who/rwho"    } , { 554 , "rtsp"            } , { 556 , "rfs"             } , { 560 , "rmonitor"        } ,
        { 561 , "monitor"         } , { 563 , "nntps"           } , { 587 , "submission"      } , { 591 , "filemaker"       } , { 593 , "ms exchange svr" } ,
        { 601 , "syslog"          } , { 604 , "tunnel profile"  } , { 623 , "afs-rmcp"        } , { 631 , "ipp"             } , { 635 , "rlz dbase"       } ,
        { 636 , "ldaps"           } , { 643 , "sanity"          } , { 646 , "ldp"             } , { 647 , "dhcp failover"   } , { 648 , "rrp"             } ,
        { 651 , "ieee-mms"        } , { 654 , "mms/mmp"         } , { 657 , "ibm rmc"         } , { 660 , "macOS svr"       } , { 662 , "nfsv3"           } ,
        { 666 , "doom"            } , { 674 , "acap"            } , { 684 , "corba iiop ssl"  } , { 688 , "realm-rusd"      } , { 690 , "vatp"            } ,
        { 691 , "ms exchange"     } , { 694 , "linux-ha"        } , { 695 , "ieee-mms-ssl"    } , { 698 , "olsr"            } , { 700 , "epp"             } ,
        { 701 , "lmp"             } , { 702 , "iris"            } , { 706 , "silc"            } , { 711 , "cisco tag dist." } , { 712 , "tbrpf"           } ,
        { 749 , "kerberos admin"  } , { 750 , "kerbero-iv"      } , { 753 , "rrh"             } , { 800 , "mdbs-dameon"     } , { 802 , "modbus/tcp"      } ,
        { 829 , "cmp"             } , { 830 , "netconf-ssh"     } , { 831 , "netconf-beep"    } , { 832 , "netconf_soap"    } , { 833 , "netconf_soap"    } ,
        { 847 , "dhcp failover"   } , { 848 , "gdoi"            } , { 853 , "dns over tls"    } , { 860 , "iscsi"           } , { 861 , "owamp"           } ,
        { 862 , "twamp"           } , { 873 , "rsync"           } , { 892 , "nfsv3"           } , { 953 , "rndc"            } , { 989 , "ftps-data"       } ,
        { 990 , "ftps"            } , { 991 , "nas"             } , { 992 , "telent(s)"       } , { 993 , "imaps"           } , { 995 , "pop3s"           } , 
    } ;

    auto it = serviceMap.find( port ) ;
    if( serviceMap.end() != it )
    {
    	return ( it->second ).c_str() ; 
    }

    return nullptr ;
}


void daniel::dns::RR::RData_WKS::Initialize()
{
	if( nullptr != pPorts )
	{
		delete pPorts ;
		pPorts = nullptr ;
	}

	address  = 0 ;
	protocol = 0 ;
}


uint16_t daniel::dns::RR::RData_WKS::ToNullStr( uint8_t * pStr , uint16_t const & length ) const
{
	if( nullptr == pStr || 1 > length )
	{
		return 0 ;
	}

	
	std::stringstream ss ;

	ss << static_cast< uint16_t >( ( address >> 24 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >> 16 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >>  8 ) & 0x000000FF ) << "."
	   << static_cast< uint16_t >( ( address >>  0 ) & 0x000000FF ) << " "
	   << static_cast< uint16_t >( protocol ) ;

	if( nullptr != pPorts && 0 < pPorts->GetCount() )
	{
		ds::LinkedList< uint16_t >::const_iterator posIter = pPorts->begin() ;
		ds::LinkedList< uint16_t >::const_iterator endIter = pPorts->end() ;

		while( posIter != endIter )
		{
			uint16_t const & port = *posIter ;
			char const * pService = GetServiceName( port ) ;
			std::string portStr = std::to_string( port ) ;

			ss << " " << ( ( nullptr == pService ) ? portStr.c_str() : std::string( pService ) + "(" + portStr + ")" ) ;

			++posIter ;
		}
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


bool daniel::dns::RR::RData_WKS::Load( uint8_t const * pData , uint16_t const & length )
{
	if( nullptr == pData || 1 > length )
	{
		return false ;
	}
	
	if( 5 > length )
	{
		return false ;
	}

	Initialize() ;

	address = ( ( pData[ 0 ] << 24 ) & 0xFF000000 )
			| ( ( pData[ 1 ] << 16 ) & 0x00FF0000 )
			| ( ( pData[ 2 ] <<  8 ) & 0x0000FF00 )
			| ( ( pData[ 3 ] <<  0 ) & 0x000000FF ) ;

	protocol = pData[ 4 ] ;

	uint16_t portslen = length - 5 ;

	for( uint16_t pos = 0 ; pos < portslen ; ++pos )
	{
		uint8_t const & dat = pData[ 5 + pos ] ;

		for( uint8_t bitPos = 0 ; bitPos < 8 ; ++bitPos )
		{
			uint16_t isIn = dat & ( 0x01U << bitPos ) ;

			if( 0 < isIn )
			{
				uint16_t port = ( pos * 8 ) + bitPos ;

				if( 1023 < port )
				{
					goto done ;
				}

				if( nullptr == pPorts )
				{
					pPorts = new ( std::nothrow ) ds::LinkedList< uint16_t >() ;
					if( nullptr == pPorts )
					{
						Initialize() ;
						return false ;
					}
				}

				uint16_t * pPort = new ( std::nothrow ) uint16_t ( port ) ;
				if( nullptr == pPort )
				{
					Initialize() ;
					return false ;
				}

				if( false == pPorts->Insert( pPort ) )
				{
					delete pPort ;
					
					Initialize() ;
					return false ;
				}
			}
		}
	}


done : 
	return true ;
}