// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "slg2.h"
#include "Slg2Doc.h"
#include "MainFrm.h"
#include "MainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MY_TIMER_100_HZ 1000
#define MY_TIMER_REFRESH_VIEW 1001

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZING()
	ON_UPDATE_COMMAND_UI(ID_HISTOGRAM, OnUpdateHistogram)
	ON_UPDATE_COMMAND_UI(ID_ALAN_CURVE, OnUpdateAlanCurve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.hMenu = NULL;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect) 
{
	if( ( pRect->right - pRect->left) < 500) pRect->right = pRect->left + 500;
	if( ( pRect->bottom - pRect->top) < 500) pRect->bottom = pRect->top + 500;	
	CFrameWnd::OnSizing(fwSide, pRect);
}

void CMainFrame::OnUpdateHistogram(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !( ( CSlg2Doc *)GetActiveDocument())->m_strCurrentFileName.IsEmpty());
}

void CMainFrame::OnUpdateAlanCurve(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable( !( ( CSlg2Doc *)GetActiveDocument())->m_strCurrentFileName.IsEmpty());
	pCmdUI->Enable( false);
}
