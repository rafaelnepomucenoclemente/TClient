#pragma once


class CTHotStartDlg : public CTClientUIBase
{

public:
TImageList* m_pHot1;
TImageList* m_pHot2;
TImageList* m_pHot3;
TImageList* m_pHot4;
TImageList* m_pHot5;
TImageList* m_pHot6;
TImageList* m_pHot7;
TButton* m_pHotBut1;
TButton* m_pHotBut2;
TButton* m_pHotBut3;
TButton* m_pHotBut4;
TScroll* m_pListx;
TButton* m_pList2;
TButton* m_pList3;
TButton* m_pHotBut5;
TButton* m_pHotBut6;
TButton* m_pHotBut7;
TComponent* m_pHotName1;
TComponent* m_pHotName2;
TComponent* m_pHotName3;
TComponent* m_pHotName4;
TComponent* m_pHotName5;
TComponent* m_pHotName6;

TComponent* m_pTitle;
TComponent* m_pHotName7;

BYTE bSettings;
BYTE bCabinet;
BYTE bChar;
BYTE bPost;
BYTE bWar;
BYTE bCom;
BYTE bEnabled;
	/*CPoint		m_ptCheckBoxOffset;
	CPoint		m_ptBasePointCategory;*/

	TButton*	m_pBtn;
	//TButton*	m_pCheckBox;

	BOOL		m_bNeedResetPos;

public:


	virtual void EnableSettings();
	virtual void EnableCabinet();
	virtual void EnableChar();
	virtual void EnablePost();
	virtual HRESULT Render(DWORD dwTickCount);

	virtual void EnableWar();
	virtual void EnableComm();
	virtual BOOL	CanWithItemUI();
public:
	//	virtual void OnLButtonUp(UINT nFlags, CPoint pt);
//	virtual void OnLButtonUp( UINT nFlags, CPoint pt );

public:
	CTHotStartDlg( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTHotStartDlg();
};