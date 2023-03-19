#pragma once


class CTClientItem
{
public:
		WORD			m_wItemID;
		BYTE			m_bGemy;
	static MAPTQUESTCLNTITEM m_mapTQuestMagicClientItem;
	static CTClientItem* FindTQuestMagicClientItem( WORD wRewardID );

	static MAPDWORD m_mapTITEMTICK;		// Item reuse time data
	static MAPDWORD m_mapTITEMLOCK;		// Item lock data
	static DWORD m_dwEQUIPCOLOR;
	static DWORD m_dwNORMALCOLOR;
	BYTE 			m_bCanGamble;
public:
	static DWORD GetTick( WORD wDelayGroupID);
	static void SetTick(WORD wDelayGroupID, DWORD dwTick );
	static void ClearTick();

	static BYTE IsLocked( WORD wDelayGroupID);
	static void Unlock( WORD wDelayGroupID);
	static void Lock( WORD wDelayGroupID);
   
	static VECTORBYTE GetEquipSlotList(LPTITEM pTITEM);

	static LPTITEMVISUAL GetDefaultVisual( LPTITEM pTITEM);

	static DWORD CalcPrice(LPTITEM pTITEM, WORD wAttrLevel);
	static WORD CalcViewAttrLevel(WORD wAttrLevel);

protected:
	LPTITEM			m_pTITEM;
	BYTE			m_bItemID;
	

	BYTE			m_bCount;

	DWORD			m_dwDuraMax;
	DWORD			m_dwDuraCurrent;
	BYTE 			m_bRefineMax;
	BYTE 			m_bRefineCurrent;
	__time64_t	m_dEndTime;

	MAPTMAGIC		m_mapTMAGIC;
	BYTE			m_bGrade;

	BYTE			m_bInstGradeMax; //�Ͻ����� m_bGrade�� ���Ѱ� - CS_ITEMLEVELREVISION_ACK�� ���� ��Ʈ��
	BYTE			m_bWrap;
	BYTE			m_bELD;
	WORD		m_wColor;
	BYTE			m_bRegGuild;

	BOOL			m_bNeedUpdate;
	BYTE			m_bMagicGrade;		///< ���� �ɼ� ���
	LPTITEMMAGIC	m_pTBestOption;		///< �ְ� ������ �ɼ�

	WORD			m_wAttrID;			///< �� �������� �ɷ�ġ ���̵�
	WORD			m_wAttrLevel;		///< ���� ���� ����
	WORD			m_wViewAttrLevel;	///< ǥ�õǴ� ���� ����
	DWORD			m_dwPrice;			///< ���� ����

	VTMAGICOPTION m_vMagicInfos;		///< �����ɼ� ���� ����Ʈ

	BOOL	 		m_bApplyAP;			///< ���������� '�������ݷ�'�� ����Ǿ����� ����
	BOOL	 		m_bApplyMAP;		///< ���������� '�������ݷ�'�� ����Ǿ����� ����
	BOOL	 		m_bApplyDP;			///< ���������� '��������'�� ����Ǿ����� ����
	BOOL	 		m_bApplyMDP;		///< ���������� '��������'�� ����Ǿ����� ����

	FLOAT			m_fOptionLv;		///< ���� �ɼ� ����

	WORD	 		m_wApplyMagicID;	///< ���ɷ����� ���� �ɼ��� ���� ���̵�
	TITEMATTR		m_itemAttr;			///< ���� ������ ����

	BOOL			m_bHasMainOption;	///< ���οɼ��� �������� ����

public:
	CTClientItem& operator = ( CTClientItem& param);

	BYTE operator == ( CTClientItem& param);
	BYTE operator != ( CTClientItem& param);

public:
	void NotifyUpdate();
	void Update();
	
	WORD GetMagicValue(BYTE bMagicID);
	void ClearMagic();
	void AddMagicValue(BYTE bMagicID, WORD wValue);

	BOOL IsEmptyMagicInfos();
	LPVTMAGICOPTION GetMagicInfos();

	DWORD GetQuality() const;
	DWORD GetQualityColor() const;
	DWORD GetMagicColor() const;


	VECTORDWORD GetSFX();
	DWORD GetGradeSFX();
	DWORD GetMagicSFX();
    BYTE			m_bGradeEffect;
	LPTITEMGRADEVISUAL GetGradeVISUAL();
	LPTITEMVISUAL GetDefaultVisual();
	LPTITEMVISUAL GetVisual();
	BYTE GetVisualGrade();
	DWORD GetVisualColor();

	void SetItemSlot(CPacket* pPacket);
	void SetItemData(CPacket* pPacket, BOOL bUseEndTime=TRUE);
	void SetItemMagic(CPacket* pPacket);

	BOOL CheckValid();

protected:
	void InitAttrVar();
	void CalcAttrID();
	void CalcAttrID(const TITEMATTR& itemAttr);

	BYTE GetWeaponPowerLevel();
	BYTE GetShieldPowerLevel();
	BYTE GetPowerLevel();
	void CalcAttrNameAndLevel();

public:
	void SetTITEM(LPTITEM p);				
	void SetItemSlot(BYTE p);				
	void SetItemID(WORD p);				
	void SetCount(BYTE p);					
	void SetDuraMax(DWORD p);				
	void SetDuraCurrent(DWORD p);			
	void SetRefineMax(BYTE p);				
	void SetRefineCurrent(BYTE p);			
	void SetCanGamble(BYTE p);				
	void SetGrade(BYTE p);					
	void SetGradeEffect(BYTE p);
	void SetEndTime( __time64_t);
	void SetWrap( BYTE bWrap );
	void SetGems( BYTE bGemy );
	void SetELD( BYTE bELD );
	void SetColor( WORD bColor );
	void SetRegGuild( BYTE bRegGuild );
	void SetInstGradeMax(BYTE bMax);

public:
	LPTITEM GetTITEM()					{ return m_pTITEM; }
	BYTE GetItemSlot()					{ return m_bItemID; }
	WORD GetItemID()					{ return m_wItemID; }
	BYTE GetCount()						{ return m_bCount; }
	DWORD GetDuraMax()					{ return m_dwDuraMax; }
	DWORD GetDuraCurrent()				{ return m_dwDuraCurrent; }
	BYTE GetGems()				        { return m_bGemy; }
	BYTE GetRefineMax()					{ return m_bRefineMax; }
	BYTE GetRefineCurrent()				{ return m_bRefineCurrent; }
	BYTE CanGamble()					{ return m_bCanGamble; }

	LPMAPTMAGIC GetTMAGIC()				{ return &m_mapTMAGIC; }
	__time64_t GetEndTime()			{ return m_dEndTime; }
	BYTE GetWrap()						{ return m_bWrap; }
	BYTE GetELD()						{ return m_bELD; }
	WORD GetColor()					{ return m_wColor; }
	BYTE GetRegGuild()				{ return m_bRegGuild; }

	BOOL HasMainMagicOption()			{ Update(); return m_bHasMainOption; }
	WORD GetAttrID()					{ Update(); return m_wAttrID; }
	WORD GetAttrLevel()					{ Update(); return m_wAttrLevel; }
	WORD GetViewAttrLevel()				{ Update(); return m_wViewAttrLevel; }
	DWORD GetPrice()					{ Update(); return m_dwPrice; }
	DWORD GetEffect()					{ Update(); return m_bGradeEffect; }
	DWORD GetSellPrice()				{ Update(); return m_dwPrice / 4; }
	BOOL GetApplyAP()					{ Update(); return m_bApplyAP; }
	BOOL GetApplyMAP()					{ Update(); return m_bApplyMAP; }	
	BOOL GetApplyDP()					{ Update(); return m_bApplyDP; }	
	BOOL GetApplyMDP()					{ Update(); return m_bApplyMDP; }
	FLOAT GetOptionLv()					{ Update(); return m_fOptionLv; }
	WORD GetApplyMagicID()				{ Update(); return m_wApplyMagicID; }
	LPTITEMATTR GetItemAttr()			{ Update(); return &m_itemAttr; }
	BYTE GetGrade() const
	{
		if( !m_bInstGradeMax || m_bGrade <= m_bInstGradeMax )
			return m_bGrade;
		return m_bInstGradeMax;
	}
		BYTE GetGemy() const
	{
			return m_bGemy;
	}
		BYTE GetGradeEffect() const
	{
			return m_bGradeEffect;
	}
		WORD GetKind() const
	{
			return m_pTITEM->m_bKind;
	}
public:
	CTClientItem();
	virtual ~CTClientItem();

};

