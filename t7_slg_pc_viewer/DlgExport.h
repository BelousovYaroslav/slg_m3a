#if !defined(AFX_DLGEXPORT_H__FA671C07_05FF_4D19_BE0F_E176D580FC3A__INCLUDED_)
#define AFX_DLGEXPORT_H__FA671C07_05FF_4D19_BE0F_E176D580FC3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgExport dialog

class CDlgExport : public CDialog
{
// Construction
public:
	int m_nStatFileVersion;
	long m_nDataFileLines;
	CString m_strFileName;
	CDlgExport(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExport)
	enum { IDD = IDD_DLG_EXPORT };
	CProgressCtrl	m_ctlProgressBar;
	BOOL	m_bChkAA;
	BOOL	m_bChkI1;
	BOOL	m_bChkI2;
	BOOL	m_bChkT1;
	BOOL	m_bChkT2;
	BOOL	m_bChkVpp;
	int		m_nTmean;
	CString	m_strOutputFileName;
	BOOL	m_bChkTimeSA;
	BOOL	m_bChkRotAngle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgExport)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnBrowse();
	afx_msg void OnNoMeaning();
	afx_msg void OnRad100m();
	afx_msg void OnRad100s();
	afx_msg void OnRad10s();
	afx_msg void OnRad1s();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXPORT_H__FA671C07_05FF_4D19_BE0F_E176D580FC3A__INCLUDED_)
