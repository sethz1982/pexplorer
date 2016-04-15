#if !defined(AFX_SHOWIATDLG_H__DB38FE36_9D63_4348_BABC_0B234125D485__INCLUDED_)
#define AFX_SHOWIATDLG_H__DB38FE36_9D63_4348_BABC_0B234125D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowIATDlg.h : header file
//
#include "MyListCtrl.h"
#include "MyPEFile.h"
/////////////////////////////////////////////////////////////////////////////
// CShowIATDlg dialog

class CShowIATDlg : public CDialog
{
// Construction
public:
	CShowIATDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowIATDlg)
	enum { IDD = IDD_DLG_SHOWIAT };
	CMyListCtrl	m_IATList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowIATDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowIATDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void ShowAllIAT();
  CString   m_strFilePath;
  CMyPEFile m_lpPeFile;
  DWORD     m_dwCurSelModuleName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWIATDLG_H__DB38FE36_9D63_4348_BABC_0B234125D485__INCLUDED_)
