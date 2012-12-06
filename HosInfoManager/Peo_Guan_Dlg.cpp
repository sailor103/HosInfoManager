// Peo_Guan_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "Peo_Guan_Dlg.h"


// CPeo_Guan_Dlg 对话框

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


// CPeo_Guan_Dlg 消息处理程序

BOOL CPeo_Guan_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // 一定要加

    //****设置listCTORL风格

	DWORD dwStyle = m_List_Guan.GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	//dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	m_List_Guan.SetExtendedStyle(dwStyle); //设置扩展风格

	//*****设置表头***


	m_List_Guan.InsertColumn(0,_T("级别"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("姓名"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("所属科号"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("人员编号"),LVCFMT_LEFT,100); //插入列

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
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if(this->m_Peo_Guan_KNo.IsEmpty()||this->m_Peo_Guan_PNo.IsEmpty()||this->m_Peo_Guan_PName.IsEmpty()||this->m_Peo_Guan_PLel.IsEmpty())
	{
	    AfxMessageBox(_T("对不起，您输入的数据不完整"));
	}



	else
	{
	
		this->m_List_Guan.DeleteAllItems();//清除显示

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
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);


	if(this->m_Peo_Guan_Del.IsEmpty())
	{
	    AfxMessageBox(_T("对不起，您输入的数据有误"));
	}
	
	else
	{
	
		this->m_List_Guan.DeleteAllItems();//清除显示
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
