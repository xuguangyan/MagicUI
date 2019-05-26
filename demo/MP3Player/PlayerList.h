#if !defined(AFX_PLAYERLIST_H__3AB51228_12E7_481E_90C9_C317672EEFAA__INCLUDED_)
#define AFX_PLAYERLIST_H__3AB51228_12E7_481E_90C9_C317672EEFAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayerList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayerList dialog

class CPlayerList : public CMagicWnd
{
	DECLARE_DYNCREATE(CPlayerList)
// Construction
public:
	CPlayerList();
	~CPlayerList();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayerList)
		// NOTE: the ClassWizard will add member functions here
	void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYERLIST_H__3AB51228_12E7_481E_90C9_C317672EEFAA__INCLUDED_)
