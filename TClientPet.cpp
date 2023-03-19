#include "Stdafx.h"
#include "TClientPet.h"
#include "TClientGame.h"
#include "TPetManageDlg.h"
// =======================================================
CTClientPet::CTClientPet()
	: CTClientRecall(), m_wPetID(0), m_pPetTemp(NULL), m_pTakeUpChar(NULL)
{
	m_bCanSelected = FALSE;
}
// -------------------------------------------------------
CTClientPet::~CTClientPet()
{
	if( m_dwTakeUpPivot )
	{
		MAPOBJECT::iterator itr = m_mapEQUIP.find(m_dwTakeUpPivot);
		if( itr != m_mapEQUIP.end() )
			m_mapEQUIP.erase(itr);
	}

	if( m_pTakeUpChar )
		m_pTakeUpChar->SetRidingPet(NULL);
}
// =======================================================
void CTClientPet::SetPetInfo(const CString& strName, WORD wPetID, const CTime& tEndTime)
{

	m_strPetName = strName;
    CTClientGame* pGame = CTClientGame::GetInstance();	
	CTPetManageDlg* pDlg = static_cast<CTPetManageDlg*>( pGame->GetFrame(TFRAME_PET_MANAGE) );
	m_wPetID = wPetID;
	m_pPetTemp = CTChart::FindTPETTEMP( wPetID );


	m_tPetEndTime = tEndTime;

	m_fBaseSpeedFactor = 1.3f;
/*
	if( m_pPetTemp->m_bRecallKind1 == PETKIND_ONE ||
		m_pPetTemp->m_bRecallKind1 == PETKIND_TWO )
	{
		FLOAT fFac = 1.0f + ( FLOAT(m_pPetTemp->m_wRecallValue1) / 100.0f );
		m_fBaseSpeedFactor *= fFac;
	}

	if( m_pPetTemp->m_bRecallKind2 == PETKIND_ONE ||
		m_pPetTemp->m_bRecallKind2 == PETKIND_TWO )
	{
		FLOAT fFac = 1.0f + ( FLOAT(m_pPetTemp->m_wRecallValue2) / 100.0f );
		m_fBaseSpeedFactor *= fFac;
	}
*/
	

    m_fBaseSpeedFactor *= 1.86f;

	//m_fBaseSpeedFactor *= 1.49f;

	m_fTDEFAULTSPEED = m_fBaseSpeedFactor;

    m_pTEMP = CTChart::FindTMONTEMP( m_pPetTemp->m_wMonID );
}
void CTClientPet::SetSaddle(WORD wItemID, const CTime& tEndTime)
{
		CString it;
	it.Format("Trace2: %d",wItemID);

	MessageBox(NULL,it,"Trace2",2);
	wSaddleID = wItemID;
	m_tPetEndTime = tEndTime;
}
// =======================================================
BOOL CTClientPet::TakeUp( CD3DDevice *pDevice,
						  CTachyonRes *pRES,
						  CTClientChar *pChar,
						  DWORD dwPivot)
{

	if( m_pTakeUpChar )
		return FALSE;

	MAPDWORD::iterator itr = m_OBJ.m_pOBJ->m_mapPIVOT.find(dwPivot);
	if( itr == m_OBJ.m_pOBJ->m_mapPIVOT.end() )
		return FALSE;

	TACTION act = pChar->FindActionID(
		TA_RIDING,
		pChar->GetWeaponID(pChar->m_bMode));
	BYTE bHideOnCapeMode = CTChart::GetTACTION(TA_RIDING)->m_bHideOnCapeMode;

	if( pChar->m_bHideOnCapeMode != bHideOnCapeMode ||
		pChar->m_bEquipMode != act.m_bEquipMode )
	{
		pChar->m_bHideOnCapeMode = bHideOnCapeMode;
		pChar->m_bEquipMode = act.m_bEquipMode;

		pChar->ResetEQUIP(
			pDevice,
			pRES);
	}

	pChar->m_bAction = TA_RIDING;
	pChar->SetAction(
		act.m_dwActID,
		act.m_dwAniID);

	m_dwTakeUpPivot = itr->second + 1;
	pChar->SetRidingPet(this);
	m_nDIR = INT(pChar->m_wDIR) - INT(m_wDIR);

	m_mapEQUIP.insert( std::make_pair(m_dwTakeUpPivot,pChar) );
	D3DXMatrixIdentity(&pChar->m_vWorld);
	m_pTakeUpChar = pChar;

	m_bMouseDIR = m_pTakeUpChar->m_bMouseDIR;
	m_bKeyDIR = TKDIR_N; //m_pTakeUpChar->m_bKeyDIR;
	
	m_pTakeUpChar->m_vPushDIR = D3DXVECTOR2(0,0);
	m_pTakeUpChar->m_vJumpDIR = D3DXVECTOR2(0,0);
	m_pTakeUpChar->m_vFallDIR = D3DXVECTOR2(0,0);

	m_pTakeUpChar->m_dwPushTick = 0;
	m_pTakeUpChar->m_dwJumpTick = 0;
	m_pTakeUpChar->m_dwFallTick = 0;

	m_bCanSelected = TRUE;

	return TRUE;
}
// -------------------------------------------------------
CTClientChar* CTClientPet::TakeDown()
{
	if( !m_pTakeUpChar )
		return NULL;

	CTClientChar* pRet = m_pTakeUpChar;

	MAPOBJECT::iterator itr = m_mapEQUIP.find(m_dwTakeUpPivot);
	if( itr != m_mapEQUIP.end() )
		m_mapEQUIP.erase(itr);

	m_pTakeUpChar->m_wDIR = m_wDIR;
	m_pTakeUpChar->m_wMoveDIR = m_wMoveDIR;
	m_pTakeUpChar->m_wPITCH = m_wPITCH;
	m_pTakeUpChar->m_nDIR = m_nDIR;
	m_pTakeUpChar->m_nPITCH = m_nPITCH;
	m_pTakeUpChar->m_bMouseDIR = m_bMouseDIR;
	m_pTakeUpChar->m_bKeyDIR = m_bKeyDIR;
	m_pTakeUpChar->m_vWorld = m_vWorld;
	m_pTakeUpChar->SetPosition(m_vPosition);

	m_vPushDIR = D3DXVECTOR2(0,0);
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

    bWhipped = 0;
	m_dwTakeUpPivot = 0;
	m_pTakeUpChar->SetRidingPet(NULL);
	m_pTakeUpChar = NULL;
	m_bDrawTalk = FALSE;
	m_bCanSelected = FALSE;
	
	m_fSpeedFactor = 1;

	return pRet;
}
// =======================================================

// =======================================================
BYTE CTClientPet::GetDrawName()
{
	if( !CTClientObjBase::GetDrawName() ||
		!CTClientGame::GetPcNAMEOption() /*||
		m_pTakeUpChar == CTClientGame::GetInstance()->GetMainChar()*/ )
	{
		return FALSE;
	}

	return TRUE;
}
// -------------------------------------------------------
CString CTClientPet::GetTitle()
{
	if( m_pTakeUpChar )
		return m_pTakeUpChar->GetTitle();
	else
		return CString("");
}
// -------------------------------------------------------
CString CTClientPet::GetName()
{
	if( m_pTakeUpChar )
		return m_pTakeUpChar->GetName();
	else
		return m_strPetName;
}
CString CTClientPet::GetUserTitle()
{
	if( m_pTakeUpChar )
		return m_pTakeUpChar->GetUserTitle();
	else
		return CString("");
}
void CTClientPet::CalcFrame(BOOL bUpdate)
{
    if( m_pTakeUpChar ) 
		m_pTakeUpChar->CalcFrame( bUpdate );

	CTClientRecall::CalcFrame( bUpdate );
}
// =======================================================
void CTClientPet::CalcHeight(LPD3DXVECTOR3 pPREV, CTClientMAP *pMAP, DWORD dwTick)
{
	CTClientRecall::CalcHeight(pPREV,pMAP,dwTick);

	if( m_pTakeUpChar )
	{
		m_pTakeUpChar->m_dwDropDamage = m_dwDropDamage;
	}
	else
	{
		if( m_bAction == TA_DEAD )
		{
			m_bAction = TA_DIE;
			m_bACTLevel = CTChart::GetTACTION( TA_DIE )->m_bLevel;
		}
	}

	m_dwDropDamage = 0;
}
// -------------------------------------------------------
void CTClientPet::Render(CD3DDevice *pDevice, CD3DCamera *pCamera)
{


	if( m_pTakeUpChar )
		 m_fSpeedFactor = GetSpeedWhenRiding();
	else
	{
		CTClientGame* pGame = CTClientGame::GetInstance();
		CTClientChar* pMyHost = pGame->FindPC(GetHostID());
		if( !pMyHost )
			m_fSpeedFactor = 1.3f;
		else

			m_fSpeedFactor = pMyHost->m_fSpeedFactor; 
	}

	CTClientRecall::Render(pDevice,pCamera);
}
// =======================================================
/*
FLOAT CTClientPet::GetSpeedWhenRiding()
{
CTClientGame* pGame = CTClientGame::GetInstance();
	CTPetManageDlg* pDlg = static_cast<CTPetManageDlg*>( pGame->GetFrame(TFRAME_PET_MANAGE) );


	//CTPetManageDlg* pDlg = static_cast<CTPetManageDlg*>(CTClientGame::m_vTFRAME[TFRAME_PET_MANAGE]);
/*

	if( m_fBaseSpeedFactor < m_pTakeUpChar->m_fSpeedFactor )
		return m_pTakeUpChar->m_fSpeedFactor;
	else
		return m_fBaseSpeedFactor;

	// �����ڵ� ( ĳ���ͼӵ� + ���ӵ� )
	m_fBaseSpeedFactor_org = m_fBaseSpeedFactor;
	return m_fBaseSpeedFactor * (m_pTakeUpChar->m_fSpeedFactor / m_pTakeUpChar->m_fTDEFAULTSPEED);
	
	if(pDlg->wSedloID != 0)

	{

	
		m_fBaseSpeedFactor = TDEF_SPEED * 1.76f;
m_fBaseSpeedFactor_org = m_fBaseSpeedFactor;

	//	m_fBaseSpeedFactor_org = m_fBaseSpeedFactor;
if( m_fBaseSpeedFactor < m_pTakeUpChar->m_fSpeedFactor )
		return m_pTakeUpChar->m_fSpeedFactor;
	else
	return m_fBaseSpeedFactor;
	}
	else
	{
		m_fBaseSpeedFactor = TDEF_SPEED * 1.50f;
		m_fBaseSpeedFactor_org = m_fBaseSpeedFactor;
		if( m_fBaseSpeedFactor < m_pTakeUpChar->m_fSpeedFactor )
		return m_pTakeUpChar->m_fSpeedFactor;
	else
	return m_fBaseSpeedFactor;

	}
}
*/
FLOAT CTClientPet::GetSpeedWhenRiding()
{
//	CTPetManageDlg* pDlg = static_cast<CTPetManageDlg*>(m_vTFRAME[TFRAME_PET_MANAGE]);


	if( m_fBaseSpeedFactor < m_pTakeUpChar->m_fSpeedFactor )
		return m_pTakeUpChar->m_fSpeedFactor;
	else
		return m_fBaseSpeedFactor;

	// �����ڵ� ( ĳ���ͼӵ� + ���ӵ� )
	m_fBaseSpeedFactor_org = m_fBaseSpeedFactor;
	return m_fBaseSpeedFactor * (m_pTakeUpChar->m_fSpeedFactor / m_pTakeUpChar->m_fTDEFAULTSPEED);
	
	//if(wSedloID != 0)
}

void CTClientPet::SetSpeedWhenRiding(WORD wMulti)
{
	if(wMulti == 1 || wMulti == 0)
	{
		m_fBaseSpeedFactor = m_fBaseSpeedFactor - m_fBaseSpeedFactor_org;
		m_fBaseSpeedFactor_org = 0;
	




		D3DXVECTOR3 vDIR( 0.0f, 0.0f, -(1.3f * 10));
		D3DXMATRIX vROT;

		D3DXMatrixRotationY(
			&vROT,
			FLOAT(m_wMoveDIR) * D3DX_PI / 900.0f);

		CTMath::Transform(
			&vROT,
			&vDIR);

		m_vJumpDIR.x = vDIR.x;
		m_vJumpDIR.y = vDIR.z;
		

	}
	else
	{
		m_fBaseSpeedFactor_org = m_fBaseSpeedFactor * 0.5f;
		m_fBaseSpeedFactor = m_fBaseSpeedFactor * 1.5f;

		D3DXVECTOR3 vDIR( 0.0f, 0.0f, -((1.3f * 10) + m_fBaseSpeedFactor));
		D3DXMATRIX vROT;

		D3DXMatrixRotationY(
			&vROT,
			FLOAT(m_wMoveDIR) * D3DX_PI / 900.0f);

		CTMath::Transform(
			&vROT,
			&vDIR);

	
		m_vJumpDIR.x = vDIR.x;
		m_vJumpDIR.y = vDIR.z;
		
	
	}
	
}

void CTClientPet::ShowSFX()
{
	if( m_pTakeUpChar )
		m_pTakeUpChar->ShowSFX();
	CTClientRecall::ShowSFX();
}

void CTClientPet::HideSFX()
{
	if( m_pTakeUpChar )
		m_pTakeUpChar->HideSFX();
	CTClientRecall::HideSFX();
}

BYTE CTClientPet::CheckFall( CTClientMAP *pMAP,
							 LPD3DXVECTOR2 pFallDIR)
{
	return m_pTakeUpChar ? CTClientMoveObj::CheckFall( pMAP, pFallDIR) : CTClientRecall::CheckFall( pMAP, pFallDIR);
}
