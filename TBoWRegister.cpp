#include "stdafx.h"
#include "TBoWRegister.h"
#include "TClientGame.h"

CTBowRegister::CTBowRegister( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{

	m_pRegister = static_cast<TButton *>(FindKid(ID_BOW_REGISTER));

	m_pText = static_cast<TComponent *>(FindKid(ID_BOW_REGTEXT)); // CUSTOM
	//m_pTime = static_cast<TComponent *>(FindKid(ID_BOW_TIME));

	m_pRegister->m_menu[TNM_LCLICK] = GM_SENDBOW_REQ;
}

CTBowRegister::~CTBowRegister()
{

}

