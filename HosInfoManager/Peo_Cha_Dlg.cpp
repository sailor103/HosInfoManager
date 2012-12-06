// Peo_Cha_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "Peo_Cha_Dlg.h"


// CPeo_Cha_Dlg �Ի���

IMPLEMENT_DYNAMIC(CPeo_Cha_Dlg, CDialog)

CPeo_Cha_Dlg::CPeo_Cha_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPeo_Cha_Dlg::IDD, pParent)
	, m_Peo_Cha_In(_T(""))
{

}

CPeo_Cha_Dlg::~CPeo_Cha_Dlg()
{
}

void CPeo_Cha_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Peo_Cha, m_Peo_Cha_In);
	DDX_Control(pDX, IDC_LIST_Peo_Cha, m_List_Cha);
}


BEGIN_MESSAGE_MAP(CPeo_Cha_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Peo_Cha, &CPeo_Cha_Dlg::OnBnClickedButtonPeoCha)
END_MESSAGE_MAP()


// CPeo_Cha_Dlg ��Ϣ�������

BOOL CPeo_Cha_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // һ��Ҫ��
	
	DWORD dwStyle = m_List_Cha.GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	//dwStyle |= LVS_EX_CHECKBOXES; //itemǰ����checkbox�ؼ�
	m_List_Cha.SetExtendedStyle(dwStyle); //������չ���

	
	
	m_List_Cha.InsertColumn(0,_T("���ƵĲ���5"),LVCFMT_LEFT,100); //������
	m_List_Cha.InsertColumn(0,_T("���ƵĲ���4"),LVCFMT_LEFT,100); //������
	m_List_Cha.InsertColumn(0,_T("���ƵĲ���3"),LVCFMT_LEFT,100); //������
	m_List_Cha.InsertColumn(0,_T("���ƵĲ���2"),LVCFMT_LEFT,100); //������
	m_List_Cha.InsertColumn(0,_T("���ƵĲ���1"),LVCFMT_LEFT,100); //������
	m_List_Cha.InsertColumn(0,_T("ְ��"),LVCFMT_LEFT,100); //������
	m_List_Cha.InsertColumn(0,_T("������"),LVCFMT_LEFT,70); //������
	m_List_Cha.InsertColumn(0,_T("����"),LVCFMT_LEFT,100); //������

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
//*****��ʼ����ʾȫ����Ϣ************************


	m_pCommand.CreateInstance(__uuidof(Command)); 
	m_pCommand->ActiveConnection=m_pConnection; 

	m_pCommand->CommandText="select distinct (PName),KName,PLel from KE,People where People.KNo=KE.KNo "; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_PName; 
		_variant_t var_KName; 
		_variant_t var_PLel; 
	

		var_PName = m_pRecordset->GetCollect (_T("PName")); 
		var_KName = m_pRecordset->GetCollect (_T("KName")); 
		var_PLel = m_pRecordset->GetCollect (_T("PLel")); 
		

		CString t_PName =(LPCTSTR)_bstr_t(var_PName); 
		CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
		CString t_PLel =(LPCTSTR)_bstr_t(var_PLel); 
	

		t_PName.TrimRight(); 
		t_KName.TrimRight(); 
		t_PLel.TrimRight(); 
		

		int nCount = m_List_Cha.GetItemCount(); 
		int nItem = m_List_Cha.InsertItem (nCount,_T("")); 
		m_List_Cha.SetItemText (nItem,0,t_PName); 
		m_List_Cha.SetItemText (nItem,1,t_KName); 
		m_List_Cha.SetItemText (nItem,2,t_PLel); 

		m_pRecordset->MoveNext(); 
	} 



	
	return 0;

}

void CPeo_Cha_Dlg::OnBnClickedButtonPeoCha()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	this->m_List_Cha.DeleteAllItems();

	CString t_a=_T("select PName,KName,PLel from KE,People where People.KNo=KE.KNo and PName='");
	t_a+=this->m_Peo_Cha_In;
	t_a+="'";
	m_pCommand->CommandText=(_bstr_t)t_a; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_PName; 
		_variant_t var_KName; 
		_variant_t var_PLel; 
	

		var_PName = m_pRecordset->GetCollect (_T("PName")); 
		var_KName = m_pRecordset->GetCollect (_T("KName")); 
		var_PLel = m_pRecordset->GetCollect (_T("PLel")); 
		

		CString t_PName =(LPCTSTR)_bstr_t(var_PName); 
		CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
		CString t_PLel =(LPCTSTR)_bstr_t(var_PLel); 
	

		t_PName.TrimRight(); 
		t_KName.TrimRight(); 
		t_PLel.TrimRight(); 
		

		int nCount = m_List_Cha.GetItemCount(); 
		int nItem = m_List_Cha.InsertItem (nCount,_T("")); 
		m_List_Cha.SetItemText (nItem,0,t_PName); 
		m_List_Cha.SetItemText (nItem,1,t_KName); 
		m_List_Cha.SetItemText (nItem,2,t_PLel); 

		m_pRecordset->MoveNext(); 
	} 

//****��ʾ���ƵĲ���********
	CString t_c;
	t_c=_T("select BL_Name from BingLi,People where People.PNo=BingLi.PNo and People.PName='");
	
	t_c+=this->m_Peo_Cha_In;
	t_c+="'";
    
    m_pCommand->CommandText=(_bstr_t)t_c; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	int i=0;
	while(!m_pRecordset->GetadoEOF()) 
	{ 

		_variant_t var_lastBF; 
		var_lastBF = m_pRecordset->GetCollect (_T("BL_Name")); 
		
		CString t_last_BF =(LPCTSTR)_bstr_t(var_lastBF); 
		
		t_last_BF.TrimRight(); 
		
		m_List_Cha.SetItemText (0,3+i,t_last_BF); 
		
		i++;
    
		m_pRecordset->MoveNext(); 
	} 

}
