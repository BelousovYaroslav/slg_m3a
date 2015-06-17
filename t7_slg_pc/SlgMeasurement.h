// SlgMeasurement.h: interface for the CSlgMeasurement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLGMEASUREMENT_H__C4458C3A_2E54_4D5F_86EB_FA060093F060__INCLUDED_)
#define AFX_SLGMEASUREMENT_H__C4458C3A_2E54_4D5F_86EB_FA060093F060__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSlgMeasurement  
{
public:
	CSlgMeasurement();
	virtual ~CSlgMeasurement();
	
	//ANGLE INCREMENT
	double GetAngleInc( void) { return ang_measurement;}
	void   SetAngleInc( double val) { ang_measurement = val;}

	//DISCHARGE CURRENT 1
	double GetDiscCur1( void) { return discharge_current1;}
	void   SetDiscCur1( double val) { discharge_current1 = val;}

	//DISCHARGE CURRENT 2
	double GetDiscCur2( void) { return discharge_current2;}
	void   SetDiscCur2( double val) { discharge_current2 = val;}

	//PERIMETER VOLTAGE
	double GetPerimVolt( void) { return perimeter_voltage;}
	void   SetPerimVolt( double val) { perimeter_voltage = val;}

	//FREQUENCY PEDESTAL AMPLITUDE
	double GetFreqPedAmpl( void) { return frequency_pedestal_amplitude;}
	void   SetFreqPedAmpl( double val) { frequency_pedestal_amplitude = val;}

	//THERMO-SENSOR 1 VOLTAGE
	double GetThermoSens1( void) { return thermo_sensor1_voltage;}
	void   SetThermoSens1( double val) { thermo_sensor1_voltage = val;}

	//THERMO-SENSOR 2 VOLTAGE
	double GetThermoSens2( void) { return thermo_sensor2_voltage;}
	void   SetThermoSens2( double val) { thermo_sensor2_voltage = val;}

	//THERMO-SENSOR 3 VOLTAGE
	double GetThermoSens3( void) { return thermo_sensor3_voltage;}
	void   SetThermoSens3( double val) { thermo_sensor3_voltage = val;}

private:
	double ang_measurement;							//ANGLE INCREMENT
	double discharge_current1;						//DISCHARGE CURRENT 1
	double discharge_current2;						//DISCHARGE CURRENT 2
	double perimeter_voltage;						//PERIMETER VOLTAGE
	double frequency_pedestal_amplitude;	//FREQUENCY PEDESTAL AMPLITUDE
	double thermo_sensor1_voltage;				//THERMO-SENSOR 1 VOLTAGE
	double thermo_sensor2_voltage;				//THERMO-SENSOR 2 VOLTAGE
	double thermo_sensor3_voltage;				//THERMO-SENSOR 3 VOLTAGE
};

#endif // !defined(AFX_SLGMEASUREMENT_H__C4458C3A_2E54_4D5F_86EB_FA060093F060__INCLUDED_)
