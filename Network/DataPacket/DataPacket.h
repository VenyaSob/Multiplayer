
#ifndef NETWORK_DATA_PACKET_H
#define NETWORK_DATA_PACKET_H


///////////////////////////////////////
// Headers			    			 //
///////////////////////////////////////
									 //
#include "../Config/Config.h"		 //
									 //
#include <vector>					 //
#include <string>					 //
									 //
///////////////////////////////////////


namespace net
{
	class DataPacket
	{
		private:

			///////////////////////////////////////////////
			// Private data type						 //
			///////////////////////////////////////////////

			typedef bool (DataPacket::* BoolType)(size_t);


		private:

			///////////////////////////////////////////////
			// Private member data 						 //
			///////////////////////////////////////////////

			std::vector<char> data;
			size_t	      read_pos;
			size_t	      send_pos;
			bool		  is_valid;


		public:

			///////////////////////////////////////////////
			// Constructor 								 //
			///////////////////////////////////////////////

			DataPacket();


			///////////////////////////////////////////////
			// Destructor 								 //
			///////////////////////////////////////////////

			virtual ~DataPacket();


			///////////////////////////////////////////////
			// Methods		 							 //
			///////////////////////////////////////////////

			void Append(const void* data, size_t size);

			void Clear();

			size_t GetReadPosition() const;

			const void* GetData() const;

			size_t GetDataSize() const;

			bool EndOfPacket() const;


		protected:

			///////////////////////////////////////////////
			// Protected methods						 //
			///////////////////////////////////////////////

			virtual const void* OnSend(size_t& size);

			virtual void OnReceive(const void* data, size_t size);


		private:

			///////////////////////////////////////////////
			// Private Method 							 //
			///////////////////////////////////////////////

			bool CheckSize(size_t size);


		public:

			///////////////////////////////////////////////
			// Overloading operators		             //
			///////////////////////////////////////////////

			operator BoolType() const;

			DataPacket& operator >>(bool& data);

			DataPacket& operator >>(INT8& data);

			DataPacket& operator >>(UINT8& data);

			DataPacket& operator >>(INT16& data);

			DataPacket& operator >>(UINT16& data);

			DataPacket& operator >>(INT32& data);

			DataPacket& operator >>(UINT32& data);

			DataPacket& operator >>(DWORD& data);

			DataPacket& operator >>(INT64& data);

			DataPacket& operator >>(UINT64& data);

			DataPacket& operator >>(float& data);

			DataPacket& operator >>(double& data);

			DataPacket& operator >>(char* data);

			DataPacket& operator >>(std::string& data);

			DataPacket& operator >>(wchar_t* data);

			DataPacket& operator >>(std::wstring& data);

			DataPacket& operator <<(bool data);

			DataPacket& operator <<(INT8 data);

			DataPacket& operator <<(UINT8 data);

			DataPacket& operator <<(INT16 data);

			DataPacket& operator <<(UINT16 data);

			DataPacket& operator <<(INT32 data);

			DataPacket& operator <<(UINT32 data);

			DataPacket& operator <<(DWORD data);

			DataPacket& operator <<(INT64 data);

			DataPacket& operator <<(UINT64 data);

			DataPacket& operator <<(float data);

			DataPacket& operator <<(double data);

			DataPacket& operator <<(const char* data);

			DataPacket& operator <<(const std::string& data);

			DataPacket& operator <<(const wchar_t* data);

			DataPacket& operator <<(const std::wstring& data);


		private:

			///////////////////////////////////////////////
			// Overloading operators		             //
			///////////////////////////////////////////////

			bool operator ==(const DataPacket& right) const;
			bool operator !=(const DataPacket& right) const;
	};


	/////////////////////////////////////////////////////////////////////////////////
	// Definition of the most common names		           	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	typedef DataPacket DATA_PACKET;
	typedef DataPacket      PACKET;

} // namespace net


#endif // NETWORK_DATA_PACKET_H
