
#include "Stdafx.h"
#include "TClientCompanion.h"
#include "TClientGame.h"

// =======================================================
CTClientCompanion::CTClientCompanion()
	: CTClientRecall(), m_wCompanionID(0)
{
	m_bCanSelected = FALSE;
}
// -------------------------------------------------------
CTClientCompanion::~CTClientCompanion()
{
	
}

// =======================================================
void CTClientCompanion::SetCompanionInfo(WORD wMonID, WORD wCompanionID, CString strName, DWORD dwExp, DWORD dwNextExp, DWORD dwLife, BYTE bLevel)
{
	m_wMonID = wMonID;
	m_wCompanionID = wCompanionID;
	m_strCompanionName = strName;
	m_dwExp = dwExp;
	m_dwNextExp = dwNextExp;
	m_dwLife = dwLife;
	m_bLevel = bLevel;
}

void CTClientCompanion::SetBonusInfo(WORD wBonusID, WORD wBonusValue)
{
	m_wBonusID = wBonusID;
	m_wBonusValue = wBonusValue;
}

void CTClientCompanion::SetCharATTR(WORD wSTR, WORD wDEX, WORD wCON, WORD wINT, WORD wWIS, WORD wMEN)
{
	m_wSTR = wSTR;
	m_wDEX = wDEX;
	m_wCON = wCON;
	m_wINT = wINT;
	m_wWIS = wWIS;
	m_wMEN = wMEN;
}

void CTClientCompanion::Spawn()
{
	//m_wCompanionID = wCompanionID;
	//m_pPetTemp = CTChart::FindTPETTEMP( wPetID );
	LPTMONTEMP pCompanionTemp = CTChart::FindTMONTEMP( m_wMonID );

	m_pTEMP = pCompanionTemp;
	//m_pTEMP->m_dwOBJ = pCompanionTemp->m_dwOBJ;
	m_pTEMP->m_bCanSelected = FALSE;
	m_pTEMP->m_fScaleX = 0.5f;
	m_pTEMP->m_fScaleY = 0.5f;
	m_pTEMP->m_fScaleZ = 0.5f;
	m_pTEMP->m_bDrawName = FALSE;
	m_pTEMP->m_bCanAttack = FALSE;
	m_pTEMP->m_strNAME = CString("");

	m_bIsSpawned = TRUE;
}

// -------------------------------------------------------
BOOL CTClientCompanion::Despawn()
{
	/*m_vPushDIR = D3DXVECTOR2(0,0);
	m_vJumpDIR = D3DXVECTOR2(0,0);
	m_vFallDIR = D3DXVECTOR2(0,0);
	m_dwPushTick = 0;
	m_dwJumpTick = 0;
	m_dwFallTick = 0;
	m_nPITCH = 0;
	m_nDIR = 0;
	m_bMouseDIR = TKDIR_N;
	m_bKeyDIR = TKDIR_N;
	SetTAction(TA_STAND);
	m_dwHP = 0;

	m_bDrawTalk = FALSE;
	m_bCanSelected = FALSE;
	
	CTClientGame::GetInstance()->DeleteRecall(m_dwID, TRUE);*/

	m_bIsSpawned = FALSE;

	return TRUE;
}
// =======================================================

// =======================================================
BYTE CTClientCompanion::GetDrawName()
{
	return FALSE;
}
// -------------------------------------------------------
void CTClientCompanion::Render(CD3DDevice *pDevice, CD3DCamera *pCamera)
{
	CTClientGame* pGame = CTClientGame::GetInstance();
	CTClientChar* pMyHost = pGame->FindPC(GetHostID());
	if( !pMyHost )
		m_fSpeedFactor = 1.3f;
	else
		m_fSpeedFactor = pMyHost->m_fSpeedFactor;

	CTClientRecall::Render(pDevice,pCamera);
}
// =======================================================
