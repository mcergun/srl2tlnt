#ifndef _TELNET_MANAGER_
#define _TELNET_MANAGER_
#include <sys/socket.h>
#include <netinet/in.h>
#include <TelnetProtocol.h>

class TelnetManager
{
public:
	int SendPacket();
	int SendPacket(TelnetBuffer &packet);
	inline int SendPacket(TelnetBuffer &packet, sockaddr_in &remote);
private:
	TelnetBuffer Packet;
	sockaddr_in RemoteHost;
	int sd;
};

#endif