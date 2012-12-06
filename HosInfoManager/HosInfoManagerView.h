
// HosInfoManagerView.h : CHosInfoManagerView ��Ľӿ�
//


#pragma once


class CHosInfoManagerView : public CView
{
protected: // �������л�����
	CHosInfoManagerView();
	DECLARE_DYNCREATE(CHosInfoManagerView)

// ����
public:
	CHosInfoManagerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CHosInfoManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // HosInfoManagerView.cpp �еĵ��԰汾
inline CHosInfoManagerDoc* CHosInfoManagerView::GetDocument() const
   { return reinterpret_cast<CHosInfoManagerDoc*>(m_pDocument); }
#endif

