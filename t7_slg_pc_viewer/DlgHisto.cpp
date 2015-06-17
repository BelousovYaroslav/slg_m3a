// DlgHisto.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "DlgHisto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHisto dialog


CDlgHisto::CDlgHisto(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHisto::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHisto)
	m_nBins = 20;
	//}}AFX_DATA_INIT
	m_doc = NULL;
	
}


void CDlgHisto::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHisto)
	DDX_Control(pDX, IDC_CW_HISTO, m_ctlHisto100m);
	DDX_Text(pDX, IDC_EDT_N_BINS, m_nBins);
	DDX_Control(pDX, IDC_CW_HISTO_1S, m_ctlHisto1s);
	DDX_Control(pDX, IDC_CW_HISTO_10S, m_ctlHisto10s);
	DDX_Control(pDX, IDC_CW_HISTO_100S, m_ctlHisto100s);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHisto, CDialog)
	//{{AFX_MSG_MAP(CDlgHisto)
	ON_EN_KILLFOCUS(IDC_EDT_N_BINS, OnKillfocusEdtNBins)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHisto message handlers

void CDlgHisto::OnKillfocusEdtNBins() 
{
	DrawHisto();
}

void CDlgHisto::DrawHisto()
{
	UpdateData( TRUE);

	if( m_doc == NULL) return;
	
	//************* 100 msec
	CNiReal64Vector data_100m(m_doc->m_dn100m), axis_100m( m_nBins);
	CNiIntVector histogram_100m( m_nBins);

	for( int i = 0; i < m_doc->m_dn100m; i++) {
		data_100m[i] = m_doc->m_dy100m[i];
	}

	// create histogram
	double min, max;
	unsigned int minIndex, maxIndex;
	data_100m.MinMax( min, minIndex, max, maxIndex);
	CNiMath::Histogram( data_100m, min, max, m_nBins, histogram_100m, axis_100m);

	//Plot Data and Histogram
	m_ctlHisto100m.PlotXvsY(axis_100m, histogram_100m);
	

	//************* 1 sec
	CNiReal64Vector data_1s(m_doc->m_dn1s), axis_1s( m_nBins);
	CNiIntVector histogram_1s( m_nBins);

	for( i = 0; i < m_doc->m_dn1s; i++) {
		data_1s[i] = m_doc->m_dy1s[i];
	}

	// create histogram
	/*double min, max;
	unsigned int minIndex, maxIndex;*/
	data_1s.MinMax( min, minIndex, max, maxIndex);
	CNiMath::Histogram( data_1s, min, max, m_nBins, histogram_1s, axis_1s);

	//Plot Data and Histogram
	m_ctlHisto1s.PlotXvsY(axis_1s, histogram_1s);

	//************* 10 sec
	if( m_doc->m_dn10s > 2.) {
		CNiReal64Vector data_10s(m_doc->m_dn10s), axis_10s( m_nBins);
		CNiIntVector histogram_10s( m_nBins);

		for( i = 0; i < m_doc->m_dn10s; i++) {
			data_10s[i] = m_doc->m_dy10s[i];
		}

		// create histogram
		data_10s.MinMax( min, minIndex, max, maxIndex);
		CNiMath::Histogram( data_10s, min, max, m_nBins, histogram_10s, axis_10s);

		//Plot Data and Histogram
		m_ctlHisto10s.PlotXvsY(axis_10s, histogram_10s);
	}

	//************* 100 sec
	if( m_doc->m_dn100s > 2.) {
		CNiReal64Vector data_100s(m_doc->m_dn100s), axis_100s( m_nBins);
		CNiIntVector histogram_100s( m_nBins);

		for( i = 0; i < m_doc->m_dn100s; i++) {
			data_100s[i] = m_doc->m_dy100s[i];
		}

		// create histogram
		data_100s.MinMax( min, minIndex, max, maxIndex);
		CNiMath::Histogram( data_100s, min, max, m_nBins, histogram_100s, axis_100s);

		//Plot Data and Histogram
		m_ctlHisto100s.PlotXvsY(axis_100s, histogram_100s);
	}
}

void CDlgHisto::OnOK() 
{
	CDialog::OnOK();
}

BOOL CDlgHisto::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DrawHisto();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
