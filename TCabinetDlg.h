#pragma once

class CTNormalCabinetDlg;
class CTCabinetSlot;
class CTCabinetItem;

class CTCabinetSlot : public CTCtrlListSlot
{
public:
	BOOL			m_bEmpty;
	TImageList*		m_pIcon;
	TComponent*		m_pName;

public:
	virtual void ShowComponent(BOOL bShow);
	virtual void Select(BOOL bSel);
	
public:
	CTCabinetSlot() : m_bEmpty(TRUE) {}
	virtual ~CTCabinetSlot() {}
};

class CTCabinetItem : public CTCtrlListItem
{
public:
	CTClientItem*	m_pClientItem;
	BYTE			m_bItemCnt;
	DWORD			m_dwStItemID;

public:
	CTCabinetItem* Clone();

public:
	virtual void ReflectSlot(CTCtrlListSlot* pSlot);
	
public:
	CTCabinetItem() : m_pClientItem(NULL) {}
	virtual ~CTCabinetItem();
};

/// ������ ������ ���� ���̽� �������̽� Ŭ����
class CTCabinetDlg : public CTClientUIBase
{
public:
	enum CABUPDATE_STATE
	{
		CABUPDATE_NOTYET,		///< ���� �����Կ� ���� �ƹ��� ������ ������ ���� ����
		CABUPDATE_DOING,		///< ������ ������ ��������
		CABUPDATE_COMPLETE,		///< ������ ������ ������
	};

	struct Cabinet
	{
		BOOL			m_bNeedUpdate;
		BOOL			m_bOpen;
		CTCLItemArray	m_vItems;

		Cabinet() 
			: m_bNeedUpdate(TRUE), m_bOpen(FALSE)
		{}
	};

	TComponent* m_pCharge;
	BOOL m_bShowCashCharge;
	BYTE m_bRememberPrevScrollPos;

protected:
	CABUPDATE_STATE	m_nCabUpdateSt;

	INT				m_nMaxItemSlot;		///< ��ü ������ ������ ��
	INT				m_nMaxItemCol;		///< ������ ���� ������ ��
	INT				m_nMaxCabCnt;		///< �������� ��
	INT				m_nMaxStorage;		///< �� �����Կ� ������ �� �ִ� �ִ� ������ ��

	TComponent*		m_pTitle;
	TComponent*		m_pSelectTxt;
	TComponent*		m_pCostTxt;

	TButton**		m_ppOpenBtn;
	Cabinet*		m_pCabinets;
	CTCtrlList*		m_pList;

	UINT			m_nSelectCab;
	INT				m_nLastHitBtn;
	BOOL			m_bNeedSetComp;
	BOOL			m_bNeedUpdate;

public:
	/**
		���� Ŭ������ �� Ŭ������ ���� ������� �ݵ�� ������ �־�� �Ѵ�.

		m_nMaxItemSlot	: ������ ������ ��ü ����
		m_nMaxItemCol	: ������ ������ ���� ����
		m_nMaxCabCnt	: ������ ����
		m_pTitle		: Ÿ��Ʋ
		m_pSelectTxt	: ����
		m_pCostTxt		: ���
		m_ppOpenBtn		: ������ ��ȣ ���� ��ư
		m_pCabinets		: ������ ��ȣ ����
	*/
	virtual void SetupComponent() = 0;

	/// ������ �������̽��� �ʱ�ȭ�Ѵ�.
	virtual void Initial();

	/// �������� ȭ�鿡 ǥ���ϵ��� ��û�Ѵ�.
	virtual void RequestShowComponent() = 0;

	/// �ش� �������� ���� ������ �����Ѵ�.
	virtual void SetCabinetInfo(UINT nCab, BOOL bOpen);

	/// �־��� �������� �����Ѵ�.
	virtual BOOL SelectCab(UINT nCab);

	/// �־��� �������� ����.
	virtual void Clear(UINT nCab);
	/// ��ü �������� ����.
	virtual void ClearAll();

	/// �������� �����Ѵ�.
	virtual void Update(DWORD dwTick);

	/// �ش� �������� �������� ������ ��´�.
	virtual INT64 GetCabOpenCost(UINT nCab);
	/// �ش� �������� �̿��ϱ� ���� ������ ��´�.
	virtual INT64 GetCabUseCost(UINT nCab);

public:
	/// �������� ���� ������ �Ϸ�Ǿ��ٰ� �����Ѵ�.
	void CompleteCabUpdate();
	/// �־��� �������� ���� ������ �Ϸ�Ǿ��ٰ� �����Ѵ�.
	void CompleteCabinetUpdate(UINT nCab);

	/// �־��� �����Կ� �������� �߰��Ѵ�.
	virtual BOOL AddItem(UINT nCab, CTCabinetItem* pItem);
	/// �־��� �����Կ��� �������� �����Ѵ�.
	VOID DeleteItem(UINT nCab, DWORD dwCabintItemID);
	/// StID �� ������ �����Կ��� �������� ã�´�.
	CTCabinetItem* GetCabItemByStID(UINT nCab, DWORD dwStItemID);
	/// ���� ���õ� �������� ��´�.
	CTCabinetItem* GetSelectCabItem();

	/// ���� ���õ� �������� ��´�.
	UINT GetSelectCab() const;

	/// �������� �뷮�� �����Ѵ�.
	void SetMaxStorage(INT nMax);
	/// �������� Ÿ��Ʋ�� �����Ѵ�.
	void SetTitle(const CString& strTITLE);

	/// �� �������� ������ �ʿ����� �뺸�Ѵ�.
	void NotifyUpdate();

	void SelectLastestItem();

public:
	virtual void SwitchFocus(TComponent* pCandidate);
	virtual BOOL DoMouseWheel( UINT nFlags, short zDelta, CPoint pt);
	virtual void OnLButtonDown(UINT nFlags, CPoint pt);
	virtual void OnRButtonDown(UINT nFlags, CPoint pt);
	virtual void ShowComponent( BOOL bVisible = TRUE);
	virtual HRESULT Render(DWORD dwTickCount);

	virtual TDROPINFO OnDrop(CPoint point);
	virtual BYTE OnBeginDrag(LPTDRAG pDRAG, CPoint point);

	virtual ITDetailInfoPtr GetTInfoKey(const CPoint& point );
	virtual BOOL GetTChatInfo(const CPoint& point, TCHATINFO& outInfo );

public:
	CTCtrlList* GetList() const							{ return m_pList; }
	CTCLItemArray& GetItemArray(UINT nCab)				{ return m_pCabinets[nCab].m_vItems; }
	const CTCLItemArray& GetItemArray(UINT nCab) const	{ return m_pCabinets[nCab].m_vItems; }
	Cabinet* GetCabinet(UINT nCab)						{ return &m_pCabinets[nCab]; }
	const Cabinet* GetCabinet(UINT nCab) const			{ return &m_pCabinets[nCab]; }
	BOOL IsOpen(UINT nCab) const						{ return m_pCabinets[nCab].m_bOpen; }
	INT GetLastHitBtn() const							{ return m_nLastHitBtn; }
	INT GetMaxStorage() const							{ return m_nMaxStorage; }
	
public:
	CTCabinetDlg( TComponent *pParent, LP_FRAMEDESC pDesc);
	virtual ~CTCabinetDlg();
};

