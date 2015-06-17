// t7_slg_pc_editor.h : main header file for the T7_SLG_PC_EDITOR application
//

#if !defined(AFX_T7_SLG_PC_EDITOR_H__5E3E71EB_A0C4_45F4_9ADC_F8EA94004BDA__INCLUDED_)
#define AFX_T7_SLG_PC_EDITOR_H__5E3E71EB_A0C4_45F4_9ADC_F8EA94004BDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Logger.h"
#include "Settings.h"

/////////////////////////////////////////////////////////////////////////////
// CT7_slg_pc_editorApp:
// See t7_slg_pc_editor.cpp for the implementation of this class
//

class CT7_slg_pc_editorApp : public CWinApp
{
public:
	CT7_slg_pc_editorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT7_slg_pc_editorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CT7_slg_pc_editorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int  GetComPort( void) { return m_nComPort;}
	void SetComPort( int newVal) { m_nComPort = newVal;}
	int  GetComBaudrate( void) { return m_nComBaudrate;}
	void SetComBaudrate( int newVal) { m_nComBaudrate = newVal;}
  void SetLastIncomingData( void);
  COleDateTime GetLastIncomingData( void) { return m_dtmLastIncomingDataTime;}
  CSettings *GetSettings( void) { return &m_pSettings;}
  CLogger * GetLogger() { return &m_pLogger;}
private:
	int m_nComPort;
	int m_nComBaudrate;
  COleDateTime m_dtmLastIncomingDataTime;
  CLogger m_pLogger;

public:
	int m_nEmergencyCode;
  double m_dblScaleCoeff;
  double m_dblAmpl;
  int m_nHangerTact;
  double m_dblMcoeff;
  int m_nStartMode;
  double m_dblControlI1min;
  double m_dblControlI2min;
  int m_nSignCoeff;
  double m_dblAmplAnglmin;
  int m_nMajorVersion, m_nMiddleVersion, m_nMinorVersion;
  int m_nPhaseShift;
  double m_dblDecCoeff;
  CString m_strOrganization;
  COleDateTime m_dtmDate;
  CSettings m_pSettings;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T7_SLG_PC_EDITOR_H__5E3E71EB_A0C4_45F4_9ADC_F8EA94004BDA__INCLUDED_)
