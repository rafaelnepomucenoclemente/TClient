#pragma once


//! SiegeManager Class.
/*!
*	@brief	������Ż�� ������ Ŭ����..
*
*	@date	2009/08/21
*	@author	�� ����
*
*/
class CTSiegeManager
{
private :

	CTSiegeManager();
	~CTSiegeManager();

public :	// MEMBER DATA.

	MAPSIEGEGODBALL			m_mapBalls;
	MAPSIEGEGODTOWER		m_mapTowers;

public :	// MEMBER FUNCTION.

	static CTSiegeManager*	GetInstance();

	/*! */
	CTGodBall*				FindGodBall( WORD wGodBallID );
	/*! */
	CTGodTower*				FindGodTower( WORD wGodTowerID );
	/*! Visible */
	void					ResetVisibleOBJ( DWORD dwTick );
	/*! ���� or Ÿ���� ���� �̺�Ʈó��.. */
	void					OnRClick();
	/*! */
	void					ChargeAffterProcess( CTGodTower* pGodTower );
	/*! */
	void					CalcTick( CD3DDevice* pDevice, DWORD dwTick );
	/*! ����ʱ�ȭ.. */
	void					Release();
	/*! ��������.. */
	void					Endwar(
		BYTE bType,
		DWORD dwWinGuildID,
		DWORD dwDefTotal,
		DWORD dwAtkTotal,
		CString strDefName,
		DWORD dwDefPower,
		WORD wDefPoint,
		WORD wDefKillPoint,
		CString strAtkName,
		DWORD dwAtkPower,
		WORD wAtkPoint,
		WORD wAtkKillPoint);

public :	// RECEIVE FUNCTION.

	/*! ������ �����������ų� ���� �����Ǵ� ���.. */
	void					RecvAddGodBall( WORD wBallID, BYTE bCamp, BOOL bInGround, D3DXVECTOR3& vPosition );
	/*! �ش� ĳ���Ϳ��� ������ ����.. */
	void					RecvRemoveGodBall( DWORD dwCharID );
	/*! �ش� ĳ���Ͱ� ������ ����.. */
	void					RecvTakeGodBall( DWORD dwCharID, WORD wBallID );
	/*! ������ �ʿ��� ���ŵ�.. */
	void					RecvDelGodBall( WORD wBallID );
	/*! Ÿ������.. */
	void					RecvAddGodTower( WORD wTowerID, BYTE bCamp, D3DXVECTOR3& vPosition );
	/*! Ÿ������.. */
	void					RecvDelGodTower( WORD wTowerID );
	/*! ĳ���Ͱ� ������ Ÿ���� �Ⱦ���.. */
	void					RecvMountGodBall( WORD wTowerID, WORD wBallID, BYTE bCamp, DWORD dwCharID );
	/*! ���� ĳ���Ͱ� �ش� Ÿ������ ������ ����.. */
	void					RecvDemountGodBall( WORD wTowerID );

};

#define SiegeMgr CTSiegeManager::GetInstance()
