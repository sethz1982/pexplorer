#if !defined(AFX_ADDSECTIONDLG_H__357FA59D_DA8B_4359_8BC5_6CA851637F4C__INCLUDED_)
#define AFX_ADDSECTIONDLG_H__357FA59D_DA8B_4359_8BC5_6CA851637F4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddSectionDlg.h : header file
//
#include "MyPEFile.h"
/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg dialog

class CAddSectionDlg : public CDialog
{
// Construction
public:
	CAddSectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddSectionDlg)
	enum { IDD = IDD_DLG_ADDSECTION };
	CString	m_strSectionName;
	UINT	m_uSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddSectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddSectionDlg)
	afx_msg void OnBtnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	DWORD CheckFileAlignment(DWORD dwSize);
	DWORD CheckSectionAlignment(DWORD dwSize);
	void AddSection();
	void GetSectionInfo();
  CString   m_strFilePath;
  CMyPEFile m_lpPeFile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSECTIONDLG_H__357FA59D_DA8B_4359_8BC5_6CA851637F4C__INCLUDED_)
