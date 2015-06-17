// slg2View.h : interface of the CSlg2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLG2VIEW_H__377FC3E9_05DE_427F_AFBB_A8F33FF864F9__INCLUDED_)
#define AFX_SLG2VIEW_H__377FC3E9_05DE_427F_AFBB_A8F33FF864F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSlg2View : public CView
{
protected: // create from serialization only
	CSlg2View();
	DECLARE_DYNCREATE(CSlg2View)

// Attributes
public:
	CSlg2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlg2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSlg2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSlg2View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in slg2View.cpp
inline CSlg2Doc* CSlg2View::GetDocument()
   { return (CSlg2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLG2VIEW_H__377FC3E9_05DE_427F_AFBB_A8F33FF864F9__INCLUDED_)
