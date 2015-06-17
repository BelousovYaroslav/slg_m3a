//{{AFX_INCLUDES()
#include "NiGraph.h"
//}}AFX_INCLUDES

#include "Slg2Doc.h"

#if !defined(AFX_DLGHISTO_H__2CCD8C5C_0892_4ECD_B2B9_649436FF5AE6__INCLUDED_)
#define AFX_DLGHISTO_H__2CCD8C5C_0892_4ECD_B2B9_649436FF5AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHisto.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHisto dialog

class CDlgHisto : public CDialog
{
// Construction
public:
	CSlg2Doc *m_doc;
	void DrawHisto( void);
	CDlgHisto(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHisto)
	enum { IDD = IDD_DLG_HISTO };
	CNiGraph	m_ctlHisto100m;
	UINT	m_nBins;
	CNiGraph	m_ctlHisto1s;
	CNiGraph	m_ctlHisto10s;
	CNiGraph	m_ctlHisto100s;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHisto)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHisto)
	afx_msg void OnKillfocusEdtNBins();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHISTO_H__2CCD8C5C_0892_4ECD_B2B9_649436FF5AE6__INCLUDED_)
