#pragma once

#include "TDetailNameDlg.h"

// =====================================================================
/**	@class		CTDetailInfoDlg
	@brief		�������� ȭ�鿡 ǥ���ϱ����� UI.
	
*/// ===================================================================

class CTDetailInfoDlg : public CTClientUIBase
{
public:
	TImageList*			m_vICON[TDETAILINFO_ICON_COUNT];
	TCOMP_ARRAY			m_vTEXT;

	TComponent*			m_pNAME;
	TComponent*			m_pTEXT;
	TComponent*			m_pBACK;
	TComponent*			m_pSTART;
	TComponent*			m_pEND;
	TComponent*			m_pCLOSE;
	TImageList*			m_pGEM_1;
	TImageList*			m_pGEM_2;
	TImageList*			m_pGEM_3;
	TImageList*			m_pGEM_4;
	TImageList*			m_pGEM_5;

	CD3DFont*			m_pNAMEFONT;

	//CRect				m_vTAREA;
	CSize				m_vTEXTSIZE;
	CPoint			m_ptTITLESTART;
	CPoint			m_ptUNTITLESTART;
	CPoint			m_ptTextStart;

	INT 				m_nTitlePosY;
	INT 				m_nTitlePosX_NOR;
	INT 				m_nTitlePosX_NIC;

	CTClientObjBase*	m_pHOST;

public:
	/// �־��� �������� ��� ������ �����Ѵ�.stupid Konst 

	void ResetINFO(ITDetailInfoPtr pInfo);

	/// �ݱ��ư�� ���̰ų� �����.
	void ShowCloseButton(BOOL bShow);
	void ShowGemStone(BYTE bGem);

public:
	virtual BOOL CanWithItemUI();
	virtual void ShowComponent( BOOL bVisible = TRUE);
	virtual void GetComponentRect( LPRECT lpRect);
	virtual ITDetailInfoPtr GetTInfoKey( const CPoint& point );
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);

protected:
	void AddText(const CString& strTEXT, DWORD dwColor);
	void ClearText();
	BYTE GetIconID( ITDetailInfoPtr pInfo);

public:
	CTDetailInfoDlg( TComponent*pParent, LP_FRAMEDESC pDesc);
	virtual ~CTDetailInfoDlg();
};