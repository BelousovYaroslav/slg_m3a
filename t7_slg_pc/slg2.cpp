// slg2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "slg2.h"

#include "MainFrm.h"
#include "slg2Doc.h"
#include "slg2View.h"
#include "MainView.h"

#include "WizardSelRunTypeStep.h"
#include "WizardSelComPortStep.h"
#include "SlgNewAverager.h"
#include "Serial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES!!!!
double gl_pTsa;
double gl_pw100;
double gl_pi1;
double gl_pi2;
double gl_pVpc;
double gl_pAA;
double gl_pT1;
double gl_pT2;
double gl_pT3;
double gl_pTSamean;

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

double gl_dGlobalTime;
CSlgNewAverager gl_avW100;
CSlgNewAverager gl_avW1000;
CSlgNewAverager gl_avW10000;
CSlgNewAverager gl_avW100000;
CSlgNewAverager gl_avI1;
CSlgNewAverager gl_avI2;
CSlgNewAverager gl_avVpc;
CSlgNewAverager gl_avAmplAng;
CSlgNewAverager gl_avT1;
CSlgNewAverager gl_avT2;
CSlgNewAverager gl_avT3;
CSlgNewAverager gl_avTsa;
CSlgNewAverager gl_avTsa1000;
CSlgNewAverager gl_avTsa10000;
CSlgNewAverager gl_avTsa100000;

BOOL gl_bDnDu = false;
double gl_dNdU_dN[ CYCLE_BUFFER_DN_DU];
double gl_dNdU_dU[ CYCLE_BUFFER_DN_DU];
double gl_dNdU_DecCoeff[ CYCLE_BUFFER_DN_DU];
int gl_dec_coeff_cntr = 0;

double gl_dec_coeff_dN_acc;
double gl_dec_coeff_dU_acc;
double gl_dec_coeff_acc;
int gl_dec_coeff_acc_cntr = 0;

double gl_dec_coeff_low_filter = 200.;

BOOL gl_dec_coeff_overround = false;

/////////////////////////////////////////////////////////////////////////////
// ПОТОК РАСПРЕДЕЛЕНИЯ ДАННЫХ

BOOL m_bStopBigThreadFlag;

DWORD WINAPI BigThread(LPVOID lparam)
{
	bool bFirstPoint = true;
	double Kcoeff = 1.0;
	CString strError;
	
	BOOL bFirst100msecPointSkipped = false;

	m_bStopBigThreadFlag = false;

	gl_pTsa = gl_pw100 = gl_pi1 = gl_pi2 = gl_pVpc = gl_pAA = gl_pT1 = gl_pT2 = gl_pT3 = gl_pTSamean = 0.;

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
			
      /*
			if( ( byte5 & 0x7f) == 16) {
				( ( CSlg2App *) AfxGetApp())->m_strSoftwareVer.Format(_T("v%d.%d.%d.0"), 
							(byte6 / 16),		//major
							byte6 % 16,			//middle
							byte7 / 16);		//minor

			}
      */

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
			if( (( CSlg2App *) AfxGetApp())->m_nEmergencyCode == 0)
				(( CSlg2App *) AfxGetApp())->m_nEmergencyCode = byte11;
			
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

			/*
			//if( nCur1 == -1) {
				if( byte5 == 2) {
					Beep( 1000, 100);
					CString pack;
					pack.Format( _T("0x%02x 0x%02x 0x%02x 0x%02x   0x%02x   0x%02x 0x%02x   0x%02x 0x%02x   0x%02x"),
							byte1, byte2, byte3, byte4,
							byte5,
							byte6, byte7,
							byte8, byte9,
							byte10);
					AfxMessageBox( pack);
				}
			//}*/

			if( gl_bDnDu) {
        //режим рассчёта коэффициента вычета
        //От гироскопа нам передаются dN и dU - всё остальное бубуйня

				gl_dNdU_dN[ gl_dec_coeff_cntr] = dAngle_inc;
				gl_dNdU_dU[ gl_dec_coeff_cntr] = dSaTime;

				gl_dec_coeff_dN_acc += fabs( dAngle_inc);
				gl_dec_coeff_dU_acc += fabs( dSaTime);

				/*
				if( fabs( dSaTime) > gl_dec_coeff_low_filter) {
					gl_dNdU_DecCoeff[ gl_dec_coeff_cntr] = dAngle_inc / dSaTime;
					
					gl_dec_coeff_dN_acc += fabs( dAngle_inc);
					gl_dec_coeff_dU_acc += fabs( dSaTime);
					
					gl_dec_coeff_acc += dAngle_inc / dSaTime;
					gl_dec_coeff_acc_cntr++;
				}
				else {
					gl_dNdU_DecCoeff[ gl_dec_coeff_cntr] = 0.;
				}*/

				gl_dec_coeff_cntr++;
				if( gl_dec_coeff_cntr == CYCLE_BUFFER_DN_DU) {
					gl_dec_coeff_overround = true;
				}
				gl_dec_coeff_cntr = ( gl_dec_coeff_cntr % CYCLE_BUFFER_DN_DU);

			}
			else {
				//Рабочий режим получения протокола

				CSlg2App *app = ( CSlg2App *) AfxGetApp();
				if( bFirst100msecPointSkipped) {
					/*if( (( CSlg2App *) AfxGetApp())->fh != NULL)
						fprintf( (( CSlg2App *) AfxGetApp())->fh, _T("%.5f\t%.5f\t%d\t%d\t%d\n"), f_dN, dAngle_inc, param, nCur1, nSaTime);
					else
						AfxMessageBox( _T("Попытка записи данных в файл с закрытым дескриптором."));*/

					if( (( CSlg2App *) AfxGetApp())->fhNew != NULL) {
						//fwrite( &f_dN, sizeof( float), 1, app->fhNew);					//f_dN
            fwrite( &n_dN, sizeof( int), 1, app->fhNew);					    //n_dN

						//fwrite( &dAngle_inc, sizeof( double), 1, app->fhNew);	//dAngle_inc
						fwrite( &param, sizeof( short), 1, app->fhNew);				  //param
						fwrite( &nCur1, sizeof( short), 1, app->fhNew);				  //nCur1
						fwrite( &nSaTime, sizeof( short), 1, app->fhNew);				//nSaTime
            
            /*
            //DELETEME
            short shFinalPart = 0xffff;
            fwrite( &shFinalPart, sizeof( short), 1, app->fhNew);
            //DELETEME
            */

					}
					else
						AfxMessageBox( _T("Попытка записи данных в bin-файл с закрытым дескриптором."));
				}
				gl_avW100.AddPoint( dAngle_inc);
				gl_avW1000.AddPoint( dAngle_inc);
				gl_avW10000.AddPoint( dAngle_inc);
				gl_avW100000.AddPoint( dAngle_inc);

				/*if( param & 0x80)
					Beep( 1000, 10);*/

        CString str;

				switch( (byte5 & 0x7f)) {
					case 0: gl_avT1.AddPoint( dCur1);			break;
					case 1: gl_avT2.AddPoint( dCur1);			break;
          case 2: gl_avT3.AddPoint( dCur1);			break;
					case 3: gl_avI1.AddPoint( dCur1);			break;
					case 4: gl_avI2.AddPoint( dCur1);			break;
					case 5: gl_avVpc.AddPoint( dCur1);		break;
					case 6: gl_avAmplAng.AddPoint( dCur1); break;
					case 7: ( ( CSlg2App *) AfxGetApp())->m_btParam1 = nCur1;  break;
					case 8: ( ( CSlg2App *) AfxGetApp())->m_btParam2 = nCur1; break;
					case 9: ( ( CSlg2App *) AfxGetApp())->m_btParam3 = nCur1; break;
					case 10: ( ( CSlg2App *) AfxGetApp())->m_btParam4 = nCur1; break;
					case 11: ( ( CSlg2App *) AfxGetApp())->m_shFlashI1min = nCur1; break; //flashParamI1min
			    case 12: ( ( CSlg2App *) AfxGetApp())->m_shFlashI2min = nCur1; break; //flashParamI2min
				  case 13: ( ( CSlg2App *) AfxGetApp())->m_shFlashAmplAng1min = nCur1; break; //flashParamAmplAngMin1
					case 14: ( ( CSlg2App *) AfxGetApp())->m_shFlashDecCoeff = nCur1; /*Beep( 100, 100);*/ break; //коэффициент вычета
	        
					case 15:
						/*if( ( nCur1 != 0) || ( nCur1 != 2))
							( ( CSlg2App *) AfxGetApp())->m_shSignCoeff = 1;
						else
							( ( CSlg2App *) AfxGetApp())->m_shSignCoeff = nCur1-1;*/
						( ( CSlg2App *) AfxGetApp())->m_shSignCoeff = (( signed short) nCur1) - 1;

            /*
            str.Format( "$nCur1:%d $SignCoeff:%d", ( signed short) nCur1, ( ( CSlg2App *) AfxGetApp())->m_shSignCoeff);
            AfxMessageBox( str);
            */

						/*Beep(200, 100);*/
					break; //flashParamSignCoeff

					case 16:
						//( ( CSlg2App *) AfxGetApp())->m_nSoftwareVer = nCur1;				//версия ПО
						/*Beep( 300, 100);*/
            ( ( CSlg2App *) AfxGetApp())->m_strSoftwareVer.Format(_T("v%d.%d.%d.0"), 
							(byte6 / 16),		//major
							byte6 % 16,			//middle
							byte7 / 16);		//minor
					break; 

					case 17:
						//сбросим признак что у нас всё калибровано и поднимем его только когда придет 21 байтик и у нас все будет оке
						
						/*
						( ( CSlg2App *) AfxGetApp())->m_bThermoCalibrated = FALSE;
						*/

						( ( CSlg2App *) AfxGetApp())->m_shFlashT1 = nCur1;
						( ( CSlg2App *) AfxGetApp())->m_shFlashT1 -= THERMO_CALIB_PARAMS_BASE;
						/*Beep( 400, 100);*/
					break;		//калибровка термодатчиков: min T

					case 18: ( ( CSlg2App *) AfxGetApp())->m_shFlashTD1_1 = nCur1; /*Beep( 500, 100);*/break; //калибровка термодатчиков: TD1_minT
					case 19: ( ( CSlg2App *) AfxGetApp())->m_shFlashTD2_1 = nCur1; /*Beep( 600, 100);*/break; //калибровка термодатчиков: TD2_minT
          case 20: ( ( CSlg2App *) AfxGetApp())->m_shFlashTD3_1 = nCur1; /*Beep( 600, 100);*/break; //калибровка термодатчиков: TD3_minT

					case 21:
						( ( CSlg2App *) AfxGetApp())->m_shFlashT2 = nCur1;
						( ( CSlg2App *) AfxGetApp())->m_shFlashT2 -= THERMO_CALIB_PARAMS_BASE;
						/*Beep( 700, 100);*/
					break;		//калибровка термодатчиков: max T

					case 22: ( ( CSlg2App *) AfxGetApp())->m_shFlashTD1_2 = nCur1; /*Beep( 800, 100);*/break; //калибровка термодатчиков: TD1_maxT
					case 23: ( ( CSlg2App *) AfxGetApp())->m_shFlashTD2_2 = nCur1; /*Beep( 900, 100);*/ break; //калибровка термодатчиков: TD2_maxT
          case 24: ( ( CSlg2App *) AfxGetApp())->m_shFlashTD3_2 = nCur1; /*Beep( 900, 100);*/ break; //калибровка термодатчиков: TD3_maxT
					
					case 25:
						( ( CSlg2App *) AfxGetApp())->m_shPhaseShift = nCur1;
					break; //фазовый сдвиг
				}

				/*
				//проверка калибровки термодатчиков
				if( ( byte5 & 0x7f) == 21) {
					if( ( ( CSlg2App *) AfxGetApp())->m_shFlashT1 >= MIN_T_THERMO_CALIBRATION &&
							( ( CSlg2App *) AfxGetApp())->m_shFlashT1 <= MAX_T_THERMO_CALIBRATION) {
						if( ( ( CSlg2App *) AfxGetApp())->m_shFlashT2 >= MIN_T_THERMO_CALIBRATION &&
								( ( CSlg2App *) AfxGetApp())->m_shFlashT2 <= MAX_T_THERMO_CALIBRATION) {
							
							
							( ( CSlg2App *) AfxGetApp())->m_bThermoCalibrated = TRUE;
							
							
							double x1, y1, x2, y2;

							x1 = ( ( CSlg2App *) AfxGetApp())->m_shFlashT1;
							x2 = ( ( CSlg2App *) AfxGetApp())->m_shFlashT2;

							
							y1 = ( ( CSlg2App *) AfxGetApp())->m_shFlashTD1_1;
							y2 = ( ( CSlg2App *) AfxGetApp())->m_shFlashTD1_2;

							( ( CSlg2App *) AfxGetApp())->m_dThermoCalibB_1TD = ( x2 * y1 - x1 * y2) / ( x1 - x2);
							( ( CSlg2App *) AfxGetApp())->m_dThermoCalibK_1TD = ( y2 - y1) / ( x2 - x1);


							y1 = ( ( CSlg2App *) AfxGetApp())->m_shFlashTD2_1;
							y2 = ( ( CSlg2App *) AfxGetApp())->m_shFlashTD2_2;

							( ( CSlg2App *) AfxGetApp())->m_dThermoCalibB_2TD = ( x2 * y1 - x1 * y2) / ( x1 - x2);
							( ( CSlg2App *) AfxGetApp())->m_dThermoCalibK_2TD = ( y2 - y1) / ( x2 - x1);
						}
					}
				}*/

				gl_avTsa.AddPoint( dSaTime);
				gl_avTsa1000.AddPoint( dSaTime);
				gl_avTsa10000.AddPoint( dSaTime);
				gl_avTsa100000.AddPoint( dSaTime);
			}

      // **************************************************
      // ОСРЕДНЕНИЕ 100 мсек
      // **************************************************

			if( gl_avTsa.GetSumm() > 3277.) {
				//накопили 100мсек
				if( bFirst100msecPointSkipped) {
					double Nimp = gl_avW100.GetSumm();				//количество импульсов (суммированное)
					gl_avW100.Reset();

					if( gl_avI1.GetCounter()) {
						double i1 = gl_avI1.GetMean();						//разрядный ток i1
						gl_pi1 = ( 2.5 - i1 / 4096. * 3.) / 2.5;	// mA
					}
					

					if( gl_avI2.GetCounter()) {
						double i2 = gl_avI2.GetMean();						//разрядный ток i2
						gl_pi2 = ( 2.5 - i2 / 4096. * 3.) / 2.5;;									// mA
					}

					if( gl_avVpc.GetCounter()) {
						double Vpc = gl_avVpc.GetMean();					//напряжение на пьезокорректорах
						gl_pVpc = ( ( Vpc / 4096. * 3.) - 2.048) * 100.;	// V
					}

					if( gl_avAmplAng.GetCounter()) {
						double AmplAng = gl_avAmplAng.GetMean();	//amplang
						//gl_pAA = AmplAng / 4096. * 3. / 0.5;							// V
						gl_pAA = AmplAng / 4. * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec;	
					}

          
          
          if( gl_avT1.GetCounter()) {
						double T1 = gl_avT1.GetMean();						//термодатчик 1
						gl_pT1 = T1 / 65535. * 200. - 100.;				//V!
					}
          /*
          if( gl_avT1.GetCounter()) {
						double T1 = gl_avT1.GetMean();						//сигнал с ДУСа
						gl_pT1 = T1 / 4096. * 3.;				//V!
					}*/


          if( gl_avT2.GetCounter()) {
						double T2 = gl_avT2.GetMean();						//термодатчик 2
						gl_pT2 = T2 / 65535. * 200. - 100.;				//V!
					}
          /*
          if( gl_avT2.GetCounter()) {
						//double T2 = gl_avT2.GetMean();						//получаемая средняя амплитуда с альтеры
						//gl_pT2 = T2 * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec;

            double T2 = gl_avT2.GetMean();						  //RULA
						gl_pT2 = T2;
					}
          */
					
          if( gl_avT3.GetCounter()) {
						double T3 = gl_avT3.GetMean();						//термодатчик 3
						gl_pT3 = T3 / 65535. * 200. - 100.;				//V!
					}

					/*double i1 = gl_avI1.GetMean();						//разрядный ток i1
					double i2 = gl_avI2.GetMean();						//разрядный ток i2
					double Vpc = gl_avVpc.GetMean();					//напряжение на пьезокорректорах
					double AmplAng = gl_avAmplAng.GetMean();	//amplang
					double T1 = gl_avT1.GetMean();						//термодатчик 1
					double T2 = gl_avT2.GetMean();						//термодатчик 2*/

					double Tsa = gl_avTsa.GetSumm();					//сумма времен Tsa (должно близится к 100мсек)
					double TsaMean = gl_avTsa.GetMean();			//среднее время Tsa за эти 100мсек

					//////////////////////////////////////////////////////////////////////
					//пересчет в физические величины
					//////////////////////////////////////////////////////////////////////
					gl_pTsa = Tsa / 32768.;														// sec
					gl_pw100 = Nimp * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec / gl_pTsa / 4.;				// ''/sec
					
					


					/*  <<--- единственный


					gl_pi1 = i1 / 4096. * 3. / 3.973;									// mA
					gl_pi2 = i2 / 4096. * 3. / 3.973;									// mA
					gl_pVpc = ( ( Vpc / 4096. * 3.) - 2.048) * 100.;	// V
					//gl_pAA = AmplAng / 4096. * 3. / 0.5;							// V
					gl_pAA = AmplAng / 4. * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec;	
					
					gl_pT1 = 70.24586 * ( T1 / 4096. * 3.) - 128.209;	// (T1 / 4096. * 3.) = V!!!!! далее в градусах
					gl_pT2 = 70.24586 * ( T2 / 4096. * 3.) - 128.209;	// V!!!!!
					/*gl_pT1 = ( T1 / 4096. * 3.);
					gl_pT2 = ( T2 / 4096. * 3.);*/                       //  <<--- одна закрывающая на обе!
					
					//gl_pT2 = T2;


					



					gl_pTSamean = TsaMean / 32768.;										// sec
	
					//глобальное время от запуска
					gl_dGlobalTime += gl_pTsa;
					double tmoment = gl_dGlobalTime;

					//разделитель 100мсек точек в статистике
					/*if( (( CSlg2App *) AfxGetApp())->fh != NULL)
						fprintf( (( CSlg2App *) AfxGetApp())->fh, _T("\n"));
					else
						AfxMessageBox( _T("Попытка записи в файл разделителя с закрытым дескриптором!"));*/

					//////////////////////////////////////////////////////////////////////
					//распихивание точек по кольцевым буферам
					//////////////////////////////////////////////////////////////////////
					(( CSlg2App *) AfxGetApp())->m_cbW100->AddPoint( gl_pw100, tmoment);
					(( CSlg2App *) AfxGetApp())->m_cbI1->AddPoint( gl_pi1, tmoment);
					(( CSlg2App *) AfxGetApp())->m_cbI2->AddPoint( gl_pi2, tmoment);
					(( CSlg2App *) AfxGetApp())->m_cbVpc->AddPoint( gl_pVpc, tmoment);
					(( CSlg2App *) AfxGetApp())->m_cbAmplAng->AddPoint( gl_pAA, tmoment);
					(( CSlg2App *) AfxGetApp())->m_cbT1->AddPoint( gl_pT1, tmoment);
					(( CSlg2App *) AfxGetApp())->m_cbT2->AddPoint( gl_pT2, tmoment);
          (( CSlg2App *) AfxGetApp())->m_cbT3->AddPoint( gl_pT3, tmoment);
					(( CSlg2App *) AfxGetApp())->m_cbTsa->AddPoint( gl_pTSamean, tmoment);
				}
				else {
          //ПРОПУСК ПЕРВЫХ 100 msec
					gl_avW100.Reset();
					gl_avW1000.Reset();
					gl_avW10000.Reset();
					gl_avW100000.Reset();
					gl_avI1.Reset();
					gl_avI2.Reset();
					gl_avVpc.Reset();
					gl_avAmplAng.Reset();
					gl_avT1.Reset();
					gl_avT2.Reset();
					gl_avTsa.Reset();
					gl_avTsa1000.Reset();
					gl_avTsa10000.Reset();
					gl_avTsa100000.Reset();

					//разделитель 100мсек точек в статистике
					//fprintf( (( CSlg2App *) AfxGetApp())->fh, _T("\n"));
					bFirst100msecPointSkipped = true;
				}
			}

      // **************************************************
      // ОСРЕДНЕНИЕ 1 сек
      // **************************************************
			if( gl_avTsa1000.GetSumm() > 32768.) {
				//накопили секундную точку
				double Nimp = gl_avW1000.GetSumm();						//количество импульсов (суммированное)
				gl_avW1000.Reset();
				double Tsa = gl_avTsa1000.GetSumm();					//сумма времен Tsa (должно близится к 1 сек)
				gl_avTsa1000.Reset();

				//пересчет в физические величины
				double tsa_1s = Tsa / 32768.;
				double w_1s = Nimp * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec / tsa_1s / 4.;

				//перекладывание в кольцевой буфер
				(( CSlg2App *) AfxGetApp())->m_cbW1000->AddPoint( w_1s, gl_dGlobalTime);				
			}

      // **************************************************
      // ОСРЕДНЕНИЕ 10 сек
      // **************************************************
			if( gl_avTsa10000.GetSumm() > 327680.) {
				//накопили 10секундную точку

				double Nimp = gl_avW10000.GetSumm();						//количество импульсов (суммированное)
				gl_avW10000.Reset();
				double Tsa = gl_avTsa10000.GetSumm();					//сумма времен Tsa (должно близится к 1 сек)
				gl_avTsa10000.Reset();

				//пересчет в физические величины
				double tsa_10s = Tsa / 32768.;
				double w_10s = Nimp * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec / tsa_10s / 4.;

				(( CSlg2App *) AfxGetApp())->m_cbW10000->AddPoint( w_10s, gl_dGlobalTime);
				//(( CSlg2App *) AfxGetApp())->m_cbW10000->AddPoint( gl_avW10000.GetMean(), gl_dGlobalTime);
			}

      // **************************************************
      // ОСРЕДНЕНИЕ 100 сек
      // **************************************************
			if( gl_avTsa100000.GetSumm() > 3276800.) {
				//накопили 100секундную точку
				
				double Nimp = gl_avW100000.GetSumm();						//количество импульсов (суммированное)
				gl_avW100000.Reset();
				double Tsa = gl_avTsa100000.GetSumm();					//сумма времен Tsa (должно близится к 1 сек)
				gl_avTsa100000.Reset();

				//пересчет в физические величины
				double tsa_100s = Tsa / 32768.;
				double w_100s = Nimp * ( ( CSlg2App *) AfxGetApp())->m_dKimpSec / tsa_100s / 4.;

				(( CSlg2App *) AfxGetApp())->m_cbW100000->AddPoint( w_100s, gl_dGlobalTime);
				//(( CSlg2App *) AfxGetApp())->m_cbW100000->AddPoint( gl_avW100000.GetMean(), gl_dGlobalTime);
				
			}	//обработка 100сек точек

		} //если растояние кольцевого буфера > 50		
		else
			Sleep( 1);
	} //while жизни потока

	return 1;
}

/////////////////////////////////////////////////////////////////////////////
// CSlg2App

BEGIN_MESSAGE_MAP(CSlg2App, CWinApp)
	//{{AFX_MSG_MAP(CSlg2App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlg2App construction

CSlg2App::CSlg2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_nEmergencyCode = 0;
	fh = NULL;
	fhNew = NULL;
	m_shSignCoeff = 0;
	//m_bThermoCalibrated = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSlg2App object

CSlg2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CSlg2App initialization

BOOL CSlg2App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Alcor Laboratories"));
	
	int kimpsec = GetProfileInt( _T("SETTINGS"), _T("K_IMP_SEC"), 1000);
	m_nComPort = GetProfileInt( _T("SETTINGS"), _T("COM_PORT"), 0);
	m_nComBaudrate = GetProfileInt( _T("SETTINGS"), _T("COM_BAUDRATE"), 0);
	m_nControlButtons = GetProfileInt( _T("SETTINGS"), _T("CONTROL_BUTTONS"), 0);
	
	m_dKimpSec = kimpsec / 1000.;

	SYSTEMTIME sysTime;
	GetSystemTime( &sysTime);
	COleDateTime time5(sysTime);
	strDirName = time5.Format( _T("%Y-%m-%d"));
	if( !::CreateDirectory( strDirName, NULL)) {
		long lErrorCode = GetLastError();
		if( lErrorCode != 183)
			strDirName = _T( ".\\");
		else
			strDirName += _T("\\");
	}
	else
		strDirName += _T("\\");

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	//ОЧИСТКА КОЛЬЦЕВОГО БУФФЕРА ПРИЕМА ДАННЫХ
	for( int i=0; i<CYCLE_BUFFER_LEN; i++) {
		gl_bCircleBuffer[ i]= 0;
	}

	//кольцевые буфера
	int n = 1024;
	m_cbW100 = new CSlgCircleBuffer( n);
	m_cbW1000  = new CSlgCircleBuffer( n);
	m_cbW10000 = new CSlgCircleBuffer( n);
	m_cbW100000 = new CSlgCircleBuffer( n);
	m_cbI1 = new CSlgCircleBuffer( n);
	m_cbI2 = new CSlgCircleBuffer( n);
	m_cbVpc = new CSlgCircleBuffer( n);
	m_cbAmplAng = new CSlgCircleBuffer( n);
	m_cbT1 = new CSlgCircleBuffer( n);
	m_cbT2 = new CSlgCircleBuffer( n);
  m_cbT3 = new CSlgCircleBuffer( n);
	m_cbTsa = new CSlgCircleBuffer( n);

	gl_dGlobalTime = 0.;

	/*
	DWORD id1;
	HANDLE hthread1 = ::CreateThread(0, 0, &BeeperThread, 0, 0, &id1);

	//ЗАПУСК ПОТОКА ДЛЯ ОБРАБОТКИ ДАННЫХ
	DWORD id2;
	HANDLE hthread2 = ::CreateThread(0, 0, &BigThread, 0, 0, &id2);
	*/

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	/*fh = NULL;
	CPropertySheet dlgWizard( _T("Новый запуск"), NULL, 0);
	
	CWizardSelComPortStep dlgPage1;
	CWizardSelRunTypeStep dlgPage2;
	
	dlgWizard.AddPage( &dlgPage1);
	dlgWizard.AddPage( &dlgPage2);

	dlgWizard.SetWizardMode();
	
	
	if( dlgWizard.DoModal() == ID_WIZFINISH) {

	}
	else
		return FALSE;*/

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSlg2Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		//RUNTIME_CLASS(CSlg2View));
		RUNTIME_CLASS(CMainView));
	
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	/*SYSTEMTIME sysTime;  // Win32 time information
	GetLocalTime(&sysTime);
	CString strStatFileName;
	strStatFileName.Format( _T("data-%d-%02d-%02d-%02d-%02d-%02d.txt"),
													sysTime.wYear, sysTime.wMonth, sysTime.wDay,
													sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	fh = fopen( strStatFileName, "w");*/
	fh = NULL;
	fhNew = NULL;
	fhb = NULL;
	
	//m_strSoftwareVer = _T("v0.0.0.0");
	m_strSoftwareVer = _T("unknown");

	return TRUE;
}


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
		// No message handlers
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

// App command to run the dialog
void CSlg2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSlg2App message handlers




int CSlg2App::ExitInstance() 
{
	m_bStopBigThreadFlag = true;
	
	int kimpsec = m_dKimpSec * 1000;
	WriteProfileInt( _T("SETTINGS"), _T("K_IMP_SEC"), kimpsec);
	WriteProfileInt( _T("SETTINGS"), _T("COM_PORT"), m_nComPort);
	WriteProfileInt( _T("SETTINGS"), _T("COM_BAUDRATE"), m_nComBaudrate);
	

	if( fh != NULL)
		fclose( fh);
	if( fhb != NULL)
		fclose( fhb);
	if( fhNew != NULL)
		fclose( fhNew);

	//кольцевые буфера
	m_cbW100->free();
	m_cbW1000->free();
	m_cbW10000->free();
	m_cbW100000->free();
	m_cbI1->free();
	m_cbI2->free();
	m_cbVpc->free();
	m_cbAmplAng->free();
	m_cbT1->free();
	m_cbT2->free();
  m_cbT3->free();
	m_cbTsa->free();

	delete m_cbW100;
	delete m_cbW1000;
	delete m_cbW10000;
	delete m_cbW100000;
	delete m_cbI1;
	delete m_cbI2;
	delete m_cbVpc;
	delete m_cbAmplAng;
	delete m_cbT1;
	delete m_cbT2;
  delete m_cbT3;
	delete m_cbTsa;

	return CWinApp::ExitInstance();
}

void CSlg2App::StartThreads()
{
	gl_nCircleBufferGet = 0;
	gl_nCircleBufferPut = 0;

	m_bStopBigThreadFlag = false;

	//ЗАПУСК ПОТОКА ДЛЯ ОБРАБОТКИ ДАННЫХ
	DWORD id2;
	HANDLE hthread2 = ::CreateThread( 0, 0, &BigThread, 0, 0, &id2);
}
