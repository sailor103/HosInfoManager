
// HosInfoManagerDoc.cpp : CHosInfoManagerDoc 类的实现
//

#include "stdafx.h"
#include "HosInfoManager.h"

#include "HosInfoManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHosInfoManagerDoc

IMPLEMENT_DYNCREATE(CHosInfoManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CHosInfoManagerDoc, CDocument)
END_MESSAGE_MAP()


// CHosInfoManagerDoc 构造/析构

CHosInfoManagerDoc::CHosInfoManagerDoc()
{
	// TODO: 在此添加一次性构造代码

}

CHosInfoManagerDoc::~CHosInfoManagerDoc()
{
}

BOOL CHosInfoManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(L"医院管理系统");

	return TRUE;
}




// CHosInfoManagerDoc 序列化

void CHosInfoManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CHosInfoManagerDoc 诊断

#ifdef _DEBUG
void CHosInfoManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHosInfoManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHosInfoManagerDoc 命令
