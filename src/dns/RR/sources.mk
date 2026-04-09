include src/dns/RR/APL/sources.mk
include src/dns/RR/CERT/sources.mk
include src/dns/RR/DANE/sources.mk
include src/dns/RR/DHCID/sources.mk
include src/dns/RR/HIP/sources.mk
include src/dns/RR/IPSECKEY/sources.mk
include src/dns/RR/SEC/sources.mk
include src/dns/RR/SSHFP/sources.mk
include src/dns/RR/SVC/sources.mk
include src/dns/RR/ZONEMD/sources.mk

OBJS += src/dns/RR/RData.o            \
		src/dns/RR/RData_A.o          \
		src/dns/RR/RData_NS.o         \
		src/dns/RR/RData_MD.o         \
		src/dns/RR/RData_MF.o         \
		src/dns/RR/RData_CNAME.o      \
		src/dns/RR/RData_SOA.o        \
		src/dns/RR/RData_MB.o         \
		src/dns/RR/RData_MG.o         \
		src/dns/RR/RData_MR.o         \
		src/dns/RR/RData_NULL.o       \
		src/dns/RR/RData_WKS.o        \
		src/dns/RR/RData_PTR.o        \
		src/dns/RR/RData_HINFO.o      \
		src/dns/RR/RData_MINFO.o      \
		src/dns/RR/RData_MX.o         \
		src/dns/RR/RData_TXT.o        \
		src/dns/RR/RData_RP.o         \
		src/dns/RR/RData_AFSDB.o      \
		src/dns/RR/RData_X25.o        \
		src/dns/RR/RData_ISDN.o       \
		src/dns/RR/RData_RT.o         \
		src/dns/RR/RData_NSAP.o       \
		src/dns/RR/RData_NSAP_PTR.o   \
		src/dns/RR/RData_SIG.o        \
		src/dns/RR/RData_KEY.o        \
		src/dns/RR/RData_PX.o         \
		src/dns/RR/RData_GPOS.o       \
		src/dns/RR/RData_AAAA.o       \
		src/dns/RR/RData_LOC.o        \
		src/dns/RR/RData_NXT.o        \
		\
		src/dns/RR/RData_SRV.o        \
		src/dns/RR/RData_NAPTR.o      \
		src/dns/RR/RData_KX.o         \
		src/dns/RR/RData_CERT.o       \
		src/dns/RR/RData_A6.o         \
		\
		src/dns/RR/RData_APL.o        \
		src/dns/RR/RData_DS.o         \
		src/dns/RR/RData_SSHFP.o      \
		src/dns/RR/RData_IPSECKEY.o   \
		src/dns/RR/RData_RRSIG.o      \
		src/dns/RR/RData_NSEC.o       \
		src/dns/RR/RData_DNSKEY.o     \
		src/dns/RR/RData_DHCID.o      \
		src/dns/RR/RData_NSEC3.o      \
		src/dns/RR/RData_NSEC3PARAM.o \
		\
		src/dns/RR/RData_TLSA.o       \
		src/dns/RR/RData_SMIMEA.o     \
		src/dns/RR/RData_HIP.o        \
		\
		src/dns/RR/RData_CDS.o        \
		src/dns/RR/RData_CDNSKEY.o    \
		src/dns/RR/RData_OPENPGPKEY.o \
		src/dns/RR/RData_CSYNC.o      \
		src/dns/RR/RData_ZONEMD.o     \
		src/dns/RR/RData_SVCB.o       \
		src/dns/RR/RData_HTTPS.o      \
		\
		src/dns/RR/RData_SPF.o        \
		\
		src/dns/RR/RData_EUI48.o      \
		src/dns/RR/RData_EUI64.o      \
		\
		src/dns/RR/RData_URI.o        \
		src/dns/RR/RData_CAA.o        \
		\
		src/dns/RR/RData_TA.o         \
		\
		src/dns/RR/RData_NAME.o