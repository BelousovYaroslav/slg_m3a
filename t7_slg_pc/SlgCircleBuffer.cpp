// SlgCircleBuffer.cpp: implementation of the CSlgCircleBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slg2.h"
#include "SlgCircleBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSlgCircleBuffer::CSlgCircleBuffer(int size)
{
	m_nSize = size;
	m_nPosition = 0;
	m_bOverRound = false;
	datax = new double[ size];
	datay = new double[ size];
	for( int i=0; i<size; i++) {
		datax[i] = datay[i] = 0.;
	}
	m_bBlockReading = false;
	m_dMin = 0.;
	m_dMean = 0.;
	m_dMax = 0.;
	m_dRms = 0.;
}

CSlgCircleBuffer::~CSlgCircleBuffer()
{
	if( datax != NULL) {
		delete datax;
		datax = NULL;
	}
	if( datay != NULL) {
		delete datay;
		datay = NULL;
	}
}

void CSlgCircleBuffer::AddPoint(double val, double time)
{
	//while( m_bBlockWriting);
	//m_bBlockReading = true;

	if( ( m_bOverRound == false) && ( m_nPosition == 0)) {
		m_dMin = val;
		m_dMax = val;
	}

	if( val < m_dMin) m_dMin = val;
	if( val > m_dMax) m_dMax = val;

	datax[ m_nPosition] = time;
	datay[ m_nPosition] = val;

	m_nPosition = ( m_nPosition + 1) % m_nSize;
	if( !m_nPosition)
		m_bOverRound = true;

	//m_bBlockReading = false;
}

void CSlgCircleBuffer::RecalculateStatistic(void)
{
	//оч. сильно надеюсь что блокировка записи включена
	int i1 = GetFirstIndex();
	int i2 = GetLastIndex();
	
	double summ = 0.;
	//if( i1 == i2) return;

	//среднее
	int index = i1, n = 0;
	while( index != i2) {
		summ += datay[ index];
		index = ( index + 1) % m_nSize;
		n++;
	}
	summ += datay[ index];
	n++;

	if( n)
		m_dMean = summ / ( double) n;
	else
		m_dMean = 0.;

	//rms
	summ = 0.;
	index = i1, n = 0;
	while( index != i2) {
		summ += ( datay[ index] - m_dMean) * ( datay[ index] - m_dMean);
		index = ( index + 1) % m_nSize;
		n++;
	}
	summ += ( datay[ index] - m_dMean) * ( datay[ index] - m_dMean);
	n++;

	m_dRms = sqrt( summ / ( double) n);
}

void CSlgCircleBuffer::free(void)
{
	if( datax != NULL) {
		delete datax;
		datax = NULL;
	}
	if( datay != NULL) {
		delete datay;
		datay = NULL;
	}
}

void CSlgCircleBuffer::Reset(void)
{
	m_nPosition = 0;
	m_bOverRound = false;
	for( int i=0; i<m_nSize; i++) {
		datax[i] = datay[i] = 0.;
	}
	m_bBlockReading = false;
	m_dMin = 0.;
	m_dMean = 0.;
	m_dMax = 0.;
	m_dRms = 0.;
}