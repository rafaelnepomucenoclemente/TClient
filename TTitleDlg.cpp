#include "stdafx.h"
#include "TTitleDlg.h"
#include "TClientGame.h"

CTTitleDlg::CTTitleDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{
m_pList = static_cast<TList*>( FindKid(ID_CTRLINST_TITLE_LIST9) );
	m_pList2 = static_cast<TList*>( FindKid(ID_CTRLINST_TITLE_LIST6) );
	m_pList3 = static_cast<TList*>( FindKid(ID_CTRLINST_TITLE_LIST14) );
	m_pBtn = static_cast<TButton *>(FindKid(ID_CTRLINST_TITLE_LIST13));

	m_pSelectedTitle = FindKid(ID_CTRLINST_TITLE_LIST2); // CUSTOM
	m_pCheck = FindKid( ID_CTRLINST_CHECKBOX );
	m_pDescription = FindKid(ID_CTRLINST_TITLE_LIST10);

	m_pList2->m_menu[TNM_LCLICK] = GM_SELECT_TITLE;

	//m_pList = Titel-Liste
	//m_pList2 = Titel in Besitz
	//m_pList3 = Kategorien-Liste

	RemoveKid(m_pCheck);

	//m_pList2->AddString(CString(), 1);
}

CTTitleDlg::~CTTitleDlg()
{	
}

void CTTitleDlg::OnLButtonDown( UINT nFlags, CPoint pt )
{
	if(!m_pList3->HitTest(pt) && !m_pBtn->HitTest(pt))
		m_pList3->ShowComponent(FALSE);

	m_pBtn->SetPushButton();

	if( m_pBtn->HitTest(pt) )
	{
		if(m_pList3->m_bVisible == FALSE)
			m_pList3->ShowComponent(TRUE);
		else
			m_pList3->ShowComponent(FALSE);
	}

	if(m_pList3->HitTest(pt))
	{
		TListItem* pHITITEM = m_pList3->GetHitItem( pt );

		if( pHITITEM && pHITITEM != NULL)
		{
			MAPTTITLEGROUPTEMP::iterator itTTITLEGROUP;
			MAPTTITLETEMP::iterator itTTITLE;

			m_pList->RemoveAll();

			DWORD dwID = m_pList3->GetHitItemData(pt);

			for( itTTITLE = CTChart::m_mapTTITLETEMP.begin(); itTTITLE != CTChart::m_mapTTITLETEMP.end(); itTTITLE++)
			{
				if((*itTTITLE).second->m_bKind == dwID || dwID == NULL)
				{
					AddStringL1((*itTTITLE).second->m_strRequirement, (*itTTITLE).second->m_strTitle, (*itTTITLE).second->m_wTitleID);
							
					LPTTITLEGROUP pTitleGroup = CTChart::FindTTITLEGROUPTEMP(dwID);
					m_pBtn->m_strText = pTitleGroup->m_strCaption;
				}
			}
			m_pList3->ShowComponent(FALSE);
		}
	}

	//CUSTOM
	if(m_pList2->HitTest(pt))
	{
		TListItem* pHITITEM = m_pList2->GetHitItem( pt );

		if( pHITITEM && pHITITEM != NULL)
		{
			DWORD dwID = m_pList2->GetHitItemData(pt);
			LPTTITLE pTitle = CTChart::FindTTITLETEMP(dwID);

			CTClientGame* pGame = CTClientGame::GetInstance();
			CTClientChar* pTCHAR = pGame->GetMainChar();

			m_pSelectedTitle->m_strText = pTitle->m_strTitle;

			pTCHAR->ResetCharTitle();

			if( pTitle )
			{
				if( pTitle->m_wTitleID != 0 && pTitle->m_wTitleID != pTCHAR->m_wCharTitleID )
					pTCHAR->SetCharTitle( pTitle->m_wTitleID);
			}
		}
	}
	//END

	if(m_pList->HitTest(pt))
	{
		TListItem* pHITITEM = m_pList->GetHitItem( pt );

		if( pHITITEM && pHITITEM != NULL)
		{
			DWORD dwID = m_pList->GetHitItemData(pt);
			LPTTITLE pTitle = CTChart::FindTTITLETEMP(dwID);

			if ( pTitle )
				m_pDescription->m_strText = pTitle->m_strDescription;
		}
	}

	CTClientUIBase::OnLButtonDown(nFlags, pt);
}

void CTTitleDlg::SwitchFocus(TComponent *pCandidate)
{
	if( m_pFocus == pCandidate )
		return;

	if( m_pFocus )
		m_pFocus->SetFocus(FALSE);

	if( pCandidate )
		pCandidate->SetFocus(TRUE);

	m_pFocus = pCandidate;
}

HRESULT CTTitleDlg::Render( DWORD dwTickCount )
{
	if( IsVisible() )
		return CTClientUIBase::Render( dwTickCount );

	return S_OK;
}

void CTTitleDlg::AddLists()
{
	ClearLists();
	m_pDescription->m_strText.Empty();
	m_pSelectedTitle->m_strText.Empty(); //CUSTOM
	m_pList3->ShowComponent(FALSE);

	MAPTTITLETEMP::iterator itTTITLE;
	MAPTTITLEGROUPTEMP::iterator itTTITLEGROUP;

	for( itTTITLE = CTChart::m_mapTTITLETEMP.begin(); itTTITLE != CTChart::m_mapTTITLETEMP.end(); itTTITLE++)
	{
		int nLine = m_pList->AddString((*itTTITLE).second->m_strTitle, 1);

		m_pList->SetItemString(nLine, 2, (*itTTITLE).second->m_strRequirement);
		m_pList->SetItemData(nLine, 1, (*itTTITLE).second->m_wTitleID);
		m_pList->SetItemData(nLine, 2, (*itTTITLE).second->m_wTitleID);
	}

	CTClientChar* pTCHAR = CTClientGame::GetInstance()->GetMainChar();

	//CUSTOM
	WORD wTitleID = pTCHAR->m_wCharTitleID;

	LPTTITLE pTitle = CTChart::FindTTITLETEMP(wTitleID);

	m_pSelectedTitle->m_strText = pTitle->m_strTitle;
	//END

	for( itTTITLEGROUP = CTChart::m_mapTTITLEGROUPTEMP.begin(); itTTITLEGROUP != CTChart::m_mapTTITLEGROUPTEMP.end(); itTTITLEGROUP++)
	{
		if((*itTTITLEGROUP).second->m_bID == 0)
			m_pBtn->m_strText = (*itTTITLEGROUP).second->m_strCaption;

		int nLine = m_pList3->AddString((*itTTITLEGROUP).second->m_strCaption);
		m_pList3->SetItemData(nLine, 0, (*itTTITLEGROUP).second->m_bID);
	}

	m_bNeedResetPos = TRUE;
}

void CTTitleDlg::ClearLists()
{
	m_pList->RemoveAll();
	//m_pList2->RemoveAll();
	m_pList3->RemoveAll();
}

void CTTitleDlg::AddStringL1(CString strRequirement, CString strTitle, WORD wTitleID)
{
	int nLine = m_pList->AddString(strTitle, 1);

	m_pList->SetItemString(nLine, 2, strRequirement);
	m_pList->SetItemData(nLine, 1, wTitleID);
	m_pList->SetItemData(nLine, 2, wTitleID);
}

void CTTitleDlg::ResetPos()
{
	m_bNeedResetPos = FALSE;
}
