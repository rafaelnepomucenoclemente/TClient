#include "stdafx.h"
#include "TItemExtPeriodDlg.h"
#include "Resource.h"
#include "TClientGame.h"

// ====================================================================================================
CTItemExtPeriodDlg::CTItemExtPeriodDlg(TComponent* pParent, LP_FRAMEDESC pDesc)
:	CTItemSlotBaseDlg(pParent, pDesc, SLOT_COUNT)
{
	m_pSlotCtrl[TARGET_SLOT] = static_cast<TImageList*>( FindKid(ID_CTRLINST_ITEM) );

	TButton* pBTN = (TButton*) FindKid(ID_CTRLINST_OK);

	if( pBTN )
		pBTN->m_menu[TNM_LCLICK] = GM_EXTEND_ITEM_PERIOD;

	ClearItem();
	ShowComponent(FALSE);
}
// ----------------------------------------------------------------------------------------------------
CTItemExtPeriodDlg::~CTItemExtPeriodDlg()
{
}
// ====================================================================================================

// ====================================================================================================
// �� �޼ҵ�� �������� ���Կ� �ø��� ��ȿ�� �������ΰ��� �Ǻ����ִ� �޼ҵ��̴�.
BOOL CTItemExtPeriodDlg::CheckItem(BYTE bSlotID, CTClientItem* pClientItem) const
{
	LPTITEM pItem = pClientItem->GetTITEM();

	// �Ⱓ������ ������ �ʴ� �������� �ɷ����� ��... �̷� ���ǹ� ������ ���� ó���Ѵ�.
	// ��� ������ �����ۿ� ����� ����
	/*if( pClientItem->CanGamble() )
	{
		m_strLastError = CTChart::LoadString( TSTR_ITEM_ERR_GAMBLE);
			return FALSE;
	}*/

	/*if( pClientItem->GetRefineMax() == 0 )
	{
		m_strLastError = CTChart::LoadString( TSTR_ITRF_ERR_CANNOTREFINE);
		return FALSE;
	}*/

	switch( bSlotID ) // ���Ժ� ������ ���� �˻�
	{
	case TARGET_SLOT	:
		if( pClientItem->GetEndTime() == 0 )
		{
			m_strLastError = CTChart::LoadString( TSTR_ISNT_EXTPERIOD_ITEM);
			return FALSE;
		}
		break;
	}
	return TRUE;
}