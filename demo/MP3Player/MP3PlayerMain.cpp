// MP3PlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MP3Player.h"
#include "MP3PlayerMain.h"
#include "PlayerList.h"

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
// CMP3Player dialog

IMPLEMENT_DYNAMIC(CMP3Player, CMagicWnd)

CMP3Player::CMP3Player()
{
}

CMP3Player::~CMP3Player()
{
}

BEGIN_MESSAGE_MAP(CMP3Player, CMagicWnd)
	//{{AFX_MSG_MAP(CMP3Player)
	ON_WM_CREATE()
	ON_BN_CLICKED(2010,OnPlayList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMP3Player message handlers

int CMP3Player::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMagicWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	CString strFilePath = path;
	strFilePath = strFilePath.Left(strFilePath.ReverseFind('\\'));

	CString strSkinPath;
	strSkinPath.Format(_T("%s\\Skin\\"), strFilePath);
	m_pListWnd = new CPlayerList();
	m_pListWnd->Create(strSkinPath, _T("PlayerList.xml"), _T("Global.xml"),NULL,WS_POPUP|WS_VISIBLE,this);
	return 0;
}

void CMP3Player::OnPlayList()
{
	if(::IsWindowVisible(m_pListWnd->m_hWnd))
		m_pListWnd->ShowWindow(SW_HIDE);
	else
		m_pListWnd->ShowWindow(SW_SHOW);
}
