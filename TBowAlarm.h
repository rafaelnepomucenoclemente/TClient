#pragma once


class CTBowAlarm : public CTClientUIBase
{

public:

	TButton*	m_pAlarm;
	TComponent* m_pText;
	TComponent* m_pTime;

public:


public:
	CTBowAlarm( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTBowAlarm();
		virtual BOOL	CanWithItemUI();
};