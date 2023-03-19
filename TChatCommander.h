#pragma once

class CTChatCommander
{
public:
	/// ��� ����
	enum CmdEnum
	{
		CMD_OPERATOR_CHAT_BAN,			///< ä�� ����
		CMD_OPERATOR_TELEPORT_POS,		///< Teleport
		CMD_OPERATOR_TELEPORT_TARGET,
		CMD_OPERATOR_GIFT,				///< GM�� �����ֱ�.
		CMD_MSG_COUNT
	};

	enum
	{
		CHAT_BAN_MAX_TIME = 30000,
	};

public:
	static const DWORD CMD_STRING[];

public:
	/// ä�� Ŀ�ǵ� �ν��Ͻ��� ��´�.
	static CTChatCommander* GetInstance();

	/// ä�� �޽����� ���� �޽��� ��� �̺�Ʈ�� ó���Ѵ�.
	static CString OnMessengerCmdByChatMsg(const CString& strCMD, const VECTORSTRING& vPARAM, DWORD dwUSER);
	/// ä�� �޽��� Ŀ�ǵ带 ����Ѵ�.
	static void RegChatCmds();

public:
	/// ä�� ���� ����� ������.
	void DoMessengerCommand(CmdEnum eCmd, const VECTORSTRING& vPARAM);
	void ChatSysMSG( const CString& strMSG);

protected:
	

protected:
	CTChatCommander(void);
};
