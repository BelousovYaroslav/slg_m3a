// slg2Doc.h : interface of the CSlg2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLG2DOC_H__8D5141A6_251C_48D7_AE95_380A460EC4A4__INCLUDED_)
#define AFX_SLG2DOC_H__8D5141A6_251C_48D7_AE95_380A460EC4A4__INCLUDED_

#include "OpenMeasDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSlg2Doc : public CDocument
{
protected: // create from serialization only
	CSlg2Doc();
	DECLARE_DYNCREATE(CSlg2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlg2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSlg2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSlg2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bZoomed;
	BOOL m_bShowCursors;
	int m_nStatFileVersion;
	void ReadDataFile( CString filename, COpenMeasDlg *dlg);
	CString m_strCurrentFileName;
	void RecalculateStatistics( void);
	//данные
	double *m_dx100m,			*m_dy100m,			m_dn100m;
	double *m_dx1s,				*m_dy1s,				m_dn1s;
	double *m_dx10s,			*m_dy10s,				m_dn10s;
	double *m_dx100s,			*m_dy100s,			m_dn100s;
	double *m_dx_i1,			*m_dy_i1,				m_dn_i1;
	double *m_dx_i2,			*m_dy_i2,				m_dn_i2;
	double *m_dx_vpc,			*m_dy_vpc,			m_dn_vpc;
	double *m_dx_aa,			*m_dy_aa,				m_dn_aa;
	double *m_dx_t1,			*m_dy_t1,				m_dn_t1;
	double *m_dx_t2,			*m_dy_t2,				m_dn_t2;
  double *m_dx_t3,			*m_dy_t3,				m_dn_t3;
	double *m_dx_tsa,			*m_dy_tsa,			m_dn_tsa;

	double m_d_100m_min, m_d_100m_mean, m_d_100m_max, m_d_100m_rms;
	double m_d_1s_min,	 m_d_1s_mean,		m_d_1s_max,		m_d_1s_rms;
	double m_d_10s_min,  m_d_10s_mean,	m_d_10s_max,	m_d_10s_rms;
	double m_d_100s_min, m_d_100s_mean, m_d_100s_max, m_d_100s_rms;
	double m_d_i1_min,	 m_d_i1_mean,		m_d_i1_max,		m_d_i1_rms;
	double m_d_i2_min,	 m_d_i2_mean,		m_d_i2_max,		m_d_i2_rms;
	double m_d_vpc_min,  m_d_vpc_mean,	m_d_vpc_max,	m_d_vpc_rms;
	double m_d_aa_min,	 m_d_aa_mean,		m_d_aa_max,		m_d_aa_rms;
	double m_d_t1_min,	 m_d_t1_mean,		m_d_t1_max,		m_d_t1_rms;
	double m_d_t2_min,   m_d_t2_mean,		m_d_t2_max,		m_d_t2_rms;
  double m_d_t3_min,   m_d_t3_mean,		m_d_t3_max,		m_d_t3_rms;
	double m_d_tsa_min,	 m_d_tsa_mean,	m_d_tsa_max,	m_d_tsa_rms;

	long nDataFileLines;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLG2DOC_H__8D5141A6_251C_48D7_AE95_380A460EC4A4__INCLUDED_)
