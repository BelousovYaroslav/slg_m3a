// SlgNewAverager.cpp: implementation of the CSlgNewAverager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slg2.h"
#include "SlgNewAverager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSlgNewAverager::CSlgNewAverager()
{
	m_dSumm = m_dMean = 0.;
	m_nCounter = 0;
}

CSlgNewAverager::~CSlgNewAverager()
{

}

void CSlgNewAverager::AddPoint( double v)
{
	m_dSumm += v; m_nCounter++;
}

double CSlgNewAverager::GetMean( void)
{
	if( m_nCounter)
		m_dMean = m_dSumm / ( double) m_nCounter;
	else
		m_dMean = 0.;

	m_dSumm = 0.; m_nCounter = 0;
	return m_dMean;
}

void CSlgNewAverager::Reset( void) {
	m_dSumm = 0.; m_nCounter = 0;
}