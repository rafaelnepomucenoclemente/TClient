#pragma once

class CTGuildAppInnerFrame : public ITInnerFrame
{
public:
	class CSelecter
	{
	public:
		TButton*		m_pLB;
		TButton*		m_pRB;
		TComponent*		m_pTXT;
		
		INT				m_nCUR;
		VECTORSTRING	m_vTXTS;
		VECTORDWORD		m_vDATAS;

		BOOL			m_bEnable;

	public:
		CSelecter(TButton* pLB, TButton* pRB, TComponent* pTXT);

	public:
		void AddTxt(DWORD dwID, DWORD dwDATA=0);
		void ClearTxt();
		
		void Move(BOOL bLeft);
		void SetCur(INT nIndex);
		INT  GetCur();
		DWORD GetData(INT nIndex);
		
		void SetEnable(BOOL bEnable);
		BOOL IsEnable();
		BOOL HitTest(CPoint pt);
	};

public:
	// !! ������ �������� Init() ���� �ʱ�ȭ ���־�� �� !!
	//
	BOOL			m_bInit;		///< �ʱ�ȭ ����

	UINT			m_nModeCnt;		///< ��ü ����� ��
	UINT			m_nCurMode;		///< ���� ���

	TList*			m_pList;		///< ���� ����Ʈ
	int				m_nPrvSel;		///< ���� �������� ���� �ε���

	TMultiLineEdit*	m_pContentEdit;	///< ���� �Է� ������
	TList*			m_pContentList; ///< ���� ��� ����Ʈ

	CSelecter*		m_pSelecter;	///< �о� ����

public:
	/// Ŭ���� �ʱ�ȭ�� �����Ѵ�. �� �Լ����� �ֿ� ������� �����ȴ�.
	virtual void Init() = 0;

	/// ���� ������ �⺻ ���� �ʱ�ȭ �Ѵ�.
	virtual void ResetMode() = 0;
	/// ���� ������ ��忡 ���� ������Ʈ�� �����Ѵ�.
	virtual void UpdateCompByMode() = 0;
	/// ���� ����Ʈ���� ���õ� �׸��� �ٸ� ��Ʈ�ѿ� �ݿ��Ѵ�.
	virtual void UpdateByListSel() = 0;
	/// ����Ʈ ��� ���θ� ��´�.
	virtual BOOL IsEditMode() = 0;
	/// ���� ��Ŀ���� �����͸� ��´�.
	virtual TEdit* GetCurEdit() = 0;

	/// ��û�� ������ ��Ʈ���� �����Ѵ�.
	virtual void ResetInfo() = 0;
	/// ��Ʈ�� ������ ���� ������ ��û�Ѵ�.
	virtual void RequestInfo() = 0;

protected:
	/// ���뿡 �־��� ���ڿ��� �����Ѵ�.
	void SetContent(const CString& strText);

public:
	virtual void OnKeyDown(UINT nChar, int nRepCnt, UINT nFlags);
	virtual void OnLButtonDown( UINT nFlags, CPoint pt );
	virtual void OnRButtonDown( UINT nFlags, CPoint pt );
	virtual void SwitchFocus( TComponent *pCandidate );
	virtual void ShowComponent( BOOL bVisible = TRUE );
	
	virtual HRESULT Render( DWORD dwTickCount );

public:
	CTGuildAppInnerFrame(TComponent *pParent, LP_FRAMEDESC pDesc, UINT nFrameID);
	virtual ~CTGuildAppInnerFrame();
}; 
