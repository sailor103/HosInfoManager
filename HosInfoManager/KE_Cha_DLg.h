#pragma once
#include "afxcmn.h"


// CKE_Cha_DLg �Ի���

class CKE_Cha_DLg : public CDialog
{
	DECLARE_DYNAMIC(CKE_Cha_DLg)

public:
	CKE_Cha_DLg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CKE_Cha_DLg();

// �Ի�������
	enum { IDD = IDD_DIALOG_KE_Cha };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_KE_Cha_InStr;
	CListCtrl m_List_Cha;
	virtual BOOL OnInitDialog(void);
	afx_msg void OnBnClickedButtonCha();


	_ConnectionPtr m_pConnection;//connection object's pointer 
	_CommandPtr m_pCommand; //command object's pointer
	//_ParameterPtr m_pParameter; //Parameter object's pointer
	_RecordsetPtr m_pRecordset;

};
