#pragma once


class CTVeteranDlg : public CTClientUIBase
{

public:
	TList*		m_pList;
	TList*		m_pList2;
	TList*		m_pList3;

	TComponent	*m_pSelectedTitle;

	TComponent	*m_pFocus;
	TComponent	*m_pDescription;
	TComponent	*m_pCheck;

	/*CPoint		m_ptCheckBoxOffset;
	CPoint		m_ptBasePointCategory;*/

	TButton*	m_pBtn;
	//TButton*	m_pCheckBox;

	BOOL		m_bNeedResetPos;

public:
	virtual void AddLists();
	virtual void ClearLists();
	virtual void AddTitles(DWORD dwGold, DWORD dwTitleID);
	virtual void AddStringL1(CString strRequirement, CString strTitle, WORD wTitleID);
	virtual void ResetPos();

public:
	virtual void OnLButtonDown( UINT nFlags, CPoint pt );
	virtual void SwitchFocus(TComponent *pCandidate);
	virtual HRESULT Render( DWORD dwTickCount );

public:
	CTVeteranDlg( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTVeteranDlg();
};