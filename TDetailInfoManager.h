#pragma once


// =====================================================================
/**	@class		CTDetailInfoManager
	@brief		������â�� ���� ���� ����, �˻� �� ȭ�� ����� ����Ѵ�.
	
*/// ===================================================================
class CTDetailInfoManager
{
public:
	/// ���� �ֱٿ� ǥ���� ������
	static ITDetailInfoPtr	m_pLastInfo;

	/// ������â�� ǥ���ϱ����� ��ٸ� �ð�.
	static DWORD			m_dwInfoTick;

	/// ������â�� ���콺�� ��ġ�� ������� �����ð� ���� �����ֱ� ���� �ð�.
	static DWORD			m_dwInfoStaticTick;

public:
	static ITDetailInfoPtr NewStatInst(
		DWORD dwInfoID,
		LPTSTATINFO,
		DWORD dwTitleColor,
		const CRect& rc = CRect(0,0,0,0) );

	/// ������ �ν��Ͻ��� �����Ѵ�.
	static ITDetailInfoPtr NewNorInst(
		const CString& strTitle,
		DWORD dwInfoID, 
		WORD wImgID, 
		const CRect& rc = CRect(0,0,0,0));

	/// ��ų ������ �ν��Ͻ��� �����Ѵ�.
	static ITDetailInfoPtr NewSkillInst(
		LPTSKILL pTSkill,
		BYTE bLevel,
		BOOL bSkillReq,
		const CRect& rc = CRect(0,0,0,0));

	/// �Ϲ� ������ ������ �ν��Ͻ��� �����Ѵ�.
	static ITDetailInfoPtr NewItemInst(
		LPTITEM pItem, 
		const CRect& rc = CRect(0,0,0,0));

	/// �־��� �����ۿ� �´� ������ �ν��Ͻ��� �����Ѵ�.
	static ITDetailInfoPtr NewItemInst(
		CTClientItem* pItem,
		const CRect& rc = CRect(0,0,0,0));

	/// �������� �´� ������ �ν��Ͻ��� �����Ѵ�.
	static ITDetailInfoPtr NewTerritoryInst(
		CString strCastle,
		CTime timeNext,
		CString strAtkGuild,
		CString strDefGuild,
		WORD wAtkGuildPoint,
		WORD wAtkCountryPoint,
		BYTE bAtkCount,
		WORD wDefGuildPoint,
		WORD wDefCountryPoint,
		BYTE bDefCount,
		CString strMyGuild,
		WORD wMyGuildPoint,
#ifdef MODIFY_GUILD
		VTOP3* vDTop3,
		VTOP3* vCTop3,
#endif
		const CRect& rc = CRect(0,0,0,0));

	/// ���������� �´� ������ �ν��Ͻ��� �����Ѵ�.
	static ITDetailInfoPtr NewTerritoryInst(
		CString strTerritory,
		CTime timeNext,
		CString strHeroName,
		const CRect& rc = CRect(0,0,0,0));

	static ITDetailInfoPtr NewPvPInst(
		BYTE bTabIndex,
		CString strName,
		BYTE bWin,
		BYTE bClass,
		BYTE bLevel,
		DWORD dwPoint,
		CTime dlDate,
		DWORD dwTitleColor,
		const CRect& rc = CRect(0,0,0,0) );

	static ITDetailInfoPtr NewTextInst(
		CString& strText,
		CPoint pt );

	static ITDetailInfoPtr NewFameInst(
		CString	strName,
		DWORD	dwTotalPoint,
		DWORD	dwMonthPoint,
		WORD	wWin,
		WORD	wLose,
		BYTE	bLevel,
		BYTE	bClass,
		const CRect& rc = CRect(0,0,0,0)
		);

	static ITDetailInfoPtr NewDefTooltipInst(
		CString strTitle,
		CString strTooltip,
		const CRect& rc = CRect(0,0,0,0));

	static ITDetailInfoPtr NewTournamentPlayerInst(
		CString strName,
		BYTE bWin,
		BYTE bCountry,
		BYTE bClass,
		BYTE bLevel,
		const CRect& rc = CRect(0,0,0,0) );

	static ITDetailInfoPtr NewTournamentPlayerInst(
		CString strTitle,
		CString strText,
		int nLine,
		const CRect& rc = CRect(0,0,0,0) );

	static ITDetailInfoPtr NewMissionInst(
		CString strTerritory,
		CTime timeNext,
		BYTE bCountry,
		BYTE bStatus,
		const CRect& rc = CRect(0,0,0,0));

	static ITDetailInfoPtr NewPlayerInst(
		CString strName,
		BYTE bLevel,
		BYTE bRace,
		BYTE bSex,
		BYTE bFace,
		BYTE bHair,
		BYTE bSenior,
		BYTE bClass,
		const CRect& rc = CRect(0,0,0,0));

public:
	static void UpdateTick(DWORD dwTick);
	static void UpdateInfo(const CPoint& pt);
};
