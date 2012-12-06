#pragma once
#include "afxcmn.h"


// CBF_Guan_Dlg 对话框

class CBF_Guan_Dlg : public CDialog
{
	DECLARE_DYNAMIC(CBF_Guan_Dlg)

public:
	CBF_Guan_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBF_Guan_Dlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BF_Guan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_BF_Guan_BFNo;
	CString m_BF_Guan_KNo;
	CString m_BF_Guan_BFAcc;
	CListCtrl m_List_Guan;
	CString m_BF_Guan_Del;
	BOOL OnInitDialog(void);

	_ConnectionPtr m_pConnection;//connection object's pointer 
	_CommandPtr m_pCommand; //command object's pointer
	//_ParameterPtr m_pParameter; //Parameter object's pointer
	_RecordsetPtr m_pRecordset;

	afx_msg void OnBnClickedButtonBfGuanInsert();
	afx_msg void OnBnClickedButtonBfGuanDel();
};
