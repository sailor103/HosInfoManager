
// HosInfoManagerDoc.cpp : CHosInfoManagerDoc ���ʵ��
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


// CHosInfoManagerDoc ����/����

CHosInfoManagerDoc::CHosInfoManagerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CHosInfoManagerDoc::~CHosInfoManagerDoc()
{
}

BOOL CHosInfoManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle(L"ҽԺ����ϵͳ");

	return TRUE;
}




// CHosInfoManagerDoc ���л�

void CHosInfoManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CHosInfoManagerDoc ���

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


// CHosInfoManagerDoc ����
