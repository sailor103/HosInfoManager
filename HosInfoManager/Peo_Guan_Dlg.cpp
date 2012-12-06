// Peo_Guan_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "Peo_Guan_Dlg.h"


// CPeo_Guan_Dlg �Ի���

IMPLEMENT_DYNAMIC(CPeo_Guan_Dlg, CDialog)

CPeo_Guan_Dlg::CPeo_Guan_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPeo_Guan_Dlg::IDD, pParent)
	, m_Peo_Guan_KNo(_T(""))
	, m_Peo_Guan_PName(_T(""))
	, m_Peo_Guan_PLel(_T(""))
	, m_Peo_Guan_Del(_T(""))
	, m_Peo_Guan_PNo(_T(""))
{

}

CPeo_Guan_Dlg::~CPeo_Guan_Dlg()
{
}

void CPeo_Guan_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_Peo_Guan_KNo, m_Peo_Guan_KNo);
	DDX_Text(pDX, IDC_EDIT_Peo_Guan_PName, m_Peo_Guan_PName);
	DDX_Text(pDX, IDC_EDIT_Peo_Guan_PLel, m_Peo_Guan_PLel);
	DDX_Text(pDX, IDC_EDIT_Peo_Guan_Del, m_Peo_Guan_Del);
	DDX_Control(pDX, IDC_LIST_Peo_Guan, m_List_Guan);
	DDX_Text(pDX, IDC_EDIT_Peo_Guan_PNo, m_Peo_Guan_PNo);
}


BEGIN_MESSAGE_MAP(CPeo_Guan_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Peo_Guan_Insert, &CPeo_Guan_Dlg::OnBnClickedButtonPeoGuanInsert)
	ON_BN_CLICKED(IDC_BUTTON_Peo_Guan_Del, &CPeo_Guan_Dlg::OnBnClickedButtonPeoGuanDel)
END_MESSAGE_MAP()


// CPeo_Guan_Dlg ��Ϣ�������

BOOL CPeo_Guan_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // һ��Ҫ��

    //****����listCTORL���

	DWORD dwStyle = m_List_Guan.GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	//dwStyle |= LVS_EX_CHECKBOXES; //itemǰ����checkbox�ؼ�
	m_List_Guan.SetExtendedStyle(dwStyle); //������չ���

	//*****���ñ�ͷ***


	m_List_Guan.InsertColumn(0,_T("����"),LVCFMT_LEFT,100); //������
	m_List_Guan.InsertColumn(0,_T("����"),LVCFMT_LEFT,100); //������
	m_List_Guan.InsertColumn(0,_T("�����ƺ�"),LVCFMT_LEFT,100); //������
	m_List_Guan.InsertColumn(0,_T("��Ա���"),LVCFMT_LEFT,100); //������

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

	m_pCommand->CommandText="select * from People"; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_PNo; 
		_variant_t var_KNo; 
		_variant_t var_PName; 
		_variant_t var_PLel; 


		var_PNo = m_pRecordset->GetCollect (_T("PNo")); 
		var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
		var_PName = m_pRecordset->GetCollect (_T("PName")); 
		var_PLel = m_pRecordset->GetCollect (_T("PLel"));


		CString t_PNo =(LPCTSTR)_bstr_t(var_PNo); 
		CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
		CString t_PName =(LPCTSTR)_bstr_t(var_PName); 
 		CString t_PLel =(LPCTSTR)_bstr_t(var_PLel); 


		t_PNo.TrimRight(); 
		t_KNo.TrimRight(); 
		t_PName.TrimRight(); 
		t_PLel.TrimRight();


		int nCount = m_List_Guan.GetItemCount(); 
		int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
		m_List_Guan.SetItemText (nItem,0,t_PNo); 
		m_List_Guan.SetItemText (nItem,1,t_KNo); 
		m_List_Guan.SetItemText (nItem,2,t_PName); 
		m_List_Guan.SetItemText (nItem,3,t_PLel); 


		m_pRecordset->MoveNext(); 
	} 



	return 0;
}

void CPeo_Guan_Dlg::OnBnClickedButtonPeoGuanInsert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	if(this->m_Peo_Guan_KNo.IsEmpty()||this->m_Peo_Guan_PNo.IsEmpty()||this->m_Peo_Guan_PName.IsEmpty()||this->m_Peo_Guan_PLel.IsEmpty())
	{
	    AfxMessageBox(_T("�Բ�������������ݲ�����"));
	}



	else
	{
	
		this->m_List_Guan.DeleteAllItems();//�����ʾ

		CString t_insert=_T("insert into People (PNo,KNo,PName,PLel) values(");

		t_insert+="'";
		t_insert+=this->m_Peo_Guan_PNo;
		t_insert+="','";
		t_insert+=this->m_Peo_Guan_KNo;
		t_insert+="','";
		t_insert+=this->m_Peo_Guan_PName;
		t_insert+="','";
		t_insert+=this->m_Peo_Guan_PLel;
		t_insert+="')";

		m_pCommand->CommandText=(_bstr_t)t_insert; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from People"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_PNo; 
			_variant_t var_KNo; 
			_variant_t var_PName; 
			_variant_t var_PLel; 


			var_PNo = m_pRecordset->GetCollect (_T("PNo")); 
			var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
			var_PName = m_pRecordset->GetCollect (_T("PName")); 
			var_PLel = m_pRecordset->GetCollect (_T("PLel"));


			CString t_PNo =(LPCTSTR)_bstr_t(var_PNo); 
			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
			CString t_PName =(LPCTSTR)_bstr_t(var_PName); 
 			CString t_PLel =(LPCTSTR)_bstr_t(var_PLel); 


			t_PNo.TrimRight(); 
			t_KNo.TrimRight(); 
			t_PName.TrimRight(); 
			t_PLel.TrimRight();


			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_PNo); 
			m_List_Guan.SetItemText (nItem,1,t_KNo); 
			m_List_Guan.SetItemText (nItem,2,t_PName); 
			m_List_Guan.SetItemText (nItem,3,t_PLel); 


			m_pRecordset->MoveNext(); 
		} 


	}


}

void CPeo_Guan_Dlg::OnBnClickedButtonPeoGuanDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);


	if(this->m_Peo_Guan_Del.IsEmpty())
	{
	    AfxMessageBox(_T("�Բ������������������"));
	}
	
	else
	{
	
		this->m_List_Guan.DeleteAllItems();//�����ʾ
		CString t_del=_T("delete from People where PNo='");
		t_del+=this->m_Peo_Guan_Del;
		t_del+="'";
		
		m_pCommand->CommandText=(_bstr_t)t_del; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from People"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_PNo; 
			_variant_t var_KNo; 
			_variant_t var_PName; 
			_variant_t var_PLel; 


			var_PNo = m_pRecordset->GetCollect (_T("PNo")); 
			var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
			var_PName = m_pRecordset->GetCollect (_T("PName")); 
			var_PLel = m_pRecordset->GetCollect (_T("PLel"));


			CString t_PNo =(LPCTSTR)_bstr_t(var_PNo); 
			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
			CString t_PName =(LPCTSTR)_bstr_t(var_PName); 
 			CString t_PLel =(LPCTSTR)_bstr_t(var_PLel); 


			t_PNo.TrimRight(); 
			t_KNo.TrimRight(); 
			t_PName.TrimRight(); 
			t_PLel.TrimRight();


			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_PNo); 
			m_List_Guan.SetItemText (nItem,1,t_KNo); 
			m_List_Guan.SetItemText (nItem,2,t_PName); 
			m_List_Guan.SetItemText (nItem,3,t_PLel); 


			m_pRecordset->MoveNext(); 
		} 



	}
}
