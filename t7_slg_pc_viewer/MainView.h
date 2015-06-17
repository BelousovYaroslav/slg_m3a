//{{AFX_INCLUDES()
#include "NiGraph.h"
#include "NiButton.h"
#include "NiNumEdit.h"
//}}AFX_INCLUDES
#if !defined(AFX_MAINVIEW_H__4133504C_1A2D_4A65_89A5_A033461F952F__INCLUDED_)
#define AFX_MAINVIEW_H__4133504C_1A2D_4A65_89A5_A033461F952F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMainView : public CFormView
{
protected:
	CMainView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMainView)

// Form Data
public:
	//{{AFX_DATA(CMainView)
	enum { IDD = IDD_MAIN_WINDOW };
	CNiGraph	m_ctlSmallGraph1;
	CNiGraph	m_ctlSmallGraph2;
	CNiGraph	m_ctlSmallGraph3;
	CNiGraph	m_ctlSmallGraph4;
	CNiGraph	m_ctlSmallGraph5;
	CNiGraph	m_ctlSmallGraph6;
	CNiGraph	m_ctlSmallGraph7;
	CNiGraph	m_ctlSmallGraph8;
	CNiGraph	m_ctlMainGraph;
	CString	m_strGraphMaxVal;
	CString	m_strGraphMeanVal;
	CString	m_strGraphMinVal;
	CString	m_strGraphRmsVal;
	CString	m_strSmGr1_max;
	CString	m_strSmGr1_mean;
	CString	m_strSmGr1_min;
	CString	m_strSmGr1_rms;
	CString	m_strSmGr2_max;
	CString	m_strSmGr2_mean;
	CString	m_strSmGr2_min;
	CString	m_strSmGr2_rms;
	CString	m_strSmGr3_max;
	CString	m_strSmGr3_mean;
	CString	m_strSmGr3_min;
	CString	m_strSmGr3_rms;
	CString	m_strSmGr4_max;
	CString	m_strSmGr4_mean;
	CString	m_strSmGr4_min;
	CString	m_strSmGr4_rms;
	CString	m_strSmGr5_max;
	CString	m_strSmGr5_mean;
	CString	m_strSmGr5_min;
	CString	m_strSmGr5_rms;
	CString	m_strSmGr6_max;
	CString	m_strSmGr6_mean;
	CString	m_strSmGr6_min;
	CString	m_strSmGr6_rms;
	CString	m_strSmGr7_max;
	CString	m_strSmGr7_mean;
	CString	m_strSmGr7_min;
	CString	m_strSmGr7_rms;
	CString	m_strSmGr8_max;
	CString	m_strSmGr8_mean;
	CString	m_strSmGr8_min;
	CString	m_strSmGr8_rms;
	CString	m_strParam1Val;
	CString	m_strParam2Val;
	CString	m_strParam3Val;
	CString	m_strParam4Val;
	CString	m_strParam5Val;
	CString	m_strParam6Val;
	CString	m_strParam7Val;
	CString	m_strParam8Val;
	CString	m_strParam9Val;
	int		m_nTMeaningInd;
	double	m_dKimpSec;
	CString	m_strSoftwareVersion;
	CString	m_strThisSoftwareVersion;
	CString	m_strLblCursorDxVal;
	CString	m_strLblCursorDyVal;
	CString	m_strCur1X_val;
	CString	m_strCur1Y_val;
	CString	m_strCur2X_val;
	CString	m_strCur2Y_val;
	int		m_nRadT2;
	int		m_nRadT1;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void SetRefreshTimer( int nPeriod = 100);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMainView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClickGraph1();
	afx_msg void OnClickGraph2();
	afx_msg void OnClickGraph3();
	afx_msg void OnClickGraph4();
	afx_msg void OnClickGraph5();
	afx_msg void OnClickGraph6();
	afx_msg void OnClickGraph7();
	afx_msg void OnClickGraph8();
	afx_msg void OnDestroy();
	afx_msg void OnChangeParam2Edt();
	afx_msg void OnChangeParam1Edt();
	afx_msg void OnChangeParam3Edt();
	afx_msg void OnChangeParam4Edt();
	afx_msg void OnKillfocusEdtKImpSec();
	afx_msg void OnHistogram();
	afx_msg void OnAlanCurve();
	afx_msg void OnBtnExport();
	afx_msg void OnRadMeaning100msec();
	afx_msg void OnRadMeaning1sec();
	afx_msg void OnRadMeaning10sec();
	afx_msg void OnRadMeaning100sec();
	afx_msg void OnUpdateZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRestoreZoom(CCmdUI* pCmdUI);
	afx_msg void OnZoomin();
	afx_msg void OnRestoreZoom();
	afx_msg void OnShowCursors();
	afx_msg void OnCursorChangeMainGraph(long FAR* CursorIndex, VARIANT FAR* XPos, VARIANT FAR* YPos, BOOL FAR* bTracking);
	afx_msg void OnRadT1Td1();
	afx_msg void OnRadT1Td2();
	afx_msg void OnRadT1Td3();
	afx_msg void OnRadT2Td1();
	afx_msg void OnRadT2Td2();
	afx_msg void OnRadT2Td3();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HANDLE hMutex;
	bool m_bEmergencyCodeApperance;
	int m_nCounterSkippedPoints;
	bool b1stPointSkipped;
	CFont m_pFont;
	int m_nMainGraph;
	void RefreshGraphs( void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINVIEW_H__4133504C_1A2D_4A65_89A5_A033461F952F__INCLUDED_)
