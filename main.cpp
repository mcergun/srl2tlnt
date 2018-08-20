#include <iostream>

using namespace std;

char recvbuf[1024] = {0};
char sendbuf[1024] = {0};

// first message from client
// 0000   ff fd 03 ff fb 18 ff fb 1f ff fb 20 ff fb 21 ff
// 0010   fb 22 ff fb 27 ff fd 05 ff fb 23

// first answer from server
// 0000   ff fd 18 ff fd 20 ff fd 23 ff fd 27

// second answer from server
// 0000   00 00 00 00 00 00 00 00 00 00 00 00 08 00 45 10
// 0010   00 5b 7e e6 40 00 40 06 bd a4 7f 00 00 01 7f 00
// 0020   00 01 00 17 de 6c 87 19 87 70 57 e0 4a 90 80 18
// 0030   01 56 fe 4f 00 00 01 01 08 0a 7c 26 d9 ce 7c 26
// 0040   d9 ce ff fb 03 ff fd 1f ff fd 21 ff fe 22 ff fb
// 0050   05 ff fa 20 01 ff f0 ff fa 23 01 ff f0 ff fa 27
// 0060   01 ff f0 ff fa 18 01 ff f0

int main(int argc, char **argv)
{
        int ret = 0;
        cout << "Hello world!" << endl;
        return ret;
}