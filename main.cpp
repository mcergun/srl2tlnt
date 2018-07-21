#include <iostream>
#include <srllib/rs232.h>

int main(int argc, char **argv)
{
	std::cout << "Hello World!" << std::endl;

	int ret = 0;
	ret = comEnumerate();

	std::cout << "Number of available ports " << ret << std::endl;

	for (int i = 0; i < ret; ++i)
	{
		std::cout << i << ", " << comGetInternalName(i) << std::endl;
	}

	return 0;
}