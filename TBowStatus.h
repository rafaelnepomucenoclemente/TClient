#pragma once


class CTBowStatus : public CTClientUIBase
{

public:
TButton*	m_pRank;
	TButton*	m_pSurr;
   
	TComponent* m_bValoP;
    TComponent* m_bDeroP;

	TImageList* m_1Min;
    TImageList* m_2Min;
	TImageList* m_1Sec;
    TImageList* m_2Sec;

	TComponent* m_Miss;
    TComponent* m_Yes;
	
	TComponent* m_No;
    TComponent* m_Finish;

public:



public:
		virtual void SetTime(BYTE bMin, BYTE bSec);


public:
	CTBowStatus( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual BOOL	CanWithItemUI();
	virtual ~CTBowStatus();
};