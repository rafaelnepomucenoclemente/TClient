// IPDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TClient.h"
#include "IPDialog.h"
#include ".\ipdialog.h"


// CIPDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CIPDialog, CDialog)
CIPDialog::CIPDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CIPDialog::IDD, pParent)
	, m_strPort(_T(""))
{
}

CIPDialog::~CIPDialog()
{
}

void CIPDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIP);
	DDX_Text(pDX, IDC_EDIT1, m_strPort);
}


BEGIN_MESSAGE_MAP(CIPDialog, CDialog)
END_MESSAGE_MAP()


// CIPDialog �޽��� ó�����Դϴ�.

void CIPDialog::OnOK()
{
	UpdateData();
	BYTE a, b, c, d;
	m_ctrlIP.GetAddress(a,b,c,d);
	m_strIP.Format("%d.%d.%d.%d", a,b,c,d);
	CDialog::OnOK();
}

void CIPDialog::OnCancel()
{
	CDialog::OnCancel();
}
