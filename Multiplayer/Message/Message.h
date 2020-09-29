
#ifndef MULTIPLAYER_MESSAGE_H
#define MULTIPLAYER_MESSAGE_H


/////////////////////////////////////////
// Headers			    			   //
/////////////////////////////////////////
									   //
#include "../../Network/Network.h"     //
									   //
/////////////////////////////////////////

namespace mp
{
	struct Message
	{	
		///////////////////////////////////////////////
		// Data type								 //
		///////////////////////////////////////////////
	
		enum Type
		{
			None,
			For_chat,
			Partial,
			Request,
			Answer
		};


		///////////////////////////////////////////////
		// Member data 								 //
		///////////////////////////////////////////////

		net::DataPacket packet;
		Type       type = None;


		///////////////////////////////////////////////
		// Constructor	  						     //
		///////////////////////////////////////////////

		Message();

		Message(Type type);

		Message(LPCSTR text);

		Message(std::string text);

		Message(net::DataPacket packet, Type type);


		///////////////////////////////////////////////
		// Methods  								 //
		///////////////////////////////////////////////

		void Clear();
	};


	/////////////////////////////////////////////////////////////////////////////////
	// Definition of the most common name	  	           	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	typedef Message MESSAGE;

} // namespace mp


#endif // MULTIPLAYER_MESSAGE_H