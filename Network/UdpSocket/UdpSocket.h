
#ifndef NETWORK_UDP_SOCKET_H
#define	NETWORK_UDP_SOCKET_H


//////////////////////////////////////////
// Headers			    				//
//////////////////////////////////////////
										//
#include "../Config/Config.h"			//
#include "../Socket/Socket.h"			//
#include "../DataPacket/DataPacket.h"	//
										//
//////////////////////////////////////////


namespace net
{
	class UdpSocket: public Socket
	{
		public:
			
			///////////////////////////////////////////////
			// Methods									 //
			///////////////////////////////////////////////
			
			Status Bind(const IpAddress address, const UINT16 port);

			void Unbind();
			
			Status Send(const DataPacket packet, const IpAddress address, const UINT16 port) const;

			Status Receive(DataPacket& packet, IpAddress& address, UINT16& port) const;
	};


	/////////////////////////////////////////////////////////////////////////////////
	// Definition of the most common name   	           	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	typedef UdpSocket UDP_SOCKET;

} // namespace net


#endif // NETWORK_UDP_SOCKET_H