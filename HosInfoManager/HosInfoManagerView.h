
// HosInfoManagerView.h : CHosInfoManagerView 类的接口
//


#pragma once


class CHosInfoManagerView : public CView
{
protected: // 仅从序列化创建
	CHosInfoManagerView();
	DECLARE_DYNCREATE(CHosInfoManagerView)

// 属性
public:
	CHosInfoManagerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHosInfoManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuKeCha();
	afx_msg void OnMenuKeGuan();
	afx_msg void OnMenuPeoCha();
	afx_msg void OnMenuPeoGuan();
	afx_msg void OnMenuBlCha();
	afx_msg void OnMenuBlGuan();
	afx_msg void OnMenuBingfangGuan();
};

#ifndef _DEBUG  // HosInfoManagerView.cpp 中的调试版本
inline CHosInfoManagerDoc* CHosInfoManagerView::GetDocument() const
   { return reinterpret_cast<CHosInfoManagerDoc*>(m_pDocument); }
#endif

