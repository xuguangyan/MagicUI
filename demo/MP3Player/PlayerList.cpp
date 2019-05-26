// PlayerList.cpp : implementation file
//

#include "stdafx.h"
#include "MP3Player.h"
#include "PlayerList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayerList dialog

IMPLEMENT_DYNAMIC(CPlayerList, CMagicWnd)

CPlayerList::CPlayerList()
{
}

CPlayerList::~CPlayerList()
{
}

BEGIN_MESSAGE_MAP(CPlayerList, CMagicWnd)
	//{{AFX_MSG_MAP(CPlayerList)
		// NOTE: the ClassWizard will add message map macros here
		ON_BN_CLICKED(3000,OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerList message handlers
void CPlayerList::OnClose()
{
	ShowWindow(SW_HIDE);
}