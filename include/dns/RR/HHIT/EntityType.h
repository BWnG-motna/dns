#pragma once

#include "Common.h"


namespace daniel
{

namespace dns
{

namespace RR
{

namespace HHIT
{


enum class EntityType : uint8_t
{
	NotDefined  =    0 ,
	DIME        =    1 , // DRIP Identity Management Entity
	Apex        =    5 ,
	RAA         =    9 , // Registered Assigning Authority ( RAA )
	HDA         =   13 , // HHIT Domain Authority
	UA          =   16 , // Unmanned Aircraft
	GCS         =   17 , // Ground Control Station
	UAS         =   18 , // Unmanned Aircraft System
	RIDModule   =   19 , // Remote Identifcation(RID) Module
	Pilot       =   20 ,
	Operator    =   21 ,
	DSS         =   22 , // Discovery and Synchronization Service ( DSS )
	USS         =   23 , // UAS Service Supplier
	SP          =   24 , // Network RID Service Provider ( SP )
	DP          =   25 , // Network RID Display Provider ( DP )
	SDSP        =   26 , // Supplemental Data Service Provider ( SDSP )
	CSRIDFinder =   27 , // Crowd Sourced RID(CSRID) Finder
} ;


bool IsValidEntityType( uint8_t const & type ) ;


}   // namespace HHIT

}   // namespace RR

}   // namespace dns

}   // namespace daniel