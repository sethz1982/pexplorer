// ConvertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PExplorer.h"
#include "ConvertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvertDlg dialog


CConvertDlg::CConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvertDlg)
	m_strFA = _T("");
	m_strRVA = _T("");
	m_strVA = _T("");
	//}}AFX_DATA_INIT
  m_nSelect = -1;
}


void CConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvertDlg)
	DDX_Control(pDX, IDC_CHECK_VA, m_BtnVA);
	DDX_Control(pDX, IDC_CHECK_RVA, m_BtnRVA);
	DDX_Control(pDX, IDC_CHECK_FA, m_BtnFA);
	DDX_Text(pDX, IDC_EDIT_FA, m_strFA);
	DDX_Text(pDX, IDC_EDIT_RVA, m_strRVA);
	DDX_Text(pDX, IDC_EDIT_VA, m_strVA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvertDlg, CDialog)
	//{{AFX_MSG_MAP(CConvertDlg)
	ON_BN_CLICKED(IDC_BTN_CONVERT, OnBtnConvert)
	ON_BN_CLICKED(IDC_CHECK_FA, OnCheckFa)
	ON_BN_CLICKED(IDC_CHECK_RVA, OnCheckRva)
	ON_BN_CLICKED(IDC_CHECK_VA, OnCheckVa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvertDlg message handlers


BOOL CConvertDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

  m_lpPeFile.Open(m_strFilePath);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConvertDlg::OnBtnConvert() 
{
  DWORD dwImageBase = m_lpPeFile.GetImageBase();
  UpdateData(TRUE);
  if (m_nSelect == 0)
  {
    DWORD dwVA = strtol(m_strVA, 0, 0x10);
    DWORD dwRVA = dwVA - dwImageBase;
    DWORD dwFA = m_lpPeFile.RVAToFA(dwRVA);

    m_strVA.Format(_T("0x%08X"), dwVA);
    m_strRVA.Format(_T("0x%08X"), dwRVA);
    m_strFA.Format(_T("0x%08X"), dwFA);
  }
  else if (m_nSelect == 1)
  {
    DWORD dwRVA = strtol(m_strRVA, 0, 0x10);
    DWORD dwVA = dwRVA + dwImageBase;
    DWORD dwFA = m_lpPeFile.RVAToFA(dwRVA);

    m_strVA.Format(_T("0x%08X"), dwVA);
    m_strRVA.Format(_T("0x%08X"), dwRVA);
    m_strFA.Format(_T("0x%08X"), dwFA);

  }
  else if (m_nSelect == 2)
  {
    DWORD dwFA = strtol(m_strFA, 0, 0x10);
    DWORD dwRVA = m_lpPeFile.FAToRVA(dwFA);
    DWORD dwVA = dwRVA + dwImageBase;

    m_strVA.Format(_T("0x%08X"), dwVA);
    m_strRVA.Format(_T("0x%08X"), dwRVA);
    m_strFA.Format(_T("0x%08X"), dwFA);
  }
  UpdateData(FALSE);
}

void CConvertDlg::OnCheckFa() 
{
  if (m_BtnFA.GetCheck() == 1)
  {
    m_BtnVA.SetCheck(0);
    m_BtnRVA.SetCheck(0);
    m_nSelect = 2;
  }
}

void CConvertDlg::OnCheckRva() 
{
  if (m_BtnRVA.GetCheck() == 1)
  {
    m_BtnVA.SetCheck(0);
    m_BtnFA.SetCheck(0);
    m_nSelect = 1;
  }
}

void CConvertDlg::OnCheckVa() 
{
  if (m_BtnVA.GetCheck() == 1)
  {
    m_BtnRVA.SetCheck(0);
    m_BtnFA.SetCheck(0);
    m_nSelect = 0;
  }
}

int CConvertDlg::DecToHex(int nDec)
{
  int nHex = 0;
  TCHAR szBuf[MAXBYTE] = {0};
  wsprintf(szBuf, _T("%d"), nDec);
  nHex = strtol(szBuf, 0, 16);
  return nHex;
}
