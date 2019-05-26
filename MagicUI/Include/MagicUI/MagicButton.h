//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicButton.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库按钮定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_BUTTON_H_
#define _MAGICUI_BUTTON_H_

#if _MSC_VER > 1000
#pragma once
#endif

//显示样式
#define BS_CLICK	0	//点弹式(每次点击都会弹起)
#define BS_PRESS	1	//按压式(每次点击切换于弹起、压下两种状态)

//绘图模式
#define DRAW_MODE_COLOR		0	//绘颜色
#define DRAW_MODE_BITMAP	1	//绘位图(BMP)
#define DRAW_MODE_IMAGE		2	//绘GDI+图(BMP,GIF,JPEG,PNG,TIFF,EMF)

//按钮状态图索引
#define INDEX_NORMAL		0	//常规
#define INDEX_FOCUS			1	//聚焦
#define INDEX_SELECTED		2	//按下
#define INDEX_DISABLED		3	//失效

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicButton : public CButton
{
	DECLARE_DYNCREATE(CMagicButton)
// Construction
public:
	CMagicButton();
	//重载创建函数
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,
				const RECT& rect, CWnd* pParentWnd, UINT nID);
	//自动加载(即绑定CButton类按钮)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
	//设背景色
	void SetBackColor(COLORREF backColor);
	void SetBackColor(COLORREF backColor,COLORREF backColorFocus,
				COLORREF backColorSelected,COLORREF backColorDisabled);
	//设前景色
	void SetForeColor(COLORREF foreColor);
	void SetForeColor(COLORREF foreColor,COLORREF foreColorFocus,
				COLORREF foreColorSelected,COLORREF foreColorDisabled);
	//设背景图
	void SetBitmap(CBitmap &bitmap);
	void SetBitmap(UINT nResID);
	void SetBitmap(LPCTSTR lpszFileName);
	void SetBitmap(HBITMAP hBitmap);
	//GDI+背景图
	void SetImage(LPCTSTR lpszFileName);

	//获取要创建区域的父窗口背景
	void GetBackgndMask();
	//设置屏蔽色
	void SetMaskColor(COLORREF color);
	//设光标
	void SetCursor(HCURSOR hCursor);
	//设边框
	void SetBorder(BOOL bBorder);
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

// Operations
private:
	//绘GDI+图
	void DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,int nIndex);
	//绘透明位图
	void DrawTransparentBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp,
										 COLORREF maskColor);
	//绘普通位图
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
	//绘颜色
	void DrawColor(CDC *pDC,CRect rect,COLORREF color);
	//拆分位图(将按钮背景图拆分成四幅状态图)
	void DivideBitmap();

public:
	BOOL EnableWindow(BOOL bEnable=TRUE);
	BOOL GetEnable();
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicButton)
	//}}AFX_VIRTUAL

	//重载DrawItem函数
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	void SetStyle(UINT nStyle);
	virtual ~CMagicButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //鼠标移出

	DECLARE_MESSAGE_MAP()
private:
	//前景色
	COLORREF m_foreColor;
	COLORREF m_foreColorFocus;
	COLORREF m_foreColorSelected;
	COLORREF m_foreColorDisabled;
	//背景色
	COLORREF m_backColor;
	COLORREF m_backColorFocus;
	COLORREF m_backColorSelected;
	COLORREF m_backColorDisabled;
	//背景图
	CBitmap m_background;
	CBitmap m_backgroundFocus;
	CBitmap m_backgroundSelected;
	CBitmap m_backgroundDisabled;
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

	int m_nFontSize;		//字体大小
	CString m_strFontName;	//字体名称
	UINT m_nAlign;			//对齐方式

	CBitmap m_backgndFull;			//全图
	CBitmap m_backgndMask;			//掩图
	TCHAR m_backgndPath[_MAX_PATH];	//GDI+背景路径

	HCURSOR m_hCursor;	//光标句柄

	BOOL m_bVisible;	//控件可视
	BOOL m_bEnable;		//控件可用
	BOOL m_bMouseOn;	//鼠标是否在上面
	BOOL m_bPressed;	//是否已被按下
	BOOL m_bBorder;		//是否有边框
	BOOL m_bMask;		//是否屏蔽某色
	COLORREF m_maskColor;//屏蔽色

	UINT m_nDrawMode;	//绘图模式
	UINT m_nStyle;		//显示样式

	UINT m_nID;		//本按钮ID
	CWnd* m_pWnd;	//父窗口指针
};

}

#endif //_MAGICUI_BUTTON_H_
