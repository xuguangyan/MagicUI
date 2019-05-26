// MSNLogin.h : main header file for the MSNLOGIN application
//

#if !defined(AFX_MSNLOGIN_H__BFADC3E3_B803_41F1_B28B_4030A05EA611__INCLUDED_)
#define AFX_MSNLOGIN_H__BFADC3E3_B803_41F1_B28B_4030A05EA611__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSNLoginApp:
// See MSNLogin.cpp for the implementation of this class
//
class CMSNLoginDlg;
class CMSNLoginApp : public CWinApp
{
public:
	CMSNLoginApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSNLoginApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMSNLoginApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	private:
		CMSNLoginDlg *m_pMSNLoginWnd;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSNLOGIN_H__BFADC3E3_B803_41F1_B28B_4030A05EA611__INCLUDED_)
