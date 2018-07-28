#include <TelnetManager.h>

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