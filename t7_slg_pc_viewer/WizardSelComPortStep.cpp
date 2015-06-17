// WizardSelComPortStep.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "WizardSelComPortStep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardSelComPortStep property page

IMPLEMENT_DYNCREATE(CWizardSelComPortStep, CPropertyPage)

CWizardSelComPortStep::CWizardSelComPortStep() : CPropertyPage(CWizardSelComPortStep::IDD)
{
	//{{AFX_DATA_INIT(CWizardSelComPortStep)
	m_nCOMPort = 0;
	//}}AFX_DATA_INIT
}

CWizardSelComPortStep::~CWizardSelComPortStep()
{
}

void CWizardSelComPortStep::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardSelComPortStep)
	DDX_CBIndex(pDX, IDC_CMB_COM, m_nCOMPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardSelComPortStep, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardSelComPortStep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardSelComPortStep message handlers

BOOL CWizardSelComPortStep::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
