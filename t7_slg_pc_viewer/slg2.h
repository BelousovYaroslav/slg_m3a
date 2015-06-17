// slg2.h : main header file for the SLG2 application
//

#if !defined(AFX_SLG2_H__5FD609B8_5021_4079_A60E_27769053C9DB__INCLUDED_)
#define AFX_SLG2_H__5FD609B8_5021_4079_A60E_27769053C9DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "Serial.h"

#include "SlgCircleBuffer.h"



/////////////////////////////////////////////////////////////////////////////
// CSlg2App:
// See slg2.cpp for the implementation of this class
//

class CSlg2App : public CWinApp
{
public:
	CString m_strSoftwareVer;
	double m_dKimpSec;
	CSlg2App();
	BYTE m_btParam1;
	BYTE m_btParam2;
	BYTE m_btParam3;
	BYTE m_btParam4;
	unsigned short m_shFlashI1min;
	unsigned short m_shFlashI2min;
	unsigned short m_shFlashAmplAng1min;
	short m_shFlashDecCoeff;
	short m_shFlashSa;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlg2App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSlg2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLG2_H__5FD609B8_5021_4079_A60E_27769053C9DB__INCLUDED_)
