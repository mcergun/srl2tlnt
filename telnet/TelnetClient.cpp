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

        return ret;
}