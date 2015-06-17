// OpenMeasDlg.cpp : implementation file
//

#include "stdafx.h"
#include "slg2.h"
#include "OpenMeasDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenMeasDlg dialog


COpenMeasDlg::COpenMeasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenMeasDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenMeasDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COpenMeasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenMeasDlg)
	DDX_Control(pDX, IDC_PRGR2, m_ctlProgress2);
	DDX_Control(pDX, IDC_PRGR, m_ctlProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenMeasDlg, CDialog)
	//{{AFX_MSG_MAP(COpenMeasDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenMeasDlg message handlers
