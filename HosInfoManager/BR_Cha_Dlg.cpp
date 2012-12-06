// BR_Cha_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "BR_Cha_Dlg.h"


// CBR_Cha_Dlg 对话框

IMPLEMENT_DYNAMIC(CBR_Cha_Dlg, CDialog)

CBR_Cha_Dlg::CBR_Cha_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBR_Cha_Dlg::IDD, pParent)
	, m_BR_Cha_In(_T(""))
{

}

CBR_Cha_Dlg::~CBR_Cha_Dlg()
{
}

void CBR_Cha_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BR_Cha, m_BR_Cha_In);
	DDX_Control(pDX, IDC_LIST_BR_Cha, m_List_Cha);
}


BEGIN_MESSAGE_MAP(CBR_Cha_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BR_Cha, &CBR_Cha_Dlg::OnBnClickedButtonBrCha)
END_MESSAGE_MAP()


// CBR_Cha_Dlg 消息处理程序

BOOL CBR_Cha_Dlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();   // 一定要加

	DWORD dwStyle = m_List_Cha.GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	//dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	m_List_Cha.SetExtendedStyle(dwStyle); //设置扩展风格




	m_List_Cha.InsertColumn(0,_T("病症"),LVCFMT_LEFT,160); //插入列
	m_List_Cha.InsertColumn(0,_T("主治大夫"),LVCFMT_LEFT,100); //插入列
	m_List_Cha.InsertColumn(0,_T("床号"),LVCFMT_LEFT,50); //插入列
	m_List_Cha.InsertColumn(0,_T("病房号"),LVCFMT_LEFT,50); //插入列
	m_List_Cha.InsertColumn(0,_T("所属科"),LVCFMT_LEFT,70); //插入列
	m_List_Cha.InsertColumn(0,_T("姓名"),LVCFMT_LEFT,100); //插入列


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


	//*****初始化显示全部信息************************


	m_pCommand.CreateInstance(__uuidof(Command)); 
	m_pCommand->ActiveConnection=m_pConnection; 

	m_pCommand->CommandText="select BL_Name,KName,BFNo,BL_BCNo,PName,BL_Info from BingLi,KE,People where BingLi.KNo=KE.KNo and BingLi.PNo=People.PNo"; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_BL_Name; 
		_variant_t var_KName; 
		_variant_t var_BFNo; 
		_variant_t var_BL_BCNo; 
		_variant_t var_PName; 
		_variant_t var_BL_Info; 

	

		var_BL_Name = m_pRecordset->GetCollect (_T("BL_Name")); 
		var_KName = m_pRecordset->GetCollect (_T("KName")); 
		var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
		var_BL_BCNo = m_pRecordset->GetCollect (_T("BL_BCNo")); 
		var_PName = m_pRecordset->GetCollect (_T("PName")); 
		var_BL_Info = m_pRecordset->GetCollect (_T("BL_Info")); 

		

		CString t_BL_Name =(LPCTSTR)_bstr_t(var_BL_Name); 
		CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
		CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
		CString t_BL_BCNo =(LPCTSTR)_bstr_t(var_BL_BCNo); 
		CString t_PName =(LPCTSTR)_bstr_t(var_PName); 
		CString t_BL_Info =(LPCTSTR)_bstr_t(var_BL_Info); 

	

		t_BL_Name.TrimRight(); 
		t_KName.TrimRight(); 
		t_BFNo.TrimRight(); 
		t_BL_BCNo.TrimRight(); 
		t_PName.TrimRight(); 
		t_BL_Info.TrimRight(); 

		

		int nCount = m_List_Cha.GetItemCount(); 
		int nItem = m_List_Cha.InsertItem (nCount,_T("")); 
		m_List_Cha.SetItemText (nItem,0,t_BL_Name); 
		m_List_Cha.SetItemText (nItem,1,t_KName); 
		m_List_Cha.SetItemText (nItem,2,t_BFNo); 
		m_List_Cha.SetItemText (nItem,3,t_BL_BCNo); 
		m_List_Cha.SetItemText (nItem,4,t_PName); 
		m_List_Cha.SetItemText (nItem,5,t_BL_Info); 



		m_pRecordset->MoveNext(); 
	} 








	return 0;
}

void CBR_Cha_Dlg::OnBnClickedButtonBrCha()
{
	// TODO: 在此添加控件通知处理程序代码

	this->UpdateData(TRUE);
	this->m_List_Cha.DeleteAllItems();

	CString t_a=_T("select BL_Name,KName,BFNo,BL_BCNo,PName,BL_Info from BingLi,KE,People where BingLi.KNo=KE.KNo and BingLi.PNo=People.PNo and BL_Name='");
	t_a+=this->m_BR_Cha_In;
	t_a+="'";
	m_pCommand->CommandText=(_bstr_t)t_a; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 


	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_BL_Name; 
		_variant_t var_KName; 
		_variant_t var_BFNo; 
		_variant_t var_BL_BCNo; 
		_variant_t var_PName; 
		_variant_t var_BL_Info; 

	

		var_BL_Name = m_pRecordset->GetCollect (_T("BL_Name")); 
		var_KName = m_pRecordset->GetCollect (_T("KName")); 
		var_BFNo = m_pRecordset->GetCollect (_T("BFNo")); 
		var_BL_BCNo = m_pRecordset->GetCollect (_T("BL_BCNo")); 
		var_PName = m_pRecordset->GetCollect (_T("PName")); 
		var_BL_Info = m_pRecordset->GetCollect (_T("BL_Info")); 

		

		CString t_BL_Name =(LPCTSTR)_bstr_t(var_BL_Name); 
		CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
		CString t_BFNo =(LPCTSTR)_bstr_t(var_BFNo); 
		CString t_BL_BCNo =(LPCTSTR)_bstr_t(var_BL_BCNo); 
		CString t_PName =(LPCTSTR)_bstr_t(var_PName); 
		CString t_BL_Info =(LPCTSTR)_bstr_t(var_BL_Info); 

	

		t_BL_Name.TrimRight(); 
		t_KName.TrimRight(); 
		t_BFNo.TrimRight(); 
		t_BL_BCNo.TrimRight(); 
		t_PName.TrimRight(); 
		t_BL_Info.TrimRight(); 

		

		int nCount = m_List_Cha.GetItemCount(); 
		int nItem = m_List_Cha.InsertItem (nCount,_T("")); 
		m_List_Cha.SetItemText (nItem,0,t_BL_Name); 
		m_List_Cha.SetItemText (nItem,1,t_KName); 
		m_List_Cha.SetItemText (nItem,2,t_BFNo); 
		m_List_Cha.SetItemText (nItem,3,t_BL_BCNo); 
		m_List_Cha.SetItemText (nItem,4,t_PName); 
		m_List_Cha.SetItemText (nItem,5,t_BL_Info); 



		m_pRecordset->MoveNext(); 
	} 



}
