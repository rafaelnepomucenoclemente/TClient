#pragma once


class CTClientPet : public CTClientRecall
{
protected:
	WORD		m_wPetID;
	CTime		m_tPetEndTime;
	LPTPET		m_pPetTemp;
	CString		m_strPetName;
  
	DWORD			m_dwTakeUpPivot;
	CTClientChar*	m_pTakeUpChar;

	FLOAT		m_fBaseSpeedFactor;
	FLOAT		m_fBaseSpeedFactor_org;

public:
	void SetPetInfo(const CString& strName, WORD wPetID, const CTime& tEndTime);
	void SetSaddle(WORD wItemID, const CTime& tEndTime);
  WORD wSaddleID;
	BYTE bSaddleType;
	CTime m_tSaddleTime;

	BOOL TakeUp(
		CD3DDevice *pDevice,
		CTachyonRes *pRES,
		CTClientChar *pChar,
		DWORD dwPivot);

	CTClientChar* TakeDown();
	FLOAT GetSpeedWhenRiding();
	void SetSpeedWhenRiding(WORD wMulti);
    BYTE bWhipped;
	CTClientChar* GetTakeUpChar() const		{ return m_pTakeUpChar; }
	const CString& GetPetName() const		{ return m_strPetName; }
	WORD GetPetID() const					{ return m_wPetID; }
	const CTime& GetPetEndTime() const		{ return m_tPetEndTime; }
	LPTPET GetPetTemp() const				{ return m_pPetTemp; }
	const CString& GetPetKindName() const	{ return m_pTEMP->m_strNAME; }
	virtual BYTE IsDrawNameWhenDead() { return FALSE; }

public:
	virtual BYTE GetDrawName();
	virtual CString GetTitle();
	virtual CString GetName();
	virtual CString GetUserTitle();
	virtual void ShowSFX();
	virtual void HideSFX();

	virtual BYTE CheckFall(
		CTClientMAP *pMAP,
		LPD3DXVECTOR2 pFallDIR);

	virtual void CalcFrame(BOOL bUpdate);
	virtual void CalcHeight(LPD3DXVECTOR3 pPREV, CTClientMAP *pMAP, DWORD dwTick);
	virtual void Render(CD3DDevice *pDevice, CD3DCamera *pCamera);

public:
	CTClientPet();
	virtual ~CTClientPet();
};
