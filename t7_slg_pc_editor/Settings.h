// Settings.h: interface for the CSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGS_H__D5FE8E11_FAAD_46A6_919E_09E9BC72FDAA__INCLUDED_)
#define AFX_SETTINGS_H__D5FE8E11_FAAD_46A6_919E_09E9BC72FDAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettings  
{
public:
	BOOL EditSettings( void);
	void SaveSettings();
	void LoadSettings();
	CSettings();
	virtual ~CSettings();

  int GetComPort() { return m_nComPort;}
  void SetComPort( int nNewPort) { m_nComPort = nNewPort;}

  int GetComBaudrate() { return m_nComBaudrate;}
  void SetComBaudrate( int nNewBaudrate) { m_nComBaudrate = nNewBaudrate;}

  BOOL GetLogLevel() { return m_nLogLevel;}
  void SetLogLevel( int nNewVal) { m_nLogLevel = nNewVal;}

  double GetScaleCoeff() { return m_dblScaleCoeff;}
  void SetScaleCoeff( double dblNewVal) { m_dblScaleCoeff = dblNewVal;}

private:
  int m_nComPort;
  int m_nComBaudrate;
  int m_nLogLevel;
  double m_dblScaleCoeff;
};

#endif // !defined(AFX_SETTINGS_H__D5FE8E11_FAAD_46A6_919E_09E9BC72FDAA__INCLUDED_)
