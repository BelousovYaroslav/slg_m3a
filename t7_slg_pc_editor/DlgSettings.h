//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGSETTINGS_H__B149734A_0C3F_4A6C_87FE_B01585659D0F__INCLUDED_)
#define AFX_DLGSETTINGS_H__B149734A_0C3F_4A6C_87FE_B01585659D0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettings dialog

class CDlgSettings : public CDialog
{
// Construction
public:
	CDlgSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSettings)
	enum { IDD = IDD_DLG_SETTINGS };
	CMSComm	m_ctlCOM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettings)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGS_H__B149734A_0C3F_4A6C_87FE_B01585659D0F__INCLUDED_)
