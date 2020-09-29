
///////////////////////////////////////////////
// Headers			    				  	 //
///////////////////////////////////////////////
											 //
#include "TcpClient.h"						 //
											 //
#include <thread>							 //	
											 //
///////////////////////////////////////////////


namespace mp
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Static private method																	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	void TcpClient::MessageHandler(TcpClient* client)							   //
	{
		Letter _new_letter;

		while (client->IsDisconnected() != true)
		{
			if (client->unread_letters.size() < client->settings.maximum_number_of_letters)
			{
				if (client->Receive(_new_letter.message, _new_letter.sender_id) == net::Socket::Done)
					client->unread_letters.push_back(_new_letter);
			}
		}
	}

	

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Private method    																		//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	net::Socket::Status TcpClient::Receive(Message& message, DWORD& sender_id) const   //
	{
		Sleep(1);

		net::DataPacket _message_info;
		net::Socket::Status _status[] = { socket.Receive(message.packet), socket.Receive(_message_info) };

		_message_info >> sender_id;

		UINT32 _message_type;
		_message_info >> _message_type;
		message.type = static_cast<Message::Type>(_message_type);

		return _status[0] > _status[1] ? _status[0] : _status[1];
	}
	


	//////////////////////////////////////////////////////////////////////////////////////////////
	// Methods																					 //
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	void TcpClient::SetSettings(Settings settings)								   //
	{
		this->settings = settings;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	net::Socket::Status TcpClient::ConnectToServer(const net::IpAddress address, const UINT16 port)  //
	{
		DisconnectFromServer();
		
		net::Socket::Status _status = socket.Connect(address, port);
		
		std::thread _message_handler_thread(MessageHandler, this);
		_message_handler_thread.detach();
		
		return _status;
	}


	/////////////////////////////////////////////////////////////////////////////////
	void TcpClient::DisconnectFromServer()										   //
	{
		socket.Disconnect();
	}

	
	/////////////////////////////////////////////////////////////////////////////////
	bool TcpClient::IsDisconnected()											   //
	{
		return socket.IsDisconnected();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	net::Socket::Status TcpClient::Send(const Message message, const DWORD recipient_id) const //
	{
		Sleep(1);

		net::DataPacket _message_info;

		_message_info << recipient_id;
		_message_info << message.type;

		net::Socket::Status _status[] = { socket.Send(message.packet), socket.Send(_message_info) };

		return _status[0] > _status[1] ? _status[0] : _status[1];
	}
	

	/////////////////////////////////////////////////////////////////////////////////////
	Letter TcpClient::GetLastLetter()												   //
	{
		Letter _last_letter = unread_letters.front();
		unread_letters.pop_front();

		return _last_letter;
	}


	/////////////////////////////////////////////////////////////////////////////////////
	std::list<Letter> TcpClient::GetListOfLetters()									   //
	{
		return unread_letters;
	}

} // namespace mp
