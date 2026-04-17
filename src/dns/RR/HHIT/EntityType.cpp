#include "dns/RR/HHIT/EntityType.h"


bool daniel::dns::RR::HHIT::IsValidEntityType( uint8_t const & typeVal )
{
	switch( typeVal )
	{
		case  1 : // DIME
		case  5 : // Apex
		case  9 : // RAA         // Registered Assigning Authority ( RAA )
		case 13 : // HDA         // HHIT Domain Authority
		case 16 : // UA          // Unmanned Aircraft
		case 17 : // GCS         // Ground Control Station
		case 18 : // UAS         // Unmanned Aircraft System
		case 19 : // RIDModule   // Remote Identifcation(RID) Module
		case 20 : // Pilot
		case 21 : // Operator
		case 22 : // DSS         // Discovery and Synchronization Service ( DSS )
		case 23 : // USS         // UAS Service Supplier
		case 24 : // SP          // Network RID Service Provider ( SP )
		case 25 : // DP          // Network RID Display Provider ( DP )
		case 26 : // SDSP        // Supplemental Data Service Provider ( SDSP )
		case 27 : // CSRIDFinder // Crowd Sourced RID(CSRID) Finder
			return true ;

		default :
			return false ;
	}

}