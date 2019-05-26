//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicText.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库文本定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_TEXT_H_
#define _MAGICUI_TEXT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//显示样式
#define PS_FIXSIZE	1
#define PS_AUTOSIZE	2
#define PS_STRETCH	4
#define PS_BORDER	8
#define PS_SCROLL	16
/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicText : public CStatic
{
	DECLARE_DYNCREATE(CMagicText)
// Construction
public:
	CMagicText();
	//重载创建函数
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	//自动加载(即绑定CStatic类)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
	//设字体颜色
	void SetTextColor(COLORREF textColor);
	void SetTextColor(COLORREF TextColor,COLORREF TextColorFocus,
				COLORREF TextColorSelected,COLORREF TextColorDisabled);
	//设边框颜色
	void SetBorderColor(COLORREF borderColor);
	void SetBorderColor(COLORREF borderColor,COLORREF borderColorFocus,
				COLORREF borderColorSelected,COLORREF borderColorDisabled);
	//设置字体
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);

	//对齐方式
	void SetAlign(UINT nAlign);

	//设置粗体
	void SetBold(BOOL bBold,BOOL bBoldFocus,BOOL bBoldSelected,BOOL bBoldDisabled);
	//设置斜体
	void SetItalic(BOOL bItalic,BOOL bItalicFocus,BOOL bItalicSelected,BOOL bItalicDisabled);
	//设置下划线
	void SetUnderline(BOOL bUnderline,BOOL bUnderlineFocus,BOOL bUnderlineSelected,BOOL bUnderlineDisabled);
	//设置删除线
	void SetStrikeOut(BOOL bStrikeOut,BOOL bStrikeOutFocus,BOOL bStrikeOutSelected,BOOL bStrikeOutDisabled);

	//获取要创建区域的父窗口背景
	void GetBackgndMask();

	//设光标
	void SetCursor(HCURSOR hCursor);
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
	//{{AFX_VIRTUAL(CMagicText)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	//设置显示样式
	void SetStyle(UINT nStyle);
	virtual ~CMagicText();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicText)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //鼠标移出

	DECLARE_MESSAGE_MAP()
private:
	//字体颜色
	COLORREF m_textColor;
	COLORREF m_textColorFocus;
	COLORREF m_textColorSelected;
	COLORREF m_textColorDisabled;
	//边框颜色
	COLORREF m_borderColor;
	COLORREF m_borderColorFocus;
	COLORREF m_borderColorSelected;
	COLORREF m_borderColorDisabled;
	//粗体
	BOOL m_bBold;
	BOOL m_bBoldFocus;
	BOOL m_bBoldSelected;
	BOOL m_bBoldDisabled;
	//斜体
	BOOL m_bItalic;
	BOOL m_bItalicFocus;
	BOOL m_bItalicSelected;
	BOOL m_bItalicDisabled;
	//下划线
	BOOL m_bUnderline;
	BOOL m_bUnderlineFocus;
	BOOL m_bUnderlineSelected;
	BOOL m_bUnderlineDisabled;
	//删除线
	BOOL m_bStrikeOut;
	BOOL m_bStrikeOutFocus;
	BOOL m_bStrikeOutSelected;
	BOOL m_bStrikeOutDisabled;

	//选择显示
	COLORREF m_borderColorShow;
	COLORREF m_textColorShow;
	BOOL m_bBoldShow;
	BOOL m_bItalicShow;
	BOOL m_bUnderlineShow;
	BOOL m_bStrikeOutShow;

	int m_nFontSize;//字体大小
	CString m_strFontName;//字体名称
	UINT m_nAlign;//对齐方式

	UINT m_nStyle;//样式
	CBitmap m_backgndMask;//掩图

	BOOL m_bVisible;//控件可视
	BOOL m_bEnable;//控件可用
	BOOL m_bMouseOn;//鼠标在其上
	BOOL m_bMouseDown;//鼠标按下
	HCURSOR m_hCursor;

	UINT m_nID;//本按钮ID
	CWnd* m_pWnd;//父窗口指针
};

}

#endif //_MAGICUI_TEXT_H_
