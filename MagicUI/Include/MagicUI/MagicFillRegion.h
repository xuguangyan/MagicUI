//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicFillRegion.h											[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库填充区定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_FILLREGION_H_
#define _MAGICUI_FILLREGION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MagicFillRegion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMagicFillRegion window
namespace GUI
{
class GUI_EXT_CLASS CMagicFillRegion : public CStatic
{
	DECLARE_DYNCREATE(CMagicFillRegion)
// Construction
public:
	CMagicFillRegion();
	//重载创建函数
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);

// Attributes
public:
	//设背景颜色
	void SetBackColor(COLORREF backColor);
	//设边框颜色
	void SetBorderColor(COLORREF borderColor);
	//设边框宽度
	void SetBorderWidth(int nWidth);
	//设圆角大小
	void SetCorner(int nSize);
	//获取要创建区域的父窗口背景
	void GetBackgndMask();
	//设置窗体透明
	void SetAlpha(int alpha);

// Operations
public:
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
private:
	//绘普通位图
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicFillRegion)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMagicFillRegion();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicFillRegion)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bVisible;//控件可视
	CBitmap m_backgndMask;//掩图

	int m_nAlpha;			//透明度
	COLORREF m_backColor;	//背景色
	COLORREF m_borderColor;	//边框色
	int m_borderWidth;		//边框宽
	int m_nCorner;			//圆角大小

	UINT m_nID;//本按钮ID
	CWnd* m_pWnd;//父窗口指针
};

}

#endif // _MAGICUI_FILLREGION_H_
