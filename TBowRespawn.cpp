#include "stdafx.h"
#include "TBowRespawn.h"
#include "TClientGame.h"

CTBowRevDlg::CTBowRevDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{
	m_pRespawn = static_cast<TButton *>(FindKid(ID_CTRLINST_OK));
	m_pText = static_cast<TComponent *>(FindKid(ID_MEDALSNEW_TEXT)); // CUSTOM
	m_pMedals = static_cast<TComponent *>(FindKid(ID_MEDALSREAL_TEXT));
	m_pRespawn->m_menu[TNM_LCLICK] = GM_BOW_REGISTER;
	m_pMedals->m_strText = "50";
	m_pText->m_strText = "PreviEW";
}
BOOL CTBowRevDlg::CanWithItemUI()
{
	return TRUE;
}
CTBowRevDlg::~CTBowRevDlg()
{

}

