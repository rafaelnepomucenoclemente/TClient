#pragma once


class CTBowWaiting : public CTClientUIBase
{

public:
	TButton*	m_pBGReFresh;
	TButton*	m_pBGMaximize;
	TComponent* m_pBGPlayers;   


	TImageList* m_1Min;
    TImageList* m_2Min;
	TImageList* m_1Sec;
    TImageList* m_2Sec;



public:



public:
		virtual void SetTime(BYTE bMin, BYTE bSec);


public:
	CTBowWaiting( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual BOOL	CanWithItemUI();
	virtual ~CTBowWaiting();
};