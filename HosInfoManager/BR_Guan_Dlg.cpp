// BR_Guan_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "BR_Guan_Dlg.h"


// CBR_Guan_Dlg �Ի���

IMPLEMENT_DYNAMIC(CBR_Guan_Dlg, CDialog)

CBR_Guan_Dlg::CBR_Guan_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBR_Guan_Dlg::IDD, pParent)
	, m_BR_Guan_BFNo(_T(""))
	, m_BR_Guan_BCNo(_T(""))
	, m_BR_Guan_BRName(_T(""))
	, m_BR_Guan_KNo(_T(""))
	, m_BR_Guan_PNo(_T(""))
	, m_BR_Guan_BRInfo(_T(""))
	, m_BR_Guan_BFNO_Del(_T(""))
	, m_BR_Guan_BCNo_Del(_T(""))
{

}

CBR_Guan_Dlg::~CBR_Guan_Dlg()
{
}

void CBR_Guan_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_BFNo, m_BR_Guan_BFNo);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_BCNo, m_BR_Guan_BCNo);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_BRName, m_BR_Guan_BRName);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_KNo, m_BR_Guan_KNo);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_PNo, m_BR_Guan_PNo);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_BRInfo, m_BR_Guan_BRInfo);
	DDX_Control(pDX, IDC_LIST_BR_Guan, m_List_Guan);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_BFNo_Del, m_BR_Guan_BFNO_Del);
	DDX_Text(pDX, IDC_EDIT_BR_Guan_BCNo_Del, m_BR_Guan_BCNo_Del);
}


BEGIN_MESSAGE_MAP(CBR_Guan_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BR_Guan_Insert, &CBR_Guan_Dlg::OnBnClickedButtonBrGuanInsert)
	ON_BN_CLICKED(IDC_BUTTON_BR_Guan_Del, &CBR_Guan_Dlg::OnBnClickedButtonBrGuanDel)
END_MESSAGE_MAP()


// CBR_Guan_Dlg ��Ϣ�������

BOOL CBR_Guan_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // һ��Ҫ��



	DWORD dwStyle = m_List_Guan.GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	//dwStyle |= LVS_EX_CHECKBOXES; //itemǰ����checkbox�ؼ�
	m_List_Guan.SetExtendedStyle(dwStyle); //������չ���


	//*****���ñ�ͷ***


	m_List_Guan.InsertColumn(0,_T("��Ҫ����"),LVCFMT_LEFT,200); //������
	m_List_Guan.InsertColumn(0,_T("���δ��"),LVCFMT_LEFT,100); //������
	m_List_Guan.InsertColumn(0,_T("��Ŀ"),LVCFMT_LEFT,70); //������
	m_List_Guan.InsertColumn(0,_T("��������"),LVCFMT_LEFT,100); //������
	m_List_Guan.InsertColumn(0,_T("������"),LVCFMT_LEFT,50); //������
	m_List_Guan.InsertColumn(0,_T("������"),LVCFMT_LEFT,50); //������


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

	m_pCommand->CommandText="select * from BingLi"; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_BFNo; 
		_variant_t var_BCNo; 
		_variant_t var_BRName; 
		_variant_t var_KNo; 
		_variant_t var_PNo; 
		_variant_t var_BRInfo; 



		var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
		var_BCNo = m_pRecordset->GetCollect (_T("BL_BCNo")); 
		var_BRName = m_pRecordset->GetCollect (_T("BL_Name")); 
		var_KNo = m_pRecordset->GetCollect (_T("KNo"));
		var_PNo = m_pRecordset->GetCollect (_T("PNo"));
		var_BRInfo = m_pRecordset->GetCollect (_T("BL_Info"));



		CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
		CString t_BCNo =(LPCTSTR)_bstr_t(var_BCNo); 
		CString t_BRName =(LPCTSTR)_bstr_t(var_BRName); 
 		CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
 		CString t_PNo =(LPCTSTR)_bstr_t(var_PNo); 
 		CString t_BRInfo =(LPCTSTR)_bstr_t(var_BRInfo); 
 	



		t_BFNo.TrimRight(); 
		t_BCNo.TrimRight(); 
		t_BRName.TrimRight(); 
		t_KNo.TrimRight();
		t_PNo.TrimRight();
		t_BRInfo.TrimRight();



		int nCount = m_List_Guan.GetItemCount(); 
		int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
		m_List_Guan.SetItemText (nItem,0,t_BFNo); 
		m_List_Guan.SetItemText (nItem,1,t_BCNo); 
		m_List_Guan.SetItemText (nItem,2,t_BRName); 
		m_List_Guan.SetItemText (nItem,3,t_KNo); 
		m_List_Guan.SetItemText (nItem,4,t_PNo); 
		m_List_Guan.SetItemText (nItem,5,t_BRInfo); 



		m_pRecordset->MoveNext(); 
	} 






	return 0;
}

void CBR_Guan_Dlg::OnBnClickedButtonBrGuanInsert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	if(this->m_BR_Guan_BFNo.IsEmpty()||this->m_BR_Guan_BCNo.IsEmpty()||this->m_BR_Guan_BRName.IsEmpty()||this->m_BR_Guan_KNo.IsEmpty()||this->m_BR_Guan_PNo.IsEmpty()||this->m_BR_Guan_BRInfo.IsEmpty())
	{
	    AfxMessageBox(_T("�Բ�������������ݲ�����"));
	}

	else
	{
	
		this->m_List_Guan.DeleteAllItems();//�����ʾ

		CString t_insert=_T("insert into BingLi (BFNo,BL_BCNo,BL_Name,KNo,PNo,BL_Info) values(");

		t_insert+="'";
		t_insert+=this->m_BR_Guan_BFNo;
		t_insert+="','";
		t_insert+=this->m_BR_Guan_BCNo;
		t_insert+="','";
		t_insert+=this->m_BR_Guan_BRName;
		t_insert+="','";
		t_insert+=this->m_BR_Guan_KNo;
		t_insert+="','";
		t_insert+=this->m_BR_Guan_PNo;
		t_insert+="','";
		t_insert+=this->m_BR_Guan_BRInfo;
		t_insert+="')";

		m_pCommand->CommandText=(_bstr_t)t_insert; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from BingLi"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_BFNo; 
			_variant_t var_BCNo; 
			_variant_t var_BRName; 
			_variant_t var_KNo; 
			_variant_t var_PNo; 
			_variant_t var_BRInfo; 



			var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
			var_BCNo = m_pRecordset->GetCollect (_T("BL_BCNo")); 
			var_BRName = m_pRecordset->GetCollect (_T("BL_Name")); 
			var_KNo = m_pRecordset->GetCollect (_T("KNo"));
			var_PNo = m_pRecordset->GetCollect (_T("PNo"));
			var_BRInfo = m_pRecordset->GetCollect (_T("BL_Info"));



			CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
			CString t_BCNo =(LPCTSTR)_bstr_t(var_BCNo); 
			CString t_BRName =(LPCTSTR)_bstr_t(var_BRName); 
 			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
 			CString t_PNo =(LPCTSTR)_bstr_t(var_PNo); 
 			CString t_BRInfo =(LPCTSTR)_bstr_t(var_BRInfo); 
	 	



			t_BFNo.TrimRight(); 
			t_BCNo.TrimRight(); 
			t_BRName.TrimRight(); 
			t_KNo.TrimRight();
			t_PNo.TrimRight();
			t_BRInfo.TrimRight();



			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_BFNo); 
			m_List_Guan.SetItemText (nItem,1,t_BCNo); 
			m_List_Guan.SetItemText (nItem,2,t_BRName); 
			m_List_Guan.SetItemText (nItem,3,t_KNo); 
			m_List_Guan.SetItemText (nItem,4,t_PNo); 
			m_List_Guan.SetItemText (nItem,5,t_BRInfo); 



			m_pRecordset->MoveNext(); 
		} 


	}




}

void CBR_Guan_Dlg::OnBnClickedButtonBrGuanDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);


	if(this->m_BR_Guan_BCNo_Del.IsEmpty()||this->m_BR_Guan_BFNO_Del.IsEmpty())
	{
	    AfxMessageBox(_T("�Բ������������������"));
	}


	else
	{
	
		this->m_List_Guan.DeleteAllItems();//�����ʾ
		CString t_del=_T("delete from BingLi where BFNo='");
		t_del+=this->m_BR_Guan_BFNO_Del;
		t_del+="' and BL_BCNo='";
		t_del+=this->m_BR_Guan_BCNo_Del;
		t_del+="'";
		
		m_pCommand->CommandText=(_bstr_t)t_del; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from BingLi"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_BFNo; 
			_variant_t var_BCNo; 
			_variant_t var_BRName; 
			_variant_t var_KNo; 
			_variant_t var_PNo; 
			_variant_t var_BRInfo; 



			var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
			var_BCNo = m_pRecordset->GetCollect (_T("BL_BCNo")); 
			var_BRName = m_pRecordset->GetCollect (_T("BL_Name")); 
			var_KNo = m_pRecordset->GetCollect (_T("KNo"));
			var_PNo = m_pRecordset->GetCollect (_T("PNo"));
			var_BRInfo = m_pRecordset->GetCollect (_T("BL_Info"));



			CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
			CString t_BCNo =(LPCTSTR)_bstr_t(var_BCNo); 
			CString t_BRName =(LPCTSTR)_bstr_t(var_BRName); 
 			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
 			CString t_PNo =(LPCTSTR)_bstr_t(var_PNo); 
 			CString t_BRInfo =(LPCTSTR)_bstr_t(var_BRInfo); 
	 	



			t_BFNo.TrimRight(); 
			t_BCNo.TrimRight(); 
			t_BRName.TrimRight(); 
			t_KNo.TrimRight();
			t_PNo.TrimRight();
			t_BRInfo.TrimRight();



			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_BFNo); 
			m_List_Guan.SetItemText (nItem,1,t_BCNo); 
			m_List_Guan.SetItemText (nItem,2,t_BRName); 
			m_List_Guan.SetItemText (nItem,3,t_KNo); 
			m_List_Guan.SetItemText (nItem,4,t_PNo); 
			m_List_Guan.SetItemText (nItem,5,t_BRInfo); 



			m_pRecordset->MoveNext(); 
		} 



	}
	
}
