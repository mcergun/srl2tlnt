#ifndef _TELNET_PROTOCOL_H_
#define _TELNET_PROTOCOL_H_

constexpr ssize_t BUFFER_SIZE = 1024;

enum TelnetCommands
{
	TlntCmd_SE = 240,
	TlntCmd_NOP = 241,
	TlntCmd_DM = 242,
	TlntCmd_BRK = 243,
	TlntCmd_IP = 244,
	TlntCmd_AO = 245,
	TlntCmd_AYT = 246,
	TlntCmd_EC = 247,
	TlntCmd_EL = 248,
	TlntCmd_GA = 249,
	TlntCmd_SB = 250,
	TlntCmd_WILL = 251,
	TlntCmd_WONT = 252,
	TlntCmd_DO = 253,
	TlntCmd_DONT = 254,
	TlntCmd_IAC = 255,
};

enum TelnetOptions
{
	TlntOpt_BinaryTransmission = 0,
	TlntOpt_Echo = 1,
	TlntOpt_Reconnection = 2,
	TlntOpt_SuppressGoAhead = 3,
	TlntOpt_MessageSize = 4,
	TlntOpt_Status = 5,
	TlntOpt_TimingMark = 6,
	TlntOpt_RemoteTransEcho = 7,
	TlntOpt_LineWidth = 8,
	TlntOpt_PageSize = 9,
	TlntOpt_CarriageReturnDisposition = 10,
	TlntOpt_HorizontalTabStops = 11,
	TlntOpt_HorizontalTabDisposition = 12,
	TlntOpt_FormfeedDisposition = 13,
	TlntOpt_VerticalTabstops = 14,
	TlntOpt_VerticalTabDisposition = 15,
	TlntOpt_LinefeedDisposition = 16,
	TlntOpt_ExtendedASCII = 17,
	TlntOpt_Logout = 18,
	TlntOpt_ByteMacro = 19,
	TlntOpt_DataEntryTerminal = 20,
	TlntOpt_SUPDUP = 21,
	TlntOpt_SUPDUPOutput = 22,
	TlntOpt_SendLocation = 23,
	TlntOpt_TerminalType = 24,
	TlntOpt_EndofRecord = 25,
	TlntOpt_TACACSUserId = 26,
	TlntOpt_OutputMarking = 27,
	TlntOpt_TerminalLocationNumber = 28,
	TlntOpt_Telnet3270Regime = 29,
	TlntOpt_X3PAD = 30,
	TlntOpt_NegotiateWindowSize = 31,
	TlntOpt_TerminalSpeed = 32,
	TlntOpt_RemoteFlowControl = 33,
	TlntOpt_Linemode = 34,
	TlntOpt_XDisplayLocation = 35,
	TlntOpt_EnvironmentOption = 36,
	TlntOpt_AuthenticationOption = 37,
	TlntOpt_EncryptionOption = 38,
	TlntOpt_NewEnvironmentOption = 39,
	TlntOpt_TN3270E = 40,
	TlntOpt_XAUTH = 41,
	TlntOpt_ExtendedOptionsList = 255,
};

struct TelnetBuffer
{
public:
	char Buffer[BUFFER_SIZE] = {0};
	ssize_t Size;
};

struct TelnetNegotiationCmd : public TelnetBuffer
{
	TelnetNegotiationCmd(TelnetCommands cmd, TelnetOptions opt)
	{
		Buffer[0] = TlntCmd_IAC;
		Buffer[1] = cmd;
		Buffer[2] = opt;
		Size = 3;
	}

	void SetCommand(TelnetCommands cmd)
	{
		Buffer[1] = cmd;
	}

	void SetOption(TelnetOptions opt)
	{
		Buffer[2] = opt;
	}

	TelnetCommands GetCommand()
	{
		return static_cast<TelnetCommands>(Buffer[1]);
	}

	TelnetOptions GetOption()
	{
		return static_cast<TelnetOptions>(Buffer[2]);
	}
};

#endif