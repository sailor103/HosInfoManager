
// HosInfoManagerView.cpp : CHosInfoManagerView ���ʵ��
//

#include "stdafx.h"
#include "HosInfoManager.h"

#include "KE_Cha_DLg.h"
#include "KE_Guan_Dlg.h"
#include "Peo_Cha_Dlg.h"
#include "Peo_Guan_Dlg.h"
#include "BR_Cha_Dlg.h"
#include "BR_Guan_Dlg.h"
#include "BF_Guan_Dlg.h"

#include "HosInfoManagerDoc.h"
#include "HosInfoManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHosInfoManagerView

IMPLEMENT_DYNCREATE(CHosInfoManagerView, CView)

BEGIN_MESSAGE_MAP(CHosInfoManagerView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHosInfoManagerView::OnFilePrintPreview)
	ON_COMMAND(ID_Menu_KE_Cha, &CHosInfoManagerView::OnMenuKeCha)
	ON_COMMAND(ID_Menu_KE_Guan, &CHosInfoManagerView::OnMenuKeGuan)
	ON_COMMAND(ID_Menu_Peo_Cha, &CHosInfoManagerView::OnMenuPeoCha)
	ON_COMMAND(ID_Menu_Peo_Guan, &CHosInfoManagerView::OnMenuPeoGuan)
	ON_COMMAND(ID_Menu_BL_Cha, &CHosInfoManagerView::OnMenuBlCha)
	ON_COMMAND(ID_Menu_BL_Guan, &CHosInfoManagerView::OnMenuBlGuan)
	ON_COMMAND(ID_Menu_BingFang_Guan, &CHosInfoManagerView::OnMenuBingfangGuan)
END_MESSAGE_MAP()

// CHosInfoManagerView ����/����

CHosInfoManagerView::CHosInfoManagerView()
{
	// TODO: �ڴ˴���ӹ������

}

CHosInfoManagerView::~CHosInfoManagerView()
{
}

BOOL CHosInfoManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CHosInfoManagerView ����

void CHosInfoManagerView::OnDraw(CDC* pDC)
{
	CHosInfoManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CDC menDC;
	CBitmap bmp,*pBmp;
	BITMAP recBmp;
	CRect rect;
	menDC.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_BACKGROUND);
	pBmp = menDC.SelectObject(&bmp);
	bmp.GetBitmap(&recBmp);
	GetClientRect(&rect);
	pDC->StretchBlt(0,0,rect.right,rect.bottom,&menDC,0,0,recBmp.bmWidth,recBmp.bmHeight,SRCCOPY);

	menDC.SelectObject(pBmp);
	bmp.DeleteObject();
	menDC.DeleteDC();
}


// CHosInfoManagerView ��ӡ


void CHosInfoManagerView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CHosInfoManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CHosInfoManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CHosInfoManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CHosInfoManagerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHosInfoManagerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CHosInfoManagerView ���

#ifdef _DEBUG
void CHosInfoManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CHosInfoManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHosInfoManagerDoc* CHosInfoManagerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHosInfoManagerDoc)));
	return (CHosInfoManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHosInfoManagerView ��Ϣ�������

void CHosInfoManagerView::OnMenuKeCha()
{
	// TODO: �ڴ���������������
	CKE_Cha_DLg CDlg;
	CDlg.DoModal();

}

void CHosInfoManagerView::OnMenuKeGuan()
{
	// TODO: �ڴ���������������
	CKE_Guan_Dlg GDlg;
	GDlg.DoModal();
}


void CHosInfoManagerView::OnMenuPeoCha()
{
	// TODO: �ڴ���������������
	CPeo_Cha_Dlg CDlg;
	CDlg.DoModal();
}

void CHosInfoManagerView::OnMenuPeoGuan()
{
	// TODO: �ڴ���������������
	CPeo_Guan_Dlg GDlg;
	GDlg.DoModal();
}

void CHosInfoManagerView::OnMenuBlCha()
{
	// TODO: �ڴ���������������
	CBR_Cha_Dlg CDlg;
	CDlg.DoModal();
}

void CHosInfoManagerView::OnMenuBlGuan()
{
	// TODO: �ڴ���������������
	CBR_Guan_Dlg GDlg;
	GDlg.DoModal();
}

void CHosInfoManagerView::OnMenuBingfangGuan()
{
	// TODO: �ڴ���������������
	CBF_Guan_Dlg GDlg;
	GDlg.DoModal();
}
