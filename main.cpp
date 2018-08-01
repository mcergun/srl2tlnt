#include <iostream>
#include <string>
#include <utility>
#include <thread>
#include <chrono>
#include <serial/Serial.h>
#include <telnet/TelnetClient.h>


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
	TelnetClient cli;
	cli.Initialize();
	cli.Connect("127.0.0.1", 23);
	return 0;
}