
//////////////////////////////////////////
// Headers			    				//
//////////////////////////////////////////
										//
#include "UdpSocket.h"					//
										//
//////////////////////////////////////////


namespace net
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Methods																				    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	Socket::Status UdpSocket::Bind(const IpAddress address, const UINT16 port)	   //
	{
		Unbind();

		socket_core = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		SOCKADDR_IN _addr_in = Socket::CreateSockAddrIn(address, port);

		if (bind(socket_core, reinterpret_cast<SOCKADDR*>(&_addr_in), sizeof(_addr_in)) == SOCKET_ERROR)
			return Error;

		return Done;
	}


	/////////////////////////////////////////////////////////////////////////////////
	void UdpSocket::Unbind()									  			       //
	{
		Socket::Close();
	}

	const size_t size = 256;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Socket::Status UdpSocket::Send(const DataPacket packet, const IpAddress address, const UINT16 port) const  //
	{
		/*
		if (socket_core != INVALID_SOCKET)
		{
			size_t _size = packet.GetDataSize();
			SOCKADDR_IN _addr_in = Socket::CreateSockAddrIn(address, port);

			if (packet.GetData() != nullptr && _size > 0)
			{
				if (sendto(socket_core, reinterpret_cast<LPCSTR>(&_size), sizeof(size_t), NULL, reinterpret_cast<const SOCKADDR*>(&_addr_in), sizeof(_addr_in)) == SOCKET_ERROR ||
					sendto(socket_core, static_cast<LPCSTR>(packet.GetData()), _size, NULL, reinterpret_cast<const SOCKADDR*>(&_addr_in), sizeof(_addr_in)) == SOCKET_ERROR)
					return Error;
			}
			else return Error;
		}
		else return Error;
		*/

		SOCKADDR_IN _addr_in = Socket::CreateSockAddrIn(address, port);
		if (sendto(socket_core, static_cast<LPCSTR>(packet.GetData()), size, NULL, reinterpret_cast<const SOCKADDR*>(&_addr_in), sizeof(_addr_in)) == SOCKET_ERROR)
			return Error;

		return Done;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////
	Socket::Status UdpSocket::Receive(DataPacket& packet, IpAddress& address, UINT16& port) const  //
	{
		/*
		if (socket_core != INVALID_SOCKET)
		{
			SOCKADDR_IN  _addr_in;
			size_t      _size = 0;
			void* _data = nullptr;

			int _addr_in_size = sizeof(_addr_in);
			
			if (recvfrom(socket_core, reinterpret_cast<LPSTR>(&_size), sizeof(size_t), NULL, reinterpret_cast<SOCKADDR*>(&_addr_in), &_addr_in_size) == SOCKET_ERROR)
				return Error;
		
			_data = new BYTE[_size];

			if(recvfrom(socket_core, reinterpret_cast<LPSTR>(_data), _size, NULL, reinterpret_cast<SOCKADDR*>(&_addr_in), &_addr_in_size) == SOCKET_ERROR)
				return Error;
			
			packet.Append(_data, _size);

			delete[] _data;
			
			address = IpAddress(ntohl(_addr_in.sin_addr.s_addr));
			port = ntohs(_addr_in.sin_port);
		}
		else return Error;
		*/

		SOCKADDR_IN  _addr_in;
		int _addr_in_size = sizeof(_addr_in);
		void* _data = new BYTE[size];

		if (recvfrom(socket_core, reinterpret_cast<LPSTR>(_data), size, NULL, reinterpret_cast<SOCKADDR*>(&_addr_in), &_addr_in_size) == SOCKET_ERROR)
			return Error;

		return Done;
	}

} // namespace net 