// KE_Cha_DLg.cpp : 实现文件
//

#include "stdafx.h"
#include "HosInfoManager.h"
#include "KE_Cha_DLg.h"


// CKE_Cha_DLg 对话框

IMPLEMENT_DYNAMIC(CKE_Cha_DLg, CDialog)

CKE_Cha_DLg::CKE_Cha_DLg(CWnd* pParent /*=NULL*/)
	: CDialog(CKE_Cha_DLg::IDD, pParent)
	, m_KE_Cha_InStr(_T(""))
{

}

CKE_Cha_DLg::~CKE_Cha_DLg()
{
//关闭数据库和释放这些对象指针
/*	m_pRecordset->Close();
	m_pConnection->Close();
	m_pCommand.Release();
	m_pRecordset.Release();
	m_pConnection.Release();*/
}

void CKE_Cha_DLg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KE_Cha, m_KE_Cha_InStr);
	DDX_Control(pDX, IDC_LIST_KE_Cha, m_List_Cha);
}


BEGIN_MESSAGE_MAP(CKE_Cha_DLg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Cha, &CKE_Cha_DLg::OnBnClickedButtonCha)
END_MESSAGE_MAP()


// CKE_Cha_DLg 消息处理程序

BOOL CKE_Cha_DLg::OnInitDialog(void)
{
    CDialog::OnInitDialog();   // 一定要加

/*	DWORD dwStyle = GetWindowLong(m_List_Cha.m_hWnd, GWL_STYLE);

	//在原有样式的基本上，添加LVS_REPORT扩展样式
	SetWindowLong(m_List_Cha.m_hWnd, GWL_STYLE, dwStyle|LVS_REPORT);



	//获取已有的扩展样式
	DWORD dwStyles = m_List_Cha.GetExStyle();

	//取消复选框样式
	dwStyles &= ~LVS_EX_CHECKBOXES;

	//添加整行选择和表格线扩展样式
	m_List_Cha.SetExtendedStyle(dwStyles|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);*/

	DWORD dwStyle = m_List_Cha.GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	//dwStyle |= LVS_EX_CHECKBOXES; //item前生成checkbox控件
	m_List_Cha.SetExtendedStyle(dwStyle); //设置扩展风格

   
	m_List_Cha.InsertColumn(0,_T("剩余病床数"),LVCFMT_LEFT,100); //插入列
	m_List_Cha.InsertColumn(0,_T("联系方式"),LVCFMT_LEFT,100); //插入列
	m_List_Cha.InsertColumn(0,_T("护士长"),LVCFMT_LEFT,70); //插入列
	m_List_Cha.InsertColumn(0,_T("主任"),LVCFMT_LEFT,70); //插入列 
	m_List_Cha.InsertColumn(0,_T("科目"),LVCFMT_LEFT,50); //插入列


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

	m_pCommand->CommandText="select KE.KName ,first.PName aa,second.PName bb,KE.KTel from KE,People first,People second where KE.KZhuren=first.PNo and KE.KHushizhang=second.PNo"; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_KName; 
		_variant_t var_Kzhuren; 
		_variant_t var_Khushi; 
		_variant_t var_Ktel; 

		var_KName = m_pRecordset->GetCollect (_T("KName")); 
		var_Kzhuren = m_pRecordset->GetCollect (_T("aa")); 
		var_Khushi = m_pRecordset->GetCollect (_T("bb")); 
		var_Ktel = m_pRecordset->GetCollect (_T("KTel")); 

		CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
		CString t_Kzhuren =(LPCTSTR)_bstr_t(var_Kzhuren); 
		CString t_Khushi =(LPCTSTR)_bstr_t(var_Khushi); 
		CString t_Ktel =(LPCTSTR)_bstr_t(var_Ktel); 

		t_KName.TrimRight(); 
		t_Kzhuren.TrimRight(); 
		t_Khushi.TrimRight(); 
		t_Ktel.TrimRight(); 

		int nCount = m_List_Cha.GetItemCount(); 
		int nItem = m_List_Cha.InsertItem (nCount,_T("")); 
		m_List_Cha.SetItemText (nItem,0,t_KName); 
		m_List_Cha.SetItemText (nItem,1,t_Kzhuren); 
		m_List_Cha.SetItemText (nItem,2,t_Khushi); 
		m_List_Cha.SetItemText (nItem,3,t_Ktel); 

		m_pRecordset->MoveNext(); 
	} 


//***********************************************
	
	return false;
}

void CKE_Cha_DLg::OnBnClickedButtonCha()
{
	// TODO: 在此添加控件通知处理程序代码

	//while(m_List_Cha.DeleteColumn(0))

	this->m_List_Cha.DeleteAllItems();

	this->UpdateData(TRUE);//获得查询数据

	m_pCommand.CreateInstance(__uuidof(Command)); 
	m_pCommand->ActiveConnection=m_pConnection; 


//**********************显示科目，主任，电话*******************

	CString a=_T("select KE.KName,People.PName,KE.KTel from KE,People where KE.KZhuren=People.PNo");
	a+=_T(" and KE.KName='");
	a+=this->m_KE_Cha_InStr;
	a+="'";

	m_pCommand->CommandText=(_bstr_t)a; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	while(!m_pRecordset->GetadoEOF()) 
	{ 
		_variant_t var_KName; 
		_variant_t var_Kzhuren; 
		_variant_t var_Khushi; 
		_variant_t var_Ktel; 

		var_KName = m_pRecordset->GetCollect (_T("KName")); 
		var_Kzhuren = m_pRecordset->GetCollect (_T("PName")); 
		//var_Khushi = m_pRecordset->GetCollect (_T("PName")); 
		var_Ktel = m_pRecordset->GetCollect (_T("KTel")); 

		CString t_KName =(LPCTSTR)_bstr_t(var_KName); 
		CString t_Kzhuren =(LPCTSTR)_bstr_t(var_Kzhuren); 
		//CString t_Khushi =(LPCTSTR)_bstr_t(var_Khushi); 
		CString t_Ktel =(LPCTSTR)_bstr_t(var_Ktel); 

		t_KName.TrimRight(); 
		t_Kzhuren.TrimRight(); 
		//t_Khushi.TrimRight(); 
		t_Ktel.TrimRight(); 

		int nCount = m_List_Cha.GetItemCount(); 
		int nItem = m_List_Cha.InsertItem (nCount,_T("")); 
		m_List_Cha.SetItemText (nItem,0,t_KName); 
		m_List_Cha.SetItemText (nItem,1,t_Kzhuren); 
		//m_List_Cha.SetItemText (nItem,2,t_Khushi); 
		m_List_Cha.SetItemText (nItem,3,t_Ktel); 

		m_pRecordset->MoveNext(); 
	} 




//*************显示护士长*****************


    CString t_b;
	t_b=_T("select People.PName from KE,People where KE.KHushizhang=People.PNo");
	t_b+=_T(" and KE.KName='");
	t_b+=this->m_KE_Cha_InStr;
	t_b+="'";

	m_pCommand->CommandText=(_bstr_t)t_b; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	int i=0;
	while(!m_pRecordset->GetadoEOF()) 
	{ 

		_variant_t var_Khushi; 
		var_Khushi = m_pRecordset->GetCollect (_T("PName")); 
		
		CString t_Khushi =(LPCTSTR)_bstr_t(var_Khushi); 
		
		t_Khushi.TrimRight(); 
		
		m_List_Cha.SetItemText (i,2,t_Khushi); 
		
        i++;
		m_pRecordset->MoveNext(); 
	} 

//***********************显示剩余病房数***************



	CString t_c;
	t_c=_T("select 24-COUNT(*) aa from BingLi,KE where KE.KNo=BingLi.KNo");
	t_c+=_T(" and KE.KName='");
	t_c+=this->m_KE_Cha_InStr;
	t_c+="'";
    
    m_pCommand->CommandText=(_bstr_t)t_c; 
	
    m_pCommand->CommandType=adCmdText; 
	m_pCommand->Parameters->Refresh(); 
	m_pRecordset= m_pCommand->Execute(NULL,NULL,adCmdUnknown); 

	 i=0;
	while(!m_pRecordset->GetadoEOF()) 
	{ 

		_variant_t var_lastBF; 
		var_lastBF = m_pRecordset->GetCollect (_T("aa")); 
		
		CString t_last_BF =(LPCTSTR)_bstr_t(var_lastBF); 
		
		t_last_BF.TrimRight(); 
		
		m_List_Cha.SetItemText (i,4,t_last_BF); 
		
        i++;
		m_pRecordset->MoveNext(); 
	} 


}
