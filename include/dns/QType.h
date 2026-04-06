#pragma once

#include "Common.h"


#undef NULL 


namespace daniel
{
	
namespace dns
{
	
enum class QType : uint16_t
{
	Sp          =      0  , // for RData SIG

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
	AFSDB       =     18  , // Andrew File System( AFS ) Database
	X25         =     19  , // for X.25 network, PSDN-address is described.
	ISDN        =     20  , // mapping hostname and address(phone number) - ISDN-address is described.
	RT          =     21  , // Route Through record. Specifies the Intermediate hosts
	NSAP        =     22  ,
	NSAP_PTR    =     23  ,
	SIG         =     24  , // Signature record ( Obsoleted by RRSIG in morden DNSEC per RFC 3755 )
	KEY         =     25  ,
	PX          =     26  ,
	GPOS        =     27  ,
	AAAA        =     28  , // a single IPv6 address
	LOC         =     29  , // Location information , based WGS84 , experimental
	NXT         =     30  ,
	EID         =     31  ,
	NIMLOC      =     32  ,
	SRV         =     33  , // Service locator record, Specifies the hostname and port number of servers providing a specific service
	ATMA        =     34  ,
	NAPTR       =     35  , // Naming Authority Pointer record, Provide rules for dynamic rewriting of to domain names or URIs
	KX          =     36  ,
	CERT        =     37  , // Ceritifate record. Stores X.509 cerificates, PGP keys, or other cryptographic certificates in the DNS
	A6          =     38  , // a single IPv6 address ( obsolete - see AAAA )
	DNAME       =     39  ,
	SINK        =     40  ,
	OPT         =     41  ,
	APL         =     42  , // Address Prefix List record, Specifies lists of address prefixes to be associated with a DNS name.
	DS          =     43  , // Establishes a delegation signer record that creates the chian of trust.
	                        // from the parent zone to the child zone by publishing a hash (digest) of the child zone's KSK.
	SSHFP       =     44  , // SSH Fingerprint record. Publishes the SSH public key fingerprint for a host to enable secure key verification
	                        // and prevent man-in-the-middle attacks.
	IPSECKEY    =     45  , // IPsec Key record. Publishes a public key or key locator 
	                        // for use with IPsec to establish secure communication with a host or gateway.
	RRSIG       =     46  , // Provides a cryptographic digital signature for specific RRset , signed with the zone's private key.
	NSEC        =     47  , // Next Secure record. Indicates the next owner name in the canonical ordering of the zone 
	                        // and lists the RR types present at the current name.
	DNSKEY      =     48  , // Publishes the public key(s) for zone ( ZSK and/or KSK ).
	DHCID       =     49  , // DHCP client identifier record. Stores a client identifier used by DHCP servers to associate DHCP leases with DNS names 
	                        // and prevent duplicate updates from different client.
	NSEC3       =     50  , // Provides authenticated denial of existence for non-existent domain names and provides the absence of
	                        // specific RR types , while preventing zone walking attacks through hashed owner names.
	NSEC3PARAM  =     51  , // NSEC3 parameters record. Contains the parameters used to generate NSEC3 records in the zone.
	TLSA        =     52  , // Associates a TLS certificate or public key with a domain name and prot for DANE.
	SMIMEA      =     53  , // S/MIME certificate association record. Associates an S/MIME certificate or public key with a domain name for secure email.
	
	HIP         =     55  , // Host Identity Protocol record. Publishes Host Identity and redezvous information for the Host Identity Protocol.
	NINFO       =     56  ,
	RKEY        =     57  ,
	TALINK      =     58  ,
	CDS         =     59  , // Child DS record. Contains a Delegation Singer record that the child zone wants the parent to publish.
	CDNSKEY     =     60  , // Child DNSKEY record. Continas a DNSKEY record that the child zone wants the parent to use for generating a DS record.
	OPENPGPKEY  =     61  ,	// OpenPGP Public Key record. Publishes an OpenPGP public key associated with a user identifier for secure email.
	CSYNC       =     62  , // Child-to-Parent Synchronization record. 
	                        // Indicates which RRsets the child wants the parent to synchronize during automated zone maintenance.
	ZONEMD      =     63  , // Zone Message Digest record. Provides a cryptographic hash of entire zone contents,
	                        // allowing verification of zone data integrity at rest.
	SVCB        =     64  , // Service Binding record. Provides information to help clients connect to a service more efficiently, 
	                        // including alternative endpoints, IP hints, port numbers, and transport parameters.
	HTTPS       =     65  , // HTTPS Service Binding record. A special use of SVCB record for HTTPS service.
	DSYNC       =     66  ,
	HHIT        =     67  ,
	BRID        =     68  ,

	SPF         =     99  , // Sender Policy Framework record. 
	                        // Specifies authorized mail servers and IP addresses that are allowed to send email for the domain
	                        // that are allowed to send email for the domain, helping to prevent email spoofing and spam.
	UINFO       =    100  ,
	UID         =    101  ,
	GID         =    102  ,
	UNSPEC      =    103  ,
	NID         =    104  ,
	L32         =    105  ,
	L64         =    106  ,
	LP          =    107  ,
	EUI48       =    108  , // 48-bit Extended Unique Identifier record.
	EUI64       =    109  , // 64-bit Extended Unique Identifier record.

	NXNAME      =    128  ,

	TKEY        =    249  ,
	TSIG        =    250  ,
	IXFR        =    251  ,
	AXFR        =    252  , // A request for a transfer of an entire zone 
	MAILB       =    253  , // A request for a mailbox-related records ( MB, MG or MR )
	MAILA       =    254  , // A request for mail agent RRs ( Obsolete - see MX )
	ALL         =    255  , // A request for all records
	URI         =    256  ,
	CAA         =    257  , // Certification Authority Authorization record.
	                        // Specifies which Cerificate Authorities ( CAs ) are authorized to issue cerificates for the domain name.
	AVC         =    258  ,
	DOA         =    259  ,
	AMTRELAY    =    260  ,
	RESINFO     =    261  ,
	WALLET      =    262  ,
	CLA         =    263  ,
	IPN         =    264  ,

	TA          =  32768  ,
	DDLV        =  32769  ,

	UNKNOWN     =  65535  ,

} ; // enum class QType


char const * ToString( QType const & type ) ;

QType StrToQType( char const * str ) ;


}   // namespace dns

}   // namespace daniel