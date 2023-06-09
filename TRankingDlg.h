#pragma once


class CTRankingDlg  :  public CTClientUIBase
{
	

private :



public:
	enum{ MAX_SLOT_COUNT = 16 };
	enum{ MAX_COLOR_SLOT_COUNT = 8 };
	enum
	{
		TRANKINFO_TAB_TOTAL = 0,
		TRANKINFO_TAB_COUNTRY,
		TRANKINFO_TAB_TOURNAMENT,
		TRANKINFO_TAB_COUNT
	};
	static BYTE		m_bTabIndex;
	TMAPFAMERANK	m_mapMONTHFAMERANK[TCONTRY_COUNT];		// Month Fame Rank pool
	VTFAMERANK		m_vtFIRSTGRADEGROUP;	
	BYTE			m_bFirstCount;
	VTFAMERANK		m_vtFAMERANK;
	TComponent*		m_pSLOT[MAX_SLOT_COUNT];
	TComponent*		m_pRANK[MAX_SLOT_COUNT];
	TComponent*		m_pNAME[MAX_SLOT_COUNT];
	TImageList*		m_pCOUNTRY[MAX_SLOT_COUNT];
	TButton*        m_pHBut;
	TComponent*		m_pGUILD[MAX_SLOT_COUNT];
	TComponent*		m_pMONTHFAME[MAX_SLOT_COUNT];
	TButton*		m_pBUTTON[MAX_SLOT_COUNT];

public :
		virtual ITDetailInfoPtr GetTInfoKey( const CPoint& point );
	CPoint m_vTPOS;
	CTRankingDlg ( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTRankingDlg();
	virtual void OnLButtonUp(UINT nFlags, CPoint pt);
	virtual void ShowComponent( BOOL bVisible = TRUE);

	static BOOL	SortRank( CTFameRank* pLeft, CTFameRank* pRight );
	void	ReleaseData();
	void	ResetData( BYTE bTopTabIndex, BYTE bBottonTabIndex );
	void	ResetTabIndex( BYTE bTabIndex );
	virtual BOOL	CanWithItemUI();
};