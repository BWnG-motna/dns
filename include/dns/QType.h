#pragma once

#include "Common.h"


namespace daniel
{
	
namespace dns
{
	
enum class QType : uint16_t
{
	A           =      1  , // a host address
	NS          =      2  , // an authoritative name server
	MD          =      3  , // a mail destination ( Obsolete - use MX )
	MF          =      4  , // a mail forwarder   ( Obsolete - use MX )
	CNAME       =      5  , // the canonical name for an alias
	SOA         =      6  , // marks the start of a zone of authority
	MB          =      7  , // a mailbox domain name ( EXPERIMENTAL )
	MG          =      8  , // a mail group member ( EXPERIMENTAL )
	MR          =      9  , // a mail rename domain name ( EXPERIMENTAL )
	NULL        =     10  , // a null RR ( EXPERIMENTAL )
	WKS         =     11  , // a well known service description
	PTR         =     12  , // a domain name pointer
	HINFO       =     13  , // host information
	MINFO       =     14  , // mailbox or mail list information
	MX          =     15  , // mail exchange
	TXT         =     16  , // text string
	RP          =     17  , // responsible persion

#if 0
	AFSDB       =     18  , // Andrew File System( AFS ) Database
	X25         =     19  ,
	ISDN        =     20  ,
	RT          =     21  ,
	NSAP        =     22  ,
	NSAP_PTR    =     23  ,
	SIG         =     24  ,
	KEY         =     25  ,
	PX          =     26  ,
	GPOS        =     27  ,
#endif

	AAAA        =     28  , // a single IPv6 address

#if 0
	LOC         =     29  ,
	NXT         =     30  ,
	EID         =     31  ,
	NIMLOC      =     32  ,
	SRV         =     33  ,
	ATMA        =     34  ,
	NAPTR       =     35  ,
	KX          =     36  ,
	CERT        =     37  ,  

#endif

	A6          =     38  , // a signle IPv6 address ( obsolete - see AAAA )
	
#if 0
	DNAME       =     39  ,
	SINK        =     40  ,
#endif

	OPT         =     41  ,

#if 0
	APL         =     42  ,
	DS          =     43  ,
	SSHFP       =     44  ,
	IPSECKEY    =     45  ,
#endif

	RRSIG       =     46  ,

#if 0
	NSEC        =     47  ,
#endif

	DNSKEY      =     48  ,
	
#if 0
	DHCID       =     49  ,
	NSEC3       =     50  ,
	NSEC3PARAM  =     51  ,
	TLSA        =     52  ,
	SMIMEA      =     53  ,
	
	HIP         =     55  ,
	NINFO       =     56  ,
	RKEY        =     57  ,
	TALINK      =     58  ,
	CDS         =     59  ,
	CDNSKEY     =     60  ,
	OPENPGPKEY  =     61  ,	
	CSYNC       =     62  ,
	ZONEMD      =     63  ,
	SVCB        =     64  ,
	HTTPS       =     65  ,
	DSYNC       =     66  ,
	HHIT        =     67  ,
	BRID        =     68  ,

	SPF         =     99  ,

	UINFO       =    100  ,
	UID         =    101  ,
	GID         =    102  ,
	UNSPEC      =    103  ,
	NID         =    104  ,
	L32         =    105  ,
	L64         =    106  ,
	LP          =    107  ,
	EUI48       =    108  ,
	EUI64       =    109  ,

	NXNAME      =    128  ,

	TKEY        =    249  ,
	TSIG        =    250  ,
	IXFR        =    251  ,
#endif

	AXFR        =    252  , // A request for a transfer of an entire zone 
	MAILB       =    253  , // A request for a mailbox-related records ( MB, MG or MR )
	MAILA       =    254  , // A request for mail agent RRs ( Obsolete - see MX )
	ALL         =    255  , // A request for all records

#if 0
	URI         =    256 ,
	CAA         =    257 ,
	AVC         =    258 ,
	DOA         =    259 ,
	AMTRELAY    =    260 ,
	RESINFO     =    261 ,
	WALLET      =    262 ,
	CLA         =    263 ,
	IPN         =    264 ,

	TA          =  32768 ,
	DDLV        =  32769 ,
#endif

	UNKNOWN     =  65535 ,

} ; // enum class QType


char const * ToString( QType const & type ) ;

QType StrToQType( char const * str ) ;


}   // namespace dns

}   // namespace daniel