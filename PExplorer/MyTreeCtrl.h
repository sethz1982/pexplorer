#if !defined(AFX_MYTREECTRL_H__49266BB2_AE9B_4CB7_BAFB_88645B5A364E__INCLUDED_)
#define AFX_MYTREECTRL_H__49266BB2_AE9B_4CB7_BAFB_88645B5A364E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl window

class CMyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMyTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ExpandTree(HTREEITEM hItem);
	HTREEITEM SetRootItem(CString strRootItem);
	virtual ~CMyTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__49266BB2_AE9B_4CB7_BAFB_88645B5A364E__INCLUDED_)