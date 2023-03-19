#include "stdafx.h"
#include "THotStartDlg.h"
#include "TClientGame.h"
#define ID_CTRLINST_LISTEK			(0x00002140)
CTHotStartDlg::CTHotStartDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
	{
	bSettings = 0;
	bChar = 0;
	bCom = 0;
	bCabinet = 0;
	bPost = 0;
	bWar = 0;


	m_pListx = static_cast<TScroll*>(FindKid(ID_CTRLINST_LISTEK));

	m_pHot1 = static_cast<TImageList*>(FindKid(ID_HOT_1));
	m_pHot2 = static_cast<TImageList*>(FindKid(ID_HOT_2));
	m_pHot3 = static_cast<TImageList*>(FindKid(ID_HOT_3));
	m_pHot4 = static_cast<TImageList*>(FindKid(ID_HOT_4));
	m_pHot5 = static_cast<TImageList*>(FindKid(ID_HOT_5));
	m_pHot6 = static_cast<TImageList*>(FindKid(ID_HOT_6));
	m_pHot7 = static_cast<TImageList*>(FindKid(ID_HOT_7));
	m_pHotBut1 = static_cast<TButton*>(FindKid(ID_HOT_BUT_1));
	m_pHotBut2	 = static_cast<TButton*>(FindKid(ID_HOT_BUT_2));
	m_pHotBut3	 = static_cast<TButton*>(FindKid(ID_HOT_BUT_3));
	m_pHotBut4	 = static_cast<TButton*>(FindKid(ID_HOT_BUT_4));
	m_pHotBut5	 = static_cast<TButton*>(FindKid(ID_HOT_BUT_5));
	m_pHotBut6	 = static_cast<TButton*>(FindKid(ID_HOT_BUT_6));
	m_pHotBut7	 = static_cast<TButton*>(FindKid(ID_HOT_BUT_7));
	m_pHotName1	 = static_cast<TComponent*>(FindKid(ID_HOT_NAME_1));
	m_pHotName2	 = static_cast<TComponent*>(FindKid(ID_HOT_NAME_2));
	m_pHotName3	 = static_cast<TComponent*>(FindKid(ID_HOT_NAME_3));
	m_pHotName4	 = static_cast<TComponent*>(FindKid(ID_HOT_NAME_4));
	m_pHotName5	 = static_cast<TComponent*>(FindKid(ID_HOT_NAME_5));
	m_pHotName6	 = static_cast<TComponent*>(FindKid(ID_HOT_NAME_6));
	m_pHotName7	 = static_cast<TComponent*>(FindKid(ID_HOT_NAME_7));
	m_pTitle = static_cast<TComponent*>(FindKid(ID_CTRLINST_TITLE));
	}

	CTHotStartDlg::~CTHotStartDlg()
	{	
	m_pListx->ShowComponent(FALSE);
	m_pListx->EnableComponent(FALSE);
	}
	BOOL CTHotStartDlg::CanWithItemUI()
	{
		return TRUE;
	}
	HRESULT CTHotStartDlg::Render(DWORD dwTickCount)
	{
	m_pListx->ShowComponent(FALSE);
	return CTClientUIBase::Render(dwTickCount);
	}




	void CTHotStartDlg::EnableWar()
	{
	bWar = 1;
	bSettings = 0;
	bChar = 0;
	bCom = 0;
	bCabinet = 0;
	bPost = 0;
	m_pListx->ShowComponent(FALSE);
	m_pListx->EnableComponent(FALSE);
	m_pHotBut1->ShowComponent(TRUE);
	m_pHotBut1->EnableComponent(TRUE);
	m_pHotBut2->ShowComponent(TRUE);
	m_pHotBut2->EnableComponent(TRUE);
	m_pHotBut3->EnableComponent(FALSE);
	m_pHotBut3->ShowComponent(FALSE);
	m_pHotBut4->EnableComponent(FALSE);
	m_pHotBut5->ShowComponent(FALSE);
	m_pHotBut5->EnableComponent(FALSE);
	m_pHotBut6->ShowComponent(FALSE);
	m_pHotBut6->EnableComponent(FALSE);
	m_pHotBut7->ShowComponent(FALSE);
	m_pHotBut7->EnableComponent(FALSE);

	m_pHotBut1->m_menu[TNM_LCLICK] = GM_GUILD_HOTTERRITORY;
	m_pHotBut2->m_menu[TNM_LCLICK] = GM_TOGGLE_FAMERANK;
		
	m_pHotName1->m_strText = "Válka";
	m_pHotName2->m_strText = "(O) Oltáø Slávy";
	m_pHotName3->m_strText = "";
	m_pHotName4->m_strText = "";
	m_pHotName5->m_strText = "";
	m_pHotName6->m_strText = "";
	m_pHotName7->m_strText = "";
	m_pTitle->m_strText = "Válka";
	m_pHot1->SetCurImage(7);
	m_pHot2->SetCurImage(8);
	m_pHot3->SetCurImage(0);
	m_pHot4->SetCurImage(0);
	m_pHot5->SetCurImage(0);
	m_pHot6->SetCurImage(0);
	m_pHot7->SetCurImage(0);
	}
	void CTHotStartDlg::EnableSettings()
	{
	m_pHotBut1->ShowComponent(TRUE);
	m_pHotBut1->EnableComponent(TRUE);
	m_pHotBut2->ShowComponent(TRUE);
	m_pHotBut2->EnableComponent(TRUE);
	m_pHotBut3->EnableComponent(TRUE);
	m_pHotBut3->ShowComponent(TRUE);
	m_pHotBut4->EnableComponent(TRUE);
	m_pHotBut5->ShowComponent(TRUE);
	m_pHotBut5->EnableComponent(TRUE);
	m_pHotBut6->ShowComponent(TRUE);
	m_pHotBut6->EnableComponent(TRUE);
	m_pHotBut7->ShowComponent(TRUE);
	m_pHotBut7->EnableComponent(TRUE);

	bSettings = 1;
	bChar = 0;
	bCabinet = 0;
	bCom = 0;
	bPost = 0;
	bWar = 0;

	m_pHot1->SetCurImage(23);
	m_pHot2->SetCurImage(24);
	m_pHot3->SetCurImage(25);
	m_pHot4->SetCurImage(26);
	m_pHot5->SetCurImage(27);
	m_pHot6->SetCurImage(28);
	m_pHot7->SetCurImage(29);

	m_pHotBut1->m_menu[TNM_LCLICK] = GM_SYSTEM_SETTING; //ok
	m_pHotBut2->m_menu[TNM_LCLICK] = GM_GAME_SETTING; //ok
	m_pHotBut3->m_menu[TNM_LCLICK] = GM_CONTROL_SETTING; //ok
	m_pHotBut4->m_menu[TNM_LCLICK] = GM_TOGGLE_HELP; //ok
	m_pHotBut5->m_menu[TNM_LCLICK] = GM_TOGGLE_CHAT_LOCK; 
	m_pHotBut6->m_menu[TNM_LCLICK] = GM_SYSTEM;
	m_pHotBut7->m_menu[TNM_LCLICK] = GM_QUIT;


	m_pTitle->m_strText = "Nastavení";
	m_pHotName1->m_strText = "Systém";
	m_pHotName2->m_strText = "Hra";
	m_pHotName3->m_strText = "Klávesnice";
	m_pHotName4->m_strText = "(H) Pomoc";
	
	if(CTClientUIBase::m_bDragLock == 1)
	{
	m_pHotName5->m_strText = "Odemknout UI";
	}
	else
	{
		m_pHotName5->m_strText = "Uzamknout UI";
	}
	
	m_pHotName6->m_strText = "Volba postavy";
	m_pHotName7->m_strText = "Ukonèit hru";

	}

	void CTHotStartDlg::EnableCabinet()
	{
		m_pTitle->m_strText = "Postava";
	m_pHotBut1->ShowComponent(TRUE);
	m_pHotBut1->EnableComponent(TRUE);
	m_pHotBut2->ShowComponent(TRUE);
	m_pHotBut2->EnableComponent(TRUE);
	m_pHotBut3->ShowComponent(FALSE);
	m_pHotBut3->EnableComponent(FALSE);
	m_pHotBut3->ShowComponent(FALSE);
	m_pHotBut4->EnableComponent(FALSE);
	m_pHotBut5->ShowComponent(FALSE);
	m_pHotBut5->EnableComponent(FALSE);
	m_pHotBut6->ShowComponent(FALSE);
	m_pHotBut6->EnableComponent(FALSE);
	m_pHotBut7->ShowComponent(FALSE);
	m_pHotBut7->EnableComponent(FALSE);

	m_pHotBut1->m_menu[TNM_LCLICK] = GM_TOGGLE_DEFINVEN;
	m_pHotBut2->m_menu[TNM_LCLICK] = GM_TOGGLE_CASH_CAB;


		bCabinet = 1;
		bSettings = 0;
		bPost = 0;
		bChar = 0;
		bWar = 0;
		bCom = 0;
		m_pHot1->SetCurImage(20);
	m_pHot2->SetCurImage(21);
	m_pHot3->SetCurImage(0);
	m_pHot4->SetCurImage(0);
	m_pHot5->SetCurImage(0);
	m_pHot6->SetCurImage(0);
	m_pHot7->SetCurImage(0);
	m_pTitle->m_strText = "Inventáø";
	m_pHotName1->m_strText = "(I) Inventáø";
	m_pHotName2->m_strText = "(,) Archív Obchodu";
	m_pHotName3->m_strText = "";
	m_pHotName4->m_strText = "";
	m_pHotName5->m_strText = "";
	m_pHotName6->m_strText = "";
	m_pHotName7->m_strText = "";
	}
	void CTHotStartDlg::EnableChar()
	{
	m_pHotBut1->ShowComponent(TRUE);
	m_pHotBut1->EnableComponent(TRUE);
	m_pHotBut2->ShowComponent(TRUE);
	m_pHotBut2->EnableComponent(TRUE);
	m_pHotBut3->ShowComponent(TRUE);
	m_pHotBut3->EnableComponent(TRUE);
	m_pHotBut3->ShowComponent(TRUE);
	m_pHotBut4->EnableComponent(TRUE);
	m_pHotBut5->ShowComponent(TRUE);
	m_pHotBut5->EnableComponent(TRUE);
	m_pHotBut6->ShowComponent(FALSE);
	m_pHotBut6->EnableComponent(FALSE);
	m_pHotBut7->ShowComponent(FALSE);
	m_pHotBut7->EnableComponent(FALSE);


	m_pHotBut1->m_menu[TNM_LCLICK] = GM_TOGGLE_CHARINFO;
	m_pHotBut2->m_menu[TNM_LCLICK] = GM_TOGGLE_SKILLINFO;
	m_pHotBut3->m_menu[TNM_LCLICK] = GM_TOGGLE_PETMANAGE;
	m_pHotBut4->m_menu[TNM_LCLICK] = GM_TOGGLE_QUESTINFO;
	m_pHotBut5->m_menu[TNM_LCLICK] = GM_OPEN_PRIVSHOP_FOR_SELL;


	bChar = 1;
	bPost = 0;
	bSettings = 0;
	bCabinet = 0;
	bWar = 0;
	m_pHot1->SetCurImage(13);
	m_pHot2->SetCurImage(14);
	m_pHot3->SetCurImage(16);
	m_pHot4->SetCurImage(18);
	m_pHot5->SetCurImage(19);
	m_pHot6->SetCurImage(0);
	m_pHot7->SetCurImage(0);
	m_pTitle->m_strText = "Postava";
	m_pHotName1->m_strText = "(C) Postava";
	m_pHotName2->m_strText = "(K) Schopnosti";
	m_pHotName3->m_strText = "(P) Zvíøe";
	m_pHotName4->m_strText = "(J) Úkoly";
	m_pHotName5->m_strText = "Vlastní Obchod";
	m_pHotName6->m_strText = "";
	m_pHotName7->m_strText = "";
	}
	void CTHotStartDlg::EnableComm()
	{
		m_pHotBut1->ShowComponent(TRUE);
		m_pHotBut1->EnableComponent(TRUE);
		m_pHotBut2->ShowComponent(TRUE);
		m_pHotBut2->EnableComponent(TRUE);
		m_pHotBut3->ShowComponent(TRUE);
		m_pHotBut3->EnableComponent(TRUE);
		m_pHotBut3->ShowComponent(TRUE);
		m_pHotBut4->EnableComponent(TRUE);
		m_pHotBut4->ShowComponent(TRUE);

		m_pHotBut5->ShowComponent(FALSE);
		m_pHotBut5->EnableComponent(FALSE);
		m_pHotBut6->ShowComponent(FALSE);
		m_pHotBut6->EnableComponent(FALSE);
		m_pHotBut7->ShowComponent(FALSE);
		m_pHotBut7->EnableComponent(FALSE);

		m_pHotBut1->m_menu[TNM_LCLICK] = GM_TOGGLE_COMMUNITY;
		m_pHotBut2->m_menu[TNM_LCLICK] = GM_TOGGLE_MESSENGER;
		m_pHotBut3->m_menu[TNM_LCLICK] = GM_TOGGLE_BLOCKLIST;
		m_pHotBut4->m_menu[TNM_LCLICK] = GM_TOGGLE_ACTLIST;

		bCom = 1;
		bChar = 0;
		bPost = 0;
		bSettings = 0;
		bCabinet = 0;
		bWar = 0;

		m_pHot1->SetCurImage(2);
		m_pHot2->SetCurImage(3);
		m_pHot3->SetCurImage(5);
		m_pHot4->SetCurImage(6);
		m_pHot5->SetCurImage(0);
		m_pHot6->SetCurImage(0);
		m_pHot7->SetCurImage(0);

	m_pTitle->m_strText = "Komunita";
	m_pHotName1->m_strText = "(G) Klan";
	m_pHotName2->m_strText = "Pøítel";
	m_pHotName3->m_strText = "Ignorovat";
	m_pHotName4->m_strText = "Seznam Akcí";
	m_pHotName5->m_strText = "";
	m_pHotName6->m_strText = "";
	m_pHotName7->m_strText = "";
	}


	void CTHotStartDlg::EnablePost()
	{
	m_pHotBut1->ShowComponent(TRUE);
	m_pHotBut1->EnableComponent(TRUE);
	m_pHotBut2->ShowComponent(FALSE);
	m_pHotBut2->EnableComponent(FALSE);
	m_pHotBut3->ShowComponent(FALSE);
	m_pHotBut3->EnableComponent(FALSE);
	m_pHotBut3->ShowComponent(FALSE);
	m_pHotBut4->EnableComponent(FALSE);
	m_pHotBut5->ShowComponent(FALSE);
	m_pHotBut5->EnableComponent(FALSE);
	m_pHotBut6->ShowComponent(FALSE);
	m_pHotBut6->EnableComponent(FALSE);
	m_pHotBut7->ShowComponent(FALSE);
	m_pHotBut7->EnableComponent(FALSE);

		bChar = 0;
		bPost = 1;
		bCom = 0;
		bSettings = 0;
		bCabinet = 0;
		bWar = 0;
	m_pHotBut1->m_menu[TNM_LCLICK] = GM_TOGGLE_MAIL;

	m_pHot1->SetCurImage(10);
	m_pHot2->SetCurImage(0);
	m_pHot3->SetCurImage(0);
	m_pHot4->SetCurImage(0);
	m_pHot5->SetCurImage(0);
	m_pHot6->SetCurImage(0);
	m_pHot7->SetCurImage(0);
	m_pTitle->m_strText = "Pošta";
	m_pHotName1->m_strText = "Dopis";
	m_pHotName2->m_strText = "";
	m_pHotName3->m_strText = "";
	m_pHotName4->m_strText = "";
	m_pHotName5->m_strText = "";
	m_pHotName6->m_strText = "";
	m_pHotName7->m_strText = "";
	}





