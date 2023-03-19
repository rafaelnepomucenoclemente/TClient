#pragma once


class CTMinimapDlg : public CTClientUIBase
{
public:
	static LPDIRECT3DTEXTURE9 m_pTMINIMAP;
	static LPDIRECT3DTEXTURE9 m_pTMASK;

public:
	TComponent *m_vTCOMP[TMINIMAPCOMP_COUNT];
	TComponent *m_pTEST;
	TComponent *m_pTITLE;
	TComponent *pMPTEXT;
	TComponent *pMPTEXT2;

	TComponent *m_pTOPFRAME;
	TGauge *m_pMINMAXBTN;
	TGauge *pHPGauge;
	TGauge *pMPGauge;
	CD3DDevice *m_pDevice;
	BYTE m_bMinimize;

	CTClientChar *m_pHost;
	LPMAPMONSTER m_pTMON;
	CTRSCSDlg *m_pTRSCS;

	CTClientMAP *m_pTMAP;
	CTClientCAM *m_pCAM;
	CRect m_rcAREA;

	TScroll *m_pTZOOMSCROLL;

public:
	void RenderTMINIMAP();
	void ResetVisible();

public:
	virtual BOOL CanWithItemUI();
	virtual BOOL DoMouseWheel( UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL HitTest( CPoint pt);
	virtual void ShowComponent( BOOL bVisible = TRUE);
	virtual HRESULT Render( DWORD dwTickCount);

public:
	CTMinimapDlg( TComponent *pParent, LP_FRAMEDESC pDesc);
	virtual ~CTMinimapDlg();
};
