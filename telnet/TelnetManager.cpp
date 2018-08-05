#include <TelnetManager.h>
#include <iostream>

void TelnetManager::AddOption(TelnetOptions opt)
{
	SupportedOptions.push_back(opt);
}

int TelnetManager::SendPacket()
{
	return SendPacket(SendPkt, RemoteHost);
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
	TelnetCommands cmd = TlntCmd_Invalid;
	if (packet.Size > 0)
	{
		if (packet.Buffer[0] == TlntCmd_IAC)
		{
			if (packet.Buffer[1] >= TlntCmd_SE &&
				packet.Buffer[1] <= TlntCmd_DONT)
			{
				cmd = static_cast<TelnetCommands>(packet.Buffer[1]);
			}
		}
		else
		{
			cmd = TlntCmd_RAW;
		}
	}
	
	return cmd;
}

TelnetPacket TelnetManager::GetSubPacket(TelnetPacket &packet)
{
	TelnetCommands cmd = GetPacketCommand(packet);
	if (cmd != TlntCmd_RAW)
	{
		return TelnetCommandPacket(packet.Buffer);
	}
	else
	{
		return packet;
	}
}

int TelnetManager::HandlePacket(TelnetPacket &packet)
{
	TelnetCommands cmd = TlntCmd_RAW;
	do
	{
		cmd = GetPacketCommand(packet);
		switch (cmd)
		{
		case TlntCmd_RAW:
			HandleSubPacket(packet);
			break;
		case TlntCmd_SE:
		case TlntCmd_NOP:
		case TlntCmd_DM:
		case TlntCmd_BRK:
		case TlntCmd_IP:
		case TlntCmd_AO:
		case TlntCmd_AYT:
		case TlntCmd_EC:
		case TlntCmd_EL:
		case TlntCmd_GA:
		case TlntCmd_SB:
		case TlntCmd_WILL:
		case TlntCmd_WONT:
		case TlntCmd_DO:
		case TlntCmd_DONT:
		{
			TelnetCommandPacket subPkt(packet.Buffer);
			HandleSubPacket(subPkt);
			packet = TelnetPacket(packet.Buffer + 3, packet.Size - 3);
			break;
		}
		default:
			break;
		}
	} while (cmd != TlntCmd_RAW && cmd != TlntCmd_Invalid);
	return 0;
}

int TelnetManager::HandleSubPacket(TelnetPacket &packet)
{
	// TODO: replace these test codes with actual packet handling later
	using namespace std;
	cout << "Raw packet received" << endl;
	cout << "Packet [ ";
	for (ssize_t i = 0; i < packet.Size; ++i)
	{
		cout << hex << static_cast<int>(packet.Buffer[i]) << " ";
	}
	cout << "]" << endl;
	return 0;
}

int TelnetManager::HandleSubPacket(TelnetCommandPacket &cmdPkt)
{
	// TODO: replace these test codes with actual packet handling later
	using namespace std;
	switch (cmdPkt.GetCommand())
	{
	case TlntCmd_DO:
		cout << "Telnet DO1 requested ";
		break;
	default:
		break;
	}
	cout << "Packet Cmd 0x" << hex << static_cast<int>(cmdPkt.GetCommand()) <<
		", Op 0x" << hex << static_cast<int>(cmdPkt.GetOption()) << endl;
	return 0;
}
