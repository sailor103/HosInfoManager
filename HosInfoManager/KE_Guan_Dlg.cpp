// KE_Guan_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "KE_Guan_Dlg.h"


// CKE_Guan_Dlg 对话框

IMPLEMENT_DYNAMIC(CKE_Guan_Dlg, CDialog)

CKE_Guan_Dlg::CKE_Guan_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKE_Guan_Dlg::IDD, pParent)
	, m_KE_Guan_KNo(_T(""))
	, m_KE_Guan_KName(_T(""))
	, m_KE_Guan_KTel(_T(""))
	, m_KE_Guan_Zhuren(_T(""))
	, m_KE_Guan_Hushizhang(_T(""))
	, m_KE_Guan_Del(_T(""))
{

}

CKE_Guan_Dlg::~CKE_Guan_Dlg()
{
}

void CKE_Guan_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_KE_Guan, m_List_Guan);
	DDX_Text(pDX, IDC_EDIT_KE_Guan_KNo, m_KE_Guan_KNo);
	DDX_Text(pDX, IDC_EDIT_KE_Guan_KName, m_KE_Guan_KName);
	DDX_Text(pDX, IDC_EDIT_KE_Guan_KTel, m_KE_Guan_KTel);
	DDX_Text(pDX, IDC_EDIT_KE_Guan_Zhuren, m_KE_Guan_Zhuren);
	DDX_Text(pDX, IDC_EDIT_KE_Guan_Hushizhang, m_KE_Guan_Hushizhang);
	DDX_Text(pDX, IDC_EDIT_KE_Guan_Del, m_KE_Guan_Del);
}


BEGIN_MESSAGE_MAP(CKE_Guan_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_KE_Guan_Insert, &CKE_Guan_Dlg::OnBnClickedButtonKeGuanInsert)
	ON_BN_CLICKED(IDC_BUTTON_KE_Guan_Del, &CKE_Guan_Dlg::OnBnClickedButtonKeGuanDel)
END_MESSAGE_MAP()


// CKE_Guan_Dlg 消息处理程序

BOOL CKE_Guan_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // 一定要加

//****设置listCTORL风格

	DWORD dwStyle = m_List_Guan.GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	//dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	m_List_Guan.SetExtendedStyle(dwStyle); //设置扩展风格

//*****设置表头***

	m_List_Guan.InsertColumn(0,_T("护士长"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("主任"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("联系电话"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("科名"),LVCFMT_LEFT,50); //插入列
	m_List_Guan.InsertColumn(0,_T("科号"),LVCFMT_LEFT,50); //插入列

//*****初始化ADO库******

	 ::CoInitialize(NULL);// 初始化OLE/COM库环境

	try

	{

		// 创建Connection对象

		m_pConnection.CreateInstance("ADODB.Connection");

		// 设置连接字符串，必须是BSTR型或者_bstr_t类型

		_bstr_t strConnect = "Provider=SQLOLEDB;Data Source=SAILOR-THINK;Integrated Security=SSPI;Initial Catalog=BingFangInfoManager";

		m_pConnection->Open(strConnect,"","",adModeUnknown);
        if(m_pConnection!=NULL)
		{
			//AfxMessageBox(_T("数据库连接成功"));
		}

	}

	// 捕捉异常

	catch(_com_error e)

	{

		// 显示错误信息

		AfxMessageBox(e.Description());

	}



//*****初始化显示数据表的信息****
	
	m_pCommand.CreateInstance(__uuidof(Command)); 
	m_pCommand->ActiveConnection=m_pConnection; 

	m_pCommand->CommandText="select * from KE"; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_KNo; 
		_variant_t var_KName; 
		_variant_t var_KTel; 
		_variant_t var_KZhuren; 
		_variant_t var_KHushizhang; 


		var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
		var_KName = m_pRecordset->GetCollect (_T("KName")); 
		var_KTel = m_pRecordset->GetCollect (_T("KTel")); 
		var_KZhuren = m_pRecordset->GetCollect (_T("KZhuren"));
		var_KHushizhang = m_pRecordset->GetCollect (_T("KHushizhang")); 


		CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
		CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
		CString t_KTel =(LPCTSTR)_bstr_t(var_KTel); 
 		CString t_KZhuren =(LPCTSTR)_bstr_t(var_KZhuren); 
		CString t_KHushizhang =(LPCTSTR)_bstr_t(var_KHushizhang); 


		t_KNo.TrimRight(); 
		t_KName.TrimRight(); 
		t_KTel.TrimRight(); 
		t_KZhuren.TrimRight();
		t_KHushizhang.TrimRight();


		int nCount = m_List_Guan.GetItemCount(); 
		int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
		m_List_Guan.SetItemText (nItem,0,t_KNo); 
		m_List_Guan.SetItemText (nItem,1,t_KName); 
		m_List_Guan.SetItemText (nItem,2,t_KTel); 
		m_List_Guan.SetItemText (nItem,3,t_KZhuren); 
		m_List_Guan.SetItemText (nItem,4,t_KHushizhang); 


		m_pRecordset->MoveNext(); 
	} 




	return 0;
}

void CKE_Guan_Dlg::OnBnClickedButtonKeGuanInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	
	this->UpdateData(TRUE);
	if(m_KE_Guan_KNo.IsEmpty()||m_KE_Guan_KName.IsEmpty()||m_KE_Guan_KTel.IsEmpty()||this->m_KE_Guan_Zhuren.IsEmpty()||this->m_KE_Guan_Hushizhang.IsEmpty())
	{
	    AfxMessageBox(_T("对不起，您输入的数据不完整"));
	}
	
	else
	{
	
		this->m_List_Guan.DeleteAllItems();//清除显示

		CString t_insert=_T("insert into KE (KNo,KName,KTel,KZhuren,KHushizhang) values(");

		t_insert+="'";
		t_insert+=this->m_KE_Guan_KNo;
		t_insert+="','";
		t_insert+=this->m_KE_Guan_KName;
		t_insert+="','";
		t_insert+=this->m_KE_Guan_KTel;
		t_insert+="','";
		t_insert+=this->m_KE_Guan_Zhuren;
		t_insert+="','";
		t_insert+=this->m_KE_Guan_Hushizhang;
		t_insert+="')";

		m_pCommand->CommandText=(_bstr_t)t_insert; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from KE"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_KNo; 
			_variant_t var_KName; 
			_variant_t var_KTel; 
			_variant_t var_KZhuren; 
			_variant_t var_KHushizhang; 


			var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
			var_KName = m_pRecordset->GetCollect (_T("KName")); 
			var_KTel = m_pRecordset->GetCollect (_T("KTel")); 
			var_KZhuren = m_pRecordset->GetCollect (_T("KZhuren"));
			var_KHushizhang = m_pRecordset->GetCollect (_T("KHushizhang")); 


			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
			CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
			CString t_KTel =(LPCTSTR)_bstr_t(var_KTel); 
			CString t_KZhuren =(LPCTSTR)_bstr_t(var_KZhuren); 
			CString t_KHushizhang =(LPCTSTR)_bstr_t(var_KHushizhang); 


			t_KNo.TrimRight(); 
			t_KName.TrimRight(); 
			t_KTel.TrimRight(); 
			t_KZhuren.TrimRight();
			t_KHushizhang.TrimRight();


			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_KNo); 
			m_List_Guan.SetItemText (nItem,1,t_KName); 
			m_List_Guan.SetItemText (nItem,2,t_KTel); 
			m_List_Guan.SetItemText (nItem,3,t_KZhuren); 
			m_List_Guan.SetItemText (nItem,4,t_KHushizhang); 


			m_pRecordset->MoveNext(); 
		} 


	}
}

void CKE_Guan_Dlg::OnBnClickedButtonKeGuanDel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);


	if(this->m_KE_Guan_Del.IsEmpty())
	{
	    AfxMessageBox(_T("对不起，您输入的数据有误"));
	}
	
	else
	{
	
		this->m_List_Guan.DeleteAllItems();//清除显示
		CString t_del=_T("delete from KE where KNo='");
		t_del+=this->m_KE_Guan_Del;
		t_del+="'";
		
		m_pCommand->CommandText=(_bstr_t)t_del; 
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown);


		m_pCommand->CommandText="select * from KE"; 
	
		m_pCommand->CommandType=adCmdText; 
		m_pCommand->Parameters->Refresh(); 
		m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

		while(!m_pRecordset->GetadoEOF()) 
		{ 
			_variant_t var_KNo; 
			_variant_t var_KName; 
			_variant_t var_KTel; 
			_variant_t var_KZhuren; 
			_variant_t var_KHushizhang; 


			var_KNo = m_pRecordset->GetCollect (_T("KNo")); 
			var_KName = m_pRecordset->GetCollect (_T("KName")); 
			var_KTel = m_pRecordset->GetCollect (_T("KTel")); 
			var_KZhuren = m_pRecordset->GetCollect (_T("KZhuren"));
			var_KHushizhang = m_pRecordset->GetCollect (_T("KHushizhang")); 


			CString t_KNo =(LPCTSTR)_bstr_t(var_KNo); 
			CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
			CString t_KTel =(LPCTSTR)_bstr_t(var_KTel); 
			CString t_KZhuren =(LPCTSTR)_bstr_t(var_KZhuren); 
			CString t_KHushizhang =(LPCTSTR)_bstr_t(var_KHushizhang); 


			t_KNo.TrimRight(); 
			t_KName.TrimRight(); 
			t_KTel.TrimRight(); 
			t_KZhuren.TrimRight();
			t_KHushizhang.TrimRight();


			int nCount = m_List_Guan.GetItemCount(); 
			int nItem = m_List_Guan.InsertItem (nCount,_T("")); 
			m_List_Guan.SetItemText (nItem,0,t_KNo); 
			m_List_Guan.SetItemText (nItem,1,t_KName); 
			m_List_Guan.SetItemText (nItem,2,t_KTel); 
			m_List_Guan.SetItemText (nItem,3,t_KZhuren); 
			m_List_Guan.SetItemText (nItem,4,t_KHushizhang); 


			m_pRecordset->MoveNext(); 
		} 


	}





}
