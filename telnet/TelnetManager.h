#ifndef _TELNET_MANAGER_
#define _TELNET_MANAGER_
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <TelnetProtocol.h>

class TelnetManager
{
public:
	void AddOption(TelnetOptions opt);
	inline int SendPacket();
	inline int SendPacket(TelnetBuffer &packet);
	inline int SendPacket(TelnetBuffer &packet, sockaddr_in &remote);
	int SendWill(TelnetOptions opt);
	int SendDo(TelnetOptions opt);
	int SendWont(TelnetOptions opt);
	int SendDont(TelnetOptions opt);
protected:
	TelnetBuffer Packet;
	sockaddr_in RemoteHost;
	std::vector<TelnetOptions> SupportedOptions = std::vector<TelnetOptions>();
	int sd = -1;
	unsigned short Port = 4023;
	bool Initialized = false;

	virtual int Initialize();
	TelnetCommands GetPacketCommand(TelnetBuffer packet);
};

#endif