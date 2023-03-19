#include "stdafx.h"
#include "TBowWaiting.h"
#include "TClientGame.h"
#define ID_BG_MAXIMIZE (0x0000695D)
#define ID_BG_REFRESH (0x00006B47)
#define ID_BG_PLAYERS (0x00006B46)
CTBowWaiting::CTBowWaiting( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{

    m_pBGPlayers = static_cast<TComponent*>(FindKid(ID_BG_PLAYERS));
	m_pBGReFresh = static_cast<TButton*>(FindKid(ID_BG_REFRESH));
    m_pBGMaximize = static_cast<TButton*>(FindKid(ID_BG_MAXIMIZE));

	m_1Min = static_cast<TImageList*>(FindKid(ID_BOWTIME_MIN1));
    m_2Min = static_cast<TImageList*>(FindKid(ID_BOWTIME_MIN2));
	m_1Sec = static_cast<TImageList*>(FindKid(ID_BOWTIME_SEC1));
    m_2Sec = static_cast<TImageList*>(FindKid(ID_BOWTIME_SEC2));
	m_pBGPlayers->ShowComponent(FALSE);
	m_pBGReFresh->ShowComponent(FALSE);
	m_pBGMaximize->ShowComponent(FALSE);
	SetTime(15,04);
}

CTBowWaiting::~CTBowWaiting()
{

}
BOOL CTBowWaiting::CanWithItemUI()
{
	return TRUE;
}
void CTBowWaiting::SetTime(BYTE bMin, BYTE bSec)
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

