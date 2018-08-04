#ifndef _TELNET_CLIENT_H
#define _TELNET_CLIENT_H

#include <string>
#include <TelnetManager.h>

class TelnetClient : public TelnetManager
{
public:
        int Initialize();
        int Connect(std::string remoteAddress, unsigned short port);
        int ReceivePacket(TelnetPacket &packet);
};

#endif