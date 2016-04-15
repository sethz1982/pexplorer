// AddSectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PExplorer.h"
#include "AddSectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg dialog


CAddSectionDlg::CAddSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddSectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddSectionDlg)
	m_strSectionName = _T("");
	m_uSize = 0;
	//}}AFX_DATA_INIT
}


void CAddSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddSectionDlg)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strSectionName);
	DDV_MaxChars(pDX, m_strSectionName, 8);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_uSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddSectionDlg, CDialog)
	//{{AFX_MSG_MAP(CAddSectionDlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddSectionDlg message handlers

void CAddSectionDlg::OnBtnAdd() 
{
  GetSectionInfo();
  if (m_lpPeFile.m_hFile == -1)
  {
    m_lpPeFile.Open(m_strFilePath);
  }
  
  AddSection();
}

void CAddSectionDlg::GetSectionInfo()
{
  UpdateData(TRUE);
  if (m_strSectionName.IsEmpty())
  {
    m_strSectionName = _T("Cr51Asm");
  }
  if (m_uSize == 0)
  {
    m_uSize = 200;    //This is Hex Convert To Dec
  }
  //Dec To Hex
  TCHAR szBuf[MAXBYTE] = {0};
  wsprintf(szBuf, _T("%d"), m_uSize);
  m_uSize = strtol(szBuf, 0, 16);

}

void CAddSectionDlg::AddSection()
{
  DWORD dwOffset = m_lpPeFile.GetSectionOffset(0);
  dwOffset = m_lpPeFile.GetNumberOfSections() * sizeof(IMAGE_SECTION_HEADER);
  DWORD dwSizeOfHeader = m_lpPeFile.GetSizeOfHeaders();
  DWORD dwSum = dwSizeOfHeader - dwOffset;
  if (dwSum >= sizeof(IMAGE_SECTION_HEADER))
  {
    WORD wNumberOfSections = m_lpPeFile.GetNumberOfSections();
    m_lpPeFile.SetNumberOfSections(wNumberOfSections + 1);
    DWORD SectionAlignment = CheckSectionAlignment(m_uSize);
    DWORD dwSizeofImage = m_lpPeFile.GetSizeOfImage();
    m_lpPeFile.SetSizeOfImage(dwSizeofImage + SectionAlignment);
    IMAGE_SECTION_HEADER SectionHeader = {0};
    m_lpPeFile.GetSectionHeader(&SectionHeader, wNumberOfSections - 1);
    IMAGE_SECTION_HEADER SectionTemp = {0};
    memcpy(SectionTemp.Name, m_strSectionName, 8);
    SectionTemp.Misc.VirtualSize = (DWORD)m_uSize;
    SectionTemp.VirtualAddress = 
      CheckSectionAlignment(SectionHeader.VirtualAddress 
      + SectionHeader.Misc.VirtualSize);
    SectionTemp.SizeOfRawData = CheckFileAlignment(m_uSize);
    SectionTemp.PointerToRawData =SectionHeader.PointerToRawData 
      + SectionHeader.SizeOfRawData;
    SectionTemp.Characteristics = IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ;
    m_lpPeFile.SetSectionHeader(SectionTemp, wNumberOfSections);
    m_lpPeFile.SeekToEnd();
    TCHAR* lpBuf = new TCHAR[SectionTemp.SizeOfRawData];
    ZeroMemory(lpBuf, SectionTemp.SizeOfRawData);
    m_lpPeFile.Write(lpBuf, SectionTemp.SizeOfRawData);
    delete[] lpBuf;
    lpBuf = NULL;

    if (m_lpPeFile.GetNumberOfRvaAndSizes() > IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT)
    {
      m_lpPeFile.ZeroBoundImportDataDir();
    }
  }
  else
  {
  
  }
}

DWORD CAddSectionDlg::CheckSectionAlignment(DWORD dwSize)
{
  DWORD SectionAlignment = m_lpPeFile.GetSectionAlignment();
  return ((dwSize / SectionAlignment) + 1) * SectionAlignment;
}

DWORD CAddSectionDlg::CheckFileAlignment(DWORD dwSize)
{
  DWORD FileAlignment = m_lpPeFile.GetFileAlignment();
  return ((dwSize / FileAlignment) + 1) * FileAlignment;
}
