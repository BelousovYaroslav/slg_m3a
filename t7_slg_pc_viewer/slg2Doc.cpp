// slg2Doc.cpp : implementation of the CSlg2Doc class
//

#include "stdafx.h"
#include "slg2.h"

#include "slg2Doc.h"
#include "MainView.h"
#include "OpenMeasDlg.h"

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
	m_dx100m	= m_dy100m =
	m_dx1s		= m_dy1s =
	m_dx10s		= m_dy10s =
	m_dx100s	= m_dy100s =
	m_dx_i1		= m_dy_i1 =
	m_dx_i2		= m_dy_i2 =
	m_dx_vpc	= m_dy_vpc =
	m_dx_aa		= m_dy_aa =
	m_dx_t1		= m_dy_t1 =
	m_dx_t2		= m_dy_t2 =
  m_dx_t3		= m_dy_t3 =
	m_dx_tsa	= m_dy_tsa = NULL;

	m_dn100m = m_dn1s = m_dn10s =	m_dn100s = m_dn_i1 = m_dn_i2 = m_dn_vpc = m_dn_aa =
	m_dn_t1 = m_dn_t2 = m_dn_t3 = m_dn_tsa = 0.;

	m_strCurrentFileName.Empty();

	nDataFileLines = 0;
	m_nStatFileVersion = 0;

	m_bShowCursors = false;
	m_bZoomed = false;
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
	tmps.LoadString( IDS_SOFTWARE_VERSION);
	this->SetTitle( _T("Viewer ") + tmps);

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

BOOL CSlg2Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	m_strCurrentFileName = lpszPathName;

	COpenMeasDlg *dlg;
	dlg = new COpenMeasDlg();
	dlg->Create( IDD_OPEN_MEAS_DLG, NULL);
	dlg->ShowWindow( SW_SHOW);
	dlg->CenterWindow();

	if (!CDocument::OnOpenDocument(lpszPathName)) {
		delete dlg;
		return FALSE;
	}
	
	nDataFileLines = 0;
	ReadDataFile( m_strCurrentFileName, dlg);
	
	POSITION pos = GetFirstViewPosition();
	(( CMainView* ) GetNextView( pos))->SetRefreshTimer();
  
	dlg->EndDialog( 0);
	delete dlg;

	return TRUE;
}

void CSlg2Doc::OnCloseDocument() 
{
	if( m_dx100m != NULL) { delete m_dx100m; m_dx100m = NULL;}
	if( m_dy100m != NULL) { delete m_dy100m; m_dy100m = NULL;}
	if( m_dx1s != NULL) { delete m_dx1s; m_dx1s = NULL;}
	if( m_dy1s != NULL) { delete m_dy1s; m_dy1s = NULL;}
	if( m_dx10s != NULL) { delete m_dx10s; m_dx10s = NULL;}
	if( m_dy10s != NULL) { delete m_dy10s; m_dy10s = NULL;}
	if( m_dx100s != NULL) { delete m_dx100s; m_dx100s = NULL;}
	if( m_dy100s != NULL) { delete m_dy100s; m_dy100s = NULL;}
	if( m_dx_i1 != NULL) { delete m_dx_i1; m_dx_i1 = NULL;}
	if( m_dy_i1 != NULL) { delete m_dy_i1; m_dy_i1 = NULL;}
	if( m_dx_i2 != NULL) { delete m_dx_i2; m_dx_i2 = NULL;}
	if( m_dy_i2 != NULL) { delete m_dy_i2; m_dy_i2 = NULL;}
	if( m_dx_vpc != NULL) { delete m_dx_vpc; m_dx_vpc = NULL;}
	if( m_dy_vpc != NULL) { delete m_dy_vpc; m_dy_vpc = NULL;}
	
	if( m_dx_aa != NULL) { delete m_dx_aa; m_dx_aa = NULL;}
	if( m_dy_aa != NULL) { delete m_dy_aa; m_dy_aa = NULL;}
	if( m_dx_t1 != NULL) { delete m_dx_t1; m_dx_t1 = NULL;}
	if( m_dy_t1 != NULL) { delete m_dy_t1; m_dy_t1 = NULL;}
	if( m_dx_t2 != NULL) { delete m_dx_t2; m_dx_t2 = NULL;}
	if( m_dy_t2 != NULL) { delete m_dy_t2; m_dy_t2 = NULL;}
  if( m_dx_t3 != NULL) { delete m_dx_t3; m_dx_t3 = NULL;}
	if( m_dy_t3 != NULL) { delete m_dy_t3; m_dy_t3 = NULL;}
	if( m_dx_tsa != NULL) { delete m_dx_tsa; m_dx_tsa = NULL;}
	if( m_dy_tsa != NULL) { delete m_dy_tsa; m_dy_tsa = NULL;}

	m_dn100m = m_dn1s = m_dn10s =	m_dn100s = m_dn_i1 = m_dn_i2 = m_dn_vpc = m_dn_aa =
	m_dn_t1 = m_dn_t2 = m_dn_t3 = m_dn_tsa = 0.;

	CDocument::OnCloseDocument();
}

void CSlg2Doc::RecalculateStatistics()
{
	if( m_dn100m == 0.) return;

	m_d_100m_min = m_d_100m_mean = m_d_100m_max = m_d_100m_rms =
	m_d_1s_min = m_d_1s_mean = m_d_1s_max = m_d_1s_rms =
	m_d_10s_min = m_d_10s_mean = m_d_10s_max = m_d_10s_rms =
	m_d_100s_min = m_d_100s_mean = m_d_100s_max = m_d_100s_rms =
	m_d_i1_min = m_d_i1_mean = m_d_i1_max = m_d_i1_rms =
	m_d_i2_min = m_d_i2_mean = m_d_i2_max = m_d_i2_rms =
	m_d_vpc_min = m_d_vpc_mean = m_d_vpc_max = m_d_vpc_rms =
	m_d_aa_min = m_d_aa_mean = m_d_aa_max = m_d_aa_rms =
	m_d_t1_min = m_d_t1_mean = m_d_t1_max = m_d_t1_rms =
	m_d_t2_min = m_d_t2_mean = m_d_t2_max = m_d_t2_rms =
  m_d_t3_min = m_d_t3_mean = m_d_t3_max = m_d_t3_rms =
	m_d_tsa_min = m_d_tsa_mean = m_d_tsa_max = m_d_tsa_rms = 0.;

	// *********************************************
	// w100msec
	// *********************************************
	double summ = 0.;
	m_d_100m_min = m_d_100m_max = m_dy100m[0];
	for( int i=0; i<m_dn100m; i++) {
		if( m_d_100m_min > m_dy100m[i])
			m_d_100m_min = m_dy100m[i];
		if( m_d_100m_max < m_dy100m[i])
			m_d_100m_max = m_dy100m[i];
		summ+= m_dy100m[i];
	}
	m_d_100m_mean = summ / m_dn100m;
	summ = 0.;
	for( i=0; i<m_dn100m; i++) {
		summ+= ( m_dy100m[i] - m_d_100m_mean) * ( m_dy100m[i] - m_d_100m_mean);
	}
	m_d_100m_rms = sqrt( summ / m_dn100m);

	// *********************************************
	// w1sec
	// *********************************************
	summ = 0.;
	m_d_1s_min = m_d_1s_max = m_dy1s[0];
	for( i=0; i<m_dn1s; i++) {
		if( m_d_1s_min > m_dy1s[i])
			m_d_1s_min = m_dy1s[i];
		if( m_d_1s_max < m_dy1s[i])
			m_d_1s_max = m_dy1s[i];
		summ += m_dy1s[i];
	}
	m_d_1s_mean = summ / m_dn1s;
	summ = 0.;
	for( i=0; i<m_dn1s; i++) {
		summ+= ( m_dy1s[i] - m_d_1s_mean) * ( m_dy1s[i] - m_d_1s_mean);
	}
	m_d_1s_rms = sqrt( summ / m_dn1s);

	// *********************************************
	// w10sec
	// *********************************************
	summ = 0.;
	m_d_10s_min = m_d_10s_max = m_dy10s[0];
	for( i=0; i<m_dn10s; i++) {
		if( m_d_10s_min > m_dy10s[i])
			m_d_10s_min = m_dy10s[i];
		if( m_d_10s_max < m_dy10s[i])
			m_d_10s_max = m_dy10s[i];
		summ += m_dy10s[i];
	}
	m_d_10s_mean = summ / m_dn10s;
	summ = 0.;
	for( i=0; i<m_dn10s; i++) {
		summ+= ( m_dy10s[i] - m_d_10s_mean) * ( m_dy10s[i] - m_d_10s_mean);
	}
	m_d_10s_rms = sqrt( summ / m_dn10s);

	// *********************************************
	// w100sec
	// *********************************************
	summ = 0.;
	m_d_100s_min = m_d_100s_max = m_dy100s[0];
	for( i=0; i<m_dn100s; i++) {
		if( m_d_100s_min > m_dy100s[i])
			m_d_100s_min = m_dy100s[i];
		if( m_d_100s_max < m_dy100s[i])
			m_d_100s_max = m_dy100s[i];
		summ += m_dy100s[i];
	}
	m_d_100s_mean = summ / m_dn100s;
	summ = 0.;
	for( i=0; i<m_dn100s; i++) {
		summ+= ( m_dy100s[i] - m_d_100s_mean) * ( m_dy100s[i] - m_d_100s_mean);
	}
	m_d_100s_rms = sqrt( summ / m_dn100s);

	// *********************************************
	// i1
	// *********************************************
	summ = 0.;
	m_d_i1_min = m_d_i1_max = m_dy_i1[0];
	for( i=0; i<m_dn_i1; i++) {
		if( m_d_i1_min > m_dy_i1[i])
			m_d_i1_min = m_dy_i1[i];
		if( m_d_i1_max < m_dy_i1[i])
			m_d_i1_max = m_dy_i1[i];
		summ += m_dy_i1[i];
	}
	m_d_i1_mean = summ / m_dn_i1;
	summ = 0.;
	for( i=0; i<m_dn_i1; i++) {
		summ+= ( m_dy_i1[i] - m_d_i1_mean) * ( m_dy_i1[i] - m_d_i1_mean);
	}
	m_d_i1_rms = sqrt( summ / m_dn_i1);

	// *********************************************
	// i2
	// *********************************************
	summ = 0.;
	m_d_i2_min = m_d_i2_max = m_dy_i2[0];
	for( i=0; i<m_dn_i2; i++) {
		if( m_d_i2_min > m_dy_i2[i])
			m_d_i2_min = m_dy_i2[i];
		if( m_d_i2_max < m_dy_i2[i])
			m_d_i2_max = m_dy_i2[i];
		summ += m_dy_i2[i];
	}
	m_d_i2_mean = summ / m_dn_i2;
	summ = 0.;
	for( i=0; i<m_dn_i2; i++) {
		summ+= ( m_dy_i2[i] - m_d_i2_mean) * ( m_dy_i2[i] - m_d_i2_mean);
	}
	m_d_i2_rms = sqrt( summ / m_dn_i2);

	// *********************************************
	// vpc
	// *********************************************
	summ = 0.;
	m_d_vpc_min = m_d_vpc_max = m_dy_vpc[0];
	for( i=0; i<m_dn_vpc; i++) {
		if( m_d_vpc_min > m_dy_vpc[i])
			m_d_vpc_min = m_dy_vpc[i];
		if( m_d_vpc_max < m_dy_vpc[i])
			m_d_vpc_max = m_dy_vpc[i];
		summ += m_dy_vpc[i];
	}
	m_d_vpc_mean = summ / m_dn_vpc;
	summ = 0.;
	for( i=0; i<m_dn_vpc; i++) {
		summ+= ( m_dy_vpc[i] - m_d_vpc_mean) * ( m_dy_vpc[i] - m_d_vpc_mean);
	}
	m_d_vpc_rms = sqrt( summ / m_dn_vpc);

	// *********************************************
	// aa
	// *********************************************
	summ = 0.;
	m_d_aa_min = m_d_aa_max = m_dy_aa[0];
	for( i=0; i<m_dn_aa; i++) {
		if( m_d_aa_min > m_dy_aa[i])
			m_d_aa_min = m_dy_aa[i];
		if( m_d_aa_max < m_dy_aa[i])
			m_d_aa_max = m_dy_aa[i];
		summ += m_dy_aa[i];
	}
	m_d_aa_mean = summ / m_dn_aa;
	summ = 0.;
	for( i=0; i<m_dn_aa; i++) {
		summ+= ( m_dy_aa[i] - m_d_aa_mean) * ( m_dy_aa[i] - m_d_aa_mean);
	}
	m_d_aa_rms = sqrt( summ / m_dn_aa);

	// *********************************************
	// Temp1
	// *********************************************
	summ = 0.;
	m_d_t1_min = m_d_t1_max = m_dy_t1[0];
	for( i=0; i<m_dn_t1; i++) {
		if( m_d_t1_min > m_dy_t1[i])
			m_d_t1_min = m_dy_t1[i];
		if( m_d_t1_max < m_dy_t1[i])
			m_d_t1_max = m_dy_t1[i];
		summ += m_dy_t1[i];
	}
	m_d_t1_mean = summ / m_dn_t1;
	summ = 0.;
	for( i=0; i<m_dn_t1; i++) {
		summ+= ( m_dy_t1[i] - m_d_t1_mean) * ( m_dy_t1[i] - m_d_t1_mean);
	}
	m_d_t1_rms = sqrt( summ / m_dn_t1);

	// *********************************************
	// Temp2
	// *********************************************
	summ = 0.;
	m_d_t2_min = m_d_t2_max = m_dy_t2[0];
	for( i=0; i<m_dn_t2; i++) {
		if( m_d_t2_min > m_dy_t2[i])
			m_d_t2_min = m_dy_t2[i];
		if( m_d_t2_max < m_dy_t2[i])
			m_d_t2_max = m_dy_t2[i];
		summ += m_dy_t2[i];
	}
	m_d_t2_mean = summ / m_dn_t2;
	summ = 0.;
	for( i=0; i<m_dn_t2; i++) {
		summ+= ( m_dy_t2[i] - m_d_t2_mean) * ( m_dy_t2[i] - m_d_t2_mean);
	}
	m_d_t2_rms = sqrt( summ / m_dn_t2);

  // *********************************************
	// Temp3
	// *********************************************
	summ = 0.;
	m_d_t3_min = m_d_t3_max = m_dy_t3[0];
	for( i=0; i<m_dn_t3; i++) {
		if( m_d_t3_min > m_dy_t3[i])
			m_d_t3_min = m_dy_t3[i];
		if( m_d_t3_max < m_dy_t3[i])
			m_d_t3_max = m_dy_t3[i];
		summ += m_dy_t3[i];
	}
	m_d_t3_mean = summ / m_dn_t3;
	summ = 0.;
	for( i=0; i<m_dn_t3; i++) {
		summ+= ( m_dy_t3[i] - m_d_t3_mean) * ( m_dy_t3[i] - m_d_t3_mean);
	}
	m_d_t3_rms = sqrt( summ / m_dn_t3);

	// *********************************************
	// Tsa
	// *********************************************
	summ = 0.;
	m_d_tsa_min = m_d_tsa_max = m_dy_tsa[0];
	for( i=0; i<m_dn_tsa; i++) {
		if( m_d_tsa_min > m_dy_tsa[i])
			m_d_tsa_min = m_dy_tsa[i];
		if( m_d_tsa_max < m_dy_tsa[i])
			m_d_tsa_max = m_dy_tsa[i];
		summ += m_dy_tsa[i];
	}
	m_d_tsa_mean = summ / m_dn_tsa;
	summ = 0.;
	for( i=0; i<m_dn_tsa; i++) {
		summ+= ( m_dy_tsa[i] - m_d_tsa_mean) * ( m_dy_tsa[i] - m_d_tsa_mean);
	}
	m_d_tsa_rms = sqrt( summ / m_dn_tsa);
}

void CSlg2Doc::ReadDataFile(CString filename, COpenMeasDlg *dlg)
{
	/*FILE *fh_test_needs;
	fh_test_needs = fopen( _T("d:\\test_needs.txt"), _T("w"));*/

	FILE *fh;
	fh = fopen( filename, _T("r"));
	if( fh == NULL) {
		AfxMessageBox( _T("Ошибка при открытии файла измерения."));
		return;
	}

	//определяем тип файла статистики (старый(ascii) или новый(bin))
	BOOL bNewOld;
	char buf_check[2];
	fread( buf_check, 2, 1, fh);
	if( buf_check[1] == '.')	{		// <---- фаршно, но терпимо
		bNewOld = false;	//ascii
		m_nStatFileVersion = 1;
	}
	else {
		bNewOld = true;		//bin
		m_nStatFileVersion = 2;
		fclose( fh);
		fh = fopen( filename, _T("rb"));
	}
	if( dlg != NULL) {
		fseek( fh, 0, SEEK_END);
		dlg->m_ctlProgress.SetRange32( 0, ftell( fh));
		dlg->m_ctlProgress.SetPos( 0);
		dlg->m_ctlProgress2.SetRange32( 0, ftell( fh));
		dlg->m_ctlProgress2.SetPos( 0);
	}
	fseek( fh, 0, SEEK_SET);

	if( bNewOld) {
		// ********************************************************************
		// ** NEW BIN STAT FILE
		// ********************************************************************
		//определяем количество линий
		m_dn100m = 0;
		double tsasumm = 0.;
		while( 1) {
			float f1;
			short s1, s2, s3;
			if( fread( &f1, sizeof( float), 1, fh) < 1)
				break;
			if( fread( &s1, sizeof( short), 1, fh) < 1)
				break;
			if( fread( &s2, sizeof( short), 1, fh) < 1) {
				break;
			}
			if( fread( &s3, sizeof( short), 1, fh) < 1)
				break;

			nDataFileLines++;
			tsasumm += ( double) s3 / 32768.;
			if( tsasumm > 0.1) {
				m_dn100m++;
				tsasumm = 0.;
			}

			if( dlg != NULL)
				if( !( nDataFileLines % 100))
					dlg->m_ctlProgress2.SetPos( ftell( fh));

			if( feof( fh))
				break;
		}
	
		//высвобождаем если что либо заказано (что-то было открыто)
		if( m_dx100m != NULL) { delete m_dx100m; m_dx100m = NULL;}
		if( m_dy100m != NULL) { delete m_dy100m; m_dy100m = NULL;}
		if( m_dx1s != NULL) { delete m_dx1s; m_dx1s = NULL;}
		if( m_dy1s != NULL) { delete m_dy1s; m_dy1s = NULL;}
		if( m_dx10s != NULL) { delete m_dx10s; m_dx10s = NULL;}
		if( m_dy10s != NULL) { delete m_dy10s; m_dy10s = NULL;}
		if( m_dx100s != NULL) { delete m_dx100s; m_dx100s = NULL;}
		if( m_dy100s != NULL) { delete m_dy100s; m_dy100s = NULL;}
		if( m_dx_i1 != NULL) { delete m_dx_i1; m_dx_i1 = NULL;}
		if( m_dy_i1 != NULL) { delete m_dy_i1; m_dy_i1 = NULL;}
		if( m_dx_i2 != NULL) { delete m_dx_i2; m_dx_i2 = NULL;}
		if( m_dy_i2 != NULL) { delete m_dy_i2; m_dy_i2 = NULL;}
		if( m_dx_vpc != NULL) { delete m_dx_vpc; m_dx_vpc = NULL;}
		if( m_dy_vpc != NULL) { delete m_dy_vpc; m_dy_vpc = NULL;}
		if( m_dx_aa != NULL) { delete m_dx_aa; m_dx_aa = NULL;}
		if( m_dy_aa != NULL) { delete m_dy_aa; m_dy_aa = NULL;}
		if( m_dx_t1 != NULL) { delete m_dx_t1; m_dx_t1 = NULL;}
		if( m_dy_t1 != NULL) { delete m_dy_t1; m_dy_t1 = NULL;}
		if( m_dx_t2 != NULL) { delete m_dx_t2; m_dx_t2 = NULL;}
		if( m_dy_t2 != NULL) { delete m_dy_t2; m_dy_t2 = NULL;}
    if( m_dx_t3 != NULL) { delete m_dx_t3; m_dx_t3 = NULL;}
    if( m_dy_t3 != NULL) { delete m_dy_t3; m_dy_t3 = NULL;}
		if( m_dx_tsa != NULL) { delete m_dx_tsa; m_dx_tsa = NULL;}
		if( m_dy_tsa != NULL) { delete m_dy_tsa; m_dy_tsa = NULL;}
	 
		//заказываем память под измерения
		m_dx100m = new double[m_dn100m];
		m_dy100m = new double[m_dn100m];
		m_dx1s = new double[m_dn100m];
		m_dy1s = new double[m_dn100m];
		m_dx10s = new double[m_dn100m];
		m_dy10s = new double[m_dn100m];
		m_dx100s = new double[m_dn100m];
		m_dy100s = new double[m_dn100m];
		m_dx_i1 = new double[m_dn100m];
		m_dy_i1 = new double[m_dn100m];
		m_dx_i2	= new double[m_dn100m];
		m_dy_i2 = new double[m_dn100m];
		m_dx_vpc = new double[m_dn100m];
		m_dy_vpc = new double[m_dn100m];
		m_dx_aa	= new double[m_dn100m];
		m_dy_aa = new double[m_dn100m];
		m_dx_t1	= new double[m_dn100m];
		m_dy_t1 = new double[m_dn100m];
		m_dx_t2	= new double[m_dn100m];
		m_dy_t2 = new double[m_dn100m];
    m_dx_t3	= new double[m_dn100m];
		m_dy_t3 = new double[m_dn100m];
		m_dx_tsa = new double[m_dn100m];
		m_dy_tsa = new double[m_dn100m];

		m_dn_i1 = m_dn_i2 = m_dn_vpc = m_dn_aa =
		m_dn_t1 = m_dn_t2 = m_dn_t3 = m_dn_tsa = m_dn100m;

		double d_global_time = 0.;
	
		double w100m = 0., t100m = 0.;
		int n100m = 0;

		double w1s = 0., t1s = 0.;
		int n1s = 0;
		m_dn1s = 0;

		double w10s = 0., t10s = 0.;
		int n10s = 0;
		m_dn10s = 0;

		double w100s = 0., t100s = 0.;
		int n100s = 0;
		m_dn100s = 0;

		double i1 = 0.;
		int n_i1_s = 0, n_i1_n = 0;

		double i2 = 0.;
		int n_i2_s = 0, n_i2_n = 0;

		double vpc = 0.;
		int n_vpc_s = 0, n_vpc_n = 0;

		double aa = 0.;
		int n_aa_s = 0, n_aa_n = 0;

		double temp1 = 0.;
		int n_temp1_s = 0, n_temp1_n = 0;

		double temp2 = 0.;
		int n_temp2_s = 0, n_temp2_n = 0;

    double temp3 = 0.;
		int n_temp3_s = 0, n_temp3_n = 0;

		double tsa = 0.;
		int n_tsa_s = 0, n_tsa_n = 0;

		fseek( fh, 0, SEEK_SET);

		while( 1) {
			float f1;
			short s1, s2, s3;
      int d1;
			
			fread( &d1, sizeof( int), 1, fh);
			fread( &s1, sizeof( short), 1, fh);
			fread( &s2, sizeof( short), 1, fh);
			fread( &s3, sizeof( short), 1, fh);
		
			/*fprintf( fh_test_needs, _T("%.4f %.4f\n"), d_global_time, f1);*/

			if( s2 == -1) {
				f1 = 0;
			}

			double p_phi = ( d1 / 2147483647. * 99310.) * ((CSlg2App *) AfxGetApp())->m_dKimpSec / 4.;
			double p_tsa = s3 / 32768.;
			switch( s1 & 0x7F) {
				case 0: temp1 += ( unsigned short) s2; n_temp1_s++; break;	//Temp1
				case 1: temp2 += ( unsigned short) s2; n_temp2_s++; break;	//Temp2
        case 2: temp3 += ( unsigned short) s2; n_temp3_s++; break;	//Temp3

				case 3: i1 += s2;	n_i1_s++; break;			//i1
				case 4: i2 += s2;	n_i2_s++; break;			//i2
				case 5: vpc += s2;	n_vpc_s++; break;		//vpc
				case 6:
					aa += s2;	n_aa_s++;
				break;			//aa

				case 7: ( ( CSlg2App *) AfxGetApp())->m_btParam1 = s2;  break;
				case 8: ( ( CSlg2App *) AfxGetApp())->m_btParam2 = s2; break;
				case 9: ( ( CSlg2App *) AfxGetApp())->m_btParam3 = s2; break;
				case 10: ( ( CSlg2App *) AfxGetApp())->m_btParam4 = s2; break;
				case 11: ( ( CSlg2App *) AfxGetApp())->m_shFlashI1min = s2; break; //flashParamI1min
				case 12: ( ( CSlg2App *) AfxGetApp())->m_shFlashI2min = s2; break; //flashParamI2min
	      case 13: ( ( CSlg2App *) AfxGetApp())->m_shFlashAmplAng1min = s2; break; //flashParamAmplAngMin1
		    case 14: ( ( CSlg2App *) AfxGetApp())->m_shFlashDecCoeff = s2; /*fprintf( fh_test_needs, _T("%.4f\n"), ( double) s2 / 65535.);*/ break; //коэффициент вычета
			  case 15: ( ( CSlg2App *) AfxGetApp())->m_shFlashSa = s2; break; //flashParamSAtime          
				case 16: //software version
					( ( CSlg2App *) AfxGetApp())->m_strSoftwareVer.Format( _T("%d.%d.%d.%d"),
							( s2 & 0x00F0) >> 4,
							( s2 & 0x000F),
							( s2 & 0xF000) >> 12,
							( s2 & 0x0F00) >> 8);	
				break;
			}

			tsa += p_tsa;			n_tsa_s++;

			w100m += p_phi;		t100m += p_tsa;
			w1s += p_phi;			t1s += p_tsa;
			w10s += p_phi;		t10s += p_tsa;
			w100s += p_phi;		t100s += p_tsa;
		
		

			d_global_time += p_tsa;
		
			if( t100m > 0.1) {
				double w100 = w100m / t100m;
				//100 ms points
				m_dx100m[n100m] = d_global_time;
				m_dy100m[n100m] = w100;
				n100m++;
				w100m = t100m = 0.;

				//i1 points
				m_dx_i1[ n_i1_n] = d_global_time;
				m_dy_i1[ n_i1_n] = ( 2.5 - i1 / n_i1_s / 4096. * 3.) / 2.5;
				if( m_dy_i1[ n_i1_n] < 0.57) {
					i1 = 0;
				}
				n_i1_n++;
				i1 = 0.; n_i1_s = 0;

				//i2 points
				m_dx_i2[ n_i2_n] = d_global_time;
				m_dy_i2[ n_i2_n] = ( 2.5 - i2 / n_i2_s / 4096. * 3.) / 2.5;
				n_i2_n++;
				i2 = 0.; n_i2_s = 0;
			
				//vpc points
				m_dx_vpc[ n_vpc_n] = d_global_time;
				m_dy_vpc[ n_vpc_n] = (( vpc / n_vpc_s / 4096. * 3.) - 2.048) * 100.;
				n_vpc_n++;
				vpc = 0.; n_vpc_s = 0;

				//aa points
				m_dx_aa[ n_aa_n] = d_global_time;
				m_dy_aa[ n_aa_n] = aa / n_aa_s / 4. * ((CSlg2App *) AfxGetApp())->m_dKimpSec;
				n_aa_n++;
				aa = 0.; n_aa_s = 0;

				//t1 points
				m_dx_t1[ n_temp1_n] = d_global_time;
				m_dy_t1[ n_temp1_n] = temp1 / n_temp1_s / 65535. * 200. - 100.;
				//m_dy_t1[ n_temp1_n] = 70.24586 * ( temp1 / n_temp1_s / 4096. * 3.) - 128.209;
				//m_dy_t1[ n_temp1_n] = ( temp1 / n_temp1_s / 4096. * 3.);
				n_temp1_n++;
				temp1 = 0.; n_temp1_s = 0;

				//t2 points
				m_dx_t2[ n_temp2_n] = d_global_time;
				m_dy_t2[ n_temp2_n] = temp2 / n_temp2_s / 65535. * 200. - 100.;
				//m_dy_t2[ n_temp2_n] = 70.24586 * ( temp2 / n_temp2_s / 4096. * 3.) - 128.209;
				//m_dy_t2[ n_temp2_n] = ( temp2 / n_temp2_s / 4096. * 3.);
				n_temp2_n++;
				temp2 = 0.; n_temp2_s = 0;

        //t3 points
				m_dx_t3[ n_temp3_n] = d_global_time;
				m_dy_t3[ n_temp3_n] = temp3 / n_temp3_s / 65535. * 200. - 100.;
				n_temp3_n++;
				temp3 = 0.; n_temp3_s = 0;

				//tsa points
				m_dx_tsa[ n_tsa_n] = d_global_time;
				m_dy_tsa[ n_tsa_n] = tsa / n_tsa_s;
				n_tsa_n++;
				tsa = 0.; n_tsa_s = 0;
			}

			//1-секундные точки
			if( t1s > 1.) {
				m_dx1s[n1s] = d_global_time;
				m_dy1s[n1s] = w1s / t1s;
				n1s++;
				m_dn1s += 1.;
				w1s = 0.; t1s = 0.;
			}

			//10-секундные точки
			if( t10s > 10.) {
				m_dx10s[n10s] = d_global_time;
				m_dy10s[n10s] = w10s / t10s;
				n10s++;
				m_dn10s += 1.;
				w10s = 0.; t10s = 0.;
			}

			//100-секундные точки
			if( t100s > 100.) {
				m_dx100s[n100s] = d_global_time;
				m_dy100s[n100s] = w100s / t100s;
				n100s++;
				m_dn100s += 1.;
				w100s = 0.; t100s = 0.;
			}

			if( dlg != NULL)
				if( !( n100m % 50))
					dlg->m_ctlProgress.SetPos( ftell( fh));

			if( feof( fh))
				break;
		}
	}
	else {
		// ********************************************************************
		// ** OLD ASCII STAT FILE
		// ********************************************************************
		//определяем количество линий
		m_dn100m = 0;
		double tsasumm = 0.;
		while( 1) {
			float f1, f2;
			int i1, i2, i3;
			fscanf(fh, "%f\t%f\t%d\t%d\t%d\n", &f1, &f2, &i1, &i2, &i3);
			nDataFileLines++;
			tsasumm += ( double) i3 / 32768.;
			if( tsasumm > 0.1) {
				m_dn100m++;
				tsasumm = 0.;
			}

			if( dlg != NULL)
				if( !( nDataFileLines % 100))
					dlg->m_ctlProgress2.SetPos( ftell( fh));

			if( feof( fh))
				break;
		}
	
		//высвобождаем если что либо заказано (что-то было открыто)
		if( m_dx100m != NULL) { delete m_dx100m; m_dx100m = NULL;}
		if( m_dy100m != NULL) { delete m_dy100m; m_dy100m = NULL;}
		if( m_dx1s != NULL) { delete m_dx1s; m_dx1s = NULL;}
		if( m_dy1s != NULL) { delete m_dy1s; m_dy1s = NULL;}
		if( m_dx10s != NULL) { delete m_dx10s; m_dx10s = NULL;}
		if( m_dy10s != NULL) { delete m_dy10s; m_dy10s = NULL;}
		if( m_dx100s != NULL) { delete m_dx100s; m_dx100s = NULL;}
		if( m_dy100s != NULL) { delete m_dy100s; m_dy100s = NULL;}
		if( m_dx_i1 != NULL) { delete m_dx_i1; m_dx_i1 = NULL;}
		if( m_dy_i1 != NULL) { delete m_dy_i1; m_dy_i1 = NULL;}
		if( m_dx_i2 != NULL) { delete m_dx_i2; m_dx_i2 = NULL;}
		if( m_dy_i2 != NULL) { delete m_dy_i2; m_dy_i2 = NULL;}
		if( m_dx_vpc != NULL) { delete m_dx_vpc; m_dx_vpc = NULL;}
		if( m_dy_vpc != NULL) { delete m_dy_vpc; m_dy_vpc = NULL;}
		if( m_dx_aa != NULL) { delete m_dx_aa; m_dx_aa = NULL;}
		if( m_dy_aa != NULL) { delete m_dy_aa; m_dy_aa = NULL;}
		if( m_dx_t1 != NULL) { delete m_dx_t1; m_dx_t1 = NULL;}
		if( m_dy_t1 != NULL) { delete m_dy_t1; m_dy_t1 = NULL;}
		if( m_dx_t2 != NULL) { delete m_dx_t2; m_dx_t2 = NULL;}
		if( m_dy_t2 != NULL) { delete m_dy_t2; m_dy_t2 = NULL;}
    if( m_dx_t3 != NULL) { delete m_dx_t3; m_dx_t3 = NULL;}
		if( m_dy_t3 != NULL) { delete m_dy_t3; m_dy_t3 = NULL;}
		if( m_dx_tsa != NULL) { delete m_dx_tsa; m_dx_tsa = NULL;}
		if( m_dy_tsa != NULL) { delete m_dy_tsa; m_dy_tsa = NULL;}
	 
		//заказываем память под измерения
		m_dx100m = new double[m_dn100m];
		m_dy100m = new double[m_dn100m];
		m_dx1s = new double[m_dn100m];
		m_dy1s = new double[m_dn100m];
		m_dx10s = new double[m_dn100m];
		m_dy10s = new double[m_dn100m];
		m_dx100s = new double[m_dn100m];
		m_dy100s = new double[m_dn100m];
		m_dx_i1 = new double[m_dn100m];
		m_dy_i1 = new double[m_dn100m];
		m_dx_i2	= new double[m_dn100m];
		m_dy_i2 = new double[m_dn100m];
		m_dx_vpc = new double[m_dn100m];
		m_dy_vpc = new double[m_dn100m];
		m_dx_aa	= new double[m_dn100m];
		m_dy_aa = new double[m_dn100m];
		m_dx_t1	= new double[m_dn100m];
		m_dy_t1 = new double[m_dn100m];
		m_dx_t2	= new double[m_dn100m];
		m_dy_t2 = new double[m_dn100m];
    m_dx_t3	= new double[m_dn100m];
		m_dy_t3 = new double[m_dn100m];
		m_dx_tsa = new double[m_dn100m];
		m_dy_tsa = new double[m_dn100m];

		m_dn_i1 = m_dn_i2 = m_dn_vpc = m_dn_aa =
		m_dn_t1 = m_dn_t2 = m_dn_t3 = m_dn_tsa = m_dn100m;

		double d_global_time = 0.;
	
		double w100m = 0., t100m = 0.;
		int n100m = 0;

		double w1s = 0., t1s = 0.;
		int n1s = 0;
		m_dn1s = 0;

		double w10s = 0., t10s = 0.;
		int n10s = 0;
		m_dn10s = 0;

		double w100s = 0., t100s = 0.;
		int n100s = 0;
		m_dn100s = 0;

		double i1 = 0.;
		int n_i1_s = 0, n_i1_n = 0;

		double i2 = 0.;
		int n_i2_s = 0, n_i2_n = 0;

		double vpc = 0.;
		int n_vpc_s = 0, n_vpc_n = 0;

		double aa = 0.;
		int n_aa_s = 0, n_aa_n = 0;

		double temp1 = 0.;
		int n_temp1_s = 0, n_temp1_n = 0;

		double temp2 = 0.;
		int n_temp2_s = 0, n_temp2_n = 0;

    double temp3 = 0.;
		int n_temp3_s = 0, n_temp3_n = 0;

		double tsa = 0.;
		int n_tsa_s = 0, n_tsa_n = 0;

		fseek( fh, 0, SEEK_SET);

		while( 1) {
			float f1, f2;
			int int1, int2, int3;
			fscanf(fh, "%f\t%f\t%d\t%d\t%d\n", &f1, &f2, &int1, &int2, &int3);
		
			double p_phi = f1 * ((CSlg2App *) AfxGetApp())->m_dKimpSec / 4.;
			double p_tsa = int3 / 32768.;
			switch( int1 & 0x0F) {
				case 0: temp1 += int2; n_temp1_s++; break;	//Temp1
				case 1: temp2 += int2; n_temp2_s++; break;	//Temp2
        case 2: temp3 += int3; n_temp3_s++; break;	//Temp3

				case 3: i1 += int2;	n_i1_s++; break;			//i1
				case 4: i2 += int2;	n_i2_s++; break;			//i2
				case 5: vpc += int2;	n_vpc_s++; break;		//vpc
				case 6: aa += int2;	n_aa_s++; break;			//aa

				case 7: ( ( CSlg2App *) AfxGetApp())->m_btParam1 = int2;  break;
				case 8: ( ( CSlg2App *) AfxGetApp())->m_btParam2 = int2; break;
				case 9: ( ( CSlg2App *) AfxGetApp())->m_btParam3 = int2; break;
				case 10: ( ( CSlg2App *) AfxGetApp())->m_btParam4 = int2; break;
				case 11: ( ( CSlg2App *) AfxGetApp())->m_shFlashI1min = int2; break; //flashParamI1min
				case 12: ( ( CSlg2App *) AfxGetApp())->m_shFlashI2min = int2; break; //flashParamI2min
	      case 13: ( ( CSlg2App *) AfxGetApp())->m_shFlashAmplAng1min = int2; break; //flashParamAmplAngMin1
		    case 14: ( ( CSlg2App *) AfxGetApp())->m_shFlashDecCoeff = int2; break; //коэффициент вычета
			  case 15: ( ( CSlg2App *) AfxGetApp())->m_shFlashSa = int2; break; //flashParamSAtime          
				case 16: //software version
					/*( ( CSlg2App *) AfxGetApp())->m_btMajVer = ( int2 & 0xFF);
					( ( CSlg2App *) AfxGetApp())->m_btMinVer = (( int2 & 0xFF00) >> 8);*/
					( ( CSlg2App *) AfxGetApp())->m_strSoftwareVer.Format( _T("%d.%d.%d.%d"),
							( int2 & 0xF000) >> 12,
							( int2 & 0x0F00) >> 8,
							( int2 & 0x00F0) >> 4,
							( int2 & 0x000F));	
				break;
			}

			tsa += p_tsa;			n_tsa_s++;

			w100m += p_phi;		t100m += p_tsa;
			w1s += p_phi;			t1s += p_tsa;
			w10s += p_phi;		t10s += p_tsa;
			w100s += p_phi;		t100s += p_tsa;
		
		

			d_global_time += p_tsa;
		
			if( t100m > 0.1) {
				double w100 = w100m / t100m;
				//100 ms points
				m_dx100m[n100m] = d_global_time;
				m_dy100m[n100m] = w100;
				n100m++;
				w100m = t100m = 0.;

				//i1 points
				m_dx_i1[ n_i1_n] = d_global_time;
				m_dy_i1[ n_i1_n] = i1 / n_i1_s / 4096. * 3. / 3.973;
				n_i1_n++;
				i1 = 0.; n_i1_s = 0;

				//i2 points
				m_dx_i2[ n_i2_n] = d_global_time;
				m_dy_i2[ n_i2_n] = i2 / n_i2_s / 4096. * 3. / 3.973;
				n_i2_n++;
				i2 = 0.; n_i2_s = 0;
			
				//vpc points
				m_dx_vpc[ n_vpc_n] = d_global_time;
				m_dy_vpc[ n_vpc_n] = (( vpc / n_vpc_s / 4096. * 3.) - 2.048) * 100.;
				n_vpc_n++;
				vpc = 0.; n_vpc_s = 0;

				//aa points
				m_dx_aa[ n_aa_n] = d_global_time;
				m_dy_aa[ n_aa_n] = ( aa / n_aa_s / 4096. * 3.) / 0.5;
				n_aa_n++;
				aa = 0.; n_aa_s = 0;

				//t1 points
				m_dx_t1[ n_temp1_n] = d_global_time;
				m_dy_t1[ n_temp1_n] = 70.24586 * ( temp1 / n_temp1_s / 4096. * 3.) - 128.209;
				//m_dy_t1[ n_temp1_n] = ( temp1 / n_temp1_s / 4096. * 3.);
				n_temp1_n++;
				temp1 = 0.; n_temp1_s = 0;

				//t2 points
				m_dx_t2[ n_temp2_n] = d_global_time;
				m_dy_t2[ n_temp2_n] = 70.24586 * ( temp2 / n_temp2_s / 4096. * 3.) - 128.209;
				//m_dy_t2[ n_temp2_n] = ( temp2 / n_temp2_s / 4096. * 3.);
				n_temp2_n++;
				temp2 = 0.; n_temp2_s = 0;

        //t3 points
				m_dx_t3[ n_temp3_n] = d_global_time;
				m_dy_t3[ n_temp3_n] = 70.24586 * ( temp3 / n_temp3_s / 4096. * 3.) - 128.209;
				n_temp3_n++;
				temp3 = 0.; n_temp3_s = 0;

				//tsa points
				m_dx_tsa[ n_tsa_n] = d_global_time;
				m_dy_tsa[ n_tsa_n] = tsa / n_tsa_s;
				n_tsa_n++;
				tsa = 0.; n_tsa_s = 0;
			}

			//1-секундные точки
			if( t1s > 1.) {
				m_dx1s[n1s] = d_global_time;
				m_dy1s[n1s] = w1s / t1s;
				n1s++;
				m_dn1s += 1.;
				w1s = 0.; t1s = 0.;
			}

			//10-секундные точки
			if( t10s > 10.) {
				m_dx10s[n10s] = d_global_time;
				m_dy10s[n10s] = w10s / t10s;
				n10s++;
				m_dn10s += 1.;
				w10s = 0.; t10s = 0.;
			}

			//100-секундные точки
			if( t100s > 100.) {
				m_dx100s[n100s] = d_global_time;
				m_dy100s[n100s] = w100s / t100s;
				n100s++;
				m_dn100s += 1.;


				w100s = 0.; t100s = 0.;
			}

			if( dlg != NULL)
				if( !( n100m % 50))
					dlg->m_ctlProgress.SetPos( ftell( fh));

			if( feof( fh))
				break;
		}
	} //endif (it's old ascii stat file)

	fclose( fh);
	/*fclose( fh_test_needs);*/

	RecalculateStatistics();
}
