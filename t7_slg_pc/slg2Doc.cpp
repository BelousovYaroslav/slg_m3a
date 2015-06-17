// slg2Doc.cpp : implementation of the CSlg2Doc class
//

#include "stdafx.h"
#include "slg2.h"

#include "slg2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlg2Doc

IMPLEMENT_DYNCREATE(CSlg2Doc, CDocument)

BEGIN_MESSAGE_MAP(CSlg2Doc, CDocument)
	//{{AFX_MSG_MAP(CSlg2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlg2Doc construction/destruction

CSlg2Doc::CSlg2Doc()
{
	// TODO: add one-time construction code here

}

CSlg2Doc::~CSlg2Doc()
{
}

BOOL CSlg2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	CString tmps;
	tmps.LoadString( IDS_STR_VER);
	this->SetTitle( tmps);
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSlg2Doc serialization

void CSlg2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSlg2Doc diagnostics

#ifdef _DEBUG
void CSlg2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSlg2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSlg2Doc commands
