// MyPEFile.cpp: implementation of the CMyPEFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyPEFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyPEFile::CMyPEFile()
          :CFile()
{
  Init();
}
CMyPEFile::CMyPEFile(int hFile)
          :CFile(hFile)
{
  Init();
}
CMyPEFile::CMyPEFile(LPCTSTR lpszFileName, UINT nOpenFlags)
          :CFile(lpszFileName,nOpenFlags)
{
  Init();
}
CMyPEFile::~CMyPEFile()
{

}
/************************************************************************/
// 功  能: 初始化结构体和成员  
// 参  数: 无
// 返回值: 无
/************************************************************************/
void CMyPEFile::Init()
{
  ZeroMemory(&m_DosHeader, sizeof(m_DosHeader));
  ZeroMemory(&m_NtHeaders, sizeof(m_NtHeaders));
  ZeroMemory(&m_SectionHeader, sizeof(m_SectionHeader));
}
/************************************************************************/
// 功  能: 打开文件  
// 参  数: lpszFileName 文件名 
// 返回值: 类型 BOOL, 打开的文件是PE文件 返回 TRUE, 其余返回FALSE
/************************************************************************/
BOOL CMyPEFile::Open(LPCTSTR lpszFileName)
{
  BOOL bRet = CFile::Open(lpszFileName, CFile::shareDenyNone);
  if (bRet)
  {
    bRet = IsPEFile();

    if (!bRet)
    {
      Close();
      return bRet;
    }
    ReadAllHeader();
  }
  return bRet;
}

void CMyPEFile::Close()
{
  Init();
  CFile::Close();
}

/************************************************************************/
// 功  能: 判断是否是PE文件  
// 参  数:  
// 返回值: 类型BOOL 
/************************************************************************/
BOOL CMyPEFile::IsPEFile()
{
  Read(&m_DosHeader, sizeof(m_DosHeader));
  if (m_DosHeader.e_magic == MZ_SIGNA)
  {
    Seek(m_DosHeader.e_lfanew, CFile::begin);
    Read(&m_NtHeaders, sizeof(m_NtHeaders.Signature));
    if (m_NtHeaders.Signature == PE_SIGNA)
    {
      return TRUE;
    }
  }
  return FALSE;
}

void CMyPEFile::ReadAllHeader()
{
  SeekToBegin();
  Read(&m_DosHeader, sizeof(m_DosHeader));
  Seek(m_DosHeader.e_lfanew, CFile::begin);
  Read(&m_NtHeaders.Signature, sizeof(m_NtHeaders.Signature));
  Read(&m_NtHeaders.FileHeader, sizeof(m_NtHeaders.FileHeader));
  Read(&m_NtHeaders.OptionalHeader, m_NtHeaders.FileHeader.SizeOfOptionalHeader);
}


IMAGE_DOS_HEADER CMyPEFile::GetDosHeader() const
{
  return m_DosHeader;
}
// Magic number
WORD CMyPEFile::Gete_magic() const
{
  return m_DosHeader.e_magic;
}
// File address of new exe header
LONG CMyPEFile::Gete_lfanew() const
{
  return m_DosHeader.e_lfanew;
}

DWORD CMyPEFile::GetSignature() const
{
  return m_NtHeaders.Signature;
}

IMAGE_FILE_HEADER CMyPEFile::GetFileHeader() const
{
  return m_NtHeaders.FileHeader;
}

IMAGE_OPTIONAL_HEADER CMyPEFile::GetOptionalHeader() const
{
  return m_NtHeaders.OptionalHeader;
}

DWORD CMyPEFile::GetImageBase() const
{
  return m_NtHeaders.OptionalHeader.ImageBase;
}

DWORD CMyPEFile::GetSectionAlignment() const
{
  return m_NtHeaders.OptionalHeader.SectionAlignment;
}

DWORD CMyPEFile::GetFileAlignment() const
{
  return m_NtHeaders.OptionalHeader.FileAlignment;
}

DWORD CMyPEFile::GetSizeOfImage() const
{
  return m_NtHeaders.OptionalHeader.SizeOfImage;
}

DWORD CMyPEFile::GetSizeOfHeaders() const
{
  return m_NtHeaders.OptionalHeader.SizeOfHeaders;
}

DWORD CMyPEFile::GetNumberOfRvaAndSizes() const
{
  int nOffset = (int)((&((IMAGE_OPTIONAL_HEADER*)NULL)->NumberOfRvaAndSizes));
  int nSizes = m_NtHeaders.FileHeader.SizeOfOptionalHeader - nOffset;
  int NumberOfRvaAndSizes = nSizes / sizeof(IMAGE_DATA_DIRECTORY);
  return NumberOfRvaAndSizes;
}

IMAGE_DATA_DIRECTORY* CMyPEFile::GetDataDirectory(DWORD NumberOfRvaAndSizes) 
{
  return &m_NtHeaders.OptionalHeader.DataDirectory[NumberOfRvaAndSizes];
}

WORD CMyPEFile::GetNumberOfSections() const
{
  return m_NtHeaders.FileHeader.NumberOfSections;
}

WORD CMyPEFile::GetSizeOfOptionalHeader() const
{
  return m_NtHeaders.FileHeader.SizeOfOptionalHeader;
}

DWORD CMyPEFile::GetSectionOffset(WORD NumOfSections)
{
  LONG lBaseOffset = m_DosHeader.e_lfanew 
                    + sizeof(m_DosHeader.e_lfanew)
                    + sizeof(IMAGE_FILE_HEADER);
  int nOffset = m_NtHeaders.FileHeader.SizeOfOptionalHeader;
  nOffset += lBaseOffset;
  nOffset += NumOfSections * sizeof(IMAGE_SECTION_HEADER);
  
  return nOffset;
}
void CMyPEFile::GetSectionHeader(IMAGE_SECTION_HEADER* SectionHeader, 
                                  WORD NumOfSections)
{
  int nOffset = GetSectionOffset(NumOfSections);;
  Seek(nOffset, CFile::begin);
  Read(SectionHeader, sizeof(IMAGE_SECTION_HEADER));
}

void CMyPEFile::SetNumberOfSections(WORD wNumOfSections)
{
  DWORD dwFileOffset = GetFileHeaderOffset();
  DWORD dwSeek = dwFileOffset 
                + (int)((&((IMAGE_FILE_HEADER*)NULL)->NumberOfSections));
  Seek(dwSeek, CFile::begin);
  Write(&wNumOfSections, sizeof(wNumOfSections));
}
void CMyPEFile::SetSizeOfImage(DWORD dwSizeOfImage)
{
  DWORD dwOptionalOffset = GetOptionalOffset();
  DWORD dwSeek = dwOptionalOffset 
                  + (int)((&((IMAGE_OPTIONAL_HEADER*)NULL)->SizeOfImage));
  Seek(dwSeek, CFile::begin);
  Write(&dwSizeOfImage, sizeof(dwSizeOfImage));
}

void CMyPEFile::ZeroBoundImportDataDir()
{
  DWORD dwOptionalOffset = GetOptionalOffset();
  DWORD dwSeek = dwOptionalOffset 
                  + (int)((&((IMAGE_OPTIONAL_HEADER*)NULL)->DataDirectory));
  dwSeek += sizeof(IMAGE_DATA_DIRECTORY) * IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT;
  IMAGE_DATA_DIRECTORY DataDirTemp = {0};
  Seek(dwSeek, CFile::begin);
  Write(&DataDirTemp, sizeof(IMAGE_DATA_DIRECTORY));
}
void CMyPEFile::SetSectionHeader(IMAGE_SECTION_HEADER SectionHeader, 
                                 WORD NumOfSections)
{
  DWORD dwSectionOffset = GetSectionOffset(NumOfSections);
  Seek(dwSectionOffset, CFile::begin);
  Write(&SectionHeader, sizeof(IMAGE_SECTION_HEADER));
}

DWORD CMyPEFile::GetOptionalOffset()
{
  LONG lBaseOffset = m_DosHeader.e_lfanew 
                    + sizeof(m_DosHeader.e_lfanew)
                    + sizeof(IMAGE_FILE_HEADER);
  return lBaseOffset;
}
DWORD CMyPEFile::GetPeFileSize()
{
  DWORD dwFileSizeHigh = 0;
  return GetFileSize((HANDLE)m_hFile, &dwFileSizeHigh);
}
DWORD CMyPEFile::GetFileHeaderOffset()
{
  DWORD dwPeOffset = Gete_lfanew() + sizeof(m_DosHeader.e_lfanew);
  return dwPeOffset;
}
DWORD CMyPEFile::CheckSectionAlignment(DWORD dwSize)
{
  DWORD SectionAlignment = GetSectionAlignment();
  if (dwSize % SectionAlignment == 0)
  {
    return dwSize;
  }
  return ((dwSize / SectionAlignment) + 1) * SectionAlignment;
}
DWORD CMyPEFile::CheckFileAlignment(DWORD dwSize)
{
  DWORD FileAlignment = GetFileAlignment();
  if (dwSize % FileAlignment == 0)
  {
    return dwSize;
  }
  return ((dwSize / FileAlignment) + 1) * FileAlignment;
}

DWORD CMyPEFile::RVAToFA(DWORD dwRVA)
{
  DWORD dwFA = -1;
  if (dwRVA < GetSizeOfHeaders())
  {
    return dwRVA;
  }
  for (int i = 0; i < GetNumberOfSections(); i++)
  {
    IMAGE_SECTION_HEADER Section = {0};
    GetSectionHeader(&Section, i);
    if (dwRVA >= Section.VirtualAddress  
      && dwRVA < (Section.VirtualAddress + Section.Misc.VirtualSize))
    {
      dwFA = dwRVA - Section.VirtualAddress + Section.PointerToRawData;
      break;
    }
    else if (dwRVA > (Section.VirtualAddress + Section.Misc.VirtualSize))
    {
      DWORD dwFileSizeAligment = CheckFileAlignment(Section.SizeOfRawData);
      dwFA = dwRVA - Section.VirtualAddress + Section.PointerToRawData;
      if (dwRVA >= Section.PointerToRawData 
          && dwRVA < Section.PointerToRawData + Section.SizeOfRawData)
      {
        break;
      }
    }
  }
  return dwFA;
}
DWORD CMyPEFile::FAToRVA(DWORD dwFA)
{
  DWORD dwRVA = -1;
  if (dwFA < GetSizeOfHeaders())
  {
    return dwFA;
  }
  for (int i = 0; i < GetNumberOfSections(); i++)
  {
    IMAGE_SECTION_HEADER Section = {0};
    GetSectionHeader(&Section, i);
    if (dwFA >= Section.PointerToRawData 
        && dwFA < (Section.PointerToRawData + Section.SizeOfRawData) )
    {
      dwRVA = dwFA - Section.PointerToRawData + Section.VirtualAddress;
    }
  }
  return dwRVA;
}

DWORD CMyPEFile::GetImportDescriptor(IMAGE_IMPORT_DESCRIPTOR* ImportDescriptor, DWORD dwCount)
{
  IMAGE_DATA_DIRECTORY* ImportDir = GetDataDirectory(IMAGE_DIRECTORY_ENTRY_IMPORT);
  DWORD dwFAImportOffset = RVAToFA(ImportDir->VirtualAddress);
  dwFAImportOffset += dwCount * sizeof(IMAGE_IMPORT_DESCRIPTOR);
  Seek(dwFAImportOffset, CFile::begin);
  Read(ImportDescriptor, sizeof(IMAGE_IMPORT_DESCRIPTOR));
  return dwFAImportOffset;
}

DWORD CMyPEFile::GetImportName(TCHAR* ImportName, DWORD dwOffset)
{
  Seek(dwOffset, CFile::begin);
  Read(ImportName, MAX_PATH);
  DWORD dwLen = strlen(ImportName);
  return dwLen;
}