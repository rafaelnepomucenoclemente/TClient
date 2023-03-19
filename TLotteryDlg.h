#pragma once


class CTLotteryDlg : public CTClientUIBase
{

public:

	TButton*	m_pStart;
    TComponent* m_pCisla[4];
	TComponent* m_pRune;
	TComponent* m_pSilver;
	TComponent* m_pCrons;


public:
	DWORD dwNum1,dwNum2,dwNum3,dwNum4;

public:
	void GenerateNumbers();
	CTLotteryDlg( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTLotteryDlg();
		virtual BOOL	CanWithItemUI();
		
};