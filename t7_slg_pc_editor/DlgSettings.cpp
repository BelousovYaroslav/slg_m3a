// DlgSettings.cpp : implementation file
//

#include "stdafx.h"
#include "t7_slg_pc_editor.h"
#include "DlgSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettings dialog


CDlgSettings::CDlgSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettings)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettings)
	DDX_Control(pDX, IDC_MSCOMM, m_ctlCOM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettings, CDialog)
	//{{AFX_MSG_MAP(CDlgSettings)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettings message handlers
