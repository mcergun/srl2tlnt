#include <iostream>
#include <iomanip>
#include <cstring>
#include <AssertMacros.h>
#include <TelnetProtocol.h>

using namespace std;

unsigned char recvbuf[1024] = {0};
unsigned char sendbuf[1024] = {0};

// first message from client
// 0000   ff fd 03 ff fb 18 ff fb 1f ff fb 20 ff fb 21 ff
// 0010   fb 22 ff fb 27 ff fd 05 ff fb
unsigned char cli1st[] = { 0xff, 0xfd, 0x03, 0xff, 0xfb, 0x18, 0xff, 0xfb, 0x1f, 0xff,
        0xfb, 0x20, 0xff, 0xfb, 0x21, 0xff, 0xfb, 0x22, 0xff, 0xfb, 0x27, 0xff,
        0xfd, 0x05, 0xff, 0xfb };

// first answer from server
// 0000   ff fd 18 ff fd 20 ff fd 23 ff fd 27
unsigned char serv1st[] = { 0xff, 0xfd, 0x18, 0xff, 0xfd, 0x20, 0xff, 0xfd, 0x23, 0xff,
        0xfd, 0x27 };

// second answer from server
// 0000   ff fb 03 ff fd 1f ff fd 21 ff fe 22 ff fb 05 ff
// 0010   fa 20 01 ff f0 ff fa 23 01 ff f0 ff fa 27 01 ff
// 0020   f0 ff fa 18 01 ff f0
unsigned char serv2nd[] = {0xff, 0xfb, 0x03, 0xff, 0xfd, 0x1f, 0xff, 0xfd, 0x21, 0xff,
        0xfe, 0x22, 0xff, 0xfb, 0x05, 0xff, 0xfa, 0x20, 0x01, 0xff, 0xf0, 0xff,
        0xfa, 0x23, 0x01, 0xff, 0xf0, 0xff, 0xfa, 0x27, 0x01, 0xff, 0xf0, 0xff,
        0xfa, 0x18, 0x01, 0xff, 0xf0 };

void printBuffer(void *buf, size_t count)
{
        unsigned char *cbuf = reinterpret_cast<unsigned char *>(buf);

        for (size_t i = 0; i < count; ++i)
        {
                cout << hex << static_cast<int>(cbuf[i]) << " ";
        }
        cout << endl;
}

// just return command count for now
size_t ProcessBuffer(void *buf, size_t count)
{
        unsigned char *cbuf = reinterpret_cast<unsigned char *>(buf);
        size_t cmdCount = 1;
        size_t startingIdx = 0;
        bool isCommand = false;

        if (ToTelnetCommand(cbuf[0]) == TlntCmd_IAC)
        {
                isCommand = true;
        }

        for (size_t i = 1; i < count; ++i)
        {
                if (ToTelnetCommand(cbuf[i]) == TlntCmd_IAC)
                {
                        if (ToTelnetCommand(cbuf[i + 1]) != TlntCmd_IAC)
                        {
                                // another command starts here
                                printBuffer(cbuf + startingIdx, i - startingIdx);
                                startingIdx = i;
                                cmdCount++;
                        }
                }
        }
        printBuffer(cbuf + startingIdx, count - startingIdx);
        return cmdCount;
}

int main(int argc, char **argv)
{
        int ret = 0;
        size_t packetSize = 0;
        size_t cmdCount = 0;
        TelnetPacket packet;
        TelnetPacket packetS1(serv1st, sizeof(serv1st));
        packet.AppendPacket(packetS1);
        packetSize += sizeof(serv1st);
        cmdCount = ProcessBuffer(packet.Buf, packet.Size);
        ASSERT_TRUE(packet.Size == packetSize);
        ASSERT_TRUE(cmdCount == 4);
        printBuffer(packet.Buf, packet.Size);

        packet.AppendBuffer(serv2nd, sizeof(serv2nd));
        packetSize += sizeof(serv2nd);
        cmdCount = ProcessBuffer(packet.Buf, packet.Size);
        ASSERT_TRUE(packet.Size == packetSize);
        ASSERT_TRUE(cmdCount == 17);
        printBuffer(packet.Buf, packet.Size);

        packet.AppendCommand(TlntCmd_DO, TlntOpt_ExtendedASCII);
        packetSize += 3;
        cmdCount = ProcessBuffer(packet.Buf, packet.Size);
        ASSERT_TRUE(packet.Size == packetSize);
        ASSERT_TRUE(cmdCount == 18);
        printBuffer(packet.Buf, packet.Size);

        cout << "Hello world!" << endl;
        return ret;
}