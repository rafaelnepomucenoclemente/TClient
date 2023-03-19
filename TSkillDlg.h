#pragma once


class CTSkillDlg : public CTClientUIBase
{
public:
	MAPTSKILLTEMP	m_mapTSKILL;		///< ���� �ִ� ��ų ���
	MAPTSKILLTEMP	m_mapTINITSKILL;	///< �ʱ�ȭ ������ ��ų ���

	CTClientChar*	m_pMainChar;
	CPoint			m_vPOS;

	TTabCtrl*		m_pTTAB;
	
	BYTE 			m_bTRADE;			///< ��ų�� ���� ���ΰ�?
	BYTE 			m_bSKILLINIT;		///< ��ų�� �ʱ�ȭ �ϴ� ���ΰ�?
	BYTE			m_bSiInvenID;		///< ��ų �ʱ�ȭ �������� �κ� ���̵�
	BYTE			m_bSiSlotID;		///< ��ų �ʱ�ȭ �������� �κ������� ���� ���̵�
	WORD			m_bSiSelectID;		///< ��ų �ʱ�ȭ�� ���� ���� �ֱٿ� ���õ� ��ų�� ���̵�

	LPTOPENBYCASH m_pOpenByCash;
	void SetOpenByCash( LPTOPENBYCASH );
	void ClearOpenByCash();

public:
	/// �ش� ��ų�� ���� ���� ��ư�� ǥ������ ���θ� ��´�.
	BYTE IsButtonVisible(
		LPTSKILL pTSKILL,
		BYTE bLevel);
	
	/// ���� ���õ� ���� ��´�.
	BYTE GetCurSel();
	
	/// ��ų �ʱ�ȭ ��带 �����Ѵ�.
	BYTE StartSkillInitMode(BYTE bInvenID, BYTE bSlotID);
	/// ��ų �ʱ�ȭ ��带 ������.
	BYTE EndSkillInitMode();

	/// ��ų �ʱ�ȭ ���� ����� ���� �����.
	void ClearInitPossSkill();
	/// ��ų �ʱ�ȭ ���� ����� �߰��Ѵ�.
	void AddInitPossSkill(WORD wSkillID);

protected:
	void UpdateNormalMode();
	void UpdateInitMode();

public:
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);
	
	virtual ITDetailInfoPtr GetTInfoKey( const CPoint& point );
	virtual BYTE OnBeginDrag(LPTDRAG pDRAG, CPoint point);
	virtual BOOL CanWithItemUI();

	virtual HRESULT Render( DWORD dwTickCount);

public:
	CTSkillDlg( TComponent *pParent, LP_FRAMEDESC pDesc);
	virtual ~CTSkillDlg();
};
