; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPlayerList
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MP3Player.h"

ClassCount=5
Class1=CMP3PlayerApp
Class2=CMP3PlayerDlg
Class3=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CPlayerList
Resource2=IDD_ABOUTBOX

[CLS:CMP3PlayerApp]
Type=0
HeaderFile=MP3Player.h
ImplementationFile=MP3Player.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CMP3PlayerDlg]
Type=0
HeaderFile=MP3PlayerDlg.h
ImplementationFile=MP3PlayerDlg.cpp
Filter=D
BaseClass=CMagicWnd
VirtualFilter=WC

[CLS:CAboutDlg]
Type=0
HeaderFile=MP3PlayerDlg.h
ImplementationFile=MP3PlayerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CPlayerList]
Type=0
HeaderFile=PlayerList.h
ImplementationFile=PlayerList.cpp
BaseClass=CDialog
Filter=D

