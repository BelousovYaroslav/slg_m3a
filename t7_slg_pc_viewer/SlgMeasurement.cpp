// SlgMeasurement.cpp: implementation of the CSlgMeasurement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slg2.h"
#include "SlgMeasurement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSlgMeasurement::CSlgMeasurement()
{
	ang_measurement = -1.;
	discharge_current1 = -1.;
	discharge_current2 = -1.;
	perimeter_voltage = -1.;
	frequency_pedestal_amplitude = -1.;
	thermo_sensor1_voltage = -1.;
	thermo_sensor2_voltage = -1.;
	thermo_sensor3_voltage = -1.;
}

CSlgMeasurement::~CSlgMeasurement()
{
}