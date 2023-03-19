#include "stdafx.h"
#include "TVeteran.h"
#include "TClientGame.h"

CTVeteranDlg::CTVeteranDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{
	
	//CPoint ptCheckBox, ptCategory;
	
	//m_pCheck->GetComponentPos(&ptCheckBox);
	//m_pList->GetComponentPos(&ptCategory);

	//m_ptBasePointCategory = ptCategory;

	//m_ptCheckBoxOffset = ptCheckBox + ptCategory;
}

CTVeteranDlg::~CTVeteranDlg()
{	
}

void CTVeteranDlg::OnLButtonDown( UINT nFlags, CPoint pt )
{
	
}

void CTVeteranDlg::SwitchFocus(TComponent *pCandidate)
{

}

HRESULT CTVeteranDlg::Render( DWORD dwTickCount )
{
	if( IsVisible() )
	{
		/*m_bNeedResetPos = TRUE;
		if(m_bNeedResetPos)
			ResetPos();

		m_bNeedResetPos = FALSE;*/

		return CTClientUIBase::Render( dwTickCount );
	}

	return S_OK;
}

void CTVeteranDlg::AddLists()
{
	

		
	
		
	
	//CUSTOM
	

}
void CTVeteranDlg::AddTitles(DWORD dwGold, DWORD dwTitleID)
{
}
void CTVeteranDlg::ClearLists()
{

}

void CTVeteranDlg::AddStringL1(CString strRequirement, CString strTitle, WORD wTitleID)
{

}

void CTVeteranDlg::ResetPos()
{

}
