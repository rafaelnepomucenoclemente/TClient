#include "StdAfx.h"
#include "TClientGame.h"
#include "Resource.h"

// ====================================================================================================
CTDetailInfoDlg::CTDetailInfoDlg( TComponent *pParent, LP_FRAMEDESC pDesc)
:	CTClientUIBase( pParent, pDesc)
{
	static const DWORD dwIconID[TDETAILINFO_ICON_COUNT] =
	{
		ID_CTRLINST_ITEM,
		ID_CTRLINST_SKILL,
		ID_CTRLINST_FACE
	};
	
	static const DWORD dwGemID_1 = ID_CTRLINST_GEM1;
	static const DWORD dwGemID_2 = ID_CTRLINST_GEM2;
	static const DWORD dwGemID_3 = ID_CTRLINST_GEM3;
	static const DWORD dwGemID_4 = ID_CTRLINST_GEM4;
	static const DWORD dwGemID_5 = ID_CTRLINST_GEM5;


	static WORD nNewCnt = 0;
	m_id = MAKELONG(m_id, ++nNewCnt);

	for( BYTE i=0; i<TDETAILINFO_ICON_COUNT; i++)
		m_vICON[i] = static_cast<TImageList*>( FindKid(dwIconID[i]) );

	m_pGEM_1 = static_cast<TImageList*>( FindKid(dwGemID_1) );
	m_pGEM_2 = static_cast<TImageList*>( FindKid(dwGemID_2) );
	m_pGEM_3 = static_cast<TImageList*>( FindKid(dwGemID_3) );
	m_pGEM_4 = static_cast<TImageList*>( FindKid(dwGemID_4) );
	m_pGEM_5 = static_cast<TImageList*>( FindKid(dwGemID_5) );
	RemoveKid(m_pGEM_1);
	RemoveKid(m_pGEM_2);
	RemoveKid(m_pGEM_3);
	RemoveKid(m_pGEM_4);
	RemoveKid(m_pGEM_5);
	CPoint pt;

	m_vICON[0]->GetComponentPos(&pt);
	m_nTitlePosX_NIC = pt.x;

	m_pTEXT = FindKid(ID_CTRLINST_TEXT);
	RemoveKid(m_pTEXT);

	m_pNAME = FindKid(ID_CTRLINST_NAME);
	m_pNAME->GetComponentPos(&pt);
	m_nTitlePosY = pt.y;
	m_nTitlePosX_NOR = pt.x;

	m_pSTART = FindKid(ID_CTRLINST_START);
	m_pEND = FindKid(ID_CTRLINST_END);
	m_pBACK = FindKid(ID_CTRLINST_BACK);

	/*m_pGEM_1->ShowComponent(FALSE);
	m_pGEM_2->ShowComponent(FALSE);
	m_pGEM_3->ShowComponent(FALSE);
	m_pGEM_4->ShowComponent(FALSE);
	m_pGEM_5->ShowComponent(FALSE);*/




	CRect rt;
	m_pSTART->GetComponentRect( &rt );
	m_ptUNTITLESTART.x = rt.left;
	m_ptUNTITLESTART.y = rt.bottom;
	m_pTEXT->GetComponentRect( &rt );
	m_ptTITLESTART.x = rt.left;
	m_ptTITLESTART.y = rt.top;
	m_ptTextStart = m_ptTITLESTART;
	m_pTEXT->GetComponentSize( &m_vTEXTSIZE );

	m_vTEXT.clear();
	ClearText();

	m_pCLOSE = FindKid(ID_CTRLINST_INFO_CLOSE);
	ShowCloseButton(FALSE);

    m_pNAMEFONT = m_pNAME->Get3DFont();
	m_bSND = FALSE;
}
// ----------------------------------------------------------------------------------------------------
CTDetailInfoDlg::~CTDetailInfoDlg()
{
	if( m_pTEXT )
	{
		delete m_pTEXT;
		m_pTEXT = NULL;
	}

	ClearText();
}
// ====================================================================================================
void CTDetailInfoDlg::ResetINFO(ITDetailInfoPtr pInfo)
{
	ClearText();

	pInfo->Build();
	INT nOutlookStyle = pInfo->GetOutlookStyle();

	switch( nOutlookStyle )
	{
	case TDETINFO_OUTLOOK_STYLE_TITLE:
		{
			m_pBACK->ShowComponent(TRUE);
			m_ptTextStart = m_ptTITLESTART;
			m_bNoHIT = FALSE;
		}
		break;
	case TDETINFO_OUTLOOK_STYLE_UNTITLE:
		{
			m_pBACK->ShowComponent(FALSE);
			m_ptTextStart = m_ptUNTITLESTART;
			m_bNoHIT = TRUE;
		}
		break;
	}

	CSize szTEXT;
	CString strFORMAT;

	CSize szITEM( m_vTEXTSIZE );
	szITEM.cx -= 2 * TINFOTEXT_MARGINE;

	UINT nLineCnt = pInfo->GetLineCount();
	for(UINT i=0; i<nLineCnt; ++i)
	{
		CString strLINE = pInfo->GetLineText(i);
		DWORD dwCOLOR = pInfo->GetLineColor(i);

		VECTORSTRING vLines;

		RECT rtRC;
		m_pTEXT->GetComponentRect( &rtRC );
		m_pTEXT->SeparateTextFitSize( strLINE, rtRC.right-rtRC.left-10, vLines);

		for( INT i=0 ; i < vLines.size() ; ++i )
			AddText( vLines[i], dwCOLOR );
	}

	BYTE bIconID = GetIconID(pInfo);
	WORD wImageID = pInfo->GetImageID();


	CPoint vPos( m_ptTextStart );
	vPos.y += m_vTEXT.size() * m_vTEXTSIZE.cy;
	m_pEND->MoveComponent( vPos );

	BOOL bShowIcon = FALSE;
	for( INT i=0; i<TDETAILINFO_ICON_COUNT; ++i )
	{
		if( nOutlookStyle == TDETINFO_OUTLOOK_STYLE_UNTITLE )
		{
			m_vICON[i]->ShowComponent(wImageID);
			continue;
		}

		if( bIconID == i )
		{
			INT nSkinIndex = pInfo->CheckUsingSkin();
			if( T_INVALID == nSkinIndex  )
				m_vICON[i]->SetSkinImageEmpty();
			else
				m_vICON[i]->SetSkinImage( nSkinIndex );

			m_vICON[i]->SetCurImage(wImageID);
			m_vICON[i]->ShowComponent(TRUE);
			bShowIcon = TRUE;
		}
		else
			m_vICON[i]->ShowComponent(FALSE);
	}

	/*BYTE bGem = 0;
	BOOL bIfGem = 0;


	if(bIconID == 0)
	{
		bGem = pInfo->GetGem();
		bIfGem = pInfo->IfGem();
	}
		
	

	if(bIconID == 0 && bIfGem)
	{
		if(bGem == 0)
		{
			m_pGEM_1->SetCurImage(0);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(0);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			m_pGEM_5->ShowComponent(TRUE);
		}

		else if(bGem == 1)
		{
			m_pGEM_1->SetCurImage(2);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(0);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			m_pGEM_5->ShowComponent(TRUE);
		}

		else if(bGem == 2)
		{
			m_pGEM_1->SetCurImage(2);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			m_pGEM_5->ShowComponent(TRUE);
		}

		else if(bGem == 3)
		{
			m_pGEM_1->SetCurImage(2);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			m_pGEM_5->ShowComponent(TRUE);
		}

		else if(bGem == 4)
		{
			m_pGEM_1->SetCurImage(2);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(2);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			m_pGEM_5->ShowComponent(TRUE);
		}

		else if(bGem == 5)
		{
			m_pGEM_1->SetCurImage(2);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(2);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(2);
			m_pGEM_5->ShowComponent(TRUE);
		}


	}
	else
	{
	m_pGEM_1->ShowComponent(FALSE);
	m_pGEM_2->ShowComponent(FALSE);
	m_pGEM_3->ShowComponent(FALSE);
	m_pGEM_4->ShowComponent(FALSE);
	m_pGEM_5->ShowComponent(FALSE);
	}*/

	if(pInfo->GetType() == TDEFINFO_TYPE_GEM_0)
	{
			m_pGEM_1->SetCurImage(0);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(0);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_0_W)
	{
			m_pGEM_1->SetCurImage(0);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(0);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_1)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(0);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_1_W)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(0);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_2)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_2_W)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(0);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_3)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_3_W)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(0);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_4)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(2);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_4_W)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(2);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(0);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_5)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(2);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(2);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else if(pInfo->GetType() == TDEFINFO_TYPE_GEM_5_W)
	{
			m_pGEM_1->SetCurImage(2);
			AddKid(m_pGEM_1);
			m_pGEM_1->ShowComponent(TRUE);

			m_pGEM_2->SetCurImage(2);
			AddKid(m_pGEM_2);
			m_pGEM_2->ShowComponent(TRUE);

			m_pGEM_3->SetCurImage(2);
			AddKid(m_pGEM_3);
			m_pGEM_3->ShowComponent(TRUE);

			m_pGEM_4->SetCurImage(2);
			AddKid(m_pGEM_4);
			m_pGEM_4->ShowComponent(TRUE);

			m_pGEM_5->SetCurImage(2);
			AddKid(m_pGEM_5);
			m_pGEM_5->ShowComponent(TRUE);
	}
	else
	{
		m_pGEM_1->ShowComponent(FALSE);
		m_pGEM_2->ShowComponent(FALSE);
		m_pGEM_3->ShowComponent(FALSE);
		m_pGEM_4->ShowComponent(FALSE);
		m_pGEM_5->ShowComponent(FALSE);

	}

	//AddKid(m_pGEM_1);




	if( bShowIcon )
		m_pNAME->MoveComponent( CPoint(m_nTitlePosX_NOR, m_nTitlePosY) );
	else
		m_pNAME->MoveComponent( CPoint(m_nTitlePosX_NIC, m_nTitlePosY) );

	m_pNAME->m_strText = pInfo->GetTitleText();
	m_pNAMEFONT->m_dwColor = pInfo->GetTitleColor();
}
// ----------------------------------------------------------------------------------------------------
void CTDetailInfoDlg::ShowCloseButton(BOOL bShow)
{
	m_pCLOSE->ShowComponent(bShow);
}
// ====================================================================================================
void CTDetailInfoDlg::ShowGemStone(BYTE bGem)
{
	m_pGEM_1->SetCurImage(2);
	m_pGEM_1->ShowComponent(TRUE);
}
// ====================================================================================================
BOOL CTDetailInfoDlg::CanWithItemUI()
{
	return TRUE;
}
// ----------------------------------------------------------------------------------------------------
void CTDetailInfoDlg::ShowComponent( BOOL bVisible)
{
	m_bVisible = bVisible;
}
// ----------------------------------------------------------------------------------------------------
void CTDetailInfoDlg::GetComponentRect( LPRECT lpRect)
{
	*lpRect = m_rc;

	if(m_pEND)
	{
		CRect rect;

		m_pEND->GetComponentRect(&rect);
		lpRect->bottom = lpRect->top + rect.bottom;
	}
}
// ====================================================================================================
void CTDetailInfoDlg::AddText(const CString& strTEXT, DWORD dwColor)
{
	TComponent* pTEXT = new TComponent(this, m_pTEXT->m_pDESC);
	int nCount = INT(m_vTEXT.size());

	pTEXT->m_id = MAKELONG(WORD(m_id), WORD(nCount+1));
	pTEXT->m_strText = strTEXT;

	CD3DFont* pFont = pTEXT->Get3DFont();
	if( pFont )
		pFont->m_dwColor = dwColor;

	CRect rect;
	rect.left = m_ptTextStart.x;
	rect.top = m_ptTextStart.y + (nCount*m_vTEXTSIZE.cy);
	rect.right = rect.left + m_vTEXTSIZE.cx;
	rect.bottom = rect.top + m_vTEXTSIZE.cy;
	pTEXT->SetComponentRect(&rect);
	pTEXT->m_bWordBreak = FALSE;

	m_vTEXT.push_back(pTEXT);
	AddKid(pTEXT);
}
// ----------------------------------------------------------------------------------------------------
void CTDetailInfoDlg::ClearText()
{
	m_pNAME->m_strText.Empty();

	while(!m_vTEXT.empty())
	{
		RemoveKid(m_vTEXT.back());
		delete m_vTEXT.back();

		m_vTEXT.pop_back();
	}

	m_blDragging = FALSE;
	m_pFocus = NULL;

	m_ptPrev = CPoint( 0, 0);
	m_tip.Reset();
}
// ----------------------------------------------------------------------------------------------------
BYTE CTDetailInfoDlg::GetIconID( ITDetailInfoPtr pInfo)
{

	switch( pInfo->GetType() )
	{
	case TDETINFO_TYPE_ITEM:
	case TDEFINFO_TYPE_INSTITEM:
	case TDEFINFO_TYPE_GEM_0:
	case TDEFINFO_TYPE_GEM_1:
	case TDEFINFO_TYPE_GEM_2:
	case TDEFINFO_TYPE_GEM_3:
	case TDEFINFO_TYPE_GEM_4:
	case TDEFINFO_TYPE_GEM_5:
	case TDEFINFO_TYPE_GEM_0_W:
	case TDEFINFO_TYPE_GEM_1_W:
	case TDEFINFO_TYPE_GEM_2_W:
	case TDEFINFO_TYPE_GEM_3_W:
	case TDEFINFO_TYPE_GEM_4_W:
	case TDEFINFO_TYPE_GEM_5_W:
	case TDETINFO_TYPE_SEALEDITEM:
	case TDETINFO_TYPE_OPTIONITEM:
		return TDETAILINFO_ICON_ITEM;

	case TDETINFO_TYPE_SKILL:
		return TDETAILINFO_ICON_SKILL;

	case TDETINFO_TYPE_PLAYER:
		return TDETAILINFO_ICON_FACE;
	}

	return TDETAILINFO_ICON_NONE;
}
// ====================================================================================================
ITDetailInfoPtr CTDetailInfoDlg::GetTInfoKey( const CPoint& point )
{
	return ITDetailInfoPtr(); //return CTDetailInfoManager::m_pLastInfo;
}

void CTDetailInfoDlg::OnLButtonDown(UINT nFlags, CPoint pt)
{
	CTDetailInfoManager::m_dwInfoStaticTick = 0;
	CTClientUIBase::OnLButtonDown(nFlags, pt);
}