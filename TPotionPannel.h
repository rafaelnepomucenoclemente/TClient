#pragma once

bool IsPREMIUMMaintain( CTClientMaintain* pMAINTAIN );
bool IsPREMIUMMaintain( LPTSKILL pTSKILL );


class CTPotionPannel : public CTClientUIBase
{
public:
	CTPotionPannel( TComponent *pParent, LP_FRAMEDESC pDesc);
	virtual ~CTPotionPannel();

public:


	void ResetPOTIONS(
		CTClientObjBase *pOBJ,
		DWORD dwTick);

	void ResetROTATION( DWORD dwTick);
	void HideAll();
	void AddMaintain(BYTE index, BYTE m_bIcon, DWORD dwTick, CTClientMaintain* pSkill, CTClientObjBase* pChar);
	void ClickedPNext();
	void ClickedPPrev();
	void ClickedNNext();
	void ClickedNPrev();
	virtual BOOL HitTest( CPoint pt);
	void FixMaintain(BYTE index,CTClientMaintain* pSkill, CTClientObjBase* pChar);
	void SetNewChar(CTClientObjBase* pChar);
	virtual ITDetailInfoPtr GetTInfoKey( const CPoint& point );
	BYTE						m_bCount;
public:

	HRESULT Render(DWORD dwTickCount);
protected:
	TImageList*				m_pMAINTAIN_ICON[ 10 ];
	TComponent*			m_pMAINTAIN_TIME[ 10 ];
	LPTSKILL					m_vMAINTAININFO_TSKILL[ 10 ];
	BYTE						m_vMAINTAININFO_LEVEL[ 10 ];

	CTClientObjBase*		m_pOBJ;
	CTClientObjBase*        m_pMainCh;
};
