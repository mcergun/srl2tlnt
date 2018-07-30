#include <TelnetManager.h>

int TelnetManager::Initialize(unsigned short port)
{
	int ret = socket(AF_INET, SOCK_STREAM, 0);
	if (ret >= 0)
	{
		sockaddr_in local;
		sd = ret;
#ifndef _DEBUG
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		ret = bind(sd, reinterpret_cast<sockaddr *>(&local),
			sizeof(local));
#else
#endif
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		ret = connect(sd, reinterpret_cast<sockaddr *>(&local),
			sizeof(local));
	}
	return ret;
}

int TelnetManager::SendPacket()
{
	return SendPacket(Packet, RemoteHost);
}

int TelnetManager::SendPacket(TelnetBuffer &packet)
{
	return SendPacket(packet, RemoteHost);
}

int TelnetManager::SendPacket(TelnetBuffer &packet, sockaddr_in &remote)
{
	int ret = sendto(sd, packet.Buffer, packet.Size, 0,
		reinterpret_cast<sockaddr *>(&remote), sizeof(remote));
	return ret;
}

int TelnetManager::SendWill(TelnetOptions opt)
{
	TelnetNegotiationCmd neg(TlntCmd_WILL, opt);

	return SendPacket(neg);
}

int TelnetManager::SendDo(TelnetOptions opt)
{
	TelnetNegotiationCmd neg(TlntCmd_DO, opt);

	return SendPacket(neg);
}

int TelnetManager::SendWont(TelnetOptions opt)
{
	TelnetNegotiationCmd neg(TlntCmd_WONT, opt);

	return SendPacket(neg);
}

int TelnetManager::SendDont(TelnetOptions opt)
{
	TelnetNegotiationCmd neg(TlntCmd_DONT, opt);

	return SendPacket(neg);
}
