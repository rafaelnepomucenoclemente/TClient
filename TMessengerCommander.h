#pragma once

class CTMessengerCommander
{
public:
	/// ��� ����
	enum CmdEnum
	{
		CMD_MSG_ADD_FRIEND,			///< ģ�� ���
		CMD_MSG_DEL_FRIEND,			///< ģ�� ����
		CMD_MSG_MAKE_GROUP,			///< ģ�� �׷� ����
		CMD_MSG_DEL_GROUP,			///< ģ�� �׷� ����
		CMD_MSG_CHANGE_GROUP,		///< ģ�� �׷��� �����Ѵ�.
		CMD_MSG_NAME_GROUP,			///< ģ�� �׷� �̸��� �����Ѵ�.
		CMD_MSG_ADD_BLOCK,			///< ������ ���ܸ�Ͽ� ����Ѵ�.
		CMD_MSG_DEL_BLOCK,			///< ������ ���ܸ�Ͽ��� �����Ѵ�.
		CMD_MSG_COUNT
	};

public:
	struct FriendGroup
	{
		BYTE bGroupID;
		CString strName;
	};
	
	struct FriendMember
	{
		DWORD dwCharID;
		CString strName;
		BYTE bLevel;
		BYTE bGroup;
		BYTE bClass;
		BYTE bConnected;
		DWORD dwRegion;
	};

	typedef std::vector<CTMessengerCommander::FriendMember*> VTFRIENDMEMBER;
	typedef std::map< BYTE, VTFRIENDMEMBER > TMAPLINKGROUPMEMBER;

public:
	static const DWORD CMD_STRING[];

protected:
	CString m_strReqTarget;

public:
	/// �޽��� Ŀ�ǵ� �ν��Ͻ��� ��´�.
	static CTMessengerCommander* GetInstance();

	/// ä�� �޽����� ���� �޽��� ��� �̺�Ʈ�� ó���Ѵ�.
	static CString OnMessengerCmdByChatMsg(const CString& strCMD, const VECTORSTRING& vPARAM, DWORD dwUSER);
	/// ä�� �޽��� Ŀ�ǵ带 ����Ѵ�.
	static void RegChatCmds();

public:
	/// �޽��� ���� ����� ������.
	void DoMessengerCommand(CmdEnum eCmd, const CString& strParam1="", const CString& strParam2="");

public:
	/// ģ�� ����� �޴´�.
	void OnFriendlist(
		BYTE bGroupCount,
		FriendGroup* pGroups,
		BYTE bFriendCount,
		FriendMember* pFriends,
		TMAPLINKGROUPMEMBER& );

	/// ģ�� ����� ��û�Ѵ�.
	void DoAddFriend(const CString& strFriend);
	/// ģ�� ��� ��û�� ���� ������ �޾� ó���Ѵ�.
	void OnFriendInvite(const CString& strInviter);
	/// ģ�� ��û�� ���� ���� ������.
	void DoFriendInviteAnswer(BYTE bReply);
	/// ģ�� ��� ��û�� ó���Ѵ�.
	void OnAddFriend(BYTE bResult, FriendMember* pFriend);

	/// ģ�� ���Ÿ� ��û�Ѵ�.
	void DoEraseFriend(DWORD dwCharID);
	/// ģ�� ���� ��û�� ó���Ѵ�.
	void OnEraseFriend(DWORD dwCharID);

	/// ģ���� ���� ���θ� ó���Ѵ�.
	void OnConnectFriend(BYTE bResult, const CString& strName, DWORD dwRegion);
	/// ģ���� ���� ������ ó���Ѵ�.
	void OnChangeFriendRegion(const CString& strName, DWORD dwRegion);

	/// ģ�� �׷� ������ ��û�Ѵ�.
	void DoMakeFriendGroup(const CString& strName);
	/// ģ�� �׷� ������ ���� ��û�� ó���Ѵ�.
	void OnMakeFriendGroup(BYTE bResult, BYTE bGroupID, const CString& strName);

	/// ģ�� �׷� ���Ÿ� ��û�Ѵ�.
	void DoEraseFriendGroup(BYTE bGroupID);
	/// ģ�� �׷� ���ſ� ���� ��û�� ó���Ѵ�.
	void OnEraseFriendGroup(BYTE bResult, BYTE bGroupID);

	/// ģ�� �׷� ������ ��û�Ѵ�.
	void DoChangeFriendGroup(DWORD dwCharID, BYTE bWantedGroup);
	/// ģ�� �׷� ���濡 ���� ��û�� ó���Ѵ�.
	void OnChangeFriendGroup(BYTE bResult, BYTE bGroup, DWORD dwCharID);

	/// ģ�� �׷�� ������ ��û�Ѵ�.
	void DoFriendGroupName(BYTE bGroup, const CString& strName);
	/// ģ�� �׷�� ���濡 ���� ��û�� ó���Ѵ�.
	void OnFriendGroupName(BYTE bResult, BYTE bGroup, const CString& strName);

	/// �׷� ��ü�� ���� �ʴ븦 ��û�Ѵ�.
	void DoInviteChatGroup(DWORD dwTMS, BYTE bGroup);
	/// Ÿ���� �ʴ븦 ��û�Ѵ�.
	void DoInviteChatTarget(DWORD dwTMS, const VECTORDWORD& vTARGET);
	/// ä�� �ʴ뿡 ���� ��û�� ó���Ѵ�.
	void OnInviteChatTarget(DWORD dwTMS, const CString& strInviter, LPMCTARGET_ARRAY pTargets);

	/// �޽��� äƮ �޽����� ������.
	void DoChat(DWORD dwTMS, const CString& strMessage);
	/// �޽��� äƮ �޽����� �����Ѵ�.
	void OnChat(DWORD dwTMS, const CString& strSender, const CString& strMessage);

	/// �޽��� äƮ ���Ḧ ��û�Ѵ�.
	void DoChatOut(CTMessengerChat* pChat);
	/// �޽��� äƮ ���Ḧ ó���Ѵ�.
	void OnChatOut(DWORD dwTMS, const CString& strTarget);

	/// �־��� ������ �����Ѵ�.
	void DoAddBlock(const CString& strTarget);
	/// �־��� ������ ������ �����Ѵ�.
	void DoDeleteBlock(const CString& strTarget);

protected:
	void ChatSysMSG( const CString& strMSG);

protected:
	CTMessengerCommander();
};















