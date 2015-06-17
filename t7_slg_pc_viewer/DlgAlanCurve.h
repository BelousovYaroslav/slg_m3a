//{{AFX_INCLUDES()
#include "NiGraph.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGALANCURVE_H__51368FBB_47F2_4C21_801C_031E99704868__INCLUDED_)
#define AFX_DLGALANCURVE_H__51368FBB_47F2_4C21_801C_031E99704868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlanCurve.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlanCurve dialog

class CDlgAlanCurve : public CDialog
{
// Construction
public:
	long m_nDataFileLines;
	CString m_strFileName;
	CDlgAlanCurve(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlanCurve)
	enum { IDD = IDD_DLG_ALAN_CURVE };
	CProgressCtrl	m_ctlPrgrss;
	CNiGraph	m_ctlAlanCurve;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlanCurve)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlanCurve)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALANCURVE_H__51368FBB_47F2_4C21_801C_031E99704868__INCLUDED_)
