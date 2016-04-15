// MyTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl

CMyTreeCtrl::CMyTreeCtrl()
{

}

CMyTreeCtrl::~CMyTreeCtrl()
{

}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl message handlers

HTREEITEM CMyTreeCtrl::SetRootItem(CString strRootItem)
{
  return InsertItem(strRootItem, TVI_ROOT);
}

void CMyTreeCtrl::ExpandTree(HTREEITEM hItem)
{
  Expand(hItem, TVE_EXPAND);
  HTREEITEM hChindItem = GetChildItem(hItem);
  while (hChindItem)
  {
    ExpandTree(hChindItem);
    hChindItem = GetChildItem(hChindItem);
  }
  HTREEITEM hNextItem = GetNextItem(hItem, TVGN_NEXT);
  while (hNextItem)
  {
    ExpandTree(hNextItem);
    hNextItem = GetNextItem(hNextItem, TVGN_NEXT);
  }
}

