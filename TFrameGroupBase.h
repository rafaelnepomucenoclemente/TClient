#pragma once

class CTFrameGroupBase : public CTClientUIBase
{
public:
	struct FrameInfo
	{
		UINT			m_nFrameID;
		ITInnerFrame*	m_pFrameCtrl;
		TButton*		m_pTabCtrl;
		BOOL			m_bUseBlank;
		CString			m_strBlankMsg;
	};

	typedef std::vector<FrameInfo>	FrameInfoArray;

public:
	FrameInfoArray	m_FrameInfoArray;
	CPoint			m_ptInnerFrame;
	INT				m_nSelectedFrame;
	TComponent*		m_pBlank;

public:
	/**
		���ο� �������� �� â�� �ڽ����� �߰��Ѵ�.

		@param pFrame		�߰��ϰ��� �ϴ� ������
		@param dwTabID		�� �������� �ǹ�ư���� ����� ��ư ���̵�
		@param strBlankMsg	���� �� ���� ����ִ� ���·� ������� �� 
							��� �����Ӵ�� ���Ե� �޽���
	*/
	virtual UINT AddFrame(ITInnerFrame* pFrame, DWORD dwTabID, const CString& strBlankMsg="");
	/// ��ü �Ҽ� �������� ��� �����Ѵ�.
	virtual void ClearFrame();
	
	/// ��ü �Ҽ� �������� ������ ��´�.
	virtual UINT GetFrameCount() const;
	/// �־��� �ε����� �������� ��´�.
	virtual ITInnerFrame* GetInnerFrame(UINT nFrame) const;
	
	/// �־��� �������� ����ְ� �ϰų� �ٽ� ���󺹱ͽ�Ų��.
	virtual void SetBlank(UINT nFrame, BOOL bBlank, const CString& strBlankMsg="");

	/// �־��� �������� �����Ѵ�.
	virtual void SetSelect(UINT nFrame);
	/// ���õ� ������ID�� ���´�.
	virtual INT GetSelectedFrame();
	/// �־��� �������� ���� ���õǾ��°��� ��´�.
	virtual BOOL IsSelect(UINT nFrame) const;

	/**
		�� �������� ������ �ʿ����� �˸���. �ַ� ���� Ŭ���̾�Ʈ ��������
		�� �Լ��� ���� ������ �˸��� ResetInfo() �� ���� �� ������ ����
		�ϴ� ������ ���� ���ȴ�.
	*/
	virtual void RequestInfo();
	/// RequestInfo() �� ����.
	virtual void ResetInfo();

public:
	virtual void ShowComponent(BOOL bVisible = TRUE);
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);

public:
	CTFrameGroupBase(TComponent* pParent, LP_FRAMEDESC pDesc, DWORD dwInnerPosID);
	CTFrameGroupBase(TComponent* pParent, LP_FRAMEDESC pDesc, const CPoint& ptInnerPos);
	virtual ~CTFrameGroupBase();
};