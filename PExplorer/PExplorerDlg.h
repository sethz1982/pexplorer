// PExplorerDlg.h : header file
//

#if !defined(AFX_PEXPLORERDLG_H__9C14B6F5_089B_464C_AB08_FA525074520C__INCLUDED_)
#define AFX_PEXPLORERDLG_H__9C14B6F5_089B_464C_AB08_FA525074520C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

#include "MyPEFile.h"
#include "MyListCtrl.h"
#include "MyTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CPExplorerDlg dialog
struct tagDirectory
{
  CString strVirtualAddress;
  CString Size;
};

class CPExplorerDlg : public CDialog
{
  enum SELECTLIST
  {
    MAINFILE, DOSHEADER, NTHEADER, 
    FILEHEADER, OPTIONALHEADER, DATADIR, 
    SECTIONHEADER, IMPORT_DIRECTORY
  };
// Construction
public:
	void OnImportListPopMenu(CPoint pt);
	void ShowImportDitectory();
	void ShowSectionHeader();
	void FormatszDataDirectory(tagDirectory*);
	void ShowDataDirectory(IMAGE_DATA_DIRECTORY*);
	void ShowOptionalHeader(IMAGE_OPTIONAL_HEADER OptionalHeader);
	void ShowFileHeader(IMAGE_FILE_HEADER FileHeader);
	void ShowPESignature(DWORD Signature);
	CString GetPEFilePath(HTREEITEM hItem);
	void ShowDosHeader(IMAGE_DOS_HEADER DosHeader);
	void InitTree();
	
	CPExplorerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPExplorerDlg)
	enum { IDD = IDD_PEXPLORER_DIALOG };
	CMyTreeCtrl	m_HeaderTree;
	CMyListCtrl	m_HeaderInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPExplorerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPExplorerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnFileOpen();
	afx_msg void OnClickTreeHeader(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreeHeader(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSectionAdd();
	afx_msg void OnSectionLoadfile();
	afx_msg void OnRclickListInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnImportShowall();
	afx_msg void OnSectionAddressconvert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
  void Open();
private:
  CString   m_strFilePath;
  CMyPEFile m_lpPeFile;
 // CStringArray
  CMap<CString, LPCTSTR, CString, LPCTSTR> m_PathMap;
  DWORD m_dwCurSelListCtrl;
  DWORD m_dwCurSelModuleName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEXPLORERDLG_H__9C14B6F5_089B_464C_AB08_FA525074520C__INCLUDED_)


