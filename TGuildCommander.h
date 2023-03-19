#pragma once

class CTGuildCommander
{
public:
	/// ��� ���� ����
	enum AuthorityEnum
	{
		AUTHORITY_MASTER,					///< ����� �̻�
		AUTHORITY_SUBMASTER,				///< �α���� �̻�
		AUTHORITY_MEMBER,					///< ���� �̻�
		AUTHORITY_NOT_MEMBER,				///< ������ ������ ���
		AUTHORITY_ALL,						///< ���� ����( ��� )
		AUTHORITY_COUNT
	};

	/// ��� ����
	enum CmdEnum
	{
		CMD_SHOW_GUILDAPPDLG,				///< ��� ����â ����
		CMD_INVITE,							///< ��� �ʴ�
		CMD_LEAVE,							///< ��� Ż��
		CMD_KICK,							///< ���� �߹�
		CMD_DISORGONIZATION,				///< ��� ��ü ��û
		CMD_DISORGONIZATION_CANCEL,			///< ��� ��ü ���
		CMD_APPOINTMENT_MASTER,				///< ����� ����
		CMD_APPOINTMENT_SUBMASTER,			///< �α���� ����
		CMD_DISMISS_SUBMASTER,				///< �α���� ����
		CMD_PEER_CANCEL,					///< �־��� ������ ���
		CMD_PEER_BARON,						///< ���ۿ� �Ӹ�
		CMD_PEER_VISCOUNT,					///< ���ۿ� �Ӹ�
		CMD_PEER_COUNT,						///< ���ۿ� �Ӹ�
		CMD_PEER_MARQUIS,					///< ���ۿ� �Ӹ�
		CMD_PEER_DUKE,						///< ���ۿ� �Ӹ�
		CMD_INVITE_TACTICS,					///< �뺴�ʴ�
		CMD_COUNT
	};

	/// ��� ����
	enum DonateEnum
	{
		DON_NONE,							///< ��ΰ� �ƴ�
		DON_EXP,							///< ����ġ ���
		DON_MONEY,							///< �ڱ� ���
		DON_PVP,							///< ���� ���
	};

	/// ������ ���� Ÿ��
	enum VolunUpdateType
	{
		VUT_NONE,
		VUT_GUILD,
		VUT_TACTICS,
		VUT_COUNT
	};

	/// ��忡 ���� �� ����
	struct GuildDetInfo
	{
		DWORD				m_dwGuildID;			///< ��� ���̵�
		CString				m_strGName;				///< ����
		//CString				m_strGDate;				///< ��� ���� ��
		INT64					m_ldwGDate;
		CString				m_strGMaster;			///< �����
		BYTE				m_bGMasterPeer;			///< ����� ����
		CString				m_strGSubMaster1;		///< �� �����1
		CString				m_strGSubMaster2;		///< �� �����2
		WORD				m_nGMbCnt;				///< ������ �� (���� ��)
		WORD				m_nGMbMax;				///< ������ �� (�ִ� ���� ��)
		BYTE				m_nGLev;				///< ��� ����
		DWORD				m_dwGExpCur;			///< ��� ����ġ (���� ��ġ)
		DWORD				m_dwGExpMax;			///< ��� ����ġ (���� ������ ��ġ)
		CString				m_strGKind;				///< ��� ����
		BYTE				m_bMyDuty;				///< ���� ����
		DWORD				m_nGRune;				///< ��� �ڱ� (��)
		DWORD				m_nGLuna;				///< ��� �ڱ� (�糪)
		DWORD				m_nGCron;				///< ��� �ڱ� (ũ��)
		BYTE				m_bMyPeerage;			///< ���� ����
		BYTE				m_bMyService;			///< ���� ��� ���嵵
		BOOL				m_bShowMark;			///< ��� ��ũ ǥ�� ����
		BYTE				m_bMark;				///< ��� ��ũ
		BYTE				m_bMarkBack;			///< ��� ��ũ ���
		BYTE				m_bMarkColor;			///< ��� ��ũ ��
		BYTE				m_bMarkBackColor1;		///< ��� ��ũ ��� ��
		BYTE				m_bMarkBackColor2;		///< ��� ��ũ ��� ��
		CString				m_strNotify;			///< ��� ��������
		DWORD			m_dwPvPTotalPoint;
		DWORD			m_dwPvPUseablePoint;
		DWORD			m_dwMonthPoint;
		DWORD			m_dwRankTotal;
		DWORD			m_dwRankMonth;

		GuildDetInfo();
	};

	/// ����
	struct GuildMember
	{
		DWORD m_dwCharID;				///< ĳ���� ���̵�
		CString m_strName;				///< ĳ���� �̸�
		BYTE m_bLevel;				///< ����
		BYTE m_bClassID;				///< ����
		BYTE m_bDuty;				///< ����
		BYTE m_bPeer;				///< ����
		BYTE m_bIsConnect;			///< ���ӿ���
		DWORD m_dwRegion;				///< ��ġ
		WORD m_wCastle;
		BYTE m_bCamp;
		DWORD m_dwTactics;		///< �ٸ� ��� �뺴�ΰ�?
		BYTE m_bWarCountry;
		INT64 m_dlConnectedDate;
	};
	typedef std::vector<GuildMember>	GuildMemberVec;

	/// ��� �뺴
	struct GuildTactics
	{
		DWORD m_dwCharID;
		CString m_strName;
		BYTE m_bLevel;
		BYTE m_bClass;
		BYTE m_bDay;
		DWORD m_dwPoint;
		INT64 m_dlMoney;
		INT64 m_dlEndTime;
		DWORD m_dwGotPoint; // ���Ⱓ���� ���� ���� ����Ʈ
		DWORD m_dwRegion;
		WORD m_wCastle;
		BYTE m_bCamp;
	};
	typedef std::vector<GuildTactics>	GuildTacticsVec;

	/// ��� ��������
	struct GuildNotify
	{
		DWORD				m_dwID;					///< ���̵�	
		BYTE				m_bDuty;				///< ���� �ۼ��� ����
		CString				m_strTitle;				///< ���� Ÿ��Ʋ
		CString				m_strAuthor;			///< ���� �ۼ���
		CString				m_strText;				///< ���� ����
		CString				m_strDate;				///< �ۼ���
	};
	typedef std::vector<GuildNotify>	GuildNotifyVec;

	/// ��� ������ ����
	struct GuildVolunteer
	{
		DWORD m_dwCharID;
		CString m_strName;
		BYTE m_bLevel;
		BYTE m_bClass;
		DWORD m_dwRegion; // ������ġ
	};
	typedef std::vector<GuildVolunteer>	GuildVolunteerVec;

	/// �뺴 ������ ����
	struct GuildTacticsVolunteer
	{
		DWORD m_dwCharID;
		CString m_strName;
		BYTE m_bLevel;
		BYTE m_bClass;
		DWORD m_dwRegion;
		BYTE m_bDay;
		DWORD m_dwPoint;
		DWORD m_dwGold;
		DWORD m_dwSilver;
		DWORD m_dwCooper;
	};
	typedef std::vector<GuildTacticsVolunteer> GuildTacticsVolunteerVec;

	/// ��� ���� ����
	struct GuildOffer
	{
		//DWORD m_dwID;
		DWORD m_dwGuildID;
		CString m_strGuildName;
		CString m_strTitle;
		CString m_strText;
		BYTE m_bMinLevel;
		BYTE m_bMaxLevel;
		INT64 m_dlTime;
		BYTE m_bApplied;
	};
	typedef std::vector<GuildOffer>		GuildOfferVec;

	/// ��� ���� ����
	struct GuildTacticsOffer
	{
		DWORD m_dwID;
		DWORD m_dwGuildID;
		CString m_strGuildName;
		CString m_strTitle;
		CString m_strText;
		BYTE m_bDay;
		BYTE m_bMinLevel;
		BYTE m_bMaxLevel	;
		DWORD m_dwPoint;
		DWORD m_dwGold;
		DWORD m_dwSilver;
		DWORD m_dwCooper;
		INT64 m_dlTime;
		BYTE m_bApplied;
	};
	typedef std::vector<GuildTacticsOffer>		GuildTacticsOfferVec;

	/// ���� ������ ����
	struct LocalTerritory
	{
		WORD				m_wCastleID;
		WORD				m_wLocalID;				///< ���������̵�
		CString				m_strLocalName;			///< �������̸�
		DWORD				m_dwGuildID;			///< ���� ���
		CString				m_strGuildName;			///< ���� ��� �̸�
		BYTE				m_bCountry;				///< �Ҽ� ����
		__int64			m_dNextWar;
		CString			m_strHeroName;
	};
	typedef std::vector<LocalTerritory>	LocalTerritoryVec;

	/// ������ ����
	struct Territory
	{
		WORD m_wCastleID;			///< �����̵�
		CString m_strCastleName;		///< ���̸�
		BYTE m_bCanApplyCastle;		///< �� ��������	//������
		DWORD m_dwGuildID;			///< ���� ���
		CString m_strGuildName;			///< ���� ��� �̸�
		BYTE m_bCountry;				///< �Ҽ� ����
		INT64 m_dlNextWar;			///< ���� ���� �ð�	//������
		CString m_strHero;				///< ���� ����		//������
		CString m_strAtkGuild;			///< ������ ���	//������
		CString m_strDefGuild;
		WORD m_wDefGuildPoint;
		WORD m_wDefCountryPoint;
		BYTE m_bDefCount;
		WORD m_wAtkGuildPoint;
		WORD m_wAtkCountryPoint;
		BYTE m_bAtkCount;
		WORD m_wMyGuildPoint;
		
		LocalTerritoryVec	m_vLocals;				///< �Ҽӵ� ������ ����Ʈ
		VTOP3 m_vDTop3s; //������ ž3
		VTOP3 m_vCTop3s; //ũ���ÿ� ž3
	};
	typedef std::vector<Territory>		TerritoryVec;

	struct Mission
	{
		WORD m_wMissionID;
		CString m_strMission;
		BYTE m_bCountry;				///< �Ҽ� ����
		CTime m_NextWar;
		BYTE m_bStatus;
	};
	typedef std::vector<Mission>		MissionVec;
	Mission m_SkyGarden;

	/// �˾� ��ư ����
	struct PopupBtnInfo
	{
		DWORD			m_dwTXT;
		DWORD			m_dwGM;
	};

	struct GuildLatestPvP
	{
		DWORD m_dwCharID;
		WORD m_wKillCount_D;
		WORD m_wDieCount_D;
		DWORD m_dwKillPoint_H_D;
		DWORD m_dwKillPoint_E_D;
		DWORD m_dwKillPoint_L_D;
		DWORD m_dwGodMonKillPoint_D;
		DWORD m_dwEntryPoint_D;
		DWORD m_dwResult;
	};
	typedef std::vector<GuildLatestPvP> GuildLatestPvPVec;

	struct GuildWeekPvP
	{
		DWORD m_dwCharID;
		WORD m_wKillCount_W;
		WORD m_wDieCount_W;
		DWORD m_dwKillPoint_H_W;
		DWORD m_dwKillPoint_E_W;
		DWORD m_dwKillPoint_L_W;
		DWORD m_dwGodMonKillPoint_W;
		DWORD m_dwEntryPoint_W;
		DWORD m_dwResult;
	};
	typedef std::vector<GuildWeekPvP> GuildWeekPvPVec;

	/// ��ɿ� ���� ���� �迭
	static const DWORD CMD_AUTHORITY[];
	/// ��ɿ� ���� ���ڿ� �迭
	static const DWORD CMD_STRING[];
	/// ��ɿ� ���� �� ���ڿ� �迭
	static const DWORD CMD_DESC_STRING[];

public:
	/// ��� Ŀ�ǵ� �ν��Ͻ��� ��´�.
	static CTGuildCommander* GetInstance();

	/// ä�� �޽����� ���� ��� ��� �̺�Ʈ�� ó���Ѵ�.
	static CString OnGuildCmdByChatMsg(const CString& strCMD, const VECTORSTRING& vPARAM, DWORD dwUSER);
	/// ä�� �޽��� Ŀ�ǵ带 ����Ѵ�.
	static void RegChatCmds();

	/// ������ ���� ���ڿ��� ��´�.
	static CString GetDutyStr(BYTE bDuty);
	/// ������ ���� ���ڿ��� ��´�.
	static CString GetPeerageStr(BYTE bPeer);
	
public:
	DWORD				m_dwInviterID;			///< ���� �ʴ��� ����� ���̵�
	BOOL				m_bDisorgCancel;		///< ��� ��ü ������� ��û���� ����
	DonateEnum			m_eCurDonMode;			///< ���� ��� ����
	VolunUpdateType		m_eCurVolunUpdate;		///< ������ ���� Ÿ��
	CString				m_strKickTarget;		///< ��� �߹� Ÿ��
	DWORD				m_dwKickTarget;		///< ��� �߹� Ÿ�� ���̵�
	CString				m_strTacticsInviter;	///< ���� �뺴���� �ʴ��� ���

	GuildDetInfo		m_GuildDetInfo;			///< ��� �� ����
	GuildMemberVec		m_GuildMemberVec;		///< ���� ����Ʈ
	GuildTacticsVec		m_GuildTacticsVec;		///< �뺴 ����Ʈ
	GuildNotifyVec		m_GuildNotifyVec;		///< �������� ����Ʈ
	GuildLatestPvPVec	m_GuildLatestPvPVec;	///< �ֱ������⿩��
	GuildWeekPvPVec	m_GuildWeekPvPVec; ///< �ְ������⿩��

	GuildVolunteerVec	m_GuildVolunteerVec;	///< ��������� ����Ʈ
	GuildTacticsVolunteerVec	m_TacticsVolunteerVec;	///< �뺴������ ����Ʈ

	GuildOfferVec		m_GuildOfferVec;		///< ��� ���� ����Ʈ
	GuildTacticsOfferVec		m_GuildTacticsOfferVec;			///< ��� ���� ����Ʈ

	TerritoryVec		m_TerritoryVec;			///< �������� ����
	MissionVec		m_MissionVec;

public:
	/// ��� ���� ����� ������.
	void DoGuildCommand(CmdEnum eCmd, const CString& strParam="");

	GuildMember* FindGuildMemberByID( DWORD dwCharID );

public:
	/// ��� ��ü/â�� ����
	// -----------------------------------------------------------------------------------------
	/// ��� â�� ���� �޽����� ó���Ѵ�.
	void RecvGuildEstablish(BYTE bResult, DWORD dwGuildID, const CString& strGuild);
	
	/// ��� ��ü ��û/��� �޽����� ó���Ѵ�.
	void RecvGuildDisorganization(BYTE bResult);
	/// ��� ��ü ��û/��� �� ������.
	void RequestGuildDisorganization(BOOL bCancel);

	/// ��� �ʴ�/����/Ż�� ����
	// -----------------------------------------------------------------------------------------
	/// ��� �ʴ� �޽����� ó���Ѵ�.
	void RecvGuildInvite(BYTE bResult, DWORD dwInviterID, const CString& strInviter, const CString& strGuild);
    /// ��� �ʴ뿡 ���� ������ ������.
	void RequestGuildInviteAnswer(BYTE bReply);
	/// �־��� �÷��̾ ���� �ʴ��Ѵ�.
	void RequestGuildInvite(const CString& strTarget);

	/// ��� ���� �޽����� ó���Ѵ�.
	void RecvGuildJoin(BYTE bResult, DWORD dwGuildID, const CString& strGuild, DWORD dwNewMemberID, const CString& strNewMember, BYTE bMax);
	
	/// ��� Ż�� �޽����� ó���Ѵ�.
	void RecvGuildLeave(BYTE bResult, const CString& strTarget, BYTE bReason);
	/**
		Ư�� ���� �߹��� ��û�Ѵ�.

		@param strTarget	�߹��ϰ��� �ϴ� ������ �̸�.
		@param bWarn		�߹����� ��� �޽����� ����� ����.
	*/
	void RequestGuildKickOut(const CString& strTarget, BOOL bWarn);
	void RequestGuildTacticsKickOut(const CString& strTarget, DWORD dwTarget, BYTE bWarn);
	/// ���� ��忡�� ������,
	void RequestGuildLeave();

	/// ��� ���� ����
	// -----------------------------------------------------------------------------------------
	/// ����� �Ӹ� �޽����� ó���Ѵ�.
	void RecvGuildDuty(BYTE bResult, const CString& strTarget, BYTE bDuty);
	/// �־��� ������ ������ �����Ѵ�.
	void RequestGuildDuty(const CString& strTarget, BYTE bDuty);

	/// ��� ���� ���� �޽����� ó���Ѵ�.
	void RecvGuildPeer(BYTE bResult, const CString& strTarget, BYTE bPeer, BYTE bOldPeer);
	/// �־��� ������ ������ �����Ѵ�.
	void RequestGuildPeer(const CString& strTarget, BYTE bPeer);

	/// ��� ���� ����
	// -----------------------------------------------------------------------------------------
	/// ������ ���� ���� �޽����� ó���Ѵ�.
	void RecvGuildAttr( DWORD dwPlayerID, DWORD dwGuildID, const CString& strGuildName, 
						BYTE bGuildPeer,  DWORD dwTacticsID, const CString& strTacticsName,
						CTClientGuildMark* pGuildMark );

	/// ��� �� ������ ��´�.
	GuildDetInfo& GetGuildDetInfo() { return m_GuildDetInfo; }

	/// ��� �� ���� ���� �޽����� ó���Ѵ�.
	void RecvGuildDetInfo(const GuildDetInfo& info);
	/// ��� �� ������ ��û�Ѵ�.
	void RequestGuildDetInfo();
	/// ��� ��� ����Ʈ ���� �޽����� ó���Ѵ�.
	void RecvGuildMemberList(GuildMemberVec* pMembers);
	/// ��� �뺴 ����Ʈ ���� �޽����� ó���Ѵ�.
	void RecvGuildTacticsList(GuildTacticsVec* pMembers);

	/// ��� ��� ����
	// -----------------------------------------------------------------------------------------
	/// ��� ��� �޽����� ó���Ѵ�.
	void RecvGuildDonation(BYTE bResult);
	/// ��� ����ġ ��θ� ��û�Ѵ�.
	void RequestGuildDonationExp(DWORD dwEXP);
	/// ��� �ڱ� ��θ� ��û�Ѵ�.
	void RequestGuildDonationMoney(DWORD dwRune,DWORD dwLuna,DWORD dwCron);
	/// ��� ���� ��θ� ��û�Ѵ�.
	void RequestGuildDonationPVP(DWORD dwPVP);

	/// �������� ����
	// -----------------------------------------------------------------------------------------
	/// ��� ���û��� ����Ʈ ���� �޽����� ó���Ѵ�.
	void RecvGuildNotifyList(GuildNotifyVec* pNotVec);
	/// ��� �������� ������ ��û�Ѵ�.
	void RequestGuildNotifyList();
	
	/// ��� ���������� �߰��� ��û�Ѵ�.
	void RequestGuildNewNotify(const CString& strTitle, const CString& strArticle);
	/// ��� ���������� ������ ��û�Ѵ�.
	void RequestGuildDelNotify(DWORD dwID);
	/// ��� ���������� ������ ��û�Ѵ�.
	void RequestGuildModNotify(DWORD dwID, const CString& strTitle, const CString& strArticle);

	/// ��� �������� ����Ʈ ���� �޽����� ó���Ѵ�.
	void RecvTacticsVolunteerList(GuildVolunteerVec* pVol);

	/// ������ ���� �޽����� ó���Ѵ�.
	void RecvDeleteVolunteer(BYTE bResult);
	/// �־��� ĳ���͸� ������ ����Ʈ���� �����Ѵ�.
	void RequestDeleteVolunteer(DWORD dwCharID);

	/// ��� ��ũ ����
	// -----------------------------------------------------------------------------------------
	/// ���ο� ��� ��ũ ����� ��û�Ѵ�.
	void RequestGuildMarkReg(CTClientGuildMark* pMark);

	/// ������ ����
	// -----------------------------------------------------------------------------------------
	/// ������ ����Ʈ �޽����� ó���Ѵ�.
	void RecvTerritoryList(TerritoryVec* pTerr);
	/// ������ ���� ����Ʈ�� ������ ��û�Ѵ�.
	void RequestTerritoryList();

	/// �뺴 �ʴ� ���� (��屸�κ��� ��û�� ���)
	// -----------------------------------------------------------------------------------------
	/// �־��� �÷��̾ �뺴���� �ʴ��Ѵ�.
	void RequestTacticsOfferInvite(const CString& strName);
	/// �뺴 �ʴ� ���� (��屸���� ���� �ݾ�����)
	// -----------------------------------------------------------------------------------------
	/// �뺴 �ʴ� �޽����� ó���Ѵ�.
	void RecvTacticsSeekInvite( const CString& strGuild, const CString& strInviter,
								DWORD dwRune, DWORD dwLuna, DWORD dwCron);
	/// �־��� �÷��̾ �뺴���� �ʴ��Ѵ�.
	void RequestTacticsSeekInvite(DWORD dwID, DWORD dwRune, DWORD dwLuna, DWORD dwCron);

	/// �뺴 ����
	// -----------------------------------------------------------------------------------------
	/// �뺴 Ż�� �޽����� ó���Ѵ�.
	void RecvTacticsLeave(BYTE bResult);
	/// �뺴 Ż�� ��û�Ѵ�.
	void RequestTacticsLeave();

public:
	/// ��� ����� �����Ѵ�.
	void SortGuildMember();
	/// �뺴�� �����Ѵ�.
	void SortTactics();
	/// �ֱ������⿩��
	void SortLatestPVP();
	/// �ְ������⿩��
	void SortWeekPVP();

public:
	/// �־��� �ε����� ���� ������ ��´�.
	const GuildMember& GetGuildMember(size_t nIndex) { return m_GuildMemberVec[nIndex]; }
	/// �־��� �ε����� ���� ������ ��´�.
	GuildMember* GetGuildMemberPtr(size_t nIndex)	{ return &m_GuildMemberVec[nIndex]; }
	/// ��ü ���� ���� ��´�.
	size_t GetCountGuildMember() { return m_GuildMemberVec.size(); }

	/// �־��� �ε����� �뺴 ������ ��´�.
	GuildTactics* GetTacticsPtr(size_t nIndex) { return &m_GuildTacticsVec[nIndex]; }
	/// ��ü �뺴�� ���� ��´�.
	size_t GetCountTactics() { return m_GuildTacticsVec.size(); }

	///< �ֱ������⿩��
	const GuildLatestPvP& GetGuildLatestPvP(size_t nIndex) const	{ return m_GuildLatestPvPVec[nIndex]; }

	///< �ְ������⿩��
	const GuildWeekPvP& GetGuildWeekPvP(size_t nIndex) const	{ return m_GuildWeekPvPVec[nIndex]; }

	/// �־��� �ε����� ���������� ��´�.
	const GuildNotify& GetGuildNotify(size_t nIndex) const	{ return m_GuildNotifyVec[nIndex]; }
	/// ��ü ���������� ���� ��´�.
	size_t GetCountGuildNotify() const { return m_GuildNotifyVec.size(); }

	/// ���� ������ ���� ���¸� ��´�.
	VolunUpdateType GetCurVolunUpdate() const { return m_eCurVolunUpdate; }

	/// �־��� �ε����� ������������ ��´�.
	Territory& GetTerritory(size_t nIndex) { return m_TerritoryVec[nIndex]; }
	/// ��ü �������� ���� ��´�.
	size_t GetCountTerritory() const	{ return m_TerritoryVec.size(); }

protected:
	CTGuildCommander();
};




