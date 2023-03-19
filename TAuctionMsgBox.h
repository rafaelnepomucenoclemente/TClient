#pragma once


enum TBID_RESULT
{
	TBID_SUCCESS,
	TBID_NOT_ENOUGH_MONEY,
	TBID_LOW_MONEY,
	TBID_OVER_BUYPRICE,
	TBID_EQUAL_BUYPRICE,
};


//! ����������� �޼����ڽ�.
class CTAuctionBidOnMsgBox : public CTClientUIBase
{
private :	// Member Data.

	TComponent*				m_pTextMoney[ TMONEY_COUNT ];
	TEdit*					m_pEditMoney[ TMONEY_COUNT ];
	TComponent*				m_pWarningMsg;

	INT64					m_ldwCurPrice;
	INT64					m_ldwBidPrice;
	INT64					m_ldwBuyPrice;

public :	// Virtual Function.

							CTAuctionBidOnMsgBox( TComponent* pParent, LP_FRAMEDESC pDESC );
	virtual					~CTAuctionBidOnMsgBox();

public :	// Member Function.

	CTAuctionBidOnMsgBox*	GetInstance();
	void					UpdateByMoney();
	void					UpdateByComp();
	/* �޼��� �ڽ����� ���� ��ư�� �������� */
	TBID_RESULT				BidOn( INT64 ldwPlayerMoney, FLOAT fIncrement );
	/* */
	TEdit*					GetCurEdit();

public :	// Inline Function.

	void					SetCurPrice( INT64 ldwCurPrice );
	void					SetBidPrice( INT64 ldwBidPrice );
	void					SetBuyPrice( INT64 ldwBuyPrice );
	INT64					GetBidPrice();
};

