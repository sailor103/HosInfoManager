#pragma once
#include "afxcmn.h"


// CBR_Cha_Dlg �Ի���

class CBR_Cha_Dlg : public CDialog
{
	DECLARE_DYNAMIC(CBR_Cha_Dlg)

public:
	CBR_Cha_Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBR_Cha_Dlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BR_Cha };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	CString m_BR_Cha_In;
	CListCtrl m_List_Cha;

    _ConnectionPtr m_pConnection;//connection object's pointer 
	_CommandPtr m_pCommand; //command object's pointer
	//_ParameterPtr m_pParameter; //Parameter object's pointer
	_RecordsetPtr m_pRecordset;
	afx_msg void OnBnClickedButtonBrCha();
};
