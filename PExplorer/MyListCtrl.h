#if !defined(AFX_MYLISTCTRL_H__D4B8C940_DDB6_4367_AD2B_7D590186A64E__INCLUDED_)
#define AFX_MYLISTCTRL_H__D4B8C940_DDB6_4367_AD2B_7D590186A64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//
#include <Tlhelp32.h>
/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();
  void SetParamCount(int nCount);
  void AutoSize();
  int AddItem(UINT nItem, CString csParams, UINT nIndex = 1);
	int SetHead(CString csParams);
// Attributes
private:
  int m_nParam;
// Operations
public:
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitList(CString csParams, int nCount);
	void DeleteAllColumns();
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__D4B8C940_DDB6_4367_AD2B_7D590186A64E__INCLUDED_)
