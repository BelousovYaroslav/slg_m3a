// DecCoeffCalc.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "DecCoeffCalc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern double gl_dNdU_dN[];
extern double gl_dNdU_dU[];
extern double gl_dNdU_DecCoeff[];
extern int gl_dec_coeff_cntr;
extern BOOL gl_dec_coeff_overround;

extern double gl_dec_coeff_dN_acc;
extern double gl_dec_coeff_dU_acc;
extern double gl_dec_coeff_acc;
extern int gl_dec_coeff_acc_cntr;

extern double gl_dec_coeff_low_filter;

extern bool PutByteInCircleBuffer(BYTE bt);

#define MY_REFRESH_TIMER 100

/////////////////////////////////////////////////////////////////////////////
// CDecCoeffCalc dialog


CDecCoeffCalc::CDecCoeffCalc(CWnd* pParent /*=NULL*/)
	: CDialog(CDecCoeffCalc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecCoeffCalc)
	m_strDecCoeff = _T("");
	//}}AFX_DATA_INIT
}


void CDecCoeffCalc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecCoeffCalc)
	DDX_Control(pDX, IDC_CWG_DN, m_ctlGraphDn);
	DDX_Control(pDX, IDC_CWG_DU, m_ctlGraphDu);
	DDX_Control(pDX, IDC_CWG_K_DEC, m_ctlGraphDecCoeff);
	DDX_Text(pDX, IDC_LBL_DEC_COEFF, m_strDecCoeff);
	DDX_Control(pDX, IDC_CWE_DU_LOW_EDGE, m_ctlNedtLowFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDecCoeffCalc, CDialog)
	//{{AFX_MSG_MAP(CDecCoeffCalc)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecCoeffCalc message handlers

BOOL CDecCoeffCalc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for( int i=0; i<CYCLE_BUFFER_DN_DU; i++) {
		gl_dNdU_dN[ i] = 0.;
		gl_dNdU_dU[ i] = 0.;
		gl_dNdU_DecCoeff[i] = 0.;
	}
	gl_dec_coeff_dN_acc = 0.;
	gl_dec_coeff_dU_acc = 0.;

	gl_dec_coeff_acc = 0.;
	gl_dec_coeff_cntr = 0;
	gl_dec_coeff_overround = false;
	
	m_ctlNedtLowFilter.SetValue( gl_dec_coeff_low_filter);

	SetTimer( MY_REFRESH_TIMER, 100, NULL);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDecCoeffCalc::OnOK() 
{
	CDialog::OnOK();
}

void CDecCoeffCalc::OnTimer(UINT nIDEvent) 
{
	CSlg2App *app = (CSlg2App*) AfxGetApp();

	if( nIDEvent == MY_REFRESH_TIMER) {
		
		if( gl_dec_coeff_overround) {
			
			CNiReal64Matrix line_dN( 2, CYCLE_BUFFER_DN_DU, 1.0);
			CNiReal64Matrix line_dU( 2, CYCLE_BUFFER_DN_DU, 1.0);
			CNiReal64Matrix line_K(  2, CYCLE_BUFFER_DN_DU, 1.0);

			for( int i=0; i < CYCLE_BUFFER_DN_DU; i++) {
				line_dN( 0, i) = i;
				line_dN( 1, i) = gl_dNdU_dN[ ( gl_dec_coeff_cntr + i) % CYCLE_BUFFER_DN_DU];

				line_dU( 0, i) = i;
				line_dU( 1, i) = gl_dNdU_dU[ ( gl_dec_coeff_cntr + i) % CYCLE_BUFFER_DN_DU];

				line_K( 0, i) = i;
				line_K( 1, i) = gl_dNdU_DecCoeff[ ( gl_dec_coeff_cntr + i) % CYCLE_BUFFER_DN_DU];
			}

			m_ctlGraphDn.PlotXY( line_dN, true);
			m_ctlGraphDu.PlotXY( line_dU, true);
			m_ctlGraphDecCoeff.PlotXY( line_K, true);
		}
		else {
			if( gl_dec_coeff_cntr > 5) {
				CNiReal64Matrix line_dN( 2, gl_dec_coeff_cntr - 1, 1.0);
				CNiReal64Matrix line_dU( 2, gl_dec_coeff_cntr - 1, 1.0);
				CNiReal64Matrix line_K(  2, gl_dec_coeff_cntr - 1, 1.0);

				for( int i = 0; i < gl_dec_coeff_cntr - 1; i++) {
					line_dN( 0, i) = i;
					line_dN( 1, i) = gl_dNdU_dN[ i];

					line_dU( 0, i) = i;
					line_dU( 1, i) = gl_dNdU_dU[ i];

					line_K( 0, i) = i;
					line_K( 1, i) = gl_dNdU_DecCoeff[ i];
				}

				m_ctlGraphDn.PlotXY( line_dN, true);
				m_ctlGraphDu.PlotXY( line_dU, true);
				m_ctlGraphDecCoeff.PlotXY( line_K, true);

				//Beep( 100, 10);
			}
		}

		//m_strDecCoeff.Format( _T("%.6f"), gl_dec_coeff_acc / gl_dec_coeff_acc_cntr);
		m_strDecCoeff.Format( _T("%.6f"), gl_dec_coeff_dN_acc / gl_dec_coeff_dU_acc);
		UpdateData( false);
	}

	CDialog::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CDecCoeffCalc, CDialog)
    //{{AFX_EVENTSINK_MAP(CDecCoeffCalc)
	ON_EVENT(CDecCoeffCalc, IDC_CWE_DU_LOW_EDGE, 1 /* ValueChanged */, OnValueChangedCweDuLowEdge, VTS_PVARIANT VTS_PVARIANT VTS_BOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDecCoeffCalc::OnValueChangedCweDuLowEdge(VARIANT FAR* Value, VARIANT FAR* PreviousValue, BOOL OutOfRange) 
{
	gl_dec_coeff_low_filter = m_ctlNedtLowFilter.GetValue();
}
