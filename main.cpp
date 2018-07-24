#include <iostream>
#include <string>
#include <utility>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <netinet/in.h>
#include <serial/Serial.h>
#include <telnet/TelnetProtocol.h>

char buf[1024] = { 0 };

void serialLoop(Serial &srl)
{
	char buf[1024] = { 0 };
	int readLen = sizeof(buf);
	bool success = false;
	while(1)
	{
		srl.ReadBuf(buf, readLen, success);
		if (success)
		{
			std::cout << buf;
			std::cout.flush();
			memset(buf, 0, readLen);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		readLen = sizeof(buf);
	}
}

int main(int argc, char **argv)
{
	const std::string DEF_SRL_PORT_NAME = "/dev/pts/4";
	const unsigned short DEF_TELNET_PORT = 10023;
	std::string deviceName = "";
	unsigned short telnetPort = 0;
	Serial srl;

	if (argc > 1)
	{
		deviceName = argv[1];
		if (argc > 2)
		{
			telnetPort = atoi(argv[1]);
		}
		else
		{
			telnetPort = DEF_TELNET_PORT;
		}
	}
	else
	{
		deviceName = DEF_SRL_PORT_NAME;
	}

	int sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		std::cout << "Can't create socket for telnet, exiting" << std::endl;
		return -1;
	}

	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(telnetPort);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(sd, reinterpret_cast<sockaddr *>(&local), sizeof(local));
	if (ret < 0)
	{
		std::cout << "Can't bind socket for telnet, exiting" << std::endl;
		return -1;
	}
	else
	{
		// Socket has been bound to the application
		// Initialize serial port, and listen for incoming packets
		// on both serial and telnet connections.
		srl = Serial(deviceName, 115200, 8, 'N', 1);

		if (srl.Open() == 0)
		{
			std::cout << "Device is opened successfully" << std::endl;
			std::thread thr(serialLoop, std::ref(srl));
			thr.join();
		}
		else
		{
			shutdown(sd, 2);
			close(sd);
		}
	}

	if (srl.IsOpened())
	{
		std::cout << "Closing device" << std::endl;
		srl.Close();
	}

	return 0;
}