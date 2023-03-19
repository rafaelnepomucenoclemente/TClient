#include "stdafx.h"
#include "Resource.h"
#include "TClientGame.h"
#include "TClientWnd.h"
#include "TNewQuestDlg.h"


CPoint CTNewQuestDlg::m_ptPOS = CPoint(0,0);

struct binary_qclass : public binary_function< CTClientQClass *, CTClientQClass *, bool>
{
	bool operator () ( const CTClientQClass * &_Left, const CTClientQClass * &_Right) const
	{
		return _Left->m_pTQCLASS && _Left->m_pTQCLASS->m_bMAIN ? true : false;
	};
};

struct binary_tquest : public binary_function< CTClientQuest *, CTClientQuest *, bool>
{
	bool operator () ( const CTClientQuest * &_Left, const CTClientQuest * &_Right) const
	{
		return binary_quest()( _Left->m_pTQUEST, _Right->m_pTQUEST);
	};
};

CTNewQuestDlg::CTNewQuestDlg( TComponent* pParent, LP_FRAMEDESC pDesc, CTClientChar* pHost)
: CTClientUIBase( pParent, pDesc), m_pHost(pHost)
{
	static DWORD dwItem[TREWARDITEMCOUNT] =
	{
		ID_CTRLINST_ITEM_1,
		ID_CTRLINST_ITEM_2
	};

	static DWORD dwSkill[TREWARDITEMCOUNT] =
	{
		ID_CTRLINST_SKILL_1,
		ID_CTRLINST_SKILL_2
	};

	static DWORD dwSel[TREWARDITEMCOUNT] =
	{
		ID_CTRLINST_SEL_1,
		ID_CTRLINST_SEL_2
	};

	m_pSummary = (TList*) FindKid( ID_CTRLINST_SUMMARY );
	m_pTerm = (TList*) FindKid( ID_CTRLINST_TERM );
	m_pContents = (TList*) FindKid( ID_CTRLINST_CONTENTS );
	m_pReward = (TList*) FindKid( ID_CTRLINST_REWARD );
	m_pAccept = (TButton*) FindKid( ID_CTRLINST_OK );
	m_pRefuse = (TButton*) FindKid( ID_CTRLINST_CANCEL );

	m_pSummary->m_nWheelMoveValue = 1;
	m_pTerm->m_nWheelMoveValue = 1;
	m_pContents->m_nWheelMoveValue = 1;
	m_pReward->m_nWheelMoveValue = 1;
	
	for( INT i=0; i < TREWARDITEMCOUNT ; ++i)
	{
		m_pITEM[i] = (TImageList*) FindKid( dwItem[i]);
		m_pSKILL[i] = (TImageList*) FindKid( dwSkill[i]);
		m_pSEL[i] = FindKid( dwSel[i] );
	}
	CPoint poska;
	//m_pReward->GetComponentPos(&poska);
    //m_pReward->MoveComponent(CPoint(poska.x, poska.y -50));
	m_pREFUSE = (TButton *) FindKid(ID_CTRLINST_CANCEL);
	m_pACCEPT = (TButton *) FindKid(ID_CTRLINST_OK);
	m_pMONEY[0] = FindKid( ID_CTRLINST_GOLD );
	m_pMONEY[1] = FindKid( ID_CTRLINST_LUNA );
	m_pMONEY[2] = FindKid( ID_CTRLINST_CRON );
	m_pEXP = FindKid( ID_CTRLINST_EXP );


	TComponent* pTermCompleted = FindKid( ID_CTRLINST_QUEST_COMPLETED );
	TComponent* pTermInCompleted = FindKid( ID_CTRLINST_QUEST_INCOMPLETED );
	TComponent* pTermFail = FindKid( ID_CTRLINST_QUEST_FAIL );

	CRect rtIcon;
	pTermCompleted->GetComponentRect( &rtIcon );
	pTermCompleted->ScreenToComponent( &rtIcon );
	pTermCompleted->MoveComponent( CPoint(rtIcon.left, 416) );
	INT nTermItemSize = m_pTerm->GetMaxItemHeight();


	for ( int i = 0; i < TERM_SLOT_COUNT; ++i )
	{
		TComponent* pCOMP0 = new TComponent( this, pTermCompleted->m_pDESC );
		TComponent* pCOMP1 = new TComponent( this, pTermInCompleted->m_pDESC );
		TComponent* pCOMP2 = new TComponent( this, pTermFail->m_pDESC );

		pCOMP0->m_id = GetUniqueID();
		pCOMP1->m_id = GetUniqueID();
		pCOMP2->m_id = GetUniqueID();

		AddKid( pCOMP0 );
		AddKid( pCOMP1 );
		AddKid( pCOMP2 );

		CPoint ptMove( rtIcon.left, rtIcon.top + (22 * i) );

		pCOMP0->MoveComponent( ptMove );
		pCOMP1->MoveComponent( ptMove );
		pCOMP2->MoveComponent( ptMove );

		m_pTermICon[ TERM_QUEST_COMPLETED ][i] = pCOMP0;
		m_pTermICon[ TERM_QUEST_INCOMPLETED ][i] = pCOMP1;
		m_pTermICon[ TERM_QUEST_FAIL ][i] = pCOMP2;

		pCOMP0->ShowComponent( FALSE );
		pCOMP1->ShowComponent( FALSE );
		pCOMP2->ShowComponent( FALSE );

	}

	RemoveKid( pTermCompleted );
	RemoveKid( pTermInCompleted );
	RemoveKid( pTermFail );

	delete pTermCompleted;
	delete pTermInCompleted;
	delete pTermFail;

	m_pMapOpen = (TButton *) FindKid( ID_CTRLINST_BTN_MAPOPEN );
	m_pMapClose = (TButton *) FindKid( ID_CTRLINST_BTN_MAPCLOSE );
	m_pMapFrame = FindKid( ID_CTRLINST_MAP_FRAME );
	m_pMap = FindKid( ID_CTRLINST_MAP_COMP );
	m_pMapImageList =  (TImageList *) FindKid( ID_CTRLINST_MAP_IMAGELIST );
	m_pMapQuestIcon = FindKid( ID_CTRLINST_MAP_QUESTICON );

	RemoveKid( m_pMapImageList );
	RemoveKid( m_pMapQuestIcon );

	m_nMainUnitX = 0;
	m_nMainUnitZ = 0;
	m_ptMapIcon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vTCENTER = D3DXVECTOR2( 0.0f, 0.0f);
	m_fTSCALE = 1.0f;
	m_pTMAP = NULL;
	m_pBACKBUF2 = NULL;
	m_pBACKTEX2 = NULL;
	m_bHideMap = FALSE;
	m_bMOVE = FALSE;
	m_bRenderMap = FALSE;

	m_pMapOpen->ShowComponent(FALSE);
	m_pContents->ApplyUserColor(TRUE);

	m_pTTOPREWARD = NULL;
	m_pTSELREWARD = NULL;
	m_pTQUEST = NULL;
	m_pHost = pHost;
	m_bPrintMSG = TRUE;
	m_pQuestDlg = this;
	m_strNPCTalk = "";
	m_strNPCTitle = "";
	m_strAnswerWhenNPCTalk = "";

	m_dwCompleteID = TSTR_GIVEUP;
	m_dwAcceptID = TSTR_GIVEUP;

	m_pAccept->m_menu[TNM_LCLICK] = GM_QUEST_GIVEUP;
	m_pRefuse->m_menu[TNM_LCLICK] = GM_CLOSE_UI;

	m_pRefuse->m_strText = CTChart::LoadString( TSTR_CLOSE );

	// Quest Tree �ʱ�ȭ
	m_pQLIST = static_cast<TList*>( FindKid(ID_CTRLINST_TREE) );
	m_pQLIST->ApplyUserColor(TRUE);

	TButton* pCTMP = static_cast<TButton*>( FindKid(ID_CTRLINST_COLLAPSE) );
	TButton* pETMP = static_cast<TButton*>( FindKid(ID_CTRLINST_EXPAND) );
	TButton* pBTMP = static_cast<TButton*>( FindKid(ID_CTRLINST_CHECK) );
	
	if( pCTMP && pETMP )
	{
		RemoveKid(pCTMP);
		RemoveKid(pETMP);
		RemoveKid(pBTMP);

		CRect rcPOS;
		pCTMP->GetComponentRect(&rcPOS);
		CSize szITEM = m_pQLIST->GetItemSize(0);

		m_nGBTNCOUNT = m_pQLIST->GetItemPerPage();
		m_vTCOLLAPSE = new TButton*[m_nGBTNCOUNT];
		m_vTEXPEND = new TButton*[m_nGBTNCOUNT];
		m_vTCHECK = new TButton*[m_nGBTNCOUNT];
		
		for(INT i=0; i<m_nGBTNCOUNT; ++i)
		{
			m_vTCOLLAPSE[i] = new TButton(this, pCTMP->m_pDESC);
			m_vTEXPEND[i] = new TButton(this, pETMP->m_pDESC);
			m_vTCHECK[i] = new TButton(this, pBTMP->m_pDESC);

			m_vTCOLLAPSE[i]->m_id = GetUniqueID();
			m_vTEXPEND[i]->m_id = GetUniqueID();
			m_vTCHECK[i]->m_id = GetUniqueID();
			m_vTCHECK[i]->SetStyle(TBS_STATE_BUTTON);

			AddKid(m_vTCOLLAPSE[i]);
			AddKid(m_vTEXPEND[i]);
			AddKid(m_vTCHECK[i]);

			m_vTCOLLAPSE[i]->MoveComponent(rcPOS.TopLeft());
			m_vTEXPEND[i]->MoveComponent(rcPOS.TopLeft());
			m_vTCHECK[i]->MoveComponent(rcPOS.TopLeft());

			m_vTCOLLAPSE[i]->ShowComponent(FALSE);
			m_vTEXPEND[i]->ShowComponent(FALSE);
			m_vTCHECK[i]->ShowComponent(FALSE);

			rcPOS.top += szITEM.cy;
		}	

		delete pCTMP;
		delete pETMP;
		delete pBTMP;
	}
	else
		m_nGBTNCOUNT = 0;

	m_pStatusIcon[0] = (TImageList*) FindKid(ID_CTRLINST_STATUS_ICON0);
	m_pStatusIcon[1] = (TImageList*) FindKid(ID_CTRLINST_STATUS_ICON1);
	m_pStatusIcon[2] = (TImageList*) FindKid(ID_CTRLINST_STATUS_ICON2);
	m_pStatusIcon[3] = (TImageList*) FindKid(ID_CTRLINST_STATUS_ICON3);
	m_pStatusIcon[4] = (TImageList*) FindKid(ID_CTRLINST_STATUS_ICON4);
}

CTNewQuestDlg::~CTNewQuestDlg(void)
{
	if( m_vTCOLLAPSE )
		delete [] m_vTCOLLAPSE;

	if( m_vTEXPEND )
		delete [] m_vTEXPEND;

	if( m_vTCHECK )
		delete [] m_vTCHECK;

	if ( m_pMapImageList )
		delete m_pMapImageList;

	if ( m_pMapQuestIcon  )
		delete m_pMapQuestIcon;
}

HRESULT CTNewQuestDlg::Render( DWORD dwTickCount )
{
	if(IsVisible())
	{
		INT nIndex = this->GetSel();

		LPTQUEST pTQUEST = NULL;
		if( nIndex >= 0 )
			pTQUEST = this->GetTQUEST(nIndex);

		if( m_pTQUEST != pTQUEST )
		{
			ResetTQUEST(pTQUEST);
			ResetMap(pTQUEST);
		}


		if(m_bPrintMSG)
			ResetButton();

		if(!m_bHideMap)
		{
			RenderMap(dwTickCount);

			if ( m_bRenderMap )
				RederMapPos(dwTickCount);
		}

		INT nTermCount = m_pTerm->GetItemCount();
		INT nTermTop = m_pTerm->GetTop();
		INT nTermIndex = nTermCount - nTermTop;

		for( int i = 0; i < TERM_SLOT_COUNT; ++i )
		{
			BOOL bHideSlot = TRUE;

			if ( pTQUEST )
			{
				if ( ( i <= nTermIndex ) && ( pTQUEST->m_vTTERM.size() > i) )
				{
					if ( pTQUEST->m_vTTERM[i]->m_bType != QTT_TIMER )
					{
						CTClientQuest *pTQuest = m_pHost->FindTQuest(pTQUEST->m_dwID);
						if(pTQuest)
						{
							CTClientTerm *pTTerm = pTQuest->FindTTerm(pTQUEST->m_vTTERM[i]);
							if(pTTerm)
								switch(pTTerm->GetResult())
							{
								case TTERMRESULT_COMPLETE	: 
									m_pTermICon[TERM_QUEST_COMPLETED][i]->ShowComponent( TRUE );
									m_pTermICon[TERM_QUEST_INCOMPLETED][i]->ShowComponent( FALSE );
									m_pTermICon[TERM_QUEST_FAIL][i]->ShowComponent( FALSE );
									bHideSlot = FALSE;
									break;
							} // case
						} // if
					}
				}
			}

			if ( bHideSlot )
			{
				m_pTermICon[TERM_QUEST_COMPLETED][i]->ShowComponent( FALSE );
				m_pTermICon[TERM_QUEST_INCOMPLETED][i]->ShowComponent( FALSE );
				m_pTermICon[TERM_QUEST_FAIL][i]->ShowComponent( FALSE );
			}

		}

		LPTREWARD pTREWARD[TREWARDITEMCOUNT] = { NULL, NULL};
		nIndex = m_pReward->GetTop();

		for( BYTE i=0; i<TREWARDITEMCOUNT; i++)
		{
			if( m_pReward->GetItemCount() > 0 && nIndex >= 0 )
			{
				DWORD dwValue = m_pReward->GetItemData( nIndex, i);

				if( dwValue == -1 )
                    pTREWARD[i] = NULL;
				else
					pTREWARD[i] = (LPTREWARD)dwValue;
			}

			if(!pTREWARD[i])
			{
				m_pITEM[i]->ShowComponent(FALSE);
				m_pSKILL[i]->ShowComponent(FALSE);
			}

			if( m_pSEL[i] )
				m_pSEL[i]->ShowComponent(FALSE);

			if( m_pTQUEST &&
				m_pTQUEST->m_bType == QT_COMPLETE &&
				!m_bPrintMSG &&
				pTREWARD[i] &&
				pTREWARD[i]->m_bMethod == RM_SELECT &&
				(!m_pTSELREWARD || m_pTSELREWARD == pTREWARD[i]) )
			{
				if( m_pSEL[i] )
					m_pSEL[i]->ShowComponent(TRUE);

				m_pTSELREWARD = pTREWARD[i];
			}
		}

		if( m_pTTOPREWARD != pTREWARD[0] )
		{
			m_pTTOPREWARD = pTREWARD[0];

			for( i=0; i<TREWARDITEMCOUNT; i++)
			{
				m_pSKILL[i]->ShowComponent(FALSE);
				m_pITEM[i]->ShowComponent(FALSE);

				if(pTREWARD[i])
					switch(pTREWARD[i]->m_bType)
					{
					case RT_SKILL	:
					case RT_SKILLUP	:
						{
							LPTSKILL pTSKILL = CTChart::FindTSKILLTEMP(WORD(pTREWARD[i]->m_dwID));

							if(pTSKILL)
							{
								m_pSKILL[i]->SetCurImage(pTSKILL->m_wIconID);
								m_pSKILL[i]->ShowComponent(TRUE);
							}
						}
						break;

					case RT_ITEM		:
					case RT_MAGICITEM	:
						{
							LPTITEM pTITEM = NULL;
							if( pTREWARD[i]->m_bType == RT_ITEM )
								pTITEM = CTChart::FindTITEMTEMP((WORD)pTREWARD[i]->m_dwID);
							else
							{
								LPTQUESTITEM pQuestItem = CTChart::FindTQUESTMAGICITEM( (WORD)pTREWARD[i]->m_dwID );
								if( pQuestItem )
									pTITEM = CTChart::FindTITEMTEMP( pQuestItem->m_wItemID );
								else
									pTITEM = NULL;
							}

							if( pTITEM )
							{
								if( pTREWARD[i]->m_bCount > 1 )
									m_pITEM[i]->m_strText = CTChart::Format( TSTR_FMT_NUMBER, pTREWARD[i]->m_bCount);
								else
									m_pITEM[i]->m_strText.Empty();

								LPTITEMVISUAL pTVISUAL = CTClientItem::GetDefaultVisual(pTITEM);
								WORD wImg = pTVISUAL? pTVISUAL->m_wIcon: 0;

								m_pITEM[i]->SetCurImage(wImg);
								m_pITEM[i]->ShowComponent(TRUE);
							}
						}
						break;
					}
			}
		}

		if( m_bPrintMSG )
		{
			int nCount = m_pQLIST->GetItemCount();
			int nTop = m_pQLIST->GetTop();
			for( INT i=0 ; i <5 ; ++i )
			{
				int nIndex = nTop + i;
				if( m_pStatusIcon[ i ] )
					m_pStatusIcon[ i ]->SetCurImage(0);

				if( m_pQLIST->GetItemString( nIndex, COL_STATE ).IsEmpty() )
				{
					CTClientQuest* pTQuest = GetCQUEST(nIndex);
					if( pTQuest && m_pStatusIcon[ i ] )
					{
						switch( pTQuest->GetResult() )
						{
						case TTERMRESULT_COMPLETE: m_pStatusIcon[ i ]->SetCurImage(1); break;
						case TTERMRESULT_INCOMPLETE: m_pStatusIcon[ i ]->SetCurImage(2); break;
						case TTERMRESULT_FAILED: m_pStatusIcon[ i ]->SetCurImage(3); break;
						case TTERMRESULT_TIMEOUT: m_pStatusIcon[ i ]->SetCurImage(4); break;
						}
					}
				}
			}
		}
		else
		{
			for( INT i=0 ; i <5 ; ++i )
				if( m_pStatusIcon[ i ] )
					m_pStatusIcon[ i ]->SetCurImage(0);
		}
	}

	return CTClientUIBase::Render(dwTickCount);
}

void CTNewQuestDlg::OnLButtonUp(UINT nFlags, CPoint pt)
{
	GetComponentPos( &CTNewQuestDlg::m_ptPOS);
	CTClientUIBase::OnLButtonUp( nFlags, pt);
}

void CTNewQuestDlg::OnLButtonDown(UINT nFlags, CPoint pt)
{
	
	CTClientUIBase::OnLButtonDown( nFlags, pt);

	if( !m_bPrintMSG && IsVisible() )
	{
		int nIndex = m_pReward->GetTop();

		if( m_pReward->GetItemCount() > 0 && nIndex >= 0 )
			for( BYTE i=0; i<TREWARDITEMCOUNT; i++)
			{
				LPTREWARD pTREWARD = (LPTREWARD) m_pReward->GetItemData( nIndex, i);

				if( pTREWARD && (DWORD)(pTREWARD) != (DWORD)(-1) &&
					pTREWARD->m_bMethod == RM_SELECT )
				{
					CRect rect;

					m_pSEL[i]->GetComponentRect(&rect);
					m_pSEL[i]->ComponentToScreen(&rect);

					if(rect.PtInRect(pt))
						m_pTSELREWARD = pTREWARD;
				}
			}
	}


	for(INT i=0; i<m_nGBTNCOUNT; ++i)
	{
		if( m_vTCOLLAPSE[i]->HitTest(pt) )
		{
			ExpendTree(i, FALSE);
			break;
		}

		if( m_vTEXPEND[i]->HitTest(pt) )
		{
			ExpendTree(i, TRUE);
			break;
		}

		if( m_vTCHECK[i]->HitTest(pt) && m_bPrintMSG )
		{
			CheckShowRight(i);
			break;
		}
	}

	if( m_pTerm->HitTest(pt) )
	{
		INT nTop = GetTop();
		INT nSel = GetSel();
		INT nIndex = nTop + nSel;

		LPTQUEST pQUEST = NULL;
		pQUEST = GetTQUEST( nSel );

		LPTTERM pTerm = GetSelTerm();
		DWORD idx = GetSelTermID();
		ResetMap( pQUEST, pTerm, idx );
	}
}

void CTNewQuestDlg::OnRButtonUp(UINT nFlags, CPoint pt)
{
	if(m_bMOVE)
	{
		CRect rtFRAME;
		m_pMap->GetComponentRect( &rtFRAME );
		m_pMap->ComponentToScreen( &rtFRAME );

		CPoint point(
			(rtFRAME.Width() / 2) + rtFRAME.left,
			(rtFRAME.Height() / 2) + rtFRAME.top);

		m_pCommandHandler->ClientToScreen(&point);
		SetCursorPos(
			point.x,
			point.y);
		ShowCursor(TRUE);

		m_bMOVE = FALSE;
	}

	CTClientUIBase::OnRButtonUp( nFlags, pt);
}

void CTNewQuestDlg::OnRButtonDown(UINT nFlags, CPoint pt)
{
	if ( IsVisible() && m_pMap->HitTest(pt) && !m_bHideMap)
	{
		CRect rtFRAME;
		m_pMap->GetComponentRect( &rtFRAME );
		m_pMap->ComponentToScreen( &rtFRAME );

		CPoint point(
			(rtFRAME.Width() / 2) + rtFRAME.left,
			(rtFRAME.Height() / 2) + rtFRAME.top);

		m_pCommandHandler->ClientToScreen(&point);
		ShowCursor(FALSE);
		SetCursorPos(
			point.x,
			point.y);

		m_bMOVE = TRUE;
	}
}

void CTNewQuestDlg::OnMouseMove(UINT nFlags, CPoint pt)
{
	if( !IsVisible() )
	{
		CTClientUIBase::OnMouseMove( nFlags, pt);
		return;
	}

	if ( m_bMOVE )
	{
		SIZE szFRAME;
		m_pMap->GetComponentSize( &szFRAME );


		CRect rtBack;
		m_pMap->GetComponentRect(&rtBack);
		m_pMap->ComponentToScreen( &rtBack );

		FLOAT fLength = ((FLOAT) m_pTMAP->m_pMAP->m_nUnitLength * m_pTMAP->m_pMAP->m_nTileLength);
		FLOAT fMinX = (szFRAME.cx / 2.0f) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));
		FLOAT fMaxX = ((TWORLDMAP_SIZE - szFRAME.cx) + (szFRAME.cx / 2.0f)) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));
		FLOAT fMinZ = (szFRAME.cy / 2.0f) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));
		FLOAT fMaxZ = ((TWORLDMAP_SIZE - szFRAME.cy) + (szFRAME.cy / 2.0f)) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));



		int nUnitX = INT(m_vTCENTER.x / fLength);
		int nUnitZ = INT(m_vTCENTER.y / fLength);

		fMinX += FLOAT(nUnitX) * fLength;
		fMaxX += FLOAT(nUnitX) * fLength;
		fMinZ += FLOAT(nUnitZ) * fLength;
		fMaxZ += FLOAT(nUnitZ) * fLength;

		CRect rtFRAME;
		m_pMap->GetComponentRect( &rtFRAME );
		m_pMap->ComponentToScreen( &rtFRAME );

		CPoint point(
			(rtFRAME.Width() / 2) + rtFRAME.left,
			(rtFRAME.Height() / 2) + rtFRAME.top);

		m_pCommandHandler->ClientToScreen(&point);
		SetCursorPos(
			point.x,
			point.y);
		m_pCommandHandler->ScreenToClient(&point);
		point -= pt;

		m_vTCENTER.x += fLength * FLOAT(point.x) / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));
		m_vTCENTER.y -= fLength * FLOAT(point.y) / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));

		m_vTCENTER.x = min( max( m_vTCENTER.x, fMinX), fMaxX);
		m_vTCENTER.y = min( max( m_vTCENTER.y, fMinZ), fMaxZ);
	}


	CTClientUIBase::OnMouseMove( nFlags, pt);
}

void CTNewQuestDlg::ShowComponent(BOOL bVisible)
{
	MoveComponent( CTNewQuestDlg::m_ptPOS );
	CTClientUIBase::ShowComponent(bVisible);

	if( bVisible )
	{
		for ( int i = 0; i < GetCount(); ++i )
		{
			LPTQUEST pQUEST = GetTQUEST(i);
			if ( pQUEST )
			{
				SetCurSel( i );
				break;
			}
		}

		ResetTQUEST(m_pTQUEST);
		ResetMap(m_pTQUEST);

		for(INT i=0; i<m_nGBTNCOUNT; ++i)
		{
			m_vTCOLLAPSE[i]->ShowComponent(FALSE);
			m_vTEXPEND[i]->ShowComponent(FALSE);
			m_vTCHECK[i]->ShowComponent(FALSE);
		}

		if ( m_bHideMap )
		{
			m_pMapOpen->ShowComponent( TRUE );
			m_pMapFrame->ShowComponent( FALSE );
			m_pMapClose->ShowComponent( FALSE );

		}
		else
		{
			m_pMapOpen->ShowComponent( FALSE );
			m_pMapFrame->ShowComponent( TRUE );
			m_pMapClose->ShowComponent( TRUE );
		}
	}
	else
	{
		if( m_pBACKBUF2 )
		{
			m_pBACKBUF2->Release();
			m_pBACKBUF2 = NULL;
		}

		if( m_pBACKTEX2 )
		{
			m_pBACKTEX2->Release();
			m_pBACKTEX2 = NULL;
		}
	}
}

ITDetailInfoPtr CTNewQuestDlg::GetTInfoKey(const CPoint& point)
{
	ITDetailInfoPtr pInfo;
	int nIndex = m_pReward->GetTop();

	for( BYTE i=0; i<TREWARDITEMCOUNT; i++)
	{
		LPTREWARD pTREWARD = NULL;

		if( m_pReward->GetItemCount() > 0 && nIndex >= 0 )
			pTREWARD = (LPTREWARD) m_pReward->GetItemData( nIndex, i );

		if(pTREWARD && (DWORD)(pTREWARD) != (DWORD)(-1) )
		{
			switch(pTREWARD->m_bType)
			{
			case RT_SKILL		:
			case RT_SKILLUP		:
				if(m_pSKILL[i]->HitTest(point))
				{
					LPTSKILL pTSKILL = CTChart::FindTSKILLTEMP(WORD(pTREWARD->m_dwID));

					if(pTSKILL)
					{
						CRect rc;
						GetComponentRect(&rc);

						if ( pTREWARD->m_bType == RT_SKILL )
						{
							pInfo = CTDetailInfoManager::NewSkillInst(
								pTSKILL, 1, FALSE, rc);
						}
						else if ( pTREWARD->m_bType == RT_SKILLUP )
						{
							pInfo = CTDetailInfoManager::NewSkillInst(
								pTSKILL, pTREWARD->m_bCount, FALSE, rc);
						}
					}
				}
				break;

			case RT_ITEM		:
			case RT_MAGICITEM	:
				if(m_pITEM[i]->HitTest(point))
				{
					CRect rc;
					GetComponentRect(&rc);

					if( pTREWARD->m_bType == RT_ITEM )
					{
						LPTITEM pTITEM = CTChart::FindTITEMTEMP(WORD(pTREWARD->m_dwID));
						pInfo = CTDetailInfoManager::NewItemInst(pTITEM, rc);
					}
					else
					{
						CTClientItem* pCItem = CTClientItem::FindTQuestMagicClientItem( (WORD) pTREWARD->m_dwID );
						pInfo = CTDetailInfoManager::NewItemInst(pCItem, rc);
					}
				}
				break;
			}
		}
	}

	return pInfo;
}

BOOL CTNewQuestDlg::GetTChatInfo(const CPoint& point, TCHATINFO& outInfo)
{
	if( m_pQLIST->HitTest(point) )
	{
		INT nColumn = 0;
		TListItem* pListItem = m_pQLIST->GetHitItem(point, &nColumn);
		if( !pListItem )
			return FALSE;

		DWORD dwID = pListItem->m_param;

		if( dwID && dwID != (DWORD)(-1) && nColumn == COL_ITEM )
		{
			LPTQUEST pTQUEST = NULL;

			if( m_bPrintMSG )
				pTQUEST = ((CTClientQuest*)(dwID))->m_pTQUEST;
			else
				pTQUEST = (LPTQUEST)dwID;

			if( pTQUEST )
			{
				outInfo.m_Type = TTEXT_LINK_TYPE_QUEST;
				outInfo.m_pQuest = pTQUEST;

				return TRUE;
			}
		}

		return FALSE;
	}
	else
	{
		int nIndex = m_pReward->GetTop();

		for( BYTE i=0; i<TREWARDITEMCOUNT; ++i )
		{
			LPTREWARD pTREWARD = NULL;

			if( m_pReward->GetItemCount() > 0 && nIndex >= 0 )
				pTREWARD = (LPTREWARD) m_pReward->GetItemData( nIndex, i);

			if( pTREWARD && (DWORD)(pTREWARD) != (DWORD)(-1) &&
				(pTREWARD->m_bType == RT_ITEM || pTREWARD->m_bType == RT_MAGICITEM) )
			{
				if(m_pITEM[i]->HitTest(point))
				{
					CTClientItem* pCItem;
					LPTITEM pTITEM;

					if( pTREWARD->m_bType == RT_ITEM )
					{
						pCItem = NULL;
						pTITEM = CTChart::FindTITEMTEMP(WORD(pTREWARD->m_dwID));
					}
					else
					{
						pCItem = CTClientItem::FindTQuestMagicClientItem( (WORD) pTREWARD->m_dwID );
						if( pCItem )
							pTITEM = pCItem->GetTITEM();
						else
							pTITEM = NULL;
					}

					if( pTITEM )
					{
						outInfo.m_Type = TTEXT_LINK_TYPE_ITEM;
						outInfo.m_pItem = pTITEM;
						outInfo.m_pClientItem = pCItem;
						
						return TRUE;
					}

					return FALSE;
				}
			}
		}
	}

	return FALSE;
}

void CTNewQuestDlg::Reset()
{
	RemoveAll();
	m_pTTOPREWARD = NULL;
	ResetTQUEST(NULL);
}

void CTNewQuestDlg::ResetTQUEST( LPTQUEST pTQUEST)
{
	LPTQUEST pTMISSION = pTQUEST;
	m_pTQUEST = pTQUEST;

	BOOL bCanPerf = TRUE;

	if( m_pTQUEST && m_pTQUEST->m_bType == QT_COMPLETE )
	{
		pTMISSION = CTChart::FindTMISSION(m_pTQUEST);

		if( !pTMISSION || pTMISSION->m_bType != QT_MISSION )
			m_pTQUEST = NULL;
		m_pACCEPT->m_strText = CTChart::LoadString( (TSTRING) m_dwCompleteID);
	}
	else if( m_pTQUEST && m_pTQUEST->m_bType == QT_MISSION )
	{
		CTClientGame* pTGAME = CTClientGame::GetInstance();
		CTClientObjBase* pTARGET = pTGAME->GetTargetObj();
		if( pTARGET )
		{
			MAPDWORD::iterator findCOND = pTARGET->m_mapTQUESTCOND.find(m_pTQUEST->m_dwID);
			if( findCOND != pTARGET->m_mapTQUESTCOND.end() )
			{
				if( findCOND->second != QCT_NONE )
					bCanPerf = FALSE;
			}
		}

		m_pACCEPT->m_strText = CTChart::LoadString( (TSTRING) m_dwAcceptID);
	}
	else
		m_pACCEPT->m_strText = CTChart::LoadString( (TSTRING) m_dwAcceptID);

	if(m_pTQUEST && bCanPerf)
		m_pACCEPT->EnableComponent(TRUE);
	else
		m_pACCEPT->EnableComponent(FALSE);

	m_pSummary->RemoveAll();
	m_pTerm->RemoveAll();
	m_pContents->RemoveAll();
	m_pReward->RemoveAll();
	m_pMONEY[0]->m_strText = "";
	m_pMONEY[1]->m_strText = "";
	m_pMONEY[2]->m_strText = "";
	m_pEXP->m_strText = "";

	int nIndex = 0;
	if(m_pTQUEST)
	{
		m_strNPCTitle = m_pTQUEST->m_strNPCName;

		if(!bCanPerf)
		{
			// �Ҽ���������Ʈ
			CString strCANNOTMSG;
			strCANNOTMSG = CTChart::LoadString( TSTR_QUEST_CANNOTPERF);

			SummaryMessage( strCANNOTMSG);
		}
		else
		{
			// ��ǥ����
			INT nTermLine = 0;
			INT nNumber = 1;
			for( BYTE i=0; i<INT(pTMISSION->m_vTTERM.size()); i++)
			{
				if( pTMISSION->m_vTTERM[i]->m_bType != QTT_TIMER )
				{
					CString strRESULT;

					CTClientQuest *pTQuest = m_pHost->FindTQuest(pTMISSION->m_dwID);
					if(pTQuest)
					{
						CTClientTerm *pTTerm = pTQuest->FindTTerm(pTMISSION->m_vTTERM[i]);
						if(pTTerm)
							switch(pTTerm->GetResult())
							{
							case TTERMRESULT_INCOMPLETE	:
								strRESULT = CTChart::Format( TSTR_QUEST_STATUS, pTTerm->m_bCount, pTMISSION->m_vTTERM[i]->m_bCount);
								break;

							case TTERMRESULT_TIMEOUT	: strRESULT.Empty(); break; //  = CTChart::LoadString( TSTR_QRESULT_TIMEOUT); break;
							case TTERMRESULT_FAILED		: strRESULT.Empty(); break; // = CTChart::LoadString( TSTR_QRESULT_FAILED); break;
							case TTERMRESULT_COMPLETE	: strRESULT.Empty(); break; //  = CTChart::LoadString( TSTR_QRESULT_COMPLETE); break;
							}
						else
						{
							strRESULT = CTChart::Format( TSTR_QUEST_STATUS, 0, pTMISSION->m_vTTERM[i]->m_bCount);
						}
					}

					TermMessage(
						pTMISSION->m_vTTERM[i]->m_dwID,
						pTMISSION->m_vTTERM[i]->m_strTermMSG,
						strRESULT,
						nTermLine,
						nNumber);
				}
			}

			// �������
			SummaryMessage( pTMISSION->m_strSummaryMSG);

			// ��ȭ����
			if(m_bPrintMSG)
			{
				CString strHeader = GetSpeakerString(m_strNPCTitle);
				TextMessage( strHeader, pTMISSION->m_strTriggerMSG);

				strHeader = GetSpeakerString(m_pHost->GetName());
				TextMessage( strHeader, pTMISSION->m_strReply);

				strHeader = GetSpeakerString(m_strNPCTitle);
				TextMessage( strHeader, pTMISSION->m_strAcceptMSG);
			}

			INT nRewardItemCount = 0;

			// ������
			 for( i=0; i<INT(pTMISSION->m_vTREWARD.size()); i++)
			{
				CString strREWARD;
				strREWARD.Empty();

				switch(pTMISSION->m_vTREWARD[i]->m_bType)
				{
				case RT_SKILL	:
				case RT_SKILLUP	:
					{
						LPTSKILL pTSKILL = CTChart::FindTSKILLTEMP(WORD(pTMISSION->m_vTREWARD[i]->m_dwID));
						CTClientSkill* pTHOSTSKILL = m_pHost->FindTSkill(WORD(pTMISSION->m_vTREWARD[i]->m_dwID));

						/*BOOL bHasAlready = (pTHOSTSKILL) &&
							(pTSKILL->m_dwClassID == pTHOSTSKILL->m_pTSKILL->m_dwClassID) &&
							(pTSKILL->m_bLevel == pTHOSTSKILL->m_pTSKILL->m_bLevel);*/

						if( pTSKILL &&
							TCHECK_CLASS( pTSKILL->m_dwClassID, m_pHost->m_bClassID) /*&&
							!bHasAlready*/ )
						{
							strREWARD = CTChart::Format( TSTR_FMT_SKILL_REWARD, pTSKILL->m_strNAME);
						}
					}

					break;

				case RT_ITEM	:
				case RT_MAGICITEM	:
					{
						LPTITEM pTITEM = NULL;
						if( pTMISSION->m_vTREWARD[i]->m_bType == RT_ITEM )
							pTITEM = CTChart::FindTITEMTEMP((WORD)pTMISSION->m_vTREWARD[i]->m_dwID);
						else
						{
							LPTQUESTITEM pQuestItem = CTChart::FindTQUESTMAGICITEM( (WORD)pTMISSION->m_vTREWARD[i]->m_dwID );
							if( pQuestItem )
								pTITEM = CTChart::FindTITEMTEMP( pQuestItem->m_wItemID );
							else
								pTITEM = NULL;
						}

						if( pTITEM && TCHECK_CLASS( pTITEM->m_dwClassID, m_pHost->m_bClassID) )
						{
							strREWARD = CTChart::Format( TSTR_FMT_REWARD, pTITEM->m_strNAME, pTMISSION->m_vTREWARD[i]->m_bCount);
						}
					}

					break;

				case RT_GOLD	:
					{
						//strREWARD = CTClientGame::MakeMoneyStr(pTMISSION->m_vTREWARD[i]->m_dwID);
						// �������� �ƴ϶� ���� �־��ִµ��� �ִ�.

						DWORD dwMONEY[3] = { 0, 0, 0 };

						CTClientGame::SplitMoney(
							pTMISSION->m_vTREWARD[i]->m_dwID,
							&dwMONEY[0],
							&dwMONEY[1],
							&dwMONEY[2]);

						CString strFMT;
						for( INT i=0 ; i < 3 ; ++i )
						{
							strFMT.Format( "%u", dwMONEY[i]);
							m_pMONEY[i]->m_strText = strFMT;
						}
					}

					break;

				case RT_EXP		:
					{
						CString strEXP;
						strEXP.Format( "%u", pTMISSION->m_vTREWARD[i]->m_dwID);
						m_pEXP->m_strText = strEXP;
					}

					break;
				}

				if(!strREWARD.IsEmpty())
				{
					switch(pTMISSION->m_vTREWARD[i]->m_bMethod)
					{
					case RM_SELECT	:
						{
							CString strTEXT;

							strTEXT = CTChart::LoadString( TSTR_TEXT_SELREWARD);
							strREWARD += strTEXT;
						}

						break;

					case RM_PROB	:
						{
							CString strTEXT;

							strTEXT = CTChart::Format( TSTR_FMT_PROBREWARD, pTMISSION->m_vTREWARD[i]->m_bProb, '%');
							strREWARD += strTEXT;
						}

						break;
					}

					INT nLine=0;
					INT nCol=0;

					if( (nRewardItemCount % 2) == 0 )
						nLine = m_pReward->AddString( strREWARD );
					else
					{
						nLine = m_pReward->GetItemCount()-1; // ������ ����
						nCol = 1;

						m_pReward->SetItemString( nLine, nCol, (LPCTSTR)strREWARD );
					}

					m_pReward->SetItemData( nLine, nCol, (DWORD) pTMISSION->m_vTREWARD[i] );
					++nRewardItemCount;
				}
			}
		}

		m_pTTOPREWARD = NULL;
		m_pTSELREWARD = NULL;
	}

	if( m_bPrintMSG == FALSE ) // NPC��ȭâ�̸�
	{
		if( m_strAnswerWhenNPCTalk.GetLength() )
		{
			CString strHeader = GetSpeakerString(m_pHost->GetName());
			TextMessage( strHeader, m_strAnswerWhenNPCTalk);		
		}

		if( m_strNPCTalk.GetLength() )
		{
			CString strHeader = GetSpeakerString(m_strNPCTitle);
			TextMessage( strHeader, m_strNPCTalk );
		}
	}
}

void CTNewQuestDlg::SummaryMessage( CString strText)
{
	CSize szITEM = m_pSummary->GetItemSize(0);
	CSize szTEXT(0,0);

	CString strFORMAT;
	CString strMSG;

	int nPOS = 0;

	if( CTNationOption::MODIFY_WORD_BREAK )
	{
		CSize szSpaceSize;
		m_pSummary->GetTextExtentPoint( " ", szSpaceSize);

		CString strLINE;
		CSize szLINE(0,0);

		strMSG = strText.Tokenize( " \n", nPOS);
		while(!strMSG.IsEmpty())
		{
			strMSG.Remove('\r');
			strMSG.Replace( "%s", m_pHost->GetName());

			CSize szMSG;
			m_pSummary->GetTextExtentPoint( LPCTSTR(strMSG), szMSG);

			if( szMSG.cx+szLINE.cx <= szITEM.cx)
			{
				strLINE += strMSG;
				szLINE.cx += szMSG.cx;
			}
			else
			{
				INT nIndex = m_pSummary->AddString(_T(""));

				m_pSummary->SetItemString( nIndex, 0, strLINE);
				m_pSummary->SetUserColor( nIndex, 0, TCOLOR_QTERM_TEXT);

				szLINE.cx = szMSG.cx;
				strLINE = strMSG;
			}

			BYTE c = strText.GetAt(nPOS-1); // ������ ���ؼ� Tokenize���߳�.
			if( c == ' ')
			{
				strLINE += ' ';
				szLINE.cx += szSpaceSize.cx;
			}
			else if( c == '\n')
			{
				INT nIndex = m_pSummary->AddString(_T(""));

				m_pSummary->SetItemString( nIndex, 0, strLINE);
				m_pSummary->SetUserColor( nIndex, 0, TCOLOR_QTERM_TEXT);

				strLINE.Empty();
				szLINE.cx = 0;
			}

			strMSG = strText.Tokenize( " \n", nPOS);
		}

		if(!strLINE.IsEmpty())
		{
			INT nIndex = m_pSummary->AddString(_T(""));

			m_pSummary->SetItemString( nIndex, 0, strLINE);
			m_pSummary->SetUserColor( nIndex, 0, TCOLOR_QTERM_TEXT);
		}
	}
	else
	{
		szITEM.cx -= TMSG_MARGINE;

		strMSG = strText.Tokenize( "\n", nPOS);
		while(!strMSG.IsEmpty())
		{
			strMSG.Remove('\r');
			strMSG.Replace( "%s", m_pHost->GetName());

			while(!strMSG.IsEmpty())
			{
				int nIndex = m_pSummary->AddString(_T(" "));
				m_pSummary->SetUserColor(1, 0, TCOLOR_QTERM_TEXT);

				m_pSummary->GetTextExtentPoint( LPCTSTR(strMSG), szTEXT);
				CString strMBCS = BuildMBCSInfo(strMSG);
				strFORMAT = strMSG;

				while( szTEXT.cx > szITEM.cx )
				{
					int nLength = strFORMAT.GetLength() - 1;

					strFORMAT.Delete(nLength);
					nLength--;

					if( nLength >= 0 && IS_MBCS_LEAD(strMBCS.GetAt(nLength)) )
						strFORMAT.Delete(nLength);

					m_pSummary->GetTextExtentPoint( LPCTSTR(strFORMAT), szTEXT);
				}

				int nCount = strMSG.GetLength() - strFORMAT.GetLength();
				strFORMAT.TrimLeft(' ');

				if( nCount > 0 )
					strMSG = strMSG.Right(nCount);
				else
					strMSG.Empty();

				m_pSummary->SetItemString( nIndex, 0, strFORMAT);
				m_pSummary->SetUserColor( nIndex, 0, TCOLOR_QTERM_TEXT);
			}

			strMSG = strText.Tokenize( "\n", nPOS);
		}
	}
}

void CTNewQuestDlg::TermMessage( DWORD dwID, CString strText, CString strRESULT, INT nLine, INT& nNumber )
{
	CString strFORMAT;
	CString strMSG;
	INT nPOS = 0;

	CSize szITEM = m_pTerm->GetItemSize(1);
	CSize szTEXT;

	strMSG = strText.Tokenize( "\n", nPOS);
	while(!strMSG.IsEmpty())
	{
		CString strNUMBER;

		strNUMBER = CTChart::Format( TSTR_FMT_TERM, nNumber++);
		int nIndex = m_pTerm->AddString(strNUMBER);
		m_pTerm->SetUserColor(nIndex, 0, TCOLOR_QTERM_TEXT);
		m_pTerm->SetItemDataAllColumn( nIndex, dwID );

		if( strRESULT.GetLength())
		{
			m_pTerm->SetItemString( nIndex, 2, strRESULT);
			m_pTerm->SetUserColor( nIndex, 2, 0xFFFFFF00);
			strRESULT.Empty();
		}

		while(!strMSG.IsEmpty())
		{
			m_pTerm->SetUserColor(nIndex, 1, TCOLOR_QTERM_TEXT);

			m_pTerm->GetTextExtentPoint( LPCTSTR(strMSG), szTEXT);
			CString strMBCS = BuildMBCSInfo(strMSG);
			strFORMAT = strMSG;

			while( szTEXT.cx > szITEM.cx )
			{
				int nLength = strFORMAT.GetLength() - 1;

				strFORMAT.Delete(nLength);
				nLength--;

				if( nLength >= 0 && IS_MBCS_LEAD(strMBCS.GetAt(nLength)) )
					strFORMAT.Delete(nLength);

				m_pTerm->GetTextExtentPoint( LPCTSTR(strFORMAT), szTEXT);
			}

			int nCount = strMSG.GetLength() - strFORMAT.GetLength();
			strFORMAT.TrimLeft(' ');

			if( nCount > 0 )
				strMSG = strMSG.Right(nCount);
			else
				strMSG.Empty();

			m_pTerm->SetItemString( nIndex, 1, strFORMAT);
			m_pTerm->SetUserColor( nIndex, 1, TCOLOR_QTERM_TEXT);

			if(strMSG.GetLength())
				nIndex = m_pTerm->AddString(_T(" "));
		}

		strMSG = strText.Tokenize( "\n", nPOS);
	}
}

void CTNewQuestDlg::TextMessage(CString strTitle, CString strText)
{
	CSize szITEM = m_pContents->GetItemSize(1);
	CSize szTEXT(0,0);

	CString strFORMAT;
	CString strMSG;

	int nPOS = 0;

	if(!strTitle.IsEmpty())
	{
		strTitle.Replace( _T("%s"), m_pHost->GetName());
		INT nIdx = m_pContents->AddString(strTitle);
		m_pContents->SetUserColor(nIdx, 0, TCOLOR_QTERM_TITLE);
	}

	if( CTNationOption::MODIFY_WORD_BREAK )
	{
		CSize szSpaceSize(0,0);
		m_pContents->GetTextExtentPoint( " ", szSpaceSize);

		CString strLINE;
		CSize szLINE(0,0);

		strMSG = strText.Tokenize( " \n", nPOS);
		while(!strMSG.IsEmpty())
		{
			strMSG.Remove('\r');
			strMSG.Replace( "%s", m_pHost->GetName());

			CSize szMSG;
			m_pContents->GetTextExtentPoint( LPCTSTR(strMSG), szMSG);

			if( szMSG.cx+szLINE.cx <= szITEM.cx)
			{
				strLINE += strMSG;
				szLINE.cx += szMSG.cx;
			}
			else
			{
				INT nIndex = m_pContents->AddString(_T(""));

				m_pContents->SetItemString( nIndex, 1, strLINE);
				m_pContents->SetUserColor( nIndex, 1, TCOLOR_QTERM_TEXT);

				szLINE.cx = szMSG.cx;
				strLINE = strMSG;
			}

			BYTE c = strText.GetAt(nPOS - 1); // ������ ���ؼ� Tokenize���߳�.
			if( c == ' ')
			{
				strLINE += ' ';
				szLINE.cx += szSpaceSize.cx;
			}
			else if( c == '\n')
			{
				INT nIndex = m_pContents->AddString(_T(""));

				m_pContents->SetItemString( nIndex, 1, strLINE);
				m_pContents->SetUserColor( nIndex, 1, TCOLOR_QTERM_TEXT);

				strLINE.Empty();
				szLINE.cx = 0;

				m_pContents->AddString(_T(""));
			}

			strMSG = strText.Tokenize( " \n", nPOS);
		}

		if( !strLINE.IsEmpty())
		{
			INT nIndex = m_pContents->AddString(_T(""));

			m_pContents->SetItemString( nIndex, 1, strLINE);
			m_pContents->SetUserColor( nIndex, 1, TCOLOR_QTERM_TEXT);
		}

		m_pContents->AddString(_T(""));
	}
	else
	{
		szITEM.cx -= TMSG_MARGINE;
		strMSG = strText.Tokenize( "\n", nPOS);
		while(!strMSG.IsEmpty())
		{
			strMSG.Remove('\r');
			strMSG.Replace( "%s", m_pHost->GetName());

			while(!strMSG.IsEmpty())
			{
				int nIndex = m_pContents->AddString(_T(" "));
				m_pContents->SetUserColor(1, 0, TCOLOR_QTERM_TEXT);

				m_pContents->GetTextExtentPoint( LPCTSTR(strMSG), szTEXT);
				CString strMBCS = BuildMBCSInfo(strMSG);
				strFORMAT = strMSG;

				while( szTEXT.cx > szITEM.cx )
				{
					int nLength = strFORMAT.GetLength() - 1;

					strFORMAT.Delete(nLength);
					nLength--;

					if( nLength >= 0 && IS_MBCS_LEAD(strMBCS.GetAt(nLength)) )
						strFORMAT.Delete(nLength);

					m_pContents->GetTextExtentPoint( LPCTSTR(strFORMAT), szTEXT);
				}

				int nCount = strMSG.GetLength() - strFORMAT.GetLength();
				strFORMAT.TrimLeft(' ');

				if( nCount > 0 )
					strMSG = strMSG.Right(nCount);
				else
					strMSG.Empty();

				m_pContents->SetItemString( nIndex, 1, strFORMAT);
				m_pContents->SetUserColor( nIndex, 1, TCOLOR_QTERM_TEXT);
			}

			strMSG = strText.Tokenize( "\n", nPOS);
			m_pContents->AddString(_T(" "));
		}
	}
}

void CTNewQuestDlg::TextMessage(DWORD dwTitleID, CString strText)
{
	CString strTitle;
	strTitle = CTChart::LoadString( (TSTRING) dwTitleID);
	TextMessage( strTitle, strText);
}

CString CTNewQuestDlg::GetSpeakerString( CString strSpeaker)
{
	CString strResult(_T(""));

	strSpeaker.TrimRight();
	strSpeaker.TrimLeft();

	if(!strSpeaker.IsEmpty())
		strResult = CTChart::Format( TSTR_FMT_QUEST_SPEEKER, strSpeaker);

	return strResult;
}

CString CTNewQuestDlg::GetResultString(CTClientQuest* pTQUEST)
{
	BYTE bResult = pTQUEST->GetResult();
	CString strRESULT;
	strRESULT.Empty();

	if( bResult != TTERMRESULT_FAILED && bResult != TTERMRESULT_TIMEOUT && pTQUEST->m_bTimmer )
	{
		strRESULT = CTChart::Format( TSTR_FMT_TIMMER, (pTQUEST->m_dwTick % 3600000) / 60000, (pTQUEST->m_dwTick % 60000) / 1000);
		return strRESULT;
	}

	switch(bResult)
	{
	case TTERMRESULT_INCOMPLETE	: strRESULT.Empty(); break; // = CTChart::LoadString( TSTR_QRESULT_INCOMPLETE); break;
	case TTERMRESULT_TIMEOUT	: strRESULT.Empty(); break; // = CTChart::LoadString( TSTR_QRESULT_TIMEOUT); break;
	case TTERMRESULT_FAILED		: strRESULT.Empty(); break; // = CTChart::LoadString( TSTR_QRESULT_FAILED); break;
	case TTERMRESULT_COMPLETE	: strRESULT.Empty(); break; // = CTChart::LoadString( TSTR_QRESULT_COMPLETE); break;
	}

	return strRESULT;
}

DWORD CTNewQuestDlg::GetTQUESTColor(LPTQUEST pTQUEST)
{
	if( pTQUEST->m_bLevel + TQLEVEL_BOUND < m_pHost->m_bLevel )
		return TCOLOR_LIGHTQUEST;
	else if( m_pHost->m_bLevel + TQLEVEL_BOUND < pTQUEST->m_bLevel )
		return TCOLOR_HAVYQUEST;

	return TCOLOR_MIDDLEQUEST;
}

void CTNewQuestDlg::ExpendTree(BYTE bIndex, BYTE bExpend)
{
	int nIndex = m_pQLIST->GetTop() + bIndex;

	if( nIndex >= 0 && nIndex < m_pQLIST->GetItemCount() && !GetTQUEST(nIndex) )
	{
		CTClientQClass* pTQClass = GetQCLASS(nIndex);

		if(pTQClass)
		{
			pTQClass->m_bExpend = bExpend;
			ResetTree();
		}
	}
}

void CTNewQuestDlg::CheckShowRight( BYTE bIndex)
{
	CTClientWnd *pMainWnd = (CTClientWnd *) AfxGetMainWnd();
	int nIndex = m_pQLIST->GetTop() + bIndex;

	if( pMainWnd && nIndex >= 0 && nIndex < m_pQLIST->GetItemCount() && GetTQUEST(nIndex) )
	{
		CTClientQuest *pCQuest = GetCQUEST(nIndex);

		if(pCQuest)
		{
			CTGaugePannel *pTPANNEL = (CTGaugePannel *) pMainWnd->m_MainGame.GetFrame(TFRAME_GAUGE);

			pCQuest->m_bCheckShowRight = m_vTCHECK[bIndex]->GetState() ? TRUE : FALSE;
			if(pTPANNEL)
				pTPANNEL->UpdateQuestINFO(pCQuest);
		}
	}
}
// ----------------------------------------------------------------------------------------------------
void CTNewQuestDlg::ResetTree()
{
	CTClientQClass* pTQClass = NULL;
	LISTTQCLASS vTQCLASS;

	int nCurIndex = m_pQLIST->GetSel();
	if( nCurIndex >= 0 && m_pQuestDlg->m_pTQUEST )
		pTQClass = GetQCLASS(nCurIndex);
	m_pQLIST->RemoveAll();

	MAPTQCLASS::iterator itr = m_pHost->m_mapTQCLASS.begin();
	MAPTQCLASS::iterator end = m_pHost->m_mapTQCLASS.end();

	for(; itr != end; ++itr)
		vTQCLASS.push_back(itr->second);
	vTQCLASS.sort(binary_qclass());

	while(!vTQCLASS.empty())
	{
		CTClientQClass* pTCLASS = vTQCLASS.front();
		INT nIndex = AddQClass(pTCLASS);
		
		if( pTQClass == pTCLASS )
			nCurIndex = nIndex;

		if(pTCLASS->m_bExpend)
		{
			LISTTQUEST vTQUEST;

			MAPTQUEST::iterator itQUEST, endQUEST;
			itQUEST = pTCLASS->m_mapTQUEST.begin();
			endQUEST = pTCLASS->m_mapTQUEST.end();

			for(; itQUEST != endQUEST; ++itQUEST)
				vTQUEST.push_back(itQUEST->second);

			vTQUEST.sort(binary_tquest());

			while(!vTQUEST.empty())
			{
				CTClientQuest* pTQUEST = vTQUEST.front();
				nIndex = AddQuest(pTQUEST->m_pTQUEST, pTQUEST, FALSE);

				if( m_pQuestDlg->m_pTQUEST == pTQUEST->m_pTQUEST )
					nCurIndex = nIndex;
				
				vTQUEST.pop_front();
			}
		}

		vTQCLASS.pop_front();
	}

	nCurIndex = min( m_pQLIST->GetItemCount() - 1, nCurIndex);
	if( nCurIndex >= 0 )
		m_pQLIST->SetCurSelItem(nCurIndex);

	ResetButton();
}
// ----------------------------------------------------------------------------------------------------
void CTNewQuestDlg::ResetButton()
{
	int nCount = m_pQLIST->GetItemCount();
	int nTop = m_pQLIST->GetTop();

	for( INT i=0; i<m_nGBTNCOUNT; ++i )
	{
		int nIndex = nTop + i;
		LPTQUEST pTQUEST = GetTQUEST(nIndex);

		if( nIndex < nCount && !pTQUEST )
		{
			CTClientQClass* pTQClass = GetQCLASS(nIndex);

			m_vTCOLLAPSE[i]->EnableComponent(pTQClass->m_bExpend);
			m_vTCOLLAPSE[i]->ShowComponent(pTQClass->m_bExpend);

			m_vTEXPEND[i]->EnableComponent(!pTQClass->m_bExpend);
			m_vTEXPEND[i]->ShowComponent(!pTQClass->m_bExpend);

			m_vTCHECK[i]->EnableComponent(FALSE);
			m_vTCHECK[i]->ShowComponent(FALSE);
		}
		else
		{
			m_vTCOLLAPSE[i]->EnableComponent(FALSE);
			m_vTCOLLAPSE[i]->ShowComponent(FALSE);

			m_vTEXPEND[i]->EnableComponent(FALSE);
			m_vTEXPEND[i]->ShowComponent(FALSE);

			if( pTQUEST && m_bPrintMSG )
			{
				CTClientQuest* pCQUEST = GetCQUEST(nIndex);

				m_vTCHECK[i]->Select(pCQUEST->m_bCheckShowRight);
				m_vTCHECK[i]->EnableComponent(TRUE);
				m_vTCHECK[i]->ShowComponent(TRUE);
			}
			else
			{
				m_vTCHECK[i]->EnableComponent(FALSE);
				m_vTCHECK[i]->ShowComponent(FALSE);
			}
		}
	}
}
// ====================================================================================================
INT CTNewQuestDlg::AddQuest(LPTQUEST pTQUEST, CTClientQuest* pCQUEST, BOOL bCheckComplete)
{
	LPTQUEST pTMISSION = pTQUEST;
	int nIndex = -1;

	if( bCheckComplete && pTQUEST->m_bType == QT_COMPLETE )
		pTMISSION = CTChart::FindTMISSION(pTQUEST);

	if( m_bPrintMSG )
	{
		nIndex = m_pQLIST->AddItem(pTMISSION->m_strTITLE, (DWORD)pCQUEST, COL_ITEM);
		m_pQLIST->SetItemDataAllColumn( nIndex, (DWORD)pCQUEST );
	}
	else
	{
		nIndex = m_pQLIST->AddItem(pTMISSION->m_strTITLE, (DWORD)pTQUEST, COL_ITEM);
		m_pQLIST->SetItemDataAllColumn( nIndex, (DWORD)pTQUEST );
	}

	if( !pCQUEST )
		pCQUEST = m_pHost->FindTQuest(pTMISSION->m_dwID);

	if( pCQUEST )
		m_pQLIST->SetItemString(nIndex, COL_STATE, m_pQuestDlg->GetResultString(pCQUEST));

	if( pTQUEST->m_dwMinLevel || pTQUEST->m_dwMaxLevel )
	{
		DWORD dwMin = max(pTQUEST->m_dwMinLevel, 1);
		
		CString strLEVEL;
		if( pTQUEST->m_dwMaxLevel )
			strLEVEL = CTChart::Format( TSTR_FMT_QUESTLEVEL_LIM, dwMin, pTQUEST->m_dwMaxLevel);
		else
			strLEVEL = CTChart::Format( TSTR_FMT_QUESTLEVEL, dwMin);

		m_pQLIST->SetItemString(nIndex, COL_LEVEL, strLEVEL);
	}

	DWORD dwTCLR = m_pQuestDlg->GetTQUESTColor(pTMISSION);

	m_pQLIST->SetUserColor(nIndex, COL_ITEM, dwTCLR);
	m_pQLIST->SetUserColor(nIndex, COL_LEVEL, dwTCLR);
	m_pQLIST->SetUserColor(nIndex, COL_STATE, dwTCLR);

	return nIndex;
}
// ----------------------------------------------------------------------------------------------------
INT CTNewQuestDlg::AddQClass(CTClientQClass* pQCLASS)
{
	int nIndex = m_pQLIST->AddItem(pQCLASS->m_pTQCLASS->m_strNAME, NULL, COL_CATEGORY);
	m_pQLIST->SetItemDataAllColumn( nIndex, NULL );
	m_pQLIST->SetItemData( nIndex, COL_CATEGORY, (DWORD)pQCLASS);

	//CString strCount;
	//strCount = CTChart::Format( TSTR_FMT_COUNT, INT(pQCLASS->m_mapTQUEST.size()));
	//m_pQLIST->SetItemString(nIndex, COL_STATE, strCount);

	m_pQLIST->SetUserColor(nIndex, COL_CATEGORY, TCOLOR_QUESTCLASS);
	m_pQLIST->SetUserColor(nIndex, COL_STATE, TCOLOR_QUESTCLASS);

	return nIndex;
}
// ----------------------------------------------------------------------------------------------------
void CTNewQuestDlg::SetQuestState(INT nIdx, LPTQUEST pTQUEST)
{
	CTClientQuest *pTQuest = m_pHost->FindTQuest(pTQUEST->m_dwID);

	if( pTQuest && pTQuest->m_bTimmer )
	{
		m_pQLIST->SetItemString(nIdx, COL_STATE, m_pQuestDlg->GetResultString(pTQuest));

		CTClientWnd *pMainWnd = (CTClientWnd *) AfxGetMainWnd();
		CTGaugePannel *pTPANNEL = (CTGaugePannel *) pMainWnd->m_MainGame.GetFrame(TFRAME_GAUGE);
		pTPANNEL->UpdateQuestINFO( pTQuest );
	}
}
// ====================================================================================================
LPTQUEST CTNewQuestDlg::GetTQUEST(INT nIdx)
{
	DWORD dwDATA = m_pQLIST->GetItemData(nIdx, COL_ITEM);

	if( dwDATA != (DWORD)-1 )
	{
		if( m_bPrintMSG )
		{
			CTClientQuest* pCQUEST = (CTClientQuest*) dwDATA;

			if( pCQUEST )
				return pCQUEST->m_pTQUEST;
		}
		else
		{
			return (LPTQUEST) dwDATA;
		}	
	}

	return NULL;
}

CTClientQuest* CTNewQuestDlg::GetCQUEST(INT nIdx)
{
	DWORD dwDATA = m_pQLIST->GetItemData(nIdx, COL_ITEM);

	if( dwDATA != (DWORD)-1 )
		return (CTClientQuest*) dwDATA;
	else
		return NULL;
}
// ----------------------------------------------------------------------------------------------------
CTClientQClass* CTNewQuestDlg::GetQCLASS(INT nIdx)
{
	DWORD dwDATA = m_pQLIST->GetItemData(nIdx, COL_CATEGORY);
	if( dwDATA != (DWORD)-1 )
		return (CTClientQClass*)(dwDATA);
	else
		return NULL;
}

BOOL CTNewQuestDlg::DoMouseWheel( UINT nFlags, short zDelta, CPoint pt)
{
	return CTClientUIBase::DoMouseWheel( nFlags, zDelta, pt);
}

void CTNewQuestDlg::OnQuestMapOpen()
{
	m_bHideMap = FALSE;

	if ( m_bVisible )
	{
		m_pMapOpen->ShowComponent( FALSE );
		m_pMapFrame->ShowComponent( TRUE );
		m_pMapClose->ShowComponent( TRUE );
	}
}

void CTNewQuestDlg::OnQuestMapClose()
{
	m_bHideMap = TRUE;

	if ( m_bVisible )
	{
		m_pMapOpen->ShowComponent( TRUE );
		m_pMapFrame->ShowComponent( FALSE );
		m_pMapClose->ShowComponent( FALSE );
	}
}

void CTNewQuestDlg::GetUnitPosition(FLOAT fPosX, FLOAT fPosY, INT& outUnitX, INT& outUnitY)
{
	FLOAT fLength = ((FLOAT) m_pTMAP->m_pMAP->m_nUnitLength * m_pTMAP->m_pMAP->m_nTileLength);

	outUnitX = INT(fPosX / fLength);
	outUnitY = INT(fPosY / fLength);
}

void CTNewQuestDlg::ResetMap( LPTTERM pTerm )
{
	m_bRenderMap = FALSE;

	for ( int i = 0; i < m_pTQUEST->m_vTTERMPOS.size(); ++i )
	{
		LPTTERMPOS pTERMPOS = m_pTQUEST->m_vTTERMPOS[i];

		if ( (pTerm->m_bType == QTT_COMPQUEST && pTERMPOS->m_bType == QTT_TCOMP_POS) ||  
			(pTERMPOS->m_bType == pTerm->m_bType &&	pTERMPOS->m_dwID == pTerm->m_dwID) )
		{
			INT nUnitX, nUnitZ;
			GetUnitPosition(pTERMPOS->m_fPosX, pTERMPOS->m_fPosZ, nUnitX,	nUnitZ );
			DWORD dwUNITID = MakeUnitID(pTERMPOS->m_dwMapID, (BYTE)nUnitX, (BYTE)nUnitZ);
			m_ptMapIcon = D3DXVECTOR3( pTERMPOS->m_fPosX, pTERMPOS->m_fPosY, pTERMPOS->m_fPosZ );
			m_vTCENTER.x = pTERMPOS->m_fPosX;
			m_vTCENTER.y = pTERMPOS->m_fPosZ;
			MAPTMINIMAP::iterator finder = CTChart::m_mapTMINIMAP.find(	dwUNITID );

			m_bRenderMap = TRUE;

			if( finder != CTChart::m_mapTMINIMAP.end() )
			{
				LPTMINIMAP temp = (*finder).second;
				m_pMapImageList->SetCurImage((*finder).second->m_bWorldID);
				break;
			}
		}


	}
}

void CTNewQuestDlg::ResetMap( LPTQUEST pTQUEST )
{
	LPTQUEST pTMISSION = pTQUEST;
	BOOL bFindInCompleteQuest = FALSE;

	m_bRenderMap = FALSE;

	if ( pTQUEST && pTQUEST->m_bType == QT_COMPLETE )
	{
		pTMISSION = CTChart::FindTMISSION(m_pTQUEST);
	}

	if ( pTQUEST )
	{

		m_bRenderMap = TRUE;

		m_pMapImageList->ShowComponent(TRUE);
		m_pMapQuestIcon->ShowComponent(TRUE);

		CTClientQuest *pTQuest = m_pHost->FindTQuest(pTQUEST->m_dwID);

		if( pTQuest )
		{
			//////////////////////////////////////////////////////////////////////////
			// Find InCompleted Quest.
			for( int i=0; i<INT(pTMISSION->m_vTTERM.size()); i++)
			{
				CTClientTerm *pTTERM = pTQuest->FindTTerm( pTMISSION->m_vTTERM[i] );

				if( pTTERM && pTTERM->GetResult() == TTERMRESULT_INCOMPLETE )
				{
					for( int j=0; j<INT(pTMISSION->m_vTTERMPOS.size()); j++)
					{
						LPTTERMPOS pTERMPOS = m_pTQUEST->m_vTTERMPOS[j];

						if( pTMISSION->m_vTTERMPOS[j]->m_bType == pTTERM->m_pTTERM->m_bType &&
							pTMISSION->m_vTTERMPOS[j]->m_dwID == pTTERM->m_pTTERM->m_dwID )
						{
							INT nUnitX, nUnitZ;
							GetUnitPosition(pTERMPOS->m_fPosX, pTERMPOS->m_fPosZ, nUnitX,	nUnitZ );
							DWORD dwUNITID = MakeUnitID(pTERMPOS->m_dwMapID, (BYTE)nUnitX, (BYTE)nUnitZ);
							m_ptMapIcon = D3DXVECTOR3( pTERMPOS->m_fPosX, pTERMPOS->m_fPosY, pTERMPOS->m_fPosZ );
							m_vTCENTER.x = pTERMPOS->m_fPosX;
							m_vTCENTER.y = pTERMPOS->m_fPosZ;

							bFindInCompleteQuest = TRUE;

							MAPTMINIMAP::iterator finder = CTChart::m_mapTMINIMAP.find(	dwUNITID );

							if( finder != CTChart::m_mapTMINIMAP.end() )
							{
								LPTMINIMAP temp = (*finder).second;
								m_pMapImageList->SetCurImage((*finder).second->m_bWorldID);
								break;
							} // if
							break;
						} // if
					} // for j
				} // if
			} // for i
		} // if pTQuest
		else 
		{
			for ( int i = 0; i < pTMISSION->m_vTTERM.size(); ++i )
			{
				LPTTERM pTTERM = pTMISSION->m_vTTERM[i];

				for( int j=0; j<INT(pTMISSION->m_vTTERMPOS.size()); j++)
				{
					LPTTERMPOS pTERMPOS = pTMISSION->m_vTTERMPOS[j];

					if( pTMISSION->m_vTTERMPOS[j]->m_bType == pTTERM->m_bType &&
						pTMISSION->m_vTTERMPOS[j]->m_dwID == pTTERM->m_dwID )
					{
						INT nUnitX, nUnitZ;
						GetUnitPosition(pTERMPOS->m_fPosX, pTERMPOS->m_fPosZ, nUnitX,	nUnitZ );
						DWORD dwUNITID = MakeUnitID(pTERMPOS->m_dwMapID, (BYTE)nUnitX, (BYTE)nUnitZ);
						m_ptMapIcon = D3DXVECTOR3( pTERMPOS->m_fPosX, pTERMPOS->m_fPosY, pTERMPOS->m_fPosZ );
						m_vTCENTER.x = pTERMPOS->m_fPosX;
						m_vTCENTER.y = pTERMPOS->m_fPosZ;

						bFindInCompleteQuest = TRUE;

						MAPTMINIMAP::iterator finder = CTChart::m_mapTMINIMAP.find(	dwUNITID );

						if( finder != CTChart::m_mapTMINIMAP.end() )
						{
							LPTMINIMAP temp = (*finder).second;
							m_pMapImageList->SetCurImage((*finder).second->m_bWorldID);
							break;
						} // if
						break;
					} // if
				}
			}	
		}

		//////////////////////////////////////////////////////////////////////////
		// All Quest Completed.
		if ( !bFindInCompleteQuest )
		{
			for( int i=0; i<INT(pTMISSION->m_vTTERMPOS.size()); i++)
			{
				LPTTERMPOS pTERMPOS = pTMISSION->m_vTTERMPOS[i];

				if ( pTERMPOS->m_bType == QTT_TCOMP_POS )
				{
					INT nUnitX, nUnitZ;
					GetUnitPosition(pTERMPOS->m_fPosX, pTERMPOS->m_fPosZ, nUnitX,	nUnitZ );
					DWORD dwUNITID = MakeUnitID(pTERMPOS->m_dwMapID, (BYTE)nUnitX, (BYTE)nUnitZ);
					m_ptMapIcon = D3DXVECTOR3( pTERMPOS->m_fPosX, pTERMPOS->m_fPosY, pTERMPOS->m_fPosZ );
					m_vTCENTER.x = pTERMPOS->m_fPosX;
					m_vTCENTER.y = pTERMPOS->m_fPosZ;

					bFindInCompleteQuest = TRUE;

					MAPTMINIMAP::iterator finder = CTChart::m_mapTMINIMAP.find(	dwUNITID );

					if( finder != CTChart::m_mapTMINIMAP.end() )
					{
						LPTMINIMAP temp = (*finder).second;
						m_pMapImageList->SetCurImage((*finder).second->m_bWorldID);
						break;
					} // if
					break;
				} // if
			} // for
		} // if
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		m_pMapImageList->ShowComponent(FALSE);
		m_pMapQuestIcon->ShowComponent(FALSE);
	}
}

void CTNewQuestDlg::ResetMap( LPTQUEST pTQUEST, LPTTERM pTerm, DWORD idx )
{
	LPTQUEST pTMISSION = pTQUEST;
	BOOL bFindInCompleteQuest = FALSE;

	m_bRenderMap = FALSE;

	if ( pTQUEST && pTQUEST->m_bType == QT_COMPLETE )
	{
		pTMISSION = CTChart::FindTMISSION(m_pTQUEST);
	}

	if ( pTQUEST )
	{
		for ( int i = 0; i < pTMISSION->m_vTTERMPOS.size(); ++i )
		{
			LPTTERMPOS pTERMPOS = pTMISSION->m_vTTERMPOS[i];

			if ( (pTerm && pTerm->m_bType == QTT_COMPQUEST && pTERMPOS->m_bType == QTT_TCOMP_POS) ||  
				(pTerm && pTERMPOS->m_bType == pTerm->m_bType && pTERMPOS->m_dwID == pTerm->m_dwID) ||
				(pTERMPOS->m_dwID == idx) )
			{
				INT nUnitX, nUnitZ;
				GetUnitPosition(pTERMPOS->m_fPosX, pTERMPOS->m_fPosZ, nUnitX,	nUnitZ );
				DWORD dwUNITID = MakeUnitID(pTERMPOS->m_dwMapID, (BYTE)nUnitX, (BYTE)nUnitZ);
				m_ptMapIcon = D3DXVECTOR3( pTERMPOS->m_fPosX, pTERMPOS->m_fPosY, pTERMPOS->m_fPosZ );
				m_vTCENTER.x = pTERMPOS->m_fPosX;
				m_vTCENTER.y = pTERMPOS->m_fPosZ;
				MAPTMINIMAP::iterator finder = CTChart::m_mapTMINIMAP.find(	dwUNITID );
				BOOL bFindInCompleteQuest = TRUE;
				m_bRenderMap = TRUE;


				if( finder != CTChart::m_mapTMINIMAP.end() )
				{
					LPTMINIMAP temp = (*finder).second;
					m_pMapImageList->SetCurImage((*finder).second->m_bWorldID);
					break;
				}
			}
		}
	}
}

void CTNewQuestDlg::RenderMap( DWORD dwTickCount )
{
	if( m_pBACKBUF2 == NULL )
	{
		D3DXCreateTexture(
			m_pDevice->m_pDevice,
			m_pDevice->m_vPRESENT.BackBufferWidth,
			m_pDevice->m_vPRESENT.BackBufferHeight, 1,
			D3DUSAGE_RENDERTARGET,
			m_pDevice->m_vPRESENT.BackBufferFormat,
			D3DPOOL_DEFAULT,
			&m_pBACKTEX2);

		if( !m_pBACKTEX2 )
			return ;

		m_pBACKTEX2->GetSurfaceLevel( 0, &m_pBACKBUF2);
	}

	SIZE szFRAME;
	m_pMap->GetComponentSize( &szFRAME );


	CRect rtBack;
	m_pMap->GetComponentRect(&rtBack);
	m_pMap->ComponentToScreen( &rtBack );

	FLOAT fLength = ((FLOAT) m_pTMAP->m_pMAP->m_nUnitLength * m_pTMAP->m_pMAP->m_nTileLength);
	FLOAT fMinX = (szFRAME.cx / 2.0f) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));// fLength / (2.0f * m_fTSCALE);
	FLOAT fMaxX = ((TWORLDMAP_SIZE - szFRAME.cx) + (szFRAME.cx / 2.0f)) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));
	FLOAT fMinZ = (szFRAME.cy / 2.0f) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));
	FLOAT fMaxZ = ((TWORLDMAP_SIZE - szFRAME.cy) + (szFRAME.cy / 2.0f)) * fLength / (m_fTSCALE * FLOAT(TWORLDMAP_SIZE));

	//
	int nUnitX, nUnitZ, nMainUnitX, nMainUnitZ;

	GetUnitPosition(m_vTCENTER.x,m_vTCENTER.y, nUnitX,nUnitZ);
	GetUnitPosition(m_ptMapIcon.x, m_ptMapIcon.z, nMainUnitX,nMainUnitZ);

	fMinX += FLOAT(nUnitX) * fLength;
	fMaxX += FLOAT(nUnitX) * fLength;
	fMinZ += FLOAT(nUnitZ) * fLength;
	fMaxZ += FLOAT(nUnitZ) * fLength;

	m_vTCENTER.x = min( max( m_vTCENTER.x, fMinX), fMaxX);
	m_vTCENTER.y = min( max( m_vTCENTER.y, fMinZ), fMaxZ);

	int nPosX = INT((FLOAT(nUnitX) * fLength + fLength / 2.0f - m_vTCENTER.x) * TWORLDMAP_SIZE / fLength) + INT( szFRAME.cx - TWORLDMAP_SIZE) / 2;
	int nPosZ = INT((FLOAT(nUnitZ) * fLength + fLength / 2.0f - m_vTCENTER.y) * TWORLDMAP_SIZE / fLength) - INT( szFRAME.cy - TWORLDMAP_SIZE) / 2;

	CTClientCAM vCAMERA;
	D3DXMATRIX vWorld;

	D3DXMatrixScaling(
		&vWorld,
		m_fTSCALE,
		m_fTSCALE,
		m_fTSCALE);

	vCAMERA.InitOrthoCamera( 
		m_pDevice->m_pDevice,
		-1.0f,
		1.0f,
		1.0f,
		1.0f );

	vCAMERA.SetPosition(
		D3DXVECTOR3( 0.0f, 0.5f, 0.0f),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
		D3DXVECTOR3( 0.0f, 0.0f, 1.0f),
		FALSE);
	vCAMERA.Activate(TRUE);

	m_pDevice->m_pDevice->SetRenderTarget( 0, m_pDevice->m_pBACKBUF);

	m_pDevice->m_pDevice->Clear(
		0, NULL,
		D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB( 0, 0, 0, 0),
		1.0f, 0);


	m_pMapImageList->MoveComponent( CPoint( nPosX , -nPosZ ));
	if ( m_bRenderMap )
		m_pMapImageList->Render(dwTickCount);
	vCAMERA.Activate(TRUE);

	m_pDevice->m_pDevice->SetRenderTarget( 0, m_pBACKBUF2);

	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pDevice->m_pDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pDevice->m_pDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE);

	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	m_pDevice->m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE);
	m_pDevice->m_pDevice->SetRenderState( D3DRS_ZENABLE, FALSE);

	m_pDevice->m_pDevice->SetStreamSource( 0, m_pDevice->m_pBACKVB, 0, sizeof(PVERTEX));
	m_pDevice->m_pDevice->SetTexture( 0, m_pDevice->m_pBACKTEX);

	m_pDevice->m_pDevice->SetTransform( D3DTS_WORLD, &vWorld);
	m_pDevice->m_pDevice->SetFVF(T3DFVF_PVERTEX);
	m_pDevice->m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);


	CRect rect( rtBack.left, rtBack.top, rtBack.left + m_pDevice->m_option.m_dwScreenX, rtBack.top + m_pDevice->m_option.m_dwScreenY);

	TNLVERTEX vRECT[4] = {
		{ FLOAT(rect.left)+0.5f, FLOAT(rect.top)+0.5f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f},
		{ FLOAT(rect.right)+0.5f, FLOAT(rect.top)+0.5f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f},
		{ FLOAT(rect.left)+0.5f, FLOAT(rect.bottom)+0.5f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f},
		{ FLOAT(rect.right)+0.5f, FLOAT(rect.bottom)+0.5f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f}
	};

	m_pDevice->m_pDevice->SetRenderTarget( 0, m_pDevice->m_pRTARGET);

	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	m_pDevice->m_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pDevice->m_pDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pDevice->m_pDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE);

	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pDevice->m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	m_pDevice->m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE);
	m_pDevice->m_pDevice->SetRenderState( D3DRS_ZENABLE, FALSE);
	m_pDevice->m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);

	m_pDevice->m_pDevice->SetTexture( 0, m_pBACKTEX2);
	m_pDevice->m_pDevice->SetFVF(T3DFVF_TNLVERTEX);

	D3DVIEWPORT9 vVIEW;
	m_pDevice->m_pDevice->GetViewport(&vVIEW);

	D3DVIEWPORT9 vCULLRECT;
	vCULLRECT.X = (DWORD) (rtBack.left > 0 ? rtBack.left + 1 : 1);
	vCULLRECT.Y = (DWORD) (rtBack.top > 0 ? rtBack.top + 1 : 1);
	vCULLRECT.Width = (DWORD) rtBack.Width() - (rtBack.left > 0 ? 0 : abs(rtBack.left));
	vCULLRECT.Height = (DWORD) rtBack.Height() - (rtBack.top > 0 ? 0 : abs(rtBack.top));
	vCULLRECT.MinZ = 0.0f;
	vCULLRECT.MaxZ = 1.0f;


	if( vVIEW.Y + vVIEW.Height < vCULLRECT.Y + vCULLRECT.Height )
		vCULLRECT.Height = vVIEW.Y + vVIEW.Height - vCULLRECT.Y;

	if( vVIEW.X + vVIEW.Width < vCULLRECT.X + vCULLRECT.Width )
		vCULLRECT.Width = vVIEW.X + vVIEW.Width - vCULLRECT.X;
	m_pDevice->m_pDevice->SetViewport(&vCULLRECT);

	m_pDevice->m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2, vRECT, sizeof(TNLVERTEX));

	m_pDevice->m_pDevice->SetViewport(&vVIEW);
	m_pCAM->Activate(TRUE);
}

void CTNewQuestDlg::RederMapPos( DWORD dwTickCount )
{

	D3DVIEWPORT9 vVIEW;
	m_pDevice->m_pDevice->GetViewport(&vVIEW);

	CRect rtBack;
	m_pMap->GetComponentRect(&rtBack);
	m_pMap->ComponentToScreen(&rtBack);

	D3DVIEWPORT9 vRECT;
	vRECT.X = (DWORD)( rtBack.left > 0 ? rtBack.left : 0  );
	vRECT.Y = (DWORD)( rtBack.top > 0 ? rtBack.top : 0 );
	vRECT.Width = (DWORD)( rtBack.Width() - (rtBack.left > 0 ? 0 : abs(rtBack.left)) );
	vRECT.Height = (DWORD)( rtBack.Height() - (rtBack.top > 0 ? 0 : abs(rtBack.top)) );
	vRECT.MinZ = 0.0f;
	vRECT.MaxZ = 1.0f;
	

	CRect rect(
		0, 0,
		m_pDevice->m_option.m_dwScreenX,
		m_pDevice->m_option.m_dwScreenY);

	CSize size;
	CPoint pt;
	D3DXVECTOR3 vPOS;

	m_pMapQuestIcon->GetComponentSize(&size);
	rect.InflateRect(size);

	vPOS = m_ptMapIcon;

	CPoint point = GetPosition(vPOS.x,vPOS.z, size.cx,size.cy);

	if(rect.PtInRect(point))
	{
		m_pMapQuestIcon->MoveComponent(point);
		m_pMapQuestIcon->Render(dwTickCount);
	}

	m_pDevice->m_pDevice->SetViewport(&vVIEW);
	CD3DImage::m_bUseGlobalClipRect = FALSE;

}

DWORD CTNewQuestDlg::MakeUnitID(WORD wMapID, BYTE nUnitX, BYTE nUnitY)
{
	return MAKELONG( MAKEWORD(nUnitX,nUnitY), wMapID );
}

LPTTERM CTNewQuestDlg::GetSelTerm()
{
	INT nTop = m_pTerm->GetTop();
	INT nSel = m_pTerm->GetSel();
	INT idx = nSel;

	if( m_pTQUEST && idx >= 0 )
		if( idx < m_pTQUEST->m_vTTERM.size() )
			return m_pTQUEST->m_vTTERM[idx];

	return NULL;
}

DWORD CTNewQuestDlg::GetSelTermID()
{
	INT nTop = m_pTerm->GetTop();
	INT nSel = m_pTerm->GetSel();
	INT idx = m_pTerm->GetItemData( nSel, 0 );

	return idx;
}

CPoint CTNewQuestDlg::GetPosition( FLOAT fPosX,
								  FLOAT fPosZ,
								  int nWidth,
								  int nHeight)
{
	FLOAT fSCALE = ((FLOAT) m_pTMAP->m_pMAP->m_nUnitLength * m_pTMAP->m_pMAP->m_nTileLength) / m_fTSCALE;

	CRect rtFRAME;
	m_pMap->GetComponentRect( &rtFRAME );
	m_pMap->ComponentToScreen( &rtFRAME );

	CPoint vRESULT(
		(rtFRAME.Width() / 2) + rtFRAME.left,
		(rtFRAME.Height() / 2) + rtFRAME.top);

	fPosX -= m_vTCENTER.x;
	fPosZ -= m_vTCENTER.y;

	vRESULT.x += INT(fPosX * FLOAT(TWORLDMAP_SIZE) / fSCALE);
	vRESULT.y -= INT(fPosZ * FLOAT(TWORLDMAP_SIZE) / fSCALE);

	vRESULT.x -= nWidth / 2;
	vRESULT.y -= nHeight / 2;

	return vRESULT;
}