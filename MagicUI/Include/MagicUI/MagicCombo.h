//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicCombo.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库下拉框定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_COMBO_H_
#define _MAGICUI_COMBO_H_

#if _MSC_VER > 1000
#pragma once
#endif

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicCombo : public CComboBox
{
	DECLARE_DYNCREATE(CMagicCombo)
// Construction
public:
	CMagicCombo();
	//重载创建函数
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID);
	//自动加载(即绑定CComboBox类按钮)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
	//设背景色
	void SetBackColor(COLORREF backColor);
	void SetBackColor(COLORREF backColor,COLORREF backColorHover,COLORREF backColorDisabled);
	//设字体颜色
	void SetTextColor(COLORREF textColor);
	void SetTextColor(COLORREF TextColor,COLORREF TextColorHover,COLORREF TextColorDisabled);
	//设边框颜色
	void SetBorderColor(COLORREF borderColor);
	//设按钮背景颜色
	void SetBtnColor(COLORREF btnColor);

	//获取要创建区域的父窗口背景
	void GetBackgndMask();
	//设光标
	void SetCursor(HCURSOR hCursor);
	//设边框
	//设置字体
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//对齐方式
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
	//{{AFX_VIRTUAL(CMagicCombo)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

	int AddString(LPCTSTR lpszString);
	int InsertString(int nIndex, LPCTSTR lpszString);
	int DeleteString(UINT nIndex);
	void ResetContent();
// Implementation
public:
	virtual ~CMagicCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicCombo)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetfocus();
	afx_msg void OnKillfocus();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //鼠标移出

	DECLARE_MESSAGE_MAP()
private:
	//背景色
	COLORREF m_backColor;
	COLORREF m_backColorHover;
	COLORREF m_backColorDisabled;

	//文本色
	COLORREF m_textColor;
	COLORREF m_textColorHover;
	COLORREF m_textColorDisabled;

	//边框色
	COLORREF m_borderColor;
	CBrush m_brBkgnd;

	//按钮背景色
	COLORREF m_btnColor;

	BOOL m_bBold;//粗体
	BOOL m_bItalic;//斜体
	BOOL m_bUnderline;//下划线
	BOOL m_bStrikeOut;//删除线

	int m_nFontSize;		//字体大小
	CString m_strFontName;	//字体名称

	HCURSOR m_hCursor;		//光标句柄
	CBitmap m_backgndMask;	//掩图

	BOOL m_bVisible;//控件可视
	BOOL m_bEnable;	//控件可用
	BOOL m_bHover;	//悬停
	BOOL m_bFocus;	//聚焦

	CStringArray m_strAry;
	CFont m_font;

	UINT m_nID;		//本按钮ID
	CWnd* m_pWnd;	//父窗口指针
};

}

#endif //_MAGICUI_COMBO_H_
