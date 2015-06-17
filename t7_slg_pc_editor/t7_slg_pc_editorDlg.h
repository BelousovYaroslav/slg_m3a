// t7_slg_pc_editorDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_T7_SLG_PC_EDITORDLG_H__E235708D_58CA_4E0D_94E7_8E15EE394261__INCLUDED_)
#define AFX_T7_SLG_PC_EDITORDLG_H__E235708D_58CA_4E0D_94E7_8E15EE394261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CT7_slg_pc_editorDlg dialog

class CT7_slg_pc_editorDlg : public CDialog
{
// Construction
public:
	void SendCommandToMc( BYTE b1, BYTE b2, BYTE b3);
	void SetControlsState( BOOL bDeviceConnectionPresent, BOOL bCanConnect);
	CT7_slg_pc_editorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CT7_slg_pc_editorDlg)
	enum { IDD = IDD_T7_SLG_PC_EDITOR_DIALOG };
	int		m_nComPort;
	int		m_nPortSpeed;
	CString	m_strConnectionStatus;
	CMSComm	m_ctlCOM;
	CString	m_strLblEmergency;
	CString	m_strOrganization;
	double	m_dblAmplCodeIn;
	int		m_nTactCodeIn;
	double	m_dblMCoeff;
	int		m_nStartMode;
	double	m_dblMinI1;
	double	m_dblMinI2;
	double	m_dblMinAmplAng;
	double	m_dblDecCoeff;
	int		m_nSignCoeff;
	CString	m_strMcVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT7_slg_pc_editorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CT7_slg_pc_editorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBtnConnect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnDisconnect();
	afx_msg void OnChangeEdtOrganisationOut();
	afx_msg void OnBtnApplyScaleCoeff();
	afx_msg void OnKillfocusEdtSignCoeffOut();
	afx_msg void OnBtnRequestParams();
	afx_msg void OnBtnRequestSernum();
	afx_msg void OnBtnRequestDate();
	afx_msg void OnBtnRequestOrg();
	afx_msg void OnSelchangeCmbCom();
	afx_msg void OnSelchangeCmbPortSpeed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nFirstTimeRequest;
  int m_nCounterOrgRequest;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T7_SLG_PC_EDITORDLG_H__E235708D_58CA_4E0D_94E7_8E15EE394261__INCLUDED_)
