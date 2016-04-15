// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyListCtrl.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers
//设置参数个数
void CMyListCtrl::SetParamCount(int nCount)
{
  m_nParam = nCount;
}
//设置ListHead
int CMyListCtrl::SetHead(CString csParams)
{
  DeleteAllColumns();

  CString csParam;
  for (int i = 0; i < m_nParam; i++)
  {
    AfxExtractSubString(csParam, csParams, i, '|');
    if (InsertColumn(i, csParam) == -1)
    {
      return -1;
    }
  }
  return 1;
}
//添加Item
int CMyListCtrl::AddItem(UINT nItem, CString csParams, UINT nIndex)
{
  CString csParam;
  if (AfxExtractSubString(csParam, csParams, 0, '|'))
  {
    if (InsertItem(nItem, csParam, nItem) == -1)
    {
      return -1;
    }
  }
  for (int i = nIndex; i < m_nParam; i++)
  {
    if (AfxExtractSubString(csParam, csParams, i, '|'))
    {
      if (SetItemText(nItem, i, csParam) == 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

//自动设置Head的宽度
void CMyListCtrl::AutoSize()
{
  SetRedraw(FALSE);
  CHeaderCtrl* pHeaderCtrl = GetHeaderCtrl();
  for (int i = 0; i < pHeaderCtrl->GetItemCount(); i++)
  {
    SetColumnWidth(i, LVSCW_AUTOSIZE);
    int nWidth1 = GetColumnWidth(i);
    SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    int nWidth2 = GetColumnWidth(i);
    SetColumnWidth(i, max(nWidth1, nWidth2));

  }
  SetRedraw(TRUE);
}
void CMyListCtrl::DeleteAllColumns()
{
  for (int i = GetHeaderCtrl()->GetItemCount(); i >= 0; i--)
  {
    DeleteColumn(i);
  }
}

void CMyListCtrl::InitList(CString csParams, int nCount)
{
  DeleteAllColumns();
  SetExtendedStyle(GetExtendedStyle()
                    |LVS_EX_GRIDLINES
                    |LVS_EX_FULLROWSELECT
                    |LVS_EX_SUBITEMIMAGES);
  SetParamCount(nCount);
  SetHead(csParams);
  AutoSize();
}

//DEL void CMyListCtrl::OnContextMenu(CWnd*, CPoint point)
//DEL {
//DEL 
//DEL 	// CG: This block was added by the Pop-up Menu component
//DEL 	{
//DEL 		if (point.x == -1 && point.y == -1){
//DEL 			//keystroke invocation
//DEL 			CRect rect;
//DEL 			GetClientRect(rect);
//DEL 			ClientToScreen(rect);
//DEL 
//DEL 			point = rect.TopLeft();
//DEL 			point.Offset(5, 5);
//DEL 		}
//DEL 
//DEL 		CMenu menu;
//DEL 		VERIFY(menu.LoadMenu(CG_IDR_POPUP_MY_LIST_CTRL));
//DEL 
//DEL 		CMenu* pPopup = menu.GetSubMenu(0);
//DEL 		ASSERT(pPopup != NULL);
//DEL 		CWnd* pWndPopupOwner = this;
//DEL 
//DEL 		while (pWndPopupOwner->GetStyle() & WS_CHILD)
//DEL 			pWndPopupOwner = pWndPopupOwner->GetParent();
//DEL 
//DEL 		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
//DEL 			pWndPopupOwner);
//DEL 	}
//DEL }
