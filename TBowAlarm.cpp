#include "stdafx.h"
#include "TBowAlarm.h"
#include "TClientGame.h"

CTBowAlarm::CTBowAlarm( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{

	m_pAlarm = static_cast<TButton *>(FindKid(ID_BOW_BUTTON));

	m_pText = static_cast<TComponent *>(FindKid(ID_BOW_TEXT)); // CUSTOM
	m_pTime = static_cast<TComponent *>(FindKid(ID_BOW_TIME));


	m_pAlarm->m_menu[TNM_LCLICK] = GM_BOW_REGISTER;

	//m_pList2->AddString(CString(), 1);
}
BOOL CTBowAlarm::CanWithItemUI()
{
	return TRUE;
}
CTBowAlarm::~CTBowAlarm()
{

}

