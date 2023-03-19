#pragma once


class CTClientSession : public CTachyonSession
{
public:
	BYTE m_bSvrID;
	BYTE m_bSVR;
	BYTE m_bLogicalValid; // ���� ��ȿ��

// Msg Sender
public:
	void SendCS_DISCONNECT_REQ();
	void SendCS_CONNECT_REQ(
		WORD wVersion,
		BYTE bChannel,
		DWORD dwUserID,
		DWORD dwCharID,
		DWORD dwKEY,
		DWORD dwIPAddr,
		WORD wPort);

	void SendCS_ATTACK_REQ(
		DWORD dwTargetID,
		BYTE bTargetType,
		DWORD dwActID,
		DWORD dwAniID);

	void SendCS_MOVEITEM_REQ(
		BYTE bInvenSRC,
		BYTE bSRCItemID,
		BYTE bInvenDEST,
		BYTE bDESTItemID,
		BYTE bCount);

	void SendCS_CHGMODERECALLMON_REQ(
		DWORD dwMonID,
		BYTE bMode);

	void SendCS_CHGMODE_REQ(
		BYTE bMode);

	void SendCS_DELRECALLMON_REQ(
		DWORD dwMonID, 
		BYTE bMonType);

	void SendCS_CORPSASK_REQ(
		CString strTargetID);

	void SendCS_CORPSREPLY_REQ(
		CString strReqNAME,
		BYTE bReply);

	void SendCS_CORPSLEAVE_REQ(
		WORD wSquadID);

	void SendCS_CORPSCMD_REQ(
		WORD wSquadID,
		DWORD dwCharID,
		WORD wMapID,
		BYTE bCMD,
		DWORD dwTargetID,
		BYTE bTargetType,
		WORD wTargetX,
		WORD wTargetZ);

	void SendCS_CORPSENEMYLIST_REQ(
		WORD wSquadID,
		DWORD dwCharID,
		LPTCORPS pTCORPS);

	void SendCS_MOVECORPSENEMY_REQ(
		DWORD dwReporterID,
		CTClientMoveObj *pTOBJ,
		WORD wMapID);

	void SendCS_MOVECORPSUNIT_REQ(
		WORD wSquadID,
		WORD wMapID,
		DWORD dwBspID,
		CTClientMoveObj *pTOBJ);

	void SendCS_ADDCORPSENEMY_REQ(
		DWORD dwReporterID,
		WORD wMapID,
		CTClientMoveObj *pTOBJ);

	void SendCS_DELCORPSENEMY_REQ(
		DWORD dwReporterID,
		DWORD dwEnemyID,
		BYTE bEnemyType);

	void SendCS_CORPSHP_REQ(
		WORD wSquadID,
		DWORD dwCharID,
		DWORD dwMaxHP,
		DWORD dwHP);

	void SendCS_CHGCORPSCOMMANDER_REQ(
		WORD wSquadID);

	void SendCS_CHGPARTYCHIEF_REQ(
		DWORD dwTargetID);

	void SendCS_PARTYADD_REQ(
		CString strTargetID,
		BYTE bObtainType);

	void SendCS_PARTYJOIN_REQ(
		CString strReqNAME,
		BYTE bObtainType,
		BYTE bReply);

	void SendCS_PARTYDEL_REQ(
		DWORD dwMemberID);

	void SendCS_PARTYMOVE_REQ(
		CString strMoveNAME,
		CString strTargetNAME,
		WORD wPartyID);

	void SendCS_CHGPARTYTYPE_REQ(
		BYTE bPartyItemType);

	void SendCS_CHAT_REQ(
		CString strSender,
		BYTE bGroup,
		DWORD dwTargetID,
		CString strNAME,
		CString strMSG,
		BYTE bCountry,
		MAPPLAYER & mapTarget);

	void SendCS_NPCITEMLIST_REQ(
		WORD wNpcID);

	void SendCS_ITEMBUY_REQ(
		WORD wNpcID,
		DWORD dwQuestID,
		WORD wItemID,
		BYTE bCount,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

#ifdef MAGICITEMSHOP
	void SendCS_MAGICITEMBUY_REQ(
		 WORD wNpcID,
		 DWORD dwMagicItemID,
		 BYTE bCount,
		 BYTE bNpcInvenID,
		 BYTE bNpcItemID );
#endif

	void SendCS_MONSTERBUY_REQ(
		WORD wNpcID,
		WORD wItemID
		);

	void SendCS_ITEMSELL_REQ(
		BYTE bInvenID,
		BYTE bSlotID,
		BYTE bCount,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

	void SendCS_HOTKEYADD_REQ(
		BYTE bType,
		WORD wID,
		BYTE bSetID,
		BYTE bSlotID);

	void SendCS_HOTKEYDEL_REQ(
		BYTE bSetID,
		BYTE bSlotID);

	void SendCS_QUESTEXEC_REQ(
		DWORD dwQuestID,
		BYTE bRewardType,
		DWORD dwRewardID);

	void SendCS_QUESTDROP_REQ(
		DWORD dwQuestID);

	void SendCS_KICKOUT_REQ(
		DWORD dwCharID);

	void SendCS_NPCTALK_REQ(
		WORD wNpcID);

	void SendCS_TELEPORT_REQ(
		WORD wPotalID,
		WORD wNpcID = 0);
    void SendCS_CHECKLOTEND_REQ(DWORD dwCharID);
	void SendCS_INVENADD_REQ(
		BYTE bSlotID,
		BYTE bInvenID,
		BYTE bItemID);

	void SendCS_INVENDEL_REQ(
		BYTE bSlotID,
		BYTE bInvenID,
		BYTE bPosID);

	void SendCS_INVENMOVE_REQ(
		BYTE bSRCSlotID,
		BYTE bDESTSlotID);

	void SendCS_HELMETHIDE_REQ(
		BYTE bHide);

	void SendCS_SKILLBUY_REQ(
		WORD wNpcID,
		WORD wSkillID );

	void SendCS_CANCELSKILL_REQ(
		BYTE bType,
		DWORD dwID,
		WORD wSkillID);

	void SendCS_SKILLINIT_REQ(
		WORD wSkillID,
		BYTE bInvenID,
		BYTE bSlotID);

	void SendCS_SKILLINITPOSSIBLE_REQ(
		BYTE bInvenID,
		BYTE bSlotID);

	void SendCS_SWITCHCHANGE_REQ(
		DWORD dwSwitchID);

	void SendCS_SETRETURNPOS_REQ(
		WORD wNpcID);

	void SendCS_DEALITEMASK_REQ(
		CString strTARGET);

	void SendCS_DEALITEMRLY_REQ(
		BYTE bReply,
		CString strReqNAME);

	void SendCS_DEALITEM_REQ(
		BYTE bOkey);

	void SendCS_ITEMUPGRADE_REQ( 
		BYTE bUpInvenID,
		BYTE bUpSlotID,
		BYTE bMatInvenID,
		BYTE bMatSlotID,
		WORD wNpcID,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash,
		WORD wColor );

	void SendCS_STOREOPEN_REQ(
		CString strName,
		BYTE bCount,
		LPPRVSHOP_ITEM pItem);

	void SendCS_STORECLOSE_REQ();

	void SendCS_STOREITEMLIST_REQ(
		CString strTarget );

	void SendCS_STOREITEMBUY_REQ(
		CString strTarget,
		BYTE bItem,
		BYTE bItemCount);

	void SendCS_FRIENDASK_REQ(
		CString strInvitee);

	void SendCS_FRIENDREPLY_REQ(
		CString strInviter,
		BYTE bReply);

	void SendCS_FRIENDERASE_REQ(
		DWORD dwFriendID);

	void SendCS_FRIENDGROUPMAKE_REQ(
		BYTE bGroup,
		CString strName);

	void SendCS_FRIENDGROUPDELETE_REQ(
		BYTE bGroupID);

	void SendCS_FRIENDGROUPCHANGE_REQ(
		DWORD dwFriend,
		BYTE bWantedGroup);

	void SendCS_FRIENDGROUPNAME_REQ(
		BYTE bGroup,
		CString strName);

	void SendCS_TMSINVITE_REQ(
		DWORD dwTMS, 
		const VECTORDWORD& vTARGET);

	void SendCS_TMSSEND_REQ(
		DWORD dwTMS,
		CString strMessage);

	void SendCS_TMSOUT_REQ(
		DWORD dwTMS);

	void SendCS_PROTECTEDADD_REQ(
		CString strProtected);

	void SendCS_PROTECTEDOPTION_REQ(
		DWORD dwCharID,
		BYTE bOption);

	void SendCS_PROTECTEDERASE_REQ(
		CString strProtected);

	void SendCS_POSTSEND_REQ(
		CString strTarget,
		CString strTitle,
		CString strMessage,
		BYTE bType,
		DWORD dwGold,
		DWORD dwSilver,
		DWORD dwCooper,
		BYTE bInvenID,
		BYTE bSlotID);

	void SendCS_POSTVIEW_REQ(
		DWORD dwPostID);

	void SendCS_POSTDEL_REQ(
		DWORD dwPostID);

	void SendCS_POSTGETITEM_REQ(
		DWORD dwPostID);

	void SendCS_POSTRETURN_REQ(
		DWORD dwPostID,
		BYTE bReturnType);

	void SendCS_PETMAKE_REQ(
		BYTE bInven,
		BYTE bSlot,
		CString szName);

	void SendCS_PETDEL_REQ(
		WORD wPetID);

	void SendCS_PETRECALL_REQ(
		WORD wPetID);

	void SendCS_PETRIDING_REQ(
		DWORD dwMonID, 
		BOOL bRide);
void SendCS_CHGTITLE_REQ(
		WORD wCharTitleID,
		CString strCharTitle);
	//END
	void SendCS_OTHERSELF_REQ(
		DWORD dwHostID,
		DWORD dwOtherSelfMonID);

	void SendCS_CHGCHANNEL_REQ(
		BYTE bChannel);

	void SendCS_CABINETPUTIN_REQ(	
		BYTE bCabinetID,
		BYTE bInven,
		BYTE bItemID,
		BYTE bCount,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

	void SendCS_CABINETTAKEOUT_REQ( 
		BYTE bCabinetID,
		DWORD dwStItemID,
		BYTE bCount,
		BYTE bInvenID,
		BYTE bItemID,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

	void SendCS_CABINETLIST_REQ();

	void SendCS_CABINETITEMLIST_REQ(
		BYTE bCabinetID);

	void SendCS_CABINETOPEN_REQ(
		BYTE bCabinetID);

	void SendCS_DUELINVITE_REQ(
		DWORD dwTarget);
	void SendCS_CHGTITLE_REQ(
		WORD wCharTitleID);
	void SendCS_DUELINVITEREPLY_REQ(
		BYTE bResult, 
		DWORD dwInviter);

	void SendCS_DUELEND_REQ();

	void SendCS_GETTARGET_REQ(
		DWORD dwCharID);

	void SendCS_GETTARGETANS_REQ(
		DWORD dwAnswerCharID,
		DWORD dwTargetID, 
		BYTE bTargetType);

	void SendCS_SMSSEND_REQ(
		BYTE bInvenID,
		BYTE bItemID,
		BYTE bType,
		CString strTargetName,
		CString strMessage);

	void SendCS_GUILDESTABLISH_REQ(
		CString strName);

	void SendCS_GUILDDISORGANIZATION_REQ(
		BOOL bCancel);

	void SendCS_GUILDINVITE_REQ(
		CString strTargetChar);

	void SendCS_GUILDINVITEANSWER_REQ(
		BYTE bAnswer,
		DWORD dwInviterID);

	void SendCS_GUILDLEAVE_REQ();

	void SendCS_GUILDKICKOUT_REQ(
		CString strTargetChar );

	void SendCS_GUILDDUTY_REQ(
		CString strTargetChar,
		BYTE bDuty );

	void SendCS_GUILDMEMBERLIST_REQ();

	void SendCS_GUILDPEER_REQ(
		CString strTargetChar,
		BYTE bPeer );

	void SendCS_GUILDINFO_REQ();

	// < ��� ���� �� / �Ҽ� ������ ���� > ���� : ��� UI������
	void SendCS_GUILDLOCALLIST_REQ();

	// < ��� ���� ���� ���� �ݳ� > ���� : ��� UI������
	void SendCS_GUILDLOCALRETURN_REQ(
		WORD wID);		// ���� �� (���־��̵�) / ������(���þ��̵�)

	// < ��� â�� ��� >
	void SendCS_GUILDCABINETLIST_REQ();

	// < ��� â�� ������ �ֱ� >
	void SendCS_GUILDCABINETPUTIN_REQ(
		BYTE bInvenID,	// �ڽ��� �κ����̵�
		BYTE bItemID,
		BYTE bCount);

	// < ��� â�� ������ ���� >
	void SendCS_GUILDCABINETTAKEOUT_REQ(
		DWORD dwItemID, // ��� â���� ������ ���̵�
		BYTE bCount,
		BYTE bInvenID,
		BYTE bItemID);

	// < ��� ����ġ / �ڱ� ��� >
	void SendCS_GUILDCONTRIBUTION_REQ(
		DWORD dwExp,	// ����ġ
		DWORD dwGold,	// �� (1������ 1�糪�̻�)
		DWORD dwSilver,
		DWORD dwCooper,
		DWORD dwPvPoint );

	// < ��� �������� ���� > ���� : ��� UI������
	void SendCS_GUILDARTICLELIST_REQ();

	// < ��� �������� ���/���� > ���� : �α���� �̻� / ��� UI������
	void SendCS_GUILDARTICLEADD_REQ(
		CString strTitle,
		CString strArticle);

	void SendCS_GUILDARTICLEDEL_REQ(
		DWORD dwID);

	// < ������� ���� ��� > ���� : ����� / ��� UI������
	void SendCS_GUILDFAME_REQ(
		DWORD dwFame,
		DWORD dwFameColor);

	// < ��� ���� / �뺴�� ���� ���� >
	void SendCS_GUILDWANTEDLIST_REQ();

	void SendCS_GUILDWANTEDADD_REQ(
		DWORD dwID,			// ���οø���-0 / ����-���̵�
		CString strTitle,
		CString strText,
		BYTE bMinLevel,
		BYTE bMaxLevel);

	// < ��� ���� / �뺴�� ���� �ø��� - ����� > ���� : �α���� �̻�
	void SendCS_GUILDWANTEDDEL_REQ(
		DWORD dwID);

	// < ��� ��û ������ ��� > ���� : ��� UI������ 
	void SendCS_GUILDVOLUNTEERLIST_REQ();

	void SendCS_GUILDVOLUNTEERING_REQ(
		DWORD dwID);		// ��� �������� ���̵�

	void SendCS_GUILDVOLUNTEERINGDEL_REQ();
    
	// < ��� �뺴 ����Ʈ > ���� : ��� UI������
	void SendCS_GUILDTACTICSLIST_REQ();

	// < ��� �뺴 �ʴ� >
	void SendCS_GUILDTACTICSINVITE_REQ(
		CString strName,
		BYTE bDay,
		DWORD dwPoint,
		DWORD dwGold,
		DWORD dwSilver,
		DWORD dwCooper );

	void SendCS_GUILDTACTICSANSWER_REQ(
		BYTE bAnswer,
		CString strInviter,
		BYTE bDay,
		DWORD dwPoint,
		DWORD dwGold,
		DWORD dwSilver,
		DWORD dwCooper );

	// < ��� �뺴 ���� >
	void SendCS_GUILDTACTICSWANTEDADD_REQ(
		DWORD dwID,			//���οø���-0 / ����-���̵�
		CString strTitle,		//����
		CString strText,		//����
		BYTE bDay,			//�Ⱓ
		BYTE bMinLevel,		//�ּҷ���
		BYTE bMaxLevel,		//�ִ뷹��
		DWORD dwPoint,		//����
		DWORD dwGold,
		DWORD dwSilver,
		DWORD dwCooper);

	void SendCS_GUILDTACTICSWANTEDDEL_REQ(
		//DWORD dwGuildID,
		DWORD dwID );

	void SendCS_GUILDTACTICSWANTEDLIST_REQ();
	void SendCS_GUILDTACTICSVOLUNTEERING_REQ(
		DWORD dwGuildID,
		DWORD dwID );

	void SendCS_GUILDTACTICSVOLUNTEERINGDEL_REQ();
	void SendCS_GUILDTACTICSREPLY_REQ(
		DWORD dwCharID,
		BYTE bReply );
	void SendCS_GUILDTACTICSKICKOUT_REQ(
		DWORD dwCharID );

	// < ��� �������� ����> ���� : �α���� �̻� / ��� UI������
	void SendCS_GUILDARTICLEUPDATE_REQ(
		DWORD dwID,
		CString strTitle,
		CString strArticle);

	void SendCS_GUILDTACTICSAPPANSWER_REQ(
		BYTE bAnswer,
		CString strInviter,
		DWORD dwRune,
		DWORD dwLuna,
		DWORD dwCron);

	void SendCS_GUILDTACTICSVOLUNTEERLIST_REQ();

	void SendCS_CASTLEAPPLY_REQ(
		WORD wCastleID,
		DWORD dwTarget);

	void SendCS_PARTYMEMBERRECALL_REQ(
		BYTE bInvenID,
		BYTE bItemID,
		CString strTarget);

	void SendCS_PARTYMEMBERRECALLANS_REQ(
		BYTE bAnswer,
		CString strInviter,
		BYTE bInvenID,
		BYTE bItemID);

	void SendCS_CASHITEMCABINET_REQ();

	void SendCS_CASHITEMGET_REQ(
		DWORD dwID,
		BYTE bInvenID,
		BYTE bItemID);

	void SendCS_CASHSHOPITEMLIST_REQ(
		WORD wItemID=0,
		BYTE bInvenID=0,
		BYTE bSlotID=0);
	void SendCS_BOWREG_REQ(
		DWORD dwID);
	void SendCS_CASHITEMBUY_REQ(
		WORD wCashItemID);

	void SendCS_CASHITEMPRESENT_REQ(
		CString strTarget,
		WORD wCashItemID);

	void SendCS_SOULMATESEARCH_REQ(
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

	void SendCS_SOULMATEREGREADY_REQ(
		CString strName,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

	void SendCS_SOULMATEREG_REQ(
		CString strName,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

	void SendCS_SOULMATEEND_REQ();

	void SendCS_GAMBLECHECK_REQ(
		BYTE bInven,
		BYTE bSlotID,
		WORD wNpcID);

	void SendCS_GAMBLEOPEN_REQ(
		BYTE bInven,
		BYTE bSlotID,
		WORD wNpcID,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash );

	void SendCS_TAKEGODBALL_REQ(
		WORD wGodBallID);

	void SendCS_MOUNTGODBALL_REQ(
		WORD wGodTower);

	void SendCS_DEMOUNTGODBALL_REQ(
		WORD wGodTower);

	// ������ ����
	void SendCS_DURATIONREP_REQ(
		BYTE bNeedCost,		// FALSE:���� TRUE:����û
		BYTE bType,			// 0:�Ϲݼ���, 1:������ 2:���μ���
		BYTE bInven,		// �Ϲݼ����� ���
		BYTE bItemID,
		WORD wNpcID,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash);

	// ������ ����
	void SendCS_REFINE_REQ(
		BYTE bNeedCost,		// FALSE:���� TRUE:����û
		BYTE bInven,
		BYTE bItemID,
		WORD wNpcID,
		BYTE bInvenIDofOpenCash,
		BYTE bSlotIDofOpenCash,
		LPTINVENITEM_ARRAY pAddItems);
		
	void SendCS_ACTEND_REQ();

	void SendCS_CASHCABINETBUY_REQ(
		WORD wShoptItemID );

	void SendCS_CASHITEMPUTIN_REQ(
		BYTE bInvenID,
		BYTE bItemID);

	void SendCS_HEROSELECT_REQ(
		WORD wBattleZoneID,
		CString strHeroName);

	void SendCS_HEROLIST_REQ();

	void SendCS_CHANGENAME_REQ(
		BYTE bInvenID,
		BYTE bItemID,
		CString szName);

	void SendCS_STOPTHECLOCK_REQ(
		BYTE bInven,
		BYTE bItem, //������ ��� INVALID_SLOT
		WORD wShopItemID);

	void SendCS_CHECKRELAY_REQ();

	void SendCS_GUILDPOINTLOG_REQ();

	void SendCS_GUILDPOINTREWARD_REQ(
		CString strTarget,
		DWORD dwPoint,
		CString strMessage);

	void SendCS_GUILDPVPRECORD_REQ();

	void SendCS_PVPRECORD_REQ(
		BYTE bType );

	void SendCS_FRIENDLIST_REQ();
	void SendCS_ITEMCHANGE_REQ( BYTE bInvenID, BYTE bItemID );

	// Auction Item List.
	void SendCS_AUCTIONFIND_REQ( LPTAUCTIONFINDINFO pFindInfo );
	void SendCS_AUCTIONREGLIST_REQ( LPTAUCTIONFINDINFO pFindInfo );
	void SendCS_AUCTIONBIDLIST_REQ( LPTAUCTIONFINDINFO pFindInfo );
	void SendCS_AUCTIONINTERESTLIST_REQ( LPTAUCTIONFINDINFO pFindInfo );

	void SendCS_AUCTIONBID_REQ( WORD wNpcID, DWORD dwAuctionID, __int64 ldwBidPrice );
	void SendCS_AUCTIONBUYDIRECT_REQ( WORD wNpcID, DWORD dwAuctionID, BYTE bCount );
	void SendCS_AUCTIONREG_REQ( LPTAUCTIONREGINFO pInfo );
	void SendCS_AUCTIONREGCANCEL_REQ( WORD wNpcID, DWORD dwAuctionID );
	void SendCS_AUCTIONINTEREST_REQ( BYTE bType, DWORD dwAuctionID, WORD wNpcID );

	// Fame Rank
	void SendCS_FAMERANKLIST_REQ( BYTE bType, BYTE bMonth );
	void SendCS_MONTHRANKLIST_REQ();	
	void SendCS_WARLORDSAY_REQ( BYTE bType, CString strSay );
	void SendCS_FIRSTGRADEGROUP_REQ();
	
	//Send Relay Only///////////////////////////////////////
	void SendCS_RELAYCHARDATA_REQ(
		WORD wVersion,
		DWORD dwCharID,
		CString strName);
	void SendCS_RELAYPROTECTEDLIST_REQ(VTSTRING& vName, VTBYTE& vBlockOption);
	void SendCS_RELAYPROTECTEDADD_REQ(CString strName, BOOL bBlockOption );
	void SendCS_RELAYPROTECTEDDEL_REQ(CString strName);
	void SendCS_RELAYPROTECTEDOPTION_REQ(CString strName, BYTE bOption);
	void SendCS_COUNTDOWN_REQ(DWORD dwCommand);
	////////////////////////////////////////////////////////

	void SendCS_WASTEREFINE_REQ( BYTE bInvenID, BYTE bItemID );
	void SendCS_SADDLE_REQ( BYTE bInvenID, BYTE bItemID );
	void SendCS_PETCANCEL_REQ();

	void SendCS_APEXSTART_REQ( long re );
	static long SnedCS_APEXDATA_REQ( const char * pBuffer, int nLen );

	void SendCS_KICKOUTMAP_REQ();
	void SendCS_REGGUILDCLOAK_REQ( BYTE bInvenID, BYTE bItemID, BYTE bReg );

	void SendCS_GUILDVOLUNTEERREPLY_REQ(
		DWORD dwCharID,
		BYTE bReply );

	void SendCS_CHATBAN_REQ(CString strName, WORD wMin);
	void SendCS_POSTLIST_REQ(WORD wPage);
#ifdef ADD_TOURNAMENT
	void SendCS_TOURNAMENTAPPLYINFO_REQ();
	void SendCS_TOURNAMENTAPPLY_REQ( BYTE bEntryID );
	void SendCS_TOURNAMENTJOINLIST_REQ();
	void SendCS_TOURNAMENTPARTYLIST_REQ( DWORD dwChiefID );
	void SendCS_TOURNAMENTPARTYADD_REQ( CString strName );
	void SendCS_TOURNAMEMTMATCHLIST_REQ();
	void SendCS_TOURNAMENTEVENTLIST_REQ();
	void SendCS_TOURNAMENTEVENTINFO_REQ( BYTE bEntryID );
	void SendCS_TOURNAMENTEVENTJOIN_REQ( BYTE bEntryID, DWORD dwCharID );
	void SendCS_TOURNAMENTCHEER_REQ( DWORD dwCharID, BYTE bInven, BYTE bSlot );
	void SendCS_TOURNAMENTAPPLYCANCEL_REQ();
	void SendCS_TOURNAMENTPARTYDEL_REQ( DWORD dwTargetID );
	void SendCS_TOURNAMENTSCHEDULE_REQ();
#endif

#ifdef ADD_RPS
	void SendCS_RPSSTART_REQ	( BYTE bType, BYTE bInven, BYTE bItemID );
	void SendCS_RPSGAME_REQ( BYTE bRPS );
#endif

#ifdef KEYHOOK_CTRLALTDEL
	void SendCS_ACDCLOSE_REQ( BYTE bType );
#endif
	
	void SendCS_CHANGECOUNTRY_REQ(
		BYTE bType,
		BYTE bCountry,
		BYTE bInvenID,
		BYTE bItemID );

	void SendCS_WARCOUNTRYBALANCE_REQ();

	void SendCS_MEETINGROOM_REQ(
		BYTE bType,
		BYTE bValue,
		CString strName );

	void SendCS_ARENA_REQ(
		BYTE bCommand, // ( 0:��û, 1:������)
		WORD wNpcID,
		WORD wArenaID );

	void SendCS_CMMOVE_REQ( 
		BYTE bChannel, 
		WORD wMapID, 
		float fPosX, 
		float fPosY, 
		float fPosZ );

	void SendCS_CMMOVETOUSER_REQ( 
		CString strUser );

	void SendCS_CMGIFT_REQ(
		CString strUser,
		WORD wGiftID );

#ifdef ADD_SKYGARDEN
	
	void SendCS_ASSISTANT_REQ(
		CString strTarget );

	void SendCS_ASSISTANTANSWER_REQ(
		BYTE bAnswer,
		CString strInviter );

	void SendCS_ASSISTANTDEL_REQ(
		DWORD dwCharID );

		
#endif
		void SendCS_RESETLOT_REQ(
		DWORD dwCharID );
public:
	CTClientSession();
	virtual ~CTClientSession();
};
