#pragma once


// CUserLog �Ի���

class CUserLog : public CDialog
{
	DECLARE_DYNAMIC(CUserLog)

public:
	CUserLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserLog();

// �Ի�������
	enum { IDD = IDD_DIALOG_Log };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_user;
	CString m_psw;
};
