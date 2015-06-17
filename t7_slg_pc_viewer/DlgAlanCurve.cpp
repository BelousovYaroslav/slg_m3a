// DlgAlanCurve.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "DlgAlanCurve.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_START_CALCULATION_TIMER 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgAlanCurve dialog


CDlgAlanCurve::CDlgAlanCurve(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlanCurve::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlanCurve)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAlanCurve::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlanCurve)
	DDX_Control(pDX, IDC_PRGRSS, m_ctlPrgrss);
	DDX_Control(pDX, IDC_ALAN_CURVE, m_ctlAlanCurve);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlanCurve, CDialog)
	//{{AFX_MSG_MAP(CDlgAlanCurve)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlanCurve message handlers

BOOL CDlgAlanCurve::OnInitDialog() 
{
	SetTimer( MY_START_CALCULATION_TIMER, 100, NULL);
	CDialog::OnInitDialog();
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlanCurve::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == MY_START_CALCULATION_TIMER) {
		KillTimer( MY_START_CALCULATION_TIMER);

		FILE *fh;
		fh = fopen( m_strFileName, "r");

		int nAlanPoints = m_nDataFileLines / 5 - 5;

		CNiReal64Matrix AlanCurve( 2, nAlanPoints, 1.0);
		int nAlanPointsCounter = 0;
	
		m_ctlPrgrss.SetRange32( 5, (m_nDataFileLines / 5 - 5));

		double tmean;
		double sigma;

		for( int i = 5; i < (m_nDataFileLines / 5 - 5); i+=5) {
			m_ctlPrgrss.SetPos( i);

			fseek( fh, 0, SEEK_SET);

			double *w = new double[ m_nDataFileLines / i + 10];
			int nw = 0;
			double *t = new double[ m_nDataFileLines / i + 10];
			int nt = 0;
		
			int nAvCntr = 0;
		
			double summdn = 0., summdt = 0.;
			int nsummdn = 0, nsummdt = 0;

			while( 1) {
				float f1, f2;
				int int1, int2, int3;
				fscanf( fh, "%f\t%f\t%d\t%d\t%d\n", &f1, &f2, &int1, &int2, &int3);

				summdt = summdt + (( double) int3 / 32768.);
				summdn = summdn + (2.903 * f1 / 4.);
				nsummdn++; nsummdt++;

				nAvCntr++;
				if( nAvCntr == i) {
					w[ nw++] = summdn / summdt;
					t[ nt++] = summdt;
					summdn = summdt = 0.;
					nAvCntr = 0;
				}

				if( feof( fh)) break;
			}

			--nw; --nt;
			double summdts = 0.;
			double summW = 0.;
			for( int k=0; k<nw; k++) {
				summdts = summdts + t[k];
				summW = summW + w[k];
			}
			tmean = summdts / nw;
			double wmean = summW / nw;
			sigma = 0.;
			for( k=0; k<nw; k++) {
				sigma = sigma + ( w[k] - wmean) * ( w[k] - wmean);
			}
			sigma = sqrt( sigma / nw);
		
			AlanCurve( 0, nAlanPointsCounter) = tmean;
			AlanCurve( 1, nAlanPointsCounter++) = sigma;

			delete w;
			delete t;
			
		}	

		fclose(fh);

		for( i=nAlanPointsCounter; i<nAlanPoints; i++) {
			AlanCurve( 0, nAlanPointsCounter) = tmean;
			AlanCurve( 1, nAlanPointsCounter++) = sigma;
		}
		m_ctlAlanCurve.PlotXY( AlanCurve, true);
	}

	CDialog::OnTimer(nIDEvent);
}
