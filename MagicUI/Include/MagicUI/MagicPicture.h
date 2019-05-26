//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicPicture.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库图片定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_PICTURE_H_
#define _MAGICUI_PICTURE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//显示样式
#define PS_FIXSIZE	1
#define PS_AUTOSIZE	2
#define PS_STRETCH	4
#define PS_BORDER	8
#define PS_SCROLL	16

//绘图模式
#define DRAW_MODE_COLOR		0	//绘颜色
#define DRAW_MODE_BITMAP	1	//绘位图(BMP)
#define DRAW_MODE_IMAGE		2	//绘GDI+图(BMP,GIF,JPEG,PNG,TIFF,EMF)
/////////////////////////////////////////////////////////////////////////////
namespace GUI
{
class GUI_EXT_CLASS CMagicPicture : public CStatic
{
	DECLARE_DYNCREATE(CMagicPicture)
// Construction
public:
	CMagicPicture();
	//重载创建函数
	BOOL Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	//自动加载(即绑定CStatic类)
	BOOL AutoLoad(UINT nID, CWnd* pParent);
// Attributes
public:
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

// Operations
private:
	//绘GDI+图
	void DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,CRect rc);
	//绘透明位图
	void DrawTransparentBitmap(CDC *pDC,CRect rect,
									  CBitmap &foreBmp,COLORREF maskColor,CRect rc);
	//绘普通位图
	void DrawOriginalBitmap(CDC *pDC,CRect rect,CBitmap &foreBmp);
public:
	BOOL EnableWindow(BOOL bEnable=TRUE);
	BOOL GetEnable();
	BOOL ShowWindow(int nCmdShow);
	BOOL GetVisible();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicPicture)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	//设置显示样式
	void SetStyle(UINT nStyle);
	virtual ~CMagicPicture();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMagicPicture)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); //鼠标移出

	DECLARE_MESSAGE_MAP()
private:
	HCURSOR m_hCursor;//光标句柄

	CBitmap m_background;//位图
	CBitmap m_backgndMask;//掩图
	UINT m_nDrawMode;//绘图模式
	TCHAR m_backgndPath[_MAX_PATH];

	UINT m_nStyle;//样式

	BOOL m_bMask;//是否屏蔽某色
	COLORREF m_maskColor;//屏蔽色

	UINT m_nID;//本按钮ID
	CWnd* m_pWnd;//父窗口指针

	CScrollBar m_HScroll,m_VScroll;//滚动条
	int m_xoffset,m_yoffset;//图片相对图片框偏移量
	int m_xorign,m_yorign;//鼠标相对图片框偏移量
	int m_xMax,m_yMax;//滚动条最大值
	
	BOOL m_bVisible;//控件可视
	BOOL m_bEnable;//控件可用
	BOOL m_bMouseDown;//鼠标按下标志
};

}

#endif //_MAGICUI_PICTURE_H_
