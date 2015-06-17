// SlgNewAverager.h: interface for the CSlgNewAverager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLGNEWAVERAGER_H__5C2B3645_1173_4EEA_A771_45ED35528312__INCLUDED_)
#define AFX_SLGNEWAVERAGER_H__5C2B3645_1173_4EEA_A771_45ED35528312__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSlgNewAverager  
{
public:
	CSlgNewAverager();
	virtual ~CSlgNewAverager();
	void Reset( void);
	void AddPoint( double v);
	double GetMean( void);
	double GetSumm( void) { return m_dSumm;}
	int GetCounter( void) { return m_nCounter;}
private:
	double m_dSumm, m_dMean;
	unsigned int m_nCounter;
};

#endif // !defined(AFX_SLGNEWAVERAGER_H__5C2B3645_1173_4EEA_A771_45ED35528312__INCLUDED_)
