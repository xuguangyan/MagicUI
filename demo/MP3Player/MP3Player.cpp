// MP3Player.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MP3Player.h"
#include "MP3PlayerMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMP3PlayerApp

BEGIN_MESSAGE_MAP(CMP3PlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CMP3PlayerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMP3PlayerApp construction

CMP3PlayerApp::CMP3PlayerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMP3PlayerApp object

CMP3PlayerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMP3PlayerApp initialization

BOOL CMP3PlayerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
//========Magic UI Library Call Sample Start========
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	CString strFilePath = path;
	strFilePath = strFilePath.Left(strFilePath.ReverseFind('\\'));

	CString strSkinPath;
	strSkinPath.Format(_T("%s\\Skin\\"), strFilePath);

	m_pPlayerWnd = new CMP3Player();
	m_pPlayerWnd->Create(strSkinPath, _T("MP3Player.xml"), _T("Global.xml"));
	m_pMainWnd = m_pPlayerWnd;

	return TRUE;
//========Magic UI Library Call Sample End========
}

int CMP3PlayerApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::ExitInstance();
}
