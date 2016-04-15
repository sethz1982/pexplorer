#if !defined(AFX_CONVERTDLG_H__670C104B_0227_474A_AB26_EA207F4ED361__INCLUDED_)
#define AFX_CONVERTDLG_H__670C104B_0227_474A_AB26_EA207F4ED361__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConvertDlg.h : header file
//
#include "MyPEFile.h"
/////////////////////////////////////////////////////////////////////////////
// CConvertDlg dialog

class CConvertDlg : public CDialog
{
// Construction
public:
	CConvertDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CConvertDlg)
	enum { IDD = IDD_DLG_CONVERT };
	CButton	m_BtnVA;
	CButton	m_BtnRVA;
	CButton	m_BtnFA;
	CString	m_strFA;
	CString	m_strRVA;
	CString	m_strVA;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvertDlg)
	afx_msg void OnBtnConvert();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckFa();
	afx_msg void OnCheckRva();
	afx_msg void OnCheckVa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int DecToHex(int nDec);
  CString   m_strFilePath;
  CMyPEFile m_lpPeFile;
  int m_nSelect;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERTDLG_H__670C104B_0227_474A_AB26_EA207F4ED361__INCLUDED_)
