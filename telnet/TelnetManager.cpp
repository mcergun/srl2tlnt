#include <TelnetManager.h>

void TelnetManager::AddOption(TelnetOptions opt)
{
	SupportedOptions.push_back(opt);
}

int TelnetManager::SendPacket()
{
	return SendPacket(Packet, RemoteHost);
}

int TelnetManager::SendPacket(TelnetPacket &packet)
{
	return SendPacket(packet, RemoteHost);
}

int TelnetManager::SendPacket(TelnetPacket &packet, sockaddr_in &remote)
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
	TelnetCommandPacket neg(TlntCmd_WILL, opt);

	return SendPacket(neg);
}

int TelnetManager::SendDo(TelnetOptions opt)
{
	TelnetCommandPacket neg(TlntCmd_DO, opt);

	return SendPacket(neg);
}

int TelnetManager::SendWont(TelnetOptions opt)
{
	TelnetCommandPacket neg(TlntCmd_WONT, opt);

	return SendPacket(neg);
}

int TelnetManager::SendDont(TelnetOptions opt)
{
	TelnetCommandPacket neg(TlntCmd_DONT, opt);

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

TelnetCommands TelnetManager::GetPacketCommand(TelnetPacket &packet)
{
	TelnetCommands cmd = TlntCmd_RAW;
	if (packet.Buffer[0] == TlntCmd_IAC)
	{
		if (packet.Buffer[1] >= TlntCmd_SE &&
			packet.Buffer[1] <= TlntCmd_DONT)
		{
			cmd = static_cast<TelnetCommands>(packet.Buffer[1]);
		}
	}
	
	return cmd;
}

int TelnetManager::HandlePacket(TelnetPacket &packet)
{
	ssize_t idx = 0;
	TelnetCommands cmd = TlntCmd_Invalid;
	TelnetPacket pck(packet);
	while (cmd != TlntCmd_RAW && idx < (packet.Size + 3))
	{
		cmd = GetPacketCommand(pck);
		if (cmd != TlntCmd_RAW && cmd != TlntCmd_Invalid)
		{
			pck = TelnetPacket(pck.Buffer + 3, pck.Size - 3);
		}
	}
	return 0;
}
