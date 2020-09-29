
#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H


//////////////////////////////////////////
// Headers			    				//
//////////////////////////////////////////
										//
#include "../Config/Config.h"			//
#include "../IpAddress/IpAddress.h"		//
										//
//////////////////////////////////////////


namespace net
{
	class Socket
	{
		protected:

			///////////////////////////////////////////////
			// Protected member data 					 //
			///////////////////////////////////////////////
			
			SOCKET socket_core;

		
		public:

			///////////////////////////////////////////////
			// Constructor  							 //
			///////////////////////////////////////////////

			Socket();


		public:

			///////////////////////////////////////////////
			// Data type								 //
			///////////////////////////////////////////////

			enum Status
			{
				Done,
				Error,
				Disconnected
			};


		public:

			///////////////////////////////////////////////
			// Methods									 //
			///////////////////////////////////////////////

			bool IsDisconnected();


		protected:
			
			///////////////////////////////////////////////
			// Protected methods		 				 //
			///////////////////////////////////////////////
			
			static SOCKADDR_IN CreateSockAddrIn(const IpAddress address, const UINT16 port);

			void Close();
	};
	
	
	/////////////////////////////////////////////////////////////////////////////////
	// Definition of the most common name	  	           	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	typedef Socket PARENT_SOCKET;

} // namespace net


#endif // NETWORK_SOCKET_H