#pragma once

class CTMessengerChat : public CTClientUIBase
{
public:
	static LP_FRAMEDESC		ms_ChatFrameDesc;

protected:
	static VTMSGCHATARRAY		ms_FreeChats;
	static TMAPMSGTOCHAT		ms_TmsActChats;
	static BOOL				ms_bShow;

public:
	/// ���ο� �޽��� ä��â�� �����Ѵ�.
	static CTMessengerChat* NewInstance(DWORD dwTmsID = 0);
	/// ������ �޽��� ä��â�� �����Ѵ�.
	static BOOL DeleteInstance(CTMessengerChat* pChat);
	/// ���� �� �ִ� ��� �޽��� ä��â�� �����Ѵ�.
	static void DeleteAllInstance();

	/// �־��� TMS ID �� ���� ä��â�� ��´�.
	static CTMessengerChat* GetChat(DWORD dwTmsID);
	/// ä�� �޽����� �����Ѵ�.
	static BOOL DoChat(CTMessengerChat* pChat, const CString& strMsg);
	/// �־��� ä��â������ �ش� Ÿ�� ������ ó���Ѵ�.
	static BOOL OnOutChatTarget(CTMessengerChat* pChat, const CString& strOutTarget);

	/// ���� Ȱ�� â�� ���̴��� ���θ� ��´�.
	static BOOL IsAllVisible()	{ return ms_bShow; }
	/// ��� Ȱ�� â�� ���̰ų� �Ⱥ��̰� �Ѵ�.
	static void ShowAll(BOOL bShow);
	
	/// ���� Ȱ��ȭ�� ä��â�� ��´�.
	static CTMessengerChat* GetCurMsgChat();
	/// ��� ä��â �߿��� ���� Ȱ��ȭ�� �����͸� ��´�.
	static TEdit* GetCurMsgChatEdit();
    
	/// P2P ������ ä��â�� �ش� Ÿ���� ���� â�� ��´�.
	static CTMessengerChat* FindInP2PByTarget(const CString& strTarget);

protected:
	CTClientGame*			m_pGame;
	CTMessengerCommander*	m_pCmd;
	
	DWORD					m_dwTmsID;
	CString					m_strMyName;
	MCTARGET_ARRAY			m_vChatTargets;

	TComponent*				m_pChatTitle;
	TButton*				m_pImeBtn;
	TButton*				m_pInviteBtn;
	//TButton*				m_pSendBtn;
	TButton*				m_pCloseBtn;
	TList*					m_pChatList;
	TList*					m_pChatMembers;
	TImageList*				m_pMyFace;
	//TImageList*				m_pTargetFace;
	//TComponent*				m_pTargetName;
	TMultiLineEdit*			m_pChatEdit;

public:
	/// ���� ��Ŀ���� ����Ʈ ��Ʈ���� ��´�.
	TEdit* GetCurEdit();

	/// Ÿ�ٵ��� �����Ѵ�.
	void SetTargets(LPMCTARGET_ARRAY pTargets);
	/// Ÿ���� �ϳ� �����Ѵ�.
	void SetTarget(LPMSGCHAT_TARGET pTarget);
	/// Ÿ���� �߰��Ѵ�.
	void AddTarget(LPMSGCHAT_TARGET pTarget);
	/// Ÿ���� �ϳ� �����Ѵ�.
	BOOL RemoveTarget(const CString& strTargetName);
	/// ��ü Ÿ���� �����Ѵ�.
	void RemoveAllTargets();

	/// ����� Ÿ�� ������ �ݿ���Ų��.
	void UpdateTarget();

	/// Ÿ���� ���� ��´�.
	INT GetTargetCount() const					{ return (INT)m_vChatTargets.size(); }
	/// �־��� �ε����� Ÿ���� ��´�.
	LPMSGCHAT_TARGET GetTarget(INT nIdx) const	{ return const_cast<MSGCHAT_TARGET*>(&m_vChatTargets[nIdx]); }
	/// Ÿ�� �迭�� ��´�.
	LPMCTARGET_ARRAY GetTargets() const			{ return const_cast<LPMCTARGET_ARRAY>(&m_vChatTargets); }
	
	/// �̸����� Ÿ�������� ��´�.
	LPMSGCHAT_TARGET FindTargetByName(const CString& strName);

	/// ä�� Ÿ��Ʋ�� �����Ѵ�.
	void SetChatTitle(const CString& strTarget, UINT nCnt);

	DWORD GetTmsID() const						{ return m_dwTmsID; }
	const CString& GetMyName() const			{ return m_strMyName; }

	/// �����Ϳ� �Էµ� ���뿡 ���� ������ �õ��Ѵ�.
	void TryChatMsgInEdit();
	/// ���ŵ� äƮ �޽����� ����Ѵ�.
	void OnChatMsg(const CString& strSender, const CString& strMessage);

	/// ģ�� ��Ͽ��� ���õ� ģ���� �ʴ��Ѵ�.
	BOOL InviteSelectedFriendInList();

public:
	virtual HRESULT Render(DWORD dwTickCount);
	
	virtual void EnableComponent( BOOL bEnable = TRUE);
	virtual void ShowComponent(BOOL bVisible = TRUE);
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);
	virtual void OnLButtonUp(UINT nFlags, CPoint pt);
	virtual void OnKeyDown( UINT nChar, int nRepCnt, UINT nFlags);

protected:
	void NotifyImeLocalModeChange();
	
public:
	CTMessengerChat(TComponent* pParent, LP_FRAMEDESC pDesc);
	virtual ~CTMessengerChat();
};












