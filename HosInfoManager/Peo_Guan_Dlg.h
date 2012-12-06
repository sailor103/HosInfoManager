#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPeo_Guan_Dlg 对话框

class CPeo_Guan_Dlg : public CDialog
{
	DECLARE_DYNAMIC(CPeo_Guan_Dlg)

public:
	CPeo_Guan_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPeo_Guan_Dlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Peo_Guan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CString m_Peo_Guan_KNo;
	CString m_Peo_Guan_PName;
	CString m_Peo_Guan_PLel;
	CString m_Peo_Guan_Del;
	BOOL OnInitDialog(void);
	CListCtrl m_List_Guan;

	_ConnectionPtr m_pConnection;//connection object's pointer 
	_CommandPtr m_pCommand; //command object's pointer
	//_ParameterPtr m_pParameter; //Parameter object's pointer
	_RecordsetPtr m_pRecordset;

	afx_msg void OnBnClickedButtonPeoGuanInsert();
	CString m_Peo_Guan_PNo;
	afx_msg void OnBnClickedButtonPeoGuanDel();
};
