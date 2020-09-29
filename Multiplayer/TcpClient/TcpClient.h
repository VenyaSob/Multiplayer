
#ifndef MULTIPLAYER_TCP_CLIENT_H
#define MULTIPLAYER_TCP_CLIENT_H


/////////////////////////////////////////
// Headers			    			   //
/////////////////////////////////////////
									   //
#include "../../Network/Network.h"     //
#include "../Message/Message.h"		   //
#include "../Letter/Letter.h"		   //
									   //
#include <list>						   //
									   //
/////////////////////////////////////////


namespace mp
{
	enum Id
	{
		System = -1,
		Send_to_all
	};

} // namespace mp


namespace mp
{
	class TcpClient
	{	
		public:
			
			///////////////////////////////////////////////
			// Data type		 						 //
			///////////////////////////////////////////////
			
			struct Settings
			{
				//////////////////////////
				// Member data			//
				//////////////////////////

				size_t maximum_number_of_letters = 1000;
			};


		private:
			
			///////////////////////////////////////////////
			// Private member data 						 //
			///////////////////////////////////////////////

			net::TcpSocket			  socket;
			std::list<Letter> unread_letters;
			Settings			    settings;


		private:

			///////////////////////////////////////////////
			// Static private method					 //
			///////////////////////////////////////////////

			static void MessageHandler(TcpClient* client);


		private:
			
			///////////////////////////////////////////////
			// Private method							 //
			///////////////////////////////////////////////

			net::Socket::Status Receive(Message& message, DWORD& sender_id) const;


		public:

			///////////////////////////////////////////////
			// Methods  								 //
			///////////////////////////////////////////////
			
			void SetSettings(Settings settings);

			net::Socket::Status ConnectToServer(const net::IpAddress address, const UINT16 port);
			
			void DisconnectFromServer();

			bool IsDisconnected();

			net::Socket::Status Send(const Message message, const DWORD recipient_id) const;
			
			Letter GetLastLetter();
				
			std::list<Letter> GetListOfLetters();
	};


	/////////////////////////////////////////////////////////////////////////////////
	// Definition of the most common name		           	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	typedef TcpClient TCP_CLIENT;

} // namespace mp


#endif // MULTIPLAYER_TCP_CLIENT_H