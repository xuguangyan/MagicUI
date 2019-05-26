// MP3PlayerDlg.h : header file
//

#if !defined(AFX_MP3PLAYERDLG_H__8A3638F0_7389_4FC2_8185_D74B86828DB8__INCLUDED_)
#define AFX_MP3PLAYERDLG_H__8A3638F0_7389_4FC2_8185_D74B86828DB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMP3Player dialog

class CPlayerList;
class CMP3Player : public CMagicWnd
{
	DECLARE_DYNCREATE(CMP3Player)
// Construction
public:
	CMP3Player();	// standard constructor
	~CMP3Player();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMP3Player)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnPlayList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		CPlayerList *m_pListWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MP3PLAYERDLG_H__8A3638F0_7389_4FC2_8185_D74B86828DB8__INCLUDED_)
