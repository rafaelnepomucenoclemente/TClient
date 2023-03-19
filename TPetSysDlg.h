#pragma once

#include "TClientCompanion.h"

class CTPetSysDlg : public CTClientUIBase
{
public:
	typedef std::map< BYTE, CTClientCompanion*> CTCompanionMap;

protected:
	CTCompanionMap m_mapCompanion;
private :
	TComponent* m_pStatT[6];
	TButton*    m_pStatB[6];
	TComponent* m_pStatV[6];
	TImageList* m_pPet[5];
	TComponent* m_pAttr[5];
	TComponent* m_pAttrV[5];

	TImageList* m_pIcon;
	TComponent* m_pName;
	TComponent* m_pBonusName;
	TComponent* m_pStatus;
	TButton* m_pSummon;
	TButton* m_pDelete;
	TButton* m_pLevelUp;
	TComponent* m_pHP;
	TComponent* m_pExp;
	TGauge* m_pHPBar;
	TGauge* m_pExpBar;
	TComponent* m_pBonusT;
	TComponent* m_pArrowUP;
	TComponent* m_pArrowDN;
    TComponent* m_pStrText;
	TComponent* m_pIntText;
	TComponent* m_pAgiText;
	TComponent* m_pWisText;
	TComponent* m_pEndText;
	TComponent* m_pWillText;
	TComponent* m_pStrVal;
	TComponent* m_pIntVal;
	TComponent* m_pAgiVal;
	TComponent* m_pWisVal;
	TComponent* m_pEndVal;
	TComponent* m_pWillVal;
    TButton* m_pStrBut;
	TButton* m_pIntBut;
	TButton* m_pAgiBut;
	TButton* m_pWisBut;
	TButton* m_pEndBut;
	TButton* m_pWillBut;
	TComponent* m_pTab1Shown;
  
	TComponent* m_pStatPText;
	TComponent* m_pStatPValue;
	TImageList* m_pSlot1T;
	TImageList* m_pSlot2T;
	TButton* m_pLeftSwitch;
	TButton* m_pRightSwitch;
	/*
	TImageList* m_pSlot1;
	TImageList* m_pSlot2;  //´ll add later
	*/
	TButton* m_pTab1;
	TButton* m_pTab2;
	TComponent* m_pLevel;

	DWORD dwSelExp;
	DWORD dwSelNextExp;

	BYTE m_bCurSelSlot;
	BYTE m_bPrevSelSlot;
	BYTE m_bLastSelSlot;

	BYTE m_bSummonedSlot;
	BOOL m_bIsSummoned;

	BYTE m_bSelTab;

public :
	CTPetSysDlg( TComponent *pParent, LP_FRAMEDESC pDesc );
	virtual ~CTPetSysDlg();

	BYTE GetLastSelSlot() { return m_bLastSelSlot; }
	BYTE GetCurSelSlot() { return m_bCurSelSlot; }
	BYTE GetSummonedSlot() { return m_bSummonedSlot; }
	BOOL IsSummoned() { return m_bIsSummoned; }

	CTClientCompanion* GetCompanionBySlot( BYTE bSlot );

	void SelectTab( BYTE bTab ) { m_bSelTab = bTab; }

	void AddCompanion( CTClientCompanion* pCOMPANION );
	void DelCompanion( BYTE bSlot );
	void DisplayCompanion( BYTE bSlot );
	void SelCompanion( BYTE bSlot );
	void SetSummonedSlot( BYTE bSlot );
	void Unsummon();
	void Update();
	void PrepareDisplay();
	void ClearDisplay();
	void ClearCompanion();

	virtual HRESULT Render( DWORD dwTickCount );
};
