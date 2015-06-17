#if !defined(AFX_WIZARDSELCOMPORTSTEP_H__8E42479C_BB49_49C2_8F87_7359C24EB271__INCLUDED_)
#define AFX_WIZARDSELCOMPORTSTEP_H__8E42479C_BB49_49C2_8F87_7359C24EB271__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardSelComPortStep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizardSelComPortStep dialog

class CWizardSelComPortStep : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardSelComPortStep)

// Construction
public:
	CWizardSelComPortStep();
	~CWizardSelComPortStep();

// Dialog Data
	//{{AFX_DATA(CWizardSelComPortStep)
	enum { IDD = IDD_WIZARD_STEP_COM };
	int		m_nCOMPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardSelComPortStep)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardSelComPortStep)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDSELCOMPORTSTEP_H__8E42479C_BB49_49C2_8F87_7359C24EB271__INCLUDED_)
