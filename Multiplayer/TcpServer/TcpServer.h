
#ifndef MULTIPLAYER_TCP_SERVER_H
#define MULTIPLAYER_TCP_SERVER_H


///////////////////////////////////////////////
// Headers			    				  	 //
///////////////////////////////////////////////
											 //
#include "../../Network/Network.h"			 //
#include "../TcpConnection/TcpConnection.h"  //
#include "../Message/Message.h"			     //
											 //
#include <vector>							 //
											 //
///////////////////////////////////////////////


namespace mp
{
	class TcpServer
	{
		private:
				
			///////////////////////////////////////////////
			// Private member data 						 //
			///////////////////////////////////////////////

			net::TcpListener		  	  listener;
			std::vector<TcpConnection> connections;
			bool					   run = false;


		public:

			///////////////////////////////////////////////
			// Static private methods					 //
			///////////////////////////////////////////////

			static void ConnectionHandler(TcpServer* server, TcpConnection this_connection);

			static void Core(TcpServer* server);

			static net::Socket::Status Send(const net::TcpSocket socket, const Message message, const DWORD sender_id);

			static net::Socket::Status Receive(const net::TcpSocket socket, Message& message, DWORD& recipient_id);


		public:
			
			///////////////////////////////////////////////
			// Methods  								 //
			///////////////////////////////////////////////
			
			net::Socket::Status Run(const net::IpAddress address, const UINT16 port);
			
			bool IsLaunched() const;

			void Stop();
	};


	/////////////////////////////////////////////////////////////////////////////////
	// Definition of the most common name   	           	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	typedef TcpServer TCP_SERVER;

} // namespace mp


#endif // MULTIPLAYER_TCP_SERVER_H
