#include "stdafx.h"
#include "TLotteryDlg.h"
#include "TClientGame.h"
#define ID_LNUMBER1 (0x00006650)
#define ID_LNUMBER2 (0x00006651)
#define ID_LNUMBER3 (0x00006652)
#define ID_LNUMBER4 (0x00006653)
#define ID_START_BUT (0x00006654)
CTLotteryDlg::CTLotteryDlg( TComponent *pParent, LP_FRAMEDESC pDesc )
: CTClientUIBase( pParent, pDesc )
{
    static DWORD dwCisla[4] =
	{
        ID_LNUMBER1,
		ID_LNUMBER2,
		ID_LNUMBER3,
		ID_LNUMBER4
	};
	for(int i=0;i<4;++i)
		m_pCisla[i] = static_cast<TComponent*>(FindKid(dwCisla[i]));

	m_pStart =static_cast<TButton*>(FindKid(ID_START_BUT));
	m_pRune = FindKid( ID_CTRLINST_RUNE );
	m_pSilver = FindKid( ID_CTRLINST_LUNA );
	m_pCrons = FindKid( ID_CTRLINST_CRON );
	m_pStart->m_menu[TNM_LCLICK] = GM_LOTTERY_START;

}
BOOL CTLotteryDlg::CanWithItemUI()
{
	return TRUE;
}
void CTLotteryDlg::GenerateNumbers()
{
	/*
	DWORD dwCisla[4];
	CString strCisla[4];
	for(int i=0;i<4;i++)
	{
		dwCisla[i] = rand() % 25 +1; 
		strCisla[i].Format("%d.",dwCisla[i]);
		m_pCisla[i]->m_strText = strCisla[i];
  
  */ //Will generate same numbers

	CString strNum1,strNum2,strNum3,strNum4;
	dwNum1 = rand() % 25+1;
	dwNum2 = rand() % 25+1;
	dwNum3 = rand() % 25+1;
	dwNum4 = rand() % 25+1;
	if(dwNum1 == dwNum2||dwNum1 == dwNum3||dwNum1 == dwNum4)
	{
		m_pStart->m_strText = "1";
		if(dwNum1+1!=dwNum2||dwNum1+1!=dwNum3||dwNum1+1!=dwNum4)
		dwNum1+=1;
		else
        dwNum1+=25;
	}
	if(dwNum2 == dwNum1||dwNum2 == dwNum3||dwNum2 == dwNum4)
	{
		m_pStart->m_strText = "2";
		if(dwNum2+2!=dwNum1||dwNum2+2!=dwNum3||dwNum2+2!=dwNum4)
		dwNum2+=2;
		else
		dwNum2+=26;
	}
	if(dwNum3 == dwNum1||dwNum3 == dwNum2||dwNum3 == dwNum4)
	{
		m_pStart->m_strText = "3";
		if(dwNum3+3!=dwNum1||dwNum3+3!=dwNum2||dwNum3+3!=dwNum4)
		dwNum3+=3;
		else
		dwNum3+=27;
	}
	if(dwNum4 == dwNum1||dwNum4 == dwNum2||dwNum4 == dwNum3)
	{
		m_pStart->m_strText = "4";
		if(dwNum4+4!=dwNum1||dwNum4+4!=dwNum2||dwNum4+4!=dwNum3)
		dwNum4+=4;
		else
		dwNum4+=28;
	}
    strNum1.Format("%d.",dwNum1);
	strNum2.Format("%d.",dwNum2);
	strNum3.Format("%d.",dwNum3);
	strNum4.Format("%d.",dwNum4);
	m_pCisla[0]->m_strText = strNum1;
	m_pCisla[1]->m_strText = strNum2;
	m_pCisla[2]->m_strText = strNum3;
	m_pCisla[3]->m_strText = strNum4;

}
CTLotteryDlg::~CTLotteryDlg()
{

}

