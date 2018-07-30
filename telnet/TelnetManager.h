#ifndef _TELNET_MANAGER_
#define _TELNET_MANAGER_
#include <sys/socket.h>
#include <netinet/in.h>
#include <TelnetProtocol.h>

class TelnetManager
{
public:
	int Initialize(unsigned short port);
	inline int SendPacket();
	inline int SendPacket(TelnetBuffer &packet);
	inline int SendPacket(TelnetBuffer &packet, sockaddr_in &remote);
	int SendWill(TelnetOptions opt);
	int SendDo(TelnetOptions opt);
	int SendWont(TelnetOptions opt);
	int SendDont(TelnetOptions opt);
private:
	TelnetBuffer Packet;
	sockaddr_in RemoteHost;
	int sd = -1;
	bool Initialized = false;
};

#endif