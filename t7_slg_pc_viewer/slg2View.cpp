// slg2View.cpp : implementation of the CSlg2View class
//

#include "stdafx.h"
#include "slg2.h"

#include "slg2Doc.h"
#include "slg2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlg2View

IMPLEMENT_DYNCREATE(CSlg2View, CView)

BEGIN_MESSAGE_MAP(CSlg2View, CView)
	//{{AFX_MSG_MAP(CSlg2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlg2View construction/destruction

CSlg2View::CSlg2View()
{
	// TODO: add construction code here

}

CSlg2View::~CSlg2View()
{
}

BOOL CSlg2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSlg2View drawing

void CSlg2View::OnDraw(CDC* pDC)
{
	CSlg2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSlg2View printing

BOOL CSlg2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSlg2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSlg2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSlg2View diagnostics

#ifdef _DEBUG
void CSlg2View::AssertValid() const
{
	CView::AssertValid();
}

void CSlg2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSlg2Doc* CSlg2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSlg2Doc)));
	return (CSlg2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSlg2View message handlers
