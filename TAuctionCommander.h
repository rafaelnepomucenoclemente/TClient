#pragma once


//! Auction Commander Class.
class CTAuctionCommander
{
private :

	CTAuctionCommander();
	~CTAuctionCommander();

private :	// MEMBER DATA.

	CTClientSession*			m_pSession;
	WORD						m_wNpcID;

public :	// REQUEST FUNCTION.

	/*! ��� ��ϼ����� ����Ʈ��û. */
	void						RequestDefaultList();
	/*! �˻����� ����Ʈ��û. */
	void						RequestSearchList( LPTAUCTIONFINDINFO pInfo );
	/*! ������� ����Ʈ��û. */
	void						RequestRegistList( LPTAUCTIONFINDINFO pInfo );
	/*! ����������� ����Ʈ��û. */
	void						RequestMyBidList( LPTAUCTIONFINDINFO pInfo );
	/*! ���ɹ�ǰ���� ����Ʈ��û. */
	void						RequestBasketList( LPTAUCTIONFINDINFO pInfo );
	/*! Update Current Page */
	void						RequestUpdatePage();
	/*! �����۵�� ��û. */
	void						RequestItemRegist();
	/*! �����۵����� ��û. */
	void						RequestItemRegCancel();
	/*! ������û. */
	void						RequestBid();
	/*! ��ñ��� ��û. */
	void						RequestBuy();
	/*! ���ɹ�ǰ ��� ��û */
	void						RequestInsertBasket();
	/*! ���ɹ�ǰ ������� ��û */
	void						RequestEraseBasket();

public :	// RECEIVE FUNCTION.

	/*! ��û�� ������ ����Ʈ�� ó���Ѵ�. */
	BOOL						RecvFindList_Result( BYTE bResult );
	void						RecvFindList();
	/*! ������� �޼������ */
	BOOL						RecvBid_Result( BYTE bResult );
	/*! ��ñ��Ű�� �޼������ */
	BOOL						RecvBuy_Result( BYTE bResult );
	/*! ��ž����� ��� �޼������ */
	BOOL						RecvReg_Result( BYTE bResult );
	/*! ��ž����� ������ �޼������ */
	BOOL						RecvRegCancel_Result( BYTE bResult );

public :	// MEMBER FUNCTION.

	/*! MainFrame( ������ưŬ�� ó�� ) */
	void						OnClicked_BidButton();
	/*! MainFrame( ��ñ��Ź�ưŬ�� ó�� ) */
	void						OnClicked_BuyButton();
	/*! MainFrame( ���ɹ�ǰ��ưŬ�� ó�� ) */
	void						OnClicked_InsertBasketButton();
	/*! BasketFrame( ���Ź�ǰ ���� ��ưŬ�� ó�� ) */
	void						OnClicked_DeleteBasketButton();
	/*! SearchFrame( �˻���ưŬ�� ó�� ) */
	void						OnClicked_SearchButton();
	/*! SearchFrame( �˻����� �ʱ�ȭ ó�� ) */
	void						OnClicked_SearchResetButton();
	/*! RegistFrame( ��Ϲ�ưŬ�� ó�� ) */
	void						OnClicked_RegistButton();
	/*! RegistFrame( ������ ������� �ʱ�ȭ ) */
	void						OnClicked_RegistResetButton();
	/*! RegistFrame( �����ҹ�ưŬ�� ó�� ) */
	void						OnClicked_RegistCancelButton();
	/*! Page �ʱ�ȭ */
	void						ClearPageNumber();
	/*! 1��ư Ȯ�� �޼���â */
	void						SimpleMsgBox( CString strMSG );
	/* ���Ĺ�ư Ŭ��ó��. */
	void						OnClicked_AlignKind( BYTE bColumn, BYTE bASC, BYTE bDESC );

public :	// INLINE FUNCTION.

	/*!	�ν��Ͻ��� ���´�. */
	static CTAuctionCommander*	GetInstance();
	/*! Session�� ���´�. */
	CTClientSession*			GetSession();
	/*! NpcID�� ������. */
	WORD						GetNpcID();
	/*! NpcID�� ����. */
	void						SetNpcID( WORD wNpcID );
};