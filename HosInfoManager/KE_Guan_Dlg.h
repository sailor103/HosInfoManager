#pragma once
#include "afxcmn.h"


// CKE_Guan_Dlg 对话框

class CKE_Guan_Dlg : public CDialog
{
	DECLARE_DYNAMIC(CKE_Guan_Dlg)

public:
	CKE_Guan_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKE_Guan_Dlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_KE_Guan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List_Guan;
	CString m_KE_Guan_KNo;
	CString m_KE_Guan_KName;
	CString m_KE_Guan_KTel;
	CString m_KE_Guan_Zhuren;
	CString m_KE_Guan_Hushizhang;
	CString m_KE_Guan_Del;
	BOOL OnInitDialog(void);

	_ConnectionPtr m_pConnection;//connection object's pointer 
	_CommandPtr m_pCommand; //command object's pointer
	//_ParameterPtr m_pParameter; //Parameter object's pointer
	_RecordsetPtr m_pRecordset;

	afx_msg void OnBnClickedButtonKeGuanInsert();
	afx_msg void OnBnClickedButtonKeGuanDel();
};
