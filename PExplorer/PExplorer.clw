; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConvertDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PExplorer.h"

ClassCount=7
Class1=CPExplorerApp
Class2=CPExplorerDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_POPUP_SECTION
Class4=CMyTreeCtrl
Resource4=IDR_MENU
Resource5=IDD_DLG_CONVERT
Class5=CAddSectionDlg
Resource6=IDD_DLG_SHOWIAT
Resource7=IDD_DLG_ADDSECTION
Class6=CShowIATDlg
Resource8=IDD_PEXPLORER_DIALOG
Class7=CConvertDlg
Resource9=IDR_IMPORT_FUN

[CLS:CPExplorerApp]
Type=0
HeaderFile=PExplorer.h
ImplementationFile=PExplorer.cpp
Filter=N

[CLS:CPExplorerDlg]
Type=0
HeaderFile=PExplorerDlg.h
ImplementationFile=PExplorerDlg.cpp
Filter=W
LastObject=CPExplorerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=PExplorerDlg.h
ImplementationFile=PExplorerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PEXPLORER_DIALOG]
Type=1
Class=CPExplorerDlg
ControlCount=2
Control1=IDC_TREE_HEADER,SysTreeView32,1350631431
Control2=IDC_LIST_INFO,SysListView32,1350631425

[MNU:IDR_MENU]
Type=1
Class=?
Command1=IDM_FILE_OPEN
Command2=IDM_FILE_EXIT
CommandCount=2

[CLS:CMyTreeCtrl]
Type=0
HeaderFile=MyTreeCtrl.h
ImplementationFile=MyTreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W
LastObject=CMyTreeCtrl

[MNU:IDR_POPUP_SECTION]
Type=1
Class=?
Command1=ID_SECTION_ADD
Command2=ID_SECTION_LOADFILE
Command3=ID_SECTION_ADDRESSCONVERT
CommandCount=3

[DLG:IDD_DLG_ADDSECTION]
Type=1
Class=CAddSectionDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_NAME,edit,1350635648
Control4=IDC_EDIT_SIZE,edit,1350643844
Control5=IDC_BTN_ADD,button,1342242817

[CLS:CAddSectionDlg]
Type=0
HeaderFile=AddSectionDlg.h
ImplementationFile=AddSectionDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddSectionDlg
VirtualFilter=dWC

[MNU:IDR_IMPORT_FUN]
Type=1
Class=?
Command1=IDM_IMPORT_SHOWALL
CommandCount=1

[DLG:IDD_DLG_SHOWIAT]
Type=1
Class=CShowIATDlg
ControlCount=1
Control1=IDC_LIST_IAT,SysListView32,1350631425

[CLS:CShowIATDlg]
Type=0
HeaderFile=ShowIATDlg.h
ImplementationFile=ShowIATDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CShowIATDlg
VirtualFilter=dWC

[DLG:IDD_DLG_CONVERT]
Type=1
Class=CConvertDlg
ControlCount=7
Control1=IDC_EDIT_RVA,edit,1350635648
Control2=IDC_EDIT_FA,edit,1350635648
Control3=IDC_EDIT_VA,edit,1350635648
Control4=IDC_BTN_CONVERT,button,1342242817
Control5=IDC_CHECK_RVA,button,1342181379
Control6=IDC_CHECK_FA,button,1342181379
Control7=IDC_CHECK_VA,button,1342181379

[CLS:CConvertDlg]
Type=0
HeaderFile=ConvertDlg.h
ImplementationFile=ConvertDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK_VA

