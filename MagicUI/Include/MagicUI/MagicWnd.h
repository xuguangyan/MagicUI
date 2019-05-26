//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicWnd.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库自绘窗口定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_WINDOW_H_
#define _MAGICUI_WINDOW_H_

#if _MSC_VER > 1300
#pragma once
#endif

#include <afxwin.h>
#include "DataDefine.h"

#include "resource.h"		// main symbols
#include "MagicButton.h"
#include "MagicCheck.h"
#include "MagicRadio.h"
#include "MagicPicture.h"
#include "MagicText.h"
#include "MagicEdit.h"
#include "MagicCombo.h"
#include "MagicGroup.h"
#include "MagicFillRegion.h"

//控件类型
#define MAGICUI_WND			0
#define MAGICUI_BUTTON		1
#define MAGICUI_CHECK		2
#define MAGICUI_RADIO		3
#define MAGICUI_PICTURE		4
#define MAGICUI_TEXT		5
#define MAGICUI_EDIT		6
#define MAGICUI_COMBO		7
#define MAGICUI_GROUP		8
#define MAGICUI_FILLREGION	9

#define UM_RADIOBOX WM_USER+100

/////////////////////////////////////////////////////////////////////////////
class CMarkup;
namespace GUI
{
class GUI_EXT_CLASS CMagicWnd : public CWnd
{
	DECLARE_DYNCREATE(CMagicWnd)
public:
	//控件信息
	typedef struct ControlInfo
	{
		CString strName;
		UINT nType;
		CWnd *pWnd;
		UINT nCmd;
	}CTRL_INFO;
	//按钮样式
	typedef struct StyleButton
	{
		//文本颜色
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;

		int nFontSize;					//字体大小
		TCHAR szFontName[LF_FACESIZE];	//字体名称
		UINT nAlign;					//对齐方式

		//粗体
		BOOL bBold;
		BOOL bBoldFocus;
		BOOL bBoldSelected;
		BOOL bBoldDisabled;
		//斜体
		BOOL bItalic;
		BOOL bItalicFocus;
		BOOL bItalicSelected;
		BOOL bItalicDisabled;
		//下划线
		BOOL bUnderline;
		BOOL bUnderlineFocus;
		BOOL bUnderlineSelected;
		BOOL bUnderlineDisabled;
		//删除线
		BOOL bStrikeOut;
		BOOL bStrikeOutFocus;
		BOOL bStrikeOutSelected;
		BOOL bStrikeOutDisabled;

		HCURSOR hCursor;	//光标
	}STYLE_BUTTON;
	//复选按钮样式
	typedef struct StyleCheck
	{
		//文本颜色
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;

		int nFontSize;					//字体大小
		TCHAR szFontName[LF_FACESIZE];	//字体名称
		UINT nAlign;					//对齐方式

		BOOL bBold;			//粗体
		BOOL bItalic;		//斜体
		BOOL bUnderline;	//下划线
		BOOL bStrikeOut;	//删除线

		//图片路径
		TCHAR szBackGround[_MAX_FNAME];
		TCHAR szImage[_MAX_FNAME];

		HCURSOR hCursor;	//光标
	}STYLE_CHECK;
	//单选按钮样式
	typedef struct StyleRadio
	{
		//文本颜色
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;

		int nFontSize;					//字体大小
		TCHAR szFontName[LF_FACESIZE];	//字体名称
		UINT nAlign;					//对齐方式

		BOOL bBold;			//粗体
		BOOL bItalic;		//斜体
		BOOL bUnderline;	//下划线
		BOOL bStrikeOut;	//删除线

		//图片路径
		TCHAR szBackGround[_MAX_FNAME];
		TCHAR szImage[_MAX_FNAME];

		HCURSOR hCursor;//光标
	}STYLE_RADIO;
	//文本样式
	typedef struct StyleText
	{
		//文本颜色
		COLORREF textColor;
		COLORREF textColorFocus;
		COLORREF textColorSelected;
		COLORREF textColorDisabled;
		//边框颜色
		COLORREF borderColor;
		COLORREF borderColorFocus;
		COLORREF borderColorSelected;
		COLORREF borderColorDisabled;

		int nFontSize;					//字体大小
		TCHAR szFontName[LF_FACESIZE];	//字体名称
		UINT nAlign;					//对齐方式

		//粗体
		BOOL bBold;
		BOOL bBoldFocus;
		BOOL bBoldSelected;
		BOOL bBoldDisabled;
		//斜体
		BOOL bItalic;
		BOOL bItalicFocus;
		BOOL bItalicSelected;
		BOOL bItalicDisabled;
		//下划线
		BOOL bUnderline;
		BOOL bUnderlineFocus;
		BOOL bUnderlineSelected;
		BOOL bUnderlineDisabled;
		//删除线
		BOOL bStrikeOut;
		BOOL bStrikeOutFocus;
		BOOL bStrikeOutSelected;
		BOOL bStrikeOutDisabled;

		HCURSOR hCursor;	//光标
	}STYLE_TEXT;
	//编辑框样式
	typedef struct StyleEdit
	{
		//文本颜色
		COLORREF textColor;
		COLORREF textColorHover;
		COLORREF textColorFocus;
		COLORREF textColorDisabled;
		//背景颜色
		COLORREF backColor;
		COLORREF backColorHover;
		COLORREF backColorFocus;
		COLORREF backColorDisabled;
		//边框颜色
		COLORREF borderColor;
		COLORREF borderColorHover;
		COLORREF borderColorFocus;
		COLORREF borderColorDisabled;
		
		int nFontSize;					//字体大小
		TCHAR szFontName[LF_FACESIZE];	//字体名称
		UINT nAlign;					//对齐方式

		BOOL bBold;			//粗体
		BOOL bItalic;		//斜体
		BOOL bUnderline;	//下划线
		BOOL bStrikeOut;	//删除线

		BOOL bPassword;		//是否为密码框
		HCURSOR hCursor;	//光标
	}STYLE_EDIT;
	//组合框样式
	typedef struct StyleCombo
	{
		//文本颜色
		COLORREF textColor;
		COLORREF textColorHover;
		COLORREF textColorDisabled;
		//背景颜色
		COLORREF backColor;
		COLORREF backColorHover;
		COLORREF backColorDisabled;
		
		COLORREF borderColor;	//边框颜色
		COLORREF btnColor;		//按钮背景颜色

		int nFontSize;					//字体大小
		TCHAR szFontName[LF_FACESIZE];	//字体名称

		BOOL bBold;			//粗体
		BOOL bItalic;		//斜体
		BOOL bUnderline;	//下划线
		BOOL bStrikeOut;	//删除线

		HCURSOR hCursor;	//光标
	}STYLE_COMBO;
	//群组框样式
	typedef struct StyleGroup
	{
		COLORREF textColor;//文本颜色

		int nFontSize;					//字体大小
		TCHAR szFontName[LF_FACESIZE];	//字体名称
		UINT nAlign;					//对齐方式

		BOOL bBold;			//粗体
		BOOL bItalic;		//斜体
		BOOL bUnderline;	//下划线
		BOOL bStrikeOut;	//删除线
	}STYLE_GROUP;
	//填充区样式
	typedef struct StyleFillRegion
	{
		COLORREF backColor;		//背景颜色
		COLORREF borderColor;	//边框颜色
		int borderWidth;		//边框宽度
		int nCorner;			//圆角大小
		int nAlpha;				//透明度
	}STYLE_FILLREGION;
// Construction
public:
	CWnd* GetWndByName(CString strName);
	CMagicWnd();
	~CMagicWnd();
	// 创建窗口
	virtual BOOL Create(LPCTSTR szSkinPath,
						LPCTSTR szMainXml, 
						LPCTSTR szGlobalXml, 
						DWORD dwExStyle		= NULL,
						DWORD dwStyle		= WS_POPUP | WS_VISIBLE, 
						CWnd * parentWnd	= NULL);
	//初始化全局样式
	void InitGlobalStyle();
	//加载全局样式
	BOOL LoadGlobalStyle(LPCTSTR szSkinPath,LPCTSTR szGlobalXml);
	//装载皮肤
	BOOL LoadSkin(LPCTSTR szSkinPath,LPCTSTR szMainXml);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicWnd)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//重载显示窗口
	BOOL ShowWindow(int nCmdShow);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMagicWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcRButtonUp(UINT nHitTest,CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest,CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRestore();
	afx_msg void OnMove();
	afx_msg void OnSize();
	afx_msg void OnMiniMize();
	afx_msg void OnMaxiMize();
	afx_msg void OnClose();
	afx_msg void OnAbout();
	afx_msg void OnBtnMinimize();
	afx_msg void OnBtnMaximize();
	afx_msg void OnBtnClose();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//}}AFX_MSG
	LRESULT OnRadioBox(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	//设置系统菜单可用
	void EnableSysMenu(BOOL bRestor,BOOL bMove,BOOL bSize,BOOL bMini,BOOL bMaxi);
private:
	BOOL FindUserStyle(CString strLabel,CMarkup &xml);
	void ReadStyleGroup(STYLE_GROUP &sg,CMarkup xml);
	void ReadStyleRegion(STYLE_FILLREGION &sf,CMarkup xml);
	void ReadStyleCombo(STYLE_COMBO &sc,CMarkup xml);
	void ReadStyleEdit(STYLE_EDIT &se,CMarkup xml);
	void ReadStyleText(STYLE_TEXT &st,CMarkup xml);
	void ReadStyleCheck(STYLE_CHECK &sc,CMarkup xml);
	void ReadStyleRadio(STYLE_RADIO &sr,CMarkup xml);
	void ReadStyleButton(STYLE_BUTTON &sb,CMarkup xml);
	void SetRegion(CMarkup xml);
	void SetGroup(CMarkup xml);
	void SetComboBox(CMarkup xml);
	void SetEdit(CMarkup xml);
	void SetText(CMarkup xml);
	void SetCheckBox(CMarkup xml);
	void SetRadioBox(CMarkup xml);
	void SetPicture(CMarkup xml);
	void SetButton(CMarkup xml);
	void SetControl(CMarkup xml);
	BOOL SetWindow(CMarkup xml);
	CPoint m_ptWnd;				//窗口的位置(*)
	CSize m_szWnd;				//窗口的大小(*)
	BOOL m_bEnable;				//窗口是否激活
	BOOL m_bVisible;			//窗口是否可见
	CSize m_szMinSize;			//窗口的最小宽高
	CSize m_szMaxSize;			//窗口的最大宽高
	BOOL m_bFixSize;			//窗口是否固定大小
	BOOL m_bCanMove;			//窗口是否可以移动
	COLORREF m_backColor;		//窗口的背景色
	COLORREF m_borderColor;		//窗口的边框颜色
	COLORREF m_maskColor;		//边框背景图像使用的掩码色
	BOOL m_bUseMaskColor;		//是否定义掩码色
	UINT m_nMenuID;				//窗口的菜单资源的ID值
	CBitmap m_backGround;		//窗口的背景图像
	CBitmap	m_backgnd[8];		//拆分背景图像为四边四角
	CRect m_rcWindowBorder;		//窗口左上右下的边白

	CString m_strSkinPath;		//皮肤包路径
	CString	m_strMainXml;		//皮肤定义文件(*.xml)
	CString	m_strGlobalXml;		//全局样式文件(*.xml)
	CRect m_rcTitleBar;			//自定义标题栏
	CRect m_rcIcon;				//自定义图标
	COLORREF m_titleBarColor;	//标题栏颜色
	COLORREF m_iconColor;		//图标颜色
	CMenu m_sysMenu;			//系统菜单
	BOOL m_bMaximize;			//窗口最大化标志
	CMagicButton m_btnMin,m_btnMax,m_btnClose;	//系统按钮
	CSize m_szMin,m_szMax,m_szClose;			//按钮相对窗口右上角偏移
	BOOL m_bMinExist,m_bMaxExist,m_bCloseExist;	//系统按钮是否存在

	CArray<CTRL_INFO,CTRL_INFO> m_aryControl;//控件信息
	STYLE_BUTTON m_styleButton;		//按钮样式
	STYLE_CHECK m_styleCheck;		//复选按钮样式
	STYLE_RADIO m_styleRadio;		//单选按钮样式
	STYLE_TEXT m_styleText;			//文本样式
	STYLE_EDIT m_styleEdit;			//编辑框样式
	STYLE_COMBO m_styleCombo;		//组合框样式
	STYLE_GROUP m_styleGroup;		//群组框样式
	STYLE_FILLREGION m_styleRegion;	//填充区样式

	CToolTipCtrl m_toolTip;//工具提示
};

}

#endif //_MAGICUI_WINDOW_H_
