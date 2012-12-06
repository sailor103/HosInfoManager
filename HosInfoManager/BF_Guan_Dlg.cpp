// BF_Guan_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "BF_Guan_Dlg.h"


// CBF_Guan_Dlg �Ի���

IMPLEMENT_DYNAMIC(CBF_Guan_Dlg, CDialog)

CBF_Guan_Dlg::CBF_Guan_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBF_Guan_Dlg::IDD, pParent)
	, m_BF_Guan_BFNo(_T(""))
	, m_BF_Guan_KNo(_T(""))
	, m_BF_Guan_BFAcc(_T(""))
	, m_BF_Guan_Del(_T(""))
{

}

CBF_Guan_Dlg::~CBF_Guan_Dlg()
{
}

void CBF_Guan_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BF_Guan_BFNo, m_BF_Guan_BFNo);
	DDX_Text(pDX, IDC_EDIT_BF_Guan_KNo, m_BF_Guan_KNo);
	DDX_Text(pDX, IDC_EDIT_BF_Guan_Acc, m_BF_Guan_BFAcc);
	DDX_Control(pDX, IDC_LIST_BF_Guan, m_List_Guan);
	DDX_Text(pDX, IDC_EDIT_BF_Guan_Del, m_BF_Guan_Del);
}


BEGIN_MESSAGE_MAP(CBF_Guan_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BF_Guan_Insert, &CBF_Guan_Dlg::OnBnClickedButtonBfGuanInsert)
	ON_BN_CLICKED(IDC_BUTTON_BF_Guan_Del, &CBF_Guan_Dlg::OnBnClickedButtonBfGuanDel)
END_MESSAGE_MAP()


// CBF_Guan_Dlg ��Ϣ�������

BOOL CBF_Guan_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // һ��Ҫ��

	DWORD dwStyle = m_List_Guan.GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	//dwStyle |= LVS_EX_CHECKBOXES; //itemǰ����checkbox�ؼ�
	m_List_Guan.SetExtendedStyle(dwStyle); //������չ���

	//*****���ñ�ͷ***


	m_List_Guan.InsertColumn(0,_T("��������"),LVCFMT_LEFT,100); //������
	m_List_Guan.InsertColumn(0,_T("�����ƺ�"),LVCFMT_LEFT,100); //������
	m_List_Guan.InsertColumn(0,_T("������"),LVCFMT_LEFT,100); //������



	//*****��ʼ��ADO��******

	::CoInitialize(NULL);// ��ʼ��OLE/COM�⻷��

	try

	{

		// ����Connection����

		m_pConnection.CreateInstance("ADODB.Connection");

		// ���������ַ�����������BSTR�ͻ���_bstr_t����

		_bstr_t strConnect = "Provider=SQLOLEDB;Data Source=SAILOR-THINK;Integrated Security=SSPI;Initial Catalog=BingFangInfoManager";

		m_pConnection->Open(strConnect,"","",adModeUnknown);
        if(m_pConnection!=NULL)
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�"));
		}

	}

	// ��׽�쳣

	catch(_com_error e)

	{

		// ��ʾ������Ϣ

		AfxMessageBox(e.Description());

	}


	//*****��ʼ����ʾ���ݱ����Ϣ****
	
	m_pCommand.CreateInstance(__uuidof(Command)); 
	m_pCommand->ActiveConnection=m_pConnection; 

	m_pCommand->CommandText="select * from BingFang"; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_BFNo; 
		_variant_t var_KNo; 
		_variant_t var_BFAcc; 
	



		var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
		var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
		var_BFAcc = m_pRecordset->GetCollect (_T("BFAccount")); 
		


		CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
		CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
		CString t_BFAcc =(LPCTSTR)_bstr_t(var_BFAcc); 
 		
 	



		t_BFNo.TrimRight(); 
		t_KNo.TrimRight(); 
		t_BFAcc.TrimRight(); 
	



		int nCount = m_List_Guan.GetItemCount(); 
		int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
		m_List_Guan.SetItemText (nItem,0,t_BFNo); 
		m_List_Guan.SetItemText (nItem,1,t_KNo); 
		m_List_Guan.SetItemText (nItem,2,t_BFAcc); 
		


		m_pRecordset->MoveNext(); 
	} 



	return 0;
}

void CBF_Guan_Dlg::OnBnClickedButtonBfGuanInsert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	if(this->m_BF_Guan_KNo.IsEmpty()||this->m_BF_Guan_BFNo.IsEmpty()||this->m_BF_Guan_BFAcc.IsEmpty())
	{
	    AfxMessageBox(_T("�Բ�������������ݲ�����"));
	}
	else
	{
	
		this->m_List_Guan.DeleteAllItems();//�����ʾ

		CString t_insert=_T("insert into BingFang (BFNo,KNo,BFAccount) values(");

		t_insert+="'";
		t_insert+=this->m_BF_Guan_BFNo;
		t_insert+="','";
		t_insert+=this->m_BF_Guan_KNo;
		t_insert+="',";
		t_insert+=this->m_BF_Guan_BFAcc;
		t_insert+=")";

		m_pCommand->CommandText=(_bstr_t)t_insert; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from BingFang"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_BFNo; 
			_variant_t var_KNo; 
			_variant_t var_BFAcc; 
		



			var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
			var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
			var_BFAcc = m_pRecordset->GetCollect (_T("BFAccount")); 
			


			CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
			CString t_BFAcc =(LPCTSTR)_bstr_t(var_BFAcc); 
	 		
	 	



			t_BFNo.TrimRight(); 
			t_KNo.TrimRight(); 
			t_BFAcc.TrimRight(); 
		



			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_BFNo); 
			m_List_Guan.SetItemText (nItem,1,t_KNo); 
			m_List_Guan.SetItemText (nItem,2,t_BFAcc); 
			


			m_pRecordset->MoveNext(); 
		} 



	}
}

void CBF_Guan_Dlg::OnBnClickedButtonBfGuanDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);


	if(this->m_BF_Guan_Del.IsEmpty())
	{
	    AfxMessageBox(_T("�Բ������������������"));
	}

	else
	{
	
		this->m_List_Guan.DeleteAllItems();//�����ʾ

		CString t_del=_T("delete from BingFang where BFNo='");
		t_del+=this->m_BF_Guan_Del;
		t_del+="'";
		
		m_pCommand->CommandText=(_bstr_t)t_del; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from BingFang"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_BFNo; 
			_variant_t var_KNo; 
			_variant_t var_BFAcc; 
		



			var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
			var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
			var_BFAcc = m_pRecordset->GetCollect (_T("BFAccount")); 
			


			CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
			CString t_BFAcc =(LPCTSTR)_bstr_t(var_BFAcc); 
	 		
	 	



			t_BFNo.TrimRight(); 
			t_KNo.TrimRight(); 
			t_BFAcc.TrimRight(); 
		



			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_BFNo); 
			m_List_Guan.SetItemText (nItem,1,t_KNo); 
			m_List_Guan.SetItemText (nItem,2,t_BFAcc); 
			


			m_pRecordset->MoveNext(); 
		} 



	}

}
