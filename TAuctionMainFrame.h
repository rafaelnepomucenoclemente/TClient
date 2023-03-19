#pragma once


//!	����Ʈ ������ ����
class CTAuctionItem : public CTCtrlListItem
{
public :	// MEMBER DATA.

	CTClientItem*			m_pItem;
	DWORD					m_dwAuctionID;
	DWORD					m_dwBidMoney[ TMONEY_COUNT ];
	DWORD					m_dwBuyMoney[ TMONEY_COUNT ];
	CString					m_strSeller;
	DWORD					m_dwRemainTick;
	INT64					m_nEndTime;
	BYTE					m_bBidCount;
	DWORD					m_dwCode;

public :	// VIRTUAL FUNCTION.

	virtual void			ReflectSlot(CTCtrlListSlot* pSlot);

public :
							CTAuctionItem();
	virtual					~CTAuctionItem();
};


//!	����
class CTAuctionSlot : public CTCtrlListSlot
{
public :

	TComponent*				m_pImageSlot;
	TImageList*				m_pImageList;
	TComponent*				m_pUpgrade;
	TComponent*				m_pName;
	TComponent*				m_pClass;
	TComponent*				m_pNeedLevel;

	/*! ��ϵ� �������� �Ѱ��϶� ( ����, �ﱸ ǥ�� ) */
	TComponent*				m_pBid;
	TComponent*				m_pBuy;
	/*! ��ϵ� �������� ������ �϶� ( �ܰ�, �Ѿ� ǥ�� ) */
	TComponent*				m_pPrice;
	TComponent*				m_pTotal;

	TComponent*				m_pImageMoney1;
	TComponent*				m_pImageMoney2;
	TComponent*				m_pRune[2];
	TComponent*				m_pLuna[2];
	TComponent*				m_pCron[2];

	TComponent*				m_pSeller;
	TComponent*				m_pLeftTime;
	TComponent*				m_pBidCount;

public :	// VIRTUAL FUNCTION.
							CTAuctionSlot();
	virtual					~CTAuctionSlot();

	virtual void			ShowComponent( BOOL bShow = TRUE );
	virtual void			Select( BOOL bSel );
};


class CTAuctionCtrlList;

//!	Auction Main Frame.
/*!
*	@brief	��� ���� ������.
*
*/
class CTAuctionMainFrame : public CTFrameGroupBase
{
public :	// DEFINITION.

	enum
	{
		MAX_ITEM_SLOT = 9,
		MAX_COLUMN_HEAD = 7,
	};

	enum
	{
		TBUTTON_FIRST,
		TBUTTON_SECOND,
		TBUTTON_THIRD,
		TBUTTON_COUNT,
	};

	enum
	{
		TCOLUMN_HEAD_NAME,
		TCOLUMN_HEAD_CLASS,
		TCOLUMN_HEAD_LEVEL,
		TCOLUMN_HEAD_PRICE,
		TCOLUMN_HEAD_SELLER,
		TCOLUMN_HEAD_LEFTTIME,
		TCOLUMN_HEAD_BIDCOUNT,
		TCOLUMN_HEAD_COUNT
	};

private :	// MEMBER DATA.

	TFrame*					m_pAuctionListFrame;
	CTAuctionCtrlList*		m_pAuctionList;

	TButton*				m_pHeadBtn[ TCOLUMN_HEAD_COUNT ];
	CString					m_strHeadOrigText[ TCOLUMN_HEAD_COUNT ];

	TComponent*				m_pCurPage;
	TComponent*				m_pLastPage;
	TButton*				m_pMoveLeftPage;
	TButton*				m_pMoveRightPage;
	TButton*				m_pMoveLeftEnd;
	TButton*				m_pMoveRightEnd;
	TButton*				m_pBtn[ TBUTTON_COUNT ];

	WORD					m_wNpcID;

public :	// VIRTUAL FUNCTION.

							CTAuctionMainFrame( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual					~CTAuctionMainFrame();
	virtual void			SetSelect(UINT nFrame);
	virtual void			RequestInfo();
	virtual void			RequestUpdatePage();
	virtual void			ResetInfo();
	virtual void			OnLButtonDown( UINT nFlags, CPoint pt );
	virtual void			OnRButtonDown( UINT nFlags, CPoint pt );
	virtual BOOL			DoMouseWheel( UINT nFlags, short zDelta, CPoint pt);
	virtual ITDetailInfoPtr	GetTInfoKey( const CPoint& point );
	virtual BOOL			GetTChatInfo( const CPoint& point, TCHATINFO& outInfo );
	virtual TDROPINFO		OnDrop( CPoint point );
	virtual void			ShowComponent( BOOL bVisible );
	virtual HRESULT			Render( DWORD dwTickCount );
	
public :	// MEMBER FUNCTION.

	/* ���� ������ ����Ʈ�� ��� Ŭ�����Ѵ�. */
	void					ClearItems();
	/* ���� ����Ǹ� ȣ���Ѵ�. */
	void					ChangedTab( INT nSelectFrameID, INT nPrevFrameID );
	/* ����Ʈ���� Component ������Ʈ */
	void					UpdateByListComp();
	/* ��ưȰ��/��Ȱ�� ó��. ( ���ɹ�ǰ, ����, ��ñ���, ���� ) */
	void					UpdateByButtons();
	/* ����Ʈ�� ���� ������Ʈ �Ѵ�. */
	void					RefreshList();

	void					MoveNextPage();
	void					MovePrevPage();
	void					MoveFirstPage();
	void					MoveLastPage();
	BOOL					AvailableBID();
	void					SetButton( TButton* pButton, CString strBtn, DWORD dwFuncGM );
	void					SetSearchFrame();
	void					SetRegistFrame();
	void					SetMyBidFrame();
	void					SetBasketFrame();

	void					SetStackItem_Search();
	void					SetCanBidItem_Search();
	void					SetStackItem_Basket();
	void					SetCanBidItem_Basket();

	/* ���� ��Ŀ�̵� ����Ʈ��Ʈ���� ���´�. */
	TEdit*					GetCurEdit();

public :	// INLINE FUNCTION.

	static CTAuctionMainFrame*		GetInstance();
	CTAuctionCtrlList*		GetList();
	CTCtrlListItem*			GetSelectedItem();
    CTCtrlListItem*			GetAuctionItem( size_t index );
	void					SetCurPage( DWORD dwCurPage );
	void					SetLastPage( DWORD dwLastPage );
	void					SetColumnString( BYTE bColumn, CString& strArrowKey );
	void					ResetColumnString();
};

