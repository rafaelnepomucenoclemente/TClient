#pragma once

enum
{
	TREG_NO_BIDMONEY,
	TREG_LOW_BUYMONEY,
	TREG_COUNT,
};

//! Regist Frame Class.
class CTAuctionRegist : public CTAuctionInnerFrame
{
public :	// DEFINITION.

	enum
	{
		TTERM_BUTTON_COUNT = 4,
		TRUNE_LENGTH_STACKITEM = 2,
		TRUNE_LENGTH_ITEM = TRUNE_LENGTH / 2
	};

private :	// COMPONENT.

	TImageList*				m_pIcon;							//!< ����� �����۾�����.
	TComponent*				m_pUpgrade;							//!< ���׷��̵� ��ġ.
	TComponent*				m_pName;							//!< �������̸�.
	TComponent*				m_pItemCount;						//!< �����ۼ���.
	TButton*				m_pTermBtn[ TTERM_BUTTON_COUNT ];	//!< ��Žð� ��ư( 6, 12, 24, 48 �ð� ).

	TComponent*				m_pTitleStartPrice;					//!< ��Ž��۰� & �ܰ�.
	TComponent*				m_pTitleBuyPrice;					//!< ��ñ��Ű� & �� ��.
	TEdit*					m_pBid[ TMONEY_COUNT ];				//!< ��Ž��۰��� ����Ʈ�ڽ�.
	TEdit*					m_pBuy[ TMONEY_COUNT ];				//!< ��ñ��Ű��� ����Ʈ�ڽ�.
	TComponent*				m_pTextBuy[ TMONEY_COUNT ];			//!< ��ñ��Ű��� �ؽ�Ʈ.
	TList*					m_pListNotice;						//!< ��������� ���� �˸�����.

private :	// MEMBER DATA.

	CTClientItem*			m_pItem;							//!< ����� �����۵�����.
	DWORD					m_dwTerm;							//!< ��Žð� ������.
	TAUCTIONREGINFO			m_RegInfo;							//!< ������ �������.
	BOOL					m_bEditEnable;						//!< if Stack > 1  m_bEditEnable = FALSE.
																//!< ��ĥ�� �ִ� �������� ��ñ��Ű����� ���� �� �� ����.
public :	// VIRTUAL FUNCTION.

							CTAuctionRegist(TComponent* pParent, LP_FRAMEDESC pDesc);
	virtual					~CTAuctionRegist();

	/*! */
	virtual void			RequestInfo();
	/*! ���� �������� �����ϸ鼭 �����۸���Ʈ�� ������Ʈ��û. */
	virtual void			RequestUpdatePage();
	/*! */
	virtual void			ResetInfo();
	/*! ����Ʈ ������Ʈ ��Ŀ������. */
	virtual void			UpdateEditable( CPoint pt );

	virtual void			OnLButtonDown( UINT nFlags, CPoint pt );
	virtual void			OnKeyDown( UINT nChar, int nRepCnt, UINT nFlags );
	virtual void			OnChar( UINT nChar, int nRepCnt, UINT nFlags);
	virtual BYTE			OnBeginDrag( LPTDRAG pDRAG, CPoint point );
	virtual TDROPINFO		OnDrop( CPoint point );
	virtual ITDetailInfoPtr	GetTInfoKey( const CPoint& point );

public :	// MEMBER FUNCTION.

	void					UpdateRegInfo();
	void					UpdateByComp();
	void					UpdateByNumber();
	BOOL					CheckInvalidPrice();
	TEdit*					GetCurEdit();

public :	// INLINE FUNCTION.

	void					SetItem( CTClientItem* pItem );
	void					SetInvenID( BYTE bInvenID );
	void					SetItemCount( BYTE bCount );
	/*! ���� �̾����� ��쿡 ��� */
	void					SetStartPrice( INT64 dwPrice );
	void					SetBuyPrice( INT64 dwPrice );
	/*! ���� �������� ��쿡 ��� */
	void					SetUnitPrice( INT64 dwPrice );
	void					SetTotalPrice( INT64 dwPrice );

	void					SetEditEnable( BOOL bEnable );
	void					SetEditUnitPrice_RuneLength( INT nRuneLength );

	CTClientItem*			GetItem();
	LPTAUCTIONREGINFO		GetRegistInfo();
	INT64					GetStartPrice();
	INT64					GetBuyPrice();
	INT64					GetTotalPrice();
};