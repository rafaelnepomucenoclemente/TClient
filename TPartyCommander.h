#pragma once

class CTPartyCommander
{
public:
	/// ��� ����
	enum CmdEnum
	{
		CMD_PARTY_INVITE,				///< ��Ƽ �ʴ�
		CMD_PARTY_KICK,					///< ��Ƽ�� �߹�
		CMD_PARTY_OUT,					///< ��Ƽ ������
		CMD_CORPS_INVITE,				///< ���� �ʴ�
		CMD_ASSISTANT_INVITE,			///< �ΰ� �ʴ�
		CMD_COUNT
	};

	/// ��ɿ� ���� ���ڿ� �迭
	static const DWORD CMD_STRING[CMD_COUNT];

public:
	/// ��Ƽ Ŀ�ǵ� �ν��Ͻ��� ��´�.
	static CTPartyCommander* GetInstance();

	/// ä�� �޽����� ���� ��Ƽ ��� �̺�Ʈ�� ó���Ѵ�.
	static CString OnPartyCmdByChatMsg(const CString& strCMD, const VECTORSTRING& vPARAM, DWORD dwUSER);
	/// ä�� �޽��� Ŀ�ǵ带 ����Ѵ�.
	static void RegChatCmds();

protected:


public:
	/// ��Ƽ ���� ����� ������.
	void DoPartyCommand(CmdEnum eCmd, const CString& strParam="");

protected:
	CTPartyCommander();
};




