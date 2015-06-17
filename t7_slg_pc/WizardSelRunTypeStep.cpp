// WizardSelRunTypeStep.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "WizardSelRunTypeStep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardSelRunTypeStep property page

IMPLEMENT_DYNCREATE(CWizardSelRunTypeStep, CPropertyPage)

CWizardSelRunTypeStep::CWizardSelRunTypeStep() : CPropertyPage(CWizardSelRunTypeStep::IDD)
{
	//{{AFX_DATA_INIT(CWizardSelRunTypeStep)
	m_nType = 0;
	//}}AFX_DATA_INIT
}

CWizardSelRunTypeStep::~CWizardSelRunTypeStep()
{
}

void CWizardSelRunTypeStep::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardSelRunTypeStep)
	DDX_Radio(pDX, IDC_TEST_RAD, m_nType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardSelRunTypeStep, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardSelRunTypeStep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardSelRunTypeStep message handlers

BOOL CWizardSelRunTypeStep::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CPropertySheet *) GetParent())->SetWizardButtons( PSWIZB_BACK + PSWIZB_FINISH);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
