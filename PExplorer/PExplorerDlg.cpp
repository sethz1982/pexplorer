// PExplorerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PExplorer.h"
#include "PExplorerDlg.h"
#include "AddSectionDlg.h"
#include "ShowIATDlg.h"
#include "ConvertDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();
  
  // Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA
  
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPExplorerDlg dialog

CPExplorerDlg::CPExplorerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPExplorerDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPExplorerDlg)
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPExplorerDlg)
  DDX_Control(pDX, IDC_TREE_HEADER, m_HeaderTree);
  DDX_Control(pDX, IDC_LIST_INFO, m_HeaderInfo);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPExplorerDlg, CDialog)
//{{AFX_MSG_MAP(CPExplorerDlg)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_WM_DROPFILES()
  ON_COMMAND(IDM_FILE_OPEN, OnFileOpen)
  ON_NOTIFY(NM_CLICK, IDC_TREE_HEADER, OnClickTreeHeader)
  ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_HEADER, OnSelchangedTreeHeader)
  ON_NOTIFY(NM_DBLCLK, IDC_LIST_INFO, OnDblclkListInfo)
  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_SECTION_ADD, OnSectionAdd)
  ON_COMMAND(ID_SECTION_LOADFILE, OnSectionLoadfile)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_INFO, OnRclickListInfo)
	ON_COMMAND(IDM_IMPORT_SHOWALL, OnImportShowall)
	ON_COMMAND(ID_SECTION_ADDRESSCONVERT, OnSectionAddressconvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPExplorerDlg message handlers

BOOL CPExplorerDlg::OnInitDialog()
{
  CDialog::OnInitDialog();
  
  // Add "About..." menu item to system menu.
  
  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);
  
  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
  {
    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty())
    {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }
  
  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon
  
  // TODO: Add extra initialization here
  
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPExplorerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  }
  else
  {
    CDialog::OnSysCommand(nID, lParam);
  }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPExplorerDlg::OnPaint() 
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting
    
    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
    
    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;
    
    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPExplorerDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}

void CPExplorerDlg::OnDropFiles(HDROP hDropInfo) 
{
  DragQueryFile(hDropInfo, 0, 
    m_strFilePath.GetBufferSetLength(MAX_PATH), MAX_PATH);
  m_strFilePath.ReleaseBuffer();
  DragFinish(hDropInfo);
  UpdateData(FALSE);
  Open();
  CDialog::OnDropFiles(hDropInfo);
}

void CPExplorerDlg::OnFileOpen() 
{
  TCHAR szFilter[] = "Executable Files (*.exe)|*.exe"
    "|Dynamic-link libraty (*.dll)|*.dll"
    "|All Files (*.*)|*.*||";
  
  CFileDialog Dlg(TRUE, NULL, NULL, 
    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    szFilter, NULL);
  if (Dlg.DoModal() == IDOK)
  {
    m_strFilePath = Dlg.GetPathName();
    Open();
  }
}

void CPExplorerDlg::Open()
{
  if (m_lpPeFile.Open(m_strFilePath))
  {
    CString strFileName = m_lpPeFile.GetFileName();
    CString strFilePath = m_lpPeFile.GetFilePath();
    m_PathMap.SetAt(strFileName, strFilePath);
    InitTree();
    m_lpPeFile.Close();
  }
  
}

void CPExplorerDlg::InitTree()
{
  //root
  HTREEITEM hRootItem = 
    m_HeaderTree.SetRootItem(m_lpPeFile.GetFileName());
  //二层
  HTREEITEM hDosHeaderItem = 
    m_HeaderTree.InsertItem(_T("DOS_HEADER"), hRootItem);
  HTREEITEM hNtHeadersItem = 
    m_HeaderTree.InsertItem(_T("NT_HEADERS"), hRootItem);
  HTREEITEM hSectionHeaderItem = 
    m_HeaderTree.InsertItem(_T("SECTION_HEADER"), hRootItem);
  HTREEITEM hImportTableItem = 
    m_HeaderTree.InsertItem(_T("IMPORT_DIRECTORY"), hRootItem);
  
  //三层
  HTREEITEM hFileHeaderItem = 
    m_HeaderTree.InsertItem(_T("FILE_HEADER"), hNtHeadersItem);
  HTREEITEM hOptionalHeaderItem = 
    m_HeaderTree.InsertItem(_T("OPTIONAL_HEADER"), hNtHeadersItem);
  
  //四层
  HTREEITEM hDataDirectoryItem = 
    m_HeaderTree.InsertItem(_T("DATA_DIRECTORY"), hOptionalHeaderItem);
  
  
  m_HeaderTree.ExpandTree(hRootItem);
}

void CPExplorerDlg::OnClickTreeHeader(NMHDR* pNMHDR, LRESULT* pResult) 
{
  
  *pResult = 0;
}

void CPExplorerDlg::OnSelchangedTreeHeader(NMHDR* pNMHDR, LRESULT* pResult) 
{
  NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  // TODO: Add your control notification handler code here
  HTREEITEM hItem = m_HeaderTree.GetSelectedItem();
  CString strSelect = m_HeaderTree.GetItemText(hItem);
  
  CString strFilePath(_T(""));
  strFilePath = GetPEFilePath(hItem);
  m_lpPeFile.Open(strFilePath);
  m_strFilePath = strFilePath;
  if (strSelect == _T("DOS_HEADER"))
  {
    m_dwCurSelListCtrl = DOSHEADER;
    m_HeaderInfo.DeleteAllItems();
    m_HeaderInfo.InitList(_T("Member|Offset|Size|Value"), 4);
    ShowDosHeader(m_lpPeFile.GetDosHeader());
  }
  else if (strSelect == _T("NT_HEADERS"))
  {
    m_dwCurSelListCtrl = NTHEADER;
    m_HeaderInfo.DeleteAllItems();
    m_HeaderInfo.InitList(_T("Member|Offset|Size|Value"), 4);
    ShowPESignature(m_lpPeFile.GetSignature());
  }
  else if (strSelect == _T("SECTION_HEADER"))
  {
    m_dwCurSelListCtrl = SECTIONHEADER;
    m_HeaderInfo.DeleteAllItems();
    m_HeaderInfo.InitList(_T("Offset|Name|VirtualSize|VirtualAddress|"
      "SizeOfRawData|PointerToRawData|"
      "PointerToRelocations|PointerToLinenumbers|"
      "NumberOfRelocations|NumberOfLinenumbers|"
      "Characteristics"), 11);
    ShowSectionHeader();
  }
  else if (strSelect == _T("IMPORT_DIRECTORY"))
  {
    m_dwCurSelListCtrl = IMPORT_DIRECTORY;
    m_HeaderInfo.DeleteAllItems();
    m_HeaderInfo.InitList(_T("Module Name|OFTs(IAT)|TimeDateStamp"
      "|ForwarderChain|Name RVA|FTs (IAT)"), 6);
    ShowImportDitectory();
  }
  else if (strSelect == _T("FILE_HEADER"))
  {
    m_dwCurSelListCtrl = FILEHEADER;
    m_HeaderInfo.DeleteAllItems();
    m_HeaderInfo.InitList(_T("Member|Offset|Size|Value|Meaning"), 5);
    ShowFileHeader(m_lpPeFile.GetFileHeader());
  }
  else if (strSelect == _T("OPTIONAL_HEADER"))
  {
    m_dwCurSelListCtrl = OPTIONALHEADER;
    m_HeaderInfo.DeleteAllItems();
    m_HeaderInfo.InitList(_T("Member|Offset|Size|Value|Meaning"), 5);
    ShowOptionalHeader(m_lpPeFile.GetOptionalHeader());
  }
  else if (strSelect == _T("DATA_DIRECTORY"))
  {
    m_dwCurSelListCtrl = DATADIR;
    m_HeaderInfo.DeleteAllItems();
    m_HeaderInfo.InitList(_T("Member|Offset|Size|Value|Section"), 5);
    ShowDataDirectory(m_lpPeFile.GetDataDirectory(0));
  }
  m_lpPeFile.Close();
  *pResult = 0;
}
void CPExplorerDlg::OnDblclkListInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
  // TODO: Add your control notification handler code here

  *pResult = 0;
}
void CPExplorerDlg::OnRclickListInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
  UNREFERENCED_PARAMETER(pNMHDR);
  if (m_dwCurSelListCtrl == IMPORT_DIRECTORY)
  {
    int nItem = m_HeaderInfo.GetSelectionMark();
    if (nItem != -1)
    {
      CPoint pt;
      GetCursorPos(&pt);
      OnImportListPopMenu(pt);
      m_dwCurSelModuleName = nItem;
    }
  }
  m_HeaderInfo.SetSelectionMark(-1);
  *pResult = 0;
}

CString CPExplorerDlg::GetPEFilePath(HTREEITEM hItem)
{
  CString strFilePath(_T(""));
  CString strTemp(_T(""));
  strTemp = m_HeaderTree.GetItemText(hItem);
  BOOL bRet = m_PathMap.Lookup(strTemp, strFilePath);
  if (bRet)
  {
    return strFilePath;
  }
  HTREEITEM hParent = m_HeaderTree.GetParentItem(hItem);
  while (hParent)
  {
    strTemp = m_HeaderTree.GetItemText(hParent);
    bRet = m_PathMap.Lookup(strTemp, strFilePath);
    if (bRet)
    {
      return strFilePath;
    }
    hParent = m_HeaderTree.GetParentItem(hParent);
  }
  return "";
}

void CPExplorerDlg::ShowDosHeader(IMAGE_DOS_HEADER DosHeader)
{
  
  int nCount = 0;
  CString strDosHDR(_T(""));
  strDosHDR.Format(_T("e_magic|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_magic)), 
    sizeof(DosHeader.e_magic),
    DosHeader.e_magic);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_cblp|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_cblp)), 
    sizeof(DosHeader.e_cblp),
    DosHeader.e_cblp);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_cp|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_cp)), 
    sizeof(DosHeader.e_cp),
    DosHeader.e_cp);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_crlc|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_crlc)), 
    sizeof(DosHeader.e_crlc),
    DosHeader.e_crlc);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_cparhdr|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_cparhdr)), 
    sizeof(DosHeader.e_cparhdr),
    DosHeader.e_cparhdr);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_minalloc|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_minalloc)), 
    sizeof(DosHeader.e_minalloc),
    DosHeader.e_minalloc);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_maxalloc|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_maxalloc)), 
    sizeof(DosHeader.e_maxalloc),
    DosHeader.e_maxalloc);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_ss|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_ss)), 
    sizeof(DosHeader.e_ss),
    DosHeader.e_ss);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_sp|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_sp)), 
    sizeof(DosHeader.e_sp),
    DosHeader.e_sp);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_csum|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_csum)), 
    sizeof(DosHeader.e_csum),
    DosHeader.e_csum);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_ip|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_ip)), 
    sizeof(DosHeader.e_ip),
    DosHeader.e_ip);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_cs|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_cs)), 
    sizeof(DosHeader.e_cs),
    DosHeader.e_cs);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_lfarlc|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_lfarlc)), 
    sizeof(DosHeader.e_lfarlc),
    DosHeader.e_lfarlc);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_ovno|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_ovno)), 
    sizeof(DosHeader.e_ovno),
    DosHeader.e_ovno);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_cs|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_cs)), 
    sizeof(DosHeader.e_cs),
    DosHeader.e_cs);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  for (int i = 0; i < 4; i++)
  {
    strDosHDR.Format(_T("e_res[%d]|0x%08p|%x|0x%04X"), i,
      ((&((IMAGE_DOS_HEADER*)NULL)->e_res[i])), 
      sizeof(DosHeader.e_res[i]),
      DosHeader.e_res[i]);
    m_HeaderInfo.AddItem(nCount++, strDosHDR);
  }
  
  strDosHDR.Format(_T("e_oemid|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_oemid)), 
    sizeof(DosHeader.e_oemid),
    DosHeader.e_oemid);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  strDosHDR.Format(_T("e_oeminfo|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_oeminfo)), 
    sizeof(DosHeader.e_oeminfo),
    DosHeader.e_oeminfo);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  for (i = 0; i < 10; i++)
  {
    strDosHDR.Format(_T("e_res2[%d]|0x%08p|%x|0x%04X"), i,
      ((&((IMAGE_DOS_HEADER*)NULL)->e_res2[i])), 
      sizeof(DosHeader.e_res2[i]),
      DosHeader.e_res2[i]);
    m_HeaderInfo.AddItem(nCount++, strDosHDR);
  }
  
  strDosHDR.Format(_T("e_lfanew|0x%08p|%x|0x%04X"), 
    ((&((IMAGE_DOS_HEADER*)NULL)->e_lfanew)), 
    sizeof(DosHeader.e_lfanew),
    DosHeader.e_lfanew);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  m_HeaderInfo.AutoSize();
}

void CPExplorerDlg::ShowPESignature(DWORD Signature)
{
  int nCount = 0;
  CString strDosHDR(_T(""));
  strDosHDR.Format(_T("Signature|0x%08p|%x|0x%08X"), 
    m_lpPeFile.Gete_lfanew(), 
    sizeof(Signature),
    Signature);
  
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  m_HeaderInfo.AutoSize();
}


void CPExplorerDlg::ShowFileHeader(IMAGE_FILE_HEADER FileHeader)
{
  LONG lBaseOffset = m_lpPeFile.Gete_lfanew() 
    + sizeof(m_lpPeFile.GetSignature());
  
  int nCount = 0;
  CString strDosHDR(_T(""));
  
  LONG lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_FILE_HEADER*)NULL)->Machine));
  strDosHDR.Format(_T("Machine|0x%08p|%x|0x%04X|i386未完"),  
    lOffset, sizeof(FileHeader.Machine),
    FileHeader.Machine);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_FILE_HEADER*)NULL)->NumberOfSections));
  strDosHDR.Format(_T("NumberOfSections|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(FileHeader.NumberOfSections),
    FileHeader.NumberOfSections);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_FILE_HEADER*)NULL)->TimeDateStamp));
  strDosHDR.Format(_T("TimeDateStamp|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(FileHeader.TimeDateStamp),
    FileHeader.TimeDateStamp);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_FILE_HEADER*)NULL)->PointerToSymbolTable));
  strDosHDR.Format(_T("PointerToSymbolTable|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(FileHeader.PointerToSymbolTable),
    FileHeader.PointerToSymbolTable);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_FILE_HEADER*)NULL)->NumberOfSymbols));
  strDosHDR.Format(_T("NumberOfSymbols|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(FileHeader.NumberOfSymbols),
    FileHeader.NumberOfSymbols);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_FILE_HEADER*)NULL)->SizeOfOptionalHeader));
  strDosHDR.Format(_T("SizeOfOptionalHeader|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(FileHeader.SizeOfOptionalHeader),
    FileHeader.SizeOfOptionalHeader);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_FILE_HEADER*)NULL)->Characteristics));
  strDosHDR.Format(_T("Characteristics|0x%08p|%x|0x%04X|未完"),       
    lOffset, sizeof(FileHeader.Characteristics),
    FileHeader.Characteristics);
  m_HeaderInfo.AddItem(nCount++, strDosHDR);
  
  m_HeaderInfo.AutoSize();
}

void CPExplorerDlg::ShowOptionalHeader(IMAGE_OPTIONAL_HEADER OptionalHeader)
{
  LONG lBaseOffset = m_lpPeFile.Gete_lfanew() 
    + sizeof(m_lpPeFile.GetSignature())
    + sizeof(IMAGE_FILE_HEADER);
  
  int nCount = 0;
  CString strHDR(_T(""));
  
  LONG lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->Magic));
  strHDR.Format(_T("Magic|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.Magic),
    OptionalHeader.Magic);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MajorLinkerVersion));
  strHDR.Format(_T("MajorLinkerVersion|0x%08p|%x|0x%02X"),       
    lOffset, sizeof(OptionalHeader.MajorLinkerVersion),
    OptionalHeader.MajorLinkerVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MinorLinkerVersion));
  strHDR.Format(_T("MinorLinkerVersion|0x%08p|%x|0x%02X"),       
    lOffset, sizeof(OptionalHeader.MinorLinkerVersion),
    OptionalHeader.MinorLinkerVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfCode));
  strHDR.Format(_T("SizeOfCode|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfCode),
    OptionalHeader.SizeOfCode);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfInitializedData));
  strHDR.Format(_T("SizeOfInitializedData|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfInitializedData),
    OptionalHeader.SizeOfInitializedData);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfUninitializedData));
  strHDR.Format(_T("SizeOfUninitializedData|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfUninitializedData),
    OptionalHeader.SizeOfUninitializedData);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->AddressOfEntryPoint));
  strHDR.Format(_T("AddressOfEntryPoint|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.AddressOfEntryPoint),
    OptionalHeader.AddressOfEntryPoint);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->BaseOfCode));
  strHDR.Format(_T("BaseOfCode|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.BaseOfCode),
    OptionalHeader.BaseOfCode);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->BaseOfData));
  strHDR.Format(_T("BaseOfData|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.BaseOfData),
    OptionalHeader.BaseOfData);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->ImageBase));
  strHDR.Format(_T("ImageBase|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.ImageBase),
    OptionalHeader.ImageBase);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SectionAlignment));
  strHDR.Format(_T("SectionAlignment|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SectionAlignment),
    OptionalHeader.SectionAlignment);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->FileAlignment));
  strHDR.Format(_T("FileAlignment|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.FileAlignment),
    OptionalHeader.FileAlignment);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MajorOperatingSystemVersion));
  strHDR.Format(_T("MajorOperatingSystemVersion|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.MajorOperatingSystemVersion),
    OptionalHeader.MajorOperatingSystemVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MinorOperatingSystemVersion));
  strHDR.Format(_T("MinorOperatingSystemVersion|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.MinorOperatingSystemVersion),
    OptionalHeader.MinorOperatingSystemVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MajorImageVersion));
  strHDR.Format(_T("MajorImageVersion|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.MajorImageVersion),
    OptionalHeader.MajorImageVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MinorImageVersion));
  strHDR.Format(_T("MinorImageVersion|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.MinorImageVersion),
    OptionalHeader.MinorImageVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MajorSubsystemVersion));
  strHDR.Format(_T("MajorSubsystemVersion|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.MajorSubsystemVersion),
    OptionalHeader.MajorSubsystemVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->MinorSubsystemVersion));
  strHDR.Format(_T("MinorSubsystemVersion|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.MinorSubsystemVersion),
    OptionalHeader.MinorSubsystemVersion);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->Win32VersionValue));
  strHDR.Format(_T("Win32VersionValue|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.Win32VersionValue),
    OptionalHeader.Win32VersionValue);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfImage));
  strHDR.Format(_T("SizeOfImage|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfImage),
    OptionalHeader.SizeOfImage);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfHeaders));
  strHDR.Format(_T("SizeOfHeaders|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfHeaders),
    OptionalHeader.SizeOfHeaders);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->CheckSum));
  strHDR.Format(_T("CheckSum|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.CheckSum),
    OptionalHeader.CheckSum);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->Subsystem));
  strHDR.Format(_T("Subsystem|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.Subsystem),
    OptionalHeader.Subsystem);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->DllCharacteristics));
  strHDR.Format(_T("DllCharacteristics|0x%08p|%x|0x%04X"),       
    lOffset, sizeof(OptionalHeader.DllCharacteristics),
    OptionalHeader.DllCharacteristics);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfStackReserve));
  strHDR.Format(_T("SizeOfStackReserve|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfStackReserve),
    OptionalHeader.SizeOfStackReserve);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfStackCommit));
  strHDR.Format(_T("SizeOfStackCommit|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfStackCommit),
    OptionalHeader.SizeOfStackCommit);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfHeapReserve));
  strHDR.Format(_T("SizeOfHeapReserve|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfHeapReserve),
    OptionalHeader.SizeOfHeapReserve);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfHeapCommit));
  strHDR.Format(_T("SizeOfHeapCommit|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.SizeOfHeapCommit),
    OptionalHeader.SizeOfHeapCommit);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->LoaderFlags));
  strHDR.Format(_T("LoaderFlags|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.LoaderFlags),
    OptionalHeader.LoaderFlags);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->NumberOfRvaAndSizes));
  strHDR.Format(_T("NumberOfRvaAndSizes|0x%08p|%x|0x%08X"),       
    lOffset, sizeof(OptionalHeader.NumberOfRvaAndSizes),
    OptionalHeader.NumberOfRvaAndSizes);
  m_HeaderInfo.AddItem(nCount++, strHDR);
  
  m_HeaderInfo.AutoSize();
}


void CPExplorerDlg::ShowDataDirectory(IMAGE_DATA_DIRECTORY * lpDataDirectory)
{
  LONG lBaseOffset = m_lpPeFile.Gete_lfanew() 
    + sizeof(m_lpPeFile.GetSignature())
    + sizeof(IMAGE_FILE_HEADER);
  LONG lOffset = lBaseOffset 
    + (LONG)((&((IMAGE_OPTIONAL_HEADER*)NULL)->NumberOfRvaAndSizes))
    + sizeof((&((IMAGE_OPTIONAL_HEADER*)NULL)->NumberOfRvaAndSizes));
  DWORD NumberOfRvaAndSizes = m_lpPeFile.GetNumberOfRvaAndSizes();
  CString strHDR(_T(""));
  if (NumberOfRvaAndSizes > 16)
  {
    NumberOfRvaAndSizes = 16;
  }
  tagDirectory* lpszDataDirectory = new tagDirectory[NumberOfRvaAndSizes];
  FormatszDataDirectory(lpszDataDirectory);
  int nCount = 0;
  
  for (DWORD i = 0; i < NumberOfRvaAndSizes; i++)
  {
    for (DWORD j = 0; j < 2; j++)
    {
      if (j == 0)
      {
        strHDR.Format(_T("%s|0x%08p|%x|0x%08X"), 
          lpszDataDirectory[i].strVirtualAddress, 
          lOffset,
          sizeof(lpDataDirectory[i].VirtualAddress), 
          lpDataDirectory[i].VirtualAddress);
        lOffset += sizeof(lpDataDirectory[i].VirtualAddress);
      }
      else if (j == 1)
      {
        strHDR.Format(_T("%s|0x%08p|%x|0x%08X"), 
          lpszDataDirectory[i].Size, 
          lOffset,
          sizeof(lpDataDirectory[i].Size), 
          lpDataDirectory[i].Size);
        lOffset += sizeof(lpDataDirectory[i].Size);
      }
      
      m_HeaderInfo.AddItem(nCount++, strHDR);
    }
  }
  
  NumberOfRvaAndSizes = m_lpPeFile.GetNumberOfRvaAndSizes();
  if (NumberOfRvaAndSizes > 16)
  {
    for (i = 16; i < NumberOfRvaAndSizes; i++)
    {
      for (DWORD j = 0; j < 2; j++)
      {
        if (j == 0)
        {
          strHDR.Format(_T("%s|0x%08p|%x|0x%08X"), 
            lpszDataDirectory[15].strVirtualAddress, 
            lOffset,
            sizeof(lpDataDirectory[15].VirtualAddress), 
            lpDataDirectory[15].VirtualAddress);
          lOffset += sizeof(lpDataDirectory[15].VirtualAddress);
        }
        else if (j == 1)
        {
          strHDR.Format(_T("%s|0x%08p|%x|0x%08X"), 
            lpszDataDirectory[15].Size, 
            lOffset,
            sizeof(lpDataDirectory[15].Size), 
            lpDataDirectory[15].Size);
          lOffset += sizeof(lpDataDirectory[15].Size);
        }
        
        m_HeaderInfo.AddItem(nCount++, strHDR);
      }
    }
  }
  
  
  if (lpszDataDirectory != NULL)
  {
    delete[] lpszDataDirectory;
    lpszDataDirectory = NULL;
  }
  m_HeaderInfo.AutoSize();
}

void CPExplorerDlg::FormatszDataDirectory(tagDirectory* lpszDataDirectory)
{
  DWORD NumberOfRvaAndSizes = m_lpPeFile.GetNumberOfRvaAndSizes();
  if (NumberOfRvaAndSizes <= 0)
  {
    return;
  }
  lpszDataDirectory[0].strVirtualAddress = _T("Export Directory RVA");
  lpszDataDirectory[0].Size = _T("Export Directory Size");
  if (NumberOfRvaAndSizes <= 1)
  {
    return;
  }
  lpszDataDirectory[1].strVirtualAddress = _T("Import Directory RVA");
  lpszDataDirectory[1].Size = _T("Import Directory Size");
  if (NumberOfRvaAndSizes <= 2)
  {
    return;
  }
  lpszDataDirectory[2].strVirtualAddress = _T("Resource Directory RVA");
  lpszDataDirectory[2].Size = _T("Resource Directory Size");
  if (NumberOfRvaAndSizes <= 3)
  {
    return;
  }
  lpszDataDirectory[3].strVirtualAddress = _T("Exception Directory RVA");
  lpszDataDirectory[3].Size = _T("Exception Directory Size");
  if (NumberOfRvaAndSizes <= 4)
  {
    return;
  }
  lpszDataDirectory[4].strVirtualAddress = _T("Security Directory RVA");
  lpszDataDirectory[4].Size = _T("Security Directory Size");
  if (NumberOfRvaAndSizes <= 5)
  {
    return;
  }
  lpszDataDirectory[5].strVirtualAddress = _T("Base Relocation Table RVA");
  lpszDataDirectory[5].Size = _T("Base Relocation Table Size");
  if (NumberOfRvaAndSizes <= 6)
  {
    return;
  }
  lpszDataDirectory[6].strVirtualAddress = _T("Debug Directory RVA");
  lpszDataDirectory[6].Size = _T("Debug Directory Size");
  if (NumberOfRvaAndSizes <= 7)
  {
    return;
  }
  lpszDataDirectory[7].strVirtualAddress = _T("Architecture Specific Data RVA");
  lpszDataDirectory[7].Size = _T("Architecture Specific DataSize");
  if (NumberOfRvaAndSizes <= 8)
  {
    return;
  }
  lpszDataDirectory[8].strVirtualAddress = _T("RVA of GP RVA");
  lpszDataDirectory[8].Size = _T("RVA of GP Size");
  if (NumberOfRvaAndSizes <= 9)
  {
    return;
  }
  lpszDataDirectory[9].strVirtualAddress = _T("TLS Directory RVA");
  lpszDataDirectory[9].Size = _T("TLS Directory Size");
  if (NumberOfRvaAndSizes <= 10)
  {
    return;
  }
  lpszDataDirectory[10].strVirtualAddress = _T("Load Configuration Directory RVA");
  lpszDataDirectory[10].Size = _T("Load Configuration Directory Size");
  if (NumberOfRvaAndSizes <= 11)
  {
    return;
  }
  lpszDataDirectory[11].strVirtualAddress = _T("Bound Import Directory RVA");
  lpszDataDirectory[11].Size = _T("Bound Import Directory Size");
  if (NumberOfRvaAndSizes <= 12)
  {
    return;
  }
  lpszDataDirectory[12].strVirtualAddress = _T("Import Address Table  RVA");
  lpszDataDirectory[12].Size = _T("Import Address Table  Size");
  if (NumberOfRvaAndSizes <= 13)
  {
    return;
  }
  lpszDataDirectory[13].strVirtualAddress = _T("Delay Import Directory RVA");
  lpszDataDirectory[13].Size = _T("Delay Import Directory Size");
  if (NumberOfRvaAndSizes <= 14)
  {
    return;
  }
  lpszDataDirectory[14].strVirtualAddress = _T("COM Runtime descriptor RVA");
  lpszDataDirectory[14].Size = _T("COM Runtime descriptor Size");
  if (NumberOfRvaAndSizes <= 15)
  {
    return;
  }
  lpszDataDirectory[15].strVirtualAddress = _T("Unknown RVA");
  lpszDataDirectory[15].Size = _T("Unknown Size");
}

void CPExplorerDlg::ShowSectionHeader()
{
  CString strHDR(_T(""));
  strHDR.Format(_T("Size|8|4|4|4|4|4|4|2|2|4"));
  int nCount = 0;
  m_HeaderInfo.AddItem(nCount++, strHDR);
  int nNumOfSection = m_lpPeFile.GetNumberOfSections();
  for (int i = 0; i < nNumOfSection; i++)
  {
    strHDR.Empty();
    IMAGE_SECTION_HEADER SectionHeader = {0};
    m_lpPeFile.GetSectionHeader(&SectionHeader, i);
    CString strName = SectionHeader.Name;
    TCHAR szName[9] = {0};
    memcpy(szName, strName, 8);
    strHDR.Format(_T("0x%08X|%8s|0x%08X|0x%08X|0x%08X"
      "|0x%08X|0x%08X|0x%08X|0x%04X|0x%04X|0x%08X"),
      m_lpPeFile.GetSectionOffset(i), szName, SectionHeader.Misc, 
      SectionHeader.VirtualAddress, SectionHeader.SizeOfRawData, 
      SectionHeader.PointerToRawData, SectionHeader.PointerToRelocations, 
      SectionHeader.PointerToLinenumbers, SectionHeader.NumberOfRelocations,
      SectionHeader.NumberOfLinenumbers, SectionHeader.Characteristics);
    m_HeaderInfo.AddItem(nCount++, strHDR);
  }
  m_HeaderInfo.AutoSize();
  //   //SetRedraw(FALSE);
  //   CHeaderCtrl* pHeaderCtrl = m_HeaderInfo.GetHeaderCtrl();
  //   for (i = 0; i < pHeaderCtrl->GetItemCount(); i++)
  //   {
  //     m_HeaderInfo.SetColumnWidth(i, LVSCW_AUTOSIZE);
  //     int nWidth1 = m_HeaderInfo.GetColumnWidth(i);
  // //     m_HeaderInfo.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
  // //     int nWidth2 = m_HeaderInfo.GetColumnWidth(i);
  //     m_HeaderInfo.SetColumnWidth(i, nWidth1);
  //     
  //   }
  //  // SetRedraw(TRUE);
}

void CPExplorerDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  {
    if (m_dwCurSelListCtrl == SECTIONHEADER)
    {
      CRect rect;//定义矩形区域
      GetDlgItem(IDC_LIST_INFO)->GetWindowRect(&rect);//获取控件区域的矩形
      
      if(rect.PtInRect(point))
      {
        CMenu menu;
        VERIFY(menu.LoadMenu(IDR_POPUP_SECTION));
        
        CMenu* pPopup = menu.GetSubMenu(0);
        ASSERT(pPopup != NULL);
        CWnd* pWndPopupOwner = this;
        
        while (pWndPopupOwner->GetStyle() & WS_CHILD)
          pWndPopupOwner = pWndPopupOwner->GetParent();
        
        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
          point.x, point.y,
          pWndPopupOwner);
      }
    }
  }
}

void CPExplorerDlg::OnSectionAdd() 
{
  CAddSectionDlg dlg;
  dlg.m_strFilePath = m_strFilePath;
  if (dlg.DoModal())
  {
  }
}

void CPExplorerDlg::OnSectionLoadfile() 
{
  TCHAR szFilter[] = "Bin Files (*.bin)|*.bin|";
  
  CFileDialog Dlg(TRUE, NULL, NULL, 
    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    szFilter, NULL);
  if (Dlg.DoModal() == IDOK)
  {
  }
}

void CPExplorerDlg::ShowImportDitectory()
{
  IMAGE_DATA_DIRECTORY* ImportDir = 
    m_lpPeFile.GetDataDirectory(IMAGE_DIRECTORY_ENTRY_IMPORT);
  DWORD dwCount = ImportDir->Size / sizeof(IMAGE_IMPORT_DESCRIPTOR);
  IMAGE_IMPORT_DESCRIPTOR ImportDescriptorCmp = {0};
  IMAGE_IMPORT_DESCRIPTOR ImportDescriptor = {0};
  for (DWORD i = 0; i < dwCount; i++)
  {
    ZeroMemory(&ImportDescriptor, sizeof(IMAGE_IMPORT_DESCRIPTOR));
    DWORD dwOffset = m_lpPeFile.GetImportDescriptor(&ImportDescriptor, i);
    if (memcmp(&ImportDescriptorCmp, 
      &ImportDescriptor, 
      sizeof(IMAGE_IMPORT_DESCRIPTOR)) == 0 || i == (dwCount - 1))
    {
      break;
    }
    TCHAR ImportName[MAX_PATH] = {0};
    DWORD dwNameOffset = m_lpPeFile.RVAToFA(ImportDescriptor.Name);
    DWORD nLen = m_lpPeFile.GetImportName(ImportName, dwNameOffset);

    CString strImport(_T(""));
    //CString strName = ImportName;
    strImport.Format(_T("%s|0x%08X|0x%08X|0x%08X|0x%08X|0x%08X"),
      ImportName,
      ImportDescriptor.OriginalFirstThunk, ImportDescriptor.TimeDateStamp,
      ImportDescriptor.ForwarderChain, ImportDescriptor.Name,
      ImportDescriptor.FirstThunk);
    m_HeaderInfo.AddItem(i, strImport);
  }
  
  m_HeaderInfo.AutoSize();
}


void CPExplorerDlg::OnImportListPopMenu(CPoint point)
{
  if (m_dwCurSelListCtrl == IMPORT_DIRECTORY)
  {
    CMenu menu;
    VERIFY(menu.LoadMenu(IDR_IMPORT_FUN));
    
    CMenu* pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);
    CWnd* pWndPopupOwner = this;
    
    while (pWndPopupOwner->GetStyle() & WS_CHILD)
      pWndPopupOwner = pWndPopupOwner->GetParent();
    
    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
      point.x, point.y,
          pWndPopupOwner);
  }
}

void CPExplorerDlg::OnImportShowall() 
{
  CShowIATDlg dlg;
  dlg.m_strFilePath = m_strFilePath;
  dlg.m_dwCurSelModuleName = m_dwCurSelModuleName;
  if (dlg.DoModal())
  {
  }
}

void CPExplorerDlg::OnSectionAddressconvert() 
{
  CConvertDlg dlg;
  dlg.m_strFilePath = m_strFilePath;
  if (dlg.DoModal())
  {

  }
}
