//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicRadio.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库单选按钮定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_RADIO_H_
#define _MAGICUI_RADIO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//绘图模式
#define DRAW_MODE_COLOR		0	//绘颜色
#define DRAW_MODE_BITMAP	1	//绘位图(BMP)
#define DRAW_MODE_IMAGE		2	//绘GDI+图(BMP,GIF,JPEG,PNG,TIFF,EMF)

//按钮状态图索引
#define INDEX_NORMAL		0	//常规
#define INDEX_FOCUS			1	//聚焦
#define INDEX_SELECTED		2	//按下
#define INDEX_DISABLED		3	//失效
#define INDEX_HOOK			4	//钩子

#define UM_RADIOBOX WM_USER+100

/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicRadio : public CButton
{
	DECLARE_DYNCREATE(CMagicRadio)
// Construction
public:
	CMagicRadio();
	//重载创建函数
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,
				const RECT& rect, CWnd* pParentWnd, UINT nID);
	//自动加载(即绑定CButton类按钮)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
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
	//设置字体
	void SetFont(int nFontSize,CString strFontName,BOOL bBold=FALSE,BOOL bItalic=FALSE,
					BOOL bUnderline=FALSE,BOOL bStrikeOut=FALSE);
	//对齐方式
	void SetAlign(UINT nAlign);

	//设置选中状态
	void SetSelect(BOOL bSelect=TRUE);
	//获取选中状态
	BOOL GetSelect();

	//设置组号
	void SetGroupID(UINT nGroupID);
	//获取组号
	UINT GetGroupID();

// Operations
private:
	//绘GDI+图
	void DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,int nIndex);
	//绘透明位图
	void DrawTransparentBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp,COLORREF maskColor);
	//绘普通位图
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
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
	virtual ~CMagicRadio();

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
	HCURSOR m_hCursor;//光标句柄

	COLORREF m_foreColor;//正常时前景色
	COLORREF m_foreColorFocus;//聚焦时前景色
	COLORREF m_foreColorSelected;//选中时前景色
	COLORREF m_foreColorDisabled;//失效时前景色

	CBitmap m_background;//正常时背景图
	CBitmap m_backgroundFocus;//聚焦时背景图
	CBitmap m_backgroundSelected;//选中时背景图
	CBitmap m_backgroundDisabled;//失效时背景图
	CBitmap m_backgroundHook;//钩子背景图

	CBitmap m_backgndFull;//全图
	CBitmap m_backgndMask;//掩图
	int m_imgWidth;//CheckBox宽(不含文字域)

	int m_nFontSize;//字体大小
	CString m_strFontName;//字体名称
	BOOL m_bBold;//粗体
	BOOL m_bItalic;//斜体
	BOOL m_bUnderline;//下划线
	BOOL m_bStrikeOut;//删除线
	UINT m_nAlign;//对齐方式

	BOOL m_bVisible;	//控件可视
	BOOL m_bEnable;		//控件可用
	BOOL m_bMouseOn;//鼠标是否在上面
	BOOL m_bSelected;//是否已被钩选
	UINT m_nGroupID;//组号
	COLORREF m_maskColor;//屏蔽色
	UINT m_nDrawMode;//绘图模式
	TCHAR m_backgndPath[_MAX_PATH];//GDI+背景路径

	UINT m_nID;//本按钮ID
	CWnd* m_pWnd;//父窗口指针
};

}

#endif //_MAGICUI_RADIO_H_
