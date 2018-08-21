#include <iostream>
#include <iomanip>
#include <cstring>
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

struct TelnetPacket
{
        TelnetPacket(void *buf, size_t size) :
                Buf(reinterpret_cast<unsigned char *>(buf)), Size(size)
        {

        }

        TelnetPacket() :
                Size(0), IsOwner(true)
        {
                Buf = new unsigned char[DEF_BUF_SIZE];
                std::memset(Buf, 0, DEF_BUF_SIZE);
        }

        ~TelnetPacket()
        {
                if (IsOwner)
                {
                        delete[] Buf;
                        IsOwner = false;
                }
                Size = 0;
                Buf = nullptr;
        }

        size_t AppendPacket(TelnetPacket &packet)
        {
                std::memcpy(Buf + Size, packet.Buf, packet.Size);
                Size += packet.Size;
                return Size;
        }

        size_t AppendBuffer(void *buf, size_t size)
        {
                std::memcpy(Buf + Size, buf, size);
                Size += size;
                return Size;
        }

        size_t AppendCommand(TelnetCommands cmd, TelnetOptions op)
        {
                Buf[Size++] = static_cast<unsigned char>(TlntCmd_IAC);
                Buf[Size++] = static_cast<unsigned char>(cmd);
                Buf[Size++] = static_cast<unsigned char>(op);
                return Size;
        }

        static constexpr size_t DEF_BUF_SIZE = 1024;
        unsigned char *Buf = nullptr;
        size_t Size = 0;
        bool IsOwner = false;
};

void printBuffer(void *buf, size_t count)
{
        unsigned char *cbuf = reinterpret_cast<unsigned char *>(buf);

        for (size_t i = 0; i < count; ++i)
        {
                cout << hex << static_cast<int>(cbuf[i]) << " ";
        }
        cout << endl;
}

int main(int argc, char **argv)
{
        int ret = 0;
        TelnetPacket packet;
        TelnetPacket packetS1(serv1st, sizeof(serv1st));
        packet.AppendPacket(packetS1);
        printBuffer(packet.Buf, packet.Size);
        packet.AppendBuffer(serv2nd, sizeof(serv2nd));
        printBuffer(packet.Buf, packet.Size);
        packet.AppendCommand(TlntCmd_DO, TlntOpt_ExtendedASCII);
        printBuffer(packet.Buf, packet.Size);
        cout << "Hello world!" << endl;
        return ret;
}