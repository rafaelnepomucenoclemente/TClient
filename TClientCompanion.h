#pragma once


class CTClientCompanion : public CTClientRecall
{
protected:
	WORD		m_wMonID;
	WORD		m_wCompanionID;
	BYTE		m_bSlot;
	CString		m_strCompanionName;

	BYTE	m_bIsSpawned;

	DWORD	m_dwExp;
	DWORD	m_dwNextExp;
	DWORD	m_dwLife;
	BYTE	m_bLevel;

	WORD	m_wBonusID;
	WORD	m_wBonusValue;
	CString	m_strBonusName;

	WORD m_wSTR;
	WORD m_wDEX;
	WORD m_wCON;
	WORD m_wINT;
	WORD m_wWIS;
	WORD m_wMEN;

public:
	void Spawn();
	BOOL Despawn();

	void SetCompanionInfo( WORD wMonID, WORD wCompanionID, CString strName, DWORD dwExp, DWORD dwNextExp, DWORD dwLife, BYTE bLevel);

	void SetBonusInfo( WORD wBonusID, WORD wBonusValue );
	void SetCharATTR( WORD wSTR, WORD wDEX, WORD wCON, WORD wINT, WORD wWIS, WORD wMEN );

	void SetSlot( BYTE bSlot ) { m_bSlot = bSlot; }

	void UpdateLife( DWORD dwLife ) { m_dwLife = dwLife; }
	void UpdateExp( DWORD dwExp ) { m_dwExp = dwExp; }
	void UpdateNextExp( DWORD dwNextExp ) { m_dwNextExp = dwNextExp; }
	void UpdateLevel( BYTE bLevel ) { m_bLevel = bLevel; }

	BYTE GetSlot()			{ return m_bSlot; }
	DWORD GetExp()			{ return m_dwExp; }
	DWORD GetNextExp()		{ return m_dwNextExp; }
	DWORD GetLife()			{ return m_dwLife; }
	BYTE GetLevel()			{ return m_bLevel; }
	WORD GetBonusID()		{ return m_wBonusID; }
	WORD GetBonusValue()	{ return m_wBonusValue; }
	BOOL IsSpawned()		{ return m_bIsSpawned; }

	const CString& GetCompanionName() const	{ return m_strCompanionName; }
	WORD GetCompanionID() const				{ return m_wCompanionID; }
	WORD GetMonID() const					{ return m_wMonID; }

	virtual BYTE IsDrawNameWhenDead() { return FALSE; }

public:
	virtual BYTE GetDrawName();
	virtual void Render(CD3DDevice *pDevice, CD3DCamera *pCamera);

public:
	CTClientCompanion();
	virtual ~CTClientCompanion();
};