#pragma once

#define TDETINFO_OUTLOOK_STYLE_TITLE			1
#define TDETINFO_OUTLOOK_STYLE_UNTITLE		2

/// ������ Ÿ�� ����
enum TDETINFO_TYPE
{
	TDETINFO_TYPE_NOR,			///< Ÿ��Ʋ�� ���� �ִ� ������ �� ����
	TDETINFO_TYPE_ITEM,			///< ������ ���� Ÿ���� �� ����
	TDEFINFO_TYPE_INSTITEM,
	TDETINFO_TYPE_SEALEDITEM,	///< ���� ������ ���� Ÿ���� �� ����
	TDETINFO_TYPE_OPTIONITEM,	///< �ɼ� ������ ���� Ÿ���� �� ����
	TDETINFO_TYPE_SKILL,		///< ��ų ���� Ÿ���� �� ����
	TDETINFO_TYPE_CASTLE,	///< �� ���� Ÿ���� �� ����
	TDETINFO_TYPE_TERRITORY, ///< ���� ���� Ÿ���� �� ����
	TDETINFO_TYPE_STAT, ///< ���� ����
	TDETINFO_TYPE_PVP, ///< PVP���� ����
	TDETINFO_TYPE_TEXT,
	TDEFINFO_TYPE_DEFTOOLTIP,	///< ���� �ִ� ������ �� ����
	TDETINFO_TYPE_FAMERANK,	///< ���� ���� ����
	TDETINFO_TYPE_TOURNAMENT_PLAYER,
	TDETINFO_TYPE_MISSION,
	TDETINFO_TYPE_PLAYER,
	TDEFINFO_TYPE_GEM_0,
	TDEFINFO_TYPE_GEM_1,
	TDEFINFO_TYPE_GEM_2,
	TDEFINFO_TYPE_GEM_3,
	TDEFINFO_TYPE_GEM_4,
	TDEFINFO_TYPE_GEM_5,
	TDEFINFO_TYPE_GEM_0_W,
	TDEFINFO_TYPE_GEM_1_W,
	TDEFINFO_TYPE_GEM_2_W,
	TDEFINFO_TYPE_GEM_3_W,
	TDEFINFO_TYPE_GEM_4_W,
	TDEFINFO_TYPE_GEM_5_W,
	TDETINFO_TYPE_COUNT
};

#define TDEFAULT_TEXT_COLOR		D3DCOLOR_ARGB(255,249,233,202)
#define TNEXTLEV_TEXT_COLOR		D3DCOLOR_ARGB(255,176,174,253)

// =====================================================================
/**	@class		ITDetailInfo
	@brief		�������� ���ް� ǥ�ø� ���� �⺻ �������̽�.
	
*/// ===================================================================
class ITDetailInfo
{
public:
	/// _GetLineState() �� ��ȯ������ ���.
	enum LINE_STATE
	{
		LS_VALID,		///< �ƹ� ���� ����
		LS_INVALID,		///< �� ������ ������ �� ����
		LS_NEEDCONV,	///< �� ������ ��ȯ�� �ʿ���
		LS_TITLE,		///< Ÿ��Ʋ�� ������
		LS_COUNT
	};

public:
	/// �������� �� ���� ǥ���ϱ����� ����.
	struct Line
	{
		CString		m_strText;
		DWORD		m_dwColor;

		Line(const CString& strText, DWORD dwColor)
		:	m_strText(strText),
			m_dwColor(dwColor)
		{}
	};

	typedef std::vector<Line> LineVec;

public:
	static const char m_cTokenMark;

protected:
	TDETINFO_TYPE	m_eType;			///< ������ Ÿ��
	
	DWORD			m_dwInfoID;			///< ������ ���̵�
	WORD			m_wImageID;			///< �������� ��ǥ�ϴ� �̹����� ���̵�
	CRect			m_rcRef;			///< ����â�� �����ϴ� ���� UI ũ��
	
	BOOL			m_bLRType;			///< ��â�� ������������ �¿������� ǥ������ ����.
	BOOL			m_bPriorLeft;		///< ��â�� �������� ���� ǥ������ ����
	BOOL			m_bPriorTop;		///< ��â�� �������� ���� ǥ������ ����

	BOOL			m_bNeedBuild;		///< �������� �ٽ� �����ؾ� �ϴ°��� ���� �÷���

	Line			m_TitleB;			///< �������� ��ǥ�ϴ� Ÿ��Ʋ
	LineVec			m_LinesB;			///< ������ ��
	INT			m_nOutlookStyle;

public:
	TDETINFO_TYPE GetType() const		{ return m_eType; }
	BOOL IsLRType() const				{ return m_bLRType; }
	BOOL IsPriorLeft() const			{ return m_bPriorLeft; }
	BOOL IsPriorTop() const				{ return m_bPriorTop; }
	DWORD GetInfoID() const				{ return m_dwInfoID; }
	WORD GetImageID() const				{ return m_wImageID; }
	const CRect& GetSize() const		{ return m_rcRef; }
	INT GetOutlookStyle() const { return m_nOutlookStyle; }

public:
	/**
		������ UI�� ���� ������ �����Ѵ�.
		�� ������ ���� GetUIPosition() �� ���� �������
		������â�� ��ġ���� �����ȴ�.
	*/
	void SetDir(BOOL bLR, BOOL bPriorLeft, BOOL bPriorTop);

	/// ������ UI�� ���� ��ġ
	virtual CPoint GetUIPosition(const CRect& rcDetDlg, const CPoint& ptMouse );

	/// �������� ��ǥ�ϴ� Ÿ��Ʋ�� ��´�.
	const CString& GetTitleText();
	/// �������� ��ǥ�ϴ� Ÿ��Ʋ�� ���� ��´�.
	DWORD GetTitleColor();

	/// �������� ��ü ���� ���� ��´�.
	UINT GetLineCount();
	/// �������� ��ü ���� �ؽ�Ʈ�� ��´�.
	const CString& GetLineText(UINT nLine);
	/// �������� ��ü ���� ���� ��´�.
	DWORD GetLineColor(UINT nLine);
	BYTE GetGem();
	BOOL IfGem();
	CString BuildTimeFormatSTR( DWORD dwTick);

public:	
	/// ���� ���� Ÿ�ٿ� ���� �������ΰ��� ���Ѵ�.
	virtual BOOL Compare(const ITDetailInfo* pTarget) = 0;
	/// �������� �����Ѵ�.
	virtual void Build() = 0;
	/// ������ �ڽ��� ��Ų�� ����� �� �ΰ�?
	virtual INT CheckUsingSkin();

public :
//	virtual CTClientItem* GetItemInst() const	{ return NULL; }

protected:
	/// �־��� ���ڿ��� ���¸� �Ǵ��Ѵ�.
	virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	
	/// �־��� ���ڿ��� ���ο� �߰��Ѵ�.
	virtual void _AddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	/// �־��� ���ڿ��� ��ȯ�� �� Ÿ��Ʋ�� �����Ѵ�.
	virtual void _ConvertAndSetTitle(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	/// �־��� ���ڿ��� ��ȯ�� �� ���ο� �߰��Ѵ�.
	virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);

protected:
	CPoint _GetUIPosition_TB(const CRect& rcDetDlg, BOOL bPriorLeft, BOOL bPriorTop);
	CPoint _GetUIPosition_LR(const CRect& rcDetDlg, BOOL bPriorLeft, BOOL bPriorTop);

public:
	ITDetailInfo(
		TDETINFO_TYPE eType,
		DWORD dwInfoID, 
		WORD wImgID, 
		const CRect& rc);

	virtual ~ITDetailInfo();
};
// =====================================================================
/**	@class		CTStatDetInfo
	@brief		���� ������ ������ ���� �������� ���ް� 
				ǥ�ø� ���� Ŭ����.
	
*/// ===================================================================
class CTStatDetInfo : public ITDetailInfo
{
public:
	/// ������ �ɷ�ġ ��ū Ÿ��
	enum TINFOTOKEN_STAT
	{
		TINFOTOKEN_STAT_STR,
		TINFOTOKEN_STAT_DEX,
		TINFOTOKEN_STAT_CON,
		TINFOTOKEN_STAT_INT,
		TINFOTOKEN_STAT_WIS,
		TINFOTOKEN_STAT_MEN,
		TINFOTOKEN_STAT_MIN_PHYSICAL_ATTACK_POWER,
		TINFOTOKEN_STAT_MAX_PHYSICAL_ATTACK_POWER,
		TINFOTOKEN_STAT_PHYSICAL_DEFENCE_POWER,
		TINFOTOKEN_STAT_MIN_LONG_ATTACK_POWER,
		TINFOTOKEN_STAT_MAX_LONG_ATTACK_POWER,
		TINFOTOKEN_STAT_ATTACK_DELAY_PHYSICAL,
		TINFOTOKEN_STAT_ATTACK_DELAY_LONG,
		TINFOTOKEN_STAT_ATTACK_DELAY_MAGIC,
		TINFOTOKEN_STAT_ATTACK_DELAY_RATE_PHYSICAL,
		TINFOTOKEN_STAT_ATTACK_DELAY_RATE_LONG,
		TINFOTOKEN_STAT_ATTACK_DELAY_RATE_MAGIC,
		TINFOTOKEN_STAT_ATTACK_LEVEL,
		TINFOTOKEN_STAT_DEFENCE_LEVEL,
		TINFOTOKEN_STAT_PHYSICAL_CRITICAL_PROB,
		TINFOTOKEN_STAT_MIN_MAGIC_ATTACK_POWER,
		TINFOTOKEN_STAT_MAX_MAGIC_ATTACK_POWER,
		TINFOTOKEN_STAT_MAGIC_DEFENCE_POWER,
		TINFOTOKEN_STAT_MAGIC_ATTACK_LEVEL,
		TINFOTOKEN_STAT_MAGIC_DEFENCE_LEVEL,
		TINFOTOKEN_STAT_CHARGE_SPEED,
		TINFOTOKEN_STAT_CHARGE_PROB,
		TINFOTOKEN_STAT_MAGIC_CRITICAL_PROB,
		TINFOTOKEN_STAT_SKILL_POINT,
		TINFOTOKEN_STAT_COUNT
	};

public:
	static const CString TSTAT_TOKENS[TINFOTOKEN_STAT_COUNT];

public:
	CTStatDetInfo(
		DWORD dwInfoID,
		LPTSTATINFO,
		DWORD dwTitleColor,
		const CRect& rc);

	virtual ~CTStatDetInfo();

public:
	virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

public:
	/// �־��� ���ڿ��� ��ȯ�� �� ���ο� �߰��Ѵ�.
	virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual CString _GetAttrString( TINFOTOKEN_STAT eToken);

public:
	LPTSTATINFO m_pStatInfo;
	DWORD m_dwTitleColor;
};

// =====================================================================
/**	@class		CTNorDetInfo
	@brief		Ÿ��Ʋ�� �׿����� ������ ���� �������� ���ް� 
				ǥ�ø� ���� Ŭ����.
	
*/// ===================================================================
class CTNorDetInfo : public ITDetailInfo
{
protected:
	/// Ÿ��Ʋ
	CString m_strTITLE;	
	
public:	
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

protected:
	virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	//virtual void _AddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	//virtual void _ConvertAndSetTitle(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	//virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);

public:
	CTNorDetInfo(
		const CString& strTitle,
		DWORD dwInfoID, 
		WORD wImgID, 
		const CRect& rc);

	virtual ~CTNorDetInfo();
};

// =====================================================================
/**	@class		CTItemDetInfo
	@brief		�Ϲ� �����ۿ� ���� �������� ���ް� ǥ�ø� ���� Ŭ����.
	
*/// ===================================================================
class CTItemDetInfo : public ITDetailInfo
{
public:
	/// ������ �ɷ�ġ ��ū Ÿ��
	enum TINFOTOKEN_ITEM
	{
		TINFOTOKEN_ITEM_ITEMMINAP,		///< �ּҰ��ݷ�
		TINFOTOKEN_ITEM_ITEMMAXAP,		///< �ִ���ݷ�
		TINFOTOKEN_ITEM_ITEMAPSEC,		///< �ʴ���ݷ�
		TINFOTOKEN_ITEM_ITEMDP,			///< ��������
		TINFOTOKEN_ITEM_ITEMMINMAP,		///< �ּҸ������ݷ�
		TINFOTOKEN_ITEM_ITEMMAXMAP,		///< �ִ븶�����ݷ�
		TINFOTOKEN_ITEM_ITEMMAPSEC,		///< �ʴ縶�����ݷ�
		TINFOTOKEN_ITEM_ITEMMDP,		///< ��������
		TINFOTOKEN_ITEM_ITEMBLOCK,		///< ���й����
		TINFOTOKEN_ITEM_ATTRLEVEL,		///< ���ɷ���
		TINFOTOKEN_ITEM_GEMSTONELEVEL, ///< �䱸����
		TINFOTOKEN_ITEM_CURDURA,		///< ���� ������
		TINFOTOKEN_ITEM_MAXDURA,		///< �ִ� ������
		TINFOTOKEN_ITEM_CURREFI,		///< ���� ���Ƚ��
		TINFOTOKEN_ITEM_MAXREFI,		///< �ִ� ���Ƚ��
		TINFOTOKEN_ITEM_SELLPRICE,		///< �Ǹ� ����
		TINFOTOKEN_ITEM_ENDTIME,	///< ��������
		TINFOTOKEN_ITEM_NEEDSLEVEL, ///< �䱸����
		TINFOTOKEN_ITEM_COUNT
	};

	/// �����ۿ��� ���������� ����ϴ� ��ū Ÿ��
	enum TINFO_ITEMTYPE
	{
		TINFO_ITEMTYPE_ITEMNORMAL,		///< �Ϲݾ�����
		TINFO_ITEMTYPE_ITEMGRADE,		///< ��ȭ������
		TINFO_ITEMTYPE_ITEMMAGIC,		///< ����������
		TINFO_ITEMTYPE_ITEMSET,			///< ��Ʈ������
		TINFO_ITEMTYPE_ITEMRARE,		///< ���������
		TINFO_ITEMTYPE_ITEMUNIQUE,		///< ����ũ������
		//TINFO_ITEMTYPE_GEMSTONELEVEL,
		TINFO_ITEMTYPE_COUNT
	};

public:
	/// ������ �ɷ�ġ ��ū ����Ʈ
	static const CString TITEM_TOKENS[TINFOTOKEN_ITEM_COUNT];
	/// �������� ���� ��ū ����Ʈ
	static const CString TITEM_TYPE_TOKENS[TINFO_ITEMTYPE_COUNT];
	/// ������ ���� ������޺� �̸�
	static const DWORD TITEMATTR_NAMES[TATTRLEVELNAME_MAX];
	/// ������ ���� �����̸� ��ū
	static const CString TITEM_ATTRNAME_TOKEN;

protected:
	LPTITEM 	m_pItemTemp;		///< ���ϰ��� �ϴ� �������� ���ø� ����Ÿ
	WORD		m_wAttrID;			///< �� �������� �ɷ�ġ ���̵�
	CString		m_strAttrName;		///< ������ ��Ÿ���� ��޸�
	WORD		m_wAttrLevel;		///< ���� ����
	DWORD		m_dwSellPrice;		///< �Ǹ� ����

public:
	LPTITEM GetItemTemp() const	{ return m_pItemTemp; }
	WORD GetAttrID() const		{ return m_wAttrID; }

public:	
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

protected:
	virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	//virtual void _AddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _ConvertAndSetTitle(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);

	/// ������ �������� ���Ѵ�.
	virtual void _BuildItemIcon();
	/// ������ ���ɰ��� ���Ѵ�.
	virtual void _BuildAttrID();
	/// ������ ���ɰ��� ���ڿ��� ��´�.
	virtual CString _GetAttrString(TINFOTOKEN_ITEM eToken);
	/// ������ ���ɰ��� ���ڿ� ������ ��´�.
	virtual DWORD _GetAttrColor(TINFOTOKEN_ITEM eToken, DWORD dwDefaultColor );

protected:
	void _BuildAttrNameAndLevel();

public:
	CTItemDetInfo(
		TDETINFO_TYPE eType,
		LPTITEM pItemTemp,
		const CRect& rc);

	virtual ~CTItemDetInfo();
};

// =====================================================================
/**	@class		CTItemInstDetInfo
	@brief		��ȭ�� �������� �ΰ� �ɼ��� ���� �� �ִ� �ν��Ͻ��� 
				�����ۿ� ���� �������� ���ް� ǥ�ø� ���� �������̽�.
	
*/// ===================================================================
class CTItemInstDetInfo : public CTItemDetInfo
{
protected:
	/// �⺻ ���ø� ����Ÿ�� ���� ���� ������ ������ �ν��Ͻ�.
	CTClientItem*	m_pItemInst;

public:
	CTClientItem* GetItemInst() const	{ return m_pItemInst; }

public:	
	//virtual void Build() = 0;
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual INT CheckUsingSkin();

protected:
	//virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	//virtual void _AddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _ConvertAndSetTitle(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	//virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _BuildItemIcon();
	virtual void _BuildAttrID();
	virtual CString _GetAttrString(TINFOTOKEN_ITEM eToken);
	virtual DWORD _GetAttrColor(TINFOTOKEN_ITEM eToken, DWORD dwDefaultColor );

public:
	CTItemInstDetInfo(
		TDETINFO_TYPE eType,
		CTClientItem* pItemInst,
		const CRect& rc);

	virtual ~CTItemInstDetInfo();
};

// =====================================================================
/**	@class		CTSealedItemDetInfo
	@brief		���ε� �����ۿ� ���� �������� ���ް� ǥ�ø� ���� Ŭ����.
	
*/// ===================================================================
class CTSealedItemDetInfo : public CTItemInstDetInfo
{
public:	
	virtual void Build();
	//virtual BOOL Compare(const ITDetailInfo* pTarget);

protected:
	//virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	//virtual void _AddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	//virtual void _ConvertAndSetTitle(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	//virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	//virtual void _BuildItemIcon();
	//virtual void _BuildAttrID();
	//virtual CString _GetAttrString(TINFOTOKEN_ITEM eToken);

public:
	CTSealedItemDetInfo(
		TDETINFO_TYPE eType,
		CTClientItem* pItemInst,
		const CRect& rc);

	virtual ~CTSealedItemDetInfo();
};

// =====================================================================
/**	@class		CTMagicItemDetInfo
	@brief		�߰��ɼ�(���,����,����) �����ۿ� ���� �������� ���ް� ǥ�ø� ���� Ŭ����.
	
*/// ===================================================================
class CTOptionItemDetInfo : public CTItemInstDetInfo
{
public:
	/// ���� �ɼ� ��ū Ÿ��
	enum TINFOTOKEN_MAGICOPTION
	{
		TINFOTOKEN_MAGICOPTION1,
		TINFOTOKEN_MAGICOPTION2,
		TINFOTOKEN_MAGICOPTION3,
		TINFOTOKEN_MAGICOPTION4,
		TINFOTOKEN_MAGICOPTION5,
		TINFOTOKEN_MAGICOPTION6,
		TINFOTOKEN_MAGICOPTION_COUNT,
	};

	/// ���� ����Ÿ ��ū Ÿ��
	enum TINFOTOKEN_MAGICDATA
	{
		TINFOTOKEN_MAGICDATA1,
		TINFOTOKEN_MAGICDATA2,
		TINFOTOKEN_MAGICDATA3,
		TINFOTOKEN_MAGICDATA4,
		TINFOTOKEN_MAGICDATA5,
		TINFOTOKEN_MAGICDATA6,
		TINFOTOKEN_MAGICDATA_COUNT
	};

	/// ���� ���� ��ū Ÿ��
	enum TINFOTOKEN_MAGIC
	{
		TINFOTOKEN_MAGIC_TITLE,
		TINFOTOKEN_MAGIC_LEVEL,
		TINFOTOKEN_MAGIC_COUNT
	};

public:
	/// ������ ��ȭ ��ū
	static const CString TGRADEITEM_TOKEN;
	static const CString TGEMITEM_TOKEN;

protected:
	BOOL	m_bProcOption;

public:
	/// ���� �ɼ� ��ū ����Ʈ
	static const CString TMAGICOPTION_TOKENS[TINFOTOKEN_MAGICOPTION_COUNT];
	/// ���� ����Ÿ ��ū ����Ʈ
	static const CString TMAGICDATA_TOKENS[TINFOTOKEN_MAGICDATA_COUNT];
	/// ���� ���� ��ū ����Ʈ
	static const CString TMAGIC_TOKENS[TINFOTOKEN_MAGIC_COUNT];
	/// �ź� �ɼ� ������ ���� ���ڿ�
	static const CString TMAGICLEVEL_NAMES[TMAGICLEVEL_MAX];

public:	
	//virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

protected:
	virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	//virtual void _AddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _ConvertAndSetTitle(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	//virtual void _BuildAttrID();
	virtual CString _GetAttrString(TINFOTOKEN_ITEM eToken);

protected:
	BOOL _GetMagicOptionString(int nIdx, CString& outOption, CString& outData);
	CString _GetMagicString(int nIdx);
	BOOL _IsMagicLine( const CString& strLine );

public:
	CTOptionItemDetInfo(
		TDETINFO_TYPE eType,
		CTClientItem* pItemInst,
		const CRect& rc);

	virtual ~CTOptionItemDetInfo();

};

// =====================================================================
/**	@class		CTSkillDetInfo
	@brief		��ų�� ���� �������� ���ް� ǥ�ø� ���� Ŭ����.
*/// ===================================================================
class CTSkillDetInfo : public ITDetailInfo
{
public:
	/// ��ų Ÿ�� ��ū
	enum TINFOTOKEN_SKILL
	{
	TINFOTOKEN_SKILL_DATA1 = 0,
	TINFOTOKEN_SKILL_DATA2,
	TINFOTOKEN_SKILL_DATA3,
	TINFOTOKEN_SKILL_DATA4,
	TINFOTOKEN_SKILL_DATA5,
	TINFOTOKEN_SKILL_DATA6,
	TINFOTOKEN_SKILL_LEVEL,
	TINFOTOKEN_SKILL_HITRATE,
	TINFOTOKEN_SKILL_ACTTIME,
	TINFOTOKEN_SKILL_DURATION,
	TINFOTOKEN_SKILL_REUSE,
	TINFOTOKEN_SKILL_USEHP,
	TINFOTOKEN_SKILL_USEMP,
	TINFOTOKEN_SKILL_UPGRADETITLE,
	TINFOTOKEN_SKILL_PREVLEVEL,
	TINFOTOKEN_SKILL_CLASSPOINT,
	TINFOTOKEN_SKILL_SKILLPOINT,
	TINFOTOKEN_SKILL_NEXTLEVEL,
	TINFOTOKEN_SKILL_NEXTPRICE,
	TINFOTOKEN_SKILL_COUNT
	};

public:
	static const CString TSKILL_TOKENS[TINFOTOKEN_SKILL_COUNT];

protected:
    LPTSKILL	m_pTSkill;		///< ��ų ���ø�
	BYTE		m_bLevel;		///< ǥ���ϰ��� �ϴ� ��ų�� ����
	BOOL		m_bSkillReq;	///< ��ų �䱸���� ǥ�� ����

	/**
		Build �� ��ų�� ���� ������ ���� �󼼸� �����ϴ� 
		������ ������ ���׷��̵� �ϱ����� �󼼸� �����ϴ�
		�������� �����ϱ����� �÷���.
	*/
	BOOL		m_bProcUpgrade;

public:
	LPTSKILL GetSkillTemp() const	{ return m_pTSkill; }
	BYTE GetSkillLevel() const		{ return m_bLevel; }
	BOOL GetSkillReq() const		{ return m_bSkillReq; }

public:
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

protected:
	virtual LINE_STATE _GetLineState(const CString& strSource, int nIdx);
	virtual void _AddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _ConvertAndSetTitle(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);
	virtual void _ConvertAndAddLine(const CString& strSource, DWORD dwColor = TDEFAULT_TEXT_COLOR);

protected:
	CString _GetSkillString(TINFOTOKEN_SKILL eToken);

public:
	CTSkillDetInfo(
		LPTSKILL  pTSkill,
		BYTE bLevel,
		BOOL bSkillReq,
		const CRect& rc);

	virtual ~CTSkillDetInfo();
};

// =====================================================================
/**	@class		CTCastleDetInfo
	@brief		���� ���� �������� ���ް� ǥ�ø� ���� Ŭ����.
*/// ===================================================================
class CTCastleDefInfo : public ITDetailInfo
{
public :
	CString	m_strCastle;
	CTime	m_timeNext;
	CString	m_strAtkGuild;
	CString m_strDefGuild;
	WORD m_wAtkGuildPoint;
	WORD m_wAtkCountryPoint;
	BYTE m_bAtkCount;
	WORD m_wDefGuildPoint;
	WORD m_wDefCountryPoint;
	BYTE m_bDefCount;
	CString m_strMyGuild;
	WORD m_wMyGuildPoint;
	VTOP3 m_vDTop3;
	VTOP3 m_vCTop3;

public :
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();
	virtual CPoint GetUIPosition(const CRect& rcDetDlg, const CPoint& ptMouse );

public :
	CTCastleDefInfo(
		CString strCastle,
		CTime timeNext,
		CString strAtkGuild,
		CString strDefGuild,
		WORD wAtkGuildPoint,
		WORD wAtkCountryPoint,
		BYTE bAtkCount,
		WORD wDefGuildPoint,
		WORD wDefCountryPoint,
		BYTE bDefCount,
		CString strMyGuild,
		WORD wMyGuildPoint,
#ifdef MODIFY_GUILD
		VTOP3* vDTop3,
		VTOP3* vCTop3,
#endif
		const CRect& rc);

	virtual ~CTCastleDefInfo();

#ifdef MODIFY_GUILD
	void WriteCTop3();
	void WriteDTop3();
#endif
};

// =====================================================================
/**	@class		CTTerritoryDetInfo
	@brief		������ ���� �������� ���ް� ǥ�ø� ���� Ŭ����.
*/// ===================================================================

class CTTerritoryDetInfo : public ITDetailInfo
{
public:
	CString m_strTerritory;
	CTime m_timeNext;
	CString m_strHeroName;

public:
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();
	virtual CPoint GetUIPosition(const CRect& rcDetDlg, const CPoint& ptMouse );
public:
	CTTerritoryDetInfo(
		CString strTerritory, 
		CTime timeNext,
		CString strHeroName,
		const CRect& rc);

	virtual ~CTTerritoryDetInfo();
};

class CTPvPDetInfo : public ITDetailInfo
{
public:
	BYTE m_bTabIndex;
	CString m_strName;
	BYTE m_bWin;
	BYTE m_bClass;
	BYTE m_bLevel;
	DWORD m_dwPoint;
	CTime m_dlDate;
	DWORD m_dwTitleColor;	

public:
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

public:
	CTPvPDetInfo(
		BYTE bTabIndex,
		CString strName,
		BYTE bWin,
		BYTE bClass,
		BYTE bLevel,
		DWORD dwPoint,
		CTime dlDate,
		DWORD dwTitleColor,
		const CRect& rc );

	virtual ~CTPvPDetInfo();
};

class CTTextDetInfo : public ITDetailInfo
{
public:
	CString m_strText;
	CPoint m_ptPosition;

public:
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();
	virtual CPoint GetUIPosition(const CRect& rcDetDlg, const CPoint& ptMouse );

public:
	CTTextDetInfo(
		CString& strText,
		CPoint pt );

	virtual ~CTTextDetInfo();
};

class CTFameRankDetInfo : public ITDetailInfo
{
public:
	CString m_strName;
	DWORD	m_dwTotalPoint;
	DWORD	m_dwMonthPoint;
	WORD	m_wWin;
	WORD	m_wLose;
	BYTE	m_bLevel;
	BYTE	m_bClass;

public:

	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

public:
	CTFameRankDetInfo(
		CString strName,
		DWORD dwTotalPoint,
		DWORD dwMonthPoint,
		WORD wWin,
		WORD wLose,
		BYTE bLevel,
		BYTE bClass,
		const CRect& rc);

	virtual ~CTFameRankDetInfo();
};

class CTDefToolTipInfo : public ITDetailInfo
{
public :
	CString	m_strToolTip;
	CString m_strTitle;

public :
	virtual BOOL Compare( const ITDetailInfo* pTarget );
	virtual void Build();

public :
	CTDefToolTipInfo( CString strTitle, CString strToolTip, const CRect& rc );
	virtual ~CTDefToolTipInfo();

};

class CTTournamentPlayerInfo : public ITDetailInfo
{
public:
	CString m_strName;
	BYTE m_bWin;
	BYTE m_bCountry;
	BYTE m_bClass;
	BYTE m_bLevel;
	BYTE m_bInfoType;
	CString m_strText;
	INT m_nLine;

public:
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();

public:
	CTTournamentPlayerInfo(
		CString strName,
		BYTE bWin,
		BYTE bCountry,
		BYTE bClass,
		BYTE bLevel,
		const CRect& rc );

	CTTournamentPlayerInfo(
		CString strTitle,
		CString strText,
		int nLine,
		const CRect& rc );

	virtual ~CTTournamentPlayerInfo();
};

class CTMissionDetInfo : public ITDetailInfo
{
public:
	CString m_strMission;
	CTime m_timeNext;
	BYTE m_bCountry;
	BYTE m_bStatus;

public:
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();
	virtual CPoint GetUIPosition(const CRect& rcDetDlg, const CPoint& ptMouse );

public:
	CTMissionDetInfo(
		CString m_strMission, 
		CTime timeNext,
		BYTE m_bCountry,
		BYTE m_bStatus,
		const CRect& rc);

	virtual ~CTMissionDetInfo();
};

class CTPlayerDetInfo : public ITDetailInfo
{
public:
	CString m_strName;
	BYTE m_bLevel;
	BYTE m_bRace;
	BYTE m_bSex;
	BYTE m_bFace;
	BYTE m_bHair;
	BYTE m_bSenior;
	BYTE m_bClass;

public:
	virtual BOOL Compare(const ITDetailInfo* pTarget);
	virtual void Build();
	virtual CPoint GetUIPosition(const CRect& rcDetDlg, const CPoint& ptMouse );

	CTPlayerDetInfo(
		CString strName,
		BYTE bLevel,
		BYTE bRace,
		BYTE bSex,
		BYTE bFace,
		BYTE bHair,
		BYTE bSenior,
		BYTE bClass,
		const CRect& rc);

	virtual ~CTPlayerDetInfo();
};

typedef SharedPtr<ITDetailInfo>			ITDetailInfoPtr;
typedef SharedPtr<CTNorDetInfo>			CTNorDetInfoPtr;
typedef SharedPtr<CTItemDetInfo>		CTItemDetInfoPtr;
typedef SharedPtr<CTItemInstDetInfo>	CTItemInstDetInfoPtr;
typedef SharedPtr<CTSealedItemDetInfo>	CTSealedItemDetInfoPtr;
typedef SharedPtr<CTOptionItemDetInfo>	CTOptionItemDetInfoPtr;
typedef SharedPtr<CTSkillDetInfo>		CTSkillDetInfoPtr;
typedef SharedPtr<CTCastleDefInfo>		CTCastleDefInfoPtr;
typedef SharedPtr<CTTerritoryDetInfo>	CTTerritoryDetInfoPtr;
typedef SharedPtr<CTFameRankDetInfo>	CTFameRankDetInfoPtr;
typedef SharedPtr<CTTournamentPlayerInfo>	CTTournamentPlayerDetInfoPtr;
typedef SharedPtr<CTMissionDetInfo>	CTMissionDetInfoPtr;
typedef SharedPtr<CTPlayerDetInfo>	CTPlayerDetInfoPtr;
