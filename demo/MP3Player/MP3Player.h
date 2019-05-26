// MP3Player.h : main header file for the MP3PLAYER application
//

#if !defined(AFX_MP3PLAYER_H__3C4DF214_3E15_4C46_BB44_D980C8281F1C__INCLUDED_)
#define AFX_MP3PLAYER_H__3C4DF214_3E15_4C46_BB44_D980C8281F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMP3PlayerApp:
// See MP3Player.cpp for the implementation of this class
//
class CMP3Player;
class CMP3PlayerApp : public CWinApp
{
public:
	CMP3PlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMP3PlayerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMP3PlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	private:
		CMP3Player *m_pPlayerWnd;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MP3PLAYER_H__3C4DF214_3E15_4C46_BB44_D980C8281F1C__INCLUDED_)
