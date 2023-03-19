#pragma once

class CTGuildRTTypeFrame : public ITInnerFrame
{
public:
	struct InfoPos
	{
		BOOL	m_bCommon;	///< ���� ������ ����
		UINT	m_nPage;	///< ������ ��ȣ
		UINT	m_nColumn;	///< Į�� ��ȣ
	};

public:
	CPoint			m_ptLastLClick;
	UINT			m_nPageMax;
	UINT			m_nCurPage;
	TButton**		m_vTab;
	CTListEx**		m_vList;

public:
	virtual void RequestInfo() = 0;
	virtual void ResetInfo() = 0;

	virtual void OnLButtonDown( UINT nFlags, CPoint pt );

	virtual void SwitchFocus(TComponent *pCandidate);
	virtual void ShowComponent( BOOL bVisible = TRUE);

public:
	virtual void ChangePage(UINT nPage);

public:
	CTGuildRTTypeFrame(TComponent *pParent, LP_FRAMEDESC pDesc, UINT nFrameID, UINT nPageCount);
	virtual ~CTGuildRTTypeFrame();
};