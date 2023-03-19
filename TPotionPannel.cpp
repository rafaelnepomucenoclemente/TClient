#include "StdAfx.h"
#include "Resource.h"
#include "TClientGame.h"
#include "TPotionPannel.h"
#define ID_MAINTAIN_1 (0x00006847)
#define ID_MAINTAIN_2 (0x00006848)
#define ID_MAINTAIN_3 (0x00006849)
#define ID_MAINTAIN_4 (0x0000684A)
#define ID_MAINTAIN_5 (0x0000684B)
#define ID_MAINTAIN_6 (0x0000684C)
#define ID_MAINTAIN_7 (0x0000684D)
#define ID_MAINTAIN_8 (0x0000684E)
#define ID_MAINTAIN_9 (0x0000684F)
#define ID_MAINTAIN_10 (0x00006850)
#define ID_MAINTAIN_TIME_1 (0x00006851)
#define ID_MAINTAIN_TIME_2 (0x00006852)
#define ID_MAINTAIN_TIME_3 (0x00006853)
#define ID_MAINTAIN_TIME_4 (0x00006854)
#define ID_MAINTAIN_TIME_5 (0x00006855)
#define ID_MAINTAIN_TIME_6 (0x00006856)
#define ID_MAINTAIN_TIME_7 (0x00006857)
#define ID_MAINTAIN_TIME_8 (0x00006858)
#define ID_MAINTAIN_TIME_9 (0x00006859)
#define ID_MAINTAIN_TIME_10 (0x0000685A)
CTPotionPannel::CTPotionPannel( TComponent *pParent, LP_FRAMEDESC pDesc)
:CTClientUIBase( pParent, pDesc)
{
	static DWORD dwIconID[10] =
	{
		
			ID_MAINTAIN_1,
			ID_MAINTAIN_2,
			ID_MAINTAIN_3,
			ID_MAINTAIN_4,
			ID_MAINTAIN_5,
			ID_MAINTAIN_6,
			ID_MAINTAIN_7,
			ID_MAINTAIN_8,
			ID_MAINTAIN_9,
			ID_MAINTAIN_10
	};


	static DWORD dwTextID[10] =
	{
		
			ID_MAINTAIN_TIME_1,
			ID_MAINTAIN_TIME_2,
			ID_MAINTAIN_TIME_3,
			ID_MAINTAIN_TIME_4,
			ID_MAINTAIN_TIME_5,
			ID_MAINTAIN_TIME_6,
			ID_MAINTAIN_TIME_7,
			ID_MAINTAIN_TIME_8,
			ID_MAINTAIN_TIME_9,
			ID_MAINTAIN_TIME_10
	};


		m_bCount = 0;

		for( BYTE j=0; j<10; j++)
		{
			m_pMAINTAIN_ICON[j] = (TImageList *) FindKid(dwIconID[j]);
			m_pMAINTAIN_TIME[j] = (TComponent*) FindKid(dwTextID[j]);
	
			if(m_pMAINTAIN_ICON[j])
			{
				m_pMAINTAIN_ICON[j]->EnableComponent(TRUE);
				m_pMAINTAIN_ICON[j]->ShowComponent(TRUE);
				m_pMAINTAIN_ICON[j]->SetCurImage(0);
			}

		//	if( m_pMAINTAIN_TIME[j])
		//		m_pMAINTAIN_TIME[j]->m_strText = "31";

			m_vMAINTAININFO_TSKILL[j] = NULL;
			m_vMAINTAININFO_LEVEL[j] = 0;
		//	m_pMAINTAIN_ICON[j]->SetCurImage(11);
		}
	

	m_bSND = FALSE;

	m_pOBJ = NULL;
}

CTPotionPannel::~CTPotionPannel()
{
}
bool SortCancel( CTClientMaintain* p1, CTClientMaintain* p2 )
{
	if( p1->m_pTSKILL && p2->m_pTSKILL )
	{
		BOOL bPremium1 = IsPREMIUMMaintain(p1);
		BOOL bPremium2 = IsPREMIUMMaintain(p2);

		if( bPremium1 && bPremium2 )
			return true;
		else if( bPremium1 || bPremium2 )
		{
			if( bPremium1 )
				return true;
			else
				return false;
		}
		else
		{
			if( p2->m_pTSKILL->m_bCanCancel && !p1->m_pTSKILL->m_bCanCancel)
				return false;
		}
	}

	return true;
}

void CTPotionPannel::ResetPOTIONS( CTClientObjBase* pOBJ, DWORD dwTick)
{
	HideAll();

	m_pOBJ = pOBJ;

	LPMAPTMAINTAIN pTMAINTAIN = pOBJ->GetTMAINTAIN();
	VTMAINTAIN vTMAINTAIN;
	VTMAINTAIN vTPRotation;
	VTMAINTAIN vTNRotation;

	{
		MAPTMAINTAIN::iterator itMAINTAIN;
		for( itMAINTAIN = pTMAINTAIN->begin(); itMAINTAIN != pTMAINTAIN->end(); itMAINTAIN++)
			vTMAINTAIN.push_back( itMAINTAIN->second );

		std::sort( vTMAINTAIN.begin(), vTMAINTAIN.end(), SortCancel);
	}



	VTMAINTAIN::iterator itMAINTAIN;

	for( int i=0; i<vTMAINTAIN.size(); ++ i )
	{
		CTClientMaintain *pTSKILL = vTMAINTAIN[i];

		

		if( pTSKILL && pTSKILL->m_pTSKILL && pTSKILL->m_pTSKILL->m_bShowIcon )
		{
			
			BYTE bTMCNT = m_bCount;
			TImageList* pTIMGLIST = m_pMAINTAIN_ICON[bTMCNT];
			TComponent* pTTIME = m_pMAINTAIN_TIME[bTMCNT];

			if( bTMCNT < 10 && pTIMGLIST )
			{
				if(pTSKILL->GetLeftTick(dwTick) < 10)
				{
					pTTIME->m_strText = CTClientGame::ToTimeOneString(pTSKILL->GetLeftTick(dwTick));
					pTTIME->ShowComponent(TRUE);
				}
				else
				{
					pTTIME->m_strText.Empty();
					pTTIME->ShowComponent(FALSE);
				}

				if( pTSKILL->m_pTSKILL->m_wIconID != 0 )
				{
					pTIMGLIST->SetCurImage(pTSKILL->m_pTSKILL->m_wIconID);
					pTIMGLIST->ShowComponent(TRUE);
				}
				else
					pTIMGLIST->ShowComponent(FALSE);

				// Detail 정보창을 생성하기 위한 기반 정보
				m_vMAINTAININFO_TSKILL[ bTMCNT ] = pTSKILL->m_pTSKILL;
				m_vMAINTAININFO_LEVEL[ bTMCNT ] = pTSKILL->m_bLevel;
			}

			++m_bCount;
		}
	}

//	ResetROTATION(dwTick);

	
		for( BYTE j=m_bCount ; j<10; ++j)
		{
			if( m_pMAINTAIN_ICON[j] )
				m_pMAINTAIN_ICON[j]->ShowComponent(FALSE);
			if( m_pMAINTAIN_TIME[j] )
				m_pMAINTAIN_TIME[j]->ShowComponent(FALSE);
		}
	
}

void CTPotionPannel::HideAll()
{


		for( BYTE j=0; j<10; ++j)
			if(m_pMAINTAIN_ICON[j])
			{
				m_pMAINTAIN_TIME[j]->m_strText.Empty();
				m_pMAINTAIN_TIME[j]->ShowComponent(FALSE);
				
				m_pMAINTAIN_ICON[j]->SetCurImage(0);
				m_pMAINTAIN_ICON[j]->ShowComponent(FALSE);

				m_vMAINTAININFO_TSKILL[j] = NULL;
				m_vMAINTAININFO_LEVEL[j] = 0;
			}
}
HRESULT CTPotionPannel::Render(DWORD dwTickCount)
{

	CPoint pt = CTClientUIBase::m_vBasis[TBASISPOINT_CENTER_BOTTOM];
	pt.x -= 350;
	pt.y -= 176;
	MoveComponent(pt);
	return CTClientUIBase::Render(dwTickCount);
}
ITDetailInfoPtr CTPotionPannel::GetTInfoKey( const CPoint& point )
{
	ITDetailInfoPtr pInfo(NULL);


		for( BYTE j=0; j<10; ++j)
		{
			if(m_pMAINTAIN_ICON[j] &&
				m_pMAINTAIN_ICON[j]->HitTest(point) )
			{
				CRect rc;
				m_pMAINTAIN_ICON[j]->GetComponentRect(&rc);
				m_pMAINTAIN_ICON[j]->ComponentToScreen(&rc);

				pInfo = CTDetailInfoManager::NewSkillInst( 
					m_vMAINTAININFO_TSKILL[j],
					m_vMAINTAININFO_LEVEL[j],
					FALSE,
					rc);

				pInfo->SetDir(TRUE, FALSE, TRUE);
				return pInfo;
			}
		}
	

	return pInfo;
}
BOOL CTPotionPannel::HitTest( CPoint pt)
{


		for( BYTE j=0; j<10; j++)
			if( m_pMAINTAIN_ICON[j] &&
				m_pMAINTAIN_ICON[j]->HitTest(pt) )
				return TRUE;


	return FALSE;
}
void CTPotionPannel::AddMaintain(BYTE index, BYTE m_bIcon, DWORD dwTick, CTClientMaintain* pSkill, CTClientObjBase* pChar)
{
	    ShowComponent(TRUE);
	   CString debug;
	      debug.Format("%d",dwTick);
	


		m_vMAINTAININFO_TSKILL[ index ] = pSkill->m_pTSKILL;
		m_vMAINTAININFO_LEVEL[ index ] = pSkill->m_bLevel;

		for(BYTE i=m_bCount;i<10; i++)
		{

		m_pMAINTAIN_ICON[i]->ShowComponent(FALSE);
		m_pMAINTAIN_TIME[i]->ShowComponent(FALSE);
		}

		if(pSkill && pSkill->m_pTSKILL->m_bPremIconID != 0 && m_vMAINTAININFO_TSKILL[index]->m_bPremIconID != 0 )
		{
			
		m_pMAINTAIN_TIME[index]->m_strText = debug;
		m_pMAINTAIN_ICON[index]->SetCurImage(m_bIcon);
		m_pMAINTAIN_TIME[index]->ShowComponent(TRUE);
		m_pMAINTAIN_ICON[index]->ShowComponent(TRUE);

		if(dwTick == 0)
		{
		//	m_pMAINTAIN_TIME[index]->m_strText.Empty();
		//	m_pMAINTAIN_TIME[index]->ShowComponent(FALSE);
		}
	

	}
		else
		{
			m_pMAINTAIN_ICON[index]->SetCurImage(-1);
			m_pMAINTAIN_TIME[index]->m_strText.Empty();
			m_pMAINTAIN_TIME[index]->ShowComponent(FALSE);
			m_pMAINTAIN_ICON[index]->ShowComponent(FALSE);
		}
}
void CTPotionPannel::SetNewChar(CTClientObjBase* m_pMainChar)
{
	m_pMainCh = m_pMainChar;
}