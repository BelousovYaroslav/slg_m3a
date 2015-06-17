#if !defined(AFX_OPENMEASDLG_H__084F0A36_491F_4EBF_8D6E_BA988A36552F__INCLUDED_)
#define AFX_OPENMEASDLG_H__084F0A36_491F_4EBF_8D6E_BA988A36552F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenMeasDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenMeasDlg dialog

class COpenMeasDlg : public CDialog
{
// Construction
public:
	COpenMeasDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenMeasDlg)
	enum { IDD = IDD_OPEN_MEAS_DLG };
	CProgressCtrl	m_ctlProgress2;
	CProgressCtrl	m_ctlProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenMeasDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenMeasDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENMEASDLG_H__084F0A36_491F_4EBF_8D6E_BA988A36552F__INCLUDED_)
