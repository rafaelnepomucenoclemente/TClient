#include "StdAfx.h"
#include "TClientGame.h"
#include "Resource.h"
#include "TTournamentMode.h"
#include "TPotionPannel.h"
static DWORD vGaugeFrameID[5][3] = {
	{ ID_FRAME_MY_GAUGE, ID_CTRLINST_POS_ME, TRUE},			// TGAUGE_FRAME_PLAYER
	{ ID_FRAME_RECALL_GAUGE, ID_CTRLINST_POS_RECALL, TRUE},	// TGAUGE_FRAME_SUMMON
	{ ID_FRAME_TARGET_GAUGE, ID_CTRLINST_POS_TARGET, TRUE},	// TGAUGE_FRAME_TARGET
	{ ID_FRAME_PARTY_GAUGE, ID_CTRLINST_POS_PARTY, TRUE},	// TGAUGE_FRAME_PARTY,
	{ ID_FRAME_NOTIFY, ID_CTRLINST_POS_NOTIFY, TRUE}};		// TGAUGE_FRAME_NOTIFY

#define ID_HOTKEY_TEXT_1 (0x0000673E)
#define ID_HOTKEY_TEXT_2 (0x0000673F)
#define ID_HOTKEY_TEXT_3 (0x00006740)
#define ID_HOTKEY_TEXT_4 (0x00006741)
#define ID_HOTKEY_TEXT_5 (0x00006742)
#define ID_HOTKEY_TEXT_6 (0x00006743)
#define ID_HOTKEY_TEXT_7 (0x00006744)
#define ID_HOTKEY_TEXT_8 (0x00006745)
#define ID_HOTKEY_TEXT_9 (0x00006746)
#define ID_HOTKEY_TEXT_10 (0x00006747)
#define ID_HOTKEY_TEXT_11 (0x00006748)
#define ID_HOTKEY_TEXT_12 (0x00006749)
#define ID_USELESS_1 (0x00006A6B)
#define ID_USELESS_2 (0x00006A6C)
#define ID_USELESS_3 (0x00006A6D)
#define ID_USELESS_4 (0x00006A6E)
#define ID_USELESS_5 (0x00006A6F)
#define ID_USELESS_6 (0x00006A70)
#define ID_USELESS_7 (0x00006A71)
#define ID_USELESS_8 (0x00006A72)
#define ID_USELESS_9 (0x00006A73)
#define ID_USELESS_10 (0x00006A74)
#define ID_USELESS_11 (0x00006A75)
#define ID_USELESS_12 (0x00006A76)
CTGaugePannel::CTGaugePannel( TComponent *pParent, LP_FRAMEDESC pDesc, TCMLParser *pParser, CTClientGame *pMainGame, CTClientChar *pHost)
:CTClientUIBase( pParent, pDesc)
{
	DWORD dwRecallpushID[] = {
		ID_CTRLINST_RECALL_SKILL_PUSH_1,
		ID_CTRLINST_RECALL_SKILL_PUSH_2,
		ID_CTRLINST_RECALL_SKILL_PUSH_3,
		ID_CTRLINST_RECALL_SKILL_PUSH_4};

	DWORD dwRecallSkillID[] = {
		ID_CTRLINST_RECALL_SKILL_1,
		ID_CTRLINST_RECALL_SKILL_2,
		ID_CTRLINST_RECALL_SKILL_3,
		ID_CTRLINST_RECALL_SKILL_4};

	DWORD dwRecallgaugeID[] = {
		ID_CTRLINST_RECALL_SKILL_GAUGE_1,
		ID_CTRLINST_RECALL_SKILL_GAUGE_2,
		ID_CTRLINST_RECALL_SKILL_GAUGE_3,
		ID_CTRLINST_RECALL_SKILL_GAUGE_4};

	DWORD dwRecallskillSMID[] = {
		ID_CTRLINST_RECALL_SKILL_SEL_1,
		ID_CTRLINST_RECALL_SKILL_SEL_2,
		ID_CTRLINST_RECALL_SKILL_SEL_3,
		ID_CTRLINST_RECALL_SKILL_SEL_4};

	DWORD dwRecallAIpushID[] = {
		ID_CTRLINST_MANUAL_AI_PUSH,
		ID_CTRLINST_ACTIVE_AI_PUSH,
		ID_CTRLINST_PASSIVE_AI_PUSH,
		ID_CTRLINST_BACK_AI_PUSH,
		ID_CTRLINST_STAY_AI_PUSH};

	DWORD dwRecallAISMID[] = {
		ID_CTRLINST_MANUAL_AI_SEL,
		ID_CTRLINST_ACTIVE_AI_SEL,
		ID_CTRLINST_PASSIVE_AI_SEL,
		ID_CTRLINST_BACK_AI_SEL,
		ID_CTRLINST_STAY_AI_SEL};

	DWORD dwRecallAI[] = {
		ID_CTRLINST_MANUAL_AI,
		ID_CTRLINST_ACTIVE_AI,
		ID_CTRLINST_PASSIVE_AI,
		ID_CTRLINST_BACK_AI,
		ID_CTRLINST_STAY_AI};
		
	DWORD vMaintainID[TPANNEL_COUNT][3] = {
		{ ID_FRAME_MAINTAIN2R, ID_FRAME_MY_GAUGE, ID_CTRLINST_MAINTAIN},		//TPANNEL_PLAYER
		{ ID_FRAME_MAINTAIN2R, ID_FRAME_RECALL_GAUGE, ID_CTRLINST_MAINTAIN},	//TPANNEL_SUMMON
		{ ID_FRAME_MAINTAIN2R, ID_FRAME_TARGET_GAUGE, ID_CTRLINST_MAINTAIN},	//TPANNEL_TARGET
		{ ID_FRAME_MAINTAIN1R, ID_FRAME_PARTY_GAUGE, ID_CTRLINST_MAINTAIN1},	//TPANNEL_PARTY1
		{ ID_FRAME_MAINTAIN1R, ID_FRAME_PARTY_GAUGE, ID_CTRLINST_MAINTAIN2},	//TPANNEL_PARTY2
		{ ID_FRAME_MAINTAIN1R, ID_FRAME_PARTY_GAUGE, ID_CTRLINST_MAINTAIN3},	//TPANNEL_PARTY3
		{ ID_FRAME_MAINTAIN1R, ID_FRAME_PARTY_GAUGE, ID_CTRLINST_MAINTAIN4},	//TPANNEL_PARTY4
		{ ID_FRAME_MAINTAIN1R, ID_FRAME_PARTY_GAUGE, ID_CTRLINST_MAINTAIN5},	//TPANNEL_PARTY5
		{ ID_FRAME_MAINTAIN1R, ID_FRAME_PARTY_GAUGE, ID_CTRLINST_MAINTAIN6}};	//TPANNEL_PARTY6
	
	m_bHotkeyBase = TRUE;
	m_pMainRecall = NULL;
	m_pHost = pHost;

	m_bUseBasis = FALSE;
	CPoint point;

	for( BYTE i=0; i<5; i++)
	{
		LP_FRAMEDESC pGAUGE = pParser->FindFrameTemplate(vGaugeFrameID[i][0]);
		TComponent *pTPOS = FindKid(vGaugeFrameID[i][1]);
		CTClientUIBase *pTFRAME = NULL;
/*
		switch(i)
		{
		//case TGAUGE_FRAME_NOTIFY	: pTFRAME = new CTDynamicHelpNewDlg( this, pGAUGE); break;
		default						: pTFRAME = new CTClientUIBase( this, pGAUGE); break;
		}
*/
		pTFRAME = new CTClientUIBase( this, pGAUGE); 
		pTPOS->GetComponentPos(&point);
		RemoveKid(pTPOS);
		delete pTPOS;
		AddKid(pTFRAME);

		if(vGaugeFrameID[i][2])
		{
			pTFRAME->m_bCanDrag = TRUE;
			pTFRAME->m_rcDrag.SetRect(
				0, 0,
				CTachyonRes::m_pDEVICE->m_option.m_dwScreenX,
				CTachyonRes::m_pDEVICE->m_option.m_dwScreenY);
		}

		pTFRAME->MoveComponent(point);
	}

	for( i=0; i<TPANNEL_COUNT; i++)
	{
		TComponent *pTFRAME = FindKid(vMaintainID[i][1]);

		CTMaintainPannel *pTPANNEL = new CTMaintainPannel( pTFRAME, pParser->FindFrameTemplate(vMaintainID[i][0]));
		TComponent *pTPOS = pTFRAME->FindKid(vMaintainID[i][2]);

		pTPOS->GetComponentPos(&point);
		pTFRAME->RemoveKid(pTPOS);
		delete pTPOS;

		pTPANNEL->m_id = vMaintainID[i][2];
		pTFRAME->AddKid(pTPANNEL);

		pTPANNEL->MoveComponent(point);
		pTPANNEL->ShowComponent(TRUE);
		pTPANNEL->EnableFloat(FALSE);

		m_vTMAINTAIN[i] = pTPANNEL;
	}

	{
		TComponent *pTFRAME = FindKid(ID_FRAME_PARTY_GAUGE);
		TComponent *pTPOS = pTFRAME->FindKid(ID_CTRLINST_MAINTAIN7);
		pTFRAME->RemoveKid(pTPOS);
		delete pTPOS;
	}
		

	m_pQList = (TList*) FindKid(ID_CTRLINST_QLIST);
	m_pQList->m_bNoHIT = TRUE;
	m_pQList->ShowComponent(TRUE);

	m_pQList->SetColumnAlign( 0, ALIGN_RIGHT);
	m_pQList->SetColumnAlign( 1, ALIGN_CENTER);
	m_pQList->SetColumnAlign( 2, ALIGN_RIGHT);
	m_pQList->ApplyUserColor(TRUE);
	m_pQList->RemoveAll();
	m_bSND = FALSE;

	{
		m_pLUCKY = FindKid(ID_CTRLINST_LUCKY);
		if( m_pLUCKY )
			m_pLUCKY->m_bNoHIT = TRUE;

		m_pLUCKY2 = FindKid( ID_CTRLINST_LUCKY2 );
		if ( m_pLUCKY2 )
			m_pLUCKY2->m_bNoHIT = TRUE;

		m_pLUCKY3 = FindKid( ID_CTRLINST_LUCKY3);
		m_pLUCKY4 = FindKid( ID_CTRLINST_LUCKY4);

		if( m_pLUCKY3 )
			m_pLUCKY3->m_bNoHIT = TRUE;

		if( m_pLUCKY4 )
			m_pLUCKY4->m_bNoHIT = TRUE;

		m_pLUCKY5 = FindKid( ID_CTRLINST_LUCKY5 );
		m_pLUCKY6 = FindKid( ID_CTRLINST_LUCKY6 );

		if( m_pLUCKY5 )
			m_pLUCKY5->m_bNoHIT = TRUE;

		if( m_pLUCKY6 )
			m_pLUCKY6->m_bNoHIT = TRUE;
	}

	{
		CPoint point;
		TComponent *pPOS = NULL;
		pPOS = FindKid(ID_CTRLINST_MINIMAP);
	
		pPOS->GetComponentPos(&point);
		point.y =+ 200;
		RemoveKid(pPOS);
	
		delete pPOS;

		{
			CTMinimapDlg *pMinimapDlg = new CTMinimapDlg( this, pParser->FindFrameTemplate(ID_FRAME_MINIMAP));
			AddKid(pMinimapDlg);
			pMinimapDlg->MoveComponent(point);
		
			pMinimapDlg->ShowComponent(TRUE);
			pMainGame->m_pTMinimap = pMinimapDlg;
		}

		{
			CTRSCSDlg *pTRSCSDlg = new CTRSCSDlg( this, pParser->FindFrameTemplate(ID_FRAME_RSCS));
			m_pTRSCS = pTRSCSDlg;
			pMainGame->m_pTRSCS = m_pTRSCS;
			AddKid(pTRSCSDlg);
			pTRSCSDlg->MoveComponent(point);
			pTRSCSDlg->ShowComponent(FALSE);
			pTRSCSDlg->EnableFloat(FALSE);
		}

		{
			m_pTournamentInfo = new CTTournamentMode(
				this,
				pParser->FindFrameTemplate(ID_FRAME_TOURNAMENT_MODE),
				CTTournamentMode::TM_BATTLE );

			AddKid(m_pTournamentInfo);
			m_pTournamentInfo->MoveComponent(point);
			m_pTournamentInfo->ShowComponent(FALSE);
			m_pTournamentInfo->EnableFloat(FALSE);
		}
	}

	{
		TComponent *pPOS = NULL;
		CPoint point;

		pPOS = FindKid(ID_CTRLINST_PET_SLOT);
		pPOS->GetComponentPos(&point);
		RemoveKid(pPOS);
		delete pPOS;

		m_pTRECALLFRM = new CTClientUIBase( this, pParser->FindFrameTemplate(ID_FRAME_RECALL_COMMAND));
		m_pTRECALLFRM->m_id = ID_CTRLINST_PET_SLOT;
		AddKid(m_pTRECALLFRM);
		m_pTRECALLFRM->MoveComponent(point);

		for( INT i=0; i<TMONSKILL_COUNT; i++)
		{
			m_pTRECALLSKILLDOWN[i] = (TImageList *) m_pTRECALLFRM->FindKid(dwRecallpushID[i]);
			m_pTRECALLSKILL[i] = (TImageList *) m_pTRECALLFRM->FindKid(dwRecallSkillID[i]);

			m_pTRECALLSKILLGAUGE[i] = (TGauge *) m_pTRECALLFRM->FindKid(dwRecallgaugeID[i]);
			m_pTRECALLSKILLGAUGE[i]->SetStyle(m_pTRECALLSKILLGAUGE[i]->GetStyle()|TGS_GROW_UP);
			m_pTRECALLSKILLSM[i] = m_pTRECALLFRM->FindKid(dwRecallskillSMID[i]);
		}

		for( INT i=0; i<TRECALLAI_COUNT; i++)
		{
			m_pTRECALLAIDOWN[i] = (TImageList *) m_pTRECALLFRM->FindKid(dwRecallAIpushID[i]);
			m_pTRECALLAISM[i] = m_pTRECALLFRM->FindKid(dwRecallAISMID[i]);
			m_pTRECALLAI[i] = m_pTRECALLFRM->FindKid(dwRecallAI[i]);
		}
	}

	{
		DWORD dwHotpushID[] = {
			ID_CTRLINST_ICON_PUSH_1,
			ID_CTRLINST_ICON_PUSH_2,
			ID_CTRLINST_ICON_PUSH_3,
			ID_CTRLINST_ICON_PUSH_4,
			ID_CTRLINST_ICON_PUSH_5,
			ID_CTRLINST_ICON_PUSH_6,
			ID_CTRLINST_ICON_PUSH_7,
			ID_CTRLINST_ICON_PUSH_8,
			ID_CTRLINST_ICON_PUSH_9,
			ID_CTRLINST_ICON_PUSH_10,
			ID_CTRLINST_ICON_PUSH_11,
			ID_CTRLINST_ICON_PUSH_12};

		DWORD dwHotkeyID[MAX_HOTKEY_POS][2] = {
			{ ID_CTRLINST_SKILL_1, ID_CTRLINST_ITEM_1},
			{ ID_CTRLINST_SKILL_2, ID_CTRLINST_ITEM_2},
			{ ID_CTRLINST_SKILL_3, ID_CTRLINST_ITEM_3},
			{ ID_CTRLINST_SKILL_4, ID_CTRLINST_ITEM_4},
			{ ID_CTRLINST_SKILL_5, ID_CTRLINST_ITEM_5},
			{ ID_CTRLINST_SKILL_6, ID_CTRLINST_ITEM_6},
			{ ID_CTRLINST_SKILL_7, ID_CTRLINST_ITEM_7},
			{ ID_CTRLINST_SKILL_8, ID_CTRLINST_ITEM_8},
			{ ID_CTRLINST_SKILL_9, ID_CTRLINST_ITEM_9},
			{ ID_CTRLINST_SKILL_10, ID_CTRLINST_ITEM_10},
			{ ID_CTRLINST_SKILL_11, ID_CTRLINST_ITEM_11},
			{ ID_CTRLINST_SKILL_12, ID_CTRLINST_ITEM_12}};

		DWORD dwHotkeyPosID[THOTKEYBASE_COUNT] = {
			ID_CTRLINST_MAIN_SLOT_2,
			ID_CTRLINST_MAIN_SLOT_1};

		for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
		{

			LP_FRAMEDESC pDESC = pParser->FindFrameTemplate(ID_FRAME_SHORTCUT_NEW);

			TComponent *pPOS = NULL;
			CPoint point;
			pPOS = FindKid(dwHotkeyPosID[i]);
			RemoveKid(pPOS);
			delete pPOS;

			m_pTHOTKEYFRM[i] = new CTClientUIBase( this, pDESC);
			m_pTHOTKEYFRM[i]->m_id = dwHotkeyPosID[i];
			AddKid(m_pTHOTKEYFRM[i]);

			m_pTHOTKEY[i][0][0] = (TImageList *) m_pTHOTKEYFRM[i]->FindKid(ID_CTRLINST_SKILL);
			m_pTHOTKEY[i][0][1] = (TImageList *) m_pTHOTKEYFRM[i]->FindKid(ID_CTRLINST_ITEM);
			m_pTHOTKEYDOWN[i][0] = (TImageList *) m_pTHOTKEYFRM[i]->FindKid(dwHotpushID[0]);

			for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
			{

				for( BYTE k=0; k<2; k++)
					m_pTHOTKEY[i][j][k] = (TImageList *) m_pTHOTKEYFRM[i]->FindKid(dwHotkeyID[j][k]);

				m_pTHOTKEYDOWN[i][j] = (TImageList *) m_pTHOTKEYFRM[i]->FindKid(dwHotpushID[j]);
				m_pTHOTKEYDOWN[i][j]->SetCurImage(0);
				m_pTHOTKEYDOWN[i][j]->m_bVCenter = FALSE;

/*
				CD3DFont *pTFONT = m_pTHOTKEYDOWN[i][j]->Get3DFont();
	
				pTFONT->m_dwLineColor = TTEXTSHADOW_COLOR;
				pTFONT->m_dwColor = TNAMETEXT_COLOR;
				pTFONT->m_bOutLine = FALSE;
				pTFONT->m_bShadow = TRUE;
*/
				m_pTHOTKEYGAUGE[i][j] = (TGauge *) m_pTHOTKEYFRM[i]->FindKid(CTClientGame::m_vTICONGAUGE[j]);
				m_pTHOTKEYGAUGE[i][j]->SetStyle(m_pTHOTKEYGAUGE[i][j]->GetStyle()|TGS_GROW_UP);
				m_pTHOTKEYSM[i][j] = m_pTHOTKEYFRM[i]->FindKid(CTClientGame::m_vTICONSM[j]);
			}

			for( j=0; j<THOTKEYCTRL_COUNT; j++) 
			{
				m_pTHOTKEYCTRL[i][j] = m_pTHOTKEYFRM[i]->FindKid(ID_CTRLINST_MAIN_SLOT);
			
			}
			
		}
	}

	m_pCAUTION15 = NULL;
#ifdef ADD_CAUTION15
	m_pCAUTION15 = FindKid(ID_CTRLINST_CAUTION_15);
#endif

	if(m_pCAUTION15)
	{
		m_bAddedCaution15 = TRUE;

		if( !CTClientGame::m_vTOPTION.m_bShowCaution15 )
			DettachCaution15();
	}
	else
		m_bAddedCaution15 = FALSE;

	m_dwCaution15State = 0;
	m_dwCaution15Tick = 0;

	m_pSiegeAlarm = FindKid(ID_CTRLINST_SIEGE_ALARM);
	if(m_pSiegeAlarm)
		DettachSiegeAlarm();
	else
		m_bAddedSiegeAlarm = FALSE;

	m_pExitTutorial = (TButton*) FindKid( ID_CTRLINST_EXIT_TUTORIAL );
	if( m_pExitTutorial )
		DettachExitTutorial();
	else
		m_bAddedExitTutorial = FALSE;

	m_bNotifySiegeAlarm = FALSE;
	m_dwNotifySiegeAlarmTick = 0;

	m_bShowPath = FALSE;
	m_bAutoPath = FALSE;
	m_dwCurQuestID = 0;

	m_pTASSISTANT[0] = NULL;
	m_pTASSISTANT[1] = NULL;
	m_pTASSISTANT[2] = NULL;
}

CTGaugePannel::~CTGaugePannel()
{
}

ITDetailInfoPtr CTGaugePannel::GetTInfoKey( const CPoint& point )
{
	for( BYTE i=0; i<TPANNEL_COUNT; ++i)
		if( m_vTMAINTAIN[i]->HitTest(point) )
			return m_vTMAINTAIN[i]->GetTInfoKey(point);

	ITDetailInfoPtr pInfo;

	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
		{
			pInfo = GetTInfoKey_Hotkey( point, i, j);

			if(pInfo)
				return pInfo;
		}

	if(m_pMainRecall)
	{
		for( i=0; i<TRECALLAI_COUNT; i++)
		{
			pInfo = GetTInfoKey_RecallAi( point, i);

			if(pInfo)
				return pInfo;
		}

		for( i=0; i<TMONSKILL_COUNT; i++)
		{
			pInfo = GetTInfoKey_RecallSkill( point, i);

			if(pInfo)
				return pInfo;
		}
	}

	if( m_pSiegeAlarm &&
		m_bAddedSiegeAlarm &&
		m_pSiegeAlarm->HitTest(point) )
	{
		CTClientGame* pGame = CTClientGame::GetInstance();

		CRect rt;
		m_pSiegeAlarm->GetComponentRect(&rt);
		m_pSiegeAlarm->ComponentToScreen(&rt);

		pInfo = CTDetailInfoManager::NewDefTooltipInst(
			CTChart::LoadString(TSTR_SIEGE_ALARM_TITLE),
			CTChart::LoadString(TSTR_SIEGE_ALARM_MSG),
			rt);

		if( pInfo )
			pInfo->SetDir(FALSE, TRUE, TRUE);

		return pInfo;
	}
	
	if( m_pExitTutorial &&
		m_bAddedExitTutorial &&
		m_pExitTutorial->HitTest(point) )
	{
		CTClientGame* pGame = CTClientGame::GetInstance();

		CRect rt;
		m_pSiegeAlarm->GetComponentRect(&rt);
		m_pSiegeAlarm->ComponentToScreen(&rt);

		CString strFMT;
		switch(pGame->GetMainChar()->m_bContryID)
		{
		case TCONTRY_D:
			strFMT = CTChart::LoadString( TSTR_TUTORIAL_SKIP_MSG_D );
			break;
		case TCONTRY_C:
			strFMT = CTChart::LoadString( TSTR_TUTORIAL_SKIP_MSG_C );
			break;
		case TCONTRY_B:
		case TCONTRY_PEACE:
			strFMT = CTChart::LoadString( TSTR_TUTORIAL_SKIP_MSG_B );
			break;
		}

		pInfo = CTDetailInfoManager::NewDefTooltipInst(
			CTChart::LoadString(TSTR_TUTORIAL_SKIP_TITLE),
			strFMT,
			rt);

		if( pInfo )
			pInfo->SetDir(FALSE, TRUE, TRUE);

		return pInfo;
	}
#ifdef ADD_SKYGARDEN
	for( int i=0 ; i < 3 ; ++i )
	{
		TComponent* pComp = m_pTASSISTANT[ i ];

		if( pComp->HitTest(point) &&
			i < CTClientGame::GetInstance()->m_vTASSISTANT.size() )
		{
			LPTASSISTANT pTASSISTANT = CTClientGame::GetInstance()->m_vTASSISTANT[ i ];
			if( pTASSISTANT )
			{
				CRect rc;
				pComp->GetComponentRect(&rc);
				pComp->ComponentToScreen(&rc);

				pInfo = CTDetailInfoManager::NewPlayerInst(
					pTASSISTANT->m_strName,
					pTASSISTANT->m_bLevel,
					pTASSISTANT->m_bRace,
					pTASSISTANT->m_bSex,
					pTASSISTANT->m_bFace,
					pTASSISTANT->m_bHair,
					pTASSISTANT->m_dwCharID == pTASSISTANT->m_dwCommanderID,
					pTASSISTANT->m_bClass,
					rc);
			}
			return pInfo;		
		}
	}
#endif
	return pInfo;
}

BOOL CTGaugePannel::CanWithItemUI()
{
	return TRUE;
}

BYTE CTGaugePannel::OnBeginDrag( LPTDRAG pDRAG, CPoint point)
{
	if( m_pTRSCS->IsVisible() && m_pTRSCS->OnBeginDrag(pDRAG, point) )
		return TRUE;

	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
	{
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
		{
			if( !m_pTHOTKEY[i][j][0]->HitTest(point) )
				continue;
			TImageList *pTIMG = NULL;

			switch(m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType)
			{
			case HOTKEY_SKILL	: pTIMG = m_pTHOTKEY[i][j][0]; break;
			case HOTKEY_ITEM	: pTIMG = m_pTHOTKEY[i][j][1]; break;
			case HOTKEY_PET : pTIMG = m_pTHOTKEY[i][j][1]; break;
			}

			if(!pTIMG)
				continue;

			if(pDRAG)
			{
				CPoint pt = point;
				CSize size;

				pDRAG->m_pIMAGE = new TImageList(
					NULL,
					pTIMG->m_pDESC);

				pDRAG->m_pIMAGE->SetCurImage(pTIMG->GetCurImage());
				pDRAG->m_pIMAGE->m_strText = pTIMG->m_strText;

				switch(i)
				{
				case THOTKEYBASE_DEF	: pDRAG->m_bSlotID = CTMainUI::MakeSlotID(TMAINSLOTID_HOTKEY_DEF, j); break;
				case THOTKEYBASE_SUB1	: pDRAG->m_bSlotID = CTMainUI::MakeSlotID(TMAINSLOTID_HOTKEY_SUB1, j); break;
				}

				pDRAG->m_pIMAGE->GetComponentSize(&size);
				pt.x -= size.cx / 2;
				pt.y -= size.cy / 2;

				pDRAG->m_pIMAGE->ShowComponent(FALSE);
				//pDRAG->m_pIMAGE->MoveComponent(pt);
			}

			return TRUE;
		}
	}

	return FALSE;
}

TDROPINFO CTGaugePannel::OnDrop( CPoint point)
{
	TDROPINFO vResult;

	if( m_pTRSCS->IsVisible() )
	{
		vResult = m_pTRSCS->OnDrop(point);
		if(vResult.m_bDrop)
			return vResult;
	}

	if(m_bDropTarget)
	{
		for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
			for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
			{
				if(!m_pTHOTKEY[i][j][0]->HitTest(point))
					continue;

				switch(i)
				{
				case THOTKEYBASE_DEF	: vResult.m_bSlotID = CTMainUI::MakeSlotID(TMAINSLOTID_HOTKEY_DEF, j); break;
				case THOTKEYBASE_SUB1	: vResult.m_bSlotID = CTMainUI::MakeSlotID(TMAINSLOTID_HOTKEY_SUB1, j); break;
				}
				vResult.m_bDrop = TRUE;

				return vResult;
			}
	}

	return vResult;
}

void CTGaugePannel::DefaultPosition( CPoint* vBASIS, BOOL bRestore )
{
	static const INT TGAUGEPANNEL_COMP_COUNT = 7;
	static DWORD vCOMP[TGAUGEPANNEL_COMP_COUNT][2] =
	{
		{ ID_FRAME_MY_GAUGE, TBASISPOINT_LEFT_TOP },
		{ ID_FRAME_RECALL_GAUGE, TBASISPOINT_LEFT_TOP },
		{ ID_FRAME_TARGET_GAUGE, TBASISPOINT_CENTER_TOP },
		{ ID_FRAME_PARTY_GAUGE, TBASISPOINT_LEFT_MIDDLE },
		{ ID_FRAME_CHAT, TBASISPOINT_LEFT_TOP },
		{ ID_FRAME_NOTIFY, TBASISPOINT_RIGHT_BOTTOM },
		{ID_CTRLINST_MESSENGER , TBASISPOINT_RIGHT_BOTTOM },
	};
	static CPoint vCOMP_OFFSET[TGAUGEPANNEL_COMP_COUNT];
	static BYTE vCOMP_BASIS[TGAUGEPANNEL_COMP_COUNT];
    
	if( bRestore )
	{
		for( INT i=0 ; i < TGAUGEPANNEL_COMP_COUNT ; ++i )
		{
			CTClientUIBase* pCOMP = (CTClientUIBase*) FindKid( vCOMP[ i ][0] );
			if( pCOMP )
			{
				pCOMP->m_vCompOffset = vCOMP_OFFSET[i];
				pCOMP->m_bBasisPoint = vCOMP_BASIS[i];

				pCOMP->DefaultPosition( vBASIS, bRestore);
			}
		}
	}
	else
	{
		for( INT i=0 ; i < TGAUGEPANNEL_COMP_COUNT ; ++i )
		{
			CTClientUIBase* pCOMP = (CTClientUIBase*) FindKid( vCOMP[ i ][0] );
			if( pCOMP )
			{
				CPoint pt;
				pCOMP->GetComponentPos(&pt);
				pt -= vBASIS[ vCOMP[i][1] ];

				pCOMP->m_vCompOffset = pt;
				pCOMP->m_bBasisPoint = (BYTE) vCOMP[i][1];

				vCOMP_OFFSET[i] = pCOMP->m_vCompOffset;
				vCOMP_BASIS[i] = pCOMP->m_bBasisPoint;

				pCOMP->DefaultPosition( vBASIS, bRestore);
			}
		}
	}

	{
		static const INT TMAINUI_COMP_COUNT = 6;

		static DWORD vCOMP[TMAINUI_COMP_COUNT][2] =
		{
			{ ID_CTRLINST_MAIN_SLOT_1, TBASISPOINT_LEFT_BOTTOM },
			{ ID_CTRLINST_MAIN_SLOT_2, TBASISPOINT_RIGHT_BOTTOM },
			{ ID_CTRLINST_PET_SLOT, TBASISPOINT_RIGHT_BOTTOM },
			{ ID_FRAME_MINIMAP, TBASISPOINT_CENTER_BOTTOM },
			{ ID_FRAME_RSCS, TBASISPOINT_CENTER_BOTTOM },
			{ ID_FRAME_TOURNAMENT_MODE, TBASISPOINT_CENTER_BOTTOM },
		};

		static CPoint vCOMP_OFFSET[TMAINUI_COMP_COUNT];
		static BYTE vCOMP_BASIS[TMAINUI_COMP_COUNT];

		if( bRestore)
		{
			for( INT i=0 ; i < TMAINUI_COMP_COUNT ; ++i )
			{
				CTClientUIBase* pCOMP = (CTClientUIBase*) FindKid( vCOMP[ i ][0] );
				if( pCOMP )
				{
					pCOMP->m_vCompOffset = vCOMP_OFFSET[i];
					pCOMP->m_bBasisPoint = vCOMP_BASIS[i];
				}
			}
		}
		else
		{
			for( INT i=0 ; i < TMAINUI_COMP_COUNT ; ++i )
			{
				CTClientUIBase* pCOMP = (CTClientUIBase*) FindKid( vCOMP[ i ][0] );
				if( pCOMP )
				{
					CPoint pt;
					pCOMP->GetComponentPos(&pt);
					pt -= vBASIS[ vCOMP[i][1] ];

					pCOMP->m_vCompOffset = pt;
					pCOMP->m_bBasisPoint = (BYTE) vCOMP[i][1];

					vCOMP_OFFSET[i] = pCOMP->m_vCompOffset;
					vCOMP_BASIS[i] = pCOMP->m_bBasisPoint;
				}
			}
		}
	}

	{
		if( m_pCAUTION15 )
		{
			CPoint pt = vBASIS[TBASISPOINT_RIGHT_TOP];
			pt.x -= 428;
			pt.y += 4;
			m_pCAUTION15->MoveComponent(pt);
		}
	}

	{
		if( m_pSiegeAlarm )
		{

			CPoint pt = vBASIS[TBASISPOINT_RIGHT_TOP];
			pt.x -= 235;
			pt.y += 180;
			m_pSiegeAlarm->MoveComponent(pt);
		}
	}

	{
		if( m_pExitTutorial )
		{
			CPoint pt = vBASIS[TBASISPOINT_RIGHT_TOP];
			pt.x -= 235;
			pt.y += 180;
			m_pExitTutorial->MoveComponent(pt);
		}
	}
}

void CTGaugePannel::ResetPosition()
{
	CTClientUIBase::ResetPosition();

	DWORD vCOMP[][2] =
	{
		{ID_FRAME_NOTIFY, TBASISPOINT_CENTER_TOP},
		{ ID_FRAME_RSCS, TBASISPOINT_CENTER_BOTTOM},
		{ ID_FRAME_MINIMAP, TBASISPOINT_CENTER_BOTTOM},
		{ ID_CTRLINST_MAIN_SLOT_1, TBASISPOINT_CENTER_BOTTOM },
		{ ID_CTRLINST_MAIN_SLOT_2, TBASISPOINT_CENTER_BOTTOM },
		{ ID_FRAME_MY_GAUGE, TBASISPOINT_LEFT_TOP},
		{ ID_CTRLINST_HB_MY_HP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HB_OP_HP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HB_MY_MP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HB_OP_MP, TBASISPOINT_CENTER_MIDDLE },

		{ ID_CTRLINST_HG_MY_HP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HG_OP_HP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HG_MY_MP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HG_OP_MP, TBASISPOINT_CENTER_MIDDLE },

		{ ID_CTRLINST_HT_MY_HP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HT_OP_HP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HT_MY_MP, TBASISPOINT_CENTER_MIDDLE },
		{ ID_CTRLINST_HT_OP_MP, TBASISPOINT_CENTER_MIDDLE },

		{ ID_CTRLINST_QLIST, TBASISPOINT_RIGHT_MIDDLE }
	};

	INT nOffset[][2] = 
	{
		{5100, 100},
		{ -110, -215},
		{ -110, -215},
		{ 112, -150},
		{-355, -150,},
		{13, 53},
		{ -150, -96 },
		{ -116, -60 },
		{ 101, -97 },
		{ 86, -60 },

		{ -150, -96 },
		{ -116, -60 },
		{ 101, -97 },
		{ 86, -60 },

		{ -197, 64 },
		{ -97, 64 },
		{ 139, 64 },
		{ 37, 64 },
		{ -325, -161 }
	};

	for( INT i=0 ; i < 19 ; ++i )
	{
		TComponent* pCOMP = FindKid( vCOMP[ i ][0] );
		if( pCOMP )
		{
			CPoint vOffset = CTClientUIBase::m_vBasis[ vCOMP[ i ][1] ];
			vOffset.x += nOffset[i][0];
			vOffset.y += nOffset[i][1];

			pCOMP->MoveComponent( vOffset );
		}
	}

	DWORD vCOMP2[5] =
	{
		ID_FRAME_MY_GAUGE,
		ID_FRAME_RECALL_GAUGE,
		ID_FRAME_TARGET_GAUGE,
		ID_FRAME_PARTY_GAUGE,
		ID_FRAME_NOTIFY
	};

	for( INT i=0 ; i < 5 ; ++i )
	{
		CTClientUIBase* pCOMP = (CTClientUIBase*) FindKid( vCOMP2[ i ] );
		pCOMP->ResetPosition();

	}

	for( BYTE i=0; i<5; i++)
	{
		CTClientUIBase *pTFRAME = (CTClientUIBase*) FindKid( vGaugeFrameID[i][0] );

		if( !pTFRAME )
			continue;

		if(vGaugeFrameID[i][2])
		{
			pTFRAME->m_bCanDrag = TRUE;
			pTFRAME->m_rcDrag.SetRect(
				CPoint(0,0),
				CTClientUIBase::m_vBasis[TBASISPOINT_RIGHT_BOTTOM] );
		}
	}

	{
		DWORD vCOMP[5][2] =
		{
			{ ID_CTRLINST_LUCKY, TBASISPOINT_RIGHT_TOP },
			{ ID_CTRLINST_LUCKY2, TBASISPOINT_RIGHT_TOP },
			{ ID_CTRLINST_LUCKY3, TBASISPOINT_RIGHT_TOP },
			{ ID_CTRLINST_LUCKY4, TBASISPOINT_RIGHT_TOP },
			{ ID_CTRLINST_MESSENGER, TBASISPOINT_RIGHT_TOP },
		};

		INT nOffset[5][2] =
		{
			{ -393, 0 },
			{ -393, 17 }, // LUCKY2
			{ -393, 34 }, // LUCKY3
			{ -393, 51 }, // LUCKY4
			{ -393, 51 }, // LUCKY4
		};

		for( INT i=0 ; i < 5 ; ++i )
		{
			TComponent* pCOMP = FindKid( vCOMP[ i ][0] );
			if( pCOMP )
			{
				CPoint vOffset = CTClientUIBase::m_vBasis[ vCOMP[ i ][1] ];
				vOffset.x += nOffset[i][0];
				vOffset.y += nOffset[i][1];
				pCOMP->MoveComponent( vOffset );
			}
		}

		DWORD vCOMP2[6][2] =
		{
		{ ID_CTRLINST_MAIN_SLOT_1, TBASISPOINT_LEFT_MIDDLE },
			{ ID_CTRLINST_MAIN_SLOT_2, TBASISPOINT_RIGHT_MIDDLE},
			{ ID_CTRLINST_PET_SLOT, TBASISPOINT_RIGHT_BOTTOM },
			{ ID_FRAME_MINIMAP, TBASISPOINT_CENTER_BOTTOM },
			{ ID_FRAME_RSCS, TBASISPOINT_CENTER_BOTTOM },
			{ ID_FRAME_TOURNAMENT_MODE, TBASISPOINT_RIGHT_TOP },
		};

		for( INT i=0 ; i < 6 ; ++i )
		{
			CTClientUIBase* pCOMP = (CTClientUIBase*) FindKid( vCOMP2[ i ][0] );
			pCOMP->ResetPosition();
			pCOMP->m_bCanDrag = FALSE;
			pCOMP->m_rcDrag = CRect( CPoint(0,0), CTClientUIBase::m_vBasis[TBASISPOINT_RIGHT_BOTTOM] );
		}
	}

	{
		if( m_pCAUTION15 )
		{
			CPoint pt = CTClientUIBase::m_vBasis[ TBASISPOINT_RIGHT_TOP ];
			pt.x -= 428;
			pt.y += 4;
			m_pCAUTION15->MoveComponent(pt);
		}
	}

	{
		if( m_pSiegeAlarm )
		{
			CPoint pt = CTClientUIBase::m_vBasis[ TBASISPOINT_RIGHT_TOP ];
			pt.x -= 235;
			pt.y += 180;
			m_pSiegeAlarm->MoveComponent(pt);
		}
	}

	{
		if( m_pExitTutorial )
		{
			CPoint pt = CTClientUIBase::m_vBasis[ TBASISPOINT_RIGHT_TOP ];
			pt.x -= 235;
			pt.y += 180;
			m_pExitTutorial->MoveComponent(pt);
		}
	}
}

void CTGaugePannel::UpdateQuestINFO( CTClientQuest *pTQUEST)
{
	if( !pTQUEST || !pTQUEST->m_pTQUEST )
		return;

	if(pTQUEST->m_bCheckShowRight)
	{
		int nCount = m_pQList->GetItemCount();

		for( int i=0; i<nCount; i++)
		{
			DWORD dwQuestID = m_pQList->GetItemData( i, TQLIST_COL_OBJ_STATUS);

			if( dwQuestID == pTQUEST->m_pTQUEST->m_dwID )
				break;
		}
		int nIndex = i < m_pQList->GetItemCount() ? i : m_pQList->AddString("");

		m_pQList->SetImageIndex( nIndex, TQLIST_COL_SHOW_PATH, TRUE, pTQUEST->m_pTQUEST->m_dwID == m_dwCurQuestID && m_bShowPath ? TQLIST_BTN_STATUS_DOWN : TQLIST_BTN_STATUS_UP);
		m_pQList->SetImageIndex( nIndex, TQLIST_COL_GOTO_PATH, TRUE, pTQUEST->m_pTQUEST->m_dwID == m_dwCurQuestID && m_bAutoPath ? TQLIST_BTN_STATUS_DOWN : TQLIST_BTN_STATUS_UP);

		m_pQList->SetItemString( nIndex, TQLIST_COL_QNAME, pTQUEST->m_pTQUEST->m_strTITLE);
		m_pQList->SetItemString( nIndex, TQLIST_COL_OBJ_STATUS, "");
		m_pQList->SetUserColor( nIndex, TQLIST_COL_QNAME, 0xFFFED000);

		m_pQList->SetItemData( nIndex, TQLIST_COL_OBJ_STATUS, pTQUEST->m_pTQUEST->m_dwID);
		m_pQList->SetItemData( nIndex, TQLIST_COL_SHOW_PATH, pTQUEST->m_pTQUEST->m_dwID);
		m_pQList->SetItemData( nIndex, TQLIST_COL_GOTO_PATH, pTQUEST->m_pTQUEST->m_dwID);

		nCount = INT(pTQUEST->m_pTQUEST->m_vTTERM.size());
		nIndex++;

		for( i=0; i<nCount; i++)
		{
			CTClientTerm *pTERM = pTQUEST->FindTTerm(pTQUEST->m_pTQUEST->m_vTTERM[i]);
			CString strRESULT;
			strRESULT.Empty();

			if(pTERM)
			{
				BYTE bResult;
				bResult = pTQUEST->GetResult();

				if( pTERM->m_pTTERM->m_bType == QTT_TIMER &&
					bResult != TTERMRESULT_FAILED &&
					bResult != TTERMRESULT_TIMEOUT &&
					pTQUEST->m_bTimmer )
				{
					strRESULT = CTChart::Format( TSTR_FMT_TIMMER, (pTQUEST->m_dwTick % 3600000) / 60000, (pTQUEST->m_dwTick % 60000) / 1000);
				}
				else
				{
					if( pTERM->m_pTTERM->m_bType != QTT_TIMER )
						bResult = pTERM->GetResult();

					switch( bResult )
					{
					case TTERMRESULT_INCOMPLETE	: strRESULT = CTChart::Format( TSTR_QUEST_STATUS, pTERM->m_bCount, pTQUEST->m_pTQUEST->m_vTTERM[i]->m_bCount); break;
					case TTERMRESULT_TIMEOUT	: strRESULT = CTChart::LoadString( TSTR_QRESULT_TIMEOUT); break;
					case TTERMRESULT_FAILED		: strRESULT = CTChart::LoadString( TSTR_QRESULT_FAILED); break;
					case TTERMRESULT_COMPLETE	: strRESULT = CTChart::LoadString( TSTR_QRESULT_COMPLETE); break;
					}
				}
			}
			else
			{
				strRESULT = CTChart::Format( TSTR_QUEST_STATUS, 0, pTQUEST->m_pTQUEST->m_vTTERM[i]->m_bCount);
			}

			if( nIndex < m_pQList->GetItemCount() )
				m_pQList->SetItemString( nIndex, TQLIST_COL_OBJ_NAME, pTQUEST->m_pTQUEST->m_vTTERM[i]->m_strTermMSG);
			else
				nIndex = m_pQList->AddString(pTQUEST->m_pTQUEST->m_vTTERM[i]->m_strTermMSG);

			m_pQList->SetImageIndex( nIndex, TQLIST_COL_SHOW_PATH, TRUE, TQLIST_BTN_STATUS_HIDE);
			m_pQList->SetImageIndex( nIndex, TQLIST_COL_GOTO_PATH, TRUE, TQLIST_BTN_STATUS_HIDE);

			m_pQList->SetItemString( nIndex, TQLIST_COL_OBJ_STATUS, strRESULT);
			m_pQList->SetUserColor( nIndex, TQLIST_COL_OBJ_NAME, 0xFFD9C298);
			m_pQList->SetUserColor( nIndex, TQLIST_COL_OBJ_STATUS, 0xFFD9C298);

			m_pQList->SetItemData( nIndex, TQLIST_COL_OBJ_STATUS, pTQUEST->m_pTQUEST->m_dwID);
			m_pQList->SetItemData( nIndex, TQLIST_COL_SHOW_PATH, pTQUEST->m_pTQUEST->m_dwID);
			m_pQList->SetItemData( nIndex, TQLIST_COL_GOTO_PATH, pTQUEST->m_pTQUEST->m_dwID);
			nIndex++;
		}
	}
	else
	{
		int nCount = m_pQList->GetItemCount();

		for( int i=nCount - 1; i>=0; i--)
		{
			DWORD dwQuestID = m_pQList->GetItemData( i, 1);

			if( dwQuestID == pTQUEST->m_pTQUEST->m_dwID )
				m_pQList->DelItem(i);
		}

		if( m_dwCurQuestID == pTQUEST->m_pTQUEST->m_dwID )
		{
			m_bShowPath = FALSE;
			m_bAutoPath = FALSE;
			m_dwCurQuestID = 0;
		}
	}
}

void CTGaugePannel::UpdateAllQuestINFO( CTClientChar *pTCHAR)
{
	if(!pTCHAR)
		return;
	int nCount = m_pQList->GetItemCount();

	for( int i=nCount - 1; i>=0; i--)
	{
		CTClientQuest *pTQUEST = pTCHAR->FindTQuest(m_pQList->GetItemData( i, TQLIST_COL_OBJ_STATUS));

		if( !pTQUEST || !pTQUEST->m_bCheckShowRight )
			m_pQList->DelItem(i);
	}

	if(m_dwCurQuestID)
	{
		CTClientQuest *pTQUEST = pTCHAR->FindTQuest(m_dwCurQuestID);

		if( !pTQUEST || !pTQUEST->m_bCheckShowRight )
		{
			m_bShowPath = FALSE;
			m_bAutoPath = FALSE;
			m_dwCurQuestID = 0;
		}
	}

	MAPTQCLASS::iterator itTCLASS;
	for( itTCLASS = pTCHAR->m_mapTQCLASS.begin(); itTCLASS != pTCHAR->m_mapTQCLASS.end(); itTCLASS++)
	{
		CTClientQClass *pTCLASS = (*itTCLASS).second;

		if(pTCLASS)
		{
			MAPTQUEST::iterator itTQUEST;

			for( itTQUEST = pTCLASS->m_mapTQUEST.begin(); itTQUEST != pTCLASS->m_mapTQUEST.end(); itTQUEST++)
				UpdateQuestINFO((*itTQUEST).second);
		}
	}
}

void CTGaugePannel::UpdateQuestBUTTON()
{
	int nCount = m_pQList->GetItemCount();

	for( int i=0; i<nCount; i++)
	{
		MAP_LISTITEM *pTLIST = m_pQList->m_items[i];

		if(pTLIST)
		{
			MAP_LISTITEM::iterator finder = pTLIST->find(TQLIST_COL_SHOW_PATH);

			if( finder != pTLIST->end() )
			{
				TListItem *pItem = (*finder).second;

				if( pItem && pItem->m_nImageIndex )
				{
					pItem->m_nImageIndex = m_bShowPath && pItem->m_param == m_dwCurQuestID ? TQLIST_BTN_STATUS_DOWN : TQLIST_BTN_STATUS_UP;
					m_pQList->m_bNeedUpdateRender = TRUE;
				}
			}

			finder = pTLIST->find(TQLIST_COL_GOTO_PATH);
			if( finder != pTLIST->end() )
			{
				TListItem *pItem = (*finder).second;

				if( pItem && pItem->m_nImageIndex )
				{
					pItem->m_nImageIndex = m_bAutoPath && pItem->m_param == m_dwCurQuestID ? TQLIST_BTN_STATUS_DOWN : TQLIST_BTN_STATUS_UP;
					m_pQList->m_bNeedUpdateRender = TRUE;
				}
			}
		}
	}
}

CString CTGaugePannel::GetResultString( CTClientTerm *pTERM)
{
	CString strRESULT;
	strRESULT.Empty();

    return strRESULT;
}

void CTGaugePannel::SetQuestState( LPTQUEST pTQUEST)
{
}

void CTGaugePannel::CalcRecallTick( CTClientRecall *pTRECALL)
{
	if( pTRECALL && pTRECALL->m_pTEMP->m_dwOBJ )
	{
		for( BYTE i=0; i<TMONSKILL_COUNT; ++i)
		{
			CTClientSkill *pTSKILL = pTRECALL->FindTSkill(pTRECALL->m_pTEMP->m_wTSKILL[i]);

			if(pTSKILL)
			{
				if(pTSKILL->m_dwTick)
				{
					m_pTRECALLSKILLGAUGE[i]->m_strText = CTClientGame::ToTimeString(pTSKILL->m_dwTick);
					m_pTRECALLSKILLGAUGE[i]->SetGauge( pTSKILL->m_dwTick, pTSKILL->m_dwReuseTick);

					m_pTRECALLSKILLGAUGE[i]->ShowComponent(TRUE);
				}
				else
					m_pTRECALLSKILLGAUGE[i]->ShowComponent(FALSE);

				m_pTRECALLSKILLSM[i]->ShowComponent(pTSKILL == pTRECALL->m_pTCURSKILL ? TRUE : FALSE);
			}
			else
			{
				m_pTRECALLSKILLGAUGE[i]->ShowComponent(FALSE);
				m_pTRECALLSKILLSM[i]->ShowComponent(FALSE);
				
				if( m_pTRECALLSKILLDOWN[i]->IsVisible() )
					m_pTRECALLSKILLDOWN[i]->ShowComponent(FALSE);
				
				if( m_pTRECALLSKILL[i]->IsVisible() )
					m_pTRECALLSKILL[i]->ShowComponent(FALSE);
			}
		}

		for( i=0; i<TRECALLAI_COUNT; ++i)
			m_pTRECALLAISM[i]->ShowComponent(pTRECALL->m_bSubAI == i || pTRECALL->m_bAI == i ? TRUE : FALSE);
	}
	else
	{
		for( BYTE i=0; i<TMONSKILL_COUNT; ++i)
		{
			m_pTRECALLSKILLGAUGE[i]->ShowComponent(FALSE);
			m_pTRECALLSKILLSM[i]->ShowComponent(FALSE);
		}

		for( i=0; i<TRECALLAI_COUNT; ++i)
			m_pTRECALLAISM[i]->ShowComponent(FALSE);
	}
}


void CTGaugePannel::ResetRecallUI( CTClientRecall *pTRECALL)
{
	if( pTRECALL && pTRECALL->m_pTEMP->m_dwOBJ )
	{
		for( BYTE i=0; i<TMONSKILL_COUNT; ++i)
		{
			CTClientSkill *pTSKILL = pTRECALL->FindTSkill(pTRECALL->m_pTEMP->m_wTSKILL[i]);

			if(pTSKILL)
			{
				m_pTRECALLSKILLDOWN[i]->ShowComponent(TRUE);
				m_pTRECALLSKILL[i]->ShowComponent(TRUE);

				m_pTRECALLSKILL[i]->SetCurImage(pTSKILL->m_pTSKILL->m_wIconID);
				m_pTRECALLSKILLDOWN[i]->SetCurImage(0);
			}
			else
			{
				m_pTRECALLSKILLDOWN[i]->ShowComponent(FALSE);
				m_pTRECALLSKILL[i]->ShowComponent(FALSE);
			}
		}

		for( i=0; i<TRECALLAI_COUNT; ++i)
		{
			m_pTRECALLAIDOWN[i]->ShowComponent(TRUE);
			m_pTRECALLAI[i]->ShowComponent(TRUE);
		}

		BOOL bPrevShow = m_pTRECALLFRM->IsVisible();
		m_pTRECALLFRM->ShowComponent(TRUE);

		if( FALSE == bPrevShow )
		{
			
			CTMainUI* pMainUI = static_cast<CTMainUI*>( CTClientGame::GetInstance()->GetFrame( TFRAME_MAIN ) );
			pMainUI->AdjustOtherCompByTREECALLSLOT( TRUE );
			
		}
	}
	else
	{
		for( BYTE i=0; i<TMONSKILL_COUNT; ++i)
		{
			m_pTRECALLSKILLDOWN[i]->ShowComponent(FALSE);
			m_pTRECALLSKILL[i]->ShowComponent(FALSE);
		}

		for( i=0; i<TRECALLAI_COUNT; ++i)
		{
			m_pTRECALLAIDOWN[i]->ShowComponent(FALSE);
			m_pTRECALLAI[i]->ShowComponent(FALSE);
		}

		BOOL bPrevShow = m_pTRECALLFRM->IsVisible();
		m_pTRECALLFRM->ShowComponent(FALSE);

		if( TRUE == bPrevShow )
		{
			CTMainUI* pMainUI = static_cast<CTMainUI*>( CTClientGame::GetInstance()->GetFrame( TFRAME_MAIN ) );
			pMainUI->AdjustOtherCompByTREECALLSLOT( FALSE );
		}
	}

	m_pMainRecall = pTRECALL;
}


void CTGaugePannel::ResetHotkeyStr()
{
	static const WORD wSkillKey[THOTKEYBASE_COUNT] = 
	{
		TKEY_SKILL_1,
		TKEY_SKILL2_1,
	};

	CTKeySetting* pKeySet = CTKeySetting::GetInstance();

	for( WORD h=0; h<THOTKEYBASE_COUNT; ++h)
	{
		
		
		for( WORD i=0; i<MAX_HOTKEY_POS; ++i)
		{


			TKEY_SET eKEY = (TKEY_SET)(wSkillKey[h]+i);
			

			DWORD dwUseless[12] = {
			ID_USELESS_1,
			ID_USELESS_2,
			ID_USELESS_3,
			ID_USELESS_4,
			ID_USELESS_5,
			ID_USELESS_6,
			ID_USELESS_7,
			ID_USELESS_8,
			ID_USELESS_9,
			ID_USELESS_10,
			ID_USELESS_11,
			ID_USELESS_12};

		    DWORD dwHotkey[MAX_HOTKEY_POS] = {
            ID_HOTKEY_TEXT_1,
			ID_HOTKEY_TEXT_2,
			ID_HOTKEY_TEXT_3,
			ID_HOTKEY_TEXT_4,
			ID_HOTKEY_TEXT_5,
			ID_HOTKEY_TEXT_6,
			ID_HOTKEY_TEXT_7,
			ID_HOTKEY_TEXT_8,
			ID_HOTKEY_TEXT_9,
			ID_HOTKEY_TEXT_10,
			ID_HOTKEY_TEXT_11,
			ID_HOTKEY_TEXT_12
			};

			TComponent* m_pUseless[12];
			m_pUseless[i] = m_pTHOTKEYFRM[h]->FindKid(dwUseless[i]);
			m_pUseless[i]->ShowComponent(FALSE);
			TComponent *m_pTHOTKEYTXT[2][12];

			m_pTHOTKEYTXT[h][i] = m_pTHOTKEYFRM[h]->FindKid(dwHotkey[i]);
			m_pTHOTKEYTXT[h][i]->m_strText = pKeySet->VKeyToStr( 
				pKeySet->GetCurVKey(eKEY),
				pKeySet->GetCurModKey(eKEY));

		}
	}
}
void CTGaugePannel::CalcHotkeyTick()
{
	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
	{
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
		{
			m_pTHOTKEYGAUGE[i][j]->ShowComponent(FALSE);
			m_pTHOTKEYSM[i][j]->ShowComponent(FALSE);
			if(m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType != HOTKEY_NONE)
			{
				DWORD dwHotkey[MAX_HOTKEY_POS] = {
					ID_HOTKEY_TEXT_1,
					ID_HOTKEY_TEXT_2,
					ID_HOTKEY_TEXT_3,
					ID_HOTKEY_TEXT_4,
					ID_HOTKEY_TEXT_5,
					ID_HOTKEY_TEXT_6,
					ID_HOTKEY_TEXT_7,
					ID_HOTKEY_TEXT_8,
					ID_HOTKEY_TEXT_9,
					ID_HOTKEY_TEXT_10,
					ID_HOTKEY_TEXT_11,
					ID_HOTKEY_TEXT_12
					};

					TComponent* m_pUseless[12];
					m_pUseless[j] = m_pTHOTKEYFRM[i]->FindKid(dwHotkey[j]);
					m_pUseless[j]->ShowComponent(TRUE);
			}
			else
			{
				DWORD dwHotkey[MAX_HOTKEY_POS] = {
					ID_HOTKEY_TEXT_1,
					ID_HOTKEY_TEXT_2,
					ID_HOTKEY_TEXT_3,
					ID_HOTKEY_TEXT_4,
					ID_HOTKEY_TEXT_5,
					ID_HOTKEY_TEXT_6,
					ID_HOTKEY_TEXT_7,
					ID_HOTKEY_TEXT_8,
					ID_HOTKEY_TEXT_9,
					ID_HOTKEY_TEXT_10,
					ID_HOTKEY_TEXT_11,
					ID_HOTKEY_TEXT_12
					};

					TComponent* m_pUseless[12];
					m_pUseless[j] = m_pTHOTKEYFRM[i]->FindKid(dwHotkey[j]);
					m_pUseless[j]->ShowComponent(FALSE);
			}

			switch(m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType)
			{
			case HOTKEY_SKILL	:
				{
					CTClientSkill *pTSKILL = m_pHost->FindTSkill(m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID);

					if(pTSKILL)
					{
						if(pTSKILL->m_dwTick)
						{
							m_pTHOTKEYGAUGE[i][j]->m_strText = CTClientGame::ToTimeString(pTSKILL->m_dwTick);
							m_pTHOTKEYGAUGE[i][j]->SetGauge( pTSKILL->m_dwTick, pTSKILL->m_dwReuseTick);

							m_pTHOTKEYGAUGE[i][j]->ShowComponent(TRUE);
						}

						if(pTSKILL->m_bLoopON)
							m_pTHOTKEYSM[i][j]->ShowComponent(TRUE);
					}
				}

				break;

			case HOTKEY_ITEM	:
				{
					LPTITEM pTITEM = CTChart::FindTITEMTEMP(m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID);
					DWORD dwTick = pTITEM ? CTClientItem::GetTick(pTITEM->m_wDelayGroupID) : 0;

					if(dwTick)
					{
						m_pTHOTKEYGAUGE[i][j]->m_strText = CTClientGame::ToTimeString(dwTick);
						m_pTHOTKEYGAUGE[i][j]->SetGauge( dwTick, pTITEM->m_dwDelay);

						m_pTHOTKEYGAUGE[i][j]->ShowComponent(TRUE);
					}
				}

				break;
			}
		}
	}
}

void CTGaugePannel::ShowHotkeyBase( BYTE bShow)
{
	bShow = TRUE; //�ӽ� ������ؾ���

	if( m_bHotkeyBase != bShow )
	{
		for( BYTE i=0; i<1; i++)
				m_pTHOTKEYCTRL[i][1]->ShowComponent(bShow);
m_pTHOTKEYCTRL[i][2]->ShowComponent(FALSE);
		m_bHotkeyBase = bShow;
	}
}

BYTE CTGaugePannel::CheckHotkeyBase( CPoint point, THOTKEY_BASE* outType )
{
	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
	{
		CRect rect;
		m_pTHOTKEYCTRL[i][THOTKEYCTRL_BASE]->GetComponentRect(&rect);
		m_pTHOTKEYCTRL[i][THOTKEYCTRL_BASE]->ComponentToScreen(&rect);

		if( rect.PtInRect(point) )
		{
			if( outType )
				*outType = (THOTKEY_BASE) i;

			return TRUE;
		}
	}

	return FALSE;
}


void CTGaugePannel::ResetHotkeyUI()
{
	BOOL bCanUsePet = m_pHost->CountCanNotUsePetMaintain() > 0 ? FALSE : TRUE;

	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
	{
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
			switch(m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType)
			{
			case HOTKEY_NONE	:
				{
					m_pTHOTKEY[i][j][1]->m_strText.Empty();
					m_pTHOTKEY[i][j][0]->SetCurImage(0);
					m_pTHOTKEY[i][j][1]->SetCurImage(0);

					m_pTHOTKEYDOWN[i][j]->ShowComponent(FALSE);
				}

				break;
	 
			case HOTKEY_SKILL	:
				{
					CTClientSkill *pTSKILL = m_pHost->FindTSkill(m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID);

					if( !pTSKILL || !pTSKILL->m_pTSKILL )
					{
						m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType = HOTKEY_NONE;
						m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID = 0;

						m_pTHOTKEYDOWN[i][j]->ShowComponent(FALSE);
						m_pTHOTKEY[i][j][0]->SetCurImage(0);
					}
					else
					{
						BOOL bENABLE = IsEnableHotkeySkill(pTSKILL);
						
						m_pTHOTKEYDOWN[i][j]->ShowComponent(TRUE);
						m_pTHOTKEYDOWN[i][j]->SetCurImage(0);

						m_pTHOTKEY[i][j][0]->SetCurImage(pTSKILL->m_pTSKILL->m_wIconID);
						m_pTHOTKEY[i][j][0]->EnableComponent(bENABLE);

						if(!bENABLE)
							pTSKILL->m_bLoopON = FALSE;
					}

					m_pTHOTKEY[i][j][1]->m_strText.Empty();
					m_pTHOTKEY[i][j][1]->SetCurImage(0);
				}

				break;

			case HOTKEY_ITEM	:
				{
					LPTITEM pTITEM = CTChart::FindTITEMTEMP(m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID);
					WORD wCount = m_pHost->GetItemCount(m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID);

					if( !wCount || !pTITEM )
					{
						// 2009.11.27 �Ǽ���
						// �κ��丮������ ������ �̵��ÿ� 
						// hotkey�� ��ϵǾ��� �������� hotkey slot���� ������� �� ������
						// bType�� wID�� ��� ����������..
//						m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType = HOTKEY_NONE;
//						m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID = 0;

						m_pTHOTKEYDOWN[i][j]->ShowComponent(FALSE);
						m_pTHOTKEY[i][j][1]->m_strText.Empty();
						m_pTHOTKEY[i][j][1]->SetCurImage(0);
					}
					else
					{
						if( wCount > 1 )
							m_pTHOTKEY[i][j][1]->m_strText = CTChart::Format( TSTR_FMT_NUMBER, wCount);
						else
							m_pTHOTKEY[i][j][1]->m_strText.Empty();

						m_pTHOTKEYDOWN[i][j]->ShowComponent(TRUE);
						m_pTHOTKEYDOWN[i][j]->SetCurImage(0);

						LPTITEMVISUAL pTVISUAL = CTClientItem::GetDefaultVisual(pTITEM);
						WORD wImg = pTVISUAL? pTVISUAL->m_wIcon: 0;

						m_pTHOTKEY[i][j][1]->SetCurImage(wImg);
					}

					m_pTHOTKEY[i][j][0]->SetCurImage(0);
				}

				break;

			case HOTKEY_PET	:
				{
					WORD wPetID = m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID;

					if( !wPetID )
					{
						m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType = HOTKEY_NONE;
						m_vTHOTKEY[m_bHotkeyID[i]][j].m_wID = 0;

						m_pTHOTKEYDOWN[i][j]->ShowComponent(FALSE);
						m_pTHOTKEY[i][j][1]->m_strText.Empty();
						m_pTHOTKEY[i][j][1]->SetCurImage(0);
					}
					else
					{
						wPetID = MAKEWORD( m_pHost->GetRaceID(), wPetID );

						LPTPET pTPET = CTChart::FindTPETTEMP( wPetID );
						if( pTPET )
						{
							m_pTHOTKEYDOWN[i][j]->ShowComponent(TRUE);
							m_pTHOTKEYDOWN[i][j]->SetCurImage(0);

							m_pTHOTKEY[i][j][1]->SetCurImage( pTPET->m_wIcon);
							m_pTHOTKEY[i][j][1]->EnableComponent(bCanUsePet);
							m_pTHOTKEY[i][j][1]->m_strText.Empty();
							m_pTHOTKEY[i][j][0]->SetCurImage(0);
						}
					}					
				}
				break;
			}
			m_pTHOTKEYCTRL[i][THOTKEYCTRL_NUM]->m_strText.Empty();
			}
			
			CTMainUI* pMainUI = static_cast<CTMainUI*>( CTClientGame::GetInstance()->GetFrame( TFRAME_MAIN ) );
            pMainUI->m_pCurCount->m_strText =  CTChart::Format( TSTR_FMT_NUMBER, m_bHotkeyID[0]+1);
		
	
}

void CTGaugePannel::ReleaseHotkey()
{
	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
	{
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
		{


			m_pTHOTKEYDOWN[i][j]->ShowComponent(FALSE);
		}

		m_bHotkeyID[i] = i;
	}

	for( i=0; i<MAX_HOTKEY_INVEN; i++)
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
		{
			m_vTHOTKEY[i][j].m_bType = HOTKEY_NONE;
			m_vTHOTKEY[i][j].m_wID = 0;
		}
}

ITDetailInfoPtr CTGaugePannel::GetTInfoKey_Hotkey(const CPoint& point, INT nHotkeyID, INT nSlotID)
{
	BYTE bHotkeySlot = m_bHotkeyID[nHotkeyID];
	ITDetailInfoPtr pInfo;

	switch(m_vTHOTKEY[bHotkeySlot][nSlotID].m_bType)
	{
	case HOTKEY_SKILL	:
		if(m_pTHOTKEY[nHotkeyID][nSlotID][0]->HitTest(point))
		{
			LPTSKILL pTSKILL = CTChart::FindTSKILLTEMP(m_vTHOTKEY[bHotkeySlot][nSlotID].m_wID);

			if( pTSKILL )
			{
				CRect rc;
				m_pTHOTKEY[nHotkeyID][nSlotID][0]->GetComponentRect(&rc);
				m_pTHOTKEY[nHotkeyID][nSlotID][0]->ComponentToScreen(&rc);

				CTClientSkill *pTSkill = m_pHost->FindTSkill(m_vTHOTKEY[bHotkeySlot][nSlotID].m_wID);
				pInfo = CTDetailInfoManager::NewSkillInst(
					pTSKILL, 
					pTSkill ? pTSkill->m_bLevel : 0,
					FALSE,
					rc);

				pInfo->SetDir(FALSE, TRUE, TRUE);
			}
		}
		break;

	case HOTKEY_ITEM	:
		if(m_pTHOTKEY[nHotkeyID][nSlotID][1]->HitTest(point))
		{
			LPTITEM pTITEM = CTChart::FindTITEMTEMP(m_vTHOTKEY[bHotkeySlot][nSlotID].m_wID);

			if( pTITEM )
			{
				CRect rc;
				m_pTHOTKEY[nHotkeyID][nSlotID][0]->GetComponentRect(&rc);
				m_pTHOTKEY[nHotkeyID][nSlotID][0]->ComponentToScreen(&rc);

				pInfo = CTDetailInfoManager::NewItemInst(pTITEM, rc);
				pInfo->SetDir(FALSE, TRUE, TRUE);
			}
		}
		break;

	case HOTKEY_PET:
		{
			// ����
		}
		break;
	}

	return pInfo;
}


ITDetailInfoPtr CTGaugePannel::GetTInfoKey_RecallSkill(const CPoint& point, INT nID)
{
	ITDetailInfoPtr pInfo;
	if( m_pTRECALLSKILL[nID]->HitTest(point) )
	{
		CTClientSkill* pSkill = m_pMainRecall->FindTSkill( m_pMainRecall->m_pTEMP->m_wTSKILL[nID] );

		if( pSkill )
		{
			CRect rc;
			m_pTRECALLSKILL[nID]->GetComponentRect(&rc);
			m_pTRECALLSKILL[nID]->ComponentToScreen(&rc);

			pInfo = CTDetailInfoManager::NewSkillInst(
				pSkill->m_pTSKILL, 
				pSkill ? pSkill->m_bLevel : 0,
				FALSE,
				rc);

			pInfo->SetDir(FALSE, TRUE, TRUE);
		}
	}

	return pInfo;
}

ITDetailInfoPtr CTGaugePannel::GetTInfoKey_RecallAi(const CPoint& point, INT nID)
{
	const DWORD RECALLINFOIDS[TRECALLAI_COUNT] = {
		60005,		// TRECALLAI_MANUAL
		60003,		// TRECALLAI_ACTIVE
		60004,		// TRECALLAI_PASSIVE
		60001,		// TRECALLAI_BACK
		60002};		// TRECALLAI_STAY
	ITDetailInfoPtr pInfo;

	if(m_pTRECALLAI[nID]->HitTest(point))
	{
		CRect rc;
		m_pTRECALLAIDOWN[nID]->GetComponentRect(&rc);
		m_pTRECALLAIDOWN[nID]->ComponentToScreen(&rc);

		pInfo = CTDetailInfoManager::NewNorInst("", RECALLINFOIDS[nID], 0, &rc);
		pInfo->SetDir(FALSE, FALSE, TRUE);
	}

	return pInfo;
}

BOOL CTGaugePannel::HitTest( CPoint pt)
{
	if(CTClientUIBase::HitTest(pt))
		return TRUE;

	if(m_pQList)
	{
		int nColumn = 0;
		TListItem *pItem = m_pQList->GetHitItem( pt, &nColumn);

		if( pItem && pItem->m_nImageIndex && (
			nColumn == TQLIST_COL_SHOW_PATH ||
			nColumn == TQLIST_COL_GOTO_PATH) )
			return TRUE;
	}

	return FALSE;
}

void CTGaugePannel::PushIcon( CPoint point)
{
	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
		{
			if( !m_pTHOTKEY[i][j][0]->HitTest(point) )
				continue;

			switch(m_vTHOTKEY[m_bHotkeyID[i]][j].m_bType)
			{
			case HOTKEY_SKILL	:
				m_pTHOTKEYDOWN[i][j]->SetCurImage(1);
				return;

			case HOTKEY_ITEM	:
				m_pTHOTKEYDOWN[i][j]->SetCurImage(1);
				return;

			case HOTKEY_PET:
				m_pTHOTKEYDOWN[i][j]->SetCurImage(1);
				return ;
			}
		}

	for( i=0; i<TMONSKILL_COUNT; i++)
		if(m_pTRECALLSKILL[i]->HitTest(point))
		{
			m_pTRECALLSKILLDOWN[i]->SetCurImage(1);
			return;
		}

	for( i=0; i<TRECALLAI_COUNT; i++)
		if(m_pTRECALLAI[i]->HitTest(point))
		{
			m_pTRECALLAIDOWN[i]->SetCurImage(1);
			return;
		}

	if( m_pQList && m_pHost && !m_pHost->IsDead() && !m_pHost->m_bGhost )
	{
		int nColumn = 0;
		TListItem *pItem = m_pQList->GetHitItem( point, &nColumn);

		if( pItem && pItem->m_nImageIndex && (
			nColumn == TQLIST_COL_SHOW_PATH ||
			nColumn == TQLIST_COL_GOTO_PATH) )
		{
			switch(pItem->m_nImageIndex)
			{
			case TQLIST_BTN_STATUS_DOWN	:
				{
					if( nColumn == TQLIST_COL_GOTO_PATH )
						m_bAutoPath = FALSE;
					else
						m_bShowPath = FALSE;

					if( !m_bShowPath && !m_bAutoPath )
						m_dwCurQuestID = 0;
				}

				break;

			case TQLIST_BTN_STATUS_UP	:
				{
					if( nColumn == TQLIST_COL_GOTO_PATH )
						m_bAutoPath = TRUE;
					else
						m_bShowPath = TRUE;

					m_dwCurQuestID = pItem->m_param;
				}

				break;
			}

			UpdateQuestBUTTON();
		}
	}
}

void CTGaugePannel::ReleaseIcon()
{
	for( BYTE i=0; i<THOTKEYBASE_COUNT; i++)
		for( BYTE j=0; j<MAX_HOTKEY_POS; j++)
			m_pTHOTKEYDOWN[i][j]->SetCurImage(0);

	for( i=0; i<TMONSKILL_COUNT; i++)
		m_pTRECALLSKILLDOWN[i]->SetCurImage(0);

	for( i=0; i<TRECALLAI_COUNT; i++)
		m_pTRECALLAIDOWN[i]->SetCurImage(0);
}

void CTGaugePannel::HotkeyNext(THOTKEY_BASE eHOTKEY)
{
	if( m_bHotkeyID[0] == 9 )
		m_bHotkeyID[0] = 0;
	if( m_bHotkeyID[1] == 10)
	    m_bHotkeyID[1] = 1;
	else
	{
		m_bHotkeyID[0]++;
	

		++m_bHotkeyID[1];

	}
	ResetHotkeyUI();
}

void CTGaugePannel::HotkeyPrev(THOTKEY_BASE eHOTKEY)
{
	if( m_bHotkeyID[0] == 0 )
		m_bHotkeyID[0] = MAX_HOTKEY_INVEN - 2;
	if( m_bHotkeyID[1] == 1 )
		m_bHotkeyID[1] = MAX_HOTKEY_INVEN - 1;

	else
	{
		m_bHotkeyID[0]--;
		--m_bHotkeyID[1];
	}
	ResetHotkeyUI();
}

void CTGaugePannel::OnLButtonDown( UINT nFlags, CPoint pt)
{
	PushIcon(pt);
	CTClientUIBase::OnLButtonDown( nFlags, pt);
}

void CTGaugePannel::OnLButtonUp( UINT nFlags, CPoint pt)
{
	ReleaseIcon();
	CTClientUIBase::OnLButtonUp( nFlags, pt);
}

void CTGaugePannel::OnMouseMove( UINT nFlags, CPoint pt)
{
	INT nX = m_ptPrev.x > pt.x ? m_ptPrev.x-pt.x : pt.x-m_ptPrev.x;
	INT nY = m_ptPrev.y > pt.y ? m_ptPrev.y-pt.y : pt.y-m_ptPrev.y;

	if( nX >= 6 || nY >= 6 )
		ReleaseIcon();

	m_ptPrev = pt;

	CTClientUIBase::OnMouseMove( nFlags, pt);
}

BOOL CTGaugePannel::IsEnableHotkeySkill( CTClientSkill * pTSKILL )
{
	BOOL bENABLE;

	CTClientGame* pGame = CTClientGame::GetInstance();
	CTClientObjBase* pTargetObj = pGame->GetTargetObj();
	
	if( pTSKILL->m_pTSKILL->m_bRangeType == TSKILLRANGE_NONE )
	{
		CTClientObjBase* pTARGET = pGame->GetSkillTarget(
			pTargetObj,
			pTSKILL->m_pTSKILL);

		BYTE bRESULT = pGame->CanUseSkill(
			pGame->GetMainChar(),
			pTARGET, 
			NULL,
			pTSKILL->m_pTSKILL);

		bENABLE = IsEnableHotkeySkill(bRESULT);
	}
	else
		bENABLE = m_pHost->CheckSkill(pTSKILL->m_pTSKILL);

	return bENABLE;
}

BOOL CTGaugePannel::IsEnableHotkeySkill(BYTE bRESULT)
{
	switch(bRESULT)
	{
	case SKILL_NEEDMP			:
	case SKILL_NEEDHP			:
	case SKILL_UNSUITWEAPON		:
	case SKILL_NEEDPREVACT		:
	case SKILL_MATCHCLASS		:
	case SKILL_WRONGTARGET		:
	case SKILL_WRONGREGION		:
	case SKILL_TRANS			:
	case SKILL_DEAD				:
	case SKILL_SILENCE			:
	case SKILL_MODE				:
	case SKILL_PEACEZONE		:
	case SKILL_NOTARGET			:
	case SKILL_NEEDITEM			: return FALSE;
	}

	return TRUE;
}

LPTHOTKEY CTGaugePannel::GetHotKey(THOTKEY_BASE eTYPE, BYTE bHotkeyID)
{
	if( bHotkeyID < MAX_HOTKEY_POS )
		return &m_vTHOTKEY[m_bHotkeyID[eTYPE]][bHotkeyID];

	return NULL;
}

void CTGaugePannel::CalcCaution15Tick(DWORD dwTick)
{
}

void CTGaugePannel::AttachCaution15()
{
	if( !m_bAddedCaution15 && m_pCAUTION15 )
	{
		m_pCAUTION15->ShowComponent(TRUE);
		m_bAddedCaution15 = TRUE;
	}
}

void CTGaugePannel::DettachCaution15()
{
	if( m_bAddedCaution15 && m_pCAUTION15 )
	{
		m_pCAUTION15->ShowComponent(FALSE);
		m_bAddedCaution15 = FALSE;
	}
}

void CTGaugePannel::AttachSiegeAlarm()
{
	if( !m_bAddedSiegeAlarm )
	{
		m_pSiegeAlarm->ShowComponent(TRUE);
		m_bAddedSiegeAlarm = TRUE;
	}
}

void CTGaugePannel::DettachSiegeAlarm()
{
	if( m_bAddedSiegeAlarm )
	{
		m_pSiegeAlarm->ShowComponent(FALSE);
		m_bAddedSiegeAlarm = FALSE;
	}

	CTDetailInfoManager::m_dwInfoStaticTick = 0;
}

void CTGaugePannel::AttachExitTutorial()
{
	if( !m_bAddedExitTutorial )
	{
		m_pExitTutorial->ShowComponent(TRUE);
		m_bAddedExitTutorial = TRUE;
	}
}

void CTGaugePannel::DettachExitTutorial()
{
	if( m_bAddedExitTutorial )
	{
		m_pExitTutorial->ShowComponent(FALSE);
		m_bAddedExitTutorial = FALSE;
	}

	CTDetailInfoManager::m_dwInfoStaticTick = 0;
}

HRESULT CTGaugePannel::Render( DWORD dwTickCount )
{
	if(!IsVisible())
		return S_OK;

	return CTClientUIBase::Render(dwTickCount);
}

void CTGaugePannel::SetNotifySiegeAlarm(BOOL bNotify)
{
	CRect rt;
	m_pSiegeAlarm->GetComponentRect(&rt);
	m_pSiegeAlarm->ComponentToScreen(&rt);
	
	CTClientGame* pGame = CTClientGame::GetInstance();
	CTDetailInfoDlg* pDetInfoDlg = static_cast<CTDetailInfoDlg*>( pGame->GetFrame(TFRAME_DETAIL_INFO) );
	CTDetailInfoManager::m_dwInfoStaticTick = 6000;

	// �˾�â ����
	ITDetailInfoPtr info = CTDetailInfoManager::NewDefTooltipInst(
		CTChart::LoadString(TSTR_SIEGE_ALARM_TITLE),
		CTChart::LoadString(TSTR_SIEGE_ALARM_MSG),
		rt);

	info->SetDir(FALSE, TRUE, TRUE);

	CTDetailInfoManager::m_pLastInfo = info;
	pGame->DisableUI(TFRAME_DETAIL_INFO);

	pDetInfoDlg->ResetINFO(CTDetailInfoManager::m_pLastInfo);

	CRect rc;
	pDetInfoDlg->GetComponentRect(&rc);

	CPoint pt = CTDetailInfoManager::m_pLastInfo->GetUIPosition(rc, CPoint(0,0));
	pDetInfoDlg->MoveComponent(pt);

	pGame->EnableUI(TFRAME_DETAIL_INFO);
}

void CTGaugePannel::ShowComponent(BOOL bVisible)
{
	CTClientUIBase::ShowComponent(bVisible);

	if(m_pCAUTION15)
		m_pCAUTION15->ShowComponent(bVisible && m_bAddedCaution15 ? TRUE : FALSE);

	if(m_pSiegeAlarm)
		m_pSiegeAlarm->ShowComponent(bVisible && m_bAddedSiegeAlarm ? TRUE : FALSE);

	if(m_pExitTutorial)
		m_pExitTutorial->ShowComponent(bVisible && m_bAddedExitTutorial ? TRUE : FALSE);
}
