// MainView.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "Slg2Doc.h"
#include "MainView.h"
#include "MainFrm.h"
#include "SlgNewAverager.h"
#include "DlgHisto.h"
#include "DlgAlanCurve.h"
#include "DlgExport.h"
#include <winver.h>
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_TIMER_1000			1101

#define MY_MAXIMIZE_VIEW_TIMER 1002
#define MY_REFRESH_VIEW_TIMER 1003

extern BOOL m_bStopThreadFlag;
extern BOOL m_bStopBigThreadFlag;
extern int gl_nCircleBufferGet;
extern int gl_nCircleBufferPut;

extern double gl_dGlobalTime;
extern CSlgNewAverager gl_avW100;
extern CSlgNewAverager gl_avW1000;
extern CSlgNewAverager gl_avW10000;
extern CSlgNewAverager gl_avW100000;
extern CSlgNewAverager gl_avI1;
extern CSlgNewAverager gl_avI2;
extern CSlgNewAverager gl_avVpc;
extern CSlgNewAverager gl_avAmplAng;
extern CSlgNewAverager gl_avT1;
extern CSlgNewAverager gl_avT2;
extern CSlgNewAverager gl_avT3;
extern CSlgNewAverager gl_avTsa;
extern CSlgNewAverager gl_avTsa1000;
extern CSlgNewAverager gl_avTsa10000;
extern CSlgNewAverager gl_avTsa100000;

extern double gl_pTsa;
extern double gl_pTSamean;

/////////////////////////////////////////////////////////////////////////////
// CMainView

IMPLEMENT_DYNCREATE(CMainView, CFormView)

CMainView::CMainView()
	: CFormView(CMainView::IDD)
{
	//{{AFX_DATA_INIT(CMainView)
	m_strGraphMaxVal = _T("");
	m_strGraphMeanVal = _T("");
	m_strGraphMinVal = _T("");
	m_strGraphRmsVal = _T("");
	m_strSmGr1_max = _T("");
	m_strSmGr1_mean = _T("");
	m_strSmGr1_min = _T("");
	m_strSmGr1_rms = _T("");
	m_strSmGr2_max = _T("");
	m_strSmGr2_mean = _T("");
	m_strSmGr2_min = _T("");
	m_strSmGr2_rms = _T("");
	m_strSmGr3_max = _T("");
	m_strSmGr3_mean = _T("");
	m_strSmGr3_min = _T("");
	m_strSmGr3_rms = _T("");
	m_strSmGr4_max = _T("");
	m_strSmGr4_mean = _T("");
	m_strSmGr4_min = _T("");
	m_strSmGr4_rms = _T("");
	m_strSmGr5_max = _T("");
	m_strSmGr5_mean = _T("");
	m_strSmGr5_min = _T("");
	m_strSmGr5_rms = _T("");
	m_strSmGr6_max = _T("");
	m_strSmGr6_mean = _T("");
	m_strSmGr6_min = _T("");
	m_strSmGr6_rms = _T("");
	m_strSmGr7_max = _T("");
	m_strSmGr7_mean = _T("");
	m_strSmGr7_min = _T("");
	m_strSmGr7_rms = _T("");
	m_strSmGr8_max = _T("");
	m_strSmGr8_mean = _T("");
	m_strSmGr8_min = _T("");
	m_strSmGr8_rms = _T("");
	m_strParam1Val = _T("");
	m_strParam2Val = _T("");
	m_strParam3Val = _T("");
	m_strParam4Val = _T("");
	m_strParam5Val = _T("");
	m_strParam6Val = _T("");
	m_strParam7Val = _T("");
	m_strParam8Val = _T("");
	m_strParam9Val = _T("");
	m_nTMeaningInd = 0;
	m_dKimpSec = 0.0;
	m_strSoftwareVersion = _T("");
	m_strThisSoftwareVersion = _T("");
	m_strLblCursorDxVal = _T("");
	m_strLblCursorDyVal = _T("");
	m_strCur1X_val = _T("");
	m_strCur1Y_val = _T("");
	m_strCur2X_val = _T("");
	m_strCur2Y_val = _T("");
	m_nRadT2 = 0;
	m_nRadT1 = 1;
	//}}AFX_DATA_INIT
	m_nCounterSkippedPoints = 0;
	b1stPointSkipped = false;	
	m_bEmergencyCodeApperance = false;
	
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));									// Zero out the structure.
	lf.lfHeight = 20;																	// Request a 12-pixel-height font.
	lstrcpy(lf.lfFaceName, _T("Times New Roman"));   // Request a face name "Arial".
	VERIFY(m_pFont.CreateFontIndirect(&lf));							// Create the font.
}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainView)
	DDX_Control(pDX, IDC_GRAPH1, m_ctlSmallGraph1);
	DDX_Control(pDX, IDC_GRAPH2, m_ctlSmallGraph2);
	DDX_Control(pDX, IDC_GRAPH3, m_ctlSmallGraph3);
	DDX_Control(pDX, IDC_GRAPH4, m_ctlSmallGraph4);
	DDX_Control(pDX, IDC_GRAPH5, m_ctlSmallGraph5);
	DDX_Control(pDX, IDC_GRAPH6, m_ctlSmallGraph6);
	DDX_Control(pDX, IDC_GRAPH7, m_ctlSmallGraph7);
	DDX_Control(pDX, IDC_GRAPH8, m_ctlSmallGraph8);
	DDX_Control(pDX, IDC_MAIN_GRAPH, m_ctlMainGraph);
	DDX_Text(pDX, IDC_MAXVAL_LABEL, m_strGraphMaxVal);
	DDX_Text(pDX, IDC_MEANVAL_LABEL, m_strGraphMeanVal);
	DDX_Text(pDX, IDC_MINVAL_LABEL, m_strGraphMinVal);
	DDX_Text(pDX, IDC_RMSVAL_LABEL, m_strGraphRmsVal);
	DDX_Text(pDX, IDC_GRAPH1_MAXVAL_LABEL, m_strSmGr1_max);
	DDX_Text(pDX, IDC_GRAPH1_MEANVAL_LABEL, m_strSmGr1_mean);
	DDX_Text(pDX, IDC_GRAPH1_MINVAL_LABEL, m_strSmGr1_min);
	DDX_Text(pDX, IDC_GRAPH1_RMSVAL_LABEL, m_strSmGr1_rms);
	DDX_Text(pDX, IDC_GRAPH2_MAXVAL_LABEL, m_strSmGr2_max);
	DDX_Text(pDX, IDC_GRAPH2_MEANVAL_LABEL, m_strSmGr2_mean);
	DDX_Text(pDX, IDC_GRAPH2_MINVAL_LABEL, m_strSmGr2_min);
	DDX_Text(pDX, IDC_GRAPH2_RMSVAL_LABEL, m_strSmGr2_rms);
	DDX_Text(pDX, IDC_GRAPH3_MAXVAL_LABEL, m_strSmGr3_max);
	DDX_Text(pDX, IDC_GRAPH3_MEANVAL_LABEL, m_strSmGr3_mean);
	DDX_Text(pDX, IDC_GRAPH3_MINVAL_LABEL, m_strSmGr3_min);
	DDX_Text(pDX, IDC_GRAPH3_RMSVAL_LABEL, m_strSmGr3_rms);
	DDX_Text(pDX, IDC_GRAPH4_MAXVAL_LABEL, m_strSmGr4_max);
	DDX_Text(pDX, IDC_GRAPH4_MEANVAL_LABEL, m_strSmGr4_mean);
	DDX_Text(pDX, IDC_GRAPH4_MINVAL_LABEL, m_strSmGr4_min);
	DDX_Text(pDX, IDC_GRAPH4_RMSVAL_LABEL, m_strSmGr4_rms);
	DDX_Text(pDX, IDC_GRAPH5_MAXVAL_LABEL, m_strSmGr5_max);
	DDX_Text(pDX, IDC_GRAPH5_MEANVAL_LABEL, m_strSmGr5_mean);
	DDX_Text(pDX, IDC_GRAPH5_MINVAL_LABEL, m_strSmGr5_min);
	DDX_Text(pDX, IDC_GRAPH5_RMSVAL_LABEL, m_strSmGr5_rms);
	DDX_Text(pDX, IDC_GRAPH6_MAXVAL_LABEL, m_strSmGr6_max);
	DDX_Text(pDX, IDC_GRAPH6_MEANVAL_LABEL, m_strSmGr6_mean);
	DDX_Text(pDX, IDC_GRAPH6_MINVAL_LABEL, m_strSmGr6_min);
	DDX_Text(pDX, IDC_GRAPH6_RMSVAL_LABEL, m_strSmGr6_rms);
	DDX_Text(pDX, IDC_GRAPH7_MAXVAL_LABEL, m_strSmGr7_max);
	DDX_Text(pDX, IDC_GRAPH7_MEANVAL_LABEL, m_strSmGr7_mean);
	DDX_Text(pDX, IDC_GRAPH7_MINVAL_LABEL, m_strSmGr7_min);
	DDX_Text(pDX, IDC_GRAPH7_RMSVAL_LABEL, m_strSmGr7_rms);
	DDX_Text(pDX, IDC_GRAPH8_MAXVAL_LABEL, m_strSmGr8_max);
	DDX_Text(pDX, IDC_GRAPH8_MEANVAL_LABEL, m_strSmGr8_mean);
	DDX_Text(pDX, IDC_GRAPH8_MINVAL_LABEL, m_strSmGr8_min);
	DDX_Text(pDX, IDC_GRAPH8_RMSVAL_LABEL, m_strSmGr8_rms);
	DDX_Text(pDX, IDC_PARAM1_VAL, m_strParam1Val);
	DDX_Text(pDX, IDC_PARAM2_VAL, m_strParam2Val);
	DDX_Text(pDX, IDC_PARAM3_VAL, m_strParam3Val);
	DDX_Text(pDX, IDC_PARAM4_VAL, m_strParam4Val);
	DDX_Text(pDX, IDC_PARAM5_VAL, m_strParam5Val);
	DDX_Text(pDX, IDC_PARAM6_VAL, m_strParam6Val);
	DDX_Text(pDX, IDC_PARAM7_VAL, m_strParam7Val);
	DDX_Text(pDX, IDC_PARAM8_VAL, m_strParam8Val);
	DDX_Text(pDX, IDC_PARAM9_VAL, m_strParam9Val);
	DDX_Radio(pDX, IDC_RAD_MEANING1, m_nTMeaningInd);
	DDX_Text(pDX, IDC_EDT_K_IMP_SEC, m_dKimpSec);
	DDX_Text(pDX, IDC_SOFTWARE_VERSION, m_strSoftwareVersion);
	DDX_Text(pDX, IDC_THIS_SOFTWARE_VERSION, m_strThisSoftwareVersion);
	DDX_Text(pDX, IDC_LBL_CURSOR_DX_VAL, m_strLblCursorDxVal);
	DDX_Text(pDX, IDC_LBL_CURSOR_DY_VAL, m_strLblCursorDyVal);
	DDX_Text(pDX, IDC_LBL_CURSOR1_X_VAL, m_strCur1X_val);
	DDX_Text(pDX, IDC_LBL_CURSOR1_Y_VAL, m_strCur1Y_val);
	DDX_Text(pDX, IDC_LBL_CURSOR2_X_VAL, m_strCur2X_val);
	DDX_Text(pDX, IDC_LBL_CURSOR2_Y_VAL, m_strCur2Y_val);
	DDX_Radio(pDX, IDC_RAD_T2_TD1, m_nRadT2);
	DDX_Radio(pDX, IDC_RAD_T1_TD1, m_nRadT1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainView, CFormView)
	//{{AFX_MSG_MAP(CMainView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_EDT_K_IMP_SEC, OnKillfocusEdtKImpSec)
	ON_COMMAND(ID_HISTOGRAM, OnHistogram)
	ON_COMMAND(ID_ALAN_CURVE, OnAlanCurve)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_BN_CLICKED(IDC_RAD_MEANING1, OnRadMeaning100msec)
	ON_BN_CLICKED(IDC_RAD_MEANING2, OnRadMeaning1sec)
	ON_BN_CLICKED(IDC_RAD_MEANING3, OnRadMeaning10sec)
	ON_BN_CLICKED(IDC_RAD_MEANING4, OnRadMeaning100sec)
	ON_UPDATE_COMMAND_UI(ID_ZOOMIN, OnUpdateZoomin)
	ON_UPDATE_COMMAND_UI(ID_RESTORE_ZOOM, OnUpdateRestoreZoom)
	ON_COMMAND(ID_ZOOMIN, OnZoomin)
	ON_COMMAND(ID_RESTORE_ZOOM, OnRestoreZoom)
	ON_COMMAND(ID_SHOW_CURSORS, OnShowCursors)
	ON_BN_CLICKED(IDC_RAD_T1_TD1, OnRadT1Td1)
	ON_BN_CLICKED(IDC_RAD_T1_TD2, OnRadT1Td2)
	ON_BN_CLICKED(IDC_RAD_T1_TD3, OnRadT1Td3)
	ON_BN_CLICKED(IDC_RAD_T2_TD1, OnRadT2Td1)
	ON_BN_CLICKED(IDC_RAD_T2_TD2, OnRadT2Td2)
	ON_BN_CLICKED(IDC_RAD_T2_TD3, OnRadT2Td3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainView message handlers

void CMainView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	int nGrWidth = cx / 8;
	CRect rc;

	if( m_ctlSmallGraph1.m_hWnd) {
		m_ctlSmallGraph1.GetWindowRect( &rc);
		m_ctlSmallGraph1.SetWindowPos( NULL, 0, 50, nGrWidth - 2, rc.Height(), SWP_NOZORDER);
	}
	
	if( m_ctlSmallGraph2.m_hWnd) {
		m_ctlSmallGraph2.GetWindowRect( &rc);
		m_ctlSmallGraph2.SetWindowPos( NULL, nGrWidth, 50, nGrWidth - 2, rc.Height(), SWP_NOZORDER);
	}

	if( m_ctlSmallGraph3.m_hWnd) {
		m_ctlSmallGraph3.GetWindowRect( &rc);
		m_ctlSmallGraph3.SetWindowPos( NULL, nGrWidth * 2, 50, nGrWidth - 2, rc.Height(), SWP_NOZORDER);
	}

	if( m_ctlSmallGraph4.m_hWnd) {
		m_ctlSmallGraph4.GetWindowRect( &rc);
		m_ctlSmallGraph4.SetWindowPos( NULL, nGrWidth * 3, 50, nGrWidth - 2, rc.Height(), SWP_NOZORDER);
	}

	if( m_ctlSmallGraph5.m_hWnd) {
		m_ctlSmallGraph5.GetWindowRect( &rc);
		m_ctlSmallGraph5.SetWindowPos( NULL, nGrWidth * 4, 50, nGrWidth - 2, rc.Height(), SWP_NOZORDER);
	}

	if( m_ctlSmallGraph6.m_hWnd) {
		m_ctlSmallGraph6.GetWindowRect( &rc);
		m_ctlSmallGraph6.SetWindowPos( NULL, nGrWidth * 5, 50, nGrWidth - 22, rc.Height(), SWP_NOZORDER);

    GetDlgItem( IDC_RAD_T1_TD1)->SetWindowPos( NULL, nGrWidth * 6 - 21, 70, 20, 12, SWP_NOZORDER);
    GetDlgItem( IDC_RAD_T1_TD2)->SetWindowPos( NULL, nGrWidth * 6 - 21, 90, 20, 12, SWP_NOZORDER);
    GetDlgItem( IDC_RAD_T1_TD3)->SetWindowPos( NULL, nGrWidth * 6 - 21, 110, 20, 12, SWP_NOZORDER);
	}

	if( m_ctlSmallGraph7.m_hWnd) {
		m_ctlSmallGraph7.GetWindowRect( &rc);
		m_ctlSmallGraph7.SetWindowPos( NULL, nGrWidth * 6, 50, nGrWidth - 22, rc.Height(), SWP_NOZORDER);

    GetDlgItem( IDC_RAD_T2_TD1)->SetWindowPos( NULL, nGrWidth * 7 - 21, 70, 20, 12, SWP_NOZORDER);
    GetDlgItem( IDC_RAD_T2_TD2)->SetWindowPos( NULL, nGrWidth * 7 - 21, 90, 20, 12, SWP_NOZORDER);
    GetDlgItem( IDC_RAD_T2_TD3)->SetWindowPos( NULL, nGrWidth * 7 - 21, 110, 20, 12, SWP_NOZORDER);
	}

	if( m_ctlSmallGraph8.m_hWnd) {
		m_ctlSmallGraph8.GetWindowRect( &rc);
		m_ctlSmallGraph8.SetWindowPos( NULL, nGrWidth * 7, 50, nGrWidth - 2, rc.Height(), SWP_NOZORDER);
	}

	int base = 50 + rc.Height();
	CWnd *pWnd = GetDlgItem( IDC_GRAPH1_MIN_LABEL);
	if( pWnd != NULL) {
		CRect rc1;
		
		pWnd->SetWindowPos( NULL, 0, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH1_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH1_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, 0, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH1_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH1_MAX_LABEL);
		pWnd->SetWindowPos( NULL, 0, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH1_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH1_RMS_LABEL);
		pWnd->SetWindowPos( NULL, 0, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH1_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		
		base = 50 + rc.Height();
		pWnd = GetDlgItem( IDC_GRAPH2_MIN_LABEL);	
		pWnd->SetWindowPos( NULL, nGrWidth, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH2_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH2_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH2_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH2_MAX_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH2_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH2_RMS_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH2_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		

		base = 50 + rc.Height();
		pWnd = GetDlgItem( IDC_GRAPH3_MIN_LABEL);	
		pWnd->SetWindowPos( NULL, nGrWidth * 2, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH3_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 2 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH3_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 2, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH3_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 2 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH3_MAX_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 2, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH3_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 2 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH3_RMS_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 2, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH3_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 2 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		

		base = 50 + rc.Height();
		pWnd = GetDlgItem( IDC_GRAPH4_MIN_LABEL);	
		pWnd->SetWindowPos( NULL, nGrWidth * 3, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH4_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 3 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH4_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 3, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH4_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 3 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH4_MAX_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 3, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH4_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 3 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH4_RMS_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 3, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH4_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 3 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		

		base = 50 + rc.Height();
		pWnd = GetDlgItem( IDC_GRAPH5_MIN_LABEL);	
		pWnd->SetWindowPos( NULL, nGrWidth * 4, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH5_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 4 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH5_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 4, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH5_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 4 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH5_MAX_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 4, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH5_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 4 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH5_RMS_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 4, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH5_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 4 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		

		base = 50 + rc.Height();
		pWnd = GetDlgItem( IDC_GRAPH6_MIN_LABEL);	
		pWnd->SetWindowPos( NULL, nGrWidth * 5, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH6_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 5 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH6_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 5, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH6_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 5 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH6_MAX_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 5, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH6_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 5 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH6_RMS_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 5, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH6_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 5 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		

		base = 50 + rc.Height();
		pWnd = GetDlgItem( IDC_GRAPH7_MIN_LABEL);	
		pWnd->SetWindowPos( NULL, nGrWidth * 6, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH7_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 6 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH7_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 6, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH7_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 6 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH7_MAX_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 6, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH7_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 6 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH7_RMS_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 6, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH7_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 6 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		

		base = 50 + rc.Height();
		pWnd = GetDlgItem( IDC_GRAPH8_MIN_LABEL);	
		pWnd->SetWindowPos( NULL, nGrWidth * 7, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd->GetWindowRect( &rc1);
		pWnd = GetDlgItem( IDC_GRAPH8_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 7 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH8_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 7, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH8_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 7 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH8_MAX_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 7, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH8_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 7 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();

		pWnd = GetDlgItem( IDC_GRAPH8_RMS_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 7, base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		pWnd = GetDlgItem( IDC_GRAPH8_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, nGrWidth * 7 + rc1.Width(), base, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		base += rc1.Height();
	}

	CRect m_rcStatusBar;
	if( m_ctlMainGraph.m_hWnd) {
		(( CMainFrame*) this->GetParentFrame())->m_wndStatusBar.GetWindowRect( m_rcStatusBar);
		m_ctlMainGraph.SetWindowPos( NULL, 5, base + 5, cx - 210 - 10, cy - base, SWP_NOZORDER);
	}

	pWnd = GetDlgItem( IDC_STATISTIC_FRAME);
	if( pWnd != NULL) {
		pWnd->SetWindowPos( NULL, cx - 210, base + 5, 210, cy - base, SWP_NOZORDER);
		
		pWnd = GetDlgItem( IDC_MIN_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 20, 200, 20, SWP_NOZORDER);
		pWnd = GetDlgItem( IDC_MINVAL_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 40, 200, 20, SWP_NOZORDER);

		pWnd = GetDlgItem( IDC_MEAN_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 70, 200, 20, SWP_NOZORDER);
		pWnd = GetDlgItem( IDC_MEANVAL_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 90, 200, 20, SWP_NOZORDER);
		
		pWnd = GetDlgItem( IDC_MAX_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 120, 200, 20, SWP_NOZORDER);
		pWnd = GetDlgItem( IDC_MAXVAL_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 140, 200, 20, SWP_NOZORDER);
		
		pWnd = GetDlgItem( IDC_RMS_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 170, 200, 20, SWP_NOZORDER);
		pWnd = GetDlgItem( IDC_RMSVAL_LABEL);
		pWnd->SetWindowPos( NULL, cx - 210 + 5, base + 190, 200, 20, SWP_NOZORDER);

		int x = cx - 210 + 5;
		base += 220;
		pWnd = GetDlgItem( IDC_PARAM1_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM1_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM2_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM2_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM3_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM3_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM4_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM4_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
			
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM5_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM5_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
				
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM6_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM6_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM7_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM7_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
				
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM8_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM8_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		
		base += rc.Height(); base += 5;
		x = cx - 210 + 5;
		pWnd = GetDlgItem( IDC_PARAM9_TITLE);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
		pWnd->GetWindowRect( rc);
		base += rc.Height();
		pWnd = GetDlgItem( IDC_PARAM9_VAL);
		pWnd->SetWindowPos( NULL, x, base, 0, 0, SWP_NOZORDER + SWP_NOSIZE);
	}

	
}

void CMainView::RefreshGraphs()
{
	BeginWaitCursor();
	CSlg2Doc *doc = (CSlg2Doc *) GetDocument();
	if( doc->m_dn100m == 0.) return;
	if( m_nTMeaningInd == 1 && doc->m_dn1s == 0.) return;
	if( m_nTMeaningInd == 2 && doc->m_dn10s == 0.) return;
	if( m_nTMeaningInd == 3 && doc->m_dn100s == 0.) return;

	//100-мсек точки
	CNiReal64Matrix line_w100m( 2, doc->m_dn100m, 1.0);
	for( int i = 0; i < doc->m_dn100m; i++) {
		line_w100m( 0, i) = doc->m_dx100m[i];
		line_w100m( 1, i) = doc->m_dy100m[i];
	}
	
	//1-секундные точки
	CNiReal64Matrix line_w1s( 2, doc->m_dn1s, 1.0);
	for( i = 0; i < doc->m_dn1s; i++) {
		line_w1s( 0, i) = doc->m_dx1s[i];
		line_w1s( 1, i) = doc->m_dy1s[i];
	}

	//10-секундные точки
	CNiReal64Matrix line_w10s( 2, doc->m_dn10s, 1.0);
	for( i = 0; i < doc->m_dn10s; i++) {
		line_w10s( 0, i) = doc->m_dx10s[i];
		line_w10s( 1, i) = doc->m_dy10s[i];
	}

	//100-сек точки
	CNiReal64Matrix line_w100s( 2, doc->m_dn100s, 1.0);
	for( i = 0; i < doc->m_dn100s; i++) {
		line_w100s( 0, i) = doc->m_dx100s[i];
		line_w100s( 1, i) = doc->m_dy100s[i];
	}

	//I1 точки
	CNiReal64Matrix line_i1( 2, doc->m_dn_i1, 1.0);
	for( i = 0; i < doc->m_dn_i1; i++) {
		line_i1( 0, i) = doc->m_dx_i1[i];
		line_i1( 1, i) = doc->m_dy_i1[i];
	}

	//I2 точки
	CNiReal64Matrix line_i2( 2, doc->m_dn_i2, 1.0);
	for( i = 0; i < doc->m_dn_i2; i++) {
		line_i2( 0, i) = doc->m_dx_i2[i];
		line_i2( 1, i) = doc->m_dy_i2[i];
	}

	//Vpc точки
	CNiReal64Matrix line_vpc( 2, doc->m_dn_vpc, 1.0);
	for( i = 0; i < doc->m_dn_vpc; i++) {
		line_vpc( 0, i) = doc->m_dx_vpc[i];
		line_vpc( 1, i) = doc->m_dy_vpc[i];
	}

	//AmplAng точки
	CNiReal64Matrix line_aa( 2, doc->m_dn_aa, 1.0);
	for( i = 0; i < doc->m_dn_aa; i++) {
		line_aa( 0, i) = doc->m_dx_aa[i];
		line_aa( 1, i) = doc->m_dy_aa[i];
	}

	//T1 точки
	CNiReal64Matrix line_t1( 2, doc->m_dn_t1, 1.0);
	for( i = 0; i < doc->m_dn_t1; i++) {
		line_t1( 0, i) = doc->m_dx_t1[i];
		line_t1( 1, i) = doc->m_dy_t1[i];
	}

	//T2 точки
	CNiReal64Matrix line_t2( 2, doc->m_dn_t2, 1.0);
	for( i = 0; i < doc->m_dn_t2; i++) {
		line_t2( 0, i) = doc->m_dx_t2[i];
		line_t2( 1, i) = doc->m_dy_t2[i];
	}

  //T3 точки
	CNiReal64Matrix line_t3( 2, doc->m_dn_t3, 1.0);
	for( i = 0; i < doc->m_dn_t3; i++) {
		line_t3( 0, i) = doc->m_dx_t3[i];
		line_t3( 1, i) = doc->m_dy_t3[i];
	}

	//Tsa точки
	CNiReal64Matrix line_tsa( 2, doc->m_dn_tsa, 1.0);
	for( i = 0; i < doc->m_dn_tsa; i++) {
		line_tsa( 0, i) = doc->m_dx_tsa[i];
		line_tsa( 1, i) = doc->m_dy_tsa[i];
	}

	
	//маленькие экранчики
	switch( m_nTMeaningInd) {
		case 0: m_ctlSmallGraph1.PlotXY( line_w100m, true); break;
		case 1: m_ctlSmallGraph1.PlotXY( line_w1s, true); break;
		case 2: m_ctlSmallGraph1.PlotXY( line_w10s, true); break;
		case 3: m_ctlSmallGraph1.PlotXY( line_w100s, true); break;
	}
	m_ctlSmallGraph2.PlotXY( line_i1, true);
	m_ctlSmallGraph3.PlotXY( line_i2, true);
	m_ctlSmallGraph4.PlotXY( line_vpc, true);
	m_ctlSmallGraph5.PlotXY( line_aa, true);
	
  switch( m_nRadT1) {
    case 0: m_ctlSmallGraph6.PlotXY( line_t1, true); break;
    case 1: m_ctlSmallGraph6.PlotXY( line_t2, true); break;
    case 2: m_ctlSmallGraph6.PlotXY( line_t3, true); break;
  }
	
  switch( m_nRadT2) {
    case 0: m_ctlSmallGraph7.PlotXY( line_t1, true); break;
    case 1: m_ctlSmallGraph7.PlotXY( line_t2, true); break;
    case 2: m_ctlSmallGraph7.PlotXY( line_t3, true); break;
  }

	m_ctlSmallGraph8.PlotXY( line_tsa, true);

	//doc->RecalculateStatistics();
	m_strSoftwareVersion = ( ( CSlg2App *) AfxGetApp())->m_strSoftwareVer;
	switch( m_nMainGraph) {
		case 1:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 0, 127, 0));

			if( m_nTMeaningInd == 0) {
				m_ctlMainGraph.PlotXY( line_w100m, true);
				m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_100m_min);
				m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_100m_mean);
				m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_100m_max);
				m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_100m_rms);
			}

			if( m_nTMeaningInd == 1) {
				m_ctlMainGraph.PlotXY( line_w1s, true);
				m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_1s_min);
				m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_1s_mean);
				m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_1s_max);
				m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_1s_rms);
			}
			
			if( m_nTMeaningInd == 2) {
				m_ctlMainGraph.PlotXY( line_w10s, true);
				m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_10s_min);
				m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_10s_mean);
				m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_10s_max);
				m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_10s_rms);
			}

			if( m_nTMeaningInd == 3) {
				m_ctlMainGraph.PlotXY( line_w100s, true);
				m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_100s_min);
				m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_100s_mean);
				m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_100s_max);
				m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_100s_rms);
			}
			
		break;

		case 2:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 127, 0, 0));
			m_ctlMainGraph.PlotXY( line_i1, true);
			m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_i1_min);
			m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_i1_mean);
			m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_i1_max);
			m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_i1_rms);
		break;

		case 3:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 0, 0, 127));
			m_ctlMainGraph.PlotXY( line_i2, true);
			m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_i2_min);
			m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_i2_mean);
			m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_i2_max);
			m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_i2_rms);
		break;

		case 4:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 0, 127, 0));
			m_ctlMainGraph.PlotXY( line_vpc, true);
			m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_vpc_min);
			m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_vpc_mean);
			m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_vpc_max);
			m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_vpc_rms);
		break;

		case 5:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 127, 0, 0));
			m_ctlMainGraph.PlotXY( line_aa, true);
			m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_aa_min);
			m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_aa_mean);
			m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_aa_max);
			m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_aa_rms);
		break;

		case 6:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 0, 0, 127));
			
      switch( m_nRadT1) {
        case 0:
          m_ctlMainGraph.PlotXY( line_t1, true);
          m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_t1_min);
			    m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_t1_mean);
			    m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_t1_max);
			    m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_t1_rms);
        break;
        case 1:
          m_ctlMainGraph.PlotXY( line_t2, true);
          m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_t2_min);
			    m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_t2_mean);
			    m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_t2_max);
			    m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_t2_rms);
        break;
        case 2:
          m_ctlMainGraph.PlotXY( line_t3, true);
          m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_t3_min);
			    m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_t3_mean);
			    m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_t3_max);
			    m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_t3_rms);
        break;
      }
		break;

		case 7:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 0, 127, 0));
			
      switch( m_nRadT2) {
        case 0:
          m_ctlMainGraph.PlotXY( line_t1, true);
          m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_t1_min);
			    m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_t1_mean);
			    m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_t1_max);
			    m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_t1_rms);
        break;
        case 1:
          m_ctlMainGraph.PlotXY( line_t2, true);
          m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_t2_min);
			    m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_t2_mean);
			    m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_t2_max);
			    m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_t2_rms);
        break;
        case 2:
          m_ctlMainGraph.PlotXY( line_t3, true);
          m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_t3_min);
			    m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_t3_mean);
			    m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_t3_max);
			    m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_t3_rms);
        break;
      }
		break;

		case 8:
			m_ctlMainGraph.GetPlots().Item( 1).SetLineColor( RGB( 127, 0, 0));
			m_ctlMainGraph.PlotXY( line_tsa, true);
			m_strGraphMinVal.Format( _T("%.4f"), doc->m_d_tsa_min);
			m_strGraphMeanVal.Format( _T("%.4f"), doc->m_d_tsa_mean);
			m_strGraphMaxVal.Format( _T("%.4f"), doc->m_d_tsa_max);
			m_strGraphRmsVal.Format( _T("%.4f"), doc->m_d_tsa_rms);
		break;

		default:
			m_nMainGraph = 1;
		break;
	}
	
	//статистика по каждому параметру
	switch( m_nTMeaningInd) {
		case 0:
			m_strSmGr1_min.Format( _T("%.4f"), doc->m_d_100m_min);
			m_strSmGr1_mean.Format( _T("%.4f"), doc->m_d_100m_mean);
			m_strSmGr1_max.Format( _T("%.4f"), doc->m_d_100m_max);
			m_strSmGr1_rms.Format( _T("%.4f"), doc->m_d_100m_rms);
		break;

		case 1:
			m_strSmGr1_min.Format( _T("%.4f"), doc->m_d_1s_min);
			m_strSmGr1_mean.Format( _T("%.4f"), doc->m_d_1s_mean);
			m_strSmGr1_max.Format( _T("%.4f"), doc->m_d_1s_max);
			m_strSmGr1_rms.Format( _T("%.4f"), doc->m_d_1s_rms);
		break;

		case 2:
			m_strSmGr1_min.Format( _T("%.4f"), doc->m_d_10s_min);
			m_strSmGr1_mean.Format( _T("%.4f"), doc->m_d_10s_mean);
			m_strSmGr1_max.Format( _T("%.4f"), doc->m_d_10s_max);
			m_strSmGr1_rms.Format( _T("%.4f"), doc->m_d_10s_rms);
		break;

		case 3:
			m_strSmGr1_min.Format( _T("%.4f"), doc->m_d_100s_min);
			m_strSmGr1_mean.Format( _T("%.4f"), doc->m_d_100s_mean);
			m_strSmGr1_max.Format( _T("%.4f"), doc->m_d_100s_max);
			m_strSmGr1_rms.Format( _T("%.4f"), doc->m_d_100s_rms);
		break;
	}

	m_strSmGr2_min.Format( _T("%.4f"), doc->m_d_i1_min);
	m_strSmGr2_mean.Format( _T("%.4f"), doc->m_d_i1_mean);
	m_strSmGr2_max.Format( _T("%.4f"), doc->m_d_i1_max);
	m_strSmGr2_rms.Format( _T("%.4f"), doc->m_d_i1_rms);

	m_strSmGr3_min.Format( _T("%.4f"), doc->m_d_i2_min);
	m_strSmGr3_mean.Format( _T("%.4f"), doc->m_d_i2_mean);
	m_strSmGr3_max.Format( _T("%.4f"), doc->m_d_i2_max);
	m_strSmGr3_rms.Format( _T("%.4f"), doc->m_d_i2_rms);
	
	m_strSmGr4_min.Format( _T("%.4f"), doc->m_d_vpc_min);
	m_strSmGr4_mean.Format( _T("%.4f"), doc->m_d_vpc_mean);
	m_strSmGr4_max.Format( _T("%.4f"), doc->m_d_vpc_max);
	m_strSmGr4_rms.Format( _T("%.4f"), doc->m_d_vpc_rms);
	
	m_strSmGr5_min.Format( _T("%.4f"), doc->m_d_aa_min);
	m_strSmGr5_mean.Format( _T("%.4f"), doc->m_d_aa_mean);
	m_strSmGr5_max.Format( _T("%.4f"), doc->m_d_aa_max);
	m_strSmGr5_rms.Format( _T("%.4f"), doc->m_d_aa_rms);
	
  switch( m_nRadT1) {
    case 0:
      m_strSmGr6_min.Format( _T("%.4f"), doc->m_d_t1_min);
	    m_strSmGr6_mean.Format( _T("%.4f"), doc->m_d_t1_mean);
	    m_strSmGr6_max.Format( _T("%.4f"), doc->m_d_t1_max);
	    m_strSmGr6_rms.Format( _T("%.4f"), doc->m_d_t1_rms);
    break;
    case 1:
      m_strSmGr6_min.Format( _T("%.4f"), doc->m_d_t2_min);
	    m_strSmGr6_mean.Format( _T("%.4f"), doc->m_d_t2_mean);
	    m_strSmGr6_max.Format( _T("%.4f"), doc->m_d_t2_max);
	    m_strSmGr6_rms.Format( _T("%.4f"), doc->m_d_t2_rms);
    break;
    case 2:
      m_strSmGr6_min.Format( _T("%.4f"), doc->m_d_t3_min);
	    m_strSmGr6_mean.Format( _T("%.4f"), doc->m_d_t3_mean);
	    m_strSmGr6_max.Format( _T("%.4f"), doc->m_d_t3_max);
	    m_strSmGr6_rms.Format( _T("%.4f"), doc->m_d_t3_rms);
    break;
  }
	
	switch( m_nRadT2) {
    case 0:
      m_strSmGr7_min.Format( _T("%.4f"), doc->m_d_t1_min);
	    m_strSmGr7_mean.Format( _T("%.4f"), doc->m_d_t1_mean);
	    m_strSmGr7_max.Format( _T("%.4f"), doc->m_d_t1_max);
	    m_strSmGr7_rms.Format( _T("%.4f"), doc->m_d_t1_rms);
    break;
    case 1:
      m_strSmGr7_min.Format( _T("%.4f"), doc->m_d_t2_min);
	    m_strSmGr7_mean.Format( _T("%.4f"), doc->m_d_t2_mean);
	    m_strSmGr7_max.Format( _T("%.4f"), doc->m_d_t2_max);
	    m_strSmGr7_rms.Format( _T("%.4f"), doc->m_d_t2_rms);
    break;
    case 2:
      m_strSmGr7_min.Format( _T("%.4f"), doc->m_d_t3_min);
	    m_strSmGr7_mean.Format( _T("%.4f"), doc->m_d_t3_mean);
	    m_strSmGr7_max.Format( _T("%.4f"), doc->m_d_t3_max);
	    m_strSmGr7_rms.Format( _T("%.4f"), doc->m_d_t3_rms);
    break;
  }
	
	m_strSmGr8_min.Format( _T("%.4f"), doc->m_d_tsa_min);
	m_strSmGr8_mean.Format( _T("%.4f"), doc->m_d_tsa_mean);
	m_strSmGr8_max.Format( _T("%.4f"), doc->m_d_tsa_max);
	m_strSmGr8_rms.Format( _T("%.4f"), doc->m_d_tsa_rms);

	EndWaitCursor();

	UpdateData( FALSE);
}

void CMainView::OnInitialUpdate() 
{
	m_dKimpSec = (( CSlg2App *) AfxGetApp())->m_dKimpSec;

	m_nMainGraph = 1;
	CFormView::OnInitialUpdate();	

	GetDlgItem( IDC_MIN_LABEL)->SetFont( &m_pFont);
	GetDlgItem( IDC_MINVAL_LABEL)->SetFont( &m_pFont);
	GetDlgItem( IDC_MEAN_LABEL)->SetFont( &m_pFont);
	GetDlgItem( IDC_MEANVAL_LABEL)->SetFont( &m_pFont);
	GetDlgItem( IDC_MAX_LABEL)->SetFont( &m_pFont);
	GetDlgItem( IDC_MAXVAL_LABEL)->SetFont( &m_pFont);
	GetDlgItem( IDC_RMS_LABEL)->SetFont( &m_pFont);
	GetDlgItem( IDC_RMSVAL_LABEL)->SetFont( &m_pFont);
	
	m_strThisSoftwareVersion.LoadString( IDS_SOFTWARE_VERSION);
	UpdateData( FALSE);

	m_ctlMainGraph.GetCursors().Item( "CursorStart").SetVisible( ((CSlg2Doc *) GetDocument())->m_bShowCursors);
	m_ctlMainGraph.GetCursors().Item( "CursorEnd").SetVisible( ((CSlg2Doc *) GetDocument())->m_bShowCursors);

	
	GetDlgItem( IDC_IC_RED_CURSOR)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR1_X_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR1_Y_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);

	GetDlgItem( IDC_IC_BLUE_CURSOR)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR2_X_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR2_Y_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);

	GetDlgItem( IDC_LBL_CURSOR_DX_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR_DY_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_CURSOR_FRAME)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);

	//блокирование недостуаных для просмотра времен осреднения (для них недостаточно статистики)
	if( ( ( CSlg2Doc *) GetDocument())->m_dn10s < 1.) {
		m_nTMeaningInd = 0;
		GetDlgItem( IDC_RAD_MEANING3)->EnableWindow( false);
	}
	else {
		GetDlgItem( IDC_RAD_MEANING3)->EnableWindow( true);
	}

	if( ( ( CSlg2Doc *) GetDocument())->m_dn100s < 1.) {
		m_nTMeaningInd = 0;
		GetDlgItem( IDC_RAD_MEANING4)->EnableWindow( false);
	}
	else {
		GetDlgItem( IDC_RAD_MEANING4)->EnableWindow( true);
	}

	SetTimer( MY_MAXIMIZE_VIEW_TIMER, 100, NULL);
	SetTimer( MY_TIMER_1000, 1000, NULL);
}

void CMainView::OnTimer(UINT nIDEvent) 
{
	CString strError;
	UpdateData( TRUE);
	
	//**** **** **** **** **** **** **** **** **** **** **** **** **** **** ****
	//событие 1000 мсек
	//**** **** **** **** **** **** **** **** **** **** **** **** **** **** ****
	if( nIDEvent == MY_TIMER_1000) {
		//////////////////////////////////////////////////////////////////////
		// Обновляем управленческие параметры
		//////////////////////////////////////////////////////////////////////
		m_strParam1Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_btParam1 * m_dKimpSec);		//код амплитуды
		m_strParam2Val.Format( _T("%d"), (( CSlg2App *) AfxGetApp())->m_btParam2);											//код такта подставки
		m_strParam3Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_btParam3 / 250.);		//коэффициент M
		m_strParam4Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_btParam4 / 100.);		//начальная мода
		m_strParam5Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_shFlashI1min / 65535. * 0.75);
		m_strParam6Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_shFlashI2min / 65535. * 0.75);
		m_strParam7Val.Format( _T("%.2f"), ( ( double) (( CSlg2App *) AfxGetApp())->m_shFlashAmplAng1min / 65535. * 6.0));
		m_strParam8Val.Format( _T("%.5f"), ( ( double) (( CSlg2App *) AfxGetApp())->m_shFlashDecCoeff) / 65535.);
		m_strParam9Val.Format( _T("%d"), (( CSlg2App *) AfxGetApp())->m_shFlashSa);
		

		//////////////////////////////////////////////////////////////////////
		// Обновляем графики
		//////////////////////////////////////////////////////////////////////
		//RefreshGraphs();
		//Beep( 100, 10);
	}

	if( nIDEvent == MY_MAXIMIZE_VIEW_TIMER) {
		KillTimer( MY_MAXIMIZE_VIEW_TIMER);
		(( CSlg2App *) AfxGetApp())->GetMainWnd()->ShowWindow( SW_MAXIMIZE);
	}

	if( nIDEvent == MY_REFRESH_VIEW_TIMER) {
		KillTimer( MY_REFRESH_VIEW_TIMER);

		m_strParam1Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_btParam1 * m_dKimpSec);		//код амплитуды
		m_strParam2Val.Format( _T("%d"), (( CSlg2App *) AfxGetApp())->m_btParam2);											//код такта подставки
		m_strParam3Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_btParam3 / 250.);		//коэффициент M
		m_strParam4Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_btParam4 / 100.);		//начальная мода
		m_strParam5Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_shFlashI1min / 65535. * 0.75);
		m_strParam6Val.Format( _T("%.2f"), ( double) (( CSlg2App *) AfxGetApp())->m_shFlashI2min / 65535. * 0.75);
		m_strParam7Val.Format( _T("%.2f"), ( ( double) (( CSlg2App *) AfxGetApp())->m_shFlashAmplAng1min / 65535. * 6.0));
		m_strParam8Val.Format( _T("%.5f"), ( ( double) (( CSlg2App *) AfxGetApp())->m_shFlashDecCoeff) / 65535.);
		m_strParam9Val.Format( _T("%d"), (( CSlg2App *) AfxGetApp())->m_shFlashSa);

		RefreshGraphs();
	}

	CFormView::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CMainView, CFormView)
  //{{AFX_EVENTSINK_MAP(CMainView)
	ON_EVENT(CMainView, IDC_GRAPH1, -600 /* Click */, OnClickGraph1, VTS_NONE)
	ON_EVENT(CMainView, IDC_GRAPH2, -600 /* Click */, OnClickGraph2, VTS_NONE)
	ON_EVENT(CMainView, IDC_GRAPH3, -600 /* Click */, OnClickGraph3, VTS_NONE)
	ON_EVENT(CMainView, IDC_GRAPH4, -600 /* Click */, OnClickGraph4, VTS_NONE)
	ON_EVENT(CMainView, IDC_GRAPH5, -600 /* Click */, OnClickGraph5, VTS_NONE)
	ON_EVENT(CMainView, IDC_GRAPH6, -600 /* Click */, OnClickGraph6, VTS_NONE)
	ON_EVENT(CMainView, IDC_GRAPH7, -600 /* Click */, OnClickGraph7, VTS_NONE)
	ON_EVENT(CMainView, IDC_GRAPH8, -600 /* Click */, OnClickGraph8, VTS_NONE)
	ON_EVENT(CMainView, IDC_MAIN_GRAPH, 1 /* CursorChange */, OnCursorChangeMainGraph, VTS_PI4 VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMainView::OnClickGraph1() 
{
	UpdateData( TRUE);
	m_nMainGraph = 1;
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("''/sec"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnClickGraph2() 
{
	m_nMainGraph = 2;
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("mA"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnClickGraph3() 
{
	m_nMainGraph = 3;	
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("mA"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnClickGraph4() 
{
	m_nMainGraph = 4;	
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("V"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnClickGraph5() 
{
	m_nMainGraph = 5;
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("V"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnClickGraph6() 
{
	m_nMainGraph = 6;
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("°C"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnClickGraph7() 
{
	m_nMainGraph = 7;
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("°C"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnClickGraph8() 
{
	m_nMainGraph = 8;
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("мсек"));
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer( 100);
}

void CMainView::OnDestroy() 
{
	UpdateData( true);
	((CSlg2App *) AfxGetApp())->m_dKimpSec = m_dKimpSec;

	CFormView::OnDestroy();
	VERIFY( m_pFont.DeleteObject());
}

void CMainView::OnKillfocusEdtKImpSec() 
{
	UpdateData( true);
	if( (( CSlg2Doc *) GetDocument())->m_strCurrentFileName.IsEmpty()) return;
	((CSlg2App *) AfxGetApp())->m_dKimpSec = m_dKimpSec;
	(( CSlg2Doc *) GetDocument())->ReadDataFile( (( CSlg2Doc *) GetDocument())->m_strCurrentFileName, NULL);
	(( CSlg2Doc *) GetDocument())->RecalculateStatistics();
}

void CMainView::OnHistogram() 
{
	CDlgHisto dlg;
	dlg.m_doc = ((CSlg2Doc *) GetDocument());
	dlg.DoModal();
}

void CMainView::OnAlanCurve() 
{
	/*CDlgAlanCurve dlg;
	dlg.m_nDataFileLines = ((CSlg2Doc *) GetDocument())->nDataFileLines;
	dlg.m_strFileName = ((CSlg2Doc *) GetDocument())->m_strCurrentFileName;
	dlg.DoModal();*/
}

void CMainView::OnBtnExport() 
{
	CDlgExport dlg;
	dlg.m_nDataFileLines = ((CSlg2Doc *) GetDocument())->nDataFileLines;
	dlg.m_strFileName = ((CSlg2Doc *) GetDocument())->m_strCurrentFileName;
	dlg.m_nStatFileVersion = ((CSlg2Doc *) GetDocument())->m_nStatFileVersion;
	dlg.DoModal();
}

void CMainView::SetRefreshTimer( int nPeriod)
{
	SetTimer( MY_REFRESH_VIEW_TIMER, nPeriod, NULL);
}

void CMainView::OnRadMeaning100msec() 
{
	SetRefreshTimer();
}

void CMainView::OnRadMeaning1sec() 
{
	SetRefreshTimer();
}

void CMainView::OnRadMeaning10sec() 
{
	SetRefreshTimer();
}

void CMainView::OnRadMeaning100sec() 
{
	SetRefreshTimer();
}

void CMainView::OnUpdateZoomin(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !( ( CSlg2Doc *)GetDocument())->m_strCurrentFileName.IsEmpty()
									&&
									( ( CSlg2Doc *)GetDocument())->m_bShowCursors);
}

void CMainView::OnUpdateRestoreZoom(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !( ( CSlg2Doc *)GetDocument())->m_strCurrentFileName.IsEmpty()
									&&
									( ( CSlg2Doc *)GetDocument())->m_bZoomed);
}

void CMainView::OnZoomin() 
{
	//m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetCaption( _T("''/sec"));
	double CurStartX = m_ctlMainGraph.GetCursors().Item( "CursorStart").GetXPosition();
	double CurStartY = m_ctlMainGraph.GetCursors().Item( "CursorStart").GetYPosition();
	double CurEndX = m_ctlMainGraph.GetCursors().Item( "CursorEnd").GetXPosition();
	double CurEndY = m_ctlMainGraph.GetCursors().Item( "CursorEnd").GetYPosition();

	double swap;
	if( CurStartX > CurEndX) {
		swap = CurStartX;
		CurStartX = CurEndX;
		CurEndX = swap;
	}

	if( CurStartY > CurEndY) {
		swap = CurStartY;
		CurStartY = CurEndY;
		CurEndY = swap;
	}

	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetMinimum( CurStartY);
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetMaximum( CurEndY);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetMinimum( CurStartX);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetMaximum( CurEndX);
	
	((CSlg2Doc *) GetDocument())->m_bZoomed = true;
	SetRefreshTimer();
}

void CMainView::OnRestoreZoom() 
{
	m_ctlMainGraph.GetAxes().Item( "YAxis-1").SetAutoScale( true);
	m_ctlMainGraph.GetAxes().Item( "XAxis").SetAutoScale( true);
	((CSlg2Doc *) GetDocument())->m_bZoomed = false;
	SetRefreshTimer();
}

void CMainView::OnShowCursors() 
{
	((CSlg2Doc *) GetDocument())->m_bShowCursors ^= 1;
	m_ctlMainGraph.GetCursors().Item( "CursorStart").SetVisible( ((CSlg2Doc *) GetDocument())->m_bShowCursors);
	m_ctlMainGraph.GetCursors().Item( "CursorEnd").SetVisible( ((CSlg2Doc *) GetDocument())->m_bShowCursors);

	GetDlgItem( IDC_IC_RED_CURSOR)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR1_X_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR1_Y_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);

	GetDlgItem( IDC_IC_BLUE_CURSOR)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR2_X_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR2_Y_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);

	GetDlgItem( IDC_LBL_CURSOR_DX_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_LBL_CURSOR_DY_VAL)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	GetDlgItem( IDC_CURSOR_FRAME)->ShowWindow( ((CSlg2Doc *) GetDocument())->m_bShowCursors ? SW_SHOW : SW_HIDE);
	
}

void CMainView::OnCursorChangeMainGraph(long FAR* CursorIndex, VARIANT FAR* XPos, VARIANT FAR* YPos, BOOL FAR* bTracking) 
{
	double CurStartX = m_ctlMainGraph.GetCursors().Item( "CursorStart").GetXPosition();
	double CurStartY = m_ctlMainGraph.GetCursors().Item( "CursorStart").GetYPosition();
	double CurEndX = m_ctlMainGraph.GetCursors().Item( "CursorEnd").GetXPosition();
	double CurEndY = m_ctlMainGraph.GetCursors().Item( "CursorEnd").GetYPosition();

	m_strLblCursorDxVal.Format( _T("%.3f"), fabs( CurStartX - CurEndX));
	m_strLblCursorDyVal.Format( _T("%.3f"), fabs( CurStartY - CurEndY));

	m_strCur1X_val.Format( _T("%.3f"), CurStartX);
	m_strCur1Y_val.Format( _T("%.3f"), CurStartY);
	m_strCur2X_val.Format( _T("%.3f"), CurEndX);
	m_strCur2Y_val.Format( _T("%.3f"), CurEndY);

	UpdateData( FALSE);
}

void CMainView::OnRadT1Td1() 
{
	m_ctlSmallGraph6.SetCaption( _T("Термодатчик 1 [КЛ], [°C]"));
  SetRefreshTimer( 100);
}

void CMainView::OnRadT1Td2() 
{
	m_ctlSmallGraph6.SetCaption( _T("Термодатчик 2 [КЛ], [°C]"));
  SetRefreshTimer( 100);
}

void CMainView::OnRadT1Td3() 
{
	m_ctlSmallGraph6.SetCaption( _T("Термодатчик 3 [Корпус], [°C]"));
  SetRefreshTimer( 100);
}

void CMainView::OnRadT2Td1() 
{
	m_ctlSmallGraph7.SetCaption( _T("Термодатчик 1 [КЛ], [°C]"));
  SetRefreshTimer( 100);
}

void CMainView::OnRadT2Td2() 
{
	m_ctlSmallGraph7.SetCaption( _T("Термодатчик 2 [КЛ], [°C]"));
  SetRefreshTimer( 100);
}

void CMainView::OnRadT2Td3() 
{
	m_ctlSmallGraph7.SetCaption( _T("Термодатчик 3 [Корпус], [°C]"));
  SetRefreshTimer( 100);
}