
///////////////////////////////////////
// Headers			    			 //
///////////////////////////////////////
									 //
#include "DataPacket.h"				 //
									 //  
///////////////////////////////////////


namespace net
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Constructor 																			    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	DataPacket::DataPacket() :													   //
		send_pos(0),
		read_pos(0),
		is_valid(true)
	{

	}



	//////////////////////////////////////////////////////////////////////////////////////////////
	// Destructor																			    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	DataPacket::~DataPacket()													   //
	{

	}



	//////////////////////////////////////////////////////////////////////////////////////////////
	// Methods																				    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	void DataPacket::Append(const void* data, size_t size)						   //
	{
		if ((data != nullptr) && (size > 0))
		{
			size_t _start_size = this->data.size();
			this->data.resize(_start_size + size);
			memcpy(&(this->data[_start_size]), data, size);
		}
	}


	/////////////////////////////////////////////////////////////////////////////////
	size_t DataPacket::GetReadPosition() const									   //
	{
		return read_pos;
	}


	/////////////////////////////////////////////////////////////////////////////////
	void DataPacket::Clear()													   //
	{
		data.clear();
		read_pos = 0;
		is_valid = true;
	}


	/////////////////////////////////////////////////////////////////////////////////
	const void* DataPacket::GetData() const										   //
	{
		return (!data.empty() ? &data[0] : nullptr);
	}


	/////////////////////////////////////////////////////////////////////////////////
	size_t DataPacket::GetDataSize() const										   //
	{
		return data.size();
	}


	/////////////////////////////////////////////////////////////////////////////////
	bool DataPacket::EndOfPacket() const										   //
	{
		return (read_pos >= data.size());
	}



	//////////////////////////////////////////////////////////////////////////////////////////////
	// Protected methods																	    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	const void* DataPacket::OnSend(size_t& size)								   //
	{
		size = GetDataSize();
		return GetData();
	}


	/////////////////////////////////////////////////////////////////////////////////
	void DataPacket::OnReceive(const void* data, size_t size)					   //
	{
		Append(data, size);
	}



	//////////////////////////////////////////////////////////////////////////////////////////////
	// Private method																		    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	bool DataPacket::CheckSize(size_t size)										   //
	{
		is_valid = is_valid && ((read_pos + size) <= data.size());

		return is_valid;
	}



	//////////////////////////////////////////////////////////////////////////////////////////////
	// Overloading operators																    //
	//////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	DataPacket::operator BoolType() const										   //
	{
		return (is_valid ? &DataPacket::CheckSize : nullptr);
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(bool& data)								   //
	{
		UINT8 _value;

		if (*this >> _value)
			data = (_value != 0);

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(INT8& data)								   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const INT8*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(UINT8& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const UINT8*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(INT16& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const INT16*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(UINT16& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const UINT16*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(INT32& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const INT32*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(UINT32& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const UINT32*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(DWORD& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const DWORD*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(INT64& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			const UINT8* _bytes = reinterpret_cast<const UINT8*>(&(this->data[read_pos]));

			data =
				(static_cast<INT64>(_bytes[0]) << 56) |
				(static_cast<INT64>(_bytes[1]) << 48) |
				(static_cast<INT64>(_bytes[2]) << 40) |
				(static_cast<INT64>(_bytes[3]) << 32) |
				(static_cast<INT64>(_bytes[4]) << 24) |
				(static_cast<INT64>(_bytes[5]) << 16) |
				(static_cast<INT64>(_bytes[6]) << 8) |
				(static_cast<INT64>(_bytes[7]));

			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(UINT64& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			const UINT8* _bytes = reinterpret_cast<const UINT8*>(&(this->data[read_pos]));

			data =
				(static_cast<UINT64>(_bytes[0]) << 56) |
				(static_cast<UINT64>(_bytes[1]) << 48) |
				(static_cast<UINT64>(_bytes[2]) << 40) |
				(static_cast<UINT64>(_bytes[3]) << 32) |
				(static_cast<UINT64>(_bytes[4]) << 24) |
				(static_cast<UINT64>(_bytes[5]) << 16) |
				(static_cast<UINT64>(_bytes[6]) << 8) |
				(static_cast<UINT64>(_bytes[7]));

			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(float& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const float*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(double& data)							   //
	{
		if (CheckSize(sizeof(data)))
		{
			data = *reinterpret_cast<const double*>(&(this->data[read_pos]));
			read_pos += sizeof(data);
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(char* data)								   //
	{
		UINT32 _length = 0;
		*this >> _length;

		if ((_length > 0) && CheckSize(_length))
		{
			memcpy(data, &(this->data[read_pos]), _length);
			data[_length] = '\0';

			read_pos += _length;
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(std::string& data)						   //
	{
		UINT32 _length = 0;
		*this >> _length;

		data.clear();

		if ((_length > 0) && CheckSize(_length))
		{
			data.assign(&(this->data[read_pos]), _length);

			read_pos += _length;
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(wchar_t* data)							   //
	{
		UINT32 _length = 0;
		UINT32 _character = 0;

		*this >> _length;

		if ((_length > 0) && CheckSize(_length * sizeof(UINT32)))
		{
			for (register UINT32 cnt = 0; cnt < _length; cnt++)
			{
				_character = 0;
				*this >> _character;
				data[cnt] = static_cast<wchar_t>(_character);
			}

			data[_length] = L'\0';
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator >>(std::wstring& data)						   //
	{
		UINT32 _length = 0;
		UINT32 _character = 0;

		*this >> _length;

		data.clear();

		if ((_length > 0) && CheckSize(_length * sizeof(UINT32)))
		{
			for (register UINT32 cnt = 0; cnt < _length; cnt++)
			{
				_character = 0;
				*this >> _character;
				data += static_cast<wchar_t>(_character);
			}
		}

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(bool data)								   //
	{
		*this << static_cast<UINT8>(data);

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(INT8 data)								   //
	{
		Append(&data, sizeof(data));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(UINT8 data)								   //
	{
		Append(&data, sizeof(data));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(INT16 data)								   //
	{
		INT16 _toWrite = data;
		Append(&_toWrite, sizeof(_toWrite));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(UINT16 data)							   //
	{
		UINT16 _toWrite = data;
		Append(&_toWrite, sizeof(_toWrite));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(INT32 data)								   //
	{
		INT32 _toWrite = data;
		Append(&_toWrite, sizeof(_toWrite));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(UINT32 data)							   //
	{
		UINT32 _toWrite = data;
		Append(&_toWrite, sizeof(_toWrite));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(DWORD data)								   //
	{
		DWORD _toWrite = data;
		Append(&_toWrite, sizeof(_toWrite));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(INT64 data)								   //
	{
		UINT8 _toWrite[] =
		{
			static_cast<UINT8>((data >> 56) & 0xFF),
			static_cast<UINT8>((data >> 48) & 0xFF),
			static_cast<UINT8>((data >> 40) & 0xFF),
			static_cast<UINT8>((data >> 32) & 0xFF),
			static_cast<UINT8>((data >> 24) & 0xFF),
			static_cast<UINT8>((data >> 16) & 0xFF),
			static_cast<UINT8>((data >> 8) & 0xFF),
			static_cast<UINT8>((data) & 0xFF)
		};

		Append(&_toWrite, sizeof(_toWrite));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(UINT64 data)							   //
	{
		UINT64 _toWrite[] =
		{
			static_cast<UINT8>((data >> 56) & 0xFF),
			static_cast<UINT8>((data >> 48) & 0xFF),
			static_cast<UINT8>((data >> 40) & 0xFF),
			static_cast<UINT8>((data >> 32) & 0xFF),
			static_cast<UINT8>((data >> 24) & 0xFF),
			static_cast<UINT8>((data >> 16) & 0xFF),
			static_cast<UINT8>((data >> 8) & 0xFF),
			static_cast<UINT8>((data) & 0xFF)
		};

		Append(&_toWrite, sizeof(_toWrite));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(float data)								   //
	{
		Append(&data, sizeof(data));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(double data)							   //
	{
		Append(&data, sizeof(data));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(const char* data)						   //
	{
		UINT32 _length = static_cast<UINT32>(strlen(data));
		*this << _length;

		Append(data, _length * sizeof(char));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(const std::string& data)				   //
	{
		UINT32 _length = static_cast<UINT32>(data.size());
		*this << _length;

		if (_length > 0)
			Append(data.c_str(), _length * sizeof(std::string::value_type));

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(const wchar_t* data)					   //
	{
		UINT32 _length = static_cast<UINT32>(wcslen(data));
		*this << _length;

		for (const wchar_t* c = data; *c != L'\0'; c++)
			*this << static_cast<UINT32>(*c);

		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////////
	DataPacket& DataPacket::operator <<(const std::wstring& data)				   //
	{
		UINT32 _length = static_cast<UINT32>(data.size());
		*this << _length;

		if (_length > 0)
		{
			for (register std::wstring::const_iterator c = data.begin(); c != data.end(); c++)
				*this << static_cast<UINT32>(*c);
		}

		return *this;
	}

} // namespace net
