
///////////////////////////////////////
// Headers			    			 //
///////////////////////////////////////
									 //
#include "TcpConnection.h"			 //
									 //
///////////////////////////////////////


namespace mp
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Methods																				    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////	
	net::IpAddress TcpConnection::GetIpAddress()								   //
	{
		return address;
	}

} // namespace mp