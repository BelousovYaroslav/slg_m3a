//{{AFX_INCLUDES()
#include "NiGraph.h"
#include "NiNumEdit.h"
//#include "mscomm1.h"
//}}AFX_INCLUDES
#if !defined(AFX_DECCOEFFCALC_H__020067C5_FCDA_4E68_A23A_930EE2034BDF__INCLUDED_)
#define AFX_DECCOEFFCALC_H__020067C5_FCDA_4E68_A23A_930EE2034BDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DecCoeffCalc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDecCoeffCalc dialog

class CDecCoeffCalc : public CDialog
{
// Construction
public:
	int m_nPointsSkipped;
	CDecCoeffCalc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDecCoeffCalc)
	enum { IDD = IDD_K_DEC_COEFF_CALC };
	CNiGraph	m_ctlGraphDn;
	CNiGraph	m_ctlGraphDu;
	CNiGraph	m_ctlGraphDecCoeff;
	CString	m_strDecCoeff;
	CNiNumEdit	m_ctlNedtLowFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecCoeffCalc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDecCoeffCalc)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnValueChangedCweDuLowEdge(VARIANT FAR* Value, VARIANT FAR* PreviousValue, BOOL OutOfRange);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECCOEFFCALC_H__020067C5_FCDA_4E68_A23A_930EE2034BDF__INCLUDED_)
