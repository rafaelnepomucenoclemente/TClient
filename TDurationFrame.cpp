#include "Stdafx.h"
#include "TDurationFrame.h"
#include "TClientGame.h"
#include "TClientWnd.h"
#include "Resource.h"

// ===============================================================================
CTDurationFrame::CTDurationFrame( TComponent *pParent, LP_FRAMEDESC pDesc)
:	CTClientUIBase(pParent,pDesc)
{
	static const DWORD dwEQUIPCOMP[] = 
	{
		ID_CTRLINST_MAIN_WEAPON,	//ES_PRMWEAPON
		ID_CTRLINST_SUB_WEAPON,		//ES_SNDWEAPON,
		ID_CTRLINST_LONG_WEAPON,	//ES_LONGWEAPON,
		ID_CTRLINST_HELMET,			//ES_HEAD,
		NULL,						//ES_BACK,
		ID_CTRLINST_BODY,			//ES_BODY,
		ID_CTRLINST_PANT,			//ES_PANTS,
		ID_CTRLINST_SHOES,			//ES_FOOT,
		ID_CTRLINST_GLOVE,			//ES_HAND,
		NULL,						//ES_NECK,
		NULL,						//ES_LFINGER,
		NULL,						//ES_RFINGER,
		NULL,						//ES_LEAR,
		NULL,						//ES_REAR,
		NULL,						//ES_FACE,
		NULL,						//ES_COSTUME_HAT,
		NULL,						//ES_COSTUME_DRESS,
		NULL,						//ES_COSTUME_ACCESSARY,
		NULL,						//ES_COSTUME_RACE
	};

	for(int i=0; i<ES_COUNT; ++i)
	{
		m_vEquip[i] = static_cast<TImageList*>( FindKid(dwEQUIPCOMP[i]) );
		if( m_vEquip[i] )
			m_vEquip[i]->SetPixelHitTest( TRUE );
	}

	m_pInfo = FindKid(ID_CTRLINST_TXT);
	
	Init();
}
// -------------------------------------------------------------------------------
CTDurationFrame::~CTDurationFrame()
{
}
// ===============================================================================

// ===============================================================================
void CTDurationFrame::Init()
{
	ShowComponent(TRUE);

	for(int i=0; i<ES_COUNT; ++i)
	{
		if(m_vEquip[i])
			m_vEquip[i]->SetCurImage(DAMAGE_NORMAL);
	}

	m_pInfo->ShowComponent(FALSE);
	m_bSND = FALSE;
}
// -------------------------------------------------------------------------------
void CTDurationFrame::Update()
{
	BOOL bExistDuration = FALSE; // ����̰ų� �������� ���Ⱑ ���� ��쿡�� ����ϱ� ���ؼ�.

	// �ϴ� ��� �������� �ʱ�ȭ
	for(BYTE i=0; i<ES_COUNT; ++i)
	{
		if( m_vEquip[i] )
		{
			m_vEquip[i]->SetCurImage(DAMAGE_NORMAL);
			m_vEquip[i]->ShowComponent(TRUE);
		}
	}

	for(BYTE i=0; i<ES_COUNT; ++i)
	{
		if( m_vEquip[i] )
		{
			DWORD dwPercent = -1;

			if( GetDurationPercent(i, dwPercent) )
			{
				if( dwPercent > 50 )
					m_vEquip[i]->SetCurImage( DAMAGE_NORMAL); // 50%�ʰ�
				else if( 30 < dwPercent && dwPercent <= 50 )
					m_vEquip[i]->SetCurImage( DAMAGE_YELLOW); // 30%�ʰ� ~50%����
				else if( dwPercent <= 30 )
					m_vEquip[i]->SetCurImage( DAMAGE_RED); // 30%����

				if( dwPercent <= 50 ) // 50% �̸��� �Ѱ� �̻� ���� ��쿡�� ����� �Ѵ�.
					bExistDuration = TRUE;
			}
			else
			{
				// ����� ���Ⱑ ���ų� dwPercent�� 0�� ��츸 �´�.

				if( dwPercent == 0 ) // ������.
				{
					m_vEquip[i]->SetCurImage(DAMAGE_BREAK);
					bExistDuration = TRUE; // ������ �Ѱ� �̻��� ��쿡�� ����Ѵ�.
				}
			}
		}
	}

	ShowComponent( bExistDuration );
}
// ===============================================================================

// ===============================================================================
BOOL CTDurationFrame::GetDurationPercent(BYTE bSlot, DWORD& outPrecent)
{
	CTClientChar* pMainChar = CTClientGame::GetInstance()->GetMainChar();
	CTClientInven* pTInven = pMainChar->FindTInven(INVEN_EQUIP);

	CTClientItem* pTItem = pTInven->FindTItem(bSlot);
	if( pTItem )
	{
		if( pTItem->GetDuraMax() && 
			pTItem->GetDuraMax() > pTItem->GetDuraCurrent() )
		{
			if( pTItem->GetDuraCurrent() == 0 )
			{
				outPrecent = 0;
				return FALSE;
			}
			else
			{
				outPrecent = pTItem->GetDuraCurrent() * 100 / pTItem->GetDuraMax();
				return TRUE;
			}
		}
		else
		{
			outPrecent = 100;
			return TRUE;
		}
	}

	return FALSE;
}
// ===============================================================================

// ===============================================================================
BOOL CTDurationFrame::HitTest( CPoint pt )
{
	return FALSE;
}
// -------------------------------------------------------------------------------
HRESULT CTDurationFrame::Render( DWORD dwTickCount )
{
	m_pInfo->ShowComponent(FALSE);

	CPoint point;
	GetCursorPos(&point);
	CTClientWnd::GetInstance()->ScreenToClient(&point);

	if( CTClientUIBase::HitTest(point) )
	{
		for(BYTE i=0; i<ES_COUNT; ++i)
		{
			if( m_vEquip[i] && 
				m_vEquip[i]->IsVisible() &&
				m_vEquip[i]->HitTest(point) )
			{
				DWORD dwPercent;
				if( GetDurationPercent(i, dwPercent) )
				{
					m_pInfo->m_strText = CTChart::Format( TSTR_FMT_NUMPERCENT, dwPercent);
					m_pInfo->ShowComponent(TRUE);

					m_pInfo->ScreenToComponent(&point);
					CSize size;
					m_pInfo->GetComponentSize(&size);
					point.x -= (size.cx / 2);
					point.y -= size.cy;

					m_pInfo->MoveComponent(point);
				}
				break;
			}
		}
	}

	return CTClientUIBase::Render(dwTickCount);
}
// ===============================================================================


























