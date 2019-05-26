//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicEdit.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库编辑框定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_EDIT_H_
#define _MAGICUI_EDIT_H_

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicEdit : public CEdit
{
	DECLARE_DYNCREATE(CMagicEdit)
// Construction
public:
	CMagicEdit();
	//重载创建函数
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
	//自动加载(即绑定CEdit类)
	BOOL AutoLoad(UINT nID, CWnd* pParent);

// Attributes
public:
	//设字体颜色
	void SetTextColor(COLORREF textColor);
	void SetTextColor(COLORREF textColor,COLORREF textColorHover,
				COLORREF textColorFocus,COLORREF textColorDisabled);
	//设背景颜色
	void SetBackColor(COLORREF backColor);
	void SetBackColor(COLORREF backColor,COLORREF backColorHover,
				COLORREF backColorFocus,COLORREF backColorDisabled);
	//设边框颜色
	void SetBorderColor(COLORREF borderColor);
	void SetBorderColor(COLORREF borderColor,COLORREF borderColorHover,
				COLORREF borderColorFocus,COLORREF borderColorDisabled);
	//设置字体
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//对齐方式
	void SetAlign(UINT nAlign);

	//获取要创建区域的父窗口背景
	void GetBackgndMask();

	//设光标
	void SetCursor(HCURSOR hCursor);

	void SetPassword(BOOL bPassword=TRUE);
// Operations

private:
	//绘普通位图
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
public:
	BOOL EnableWindow(BOOL bEnable=TRUE);
	BOOL GetEnable();
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicEdit)
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CMagicEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	//字体颜色
	COLORREF m_textColor;
	COLORREF m_textColorFocus;
	COLORREF m_textColorHover;
	COLORREF m_textColorDisabled;

	//背景颜色
	COLORREF m_backColor;
	COLORREF m_backColorFocus;
	COLORREF m_backColorHover;
	COLORREF m_backColorDisabled;

	//边框颜色
	COLORREF m_borderColor;
	COLORREF m_borderColorFocus;
	COLORREF m_borderColorHover;
	COLORREF m_borderColorDisabled;

	CBrush m_brBkgnd;//背景画刷
	CBitmap m_backgndMask;//掩图
	HCURSOR m_hCursor;//光标句柄

	BOOL m_bVisible;//可视
	BOOL m_bEnable;//可用
	BOOL m_bHover;//悬停
	BOOL m_bFocus;//聚焦

	CString m_strText;
	CFont m_font;

	UINT m_nID;//本按钮ID
	CWnd* m_pWnd;//父窗口指针
};

}

#endif //_MAGICUI_EDIT_H_
