// Logger.h: interface for the CLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGGER_H__5806D675_2997_4962_A110_A3EAE5945EA5__INCLUDED_)
#define AFX_LOGGER_H__5806D675_2997_4962_A110_A3EAE5945EA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogger  
{
public:
	void Init();
	void LogTrace( const char *strMessage, ...);
  void LogDebug( const char *strMessage, ...);
  void LogInfo(  const char *strMessage, ...);
  void LogWarn(  const char *strMessage, ...);
  void LogError( const char *strMessage, ...);
  void LogFatal( const char *strMessage, ...);
  CLogger();
	virtual ~CLogger();

private:
	FILE *m_fh;
};

#endif // !defined(AFX_LOGGER_H__5806D675_2997_4962_A110_A3EAE5945EA5__INCLUDED_)
