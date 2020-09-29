
///////////////////////////////////////
// Headers			    			 //
///////////////////////////////////////
									 //
#include "TcpServer.h"				 //
									 //
#include "../TcpClient/TcpClient.h"	 //
								     //
#include "../Letter/Letter.h"		 //
#include "../Answer/Answer.h"		 //
									 //
#include <thread>					 //
									 //
///////////////////////////////////////


namespace mp
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Static private methods																    //
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////
	void TcpServer::ConnectionHandler(TcpServer* server, TcpConnection this_connection)  //
	{
		this_connection.id = (server->connections.size() + 1);
		server->connections.push_back(this_connection);

		Letter _letter;

		while (server->IsLaunched() == true)
		{
			if (Receive(this_connection.socket, _letter.message, _letter.recipient_id) == net::Socket::Done)
			{
				if (_letter.recipient_id <= server->connections.size())
					Send(server->connections[_letter.recipient_id - 1].socket, _letter.message, this_connection.id);
				else
					Send(this_connection.socket, _letter.message << Answer("Error"), Id::System);
				
				_letter.Clear();
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void TcpServer::Core(TcpServer* server)																		    //
	{
		TcpConnection new_connection;

		while (server->listener.Accept(new_connection.socket) == net::Socket::Done)
		{
			std::thread _connection_handler_thread(ConnectionHandler, server, new_connection);
			_connection_handler_thread.detach();
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	net::Socket::Status TcpServer::Send(const net::TcpSocket socket, const Message message, const DWORD sender_id)  //
	{
		Sleep(1);

		net::DataPacket _message_info;

		_message_info << sender_id;
		_message_info << message.type;

		net::Socket::Status _status[] = { socket.Send(message.packet), socket.Send(_message_info) };

		return _status[0] > _status[1] ? _status[0] : _status[1];
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	net::Socket::Status TcpServer::Receive(const net::TcpSocket socket, Message& message, DWORD& recipient_id)  //
	{
		Sleep(1);

		net::DataPacket _message_info;
		net::Socket::Status _status[] = { socket.Receive(message.packet), socket.Receive(_message_info) };

		_message_info >> recipient_id;

		int _type;
		_message_info >> _type;
		message.type = static_cast<Message::Type>(_type);

		return _status[0] > _status[1] ? _status[0] : _status[1];
	}



	//////////////////////////////////////////////////////////////////////////////////////////////
	// Methods																				    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	net::Socket::Status TcpServer::Run(const net::IpAddress address, const UINT16 port)  //
	{
		if (listener.Listen(address, port) == net::Socket::Done)
		{
			run = true;

			std::thread _core_thread(Core, this);
			_core_thread.detach();
			
			return net::Socket::Done;
		}
		
		return net::Socket::Error;
	}


	/////////////////////////////////////////////////////////////////////////////////
	bool TcpServer::IsLaunched() const											   //
	{
		return run;
	}


	/////////////////////////////////////////////////////////////////////////////////
	void TcpServer::Stop()														   //
	{
		run = false;
	}

} // namespace mp
