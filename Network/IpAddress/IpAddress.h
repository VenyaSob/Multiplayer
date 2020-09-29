
#ifndef NETWORK_IP_ADDRESS_H
#define	NETWORK_IP_ADDRESS_H


///////////////////////////////////////
// Headers		      			     //
///////////////////////////////////////
									 //
#include "../Config/Config.h"		 //	
									 //
#include <string>					 //
#include <ostream>					 //
#include <istream>					 //
									 //
///////////////////////////////////////


namespace net
{
	class IpAddress
	{
		private:

			///////////////////////////////////////////////
			// Private member data 						 //
			///////////////////////////////////////////////

			UINT32 address;
			bool	 valid;


		public:

			///////////////////////////////////////////////
			// Data type								 //
			///////////////////////////////////////////////

			enum
			{
				BUF_SIZE = 16
			};


		public:

			///////////////////////////////////////////////
			// Static member data						 //
			///////////////////////////////////////////////

			static const IpAddress		None;
			static const IpAddress		 Any;
			static const IpAddress LocalHost;
			static const IpAddress Broadcast;


		private:

			///////////////////////////////////////////////
			// Private method		 					 //
			///////////////////////////////////////////////

			void convert(const std::string address);


		public:

			///////////////////////////////////////////////
			// Constructors 							 //
			///////////////////////////////////////////////

			IpAddress();

			IpAddress(LPCSTR address);

			IpAddress(const std::string address);

			IpAddress(UINT8 byte_1, UINT8 byte_2, UINT8 byte_3, UINT8 byte_4);

			explicit IpAddress(const UINT32 address);


		public:

			///////////////////////////////////////////////
			// Methods		 							 //
			///////////////////////////////////////////////

			std::string ToString() const;

			UINT32 ToInteger() const;


		public:

			///////////////////////////////////////////////
			// Static method		 					 //
			///////////////////////////////////////////////

			static IpAddress GetLocalAddress();


		public:

			///////////////////////////////////////////////
			// Overloading operator			             //
			///////////////////////////////////////////////

			operator bool() const;


		public:

			///////////////////////////////////////////////
			// Overloading a friendly operator           //
			///////////////////////////////////////////////

			friend bool operator <(const IpAddress left, const IpAddress right);
	};



	/////////////////////////////////////////////////////////////////////////////////
	// Global operator overloading                       	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	bool operator ==(const IpAddress left, const IpAddress right);
	
	bool operator !=(const IpAddress left, const IpAddress right);

	bool operator <(const IpAddress left, const IpAddress right);

	bool operator >(const IpAddress left, const IpAddress right);

	bool operator <=(const IpAddress left, const IpAddress right);

	bool operator >=(const IpAddress left, const IpAddress right);


	std::istream& operator >>(std::istream& stream, IpAddress& address);

	std::ostream& operator <<(std::ostream& stream, const IpAddress& address);


	/////////////////////////////////////////////////////////////////////////////////
	// Definition of the most common names		           	  	 				   //
	/////////////////////////////////////////////////////////////////////////////////

	typedef IpAddress IP_ADDRESS;
	typedef IpAddress    ADDRESS;
	typedef IpAddress	 	  IP;

} // namespace net


#endif // NETWORK_IPADDRESS_H