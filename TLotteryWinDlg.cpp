#include "stdafx.h"
#include "TLotteryWinDlg.h"
#include "TClientGame.h"
#define ID_GOLDY (0x00006293)
#define ID_STRIBRA (0x00006294)
#define ID_BRONZY (0x00006295)
#define ID_SKILLTEXT (0x00006825)
#define ID_OK_BUT (0x00006828)
CTLotWinDlg::CTLotWinDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{
	m_pGolds = static_cast<TComponent*>(FindKid(ID_GOLDY));
	m_pSilvers = static_cast<TComponent*>(FindKid(ID_STRIBRA));
	m_pCrons = static_cast<TComponent*>(FindKid(ID_BRONZY));
	m_pSText = static_cast<TComponent*>(FindKid(ID_SKILLTEXT));
	m_pOK = static_cast<TButton*>(FindKid(ID_OK_BUT));
	m_pSText->m_strText = "Increased exp rate : +15% (4 mins.)";  //custom

}
BOOL CTLotWinDlg::CanWithItemUI()
{
	return TRUE;
}
CTLotWinDlg::~CTLotWinDlg()
{

}

