//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicGroup.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库群组框定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_GROUP_H_
#define _MAGICUI_GROUP_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MagicGroup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMagicGroup window
namespace GUI
{
class GUI_EXT_CLASS CMagicGroup : public CStatic
{
	DECLARE_DYNCREATE(CMagicGroup)
// Construction
public:
	CMagicGroup();
	//重载创建函数
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	//自动加载(即绑定CStatic类)
	BOOL AutoLoad(UINT nID, CWnd* pParent);

// Attributes
public:
	//设字体颜色
	void SetTextColor(COLORREF textColor);
	//设置字体
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//对齐方式
	void SetAlign(UINT nAlign);

	//获取要创建区域的父窗口背景
	void GetBackgndMask();

// Operations
public:
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
private:
	//绘普通位图
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicGroup)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMagicGroup();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicGroup)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bVisible;//控件可视
	BOOL m_bEnable;//控件可用
	
	COLORREF m_textColor;//字体颜色
	CFont m_font;//字体样式
	UINT m_nAlign;//对齐方式
	CSize m_szText;//文本大小

	CBitmap m_backgndMask;//掩图

	UINT m_nID;//本按钮ID
	CWnd* m_pWnd;//父窗口指针
};

}

#endif // _MAGICUI_GROUP_H_
