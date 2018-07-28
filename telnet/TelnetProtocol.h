#ifndef _TELNET_PROTOCOL_H_
#define _TELNET_PROTOCOL_H_

constexpr ssize_t BUFFER_SIZE = 1024;

enum TelnetCommands
{
	TelnetCommand_SE = 240,
	TelnetCommand_NOP = 241,
	TelnetCommand_DM = 242,
	TelnetCommand_BRK = 243,
	TelnetCommand_IP = 244,
	TelnetCommand_AO = 245,
	TelnetCommand_AYT = 246,
	TelnetCommand_EC = 247,
	TelnetCommand_EL = 248,
	TelnetCommand_GA = 249,
	TelnetCommand_SB = 250,
	TelnetCommand_WILL = 251,
	TelnetCommand_WONT = 252,
	TelnetCommand_DO = 253,
	TelnetCommand_DONT = 254,
	TelnetCommand_IAC = 255,
};

struct TelnetBuffer
{
public:
	ssize_t Size;
	char Buffer[BUFFER_SIZE];
};

struct TelnetCommandBuffer : public TelnetBuffer
{
public:
	TelnetCommands IAC()
	{
		return static_cast<TelnetCommands> (Buffer[0]);
	}

	TelnetCommands CMD()
	{
		return static_cast<TelnetCommands> (Buffer[1]);
	}

	char * OptionalBuffer()
	{
		return &(Buffer[2]);
	}

	ssize_t OptionalBufferSize()
	{
		return Size - 2;
	}
};

#endif