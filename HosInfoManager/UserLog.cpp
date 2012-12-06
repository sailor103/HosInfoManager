// UserLog.cpp : 实现文件
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "UserLog.h"


// CUserLog 对话框

IMPLEMENT_DYNAMIC(CUserLog, CDialog)

CUserLog::CUserLog(CWnd* pParent /*=NULL*/)
	: CDialog(CUserLog::IDD, pParent)
	, m_user(_T(""))
	, m_psw(_T(""))
{

}

CUserLog::~CUserLog()
{
}

void CUserLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_user);
	DDX_Text(pDX, IDC_EDIT_PSW, m_psw);
}


BEGIN_MESSAGE_MAP(CUserLog, CDialog)
END_MESSAGE_MAP()


// CUserLog 消息处理程序
