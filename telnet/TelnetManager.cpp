#include <TelnetManager.h>

void TelnetManager::AddOption(TelnetOptions opt)
{
	SupportedOptions.push_back(opt);
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
	int ret = -1;
	if (Initialized)
	{
		ret = send(sd, packet.Buffer, packet.Size, 0);
	}
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

int TelnetManager::Initialize()
{
	sd = socket(AF_INET, SOCK_STREAM, 0);
	// if (ret >= 0)
	// {
	// 	sockaddr_in local;
	// 	sd = ret;
	// 	Port = port;
	// 	local.sin_family = AF_INET;
	// 	local.sin_port = htons(port);
	// 	local.sin_addr.s_addr = htonl(INADDR_ANY);
	// 	ret = bind(sd, reinterpret_cast<sockaddr *>(&local),
	// 		sizeof(local));
	// }
	// Initialized = (ret == 0);
	return sd;
}

TelnetCommands TelnetManager::GetPacketCommand(TelnetBuffer packet)
{
	TelnetCommands cmd = TlntCmd_RAW;
	if (packet.Buffer[0] == TlntCmd_IAC)
	{

	}
	
	return cmd;
}
