
// HosInfoManagerDoc.h : CHosInfoManagerDoc ��Ľӿ�
//


#pragma once


class CHosInfoManagerDoc : public CDocument
{
protected: // �������л�����
	CHosInfoManagerDoc();
	DECLARE_DYNCREATE(CHosInfoManagerDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CHosInfoManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


