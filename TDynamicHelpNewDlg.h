#pragma once


class CTDynamicHelpNewDlg : public CTClientUIBase
{

protected:
		LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DTEXTURE9 *m_pTEX;

	LPWORD m_pHEIGHT;
	LPWORD m_pWIDTH;

	DWORD m_dwTRES;
	DWORD m_dwTPOS;

	int m_nPartCount;
	int m_nHEIGHT;
	int m_nWIDTH;

public:
	DWORD m_dwTSPEED;
      
TComponent* m_pText;
public:
	void InitTEXT( CString& strTEXT);
	virtual HRESULT Render( DWORD dwTickCount);
	void Release();


public:
	CTDynamicHelpNewDlg( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTDynamicHelpNewDlg();
};