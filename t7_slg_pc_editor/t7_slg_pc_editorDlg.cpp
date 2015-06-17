// t7_slg_pc_editorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "t7_slg_pc_editor.h"
#include "t7_slg_pc_editorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_FLUSH_COM 10000
#define TIMER_COM_STATE 10001
#define TIMER_REFRESH_DATA 10002
#define TIMER_FIRST_TIME_DATA 10003
#define TIMER_ORG_REQUEST 10004
#define TIMER_UNBLOCK_CONTROLS_UPON_SENT 10005
extern HANDLE gl_hThread;
extern DWORD WINAPI BigThread(LPVOID lparam);

extern CT7_slg_pc_editorApp theApp;
extern int gl_nCircleBufferGet;
extern int gl_nCircleBufferPut;
extern int gl_GetCircleBufferDistance( void);
extern bool PutByteInCircleBuffer(BYTE bt);
extern BOOL m_bStopBigThreadFlag;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT7_slg_pc_editorDlg dialog

CT7_slg_pc_editorDlg::CT7_slg_pc_editorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CT7_slg_pc_editorDlg::IDD, pParent)
{
  theApp.GetLogger()->LogTrace( "CT7_slg_pc_editorDlg::CT7_slg_pc_editorDlg: in");
	//{{AFX_DATA_INIT(CT7_slg_pc_editorDlg)
	m_nComPort = 0;
	m_nPortSpeed = 0;
	m_strConnectionStatus = _T("Разъединено");
	m_strLblEmergency = _T("");
	m_strOrganization = _T("");
	m_dblAmplCodeIn = 0.0;
	m_nTactCodeIn = 0;
	m_dblMCoeff = 0.0;
	m_nStartMode = 0;
	m_dblMinI1 = 0.0;
	m_dblMinI2 = 0.0;
	m_dblMinAmplAng = 0.0;
	m_dblDecCoeff = 0.0;
	m_nSignCoeff = 0;
	m_strMcVersion = _T("-");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  theApp.GetLogger()->LogTrace( "CT7_slg_pc_editorDlg::CT7_slg_pc_editorDlg: out");
}

void CT7_slg_pc_editorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CT7_slg_pc_editorDlg)
	DDX_CBIndex(pDX, IDC_CMB_COM, m_nComPort);
	DDX_CBIndex(pDX, IDC_CMB_PORT_SPEED, m_nPortSpeed);
	DDX_Text(pDX, IDC_STR_CONN_STATE, m_strConnectionStatus);
	DDX_Control(pDX, IDC_MSCOMM, m_ctlCOM);
	DDX_Text(pDX, IDC_LBL_EMERGENCY, m_strLblEmergency);
	DDX_Text(pDX, IDC_EDT_ORGANISATION_OUT, m_strOrganization);
	DDX_Text(pDX, IDC_EDT_AMPL_CODE_IN, m_dblAmplCodeIn);
	DDX_Text(pDX, IDC_EDT_TACT_CODE_IN, m_nTactCodeIn);
	DDX_Text(pDX, IDC_EDT_M_COEFF_IN, m_dblMCoeff);
	DDX_Text(pDX, IDC_EDT_START_MODE_IN, m_nStartMode);
	DDX_Text(pDX, IDC_EDT_MIN_CUR1_IN, m_dblMinI1);
	DDX_Text(pDX, IDC_EDT_MIN_CUR2_IN, m_dblMinI2);
	DDX_Text(pDX, IDC_EDT_MIN_AMPL_ANG_IN, m_dblMinAmplAng);
	DDX_Text(pDX, IDC_EDT_DEC_COEFF_IN, m_dblDecCoeff);
	DDX_Text(pDX, IDC_EDT_SIGN_COEFF_IN, m_nSignCoeff);
	DDX_Text(pDX, IDC_STR_MC_VER, m_strMcVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CT7_slg_pc_editorDlg, CDialog)
	//{{AFX_MSG_MAP(CT7_slg_pc_editorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, OnBtnDisconnect)
	ON_EN_CHANGE(IDC_EDT_ORGANISATION_OUT, OnChangeEdtOrganisationOut)
	ON_BN_CLICKED(IDC_BTN_APPLY_SCALE_COEFF, OnBtnApplyScaleCoeff)
	ON_EN_KILLFOCUS(IDC_EDT_SIGN_COEFF_OUT, OnKillfocusEdtSignCoeffOut)
	ON_BN_CLICKED(IDC_BTN_REQUEST_PARAMS, OnBtnRequestParams)
	ON_BN_CLICKED(IDC_BTN_REQUEST_SERNUM, OnBtnRequestSernum)
	ON_BN_CLICKED(IDC_BTN_REQUEST_DATE, OnBtnRequestDate)
	ON_BN_CLICKED(IDC_BTN_REQUEST_ORG, OnBtnRequestOrg)
	ON_CBN_SELCHANGE(IDC_CMB_COM, OnSelchangeCmbCom)
	ON_CBN_SELCHANGE(IDC_CMB_PORT_SPEED, OnSelchangeCmbPortSpeed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT7_slg_pc_editorDlg message handlers

BOOL CT7_slg_pc_editorDlg::OnInitDialog()
{
  theApp.GetLogger()->LogInfo( "CT7_slg_pc_editorDlg::OnInitDialog(): in");

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetControlsState( FALSE, TRUE);
	m_nComPort = (( CT7_slg_pc_editorApp *) AfxGetApp())->GetComPort();
	m_nPortSpeed = (( CT7_slg_pc_editorApp *) AfxGetApp())->GetComBaudrate();
	UpdateData( FALSE);


  m_ctlCOM.SetInBufferSize( 2048);
	m_ctlCOM.SetCommPort( 1);
	m_ctlCOM.SetSettings( _T("115200,N,8,1"));
	m_ctlCOM.SetInputLen( 200);
	m_ctlCOM.SetInputMode( 1);
	m_ctlCOM.SetInBufferCount( 0);
	m_ctlCOM.SetOutBufferCount( 0);
	m_ctlCOM.SetOutBufferSize( 3);

  SetTimer( TIMER_COM_STATE, 1000, NULL);

  CString str;
  str.Format( _T("%.3f"), theApp.m_dblScaleCoeff);
  GetDlgItem( IDC_EDT_SCALE_COEFF)->SetWindowText( str);

  m_nFirstTimeRequest = 0;

  theApp.GetLogger()->LogInfo( "CT7_slg_pc_editorDlg::OnInitDialog(): out");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CT7_slg_pc_editorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CT7_slg_pc_editorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CT7_slg_pc_editorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CT7_slg_pc_editorDlg::SetControlsState( BOOL bDeviceConnectionPresent, BOOL bCanConnect)
{
	GetDlgItem( IDC_CMB_COM)->EnableWindow( !bDeviceConnectionPresent);
	GetDlgItem( IDC_CMB_PORT_SPEED)->EnableWindow( !bDeviceConnectionPresent);
	GetDlgItem( IDC_BTN_CONNECT)->EnableWindow( bCanConnect);
	GetDlgItem( IDC_BTN_DISCONNECT)->EnableWindow( bDeviceConnectionPresent);

  GetDlgItem( IDC_BTN_SEND_AMPL)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_TACTCODE)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_M_COEFF)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_START_MODE)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_SERIAL)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_ORGANIZATION)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_DATE)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_I1_MIN)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_I2_MIN)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_AMPLANG_MIN)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_DEC_COEFF)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_SIGNCOEFF)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_SEND_PHASE_SHIFT)->EnableWindow( bDeviceConnectionPresent);

  GetDlgItem( IDC_BTN_REQUEST_PARAMS)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_REQUEST_SERNUM)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_REQUEST_ORG)->EnableWindow( bDeviceConnectionPresent);
  GetDlgItem( IDC_BTN_REQUEST_DATE)->EnableWindow( bDeviceConnectionPresent);

	GetDlgItem( IDC_EDT_AMPL_CODE_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_TACT_CODE_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_M_COEFF_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_START_MODE_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_SER_NUM_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_ORGANISATION_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_MIN_CUR1_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_MIN_CUR2_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_MIN_AMPL_ANG_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_DEC_COEFF_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_SIGN_COEFF_OUT)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_PHASE_SHIFT_OUT)->EnableWindow( bDeviceConnectionPresent);

  /*
	GetDlgItem( IDC_EDT_TCALIB_T1_TD1)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_TCALIB_T1_TD2)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_TCALIB_T2_TD1)->EnableWindow( bDeviceConnectionPresent);
	GetDlgItem( IDC_EDT_TCALIB_T2_TD2)->EnableWindow( bDeviceConnectionPresent);
  */
	GetDlgItem( IDC_BTN_RESET_CALIB)->EnableWindow( bDeviceConnectionPresent);
		
	
}

void CT7_slg_pc_editorDlg::OnDestroy() 
{
	UpdateData( TRUE);
	CDialog::OnDestroy();
	
	(( CT7_slg_pc_editorApp *) AfxGetApp())->SetComPort( m_nComPort);
	(( CT7_slg_pc_editorApp *) AfxGetApp())->SetComBaudrate( m_nPortSpeed);
}

void CT7_slg_pc_editorDlg::OnBtnConnect() 
{
  UpdateData( TRUE);
  m_ctlCOM.SetCommPort( 1 + m_nComPort);
  switch( m_nPortSpeed) {
    case 0: m_ctlCOM.SetSettings( _T("57600,N,8,1")); break;
    case 1: m_ctlCOM.SetSettings( _T("115200,N,8,1")); break;
    case 2: m_ctlCOM.SetSettings( _T("128000,N,8,1")); break;
    case 3: m_ctlCOM.SetSettings( _T("256000,N,8,1")); break;
    case 4: m_ctlCOM.SetSettings( _T("460800,N,8,1")); break;
    case 5: m_ctlCOM.SetSettings( _T("512000,N,8,1")); break;
  }

	
  m_ctlCOM.SetPortOpen( true);

  SetTimer( TIMER_FLUSH_COM, 100, NULL);
  
  
  m_bStopBigThreadFlag = FALSE;
  
  DWORD id2;
  gl_hThread = ::CreateThread(0, 0, &BigThread, 0, 0, &id2);

  GetDlgItem( IDC_BTN_CONNECT)->EnableWindow( FALSE);
  SetTimer( TIMER_FIRST_TIME_DATA, 100, NULL);
  SetTimer( TIMER_REFRESH_DATA, 1000, NULL);
}

void CT7_slg_pc_editorDlg::OnBtnDisconnect() 
{
	m_ctlCOM.SetPortOpen( false);

	KillTimer( TIMER_FLUSH_COM);
  KillTimer( TIMER_REFRESH_DATA);
	m_bStopBigThreadFlag = true;
		
  SetControlsState( FALSE, TRUE);

	gl_nCircleBufferGet = 0;
  gl_nCircleBufferPut = 0;	
}

void CT7_slg_pc_editorDlg::OnTimer(UINT nIDEvent) 
{
  switch( nIDEvent) {
    case TIMER_FLUSH_COM:
      //theApp.GetLogger()->LogTrace( "CT7_slg_pc_editorDlg::OnTimer(TIMER_FLUSH_COM)");
      if( m_ctlCOM.GetPortOpen()) {
				
				short nBytes = m_ctlCOM.GetInBufferCount();
				if( nBytes > 10) {
					VARIANT var = m_ctlCOM.GetInput();
					
					
					char *buff;//[2048];
					int count = var.parray->rgsabound[0].cElements;
					buff = new char[count];
					/*
					if( count<0 || count > 2048) {
						CString strError;
						strError.Format( _T("COUNT: %d"), count);
						AfxMessageBox( strError);
						Beep( 1000, 1000);
					}
					*/
					memcpy( buff, var.parray->pvData, count);

					for( int qq=0; qq<count; qq++) {
						//fprintf( ((CSlg2App*) AfxGetApp())->fhb, "%x", buff[qq]);
						if( !PutByteInCircleBuffer( buff[qq])) {
							m_ctlCOM.SetPortOpen( false);
							for( int err=0; err < ERROR_2; err++) {
								Beep( 100, 100);
								Sleep( 200);
							}
							theApp.m_nEmergencyCode = 1002;
							m_strLblEmergency.Format( _T("1002"));
							UpdateData( false);

							m_ctlCOM.SetPortOpen( false);

							KillTimer( TIMER_FLUSH_COM);
              KillTimer( TIMER_REFRESH_DATA);
              
              
							m_bStopBigThreadFlag = true;
		

							gl_nCircleBufferGet = 0;
							gl_nCircleBufferPut = 0;

              SetControlsState( FALSE, FALSE);
						}
					}
				}
			}
			else {
				for( int err=0; err < ERROR_5; err++) {
					Beep( 100, 100);
					Sleep( 200);
				}

        KillTimer( TIMER_FLUSH_COM);
        KillTimer( TIMER_REFRESH_DATA);
        
        
        m_bStopBigThreadFlag = true;
		

				gl_nCircleBufferGet = 0;
				gl_nCircleBufferPut = 0;

				theApp.m_nEmergencyCode = 1005;
				m_strLblEmergency.Format( _T("1005"));
				UpdateData( false);

        SetControlsState( FALSE, FALSE);
			}
    break;

    case TIMER_COM_STATE:
      theApp.GetLogger()->LogTrace( "CT7_slg_pc_editorDlg::OnTimer(TIMER_COM_STATE)");
      if( m_ctlCOM.GetPortOpen()) {
        
        COleDateTimeSpan span = COleDateTime::GetCurrentTime() - theApp.GetLastIncomingData();
        if( span.GetTotalSeconds() > 1) {
          m_strConnectionStatus = "COM-порт открыт. Потока данных нет.";
        }
        else {
          m_strConnectionStatus = "Соединено. Поток данных есть.";
        }
      }
      else
        m_strConnectionStatus = "Разъединено";
      
      UpdateData( FALSE);
    break;

    case TIMER_REFRESH_DATA:
      theApp.GetLogger()->LogTrace( "CT7_slg_pc_editorDlg::OnTimer:TIMER_REFRESH_DATA: theApp.m_dblAngl=%f", theApp.m_dblAmpl);
      m_dblAmplCodeIn = theApp.m_dblAmpl;
      m_nTactCodeIn   = theApp.m_nHangerTact;
      m_dblMCoeff     = theApp.m_dblMcoeff;
      m_nStartMode    = theApp.m_nStartMode;
      m_dblMinI1      = theApp.m_dblControlI1min;
      m_dblMinI2      = theApp.m_dblControlI2min;
      m_dblMinAmplAng = theApp.m_dblAmplAnglmin;
      m_dblDecCoeff   = theApp.m_dblDecCoeff;
      m_nSignCoeff    = theApp.m_nSignCoeff;
      m_strMcVersion.Format( _T("%d.%d.%d"), theApp.m_nMajorVersion, theApp.m_nMiddleVersion, theApp.m_nMinorVersion);
      UpdateData( FALSE);
    break;

    case TIMER_FIRST_TIME_DATA:
      theApp.GetLogger()->LogDebug( "CT7_slg_pc_editorDlg::OnTimer(TIMER_FIRST_TIME_DATA)");
      
      UpdateData( TRUE);
      if( m_strConnectionStatus.Right( 6) != "данных") {
        m_strConnectionStatus += " Запрос данных";
        UpdateData( FALSE);
      }

      switch( m_nFirstTimeRequest) {
        case 0: if( m_ctlCOM.GetPortOpen()) OnBtnRequestParams(); break;
        case 1: if( m_ctlCOM.GetPortOpen()) OnBtnRequestSernum(); break;
        case 2: if( m_ctlCOM.GetPortOpen()) OnBtnRequestDate(); break;
        case 3: 
          KillTimer( TIMER_FIRST_TIME_DATA);
          if( m_ctlCOM.GetPortOpen()) {
            OnBtnRequestOrg();
          }
      }
      
      
      m_nFirstTimeRequest++;
    break;

    case TIMER_ORG_REQUEST:
      theApp.GetLogger()->LogTrace( "CT7_slg_pc_editorDlg::OnTimer(TIMER_ORG_REQUEST)");
      SendCommandToMc( 'a' + m_nCounterOrgRequest, 0, 0);
      m_nCounterOrgRequest++;
      if( m_nCounterOrgRequest == 17)
        KillTimer( TIMER_ORG_REQUEST);
    break;

    case TIMER_UNBLOCK_CONTROLS_UPON_SENT:
      theApp.GetLogger()->LogTrace( "CT7_slg_pc_editorDlg::OnTimer(TIMER_UNBLOCK_CONTROLS_UPON_SENT)");
      KillTimer( TIMER_UNBLOCK_CONTROLS_UPON_SENT);
      SetControlsState( TRUE, !m_ctlCOM.GetPortOpen());
    break;
  }
	CDialog::OnTimer(nIDEvent);
}

void CT7_slg_pc_editorDlg::OnChangeEdtOrganisationOut() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData( TRUE);
  if( m_strOrganization.GetLength() >=16) {
    m_strOrganization = m_strOrganization.Left( 16);
    UpdateData( FALSE);
  }	
}

void CT7_slg_pc_editorDlg::OnBtnApplyScaleCoeff() 
{
  UpdateData( TRUE);
  
  CString str;
  GetDlgItem( IDC_EDT_SCALE_COEFF)->GetWindowText( str);
  double dblScaleCoeff = atof( str);
  if( dblScaleCoeff < 2.5 || dblScaleCoeff > 3.3) {
    dblScaleCoeff = 2.9;    
  }
  theApp.m_dblScaleCoeff = dblScaleCoeff;

  str.Format( _T("%.3f"), theApp.m_dblScaleCoeff);
  GetDlgItem( IDC_EDT_SCALE_COEFF)->SetWindowText( str);  
}

void CT7_slg_pc_editorDlg::OnKillfocusEdtSignCoeffOut() 
{
    int nPrevVal = m_nSignCoeff;
  UpdateData( TRUE);
  if( m_nSignCoeff != 1 || m_nSignCoeff != -1) {
    m_nSignCoeff = nPrevVal;
    UpdateData( FALSE);
  }
}

void CT7_slg_pc_editorDlg::OnBtnRequestParams() 
{
  UpdateData( TRUE);
  if( m_strConnectionStatus.Right( 6) != "данных") {
    m_strConnectionStatus += " Запрос данных";
    UpdateData( FALSE);
  }
  SendCommandToMc( 49, 0, 0);
}

void CT7_slg_pc_editorDlg::SendCommandToMc(BYTE b1, BYTE b2, BYTE b3)
{
  SetControlsState( FALSE, FALSE);
  KillTimer( TIMER_UNBLOCK_CONTROLS_UPON_SENT);

  char str[3];
	str[0] = b1;
	str[1] = b2;
	str[2] = b3;

	SAFEARRAY *psa;
  SAFEARRAYBOUND rgsabound[1];
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = 3;
  psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
	memcpy( psa->pvData, str, 3);
	
	VARIANT var;
	var.vt = VT_ARRAY | VT_UI1;
	var.parray = psa;

	if( m_ctlCOM.GetPortOpen()) {
		m_ctlCOM.SetOutput( var);
		int s = m_ctlCOM.GetOutBufferCount();
	}
	else {
		Beep( 5000, 100);
	}

	SafeArrayDestroy( psa);
  SetTimer( TIMER_UNBLOCK_CONTROLS_UPON_SENT, 300, NULL);
}

void CT7_slg_pc_editorDlg::OnBtnRequestSernum() 
{
	SendCommandToMc( 'S', 0, 0);
}

void CT7_slg_pc_editorDlg::OnBtnRequestDate() 
{
  SendCommandToMc( 'U', 0, 0);
}

void CT7_slg_pc_editorDlg::OnBtnRequestOrg() 
{
  m_nCounterOrgRequest = 0;
  SetTimer( TIMER_ORG_REQUEST, 100, NULL);
}

//DEL void CT7_slg_pc_editorDlg::SetInteractionState(BOOL bEnable)
//DEL {
//DEL   GetDlgItem( IDC_BTN_REQUEST_PARAMS)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_AMPL_CODE_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_AMPL)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_TACT_CODE_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_TACTCODE)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_M_COEFF_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_M_COEFF)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_START_MODE_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_START_MODE)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_MIN_CUR1_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_I1_MIN)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_MIN_CUR2_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_I2_MIN)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_MIN_AMPL_ANG_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_AMPLANG_MIN)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_DEC_COEFF_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_DEC_COEFF)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_SIGN_COEFF_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_SIGNCOEFF)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_EDT_PHASE_SHIFT_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_PHASE_SHIFT)->EnableWindow( bEnable);
//DEL   
//DEL   GetDlgItem( IDC_BTN_REQUEST_SERNUM)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_EDT_SER_NUM_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_SERIAL)->EnableWindow( bEnable);
//DEL   
//DEL   GetDlgItem( IDC_BTN_REQUEST_DATE)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_DTP_DATE_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_DATE)->EnableWindow( bEnable);
//DEL 
//DEL   GetDlgItem( IDC_BTN_REQUEST_ORG)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_EDT_ORGANISATION_OUT)->EnableWindow( bEnable);
//DEL   GetDlgItem( IDC_BTN_SEND_ORGANIZATION)->EnableWindow( bEnable);
//DEL }

void CT7_slg_pc_editorDlg::OnSelchangeCmbCom() 
{
  UpdateData( TRUE);
}

void CT7_slg_pc_editorDlg::OnSelchangeCmbPortSpeed() 
{
  UpdateData( TRUE);
}
