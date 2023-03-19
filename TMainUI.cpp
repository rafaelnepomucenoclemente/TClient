#include "StdAfx.h"
#include "TClientGame.h"
#include "Resource.h"
#include "TPetManageDlg.h"

LPTEXTURESET CTMainUI::m_pNOTIFYMAIL = NULL;


CTMainUI::CTMainUI( TComponent *pParent, LP_FRAMEDESC pDesc, TCMLParser *pParser, CTClientChar *pHost )
:CTClientUIBase( pParent, pDesc)
{
	DWORD dwMainButtonID[] = {
		ID_CTRLINST_CHAR,
		ID_CTRLINST_SKILL,
		ID_CTRLINST_COMMUNITY,
		ID_CTRLINST_SYSTEM,
		ID_CTRLINST_INVEN_SLOT,
		ID_CTRLINST_PET,
		ID_CTRLINST_FAMERANK,
		ID_CTRLINST_HELP };

	DWORD dwMsgButtonID[] = {
		ID_CTRLINST_MESSENGER,
		ID_CTRLINST_MAIL,
		ID_CTRLINST_CHAT_LOCK};

	DWORD dwCashMenuID[] = {
			ID_CTRLINST_CASH_CHARGE};
			time_t now = time(0);



   tm *ltm = localtime(&now);
	CTClientGame* pMainGame = CTClientGame::GetInstance();
	CPoint kokot;

	m_pCENTER = new CTClientUIBase( this, pParser->FindFrameTemplate(ID_FRAME_MAIN_CENTER));
	//m_pTOPC = new CTClientUIBase( this, pParser->FindFrameTemplate(ID_CTRLINST_HONORBAR));
	m_pLOT = (TButton*) m_pCENTER->FindKid(ID_CTRLINST_LOTNEW);
	m_pLOT->ShowComponent(FALSE);

	m_pCashShopButton = (TGauge*) m_pCENTER->FindKid( ID_CTRLINST_CASHSHOP );
	m_pCashShopButton->SetStyle(TGS_GROW_LEFT);

	m_pRIGHT = new CTClientUIBase( this, pParser->FindFrameTemplate(ID_FRAME_MAIN_RIGHT));
	m_pCabinetButton = (TButton*) m_pRIGHT->FindKid( ID_CTRLINST_INVEN_SLOT );
	m_pTPARTYITEM = m_pRIGHT->FindKid( ID_CTRLINST_PARTY_ITEM);
	m_pLucky = m_pCENTER->FindKid(ID_CTRLINST_CASH_ITEM);

	//m_pJest = FindKid(ID_CTRLINST_HONORBAR);
	//m_pLucky->m_strText
	m_bUseBasis = FALSE;
    m_Honor = new CTClientUIBase( this, pParser->FindFrameTemplate(ID_CTRLINST_HONORBAR));
	CTDurationFrame *pDuration = new CTDurationFrame( this, pParser->FindFrameTemplate(ID_FRAME_DURATION));

	GAMEOPTION& GameOption = CTClientGame::GetInstance()->GetDevice()->m_option;

	TComponent *pPOS = NULL;
	CPoint point;
	pPOS = m_pCENTER->FindKid( ID_CTRLINST_DURATION);
	pPOS->GetComponentPos(&point);
	m_pCENTER->RemoveKid(pPOS);
	delete pPOS;
	m_pCENTER->AddKid(pDuration);

	pDuration->MoveComponent(point);
	pDuration->ShowComponent(TRUE);
	pDuration->EnableFloat(FALSE);

   
	for( INT i=0; i<TMAINBUTTON_COUNT; ++i)
		m_pTMAINBTN[i] = m_pRIGHT->FindKid(dwMainButtonID[i]);

	m_Region =  (TComponent*)FindKid(ID_CTRLINST_REGTEXT);
	m_Channel =  (TComponent*)FindKid(ID_CTRLINST_CHANTEXT);
	m_Clock = (TComponent*) FindKid(ID_CTRLINST_CLOCK);
	m_ClockTex = (TComponent*) FindKid(ID_CTRLINST_CLOCKTEX);
	m_pMedals = (TComponent*) FindKid(ID_CTRLINST_MEDALS);
	m_pLuckyNew = (TComponent*) FindKid(ID_CTRLINST_LUCKYNEW);
	m_pLuckyText = (TComponent*) FindKid(ID_CTRLINST_LUCKYTEXT);
	m_pChar = static_cast<TButton*>(m_pRIGHT->FindKid(ID_CTRLINST_CHAR));

	m_pLuckyText->m_strText = "0";
	m_pMedals->m_strText = "0";
	CString time;
	time.Format("%d:%d",ltm->tm_hour,ltm->tm_min);

	AddKid(m_Channel);
	AddKid(m_Region);
	RemoveKid(m_Channel);
	RemoveKid(m_Region);
	m_pSettings = static_cast<TButton*>(m_pRIGHT->FindKid(ID_CTRLINST_SYSTEM));

	for( INT i=0; i<TMSGBUTTON_COUNT; ++i)
		m_pTMSGBTN[i] = m_pRIGHT->FindKid(dwMsgButtonID[i]);

	for( INT i=0; i<TCASHMENU_COUNT; ++i)
	{
		m_pTTCASHMENU[i] = m_pCENTER->FindKid(dwCashMenuID[i]);

		m_pCENTER->RemoveKid(m_pTTCASHMENU[i]);
		m_pCENTER->AddKid(m_pTTCASHMENU[i]);
	}

	m_pTCHAPTERMSG = FindKid(ID_CTRLINST_CHAPTER_MSG);
	m_pTREGIONMSG = FindKid(ID_CTRLINST_REGION_MSG);
	m_pTQUESTMSG = FindKid(ID_CTRLINST_QUEST_MSG);

	m_Povest = static_cast< TComponent* >( FindKid( ID_CTRLINST_POVEST ) );
	m_H1 = static_cast< TComponent* >( FindKid( ID_CTRLINST_HONORBAR ) );
m_H2 = static_cast< TComponent* >( FindKid( ID_CTRLINST_HONORBAR2 ) );
m_Map = static_cast< TComponent* >( FindKid( ID_CTRLINST_REGION2 ) ); 
m_Chan = static_cast< TComponent* >( FindKid( ID_CTRLINST_CHAN ) );
m_pCurCount = static_cast< TComponent* >( FindKid( ID_CTRLINST_HKC ) );
m_pSCROLLUP = static_cast< TButton* >( FindKid( ID_CTRLINST_SCRUP ) );
m_pSCROLLDOWN = static_cast< TButton* >( FindKid( ID_CTRLINST_SCRDOWN ) );
m_pPartyIT = static_cast <TComponent*>(FindKid(ID_PARTY_IT2));
m_pLucky->ShowComponent(FALSE);//old
 m_pPartyIT->SetTextAlign(ALIGN_CENTER);
	AddKid(m_Povest);
	m_BU = FindKid(ID_CTRLINST_BU);
	AddKid(m_BU);
	RemoveKid(m_Povest);
	RemoveKid(m_BU);
	m_pTCHAPTERMSG->m_bUseImageClrForText = TRUE;
	m_pTREGIONMSG->m_bUseImageClrForText = TRUE;
	m_pTQUESTMSG->m_bUseImageClrForText = TRUE;
	RemoveKid(m_pTCHAPTERMSG);
	RemoveKid(m_pTREGIONMSG);
	RemoveKid(m_pTQUESTMSG);

	AddKid(m_pTCHAPTERMSG);
	AddKid(m_pTREGIONMSG);
	AddKid(m_pTQUESTMSG);

	m_pTCHAPTERMSG->m_bNoHIT = TRUE;
	m_pTREGIONMSG->m_bNoHIT = TRUE;
	m_pTQUESTMSG->m_bNoHIT = TRUE;

	CD3DFont *pTFONT = m_pTCHAPTERMSG->Get3DFont();
	pTFONT->m_dwColor = TTITLEMSG_COLOR;
	pTFONT->m_dwLineColor = TTEXTSHADOW_COLOR;
	pTFONT->m_bOutLine = TRUE;

	pTFONT = m_pTREGIONMSG->Get3DFont();
	pTFONT->m_dwColor = TTITLEMSG_COLOR;
	pTFONT->m_dwLineColor = TTEXTSHADOW_COLOR;
	pTFONT->m_bOutLine = TRUE;

	pTFONT = m_pTQUESTMSG->Get3DFont();

	pTFONT->m_dwColor = TTITLEMSG_COLOR;
	pTFONT->m_dwLineColor = TTEXTSHADOW_COLOR;
	pTFONT->m_bOutLine = TRUE;

	m_pMESSENGER = (TButton *) m_pRIGHT->FindKid( ID_CTRLINST_MESSENGER);
	m_pMAIL = (TButton *) m_pRIGHT->FindKid( ID_CTRLINST_MAIL );

	m_bNotifyNewMail = FALSE;
	m_bNotifyNewMsg = FALSE;
	m_bNotifyNewCashCabinet = FALSE;

	m_bCashMenu = FALSE;

	m_pTCHAPTERMSG->ShowComponent(FALSE);
	m_pTREGIONMSG->ShowComponent(FALSE);
	m_pTQUESTMSG->ShowComponent(FALSE);

	m_bSND = FALSE;
	m_ptPrev = CPoint(0,0);

	m_dwNotifyMailTick = 0;
	m_vNotifyMailStart = m_vNotifyMailEnd = D3DXVECTOR2( -1000.0f, -1000.0f );

	// 채팅방 생성
	{
		CPoint point;
		LP_FRAMEDESC pGAUGE = pParser->FindFrameTemplate( ID_FRAME_CHAT );
		TComponent *pTPOS = FindKid( ID_CTRLINST_POS_CHAT );
		CTChatFrame* pTFRAME = new CTChatFrame( this, pGAUGE, pMainGame, pParser);
		pTPOS->GetComponentPos(&point);
		RemoveKid(pTPOS);
		delete pTPOS;
		AddKid(pTFRAME);
		pTFRAME->MoveComponent(point);
		pMainGame->m_pChatFrame = pTFRAME;
	}

	AddKid( m_pRIGHT );
	AddKid( m_pCENTER );
	AddKid( m_Honor);
AddKid( m_Povest);
	AddKid( m_BU);
		RemoveKid(m_Povest);
	RemoveKid(m_BU);
AddKid(m_Channel);
AddKid(m_Region);
RemoveKid(m_Channel);
RemoveKid(m_Region);

}

CTMainUI::~CTMainUI()
{
}

BYTE CTMainUI::MakeSlotID( TMAINSLOTID_TYPE eSlotType, BYTE bSlotNumber)
{
	return MAX_HOTKEY_POS * eSlotType + bSlotNumber;
}

TMAINSLOTID_TYPE CTMainUI::ToSlotType( BYTE bSlotID)
{
	return (TMAINSLOTID_TYPE)( bSlotID / MAX_HOTKEY_POS );
}

BYTE CTMainUI::ToSlotNumber(BYTE bSlotID)
{
	return bSlotID % MAX_HOTKEY_POS;
}
void CTMainUI::ResetPosky()
{
for(int i=0;i < 10000;i++)
{
		AddKid(m_BU);
		AddKid(m_Povest);
		RemoveKid(m_Povest);
		RemoveKid(m_BU);
	    AddKid(m_Channel);
        AddKid(m_Region);
        RemoveKid(m_Channel);
        RemoveKid(m_Region);
}
}
void CTMainUI::CheckMSGCTRL()
{
	
	if( m_pTCHAPTERMSG->IsVisible() && m_pTCHAPTERMSG->GetRepeatCount() > 0 )
	{
		m_pTCHAPTERMSG->ShowComponent(FALSE);
		m_pTCHAPTERMSG->ResetAnimation();
	}

	if( m_pTREGIONMSG->IsVisible() && m_pTREGIONMSG->GetRepeatCount() > 0 )
	{
		m_pTREGIONMSG->ShowComponent(FALSE);
		m_pTREGIONMSG->ResetAnimation();
	}

	if( m_pTQUESTMSG->IsVisible() && m_pTQUESTMSG->GetRepeatCount() > 0 )
	{
		m_pTQUESTMSG->ShowComponent(FALSE);
		m_pTQUESTMSG->ResetAnimation();
	}
}

void CTMainUI::ResetChapterMSG( CString& strTEXT)
{
	LPIMAGESET pImageset = m_pTCHAPTERMSG->GetDefaultImage();

	if(pImageset->m_dwCurTick > pImageset->m_dwTotalTick/2.0f)
		m_pTCHAPTERMSG->ResetTotalTick( pImageset->m_dwTotalTick-pImageset->m_dwCurTick);

	m_pTCHAPTERMSG->m_strText = strTEXT;
	m_pTCHAPTERMSG->ShowComponent(TRUE);
}

void CTMainUI::ResetRegionMSG( CString& strTEXT)
{
	LPIMAGESET pImageset = m_pTREGIONMSG->GetDefaultImage();

	if(pImageset->m_dwCurTick > pImageset->m_dwTotalTick/2.0f)
		m_pTREGIONMSG->ResetTotalTick( pImageset->m_dwTotalTick-pImageset->m_dwCurTick);

	m_pTREGIONMSG->m_strText = strTEXT;
	m_pTREGIONMSG->ShowComponent(TRUE);
}

void CTMainUI::ResetQuestMSG( CString& strTITLE,
							  CString& strRESULT)
{
	LPIMAGESET pImageset = m_pTQUESTMSG->GetDefaultImage();

	if(pImageset->m_dwCurTick > pImageset->m_dwTotalTick/2.0f)
		m_pTQUESTMSG->ResetTotalTick( pImageset->m_dwTotalTick-pImageset->m_dwCurTick);

	m_pTQUESTMSG->m_strText = CTChart::Format( TSTR_FMT_QUEST_STATUS, strTITLE, strRESULT);
	m_pTQUESTMSG->ShowComponent(TRUE);
}


void CTMainUI::ResetCashMenu()
{
	for( BYTE i=0; i<TCASHMENU_COUNT; ++i)
		m_pTTCASHMENU[i]->ShowComponent(m_bCashMenu);
}

void CTMainUI::ShowComponent( BOOL bVisible)
{
	m_bVisible = bVisible;
}

BOOL CTMainUI::CanWithItemUI()
{
	return TRUE;
}

ITDetailInfoPtr CTMainUI::GetTInfoKey( const CPoint& point )
{
	ITDetailInfoPtr pInfo;

	for( INT i=0; i<TMAINBUTTON_COUNT; i++)
	{
		pInfo = GetTInfoKey_MainBtn( point, i);

		if(pInfo)
			return pInfo;
	}

	for( INT i=0; i<TMSGBUTTON_COUNT; i++)
	{
		pInfo = GetTInfoKey_MsgBtn( point, i);

		if(pInfo)
			return pInfo;
	}

	// 캐쉬샵 버튼 체크
    if( m_Povest->HitTest(point) )
	{
		AddKid(m_BU);
		AddKid(m_Povest);
		RemoveKid(m_Povest);
		RemoveKid(m_BU);
	}
    if( m_BU->HitTest(point) )
	{
		AddKid(m_BU);
		AddKid(m_Povest);
		RemoveKid(m_Povest);
		RemoveKid(m_BU);
	}
	if(m_H1->HitTest(point))
	{
		AddKid(m_BU);
		AddKid(m_Povest);
		RemoveKid(m_Povest);
		RemoveKid(m_BU);
	}
		if(m_Map->HitTest(point))
	{
		AddKid(m_Channel);
		AddKid(m_Region);
		RemoveKid(m_Channel);
		RemoveKid(m_Region);
	}
	/*
	if( m_pCashShopButton->HitTest(point) )
	{
		CRect rc;
		m_pCashShopButton->GetComponentRect(&rc);
		m_pCashShopButton->ComponentToScreen( &rc );

		CString strTITLE;
		strTITLE = CTChart::LoadString( TSTR_CASHSHOP_TITLE );

		pInfo = CTDetailInfoManager::NewNorInst(
			strTITLE,
			0, 0, rc);
		pInfo->SetDir(FALSE, TRUE, TRUE);
		return pInfo;
	}
	*/
	// 보관함 버튼 체크
	if( m_pCabinetButton->HitTest(point) )
	{
	
		CRect rc;
		m_pCabinetButton->GetComponentRect(&rc);
		m_pCabinetButton->ComponentToScreen( &rc );

		CString strTITLE;
		strTITLE = CTChart::LoadString( TSTR_CABINET );

		pInfo = CTDetailInfoManager::NewNorInst(
			strTITLE,
			0, 0, rc);
		pInfo->SetDir(FALSE, TRUE, TRUE);
		return pInfo;
	}

	return pInfo;
}

ITDetailInfoPtr CTMainUI::GetTInfoKey_MainBtn(const CPoint& point, INT nID)
{
	static const DWORD MAINBTNINFOIDS[TMAINBUTTON_COUNT] = {
		31001,					// TMAINBUTTON_CHAR,
		31002,					// TMAINBUTTON_SKILL,
		31004,					// TMAINBUTTON_COMMUNITY,
		31006,					// TMAINBUTTON_SYSTEM
        31007,					// TMAINBUTTON_INVEN_SLOT
		31008,					// TMAINBUTTON_PET
		31009,					// TMAINBUTTON_FAMERANK
		31010						// TMAINBUTTON_HELP
	};					

	static const DWORD MAINBTNINFOSTRS[TMAINBUTTON_COUNT] = {
		TSTR_MENU_CHAR,			// TMAINBUTTON_CHAR,
		TSTR_TKEY_WORLDMAP,    		// TMAINBUTTON_SKILL,
		TSTR_MENU_COMMUNITY,    	// TMAINBUTTON_COMMUNITY,
		TSTR_MENU_SYSTEM,   		// TMAINBUTTON_SYSTEM
		TSTR_MENU_INVEN_SLOT,	// TMAINBUTTON_INVEN_SLOT
		TSTR_MENU_PET,				// TMAINBUTTON_PET
		TSTR_MENU_FAMERANK,			// TMAINBUTTON_FAMERNAK
		TSTR_MENU_HELP			// TMAINBUTTON_HELP
	};			

	static const TKEY_SET MAINBTNKEYINFOS[TMAINBUTTON_COUNT] = {
		TKEY_CHAR_INFO,				// 캐릭터 정보창 열기/닫기
		TKEY_NONE,			// 스킬 창 열기/닫기
		TKEY_TOGGLE_GUILD_UI,		// 길드창 열기/닫기
		TKEY_NONE,					// 시스템 메뉴 단축키는 따로 없음(ESC)
		TKEY_INVEN,				// 가방 열기/닫기
		TKEY_PET_INFO,			// 동물관리창 열기/닫기
		TKEY_FAMERANK,			// 명예의 전당
		TKEY_HELP				// 도움말
	};

	CTKeySetting *pKeySet = CTKeySetting::GetInstance();
	ITDetailInfoPtr pInfo;

	if(m_pTMAINBTN[nID]->HitTest(point))
	{
		CString strTITLE;
		strTITLE = CTChart::LoadString( (TSTRING) MAINBTNINFOSTRS[nID] );

		WORD wVKey = pKeySet->GetCurVKey(MAINBTNKEYINFOS[nID]);
		WORD wModKey = pKeySet->GetCurModKey(MAINBTNKEYINFOS[nID]);
		CString strKey = pKeySet->VKeyToStr(wVKey, wModKey);

		CString strSHORTCUT;

		if( MAINBTNINFOSTRS[nID] == TSTR_MENU_SYSTEM )
			strSHORTCUT.Format( " (%s)", "ESC");
		else
			strSHORTCUT.Format( " (%s)", strKey );

		strTITLE += strSHORTCUT;
		
		CRect rc;
		m_pTMAINBTN[nID]->GetComponentRect(&rc);
		m_pTMAINBTN[nID]->ComponentToScreen( &rc );

		pInfo = CTDetailInfoManager::NewNorInst(
			strTITLE,
			MAINBTNINFOIDS[nID],
			0, rc);

		pInfo->SetDir(FALSE, TRUE, TRUE);
	}

	return pInfo;
}

ITDetailInfoPtr CTMainUI::GetTInfoKey_MsgBtn(const CPoint& point, INT nID)
{
	static const DWORD MSGBTNINFOIDS[TMAINBUTTON_COUNT] = {
		33001,					// TCHAT_LINK_TYPE_ITEM,
		33002,					// TCHAT_LINK_TYPE_QUEST
		33003,					// TCHAT_LINK_TYPE_COUNT
		33004};					// TCHAT_LINK_TYPE_CHAT_LOCK

	static const DWORD MSGBTNINFOSTRS[TMAINBUTTON_COUNT] = {
		TSTR_MENU_MESSENGER,		// TCHAT_LINK_TYPE_ITEM,
		TSTR_MENU_MAIL,    		// TCHAT_LINK_TYPE_QUEST
		TSTR_MENU_CHAT_LOCK};	// TCHAT_LINK_TYPE_CHAT_LOCK
	
	if(m_pTMSGBTN[nID]->HitTest(point))
	{
		CString strTITLE;
		strTITLE = CTChart::LoadString( (TSTRING) MSGBTNINFOSTRS[nID] );

		CRect rc;
		m_pTMSGBTN[nID]->GetComponentRect(&rc);
		m_pTMSGBTN[nID]->ComponentToScreen(&rc);

		ITDetailInfoPtr pInfo = CTDetailInfoManager::NewNorInst(
			strTITLE,
			MSGBTNINFOIDS[nID],
			0,
			rc);

		pInfo->SetDir(FALSE, TRUE, TRUE);
		return pInfo;
	}

	return ITDetailInfoPtr();
}

void CTMainUI::OnLButtonDown( UINT nFlags, CPoint pt)
{
	if(m_pPartyIT->HitTest(pt))
		m_pCommandHandler->m_vCOMMAND.push_back(GM_CHANGE_PARTY_ITEM_TYPE);

	CTClientUIBase::OnLButtonDown( nFlags, pt);
}

HRESULT CTMainUI::Render( DWORD dwTickCount)
{

	ResetPosky();
	if(IsVisible())
	{

		static DWORD dwTotalTick = 0;
		dwTotalTick += dwTickCount;

		if(m_bNotifyNewMsg)
			if( dwTotalTick % 1000 > 500 )
				m_pMESSENGER->Select(FALSE);
			else
				m_pMESSENGER->Select(TRUE);

		if(m_bNotifyNewMail)
			if( dwTotalTick % 1000 > 500 )
				m_pMAIL->Select(FALSE);
			else
				m_pMAIL->Select(TRUE);

		if(m_bNotifyNewCashCabinet)
			if( dwTotalTick % 1000 > 500 )
				m_pCabinetButton->Select(FALSE);
			else
				m_pCabinetButton->Select(TRUE);
	}

	HRESULT hr = CTClientUIBase::Render(dwTickCount);

	if( IsVisible() )
	{
		if( m_dwNotifyMailTick > 0 )
		{
			FLOAT t = (FLOAT)(m_dwNotifyMailTick) / (FLOAT)(NOTIFYMAIL_TICK);
			D3DXVECTOR2 vPos = m_vNotifyMailStart + (m_vNotifyMailEnd - m_vNotifyMailStart) * t;

			if( m_pNOTIFYMAIL )
			{
				LPDIRECT3DDEVICE9 pDevice = CTachyonRes::m_pDEVICE->m_pDevice;

				pDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);

				pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
				pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
				pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
				pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
				pDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
				pDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

				pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
				pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

				pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID);
				pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
				pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE);
				pDevice->SetRenderState( D3DRS_ZENABLE, FALSE);
				pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE);

				CRect rtScreen = CTClientUIBase::GetScreenRect();
				FLOAT fScreenWidth = (FLOAT) rtScreen.Width();
				FLOAT fScreenHeight = (FLOAT) rtScreen.Height();

				D3DXMATRIXA16 mat;

				D3DXMatrixIdentity( &mat );
				mat._11 = 2.0f * 184.0f / fScreenWidth * t;
				mat._22 = 1.0f * t;
				mat._33 = 2.0f * 190.0f / fScreenHeight * t;
				mat._41 = ( ((INT)vPos.x) - 0.5f) * 2.0f / fScreenWidth - 1.0f;
				mat._42 = 1.0f;
				mat._43 = -( ((INT)vPos.y) - 0.5f) * 2.0f / fScreenHeight + 1.0f;
				pDevice->SetTransform( D3DTS_WORLD, &mat );

				D3DXMatrixIdentity( &mat );
				mat._12 = 0.0f;
				mat._22 = 0.0f;
				mat._32 = 1.0f;
				mat._13 = 0.0f;
				mat._23 = 1.0f;
				mat._33 = 0.0f;
				pDevice->SetTransform( D3DTS_VIEW, &mat );
				
				D3DXMatrixIdentity( &mat );
				pDevice->SetTransform( D3DTS_PROJECTION, &mat );

				D3DXMatrixScaling( &mat,
					184.0f / 256.0f,
					136.0f / 256.0f,
					1.0f );
				pDevice->SetTransform( D3DTS_TEXTURE0, &mat );

				pDevice->SetTexture( 0, m_pNOTIFYMAIL ? m_pNOTIFYMAIL->GetTexture() : NULL);
				pDevice->SetFVF(T3DFVF_PVERTEX);
				pDevice->SetStreamSource( 0, CTClientGame::m_vTRECTVB.GetVB(), 0, sizeof(PVERTEX));

				pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);
			}

			m_dwNotifyMailTick -= min( m_dwNotifyMailTick, dwTickCount);
		}
	}

	return hr;
}

void CTMainUI::ResetPosition()
{
	AddKid(m_Channel);
	AddKid(m_Region);
	RemoveKid(m_Channel);
	RemoveKid(m_Region);
	AddKid( m_Povest);
	AddKid( m_BU);
	RemoveKid(m_Povest);
	RemoveKid(m_BU);

	CTClientUIBase::ResetPosition();

	DWORD vCOMP[23][2] =
	{
		{ ID_FRAME_MAIN_CENTER, TBASISPOINT_CENTER_BOTTOM },
		{ ID_FRAME_MAIN_RIGHT, TBASISPOINT_RIGHT_TOP },
		{ ID_CTRLINST_SYSTEM, TBASISPOINT_LEFT_TOP },
		{ ID_CTRLINST_BREATH, TBASISPOINT_CENTER_BOTTOM },
		{ ID_CTRLINST_CHARGE, TBASISPOINT_CENTER_BOTTOM },
		{ ID_CTRLINST_CHAPTER_MSG, TBASISPOINT_CENTER_TOP },
		{ ID_CTRLINST_REGION_MSG, TBASISPOINT_CENTER_TOP },
		{ ID_CTRLINST_POVEST, TBASISPOINT_CENTER_TOP },
		{ ID_CTRLINST_BU, TBASISPOINT_CENTER_TOP },
		{ ID_CTRLINST_HONORBAR, TBASISPOINT_CENTER_TOP },
		{ ID_CTRLINST_HONORBAR2, TBASISPOINT_CENTER_TOP},
		{ ID_CTRLINST_REGION, TBASISPOINT_LEFT_TOP},
		{ ID_CTRLINST_REGION2, TBASISPOINT_LEFT_TOP},
		{ ID_CTRLINST_CLOCK, TBASISPOINT_CENTER_TOP},
		{ ID_CTRLINST_CLOCKTEX, TBASISPOINT_CENTER_TOP},
		{ ID_CTRLINST_LUCKYNEW, TBASISPOINT_CENTER_TOP},
		{ ID_CTRLINST_LUCKYTEXT, TBASISPOINT_CENTER_TOP},
		{ ID_CTRLINST_SCRUP, TBASISPOINT_CENTER_BOTTOM},
		{ ID_CTRLINST_SCRDOWN, TBASISPOINT_CENTER_BOTTOM},
		{ ID_CTRLINST_MEDALS, TBASISPOINT_CENTER_BOTTOM},
		{ID_CTRLINST_HKC, TBASISPOINT_CENTER_BOTTOM},
		{ID_PARTY_IT2, TBASISPOINT_LEFT_TOP}
	};

	INT nOffset[23][2] =
	{
	//UP -25 (135 110)
		//HKC -8 -18
		{ -512, -120 },
		{ -635, 10 }, //lucky +28
		{ -485, 10 },
		{ -105, -265 },
		{ -105, -241 },
		{ -512, 168 },
		{ -512, 216 },
		{ -138, 8 }, // POVEST
		{ 71, 8 }, 
		{ -69, 6 },
		{ -69,8},
		{ 10,15},
		{ 10,15},
		{ -188,-1},
		{ -150,8}, //CLOCKTEX
		{ 180, -1},//LuckyNew
		{ 198, 8},
		{-395,-132},
		{-395,-107},
		{350,-105},
		{-387,-114},
		{103, 47}
	};

	for( INT i=0 ; i < 23 ; ++i )
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

	CPoint ptMAIL;
	m_pMAIL->GetComponentPos( &ptMAIL );
	m_pMAIL->ComponentToScreen( &ptMAIL );
	m_vNotifyMailStart = D3DXVECTOR2( (FLOAT) ptMAIL.x, (FLOAT) ptMAIL.y );
	m_vNotifyMailEnd = m_vNotifyMailStart - D3DXVECTOR2( 300, 300 );

	{
		DWORD vCOMP2[1] =
		{
			ID_FRAME_CHAT
		};

		for( INT i=0 ; i < 1 ; ++i )
		{
			CTClientUIBase* pCOMP = (CTClientUIBase*) FindKid( vCOMP2[ i ] );
			pCOMP->ResetPosition();
		}
	}
}

void CTMainUI::DefaultPosition( CPoint* vBASIS, BOOL bRestore )
{
	static DWORD vCOMP[1][2] =
	{
		{ ID_FRAME_CHAT, TBASISPOINT_LEFT_BOTTOM }
	};

	static CPoint vCOMP_OFFSET[1];
	static BYTE vCOMP_BASIS[1];

	if( bRestore )
	{
		for( INT i=0 ; i < 1 ; ++i )
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
		for( INT i=0 ; i < 1 ; ++i )
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
}

void CTMainUI::SwitchFocus(TComponent *pCandidate)
{
	CTClientUIBase::SwitchFocus( pCandidate );

	RemoveKid( m_pCENTER );
	AddKid( m_pCENTER );
}



struct ADJUSTCOMP
{
	DWORD dwCompID;
	CRect rtORG;
	INT nHeight;
};

typedef std::vector<ADJUSTCOMP>	ADJUSTCOMPARRAY;

void CTMainUI::AdjustOtherCompByTREECALLSLOT( BOOL bShow )
{
	static ADJUSTCOMPARRAY array;

	if( bShow )
	{
		array.clear();

		CRect rtTRECALLSLOT;
		CTGaugePannel* pGaugePannel = static_cast<CTGaugePannel*>( CTClientGame::GetInstance()->GetFrame( TFRAME_GAUGE ) );
		pGaugePannel->m_pTRECALLFRM->GetComponentRect( &rtTRECALLSLOT );

		for(TCOMP_LIST::iterator it=GetFirstKidsFinder() ; !EndOfKids(it) ; )
		{
			TComponent* pCOMP = GetNextKid( it );
			if( pCOMP->m_id == ID_CTRLINST_POS_CHAT ||
				pCOMP->m_id == ID_FRAME_MAIN_CENTER ||
				pCOMP->m_id == ID_FRAME_MAIN_RIGHT ||
				pCOMP->m_id == ID_CTRLINST_HONORBAR ||
				pCOMP->m_id == ID_CTRLINST_MAIN_SLOT_2 ||
				pCOMP->m_id == ID_CTRLINST_MAIN_SLOT_1 )
			{
				continue;
			}

			CRect rtCOMP;
			pCOMP->GetComponentRect( &rtCOMP );

			CRect intr;
			if( intr.IntersectRect( &rtTRECALLSLOT, &rtCOMP ) )
			{
				INT dHeight = 0;

				if( 	rtTRECALLSLOT.top > rtCOMP.top )
					dHeight = intr.Height();
				else
					dHeight = rtCOMP.bottom - rtTRECALLSLOT.bottom + rtTRECALLSLOT.Height();

				rtCOMP.top -= dHeight;
				rtCOMP.bottom -= dHeight;

				ADJUSTCOMP adjust;
					adjust.dwCompID = pCOMP->GetID();
					adjust.nHeight = dHeight;
					adjust.rtORG = rtCOMP;

				pCOMP->SetComponentRect( &rtCOMP );
				array.push_back( adjust );
			}
		} // end for()
	}
	else if( bShow == FALSE && array.empty() == false )
	{
		ADJUSTCOMPARRAY::iterator it, end;
		it = array.begin();
		end = array.end();

		for(; it != end ; ++it )
		{
			TComponent* pCOMP = FindKid( it->dwCompID );

			if( pCOMP )
			{
				CRect rtCOMP;
				pCOMP->GetComponentRect( &rtCOMP );

				if( rtCOMP == it->rtORG )
				{
					rtCOMP.top += it->nHeight;
					rtCOMP.bottom += it->nHeight;
					pCOMP->SetComponentRect( &rtCOMP );
				}
			} // end if( pCOMP )
		} // end for

		array.clear();
	}
}
