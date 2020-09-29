
#ifndef MULTIPLAYER_REQUEST_H
#define MULTIPLAYER_REQUEST_H


////////////////////////////////////////////////////
// Headers			    					      //
////////////////////////////////////////////////////
												  //
#include "../../Network/DataPacket/DataPacket.h"  //
												  //
////////////////////////////////////////////////////


namespace mp
{
	enum Request 
	{
		None,
	};


	///////////////////////////////////////////////
	// Global operator overloading		         //
	///////////////////////////////////////////////

	net::DataPacket& operator <<(net::DataPacket& packet, Request request);

	net::DataPacket& operator >>(net::DataPacket& packet, Request& request);

} // namespace mp


#endif // MULTIPLAYER_REQUEST_H