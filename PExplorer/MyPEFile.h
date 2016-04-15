// MyPEFile.h: interface for the CMyPEFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPEFILE_H__DF57E365_EE38_48C8_9008_509E5189A2F0__INCLUDED_)
#define AFX_MYPEFILE_H__DF57E365_EE38_48C8_9008_509E5189A2F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afx.h>

#define MZ_SIGNA 0x5A4D
#define PE_SIGNA 0x00004550

class CMyPEFile : public CFile  
{
public:
	CMyPEFile();
  CMyPEFile(int hFile);
  CMyPEFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	virtual ~CMyPEFile();
public:
  virtual BOOL Open(LPCTSTR lpszFileName);
  virtual void Close();
public:
  DWORD GetPeFileSize();
  DWORD GetFileHeaderOffset();
	DWORD GetOptionalOffset();
  DWORD GetSectionOffset(WORD NumOfSections);
	void ReadAllHeader();
  //��ȡ DOS_HEADER
  IMAGE_DOS_HEADER GetDosHeader() const;
  WORD Gete_magic() const;    // Magic number
  LONG Gete_lfanew() const;   // File address of new exe header

  //��ȡNT Header
  DWORD GetSignature() const;
  
  IMAGE_FILE_HEADER GetFileHeader() const;
  WORD GetNumberOfSections() const;
  WORD GetSizeOfOptionalHeader() const;
  IMAGE_OPTIONAL_HEADER GetOptionalHeader() const;
  DWORD GetImageBase() const;
  DWORD GetSectionAlignment() const;
  DWORD GetFileAlignment() const;
  DWORD GetSizeOfImage() const;
  DWORD GetSizeOfHeaders() const;
  DWORD GetNumberOfRvaAndSizes() const;
  IMAGE_DATA_DIRECTORY* GetDataDirectory(DWORD NumberOfRvaAndSizes);
  
  void GetSectionHeader(IMAGE_SECTION_HEADER* SectionHeader,WORD NumOfSections);

  DWORD GetImportDescriptor(IMAGE_IMPORT_DESCRIPTOR*, DWORD);
  DWORD GetImportName(TCHAR*, DWORD );
  //����NT Header
  void SetNumberOfSections(WORD wNumOfSections);
  void SetSizeOfImage(DWORD dwSizeOfImage);
  void ZeroBoundImportDataDir();
  void SetSectionHeader(IMAGE_SECTION_HEADER SectionHeader, WORD NumOfSections);

  //ת��
  DWORD CheckSectionAlignment(DWORD dwSize);
  DWORD CheckFileAlignment(DWORD dwSize);
  DWORD RVAToFA(DWORD dwRVA);
  DWORD FAToRVA(DWORD dwFA);
private:
  //�ж��Ƿ���PE�ļ�
	BOOL IsPEFile();
  //��ʼ���ṹ��ͳ�Ա
  void Init();
private:
  IMAGE_DOS_HEADER      m_DosHeader;
  IMAGE_NT_HEADERS      m_NtHeaders;
  IMAGE_SECTION_HEADER  m_SectionHeader;
};

#endif // !defined(AFX_MYPEFILE_H__DF57E365_EE38_48C8_9008_509E5189A2F0__INCLUDED_)