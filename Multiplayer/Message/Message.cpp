
/////////////////////////////////////////
// Headers			    			   //
/////////////////////////////////////////
									   //
#include "Message.h"			       //
									   //
/////////////////////////////////////////


namespace mp
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Constructor	  																		    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	Message::Message()																   //
	{

	}


	/////////////////////////////////////////////////////////////////////////////////////
	Message::Message(Type type):													   //	
	type(type)
	{

	}


	/////////////////////////////////////////////////////////////////////////////////////
	Message::Message(LPCSTR text):													   //
	type(For_chat)
	{
		packet << text;
	}


	/////////////////////////////////////////////////////////////////////////////////////
	Message::Message(std::string text):												   //
	type(For_chat)
	{
		packet << text;
	}	
	

	/////////////////////////////////////////////////////////////////////////////////////
	Message::Message(net::DataPacket packet, Type type):							   //
	packet(packet),
	type(type)
	{
		
	}



	//////////////////////////////////////////////////////////////////////////////////////////////
	// Methods																					//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	void Message::Clear()														   //
	{
		packet.Clear();
		type = None;
	}

} // namespace mp