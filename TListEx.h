#pragma once

struct TITLECOMP
{
	std::vector<TComponent*> m_vComp;

	void ShowComponent( BOOL bShow )
	{
		for( INT i=0 ; i < m_vComp.size() ; ++i )
			m_vComp[i]->ShowComponent( bShow );
	}
};

typedef std::vector<TITLECOMP> VTITLECOMP;

class CTListEx : public TComponent 
{
public:
	enum { TCML_TYPE_LISTEX = 0xF0 };

	class TPrivateList : public TList
	{
	public:
		void SetTop(int nIdx);
		BOOL SetItem(int nLine, int nColumn, const CString& strText, DWORD dwData, DWORD dwColor = 0 );

	public:
		TPrivateList(TComponent *pParent, LP_FRAMEDESC pDesc);
	};

	typedef std::vector<TPrivateList*>	TLISTARRAY;

protected:
	int				m_nLastID;
	int				m_nPage;
	BOOL			m_bReady;
	BOOL			m_bNeedUpdate;
	
	BOOL			m_bMovingScroll;
	int				m_nItemPerPage;
	
	TPrivateList*	m_pCommonList;
	TLISTARRAY		m_vPageLists;
	TScroll*		m_pScroll;
	TButton*		m_pPageBtn;
	TImageList*		m_pTitleImgs;
	VTITLECOMP		m_vTitle;

	// < ���� ���� ����Ʈ�� �����ϱ� ���� �Լ��� >
public:
	void SetCommonList(LP_FRAMEDESC pDesc);
	void SetScroll(LP_FRAMEDESC pDesc);
	void SetPageButton(LP_FRAMEDESC pDesc);
	//void SetTitle(LP_FRAMEDESC pDesc);
	void AddPageTitle( INT nCount, TComponent** pTitles );
	int AddPageList(LP_FRAMEDESC pDesc);
	
	// ����!!
	void Build();

	// < ���� �� ����Ʈ �̿��� ���� �Լ��� >
public:
	int AddItem();
	void DelItem(int nLine);
	void ClearItem();

	void SetCommonItem(int nLine, int nCol, const CString& strItem, DWORD dwUser=0, DWORD dwColor = 0);
	void SetPageItem(int nLine, int nPage, int nCol, const CString& strItem, DWORD dwUser=0, DWORD dwColor = 0);

	void SetCommonItemGM(int nCol, DWORD dwEvent, DWORD dwGM);
	void SetPageItemGM(int nPage, int nCol, DWORD dwEvent, DWORD dwGM);

	DWORD GetCommonItemData(int nLine, int nCol);
	DWORD GetPageItemData(int nLine, int nPage, int nCol);

	TListItem* GetCommonItem(int nLine, int nCol);
	TListItem* GetPageItem(int nLine, int nPage, int nCol);

	TListItem* GetHitItem(const CPoint& pt);
	DWORD GetHitItemData(const CPoint& pt);

	int GetItemCount();
	
	TList* GetCommonList()			{ return m_pCommonList; }
	TList* GetPageList(int nIndex)	{ return m_vPageLists[nIndex]; }
	int GetPageCount()				{ return (int)m_vPageLists.size(); }
	int GetCurrentPage()			{ return m_nPage; }
	BOOL IsReady()					{ return m_bReady; }

protected:
	UINT GetUniqueID();
	TComponent* GetHitComp(const CPoint& pt);

	void UpdateScroll();
	void Update(DWORD dwTick);

public:
	virtual void ShowComponent( BOOL bVisible = TRUE);

protected:
	virtual void OnMouseMove( UINT nFlags, CPoint pt );
	virtual void OnLButtonUp( UINT nFlags, CPoint pt );
	virtual void OnRButtonUp( UINT nFlags, CPoint pt );
	virtual void OnLButtonDown( UINT nFlags, CPoint pt );	
	virtual void OnRButtonDown( UINT nFlags, CPoint pt );
	virtual BOOL DoMouseWheel( UINT nFlags, short zDelta, CPoint pt);
	virtual HRESULT Render( DWORD dwTickCount );

public:
	CTListEx(TComponent *pParent, LP_FRAMEDESC pDesc);
	virtual ~CTListEx();
};



























