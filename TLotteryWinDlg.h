#pragma once


class CTLotWinDlg : public CTClientUIBase
{

public:

	TComponent* m_pGolds;
	TComponent* m_pSilvers;
	TComponent* m_pCrons;
	TComponent* m_pSText;
	TButton* m_pOK;


public:


public:
	void GenerateNumbers();
	CTLotWinDlg( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTLotWinDlg();
		virtual BOOL	CanWithItemUI();
		
};