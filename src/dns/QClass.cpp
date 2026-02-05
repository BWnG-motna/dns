#include "dns/QClass.h"


char const * daniel::dns::ToString( QClass const & qclass )
{
	switch( qclass )
	{
		case QClass::IN :
			return "IN" ;

		case QClass::CS :
			return "CS" ;

		case QClass::CH :
			return "CH" ;

		case QClass::HS :
			return "HS" ;

		case QClass::ALL :
			return "*" ;

		default :
			return "UNKNOWN" ;
	}
}
