#pragma once
#include "afxcmn.h"


// CPeo_Cha_Dlg �Ի���

class CPeo_Cha_Dlg : public CDialog
{
	DECLARE_DYNAMIC(CPeo_Cha_Dlg)

public:
	CPeo_Cha_Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPeo_Cha_Dlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Peo_Cha };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Peo_Cha_In;
	CListCtrl m_List_Cha;
	BOOL OnInitDialog(void);

    _ConnectionPtr m_pConnection;//connection object's pointer 
	_CommandPtr m_pCommand; //command object's pointer
	//_ParameterPtr m_pParameter; //Parameter object's pointer
	_RecordsetPtr m_pRecordset;


	afx_msg void OnBnClickedButtonPeoCha();
};
