// BF_Guan_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "BF_Guan_Dlg.h"


// CBF_Guan_Dlg 对话框

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


// CBF_Guan_Dlg 消息处理程序

BOOL CBF_Guan_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // 一定要加

	DWORD dwStyle = m_List_Guan.GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	//dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	m_List_Guan.SetExtendedStyle(dwStyle); //设置扩展风格

	//*****设置表头***


	m_List_Guan.InsertColumn(0,_T("病床数量"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("所属科号"),LVCFMT_LEFT,100); //插入列
	m_List_Guan.InsertColumn(0,_T("病房号"),LVCFMT_LEFT,100); //插入列



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
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if(this->m_BF_Guan_KNo.IsEmpty()||this->m_BF_Guan_BFNo.IsEmpty()||this->m_BF_Guan_BFAcc.IsEmpty())
	{
	    AfxMessageBox(_T("对不起，您输入的数据不完整"));
	}
	else
	{
	
		this->m_List_Guan.DeleteAllItems();//清除显示

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
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);


	if(this->m_BF_Guan_Del.IsEmpty())
	{
	    AfxMessageBox(_T("对不起，您输入的数据有误"));
	}

	else
	{
	
		this->m_List_Guan.DeleteAllItems();//清除显示

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
