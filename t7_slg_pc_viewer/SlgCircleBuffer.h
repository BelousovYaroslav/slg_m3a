// SlgCircleBuffer.h: interface for the CSlgCircleBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLGCIRCLEBUFFER_H__DD593249_1B19_4AD6_A4F5_37EE0E3558D9__INCLUDED_)
#define AFX_SLGCIRCLEBUFFER_H__DD593249_1B19_4AD6_A4F5_37EE0E3558D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyPoint.h"

class CSlgCircleBuffer  
{
public:
	CSlgCircleBuffer( int);
	virtual ~CSlgCircleBuffer();

	int GetFirstIndex( void) { return ( m_bOverRound ? m_nPosition : 0);}
	int GetLastIndex( void) { return ( ( m_nPosition + m_nSize - 1) % m_nSize);}
	void AddPoint( double val, double time);
	int GetSize( void) { return m_nSize;}
	int GetActualSize( void) { return ( m_bOverRound ? m_nSize : m_nPosition);}
	double *GetDataX( void) { while( m_bBlockReading); return datax;}
	double *GetDataY( void) { while( m_bBlockReading); return datay;}
	void BlockReadingOn( void) { m_bBlockReading = true;}
	void BlockReadingOff( void) { m_bBlockReading = false;}
	void BlockWritingOn( void) { m_bBlockWriting = true;}
	void BlockWritingOff( void) { m_bBlockWriting = false;}
	double GetMin() { return m_dMin;}
	double GetMean() { return m_dMean;}
	double GetMax() { return m_dMax;}
	double GetRMS() { return m_dRms;}
	void RecalculateStatistic( void);
	void free( void);
	void Reset( void);

private:
	int m_nSize;
	int m_nPosition;
	double *datax;
	double *datay;
	bool m_bOverRound;
	bool m_bBlockReading;
	bool m_bBlockWriting;
	double m_dMin;
	double m_dMean;
	double m_dMax;
	double m_dRms;
};

#endif // !defined(AFX_SLGCIRCLEBUFFER_H__DD593249_1B19_4AD6_A4F5_37EE0E3558D9__INCLUDED_)
