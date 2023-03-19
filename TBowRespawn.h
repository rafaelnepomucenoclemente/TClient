#pragma once


class CTBowRevDlg : public CTClientUIBase
{

public:

	TButton*	m_pRespawn;
	TComponent* m_pText;
	TComponent* m_pMedals;

public:


public:
	CTBowRevDlg( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTBowRevDlg();
		virtual BOOL	CanWithItemUI();
};