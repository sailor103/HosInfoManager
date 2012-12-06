#pragma once
#include "afxcmn.h"


// CBR_Guan_Dlg 对话框

class CBR_Guan_Dlg : public CDialog
{
	DECLARE_DYNAMIC(CBR_Guan_Dlg)

public:
	CBR_Guan_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBR_Guan_Dlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BR_Guan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_BR_Guan_BFNo;
	CString m_BR_Guan_BCNo;
	CString m_BR_Guan_BRName;
	CString m_BR_Guan_KNo;
	CString m_BR_Guan_PNo;
	CString m_BR_Guan_BRInfo;
	CListCtrl m_List_Guan;
	CString m_BR_Guan_BFNO_Del;
	CString m_BR_Guan_BCNo_Del;
	virtual BOOL OnInitDialog(void);

	_ConnectionPtr m_pConnection;//connection object's pointer 
	_CommandPtr m_pCommand; //command object's pointer
	//_ParameterPtr m_pParameter; //Parameter object's pointer
	_RecordsetPtr m_pRecordset;
	afx_msg void OnBnClickedButtonBrGuanInsert();
	afx_msg void OnBnClickedButtonBrGuanDel();
};
