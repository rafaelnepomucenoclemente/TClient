#pragma once


//!	Auction InnerFrame Class.
class CTAuctionInnerFrame : public ITInnerFrame
{
private :	// Member Data.

	TAUCTIONFINDINFO		m_FindInfo;
	INT						m_nCurPage;
	INT						m_nLastPage;

public :	// Virtual Function.

	CTAuctionInnerFrame( TComponent* pParent, LP_FRAMEDESC pDESC, UINT nFrameID );
	virtual ~CTAuctionInnerFrame();

	virtual void			RequestInfo();
	/*! ���� �������� �����ϸ鼭 �����۸���Ʈ�� ������Ʈ��û. */
	virtual void			RequestUpdatePage();
	/*! ����Ʈ ������Ʈ ��Ŀ������. */
	virtual void			UpdateEditable( CPoint pt );

public :	// Member Function.

public :	// Inline Function.

	void					SetCurPage( INT nCurPage );
	void					SetLastPage( INT nLastPage );
	void					SetAlignKind( BYTE bAlignKind );
	WORD					GetPageNum();
	INT						GetCurPage();
	INT						GetLastPage();
	LPTAUCTIONFINDINFO		GetFindInfo();
};

