#pragma once

class CTGuildNotifyDlg : public CTClientUIBase
{
public:
	enum { BUTTON_COUNT = 3 };

	enum COLUMN
	{
		COL_TITLE,			///< ���� ����
		COL_DATE,			///< ���� �ۼ���
		COL_SELECTION,		///< ���� ��ü ����
		COL_DELETE,			///< ���� ���� ��ư
		COL_COUNT
	};

	enum MODE
	{
		MODE_NORMAL,		///< �Ϲ� ��� (������ ���°͸� ������)
		MODE_MASTER,		///< ����� ��� (���� ���� ����)
		MODE_NEW,			///< ������ �ۼ�
		MODE_EDIT,			///< ���� ����
		MODE_COUNT
	};

	typedef CTGuildCommander::GuildNotify		GuildNotify;
	typedef CTGuildCommander::GuildNotifyVec	GuildNotifyVec;

public:
	static const BUTTON_STATE	MODE_BTN_VIEW[MODE_COUNT][BUTTON_COUNT];

protected:
	MODE			m_eMode;
	INT				m_nPrvSel;
	INT				m_nModIdx;

	TList*			m_pList;
	TComponent*		m_pViewAuthor;
	
	TComponent*		m_pViewTitle;
	TEdit*			m_pEditTitle;
	
	TMultiLineEdit*	m_pEditContents;
	TList*			m_pViewContents;

	TComponent*		m_pBTN[BUTTON_COUNT];

public:
	/// ���� ����� �ֽ��� ������ �����Ѵ�.
	void UpdateInfo();

	/// ���� ������ �⺻ ���� �ʱ�ȭ �Ѵ�. �⺻ ���� ����� ���ο� ���� �ٸ��� �����ȴ�.
	void ResetMode();
	/// ��忡 ���� ������Ʈ�� �ٽ� �����Ѵ�.
	void UpdateCompByMode();

	/// ������ �ۼ��� �����Ѵ�.
	void StartNew();
	/// ������ �ۼ��� ������.
	void EndNew(BOOL bOK);

	/// ���� ������ �����Ѵ�.
	void StartModify();
	/// ���� ������ ������.
	void EndModify(BOOL bOK);

	/// ������ �����Ѵ�.
	void Delete();

	/// ���� ������� ���θ� ��´�.
	BOOL IsEditMode();
	/// ���� ��Ŀ���� ����Ʈ ��Ʈ���� ��´�.
	TEdit* GetCurEdit();

protected:
	/// ���� ���õ� ���������� �ݿ��Ѵ�.
	void UpdateByListSel();

public:
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);
	virtual void OnKeyDown(UINT nChar, int nRepCnt, UINT nFlags);
	virtual void ShowComponent( BOOL bVisible = TRUE);
	virtual HRESULT Render( DWORD dwTickCount );

public:
	CTGuildNotifyDlg( TComponent *pParent, LP_FRAMEDESC pDesc);
	virtual ~CTGuildNotifyDlg();
};