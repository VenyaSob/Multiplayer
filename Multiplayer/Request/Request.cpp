
/////////////////////////////////////////
// Headers			    			   //
/////////////////////////////////////////
                                       //
#include "Request.h"			       //
                                       //
/////////////////////////////////////////


namespace mp
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    // Global operator overloading  														    //
    //////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////
    net::DataPacket& operator <<(net::DataPacket& packet, Request request)             //
    {
        return packet << request;
    }


    /////////////////////////////////////////////////////////////////////////////////////
    net::DataPacket& operator >>(net::DataPacket& packet, Request& request)            //
    {
        UINT32 _request;
        packet >> _request;
        request = static_cast<Request>(_request);
        
        return packet;
    }

} // namespace mp