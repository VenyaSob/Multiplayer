
///////////////////////////////////////
// Headers			    			 //
///////////////////////////////////////
									 //
#include "TcpSocket.h"				 //
									 //
///////////////////////////////////////


namespace net
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Methods																				    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	Socket::Status TcpSocket::Connect(const IpAddress address, const UINT16 port)  //
	{
		Disconnect();

		socket_core = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socket_core == INVALID_SOCKET)
			return Error;

		SOCKADDR_IN _addr_in = Socket::CreateSockAddrIn(address, port);

		if (connect(socket_core, reinterpret_cast<SOCKADDR*>(&_addr_in), sizeof(_addr_in)) != 0)
			return Error;

		return Done;
	}


	/////////////////////////////////////////////////////////////////////////////////
	void TcpSocket::Disconnect()												   //
	{
		Socket::Close();
	}


	/////////////////////////////////////////////////////////////////////////////////
	Socket::Status TcpSocket::Send(const DataPacket packet) const			       //
	{
		if (socket_core != INVALID_SOCKET)
		{
			size_t _size = packet.GetDataSize();

			if (packet.GetData() != nullptr && _size > 0)
			{
				if (send(socket_core, reinterpret_cast<LPCSTR>(&_size), sizeof(size_t), NULL) == SOCKET_ERROR ||
					send(socket_core, static_cast<LPCSTR>(packet.GetData()), _size, NULL) == SOCKET_ERROR)
					return Error;
			}
			else return Error;
		}
		else return Disconnected;
		
		return Done;
	}
	
		
	/////////////////////////////////////////////////////////////////////////////////
	Socket::Status TcpSocket::Receive(DataPacket& packet) const					   //
	{
		if (socket_core != INVALID_SOCKET)
		{
			size_t _size = 0;	
			void*  _data = nullptr;

			if (recv(socket_core, reinterpret_cast<LPSTR>(&_size), sizeof(size_t), NULL) == SOCKET_ERROR)
				return Error;

			_data = new BYTE[_size];

			if (recv(socket_core, reinterpret_cast<LPSTR>(_data), _size, NULL) == SOCKET_ERROR)
				return Error;
			
			packet.Clear();
			packet.Append(_data, _size);

			delete[] _data;
		}
		else return Disconnected;

		return Done;
	}

} // namespace net;	