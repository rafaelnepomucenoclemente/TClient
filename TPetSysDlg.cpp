#include "StdAfx.h"
#include "TPetSysDlg.h"
#include "TClientGame.h"
//#include "TCustomStrings.h"

#define TCOMPANION_EXHAUSTED_HP (2400)
#define TCOMPANION_NORMAL_HP	(10000)
#define TCOMPANION_HEALTHY_HP	(129600)
#define TSTR_CUSTOM_COMPANION_EXP		"%d / %d"
#define TSTR_CUSTOM_COMPANION_HP		"HP: %d"
#define TSTR_CUSTOM_COMPANION_LEVEL		"Level: %d"
#define TSTR_CUSTOM_COMPANION_DESPAWN	"Withdraw"
#define TSTR_CUSTOM_COMPANION_SPAWN		"Call"
#define TSTR_COMPANION_EXHAUSTED		"Exhausted"
#define TSTR_COMPANION_NORMAL			"Normal"
#define TSTR_COMPANION_HEALTHY			"Healthy"

CTPetSysDlg::CTPetSysDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
	: CTClientUIBase(pParent, pDesc)
{
	m_pIcon = static_cast<TImageList*>(FindKid(ID_PET_SLOT1));
	m_pName = static_cast<TComponent*>(FindKid(ID_PET_NAME));
	m_pBonusName = static_cast<TComponent*>(FindKid(ID_PET_BONUS));
	m_pStatus = static_cast<TComponent*>(FindKid(ID_PET_STATUS));
	m_pHP = static_cast<TComponent*>(FindKid(ID_PET_HP));
	m_pExp = static_cast<TComponent*>(FindKid(ID_PET_EXP));
	m_pLevel = static_cast<TComponent*>(FindKid(ID_PET_LEVEL));
	m_pSummon = static_cast<TButton*>(FindKid(ID_PET_SUMMON));
	m_pDelete = static_cast<TButton*>(FindKid(ID_PET_DELETE));
	m_pLevelUp = static_cast<TButton*>(FindKid(ID_PET_LEVELUP));
	m_pTab1 = static_cast<TButton*>(FindKid(ID_PET_TAB1));
	m_pTab2 = static_cast<TButton*>(FindKid(ID_PET_TAB2));
	
	m_pHPBar = static_cast<TGauge*>(FindKid(ID_PET_EXPBAR));
	m_pExpBar = static_cast<TGauge*>(FindKid(ID_PET_HPBAR));
	m_pArrowUP = static_cast<TButton*>(FindKid(ID_PET_ARROWUP)); 

	m_pTab1Shown = static_cast<TComponent*>(FindKid(ID_PET_STATUI));
	m_pStatPText = static_cast<TComponent*>(FindKid(ID_PET_STATTEXT));
	m_pStatPValue = static_cast<TComponent*>(FindKid(ID_PET_STATVALUE));

	m_pSlot1T = static_cast<TImageList*>(FindKid(ID_PET_SLOTV1));
	m_pSlot2T = static_cast<TImageList*>(FindKid(ID_PET_SLOTV2));

	m_pBonusT = static_cast<TComponent*>(FindKid(ID_PET_BONUSTAB_TEXT));
	m_pLeftSwitch = static_cast<TButton*>(FindKid(ID_PET_LEFTSWITCH));
	m_pRightSwitch = static_cast<TButton*>(FindKid(ID_PET_RIGHTSWITCH));

	static DWORD dwStatT[6] =
	{
		ID_PET_STRTEXT,	//TCHARSTAT_STR
		ID_PET_AGITEXT,	//TCHARSTAT_DEX
		ID_PET_ENDTEXT,	//TCHARSTAT_CON
		ID_PET_INTTEXT,	//TCHARSTAT_INT
		ID_PET_WISTEXT,	//TCHARSTAT_WIS
		ID_PET_WILLTEXT	//TCHARSTAT_MEN
	};

	static DWORD dwStatB[6] =
	{
		ID_PET_STRBUT,
		ID_PET_AGIBUT,
		ID_PET_ENDBUT,
		ID_PET_INTBUT,
		ID_PET_WISBUT,
		ID_PET_WILLBUT

	};

    static DWORD dwStatV[6] =
	{
		ID_PET_STRVAL,	//TCHARSTAT_STR
		ID_PET_AGIVAL,	//TCHARSTAT_DEX
		ID_PET_ENDVAL,	//TCHARSTAT_CON
		ID_PET_INTVAL,	//TCHARSTAT_INT
		ID_PET_WISVAL,	//TCHARSTAT_WIS
		ID_PET_WILLVAL	//TCHARSTAT_MEN
	};

	static DWORD dwPET[5] =
	{
		ID_PET_1,
		ID_PET_2,
		ID_PET_3,
		ID_PET_4,
		ID_PET_5
	};

	static DWORD dwAttrT[5] =
	{
		ID_PET_BONUS1T,
		ID_PET_BONUS2T,
		ID_PET_BONUS3T,
		ID_PET_BONUS4T,
		ID_PET_BONUS5T
	};

	static DWORD dwAttrV[5] =
	{
		ID_PET_BONUS1V,
		ID_PET_BONUS2V,
		ID_PET_BONUS3V,
		ID_PET_BONUS4V,
		ID_PET_BONUS5V
	};

	for( BYTE i=0; i < TCHARSTAT_COUNT; ++i)
		m_pStatT[i] = static_cast<TComponent*>(FindKid( dwStatT[i] ));

	for( BYTE i=0; i < TCHARSTAT_COUNT; ++i)
	{
		m_pStatV[i] = static_cast<TComponent*>(FindKid( dwStatV[i] ));
		m_pStatV[i]->m_strText = "0 + (1)";
	}

	for( BYTE i=0; i < TCHARSTAT_COUNT; ++i)
	    m_pStatB[i] =  static_cast<TButton*>(FindKid( dwStatB[i] ));

	for( BYTE i=0; i < 5; ++i)
		m_pPet[i] = static_cast<TImageList*>(FindKid( dwPET[i] ));

	for( BYTE i=0; i < 5; ++i)
		m_pAttr[i] = static_cast<TComponent*>(FindKid( dwAttrT[i] ));
	
	for( BYTE i=0; i < 5; ++i)
		m_pAttrV[i] = static_cast<TComponent*>(FindKid( dwAttrV[i] ));

	m_pStatPValue->m_strText = "0";

	ClearCompanion();

	m_pAttr[0]->m_strText = "FACK";
	m_pAttrV[0]->m_strText = "+ 20%";

	SelectTab(2);
	
	m_pLevelUp->ShowComponent(FALSE);
	m_pLevelUp->EnableComponent(FALSE);

	m_pSummon->m_menu[TNM_LCLICK] = GM_SUMMON_PET;
	m_pDelete->m_menu[TNM_LCLICK] = GM_COMPANION_WARN_DELETE;

	m_pLeftSwitch->m_menu[TNM_LCLICK] = GM_SELECTCOMPANION_PREV;
	m_pRightSwitch->m_menu[TNM_LCLICK] = GM_SELECTCOMPANION_NEXT;

	m_pTab1->m_menu[TNM_LCLICK] = GM_COMPANION_TABONE;
	m_pTab2->m_menu[TNM_LCLICK] = GM_COMPANION_TABTWO;
}

CTPetSysDlg::~CTPetSysDlg()
{
	ClearCompanion();
}

void CTPetSysDlg::PrepareDisplay()
{
	BYTE bCount = m_mapCompanion.size();

	for( BYTE i=0; i < bCount; ++i)
		m_pPet[i]->SetCurImage(2);
}

void CTPetSysDlg::AddCompanion( CTClientCompanion* pCOMPANION )
{
	BYTE bSlot = pCOMPANION->GetSlot();

	m_mapCompanion.insert( CTCompanionMap::value_type( bSlot, pCOMPANION));

	SelCompanion( 0 );
}

void CTPetSysDlg::DelCompanion( BYTE bSlot )
{
	CTCompanionMap::iterator finder = m_mapCompanion.find( bSlot );
	if( finder != m_mapCompanion.end() )
	{
		delete (*finder).second;
		m_mapCompanion.erase( CTCompanionMap::key_type( bSlot ));
	}

	CTCompanionMap::iterator it;
	BYTE bLastSlot = bSlot;

	ClearDisplay();
	
	for( it = m_mapCompanion.begin(); it != m_mapCompanion.end(); ++it)
	{
		if( (*it).second->GetSlot() == bLastSlot+1 )
		{
			CTClientCompanion* pCOMPANION = (*it).second;
			(*it).second->SetSlot( bLastSlot );
			m_mapCompanion.insert( CTCompanionMap::value_type( bLastSlot, pCOMPANION));
			delete (*it).second;
			m_mapCompanion.erase( CTCompanionMap::key_type( bLastSlot+1 ));
		}

		bLastSlot = (*it).second->GetSlot() + 1;
	}

	BYTE bSel = ((bLastSlot - 1) < 0) ? 0 : (bLastSlot - 1);

	PrepareDisplay();
	SelCompanion( bSel );
}

void CTPetSysDlg::DisplayCompanion( BYTE bSlot )
{
	CTClientCompanion* pCOMPANION;

	CTCompanionMap::iterator finder = m_mapCompanion.find( bSlot );
	if( finder != m_mapCompanion.end() )
		pCOMPANION = (*finder).second;
	else
		ClearDisplay();

	CString strLevel;
	CString strExp;
	CString strHP;

	DWORD dwExp		= pCOMPANION->GetExp();
	DWORD dwNextExp = pCOMPANION->GetNextExp();

	DWORD dwLife	= pCOMPANION->GetLife();

	dwSelExp = dwExp; 
	dwSelNextExp = dwNextExp;

	LPTMONTEMP pTMON = CTChart::FindTMONTEMP(pCOMPANION->GetMonID());

	m_pIcon->SetCurImage( (int)pTMON->m_wFaceIcon );

	if( dwLife < TCOMPANION_EXHAUSTED_HP )
	{
		m_pStatus->m_strText = TSTR_COMPANION_EXHAUSTED;
//		m_pStatus->SetTextClr( TCOLOR_COMPANION_EXHAUSTED );
	}
	else if( dwLife <= TCOMPANION_NORMAL_HP )
	{
		m_pStatus->m_strText = TSTR_COMPANION_NORMAL;
//		m_pStatus->SetTextClr( TCOLOR_COMPANION_NORMAL );
	}
	else if( dwLife <= TCOMPANION_HEALTHY_HP )
	{
		m_pStatus->m_strText = TSTR_COMPANION_HEALTHY;
//		m_pStatus->SetTextClr( TCOLOR_COMPANION_HEALTHY );
	}

	strLevel.Format(TSTR_CUSTOM_COMPANION_LEVEL, pCOMPANION->GetLevel());
	if( dwNextExp > 0 )
		strExp.Format(TSTR_CUSTOM_COMPANION_EXP, dwExp, dwNextExp);
	else
		strExp = "Maximum Experience";
	strHP.Format(TSTR_CUSTOM_COMPANION_HP, dwLife);
	m_pHP->m_strText = strHP;
	m_pName->m_strText = pCOMPANION->GetCompanionName();
	m_pLevel->m_strText= strLevel;
	
	m_pExp->m_strText = strExp;
	m_pExpBar->SetGauge(dwExp, dwNextExp, 0);
	m_pHPBar->SetGauge(dwLife, 11000, 0);
}

void CTPetSysDlg::SelCompanion( BYTE bSlot )
{
	CTCompanionMap::iterator finder = m_mapCompanion.find( bSlot );
	if( finder == m_mapCompanion.end() )
		return;

	m_bPrevSelSlot = m_bCurSelSlot;
	m_bLastSelSlot = bSlot;
	m_bCurSelSlot = bSlot;

	int bSlotDiff = m_bCurSelSlot - m_bPrevSelSlot;

	CPoint btnPos;
	m_pArrowUP->GetComponentPos(&btnPos);

	btnPos.x = btnPos.x + (16 * bSlotDiff);
	m_pArrowUP->MoveComponent(btnPos);

	m_pPet[m_bPrevSelSlot]->SetCurImage(2);
	m_pPet[bSlot]->SetCurImage(1);

	DisplayCompanion( bSlot );
}

void CTPetSysDlg::SetSummonedSlot( BYTE bSlot )
{
	m_bSummonedSlot = bSlot;
	m_bIsSummoned = TRUE;
}

void CTPetSysDlg::Unsummon()
{
	m_bSummonedSlot = T_INVALID;
	m_bIsSummoned = FALSE;
}

CTClientCompanion* CTPetSysDlg::GetCompanionBySlot( BYTE bSlot )
{
	CTCompanionMap::iterator finder = m_mapCompanion.find( bSlot );
	if( finder != m_mapCompanion.end() )
		return (*finder).second;

	return NULL;
}

void CTPetSysDlg::Update()
{
	ClearDisplay();
	PrepareDisplay();
	SelCompanion( m_bLastSelSlot );
}

void CTPetSysDlg::ClearDisplay()
{
	m_pBonusT->m_strText.Empty();
	m_pSlot1T->SetCurImage(0);
	m_pSlot2T->SetCurImage(0);

	for( BYTE i=0; i < 5; ++i)
		m_pPet[i]->SetCurImage(0);

	CPoint btnPos;
	m_pArrowUP->GetComponentPos(&btnPos);
	btnPos.x = btnPos.x + (0 - m_bCurSelSlot)*16;
	m_pArrowUP->MoveComponent(btnPos);

	m_pHPBar->SetStyle(TGS_GROW_UP);
	m_pExpBar->SetStyle(TGS_GROW_RIGHT);
	m_pStatus->m_strText.Empty();
	m_pBonusName->m_strText.Empty();
	m_pName->m_strText.Empty();
	m_pHP->m_strText.Empty();
	m_pLevel->m_strText.Empty();
	m_pExp->m_strText.Empty();
	m_pHPBar->SetGauge(0,0,0);
	m_pExpBar->SetGauge(0,0,0);
	m_pIcon->SetCurImage(0);

	dwSelExp = 0;
	dwSelNextExp = 1;

	m_bCurSelSlot = 0;
	m_bPrevSelSlot = 0;
}

void CTPetSysDlg::ClearCompanion()
{
	ClearDisplay();

	m_bLastSelSlot = 0;
	m_bSelTab = 0;
	m_bSummonedSlot = T_INVALID;
	m_bIsSummoned = FALSE;

	CTCompanionMap::iterator it;
	for( it = m_mapCompanion.begin(); it != m_mapCompanion.end(); ++it)
		delete (*it).second;

	m_mapCompanion.clear();
}

HRESULT CTPetSysDlg::Render(DWORD dwTickCount)
{	
	/*for(int i = 0; i<5; i++)
		m_pAttr[i]->ShowComponent(FALSE);
	for(int i = 0; i<5; i++)
		m_pAttrV[i]->ShowComponent(FALSE);*/

	if(m_mapCompanion.size() == 0)
	{
		m_pArrowUP->ShowComponent(FALSE);
		m_pLeftSwitch->ShowComponent(FALSE);
		m_pRightSwitch->ShowComponent(FALSE);
		m_pDelete->EnableComponent(FALSE);
		m_pSummon->EnableComponent(FALSE);
	}
	else if(m_mapCompanion.size() > 0)
	{	
		m_pArrowUP->ShowComponent(TRUE);
		m_pLeftSwitch->ShowComponent(TRUE);
		m_pRightSwitch->ShowComponent(TRUE);
		m_pDelete->EnableComponent(TRUE);
		m_pSummon->EnableComponent(TRUE);
	}

	if( m_bSelTab == 1 )
	{
		m_pTab1->Select(FALSE);
		m_pTab2->Select(TRUE);

		for( BYTE i=0; i < 5; ++i)
			m_pAttr[i]->ShowComponent(FALSE);

		for( BYTE i=0; i < 5; ++i)
			m_pAttrV[i]->ShowComponent(FALSE);

		for( BYTE i=0; i < TCHARSTAT_COUNT; ++i) //?TRUE:FALSE
			m_pStatT[i]->ShowComponent(TRUE);

		for( BYTE i=0; i < TCHARSTAT_COUNT; ++i)
			m_pStatV[i]->ShowComponent(TRUE);

		for( BYTE i=0; i < TCHARSTAT_COUNT; ++i)
			m_pStatB[i]->ShowComponent(TRUE);

		m_pTab1Shown->ShowComponent(TRUE);
		m_pStatPText->ShowComponent(TRUE);
		m_pStatPValue->ShowComponent(TRUE);
	}
	else if( m_bSelTab == 2 )
	{
		m_pTab1->Select(TRUE);
		m_pTab2->Select(FALSE);
//WAIT
		for( BYTE i=0; i < TCHARSTAT_COUNT; ++i)
			m_pStatT[i]->ShowComponent(FALSE);

		for( BYTE i=0; i < TCHARSTAT_COUNT; ++i) //?FALSE
			m_pStatV[i]->ShowComponent(FALSE); //what is problem?!!!!!!!
	
		for( BYTE i=0; i < 5; ++i)
			m_pAttr[i]->ShowComponent(TRUE);

		for( BYTE i=0; i < 5; ++i)
			m_pAttrV[i]->ShowComponent(TRUE);

		for( BYTE i=0; i < TCHARSTAT_COUNT; ++i)
			m_pStatB[i]->ShowComponent(FALSE);

		m_pTab1Shown->ShowComponent(FALSE);
		m_pStatPText->ShowComponent(FALSE);
		m_pStatPValue->ShowComponent(FALSE);
	}

	if( m_bCurSelSlot == m_bSummonedSlot )
	{
		m_pSummon->m_strText = TSTR_CUSTOM_COMPANION_DESPAWN;
		m_pDelete->EnableComponent(FALSE);
	}
	else
	{
		m_pSummon->m_strText = TSTR_CUSTOM_COMPANION_SPAWN;
		m_pDelete->EnableComponent(TRUE);
	}
	
	if(dwSelExp <= dwSelNextExp)
	{
		m_pSummon->ShowComponent(TRUE);
		m_pDelete->ShowComponent(TRUE);
		m_pLevelUp->ShowComponent(FALSE);
	}
	else
	{
		m_pSummon->ShowComponent(FALSE);
		m_pDelete->ShowComponent(FALSE);
		m_pLevelUp->ShowComponent(TRUE);
	}

	return CTClientUIBase::Render(dwTickCount);
}
