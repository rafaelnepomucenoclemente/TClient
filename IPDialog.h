#pragma once
#include "afxcmn.h"


// CIPDialog ��ȭ �����Դϴ�.

class CIPDialog : public CDialog
{
	DECLARE_DYNAMIC(CIPDialog)

public:
	CIPDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CIPDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_ctrlIP;
	CString m_strIP;
	CString m_strPort;
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
