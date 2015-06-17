// Settings.cpp: implementation of the CSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "t7_slg_pc_editor.h"
#include "Settings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CT7_slg_pc_editorApp theApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettings::CSettings()
{
}

CSettings::~CSettings()
{
}

void CSettings::LoadSettings()
{
  m_nComPort = theApp.GetProfileInt( _T("Settings"), _T("COM_PORT"), 1);
  m_nComBaudrate = theApp.GetProfileInt( _T("Settings"), _T("COM_BAUDRATE"), 1);
  m_nLogLevel = theApp.GetProfileInt( _T("Settings"), _T("LOG_LEVEL"), 6);
  int nScaleCoeff = theApp.GetProfileInt( _T("Settings"), _T("SCALE_COEFF"), 2900);
  m_dblScaleCoeff = nScaleCoeff / 1000.;
}

void CSettings::SaveSettings()
{
  theApp.WriteProfileInt( _T("Settings"), _T("COM_PORT"), m_nComPort);
  theApp.WriteProfileInt( _T("Settings"), _T("COM_BAUDRATE"), m_nComBaudrate);
  theApp.WriteProfileInt( _T("Settings"), _T("LOG_LEVEL"), m_nLogLevel);
  theApp.WriteProfileInt( _T("Settings"), _T("SCALE_COEFF"), ( int) ( m_dblScaleCoeff * 1000.));
}

BOOL CSettings::EditSettings()
{
  /*CDlgComPortSettings dlg;

  dlg.m_nComPort = m_nComPort - 1;
  dlg.m_nLogLevel = m_nLogLevel;
  dlg.m_strDataDir = m_strDataDir;

  if( dlg.DoModal() == IDOK) {
    m_nComPort = dlg.m_nComPort + 1;
    m_nLogLevel = dlg.m_nLogLevel;
    m_strDataDir = dlg.m_strDataDir;

    SaveSettings();
    return TRUE;
  }*/

  return FALSE;
}
