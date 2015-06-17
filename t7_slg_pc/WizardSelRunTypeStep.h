#if !defined(AFX_WIZARDSELRUNTYPESTEP_H__6268153E_588A_464C_95FC_52D4DDAAAD93__INCLUDED_)
#define AFX_WIZARDSELRUNTYPESTEP_H__6268153E_588A_464C_95FC_52D4DDAAAD93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardSelRunTypeStep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizardSelRunTypeStep dialog

class CWizardSelRunTypeStep : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardSelRunTypeStep)

// Construction
public:
	CWizardSelRunTypeStep();
	~CWizardSelRunTypeStep();

// Dialog Data
	//{{AFX_DATA(CWizardSelRunTypeStep)
	enum { IDD = IDD_WIZARD_MEAS_TYPE_SEL };
	int		m_nType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardSelRunTypeStep)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardSelRunTypeStep)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDSELRUNTYPESTEP_H__6268153E_588A_464C_95FC_52D4DDAAAD93__INCLUDED_)
