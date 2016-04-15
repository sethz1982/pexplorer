// ShowIATDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PExplorer.h"
#include "ShowIATDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowIATDlg dialog


CShowIATDlg::CShowIATDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowIATDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowIATDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShowIATDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowIATDlg)
	DDX_Control(pDX, IDC_LIST_IAT, m_IATList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowIATDlg, CDialog)
	//{{AFX_MSG_MAP(CShowIATDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowIATDlg message handlers

BOOL CShowIATDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_IATList.DeleteAllItems();
  m_IATList.InitList(_T("OFTs|Hint|Name"), 3);
  ShowAllIAT();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowIATDlg::ShowAllIAT()
{
  if (m_lpPeFile.m_hFile == -1)
  {
    m_lpPeFile.Open(m_strFilePath);
  }
  IMAGE_IMPORT_DESCRIPTOR ImportDescriptor = {0};
  DWORD dwOffset = 0;
  m_lpPeFile.GetImportDescriptor(&ImportDescriptor, 
                                  m_dwCurSelModuleName);
  if (ImportDescriptor.OriginalFirstThunk != NULL 
    && ImportDescriptor.OriginalFirstThunk < m_lpPeFile.GetPeFileSize())
  {
    
    dwOffset = m_lpPeFile.RVAToFA(ImportDescriptor.OriginalFirstThunk);
  }
  else if (ImportDescriptor.FirstThunk != NULL 
    && ImportDescriptor.FirstThunk < m_lpPeFile.GetPeFileSize())
  {
    dwOffset = m_lpPeFile.RVAToFA(ImportDescriptor.FirstThunk);
  }
  
  int nCount = 0;
  while (TRUE)
  {
    DWORD dwIATOffet = 0;
    m_lpPeFile.Seek(dwOffset, CFile::begin);
    dwOffset += sizeof(DWORD);
    m_lpPeFile.Read(&dwIATOffet, sizeof(DWORD));
    if (dwIATOffet == 0)
    {
      break;
    }
    CString strListItem(_T(""));
    if (dwIATOffet > 0x80000000)
    {
      DWORD dwOrdinal = IMAGE_ORDINAL32(dwIATOffet);
      strListItem.Format(_T("0x%08X|N/A|Ordinal:0x%08X"),
        dwIATOffet, dwOrdinal);
    }
    else
    {
      DWORD dwApiOffset = m_lpPeFile.RVAToFA(dwIATOffet);
      m_lpPeFile.Seek(dwApiOffset, CFile::begin);
      TCHAR szApiName[MAX_PATH] = {0};
      m_lpPeFile.Read(szApiName, MAX_PATH);
      IMAGE_IMPORT_BY_NAME* ImportName = (IMAGE_IMPORT_BY_NAME*)szApiName;
      
      strListItem.Format(_T("0x%08X|0x%04x|%s"),
        dwIATOffet, ImportName->Hint,
                          ImportName->Name);
    }

    
    m_IATList.AddItem(nCount++, strListItem);
  }
  m_IATList.AutoSize();
}
