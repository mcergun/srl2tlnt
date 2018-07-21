#include <iostream>
#include <string>
#include <serial/Serial.h>

int main(int argc, char **argv)
{
	const std::string deviceName = "/dev/pts/3";

	Serial srl = Serial(deviceName, 115200, 8, 'N', 1);

	if (srl.Open() == 0)
	{
		std::cout << "Device is opened successfully" << std::endl;
	}

	while (1)
	{
		bool readSuccessful = false;
		// char readChar = srl.ReadChar(readSuccessful);
		// if (readSuccessful)
		// {
		// 	std::cout << readChar;
		// }
		char buf[1024];
		int readLen = sizeof(buf);
		char readChar = srl.ReadBuf(buf, readLen, readSuccessful);
		if (readSuccessful)
		{
			std::cout << buf;
			std::cout.flush();
		}
		delay(100);
	}

	if (srl.IsOpened())
	{
		std::cout << "Closing device" << std::endl;
		srl.Close();
	}

	return 0;
}