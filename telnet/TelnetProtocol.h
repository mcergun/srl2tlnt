#ifndef _TELNET_PROTOCOL_H_
#define _TELNET_PROTOCOL_H_

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

#endif