#include "stdafx.h"
#include "TBowStatus.h"
#include "TClientGame.h"

CTBowStatus::CTBowStatus( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{
	m_bValoP = static_cast<TComponent*>(FindKid(ID_CTRLINST_VALOP));
    m_bDeroP = static_cast<TComponent*>(FindKid(ID_CTRLINST_DEROP));
	m_Miss = static_cast<TComponent*>(FindKid(ID_CTRLINST_MISSI));
    m_Yes = static_cast<TComponent*>(FindKid(ID_CTRLINST_BOW_YES));
	m_No = static_cast<TComponent*>(FindKid(ID_CTRLINST_BOW_NO));
    m_Finish = static_cast<TComponent*>(FindKid(ID_CTRLINST_BOW_FINISH));

	m_pRank = static_cast<TButton*>(FindKid(ID_BUTTON_BOWRANK));
    m_pSurr = static_cast<TButton*>(FindKid(ID_BUTTON_BOWSURR));

	m_1Min = static_cast<TImageList*>(FindKid(ID_BOWTIME_MIN1));
    m_2Min = static_cast<TImageList*>(FindKid(ID_BOWTIME_MIN2));
	m_1Sec = static_cast<TImageList*>(FindKid(ID_BOWTIME_SEC1));
    m_2Sec = static_cast<TImageList*>(FindKid(ID_BOWTIME_SEC2));


	m_Yes->m_strText = "";
	m_No->m_strText = "";
	m_Finish->m_strText = "";
	m_Miss->m_strText = "";




}

CTBowStatus::~CTBowStatus()
{

}
BOOL CTBowStatus::CanWithItemUI()
{
	return TRUE;
}
void CTBowStatus::SetTime(BYTE bMin, BYTE bSec)
{
		BYTE bMin1 = bMin / 10;
		BYTE bMin2 = bMin % 10;

		BYTE bSec1 = bSec / 10;
		BYTE bSec2 = bSec % 10;

		if(bMin <= 10)
		{
		m_1Min->SetCurImage(0);
		m_2Min->SetCurImage(bMin);
		}
		if(bSec <= 10)
		{
		m_1Sec->SetCurImage(0);
		m_2Sec->SetCurImage(bSec);
		}
		if(bMin >= 10)
		{
		m_1Min->SetCurImage(bMin1);
		m_2Min->SetCurImage(bMin2);
		}
		if(bSec >= 10)
		{
		m_1Sec->SetCurImage(bSec1);
		m_2Sec->SetCurImage(bSec2);

		}
}

