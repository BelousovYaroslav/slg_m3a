// DlgExport.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "DlgExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExport dialog


CDlgExport::CDlgExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExport)
	m_bChkAA = FALSE;
	m_bChkI1 = FALSE;
	m_bChkI2 = FALSE;
	m_bChkT1 = FALSE;
	m_bChkT2 = FALSE;
	m_bChkVpp = FALSE;
	m_nTmean = 0;
	m_strOutputFileName = _T("");
	m_bChkTimeSA = FALSE;
	m_bChkRotAngle = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExport)
	DDX_Control(pDX, IDC_PRG_ACTION, m_ctlProgressBar);
	DDX_Check(pDX, IDC_CHK_AA, m_bChkAA);
	DDX_Check(pDX, IDC_CHK_I1, m_bChkI1);
	DDX_Check(pDX, IDC_CHK_I2, m_bChkI2);
	DDX_Check(pDX, IDC_CHK_T1, m_bChkT1);
	DDX_Check(pDX, IDC_CHK_T2, m_bChkT2);
	DDX_Check(pDX, IDC_CHK_V_PP, m_bChkVpp);
	DDX_Radio(pDX, IDC_NO_MEANING, m_nTmean);
	DDX_Text(pDX, IDC_LBL_OUTPUT_FILENAME, m_strOutputFileName);
	DDX_Check(pDX, IDC_CHK_TSA, m_bChkTimeSA);
	DDX_Check(pDX, IDC_CHK_ROT_SPEED, m_bChkRotAngle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExport, CDialog)
	//{{AFX_MSG_MAP(CDlgExport)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_NO_MEANING, OnNoMeaning)
	ON_BN_CLICKED(IDC_RAD_100M, OnRad100m)
	ON_BN_CLICKED(IDC_RAD_100S, OnRad100s)
	ON_BN_CLICKED(IDC_RAD_10S, OnRad10s)
	ON_BN_CLICKED(IDC_RAD_1S, OnRad1s)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExport message handlers

void CDlgExport::OnOK() 
{
	UpdateData( TRUE);

  //если ничего не выбрали - то и экспортировать нечего
	if( !m_bChkAA && !m_bChkI1 && !m_bChkI2 && !m_bChkRotAngle &&
			!m_bChkT1 && !m_bChkT2 && !m_bChkTimeSA && !m_bChkVpp) {

		AfxMessageBox( _T("Нет отмеченных данных для экспорта!"));
		return;
	}

	FILE *fhOut = fopen( m_strOutputFileName, _T("w"));

	if( m_bChkTimeSA)
		fprintf( fhOut, _T("%-12s"), _T("t,[сек]"));
	
	if( m_bChkRotAngle) {
		if( m_nTmean)
			fprintf( fhOut, _T("%-12s"), _T("w[''/сек]"));
		else
			fprintf( fhOut, _T("%-12s"), _T("phi['']"));
	}

	if( m_bChkI1) fprintf( fhOut, _T("%-12s"), _T("I1,[мА]"));
	if( m_bChkI2) fprintf( fhOut, _T("%-12s"), _T("I2,[мА]"));
	if( m_bChkVpp) fprintf( fhOut, _T("%-12s"), _T("Vpc,[В]"));
	if( m_bChkAA) fprintf( fhOut, _T("%-12s"), _T("AA,['']"));
	if( m_bChkT1) fprintf( fhOut, _T("%-12s"), _T("T1(HIRO),[°C]"));
	if( m_bChkT2) fprintf( fhOut, _T("%-12s"), _T("T2(BODY),[°C]"));
	fprintf( fhOut, _T("\n"));

	FILE *fh;
	switch( m_nStatFileVersion) {
		case 1: fh = fopen( m_strFileName, "r"); break;
		case 2: fh = fopen( m_strFileName, "rb"); break;
		default: CDialog::OnOK(); return;
	}
	

	m_ctlProgressBar.SetRange32( 0, m_nDataFileLines);

	
	//VARIABLES FOR INPUT DATA (OldFormat and NewFormat)
	float of_f1, of_f2;
	int of_i1, of_i2, of_i3;
	//float nf_f1;
	short nf_s1, nf_s2, nf_s3;
  int nf_d1;
			
	int nLine = 0;

	double w_Summ = 0., w_Counter = 0.;
	double i1_Summ = 0., i1_Counter = 0.;
	double i2_Summ = 0., i2_Counter = 0.;
	double vpc_Summ = 0., vpc_Counter = 0.;
	double aa_Summ = 0., aa_Counter = 0.;
	double t1_Summ = 0., t1_Counter = 0., t1_prev = 0.;
	double t2_Summ = 0., t2_Counter = 0., t2_prev = 0.;
	double tsa_Summ = 0.;
	double dGlobalTime = 0.;

	double tMean;
	switch( m_nTmean) {
		case 1: tMean = 0.1; break;
		case 2: tMean = 1.; break;
		case 3: tMean = 10.; break;
		case 4: tMean = 100.; break;
	}

	while( 1) {
		double p_phi, p_tsa;

		switch( m_nStatFileVersion) {
			case 1:
				fscanf( fh, "%f\t%f\t%d\t%d\t%d\n", &of_f1, &of_f2, &of_i1, &of_i2, &of_i3);

				p_phi = of_f1 * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec / 4.;
				w_Summ += p_phi;

				p_tsa = of_i3 / 32768.;
				tsa_Summ += p_tsa;
				dGlobalTime += p_tsa;

				if( of_i1 == 0) { t1_Summ += of_i2; t1_Counter += 1.; }
				if( of_i1 == 1) { t2_Summ += of_i2; t2_Counter += 1.; }
				if( of_i1 == 2) { i1_Summ += of_i2; i1_Counter += 1.; }
				if( of_i1 == 3) { i2_Summ += of_i2; i2_Counter += 1.; }
				if( of_i1 == 4) { vpc_Summ += of_i2; vpc_Counter += 1.; }
				if( of_i1 == 5) { aa_Summ += of_i2; aa_Counter += 1.; }
			break;

			case 2:
				//fread( &nf_f1, sizeof( float), 1, fh);
        fread( &nf_d1, sizeof( int), 1, fh);
				fread( &nf_s1, sizeof( short), 1, fh);
				fread( &nf_s2, sizeof( short), 1, fh);
				fread( &nf_s3, sizeof( short), 1, fh);

				p_phi = ( nf_d1 / 2147483647. * 99310.) * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec / 4.;
				w_Summ += p_phi;

				p_tsa = nf_s3 / 32768.;
				tsa_Summ += p_tsa;
				dGlobalTime += p_tsa;

				if( ( nf_s1 & 0x7F) == 0) {
					t1_Summ += ( unsigned short) nf_s2; t1_Counter += 1.; }
				if( ( nf_s1 & 0x7F) == 1) {
					t2_Summ += ( unsigned short) nf_s2; t2_Counter += 1.; }
				if( ( nf_s1 & 0x7F) == 2) {
					i1_Summ += nf_s2; i1_Counter += 1.; }
				if( ( nf_s1 & 0x7F) == 3) {
					i2_Summ += nf_s2; i2_Counter += 1.; }
				if( ( nf_s1 & 0x7F) == 4) {
					vpc_Summ += nf_s2; vpc_Counter += 1.; }
				if( ( nf_s1 & 0x7F) == 5) {
					aa_Summ += nf_s2; aa_Counter += 1.; }
			break;
		}

		if( feof( fh))
			break;

		if( !m_nTmean) {
			if( m_bChkTimeSA) fprintf( fhOut, _T("%-12.4f"), dGlobalTime);
			if( m_bChkRotAngle) fprintf( fhOut, _T("%-12.4f"), w_Summ);
			if( m_bChkI1) fprintf( fhOut, _T("%-12.4f"), i1_Summ / i1_Counter / 4096. * 3. / 3.973);
			if( m_bChkI2) fprintf( fhOut, _T("%-12.4f"), i2_Summ / i2_Counter / 4096. * 3. / 3.973);
			if( m_bChkVpp) fprintf( fhOut, _T("%-12.4f"), (( vpc_Summ / vpc_Counter / 4096. * 3.) - 2.048) * 100.);
			if( m_bChkAA) fprintf( fhOut, _T("%-12.4f"), ( aa_Summ / aa_Counter / 4096. * 3.) / 0.5);
			
			if( m_bChkT1) {
				//fprintf( fhOut, _T("%-12.4f"), 70.24586 * ( t1_Summ / t1_Counter / 4096. * 3.) - 128.209);
				if( t1_Counter != 0) {
					t1_prev = t1_Summ / t1_Counter / 65535. * 200. - 100.;
					fprintf( fhOut, _T("%-12.4f"), t1_prev);
				}
				else
					fprintf( fhOut, _T("%-12.4f"), t1_prev);
			}

			if( m_bChkT2) {
				//fprintf( fhOut, _T("%-12.4f"), 70.24586 * ( t2_Summ / t2_Counter / 4096. * 3.) - 128.209);
				if( t2_Counter != 0) {
					t2_prev = t2_Summ / t2_Counter / 65535. * 200. - 100.;
					fprintf( fhOut, _T("%-12.4f"), t2_prev);
				}
				else
					fprintf( fhOut, _T("%-12.4f"), t2_prev);
			}

			fprintf( fhOut, _T("\n"));

			tsa_Summ = 0.;
			w_Summ = w_Counter = 0.;
			i1_Summ = i1_Counter = 0.;
			i2_Summ = i2_Counter = 0.;
			vpc_Summ = vpc_Counter = 0.;
			aa_Summ = aa_Counter = 0.;
			t1_Summ = t1_Counter = 0.;
			t2_Summ = t2_Counter = 0.;
		}
		else if( tsa_Summ > tMean) {
      if( m_bChkTimeSA) fprintf( fhOut, _T("%-12.4f"), dGlobalTime);
			if( m_bChkRotAngle) fprintf( fhOut, _T("%-12.4f"), w_Summ / tsa_Summ);
			
      if( m_bChkI1)
        fprintf( fhOut, _T("%-12.4f"), i1_Summ / i1_Counter / 4096. * 3. / 3.973);
			
      if( m_bChkI2)
        fprintf( fhOut, _T("%-12.4f"), i2_Summ / i2_Counter / 4096. * 3. / 3.973);

			if( m_bChkVpp)
        fprintf( fhOut, _T("%-12.4f"), (( vpc_Summ / vpc_Counter / 4096. * 3.) - 2.048) * 100.);
			
			if( m_bChkAA)
				fprintf( fhOut, _T("%-12.4f"), aa_Summ / aa_Counter / 4. * ((CSlg2App *) AfxGetApp())->m_dKimpSec);//( aa_Summ / aa_Counter / 4096. * 3.) / 0.5);
				
			if( m_bChkT1)
				//fprintf( fhOut, _T("%-12.4f"), 70.24586 * ( t1_Summ / t1_Counter / 4096. * 3.) - 128.209);
				fprintf( fhOut, _T("%-12.4f"), t1_Summ / t1_Counter / 65535. * 200. - 100.);

			if( m_bChkT2) 
				//fprintf( fhOut, _T("%-12.4f"), 70.24586 * ( t2_Summ / t2_Counter / 4096. * 3.) - 128.209);
				fprintf( fhOut, _T("%-12.4f"), t2_Summ / t2_Counter / 65535. * 200. - 100.);

			fprintf( fhOut, _T("\n"));

			tsa_Summ = 0.;
			w_Summ = w_Counter = 0.;
			i1_Summ = i1_Counter = 0.;
			i2_Summ = i2_Counter = 0.;
			vpc_Summ = vpc_Counter = 0.;
			aa_Summ = aa_Counter = 0.;
			t1_Summ = t1_Counter = 0.;
			t2_Summ = t2_Counter = 0.;
		}

		nLine++;
		m_ctlProgressBar.SetPos( nLine);

	}

	fclose(fh);
	fclose(fhOut);

	CDialog::OnOK();
}

BOOL CDlgExport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	(( CButton *) GetDlgItem( IDC_CHK_TSA))->SetCheck( BST_CHECKED);
	(( CButton *) GetDlgItem( IDC_CHK_ROT_SPEED))->SetCheck( BST_CHECKED);

	::GetCurrentDirectory( 1024, m_strOutputFileName.GetBuffer( 1024));
	m_strOutputFileName.ReleaseBuffer();
	m_strOutputFileName += _T("\\export.txt");

	UpdateData( FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgExport::OnBtnBrowse() 
{
	UpdateData( TRUE);
	char szFilters[] = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
  CFileDialog fileDlg( FALSE, "txt", "*.txt", OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	if( fileDlg.DoModal() == IDOK) {
		m_strOutputFileName = fileDlg.GetPathName();
		UpdateData( FALSE);
	}
}

void CDlgExport::OnNoMeaning() 
{
	GetDlgItem( IDC_CHK_ROT_SPEED)->SetWindowText( _T("Угол поворота"));
}

void CDlgExport::OnRad100m() 
{
	GetDlgItem( IDC_CHK_ROT_SPEED)->SetWindowText( _T("Угловая скорость"));
	
}

void CDlgExport::OnRad100s() 
{
	GetDlgItem( IDC_CHK_ROT_SPEED)->SetWindowText( _T("Угловая скорость"));
}

void CDlgExport::OnRad10s() 
{
	GetDlgItem( IDC_CHK_ROT_SPEED)->SetWindowText( _T("Угловая скорость"));
}

void CDlgExport::OnRad1s() 
{
	GetDlgItem( IDC_CHK_ROT_SPEED)->SetWindowText( _T("Угловая скорость"));
}
