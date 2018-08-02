#include <arpa/inet.h>
#include <TelnetClient.h>

int TelnetClient::Initialize()
{
        int ret = TelnetManager::Initialize();
        Initialized = (ret >= 0);
        return ret;
}

int TelnetClient::Connect(std::string remoteAddress, unsigned short port)
{
        int ret = -1;
        if (Initialized)
        {
                Port = port;
                RemoteHost.sin_family = AF_INET;
                RemoteHost.sin_port = htons(Port);
                RemoteHost.sin_addr.s_addr = inet_addr(remoteAddress.c_str());
                ret = connect(sd, reinterpret_cast<sockaddr *>(&RemoteHost),
                        sizeof(RemoteHost));
        }
        if (ret == 0)
        {
                Connected = true;
        }

        return ret;
}

int TelnetClient::ReceivePacket(TelnetBuffer &packet)
{
        int ret = -1;
        if (Connected)
        {
                ret = recv(sd, packet.Buffer, packet.Size, 0);
                if (ret >= 0)
                {
                        TelnetCommands cmd = GetPacketCommand(packet);
                        if (cmd != TlntCmd_RAW)
                        {
                                TelnetBuffer packet2(packet.Buffer + 3, 3);
                                cmd = GetPacketCommand(packet2);
                        }
                }
        }
        return ret;
}