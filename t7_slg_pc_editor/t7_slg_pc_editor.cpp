// t7_slg_pc_editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "t7_slg_pc_editor.h"
#include "t7_slg_pc_editorDlg.h"
#include "DlgSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// The one and only CT7_slg_pc_editorApp object

CT7_slg_pc_editorApp theApp;




//КОЛЬЦЕВОЙ БУФЕР БАЙТ
#define CYCLE_BUFFER_LEN 32768

char gl_bCircleBuffer[ CYCLE_BUFFER_LEN];
int gl_nCircleBufferGet;
int gl_nCircleBufferPut;
bool gl_PutByteInCircleBuffer( BYTE bt);

int gl_GetCircleBufferDistance( void)
{
	return( ( CYCLE_BUFFER_LEN + gl_nCircleBufferPut - gl_nCircleBufferGet) % CYCLE_BUFFER_LEN);
}

bool PutByteInCircleBuffer(BYTE bt)
{
	if( gl_nCircleBufferPut == gl_nCircleBufferGet - 1) return false;
	gl_bCircleBuffer[ gl_nCircleBufferPut] = bt;
	gl_nCircleBufferPut = ( ++gl_nCircleBufferPut) % CYCLE_BUFFER_LEN;
	return true;
}




/////////////////////////////////////////////////////////////////////////////
// ПОТОК РАСПРЕДЕЛЕНИЯ ДАННЫХ

BOOL m_bStopBigThreadFlag;
HANDLE gl_hThread;
DWORD WINAPI BigThread(LPVOID lparam)
{
	bool bFirstPoint = true;
	double Kcoeff = 1.0;
	CString strError;
	
	BOOL bFirst100msecPointSkipped = false;

	m_bStopBigThreadFlag = false;


	while( !m_bStopBigThreadFlag) {
		int distance = ( CYCLE_BUFFER_LEN + gl_nCircleBufferPut - gl_nCircleBufferGet) % CYCLE_BUFFER_LEN;

    if( distance > 50) {
			BYTE byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8, byte9, byte10, byte11, byte12;
      BYTE btCheckSumm = 0;
			short param, nCur1, nSaTime;
			double dAngle_inc, dCur1, dSaTime;
			
			int nMarkerCounter = 0;
			do {

				//прокручиваем буфер выискивая последовательные 2 байта маркера (0x55, 0xAA)
				if( ( ( CYCLE_BUFFER_LEN + gl_nCircleBufferPut - gl_nCircleBufferGet) % CYCLE_BUFFER_LEN) > 20) {
					byte1 = gl_bCircleBuffer[ gl_nCircleBufferGet];
					gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;

          switch( nMarkerCounter) {
            case 0:
              if( byte1 == 0x55)
                nMarkerCounter++;
            break;

            case 1:
              if( byte1 == 0xAA)
                nMarkerCounter++;  //2! (условие выхода)
              else
                nMarkerCounter = 0;
            break;
          }
				} 
			} while( nMarkerCounter != 2);

      //ПРИРАЩЕНИЕ УГЛА: 4 байта
			byte1 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			byte2 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			byte3 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			byte4 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			
			//float f_dN;
      int n_dN;

			char *ptr;
      
      //ptr = ( char *) &f_dN;
      ptr = ( char *) &n_dN;

			ptr[0] = byte1;
			ptr[1] = byte2;
			ptr[2] = byte3;
			ptr[3] = byte4;
      
			dAngle_inc = ( ( double) n_dN / 2147483647. * 99310.);

			//НОМЕР ЧЕРЕДУЮЩЕГОСЯ (ТЕХНОЛОГИЧЕСКОГО, АНАЛОГОВОГО) ПАРАМЕТРА. 1 байт
			byte5 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			param = byte5;
	
			//ЗНАЧЕНИЕ ТЕХНОЛОГИЧЕСКОГО (АНАЛОГОВОГО) ПАРАМЕТРА. 2 Байта
			byte6 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			byte7 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			nCur1 = ( byte7 << 8) + byte6;
			dCur1 = ( double) (unsigned short) nCur1;
			
			//SA TIMING.
      //ИНТЕРВАЛ ВРЕМЕНИ МЕЖДУ ТЕКУЩИМ И ПРЕДЫДУЩИМ МОМЕНТАМИ ФИКСАЦИИ ПАРАМЕТРОВ. 2 БАЙТА
			byte8 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			byte9 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			nSaTime = ( byte9 << 8) + byte8;
			dSaTime = nSaTime;

      //ПОРЯДКОВЫЙ НОМЕР СООБЩЕНИЯ. 1 БАЙТ
      byte10 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;

			//EMERGENCY CODE
      //КОД ОШИБКИ. 1 БАЙТ
			byte11 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			if( theApp.m_nEmergencyCode == 0)
				theApp.m_nEmergencyCode = byte11;
			
      //CHEKSUMM
      //КОНТРОЛЬНАЯ СУММА, CS. 1 байт
			byte12 = gl_bCircleBuffer[ gl_nCircleBufferGet];
			gl_nCircleBufferGet = ( gl_nCircleBufferGet + 1) % CYCLE_BUFFER_LEN;
			
      btCheckSumm = byte1;
      btCheckSumm += byte2;
      btCheckSumm += byte3;
      btCheckSumm += byte4;
      btCheckSumm += byte5;
      btCheckSumm += byte6;
      btCheckSumm += byte7;
      btCheckSumm += byte8;
      btCheckSumm += byte9;
      btCheckSumm += byte10;
      btCheckSumm += byte11;
      
      if( btCheckSumm != byte12) {
        //TODO несовпадение контрольной суммы
        CString strMsg;
        strMsg.Format( _T("\nBytes:\n%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\nCS(mc): %02x\nCS(pc): %02x"),
                byte1, byte2, byte3, byte4, byte5, byte6,
                byte7, byte8, byte9, byte10, byte11, byte12, btCheckSumm);
        AfxMessageBox( _T("Несовпадение контрольной суммы! FAIL!") + strMsg);
        continue;
        //PostQuitMessage( 0);
      }

      theApp.SetLastIncomingData();
			
      int nD, nM, nY;

			switch( ( byte5 & 0x7f)) {
			  
        //код амплитуды
        case 7: theApp.m_dblAmpl = ( double) nCur1 * theApp.m_dblScaleCoeff;  theApp.GetLogger()->LogDebug( "BigThread::Got 7: %d", nCur1); break;

        //такт подставки
				case 8: theApp.m_nHangerTact = nCur1; theApp.GetLogger()->LogDebug( "BigThread::Got 8: %d", nCur1); break;

        //коэффициент M
				case 9: theApp.m_dblMcoeff = ( double) nCur1 / 250.; theApp.GetLogger()->LogDebug( "BigThread::Got 9: %d", nCur1); break;

        //начальная мода
				case 10: theApp.m_nStartMode = nCur1; theApp.GetLogger()->LogDebug( "BigThread::Got 10: %d", nCur1);  break;

        //контрольный ток I1
        case 11: theApp.m_dblControlI1min = ( double) nCur1 / 65535. * 0.75; theApp.GetLogger()->LogDebug( "BigThread::Got 11: %d", nCur1);  break;

        //контрольный ток I2
			  case 12: theApp.m_dblControlI2min = ( double) nCur1 / 65535. * 0.75; theApp.GetLogger()->LogDebug( "BigThread::Got 12: %d", nCur1);  break;

        //контрольный AmplAng
				case 13: theApp.m_dblAmplAnglmin = ( double) nCur1 / 65535. * 0.75; theApp.GetLogger()->LogDebug( "BigThread::Got 13: %d", nCur1);  break;

				//коэффициент вычета
        case 14: theApp.m_dblDecCoeff = nCur1 / 65535; /*Beep( 100, 100);*/ theApp.GetLogger()->LogDebug( "BigThread::Got 14: %d", nCur1); break;
	        
				//Знаковый коэффициент
        case 15: theApp.m_nSignCoeff = nCur1 - 1; theApp.GetLogger()->LogDebug( "BigThread::Got 15: %d", nCur1); break;

        //версия ПО
				case 16:
          theApp.GetLogger()->LogDebug( "BigThread::Got 16"); 
          theApp.m_nMajorVersion   = ( byte6 / 16);//major
					theApp.m_nMiddleVersion  = byte6 % 16;		//middle
					theApp.m_nMinorVersion   = byte7 / 16;		//minor					
				break; 

        //фазовый сдвиг
        case 25:
          theApp.GetLogger()->LogDebug( "BigThread::Got 25: %d", nCur1); 
				  theApp.m_nPhaseShift = nCur1;
				break;

        case 26: //Device_Num.Byte1
          theApp.GetLogger()->LogDebug( "BigThread::Got 26: %d", nCur1); 
        break;

        case 27: //Device_Num.Byte1
          theApp.GetLogger()->LogDebug( "BigThread::Got 27: %d", nCur1); 
        break;

        case 28: //Organization.Byte1
          theApp.GetLogger()->LogDebug( "BigThread::Got 28: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 0, ( BYTE) nCur1);
        break;

        case 29: //Organization.Byte2
          theApp.GetLogger()->LogDebug( "BigThread::Got 29: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 1, ( BYTE) nCur1);
        break;

        case 30: //Organization.Byte3
          theApp.GetLogger()->LogDebug( "BigThread::Got 30: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 2, ( BYTE) nCur1);
        break;

        case 31: //Organization.Byte4
          theApp.GetLogger()->LogDebug( "BigThread::Got 31: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 3, ( BYTE) nCur1);
        break;    
        
        case 32: //Organization.Byte5
          theApp.GetLogger()->LogDebug( "BigThread::Got 32: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 4, ( BYTE) nCur1);
        break;    
        
        case 33: //Organization.Byte6
          theApp.GetLogger()->LogDebug( "BigThread::Got 33: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 5, ( BYTE) nCur1);
        break;    
        
        case 34: //Organization.Byte7
          theApp.GetLogger()->LogDebug( "BigThread::Got 34: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 6, ( BYTE) nCur1);
        break;    
        
        case 35: //Organization.Byte8
          theApp.GetLogger()->LogDebug( "BigThread::Got 35: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 7, ( BYTE) nCur1);
        break;    
        
        case 36: //Organization.Byte9
          theApp.GetLogger()->LogDebug( "BigThread::Got 36: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 8, ( BYTE) nCur1);
        break;    
        
        case 37: //Organization.Byte10
          theApp.GetLogger()->LogDebug( "BigThread::Got 37: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 9, ( BYTE) nCur1);
        break;    
        
        case 38: //Organization.Byte11
          theApp.GetLogger()->LogDebug( "BigThread::Got 38: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 10, ( BYTE) nCur1);
        break;    
        
        case 39: //Organization.Byte12
          theApp.GetLogger()->LogDebug( "BigThread::Got 39: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 11, ( BYTE) nCur1);
        break;    
        
        case 40: //Organization.Byte13
          theApp.GetLogger()->LogDebug( "BigThread::Got 40: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 12, ( BYTE) nCur1);
        break;    
        
        case 41: //Organization.Byte14
          theApp.GetLogger()->LogDebug( "BigThread::Got 41: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 13, ( BYTE) nCur1);
        break;    
        
        case 42: //Organization.Byte15
          theApp.GetLogger()->LogDebug( "BigThread::Got 42: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 14, ( BYTE) nCur1);
        break;    

        case 43: //Organization.Byte16    БЕЗ завершающего 0 на конце!!!!!
          theApp.GetLogger()->LogDebug( "BigThread::Got 43: %d", nCur1); 
          theApp.m_strOrganization.SetAt( 15, ( BYTE) nCur1);
        break;    

        case 44: //Date.Year
          theApp.GetLogger()->LogDebug( "BigThread::Got 44: %d", nCur1); 
          nD = theApp.m_dtmDate.GetDay(), nM = theApp.m_dtmDate.GetMonth(), nY = theApp.m_dtmDate.GetYear();
          theApp.m_dtmDate.SetDate( nY, nM, nCur1);
        break;    

        case 45: //Date.Month
          theApp.GetLogger()->LogDebug( "BigThread::Got 45: %d", nCur1); 
          nD = theApp.m_dtmDate.GetDay(), nM = theApp.m_dtmDate.GetMonth(), nY = theApp.m_dtmDate.GetYear();
          theApp.m_dtmDate.SetDate( nY, nCur1, nD);
        break;    

        case 46: //Date.Day
          theApp.GetLogger()->LogDebug( "BigThread::Got 46: %d", nCur1); 
          nD = theApp.m_dtmDate.GetDay(), nM = theApp.m_dtmDate.GetMonth(), nY = theApp.m_dtmDate.GetYear();
          theApp.m_dtmDate.SetDate( nCur1, nM, nD);
        break;    
			}

				

		} //если растояние кольцевого буфера > 50		
		else
			Sleep( 1);
	} //while жизни потока

	return 1;
}




/////////////////////////////////////////////////////////////////////////////
// CT7_slg_pc_editorApp

BEGIN_MESSAGE_MAP(CT7_slg_pc_editorApp, CWinApp)
	//{{AFX_MSG_MAP(CT7_slg_pc_editorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT7_slg_pc_editorApp construction

CT7_slg_pc_editorApp::CT7_slg_pc_editorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// CT7_slg_pc_editorApp initialization

BOOL CT7_slg_pc_editorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	//ЧТЕНИЕ НАСТРОЕК
  theApp.SetRegistryKey(_T("Alcor Laboratories"));
	theApp.LoadStdProfileSettings();
  m_pSettings.LoadSettings();
	/*m_nComPort = GetProfileInt( _T("SETTINGS"), _T("COM_PORT"), 0);
	m_nComBaudrate = GetProfileInt( _T("SETTINGS"), _T("COM_BAUDRATE"), 0);
  int nScaleCoeff = GetProfileInt( _T("SETTINGS"), _T("SCALECOEFF"), 2900);
  m_dblScaleCoeff = nScaleCoeff / 1000.;*/
  
  m_nComPort = m_pSettings.GetComPort();
  m_nComBaudrate = m_pSettings.GetComBaudrate();
  m_dblScaleCoeff = m_pSettings.GetScaleCoeff();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  m_dtmLastIncomingDataTime = COleDateTime::GetCurrentTime();

  m_pLogger.Init();
  GetLogger()->LogInfo( "CT7_slg_pc_editorApp::InitInstance(): in");

  m_dblAmpl = 0.0;
  m_nHangerTact = 0;
  m_dblMcoeff = 0.;
  m_nStartMode = 0;
  m_dblControlI1min = 0.;
  m_dblControlI2min = 0.;
  m_nSignCoeff = 0;
  m_dblAmplAnglmin = 0;
  m_nMajorVersion = 0; m_nMiddleVersion = 0; m_nMinorVersion = 0;
  m_nPhaseShift = 0;
  m_dblDecCoeff = 0.;

  m_strOrganization = "                 ";
  int nResponse;
  try {
    GetLogger()->LogInfo( "CT7_slg_pc_editorApp::InitInstance(): before dlg construction");
	  CT7_slg_pc_editorDlg dlg;
    //CDlgSettings dlg;

	  m_pMainWnd = &dlg;

    GetLogger()->LogInfo( "CT7_slg_pc_editorApp::InitInstance(): before dlg doModal");
	  nResponse = dlg.DoModal();
  }
  catch( CException *e) {
    e->Delete();
    DWORD k = GetLastError();
    CString strMsg, strMsg2;
    e->GetErrorMessage( strMsg2.GetBuffer( 255), 255);
    strMsg2.ReleaseBuffer();
    strMsg.Format( "GetLastError(): %ld\nMessage:%s", k, strMsg2);
    AfxMessageBox( strMsg);
  }
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if( nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

  GetLogger()->LogInfo( "CT7_slg_pc_editorApp::InitInstance(): out");
	return FALSE;
}

int CT7_slg_pc_editorApp::ExitInstance() 
{
  m_pSettings.SetComPort( m_nComPort);
  m_pSettings.SetComBaudrate( m_nComBaudrate);
  m_pSettings.SetScaleCoeff( m_dblScaleCoeff);

  m_pSettings.SaveSettings();
	return CWinApp::ExitInstance();
}

void CT7_slg_pc_editorApp::SetLastIncomingData()
{
  m_dtmLastIncomingDataTime = COleDateTime::GetCurrentTime();
}
