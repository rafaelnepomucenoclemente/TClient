#pragma once

class CTChatFrame : public CTClientUIBase
{
public:
	enum PopupEnum
	{
		POPUP_CHATTYPE,
		POPUP_CHATFLAG_ALL,
		POPUP_CHATFLAG_NORMAL,
		POPUP_LATEST_WHISPER,
		POPUP_COUNT,
	};

public:
	static const LONG		SNAP_REACT_VALUE;					///< ä�� ����Ʈ�� ���� ���� �Ÿ�
	static const CHAR		CHAT_CMD_MARK;						///< ä�� Ŀ�ǵ� ��ũ
	static const DWORD		CHAT_FLAGS[TCHAT_FLAG_COUNT];		///< ä�� �÷��� �迭
	static const DWORD		CHAT_FLAG_STRINGS[TCHAT_FLAG_COUNT];///< ä�� �÷��� �̸� �迭
	static const DWORD		DEFAULT_CHAT_FLAGS[];				///< ����Ʈ�� ������ �⺻ ä�� �÷���
	static const BYTE		CHAT_SHOW_NEWMSG[];					///< ���ο� ä�� �޽����� ���� ���θ� �˸��� ����
	static const INT		POPUP_TO_LIST[];					///< �˾� �ε��� -  ����Ʈ �ε��� ���̺�
	static const DWORD		CHAT_MODE_CMD[];					///< ä�� ��� ���

protected:
	CTClientGame*			m_pMainGame;						///< ���� ���� ������

	TComponent*				m_pListTemplate;					///< ä�� ����Ʈ ������ ���� ���ø� ��ü
	TComponent*				m_pListTemplate2;					///< ���� ����Ʈ ������ ���� ���ø� ��ü
	
	CTChatList*				m_vLists[TCHAT_SET_COUNT];			///< ä�� ����Ʈ �迭
	CRect					m_rcDefaultList;					///< ä�� ����Ʈ�� �⺻ ��ġ�� ũ��
	CTChatTabButton*                m_Jab;

	CTChatList*				m_pNotifyList;						///< ��� ���� �޽��� ���� ����Ʈ
	CTChatList*				m_pUpgradeShowList;				///< ��ȭ ���� �޽��� ���� ����Ʈ
	DWORD					m_dwNotifyTime;						///< ���� ������ ȭ�鿡 ǥ���� ���� �ð�
	
	CTChatTabButton*		m_vTabs[TCHAT_SET_COUNT];			///< �� �迭
	CTChatTabButton*        m_TAB1;
	CRect					m_vTabRect[TCHAT_SET_COUNT];		///< ���Կ� ���� ���� ��ġ �迭
	INT						m_iTabCount;						///< ���� ����
   
	CTChatTabButton*		m_pSelectTab;						///< ���õ� ��
	CTChatTabButton*		m_pHitTab;							///< ���� �ֱٿ� Ŭ���� ��

	TComponent*				m_pChatTypeCtrl;					///< ä�� Ÿ���� ǥ���ϱ����� ��Ʈ��
	TEdit*					m_pChatEditCtrl;					///< ä�� �Է��� �ޱ����� ������ ��Ʈ��
	TEdit*					m_pChatWhisperTargetEditCtrl;	///< �Ӹ� ��� �Է��� �ޱ� ���� ������ ��Ʈ��
	BOOL					m_bChatEditON;						///< ���� ä�� �Է������� ����
	TComponent*				m_pChatEditBack;					///< ä�� �Է� ���
	TComponent*				m_pChatTabBack;
	TComponent*				m_pChatMode;

	//TButton*				m_pChatLockCtrl;					///< ä�� ����Ʈ ��/��� ��ư			
	TButton*				m_pChatImeCtrl;						///< ä�� �Է� ��� ��ư

	DWORD					m_dwTick;							///< ä��â�� ��� �̺�Ʈ�� �߻� �� �ĺ����� ����ð�.

	BYTE					m_bChatMode;						///< ���� ä�� ���
	CString					m_strChatTarget;					///< ���� �ֱ��� �Ӹ� Ÿ�� �̸�
	DWORD					m_dwChatTargetID;					///< ���� �ֱ��� �Ӹ� Ÿ�� ���̵�
	CString					m_strLastWhisper;					///< ���� ���������� ���� �Ӹ� ���
	CString					m_strCandiWhisper;				///< �Ӹ� ��� ������ (������ ��ư���� �Ӹ� ��� ���ý� ���)

	CTMiniPopupDlg*			m_vPopup[POPUP_COUNT];				///< ä�� ���� �˾� ����Ʈ

	/**
		ä�� �������� ������ ����.
		�������� ���ٴ� �ǹ̴� ����Ʈ�� ���� �̵��̳� �߰� ���Ÿ�
		�� �� ���� �Ѵٴ� ���̴�. ���� �������� ��� ���¿����� ä��
		����Ʈ�� ��� HitTest ����� �����ϰ� �ȴ�. ��, ����Ʈ�� Ŭ��
		�� �� ���� �ȴٴ� �ǹ��̴�.
	*/
	BOOL					m_bLock;

	/// ä�� �������� ȭ�鿡 ǥ������ ����
	BOOL					m_bChatFrameVisible;

	// ���� ���� �Ǵܿ� ���Ǵ� ������
	BOOL					m_bProcSnapLeft;
	BOOL					m_bProcSnapTop;
	BOOL					m_bProcSnapRight;
	BOOL					m_bProcSnapBottom;

	TMAPCHATCMD	m_FpChatCmdMap;
	STRINGQUEUE		m_queLatestWhisper;
	BOOL					m_bInitialized;

public:
	/// ä�� Ÿ�Կ� ���� ���� ��´�.
	static DWORD GetChatTypeColor(BYTE bChatMode);
	/// ä�� Ÿ�Կ� ���� ��Ī�� ��´�.
	static const CString& GetChatTypeString(BYTE bChatMode);
	/// ä�� Ÿ�Կ� ���� ��ǥ ��Ī�� ��´�.
	const CString& GetChatTypeRepresentation(BYTE bChatMode);

	/// �־��� ����Ʈ �ε����� �ش��ϴ� �˾� �ε����� ��´�.
	static INT GetPopupIndex(INT nListIndex);

public:
	/// �־��� �˾� ��ȭ���ڸ� ä�� ��� ���ÿ����� ����ϵ��� �����Ѵ�.
	void SetPopup(PopupEnum ePopup, CTMiniPopupDlg* pPopup);
	/// ä�� �˾��� ȭ�鿡 ���ų� �����.
	void ShowPopup(PopupEnum ePopup, BOOL bShow);
	/// ��� ä�� �˾��� ȭ�鿡�� �����.
	void HideAllPopup();
	void ShowAllPopup();
	/// ä�� �˾��� ���������� ���θ� ��´�.
	BOOL IsVisiblePopup(PopupEnum ePopup);

	/// ä�� �÷����� ������ �˾��� �ݿ���Ų��.
	void UpdateChatFlagToPopup();
	void SetHeightAllInnerChatList( INT nHeight );

	/**
		ä�� �������� �����Ѵ�.

		@param dwTick	��� �ð�
	*/
	void Update(DWORD dwTick);

	/**
		���� ���� �����Ѵ�. �̶� �ǰ� ��ũ�� ����Ʈ�� ȭ�鿡 ǥ�õȴ�.

		@warning	���� ���� ������ ���� ���¶�� �ش� ���� ������ �� ����.
	*/
	void ChangeSelection(CTChatTabButton* pTab);
	void ChangeSelection(TCHAT_SET);

	/// �־��� �� ���� ��ȯ�Ѵ�. �� ��ȯ�� ������ ��ȯ�� �Բ� ��ġ ��ȯ�� �ǹ��Ѵ�.
	void SwapTab(CTChatTabButton* pTab1, CTChatTabButton* pTab2);
	/// �־��� �ǰ� �׿� ��ũ�� ����Ʈ�� ������ ������ �߰��Ѵ�.
	void AddTabAndList(CTChatTabButton* pTab);
	/// �־��� �ǰ� �׿� ��ũ�� ����Ʈ�� ������ ������ ����.
	void RemoveTabAndList(CTChatTabButton* pTab);

	/**
		����Ʈ�� �ֺ��� �����Ǿ�� �ϴ��� �����ϰ� ���� �׷��ٸ�
		������ ����� ��ġ�� ��ȯ�ϴ�.

		@param pList		�������θ� ������ ����Ʈ
		@param outRect		���� �� ����� ��ġ. ��ȯ���� TRUE �� 
							��츸 ��ȿ�ϴ�.
		@return				���� �߻� ����.
	*/
	BOOL SnapList(CTChatList* pList, CRect& outRect);

	///
	void ResetSetting();

	/// ���Ʈ���� ����� ä�� �������� ���·� ���� ���¸� �����Ѵ�.
	void LoadSetting( BOOL bReset = FALSE);
	/// ���� ä�� �������� ���¸� ������Ʈ���� �����Ѵ�.
	void SaveSetting();

	/// �־��� ��ġ�� �ش��ϴ� �� ��ư�� ��´�.
	CTChatTabButton* GetHitTab(const CPoint& pt);
	/// �־��� ����Ʈ�� ��ũ�� �� ��ư�� ��´�.
	CTChatTabButton* FindTab(CTChatList* pList);

	/// �־��� ��ġ�� �ش��ϴ� ä�� ����Ʈ�� ��´�.
	CTChatList* GetHitList(const CPoint& pt);

	/// �־��� �˾��� ��ũ�� ä�� ����Ʈ�� ��´�.
	CTChatList* FindList(CTMiniPopupDlg* pPopup);

	CTChatList* FindList( DWORD dwChatFlag );

	/// ������� �Էµ� ä�� �޽����� �ʱ�ȭ�Ѵ�.
	void ResetChatMsg(BOOL bEnable);
	/// ����Ʈ�� ��� ä�� ����� �ʱ�ȭ�Ѵ�.
	void ResetChatList();
	
	/// �Ӹ� ����� �Է��Ѵ�.
	void ShowWhisperTargetInput( BOOL bShow );
	void ProcWhisperTargetInput( BOOL bCancel );
	void LoseFocusWhisperTargetInput( BOOL bCancel );

	void AddWhisperList( CString strWhisperTarget );

	/// ä�� �����ͷ� ����Ʈ ��ũ ����Ÿ�� �ִ´�.
	void InsertInfoToChatEdit(LPTQUEST pQuest);
	/// ä�� �����ͷ� ������ ��ũ ����Ÿ�� �ִ´�.
	void InsertInfoToChatEdit(LPTITEM pItem, CTClientItem* pClientItem);
	/// ä�� �������� �� ������ �־��� ���ڿ��� �����Ѵ�.
	void PushFrontMsgToEdit(const CString& strMsg);

	/// ���� �����Ϳ� �Էµ� ä�� �޽����� ó���ϰ� �����ؾ��� �޽����� ��´�.
	CString ProcChatMsgInEdit();

	/// ���� �����Ϳ� �Էµ� �޽����� �¿� ������ �����Ѵ�.	
	void TrimMsgInEdit();
	/// ���� �����Ϳ� �Էµ� �޽����� ��� �����Ѵ�.
	void ClearMsgInEdit();

	/**
		ä�� �޽����� ���������� �����Ͽ� ����Ʈ�� �� ������ ǥ���ϰ� �Ѵ�.

		@param strTYPE		ä�� Ÿ���� ��Ÿ���� ���ڿ�
		@param strNAME		�޽����� ���� ���� �̸�
		@param strMSG		ǥ���ϰ��� �ϴ� �޽���
		@param dwCOLOR		ǥ���ϰ��� �ϴ� �޽����� ��
		@param dwChatFlag	�� �޽����� Ÿ�� �÷���
		@param dwSoundID	�� �޽����� ����Ʈ�� ǥ���Ҷ� �� ���� ID 
							�ƹ� �Ҹ��� ������ �ʴ´ٸ� 0 �� �����ϸ� �ȴ�.
							�⺻���� 0 �̴�.
		@param bSoundType	���� ���� ID �� Ÿ��. (Only WAV:MEDIA_TSOUND)
		@return				������ ǥ�õǴ� �޽���
	*/
	CString ChatSysMSG(
		const CString& strTYPE,
		const CString& strNAME,
		const CString& strMSG,
		DWORD dwCOLOR,
		DWORD dwChatFlag,
		DWORD dwSoundID = 0,
		BYTE bSoundType = MEDIA_TSOUND);

	CString ChatMSG(
		const CString& strTYPE,
		const CString& strNAME,
		const CString& strMSG,
		DWORD dwCOLOR,
		DWORD dwChatFlag,
		DWORD dwSoundID,
		BYTE bSoundType,
		DWORD dwSenderID );

	/// ä�� ���������� ��Ŀ���� �����Ѵ�.
	void ForceFocus();

	/// ��� ä�� ����Ʈ�� ����� ���̰� ���� ���θ� �����Ѵ�.
	void SetHideBackgroundOfList(BOOL bHide);
	/// ������ ��� ���θ� �����Ѵ�.
	void SetLock(BOOL bLock);

	/// IME ��� ��尡 ���ŵǾ����� ä�� �����ӿ� �뺸�Ѵ�.
	void NotifyImeLocalModeChange();

	/// �����Ϳ� �Էµ� ������ ���� ���� ä�� ��带 �˻��Ѵ�.
	void CheckChatMode();
	/// ���� ä�� ��带 �����Ѵ�.
	void SetChatMode(BYTE bChatMode, CString strTarget = "");
	/// �Ӹ� ��忡���� ä�� Ÿ���� �����Ѵ�.
	void SetChatTarget(const CString& strTarget, DWORD dwTargetID=0);

	/// ä�� ��� ���� Ŀ�ǵ� �̺�Ʈ�� ó���Ѵ�.
	static CString OnChatModeCmd(const CString& strMSG, const VECTORSTRING& vPARAM, DWORD dwUSER);

	/// ȣĪ ����
	static CString OnChatTitleCmd(const CString& strMSG, const VECTORSTRING& vPARAM, DWORD dwUSER);

	/// �޽����� ���� �Լ� �����͸� �����Ѵ�.
	void AddChatCmdProc(const CString& strCMD, FP_CHATCMDPROC fp, DWORD dwUSER=0);
	/// ������ �޽��� �Լ� ������ ���̺��� ��� �����Ѵ�.
	void ClearChatCmdProc();

	TListItem* HitTestChatList( CPoint pt );

public:
	/// ������ ���� â�� ���� ��� �� �ִ��� ���θ� ��´�.
	virtual BOOL CanWithItemUI();
	/// �������� ȭ�鿡 ���ų� �����.
	virtual void ShowComponent(BOOL bVisible = TRUE);
	/// �� �������� �־��� ��ǥ�� �����ϴ��� �˻��Ѵ�.
	virtual BOOL HitTest( CPoint pt);

	virtual void ResetPosition();
	virtual void DefaultPosition( CPoint* vBASIS, BOOL bRestore );

protected:
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);
	virtual void OnLButtonUp(UINT nFlags, CPoint pt);
	virtual void OnRButtonDown(UINT nFlags, CPoint pt);
	virtual void OnRButtonUp(UINT nFlags, CPoint pt);
	virtual void OnMouseMove(UINT nFlags, CPoint pt);
	virtual void OnLoseFocus( TComponent* pSetFocus );
	/// ä�� �Է� �����ͷ� ��Ŀ���� �����ϱ� ���� �籸�� �Ǿ���.
	virtual void SwitchFocus(TComponent* pCandidate);
    	
public:
	/**
		ä��â�� �� �Լ� ȣ�� �ĺ��� TCHAT_TIMER �� ���ǵ� 
		�ð� ����� �ڵ����� ȭ�鿡�� ������� �ȴ�.
	*/
	void ResetTick()								{ m_dwTick = 0; }

	/// �־��� �ε����� ä�� ����Ʈ�� ��´�.
	CTChatList* GetChatList(INT iIndex) const		{ return m_vLists[iIndex]; }

	/// ä�� ������ ��Ʈ���� ��´�.
	TEdit* GetChatEditCtrl() const					{ return m_pChatEditCtrl; }
	/// �Ӹ� ��� �Է� ��Ʈ�� ��´�.
	TEdit* GetWhisperTargetEditCtrl() const					{ return m_pChatWhisperTargetEditCtrl; }
	/// ä�� �Է������� ���θ� ��´�.
	BOOL IsChatEditON() const						{ return m_bChatEditON; }

	/// ä�� ����Ʈ�� �⺻ ��ġ�� ��´�.
	const CRect& GetDefaultListRect() const			{ return m_rcDefaultList; }
	const INT GetDefaultListHeight() const { return m_rcDefaultList.Height(); }
	/// �־��� ���Կ� �ش��ϴ� ���� ��ġ�� ��´�.
	const CRect& GetTabSlotRect(INT iSlot) const	{ return m_vTabRect[iSlot]; }

	/// �������� ������ ���θ� ��´�.
	BOOL IsLock() const								{ return m_bLock; }

	/// ���� ���� �������� ��´�.
	CTClientGame* GetMainGame() const				{ return m_pMainGame; }

	BYTE GetChatMode() const						{ return m_bChatMode; }
	DWORD GetChatTargetID() const					{ return m_dwChatTargetID; }
	const CString& GetChatTarget() const			{ return m_strChatTarget; }

	CTChatList* GetNotifyList() const				{ return m_pNotifyList; }

	/// ���� �������� ���� �Ӹ� ��븦 ��´�.
	const CString& GetLastWhisperTarget() const		{ return m_strLastWhisper; }

	void SetCandiWhisperTarget( CString strCandiWhisper ) { m_strCandiWhisper = strCandiWhisper; }
	const CString& GetCandiWhisperTarget() const		{ return m_strCandiWhisper; }

	TEdit* GetCurEdit();
	BOOL GetApplyCursor( LPTCURSOR_TYPE pbCursor );

	void ToggleTacticsChatMode( DWORD dwTactics );

#ifdef DEBUG
	/// ���� �������� ������ ����Ѵ�.
	inline void _LOG(LPCSTR func);
#endif

protected:
	/// �� �����ӿ��� ����� �� �ִ� ������ ID �� ��´�.
	UINT GetUniqueID(TComponent* pParent);

	/// rcFrom ����Ʈ�� rcTo ����Ʈ�� ���� �Ŵ��� �˻��ϰ� ���� �ȴٸ� ���� ��ġ�� ��´�.
	BOOL SnapList(const CRect& rcFrom, const CRect& rcTo, CRect& outRect);

	// ���� �˻� �Լ���..
	BOOL SnapList_LeftToRight(const CRect& rcFrom, const CRect& rcTo, CRect& outRect);
	BOOL SnapList_RightToLeft(const CRect& rcFrom, const CRect& rcTo, CRect& outRect);
	BOOL SnapList_UpToDown(const CRect& rcFrom, const CRect& rcTo, CRect& outRect);
	BOOL SnapList_DownToUp(const CRect& rcFrom, const CRect& rcTo, CRect& outRect);

public:
	CTChatFrame(TComponent *pParent, LP_FRAMEDESC pDesc, CTClientGame* pMainGame, TCMLParser *pParser);
	virtual ~CTChatFrame();
};
