#include "StdAfx.h"
#include "TUIBar.h"
#include "TClientGame.h"
#define ID_BUTTON_EX (0x000065D7)
#define ID_BUTTON_N1 (0x000065CF)
#define ID_BUTTON_N2 (0x000065D0)
#define ID_BUTTON_N3 (0x000065D1)
#define ID_BUTTON_N4 (0x000065D2)
#define ID_BUTTON_N5 (0x000065D3)
#define ID_BUTTON_N6 (0x000065D4)
#define ID_BUTTON_N7 (0x000065D5)
#define ID_BUTTON_N8 (0x000065D6)
#define ID_BUTTON_N9 (0x0000680F)
#define ID_IMAGE_USELESS (0x0000680E)


CTUIBarDlg::CTUIBarDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
	: CTClientUIBase(pParent, pDesc)
{

	static DWORD dwHiden[9] =
	{
    ID_BUTTON_N1,
	ID_BUTTON_N2,
	ID_BUTTON_N3,
	ID_BUTTON_N4,
	ID_BUTTON_N5,
	ID_BUTTON_N6,
	ID_BUTTON_N7,
	ID_BUTTON_N8,
	ID_BUTTON_N9
	};

	for(int i =0;i<9;++i) // i++ = 10% swag, ++i = 150% swag
	m_pButIdx[i] = static_cast<TButton*>(FindKid(dwHiden[i]));

	m_pButEx = static_cast<TButton*>(FindKid(ID_BUTTON_EX));

}

CTUIBarDlg::~CTUIBarDlg()
{

}
HRESULT CTUIBarDlg::Render(DWORD dwTickCount)
{
	if(bShownAll && bShownFade)
	ShowComponent(TRUE);
	else
    ShowComponent(FALSE);

	TComponent* m_pUseless = FindKid(ID_IMAGE_USELESS);
	m_pUseless->ShowComponent(FALSE);
	if(!bShownBar)
	{
		for(int i=0;i<9;i++)
			m_pButIdx[i]->ShowComponent(FALSE);
	}
	else
	{
		for(int i=0;i<9;i++)
			m_pButIdx[i]->ShowComponent(TRUE);
	}

	



	CPoint pt = CTClientUIBase::m_vBasis[TBASISPOINT_CENTER_TOP];
	pt.x -= 105;
	pt.y += 32;
	MoveComponent(pt);
	return CTClientUIBase::Render(dwTickCount);
}
BOOL CTUIBarDlg::CanWithItemUI()
{
	return TRUE;
}