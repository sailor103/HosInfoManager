
// HosInfoManagerView.cpp : CHosInfoManagerView 类的实现
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
	// 标准打印命令
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

// CHosInfoManagerView 构造/析构

CHosInfoManagerView::CHosInfoManagerView()
{
	// TODO: 在此处添加构造代码

}

CHosInfoManagerView::~CHosInfoManagerView()
{
}

BOOL CHosInfoManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHosInfoManagerView 绘制

void CHosInfoManagerView::OnDraw(CDC* pDC)
{
	CHosInfoManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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


// CHosInfoManagerView 打印


void CHosInfoManagerView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CHosInfoManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHosInfoManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHosInfoManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CHosInfoManagerView 诊断

#ifdef _DEBUG
void CHosInfoManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CHosInfoManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHosInfoManagerDoc* CHosInfoManagerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHosInfoManagerDoc)));
	return (CHosInfoManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CHosInfoManagerView 消息处理程序

void CHosInfoManagerView::OnMenuKeCha()
{
	// TODO: 在此添加命令处理程序代码
	CKE_Cha_DLg CDlg;
	CDlg.DoModal();

}

void CHosInfoManagerView::OnMenuKeGuan()
{
	// TODO: 在此添加命令处理程序代码
	CKE_Guan_Dlg GDlg;
	GDlg.DoModal();
}


void CHosInfoManagerView::OnMenuPeoCha()
{
	// TODO: 在此添加命令处理程序代码
	CPeo_Cha_Dlg CDlg;
	CDlg.DoModal();
}

void CHosInfoManagerView::OnMenuPeoGuan()
{
	// TODO: 在此添加命令处理程序代码
	CPeo_Guan_Dlg GDlg;
	GDlg.DoModal();
}

void CHosInfoManagerView::OnMenuBlCha()
{
	// TODO: 在此添加命令处理程序代码
	CBR_Cha_Dlg CDlg;
	CDlg.DoModal();
}

void CHosInfoManagerView::OnMenuBlGuan()
{
	// TODO: 在此添加命令处理程序代码
	CBR_Guan_Dlg GDlg;
	GDlg.DoModal();
}

void CHosInfoManagerView::OnMenuBingfangGuan()
{
	// TODO: 在此添加命令处理程序代码
	CBF_Guan_Dlg GDlg;
	GDlg.DoModal();
}
