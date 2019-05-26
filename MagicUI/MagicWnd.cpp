//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicWnd.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库自绘窗口实现
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Include/MagicUI/MagicWnd.h"

#include "Markup.h"
#include "Common.h"
#include "Attrib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicWnd,CWnd);

CMagicWnd::CMagicWnd()
{
	m_ptWnd=CPoint(100,100);	//窗口的位置(*)
	m_szWnd=CSize(300,200);		//窗口的大小(*)
	m_bEnable=TRUE;				//窗口是否激活
	m_bVisible=TRUE;			//窗口是否可见
	m_szMinSize=CSize(112,25);	//窗口的最小宽高
	m_szMaxSize=CSize(0,0);		//窗口的最大宽高
	m_bFixSize=FALSE;			//窗口是否固定大小
	m_bCanMove=TRUE;			//窗口是否可以移动
	m_backColor=RGB(147,169,213);				//窗口的背景色
	m_maskColor=RGB(255,0,255);					//边框背景图像使用的掩码色
	m_bUseMaskColor=TRUE;		//是否定义掩码色
	m_nMenuID=NULL;				//窗口的菜单资源的ID值
	m_rcWindowBorder=CRect(0,0,0,0);		//窗口左上右下的边白

	m_strSkinPath="";					//皮肤包路径
	m_strMainXml="";					//皮肤定义文件(*.xml)
	m_strGlobalXml="";					//全局样式文件(*.xml)
	m_rcTitleBar=CRect(0,0,300,18);		//自定义标题栏
	m_titleBarColor=RGB(6,105,178);		//标题栏颜色
	m_rcIcon=CRect(1,1,16,16);;			//自定义
	m_iconColor=RGB(255,249,157);		//图标颜色	
	m_szMin=CSize(1+16*3,1);			//按钮相对窗口右上角偏移
	m_szMax=CSize(1+16*2,1);			//按钮相对窗口右上角偏移
	m_szClose=CSize(1+16*1,1);			//按钮相对窗口右上角偏移
	m_bMaximize=FALSE;					//窗口最大化标志
	m_bMinExist=FALSE;					//存在最小化按钮
	m_bMaxExist=FALSE;					//存在最大化按钮
	m_bCloseExist=FALSE;				//存在关闭按钮
}

CMagicWnd::~CMagicWnd()
{
	for(int i=0;i<m_aryControl.GetSize();i++)
	{
		CTRL_INFO ctrlInfo;
		ctrlInfo=m_aryControl.GetAt(i);
		delete ctrlInfo.pWnd;
	}
}

BEGIN_MESSAGE_MAP(CMagicWnd, CWnd)
	//{{AFX_MSG_MAP(CMagicWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCRBUTTONUP()
	ON_WM_NCLBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDM_RESTORE, OnRestore)
	ON_COMMAND(IDM_MOVE, OnMove)
	ON_COMMAND(IDM_SIZE, OnSize)
	ON_COMMAND(IDM_MINIMIZE, OnMiniMize)
	ON_COMMAND(IDM_MAXIMIZE, OnMaxiMize)
	ON_COMMAND(IDM_CLOSE, OnClose)
	ON_COMMAND(IDM_ABOUTBOX, OnAbout)
	ON_BN_CLICKED(IDC_BTN_MINIMIZE, OnBtnMinimize)
	ON_BN_CLICKED(IDC_BTN_MAXIMIZE, OnBtnMaximize)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_RADIOBOX,OnRadioBox)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicWnd message handlers

//创建窗口
BOOL CMagicWnd::Create(LPCTSTR szSkinPath,LPCTSTR szMainXml,LPCTSTR szGlobalXml,
					   DWORD dwExStyle,DWORD dwStyle,CWnd * parentWnd)
{
	m_strSkinPath=szSkinPath;
	m_strMainXml=szMainXml;
	m_strGlobalXml=szGlobalXml;

	//去掉系统标题栏
	dwStyle&=~WS_CAPTION;

	//判断FixSize
	if(m_bFixSize)
	{
		dwStyle&=~WS_THICKFRAME;
		dwStyle|=WS_DLGFRAME;
	}
	else
	{
		dwStyle|=WS_THICKFRAME;
		dwStyle&=~WS_DLGFRAME;
	}

	//窗口类
	WNDCLASS wndcls;
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	wndcls.hbrBackground=NULL;
	wndcls.hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wndcls.hIcon=AfxGetApp()->LoadIcon(IDC_APP_MAGIC);
	wndcls.hInstance=AfxGetInstanceHandle();
	wndcls.lpfnWndProc=::DefWindowProc;
	wndcls.lpszClassName="MagicWndCls";
	wndcls.lpszMenuName=NULL;
	wndcls.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	//创建窗口
	HWND hWnd=NULL;
	if(parentWnd) hWnd=parentWnd->m_hWnd;
	return CWnd::CreateEx(dwExStyle,"MagicWndCls",AfxGetAppName(),dwStyle,m_ptWnd.x,m_ptWnd.y,
		m_szWnd.cx,m_szWnd.cy,hWnd,NULL,NULL);
}

int CMagicWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	//创建系统菜单,添加About项
 	m_sysMenu.LoadMenu(IDR_SYSMENU);
 	CMenu *pSysMenu=m_sysMenu.GetSubMenu(0);
	if (pSysMenu != NULL)
 	{
 		CString strAboutMenu;
 		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	//工具提示
	m_toolTip.Create(this);

	//初始化全局样式
	InitGlobalStyle();

	//加载全局样式
	LoadGlobalStyle(m_strSkinPath,m_strGlobalXml);
	//装载皮肤
	if(LoadSkin(m_strSkinPath,m_strMainXml))
		return 0;

	//创建系统按钮
	int cx=m_szWnd.cx;
	CRect rcBtnMin=CRect(cx-m_szMin.cx,  m_szMin.cy,  cx-m_szMin.cx+16,  m_szMin.cy+16);
	CRect rcBtnMax=CRect(cx-m_szMax.cx,  m_szMax.cy,  cx-m_szMax.cx+16,  m_szMax.cy+16);
	CRect rcClose= CRect(cx-m_szClose.cx,m_szClose.cy,cx-m_szClose.cx+16,m_szClose.cy+16);

	m_btnMin.Create("-",WS_CHILD|WS_VISIBLE,rcBtnMin,this,IDC_BTN_MINIMIZE);
	m_btnMin.SetForeColor(RGB(245,159,188),RGB(255,255,255),RGB(208,208,0),-1);
	m_btnMin.SetBackColor(RGB(63,188,239),RGB(141,207,224),RGB(147,169,213),-1);
	m_btnMax.Create("+",WS_CHILD|WS_VISIBLE,rcBtnMax,this,IDC_BTN_MAXIMIZE);
	m_btnMax.SetForeColor(RGB(245,159,188),RGB(255,255,255),RGB(208,208,0),-1);
	m_btnMax.SetBackColor(RGB(63,188,239),RGB(141,207,224),RGB(147,169,213),-1);
	m_btnClose.Create("x",WS_CHILD|WS_VISIBLE,rcClose,this,IDC_BTN_CLOSE);
	m_btnClose.SetForeColor(RGB(245,159,188),RGB(255,255,255),RGB(208,208,0),-1);
	m_btnClose.SetBackColor(RGB(63,188,239),RGB(141,207,224),RGB(147,169,213),-1);

	m_toolTip.AddTool(&m_btnMin,"最小化");
	m_toolTip.AddTool(&m_btnMax,"最大化");
	m_toolTip.AddTool(&m_btnClose,"关闭");

	m_bMinExist=TRUE;
	m_bMaxExist=TRUE;
	m_bCloseExist=TRUE;

	return 0;
}

//处理系统菜单命令
void CMagicWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if(nID==SC_MOVE||nID==0xF012)
	{
		if(!m_bCanMove)
			return ;
	}
	CWnd::OnSysCommand(nID, lParam);
}

//调整控件位置
void CMagicWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_rcTitleBar.right=cx;
	m_szWnd.cx=cx;
	m_szWnd.cy=cy;

	if(m_bMinExist)
		m_btnMin.SetWindowPos(NULL,cx-m_szMin.cx,m_szMin.cy,0,0,SWP_NOZORDER|SWP_NOSIZE);
	if(m_bMaxExist)
		m_btnMax.SetWindowPos(NULL,cx-m_szMax.cx,m_szMax.cy,0,0,SWP_NOZORDER|SWP_NOSIZE);
	if(m_bCloseExist)
		m_btnClose.SetWindowPos(NULL,cx-m_szClose.cx,m_szClose.cy,0,0,SWP_NOZORDER|SWP_NOSIZE);
}

//判断HitTest区域
LRESULT CMagicWnd::OnNcHitTest(CPoint point)
{
	CRect rc;

	//系统图标区
	rc=m_rcIcon;
	ClientToScreen(&rc);
	if(rc.PtInRect(point))
		return HTSYSMENU;

	//标题栏区
	rc=m_rcTitleBar;
	ClientToScreen(&rc);
	if(rc.PtInRect(point))
		return HTCAPTION;

	return CWnd::OnNcHitTest(point);
}

//右键单击标题栏弹出菜单
void CMagicWnd::OnNcRButtonUp(UINT nHitTest,CPoint point)
{
	switch(nHitTest)
	{
	case HTSYSMENU:
	case HTCAPTION:
		CMenu *pSysMenu=m_sysMenu.GetSubMenu(0);
		if(pSysMenu != NULL)
			pSysMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
		break;
	}

	CWnd::OnNcRButtonUp(nHitTest,point);
}

//左键单击系统图标弹出菜单
void CMagicWnd::OnNcLButtonUp(UINT nHitTest,CPoint point)
{
	switch(nHitTest)
	{
	case HTSYSMENU:
		CMenu *pSysMenu=m_sysMenu.GetSubMenu(0);
		if(pSysMenu != NULL)
			pSysMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
		break;
	}

	CWnd::OnNcLButtonUp(nHitTest,point);
}

BOOL CMagicWnd::OnEraseBkgnd(CDC* pDC)
{
	//===绘背景、标题栏、图标(无皮肤情况)===
	CRect rect;
	GetClientRect(&rect);
	//创建背景画刷
	CBrush brBkgnd;
	brBkgnd.CreateSolidBrush(m_backColor);
	//创建标题栏画刷
	CBrush brTitleBar;
	brTitleBar.CreateSolidBrush(m_titleBarColor);
	//创建图标画刷
	CBrush brIcon;
	brIcon.CreateSolidBrush(m_iconColor);

	m_rcTitleBar.right=rect.Width();

	pDC->FillRect(rect,&brBkgnd);
	pDC->FillRect(m_rcTitleBar,&brTitleBar);
	pDC->FillRect(m_rcIcon,&brIcon);


	//===绘背景(皮肤情况)===
	if(!m_backGround.m_hObject)
		return TRUE;
	//获取窗口矩形
	CRect rc;
	GetWindowRect(&rc);
	//获取窗口DC
	CDC *pWndDC;
	pWndDC=GetWindowDC();
	//创建兼容DC
	CDC memDC;
    memDC.CreateCompatibleDC(pWndDC);
	//边白为零,只绘背景
	if(m_rcWindowBorder==CRect(0,0,0,0))
	{
		BITMAP bit;   
		m_backGround.GetBitmap(&bit);
		memDC.SelectObject(&m_backGround);
		pWndDC->StretchBlt(0,0,rc.Width(),rc.Height(),&memDC,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
		return TRUE;
	}
    
	//绘四边四角
	int nL=m_rcWindowBorder.left;	//左边距
	int nT=m_rcWindowBorder.top;	//上边距
	int nR=m_rcWindowBorder.right;	//右边距
	int nB=m_rcWindowBorder.bottom;	//下边距

	CRect rt[8];
	rt[0]=CRect(0,0,nL,nT);							//左上角
	rt[1]=CRect(rc.Width()-nR,0,nR,nT);				//右上角
	rt[2]=CRect(0,rc.Height()-nB,nL,nB);			//左下角
	rt[3]=CRect(rc.Width()-nR,rc.Height()-nB,nR,nB);//右下角
	rt[4]=CRect(nL,0,rc.Width()-nL-nR,nT);				//上边
	rt[5]=CRect(nL,rc.Height()-nB,rc.Width()-nL-nR,nB);	//下边
	rt[6]=CRect(0,nT,nL,rc.Height()-nT-nB);				//左边
	rt[7]=CRect(rc.Width()-nR,nT,nR,rc.Height()-nT-nB);	//右边

	for(int i=0;i<8;i++)
	{
		BITMAP bit;   
		m_backgnd[i].GetBitmap(&bit);
		memDC.SelectObject(&m_backgnd[i]);
		pWndDC->StretchBlt(rt[i].left,rt[i].top,rt[i].right,rt[i].bottom,&memDC,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
	}
	//绘中间(用背景色)
	pWndDC->FillRect(CRect(nL,nT,rc.Width()-nR,rc.Height()-nB),&brBkgnd);

	ReleaseDC(pWndDC);

	return TRUE;
}

//===系统菜单命令begin===//

//还原
void CMagicWnd::OnRestore()
{
	SendMessage(WM_SYSCOMMAND,SC_RESTORE,0);
	m_bMaximize=FALSE;
	EnableSysMenu(FALSE,m_bCanMove,TRUE,TRUE,TRUE);
}
//移动
void CMagicWnd::OnMove()
{
	SendMessage(WM_SYSCOMMAND,SC_MOVE,0);
}
//大小
void CMagicWnd::OnSize()
{
	SendMessage(WM_SYSCOMMAND,SC_SIZE,0);
}
//最小化
void CMagicWnd::OnMiniMize()
{
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
}
//最大化
void CMagicWnd::OnMaxiMize()
{
	SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);
	m_bMaximize=TRUE;
	EnableSysMenu(TRUE,FALSE,FALSE,TRUE,FALSE);
}
//关闭
void CMagicWnd::OnClose()
{
	SendMessage(WM_SYSCOMMAND,SC_CLOSE,0);
}
//关于
void CMagicWnd::OnAbout()
{
	SendMessage(WM_SYSCOMMAND,IDM_ABOUTBOX,0);
}

//===系统菜单命令end===//

//===系统按钮begin===//

//最小化
void CMagicWnd::OnBtnMinimize() 
{
	// TODO: Add your control notification handler code here
	OnMiniMize();
}
//最大化
void CMagicWnd::OnBtnMaximize() 
{
	// TODO: Add your control notification handler code here
	if(m_bMaximize)
		OnRestore();
	else
		OnMaxiMize();
}
//关闭
void CMagicWnd::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	OnClose();
}
//===系统按钮end===//

//设置窗口最大、最小尺寸
void CMagicWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if(!m_bFixSize)
	{
		lpMMI->ptMinTrackSize=CPoint(m_szMinSize.cx,m_szMinSize.cy);
		if(m_szMaxSize.cx!=0&&m_szMaxSize.cy!=0)
			lpMMI->ptMaxTrackSize=CPoint(m_szMaxSize.cx,m_szMaxSize.cy);
	}

	CWnd::OnGetMinMaxInfo(lpMMI);
}

//初始化全局样式
void CMagicWnd::InitGlobalStyle()
{
	//按钮样式
	m_styleButton.textColor=GetSysColor(COLOR_BTNTEXT);
	m_styleButton.textColorFocus=GetSysColor(COLOR_BTNTEXT);
	m_styleButton.textColorSelected=GetSysColor(COLOR_BTNTEXT);
	m_styleButton.textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	m_styleCheck.nFontSize=10;
	strcpy(m_styleButton.szFontName,"宋体");
	m_styleButton.nAlign=DT_LEFT;

	m_styleButton.bBold=m_styleButton.bBoldFocus=m_styleButton.bBoldSelected=m_styleButton.bBoldDisabled=FALSE;
	m_styleButton.bItalic=m_styleButton.bItalicFocus=m_styleButton.bItalicSelected=m_styleButton.bItalicDisabled=FALSE;
	m_styleButton.bUnderline=m_styleButton.bUnderlineFocus=m_styleButton.bUnderlineSelected=m_styleButton.bUnderlineDisabled=FALSE;
	m_styleButton.bStrikeOut=m_styleButton.bStrikeOutFocus=m_styleButton.bStrikeOutSelected=m_styleButton.bStrikeOutDisabled=FALSE;

	m_styleButton.hCursor=LoadCursor(NULL,MAKEINTRESOURCE(32649));//手形光标
	
	//复选框样式
	m_styleCheck.textColor=GetSysColor(COLOR_BTNTEXT);
	m_styleCheck.textColorFocus=GetSysColor(COLOR_BTNTEXT);
	m_styleCheck.textColorSelected=GetSysColor(COLOR_BTNTEXT);
	m_styleCheck.textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	m_styleCheck.nFontSize=10;
	strcpy(m_styleCheck.szFontName,"宋体");
	m_styleCheck.nAlign=DT_LEFT;

	m_styleCheck.bBold=FALSE;
	m_styleCheck.bItalic=FALSE;
	m_styleCheck.bUnderline=FALSE;
	m_styleCheck.bStrikeOut=FALSE;

	strcpy(m_styleCheck.szBackGround,"");
	strcpy(m_styleCheck.szImage,"");

	m_styleCheck.hCursor=LoadCursor(NULL,MAKEINTRESOURCE(32649));//手形光标

	//单选框样式
	m_styleRadio.textColor=GetSysColor(COLOR_BTNTEXT);
	m_styleRadio.textColorFocus=GetSysColor(COLOR_BTNTEXT);
	m_styleRadio.textColorSelected=GetSysColor(COLOR_BTNTEXT);
	m_styleRadio.textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	m_styleRadio.nFontSize=10;
	strcpy(m_styleRadio.szFontName,"宋体");
	m_styleRadio.nAlign=DT_LEFT;

	m_styleRadio.bBold=FALSE;
	m_styleRadio.bItalic=FALSE;
	m_styleRadio.bUnderline=FALSE;
	m_styleRadio.bStrikeOut=FALSE;

	strcpy(m_styleRadio.szBackGround,"");
	strcpy(m_styleRadio.szImage,"");

	m_styleRadio.hCursor=LoadCursor(NULL,MAKEINTRESOURCE(32649));//手形光标

	//文本样式
	m_styleText.textColor=GetSysColor(COLOR_BTNTEXT);
	m_styleText.textColorFocus=GetSysColor(COLOR_BTNTEXT);
	m_styleText.textColorSelected=GetSysColor(COLOR_BTNTEXT);
	m_styleText.textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	m_styleText.borderColor=-1;
	m_styleText.borderColorFocus=-1;
	m_styleText.borderColorSelected=-1;
	m_styleText.borderColorDisabled=-1;

	m_styleText.nFontSize=10;
	strcpy(m_styleText.szFontName,"宋体");
	m_styleText.nAlign=DT_LEFT;
	
	m_styleText.bBold=m_styleText.bBoldFocus=m_styleText.bBoldSelected=m_styleText.bBoldDisabled=FALSE;
	m_styleText.bItalic=m_styleText.bItalicFocus=m_styleText.bItalicSelected=m_styleText.bItalicDisabled=FALSE;
	m_styleText.bUnderline=m_styleText.bUnderlineFocus=m_styleText.bUnderlineSelected=m_styleText.bUnderlineDisabled=FALSE;
	m_styleText.bStrikeOut=m_styleText.bStrikeOutFocus=m_styleText.bStrikeOutSelected=m_styleText.bStrikeOutDisabled=FALSE;

	m_styleText.hCursor=LoadCursor(NULL,IDC_ARROW);//箭头光标

	//编辑框样式
	m_styleEdit.textColor=GetSysColor(COLOR_BTNTEXT);
	m_styleEdit.textColorHover=GetSysColor(COLOR_BTNTEXT);
	m_styleEdit.textColorFocus=GetSysColor(COLOR_BTNTEXT);
	m_styleEdit.textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	m_styleEdit.backColor=GetSysColor(COLOR_3DHIGHLIGHT);
	m_styleEdit.backColorHover=GetSysColor(COLOR_3DHIGHLIGHT);
	m_styleEdit.backColorFocus=GetSysColor(COLOR_3DHIGHLIGHT);
	m_styleEdit.backColorDisabled=GetSysColor(COLOR_3DHIGHLIGHT);

	m_styleEdit.borderColor=GetSysColor(COLOR_BTNTEXT);
	m_styleEdit.borderColorHover=GetSysColor(COLOR_BTNTEXT);
	m_styleEdit.borderColorFocus=GetSysColor(COLOR_BTNTEXT);
	m_styleEdit.borderColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	m_styleEdit.nFontSize=10;
	strcpy(m_styleEdit.szFontName,"宋体");
	m_styleEdit.nAlign=ES_LEFT;

	m_styleEdit.bBold=FALSE;
	m_styleEdit.bItalic=FALSE;
	m_styleEdit.bUnderline=FALSE;
	m_styleEdit.bStrikeOut=FALSE;
	m_styleEdit.bPassword=FALSE;

	m_styleEdit.hCursor=LoadCursor(NULL,IDC_IBEAM);//I型光标

	//组合框样式
	m_styleCombo.textColor=GetSysColor(COLOR_BTNTEXT);
	m_styleCombo.textColorHover=GetSysColor(COLOR_BTNTEXT);
	m_styleCombo.textColorDisabled=GetSysColor(COLOR_GRAYTEXT);

	m_styleCombo.backColor=GetSysColor(COLOR_3DHILIGHT);
	m_styleCombo.backColorHover=GetSysColor(COLOR_3DHILIGHT);
	m_styleCombo.backColorDisabled=GetSysColor(COLOR_3DHILIGHT);

	m_styleCombo.borderColor=GetSysColor(COLOR_BTNTEXT);

	m_styleCombo.btnColor=GetSysColor(COLOR_3DFACE);

	m_styleCombo.nFontSize=10;
	strcpy(m_styleCombo.szFontName,"宋体");
	
	m_styleCombo.bBold=FALSE;
	m_styleCombo.bItalic=FALSE;
	m_styleCombo.bUnderline=FALSE;
	m_styleCombo.bStrikeOut=FALSE;

	m_styleCombo.hCursor=LoadCursor(NULL,IDC_ARROW);//箭头光标
	
	//群组框样式
	m_styleGroup.textColor=GetSysColor(COLOR_BTNTEXT);

	m_styleGroup.nFontSize=10;
	strcpy(m_styleGroup.szFontName,"宋体");
	m_styleGroup.nAlign=SS_LEFT;

	m_styleGroup.bBold=FALSE;
	m_styleGroup.bItalic=FALSE;
	m_styleGroup.bUnderline=FALSE;
	m_styleGroup.bStrikeOut=FALSE;
	
	//填充区样式
	m_styleRegion.backColor=RGB(236,243,246);
	m_styleRegion.borderColor=RGB(0,136,228);
	m_styleRegion.borderWidth=2;
	m_styleRegion.nCorner=10;
	m_styleRegion.nAlpha=0;
}

//初始化全局样式
BOOL CMagicWnd::LoadGlobalStyle(LPCTSTR szSkinPath,LPCTSTR szGlobalXml)
{
	//加载xml
	m_strSkinPath=szSkinPath;
	m_strGlobalXml=szGlobalXml;
	CString strPath(m_strSkinPath+m_strGlobalXml);
	CMarkup xml;
	if(!xml.Load(strPath))
		return FALSE;

	//查找根结点
	xml.ResetMainPos();
	if(!xml.FindElem())
		return FALSE;
	xml.IntoElem();

	while(xml.FindElem())
	{
		CString str;

		CString strTagName=xml.GetTagName();
		if(strTagName=="ButtonStyle")
		{
			ReadStyleButton(m_styleButton,xml);
		}
		else if(strTagName=="CheckBoxStyle")
		{
			ReadStyleCheck(m_styleCheck,xml);
		}
		else if(strTagName=="RadioButtonStyle")
		{
			ReadStyleRadio(m_styleRadio,xml);
		}
		else if(strTagName=="TextStyle")
		{
			ReadStyleText(m_styleText,xml);
		}
		else if(strTagName=="EditStyle")
		{
			ReadStyleEdit(m_styleEdit,xml);
		}
		else if(strTagName=="ComboBoxStyle")
		{
			ReadStyleCombo(m_styleCombo,xml);
		}
		else if(strTagName=="GroupBoxStyle")
		{
			ReadStyleGroup(m_styleGroup,xml);
		}
		else if(strTagName=="FillRegionStyle")
		{
			ReadStyleRegion(m_styleRegion,xml);
		}
	}

	return TRUE;
}

//装载皮肤
BOOL CMagicWnd::LoadSkin(LPCTSTR szSkinPath,LPCTSTR szMainXml)
{	
	//加载xml
	m_strSkinPath=szSkinPath;
	m_strMainXml=szMainXml;
	CString strPath(m_strSkinPath+m_strMainXml);
	CMarkup xml;
	if(!xml.Load(strPath))
		return FALSE;

	//查找根结点
	xml.ResetMainPos();
	if(!xml.FindElem())
		return FALSE;
	xml.IntoElem();

	//查找Window结点
	if(!xml.FindElem("Window"))
		return FALSE;
	if(!SetWindow(xml))
		return FALSE;

	//进入Window结点内部
	xml.IntoElem();
	SetControl(xml);

	return TRUE;
}

void CMagicWnd::EnableSysMenu(BOOL bRestor, BOOL bMove, BOOL bSize, BOOL bMini, BOOL bMaxi)
{
	UINT nEnable;
	nEnable=bRestor?MF_ENABLED:MF_GRAYED;
	m_sysMenu.GetSubMenu(0)->EnableMenuItem(IDM_RESTORE,nEnable);
	nEnable=bMove?MF_ENABLED:MF_GRAYED;
	m_sysMenu.GetSubMenu(0)->EnableMenuItem(IDM_MOVE,nEnable);
	nEnable=bSize?MF_ENABLED:MF_GRAYED;
	m_sysMenu.GetSubMenu(0)->EnableMenuItem(IDM_SIZE,nEnable);
	nEnable=bMini?MF_ENABLED:MF_GRAYED;
	m_sysMenu.GetSubMenu(0)->EnableMenuItem(IDM_MINIMIZE,nEnable);
	nEnable=bMaxi?MF_ENABLED:MF_GRAYED;
	m_sysMenu.GetSubMenu(0)->EnableMenuItem(IDM_MAXIMIZE,nEnable);
}

BOOL CMagicWnd::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_SHOWMAXIMIZED)
	{
		if(m_bFixSize)
		{
			nCmdShow=SW_SHOWNORMAL;
		}
		else
		{
			m_bMaximize=TRUE;
			EnableSysMenu(TRUE,m_bCanMove,TRUE,TRUE,FALSE);
		}
	}
	return CWnd::ShowWindow(nCmdShow);
}

BOOL CMagicWnd::SetWindow(CMarkup xml)
{
	CString strWndName=xml.GetAttrib("Name");
	//if(strWndName=="") return FALSE;

	//背景色
	CString strBackColor=xml.GetAttrib("BackColor");
	CAttrib::GetColor(strBackColor,m_backColor);

	//背景图
	CString strBackground=xml.GetAttrib("Background");
	CString strPath=m_strSkinPath+strBackground;
	HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),strPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(hBitmap)
	{
		if(m_backGround.m_hObject)
			m_backGround.DeleteObject();
		m_backGround.Attach(hBitmap);
	}

	//窗口掩码色
	CString strUseMaskColor=xml.GetAttrib("UseMaskColor");
	CAttrib::GetBool(strUseMaskColor,m_bUseMaskColor);
	CString strMaskColor=xml.GetAttrib("MaskColor");
	CAttrib::GetColor(strMaskColor,m_maskColor);
	//窗口边白
	CString strWindowBorder=xml.GetAttrib("WindowBorder");
	CAttrib::GetRect(strWindowBorder,m_rcWindowBorder);

	if(m_backGround.m_hObject)
	{
		//拆分背景图
		CDC *pWndDC;
		pWndDC=GetWindowDC();

		CDC memSrcDC,memDesDC;
		memSrcDC.CreateCompatibleDC(pWndDC);
		memDesDC.CreateCompatibleDC(pWndDC);

		memSrcDC.SelectObject(&m_backGround);
		BITMAP bit;
		m_backGround.GetBitmap(&bit);

		int nL=m_rcWindowBorder.left;
		int nT=m_rcWindowBorder.top;
		int nR=m_rcWindowBorder.right;
		int nB=m_rcWindowBorder.bottom;

		CRect rc[8];
		rc[0]=CRect(0,0,nL,nT);//左上角
		rc[1]=CRect(bit.bmWidth-nR,0,nR,nT);//右上角
		rc[2]=CRect(0,bit.bmHeight-nB,nL,nB);//左下角
		rc[3]=CRect(bit.bmWidth-nR,bit.bmHeight-nB,nR,nB);//右下角
		rc[4]=CRect(nL,0,bit.bmWidth-nL-nR,nT);//上边
		rc[5]=CRect(nL,bit.bmHeight-nB,bit.bmWidth-nL-nR,nB);//下边
		rc[6]=CRect(0,nT,nL,bit.bmHeight-nT-nB);//左边
		rc[7]=CRect(bit.bmWidth-nR,nT,nR,bit.bmHeight-nT-nB);//右边

		for(int i=0;i<8;i++)
		{
			if(m_backgnd[i].m_hObject)
				m_backgnd[i].DeleteObject();
			m_backgnd[i].CreateCompatibleBitmap(pWndDC,rc[i].right,rc[i].bottom);
			memDesDC.SelectObject(&m_backgnd[i]);
			memDesDC.BitBlt(0,0,rc[i].right,rc[i].bottom,&memSrcDC,rc[i].left,rc[i].top,SRCCOPY);
		}

		if(m_bUseMaskColor)
		{
			ModifyStyleEx(NULL,WS_EX_LAYERED);
			CCommon::SetAlpha(m_hWnd,m_maskColor,0,LWA_COLORKEY);
		}
	}

	//窗口位置和大小
	CString strRect=xml.GetAttrib("Rect");
	CAttrib::GetRect(strRect,m_ptWnd,m_szWnd);
	SetWindowPos(NULL,m_ptWnd.x,m_ptWnd.y,m_szWnd.cx,m_szWnd.cy,SWP_NOZORDER);

	//标题栏
	m_rcTitleBar=CRect(0,0,m_szWnd.cx,18);

	//窗口是否可移动
	CString strCanMove=xml.GetAttrib("CanMove");
	CAttrib::GetBool(strCanMove,m_bCanMove);

	//窗口是否可改大小
	CString strFixSize=xml.GetAttrib("FixSize");
	CAttrib::GetBool(strFixSize,m_bFixSize);

	//判断FixSize
	if(m_bFixSize)
	{
		//m_btnMax.EnableWindow(FALSE);
		ModifyStyle(WS_THICKFRAME,WS_DLGFRAME);
		//SetWindowLong(m_hWnd, GWL_STYLE, (LONG)(GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_BORDER ));
	}
	else
	{
		//m_btnMax.EnableWindow(TRUE);
		ModifyStyle(WS_DLGFRAME,WS_THICKFRAME);
		//SetWindowLong(m_hWnd, GWL_STYLE, (LONG)(GetWindowLong(m_hWnd, GWL_STYLE) & WS_BORDER ));

		//窗口最小值
		CString strMinSize=xml.GetAttrib("MinSize");
		CAttrib::GetSize(strMinSize,m_szMinSize);
		//窗口最大值
		CString strMaxSize=xml.GetAttrib("MaxSize");
		CAttrib::GetSize(strMaxSize,m_szMaxSize);
	}
	EnableSysMenu(m_bMaximize,m_bCanMove,!m_bFixSize,TRUE,!m_bMaximize&&!m_bFixSize);

	//可见
	BOOL bVisible=TRUE;
	CString strVisible=xml.GetAttrib("Visible");
	CAttrib::GetBool(strVisible,bVisible);
	if(!bVisible) ShowWindow(SW_HIDE);
	//可用
	BOOL bEnable=TRUE;
	CString strEnable=xml.GetAttrib("Enable");
	CAttrib::GetBool(strEnable,bEnable);
	if(!bEnable) EnableWindow(FALSE);

	//保存控件信息
	CTRL_INFO ctrlInfo;
	ctrlInfo.strName=strWndName;
	ctrlInfo.nType=MAGICUI_WND;
	ctrlInfo.pWnd=CWnd::FromHandle(m_hWnd);
	ctrlInfo.nCmd=NULL;
	m_aryControl.Add(ctrlInfo);

	return TRUE;
}

void CMagicWnd::SetControl(CMarkup xml)
{
	while(xml.FindElem())
	{
		CString strTagName=xml.GetTagName();
		if(strTagName=="Button")
			SetButton(xml);
		else if(strTagName=="CheckBox")
			SetCheckBox(xml);
		else if(strTagName=="RadioBox")
			SetRadioBox(xml);
		else if(strTagName=="Picture")
			SetPicture(xml);
		else if(strTagName=="Text")
			SetText(xml);
		else if(strTagName=="Edit")
			SetEdit(xml);
		else if(strTagName=="ComboBox")
			SetComboBox(xml);
		else if(strTagName=="GroupBox")
			SetGroup(xml);
		else if(strTagName=="FillRegion")
			SetRegion(xml);
	}
}

void CMagicWnd::SetButton(CMarkup xml)
{
	//变量定义
	CString strRect,strString,strCmd,strBackground,strImage;
	CPoint pt;
	CSize sz;

	CString strName=xml.GetAttrib("Name");
	//if(strName=="") return ;

	if(strName=="btnMin")
	{
		if(m_btnMin.m_hWnd) return;
		strRect=xml.GetAttrib("Rect");
		if(CAttrib::GetRect(strRect,pt,sz))
		{
			//-----创建控件对象-----//
			m_bMinExist=TRUE;
			m_szMin.cx=m_szWnd.cx-pt.x;
			m_szMin.cy=pt.y;
			CRect rc=CRect(pt,sz);
			strString=xml.GetAttrib("String");
			m_btnMin.Create(strString,WS_VISIBLE,rc,this,IDC_BTN_MINIMIZE);
			
			//-----保存控件信息-----//
			CTRL_INFO ctrlInfo;
			ctrlInfo.strName=strName;
			ctrlInfo.nType=MAGICUI_BUTTON;
			ctrlInfo.pWnd=&m_btnMin;
			ctrlInfo.nCmd=IDC_BTN_MINIMIZE;
			m_aryControl.Add(ctrlInfo);
			
			//-----读取常规样式-----//
			strImage=xml.GetAttrib("Image");
			if(strImage!="")
			{
				CString strPath=m_strSkinPath+strImage;
				m_btnMin.SetImage(strPath);
			}
			else
			{
				strBackground=xml.GetAttrib("Background");
				if(strBackground!="")
				{
					CString strPath=m_strSkinPath+strBackground;
					m_btnMin.SetBitmap(strPath);
				}
			}

			//边框
			BOOL bBorder=FALSE;
			CString strBorder=xml.GetAttrib("Border");
			CAttrib::GetBool(strBorder,bBorder);
			m_btnMin.SetBorder(bBorder);

			//工具提示
			CString strToolTip=xml.GetAttrib("ToolTip");
			if(strToolTip!="") m_toolTip.AddTool(&m_btnMin,strToolTip);
		}
	}
	else if(strName=="btnMax")
	{
		if(m_btnMax.m_hWnd) return;
		strRect=xml.GetAttrib("Rect");
		if(CAttrib::GetRect(strRect,pt,sz))
		{
			//-----创建控件对象-----//
			m_bMaxExist=TRUE;
			m_szMax.cx=m_szWnd.cx-pt.x;
			m_szMax.cy=pt.y;
			CRect rc=CRect(pt,sz);
			strString=xml.GetAttrib("String");
			m_btnMax.Create(strString,WS_VISIBLE,rc,this,IDC_BTN_MAXIMIZE);
		
			//-----保存控件信息-----//
			CTRL_INFO ctrlInfo;
			ctrlInfo.strName=strName;
			ctrlInfo.nType=MAGICUI_BUTTON;
			ctrlInfo.pWnd=&m_btnMax;
			ctrlInfo.nCmd=IDC_BTN_MAXIMIZE;
			m_aryControl.Add(ctrlInfo);

			//-----读取常规样式-----//
			strImage=xml.GetAttrib("Image");
			if(strImage!="")
			{
				CString strPath=m_strSkinPath+strImage;
				m_btnMax.SetImage(strPath);
			}
			else
			{
				strBackground=xml.GetAttrib("Background");
				if(strBackground!="")
				{
					CString strPath=m_strSkinPath+strBackground;
					m_btnMax.SetBitmap(strPath);
				}
			}

			//边框
			BOOL bBorder=FALSE;
			CString strBorder=xml.GetAttrib("Border");
			CAttrib::GetBool(strBorder,bBorder);
			m_btnMax.SetBorder(bBorder);

			//工具提示
			CString strToolTip=xml.GetAttrib("ToolTip");
			if(strToolTip!="") m_toolTip.AddTool(&m_btnMax,strToolTip);
		}
	}
	else if(strName=="btnClose")
	{
		if(m_btnClose.m_hWnd) return;
		strRect=xml.GetAttrib("Rect");
		if(CAttrib::GetRect(strRect,pt,sz))
		{
			//-----创建控件对象-----//
			m_bCloseExist=TRUE;
			m_szClose.cx=m_szWnd.cx-pt.x;
			m_szClose.cy=pt.y;
			CRect rc=CRect(pt,sz);
			strString=xml.GetAttrib("String");
			m_btnClose.Create(strString,WS_VISIBLE,rc,this,IDC_BTN_CLOSE);
						
			//-----保存控件信息-----//
			CTRL_INFO ctrlInfo;
			ctrlInfo.strName=strName;
			ctrlInfo.nType=MAGICUI_BUTTON;
			ctrlInfo.pWnd=&m_btnClose;
			ctrlInfo.nCmd=IDC_BTN_CLOSE;
			m_aryControl.Add(ctrlInfo);

			//-----读取常规样式-----//
			strImage=xml.GetAttrib("Image");
			if(strImage!="")
			{
				CString strPath=m_strSkinPath+strImage;
				m_btnClose.SetImage(strPath);
			}
			else
			{
				strBackground=xml.GetAttrib("Background");
				if(strBackground!="")
				{
					CString strPath=m_strSkinPath+strBackground;
					m_btnClose.SetBitmap(strPath);
				}
			}

			//边框
			BOOL bBorder=FALSE;
			CString strBorder=xml.GetAttrib("Border");
			CAttrib::GetBool(strBorder,bBorder);
			m_btnClose.SetBorder(bBorder);

			//工具提示
			CString strToolTip=xml.GetAttrib("ToolTip");
			if(strToolTip!="") m_toolTip.AddTool(&m_btnClose,strToolTip);
		}
	}
	else
	{
		strRect=xml.GetAttrib("Rect");
		if(CAttrib::GetRect(strRect,pt,sz))
		{
			//-----创建控件对象-----//
			CMagicButton *pBtn=new CMagicButton();
			CRect rc=CRect(pt,sz);
			strString=xml.GetAttrib("String");
			strCmd=xml.GetAttrib("Cmd");
			UINT nCmd=atoi(strCmd);
			pBtn->Create(strString,WS_VISIBLE,rc,this,nCmd);

			//-----保存控件信息-----//
			CTRL_INFO ctrlInfo;
			ctrlInfo.strName=strName;
			ctrlInfo.nType=MAGICUI_BUTTON;
			ctrlInfo.pWnd=pBtn;
			ctrlInfo.nCmd=nCmd;
			m_aryControl.Add(ctrlInfo);

			//-----读取常规样式-----//
			strImage=xml.GetAttrib("Image");
			if(strImage!="")
			{
				CString strPath=m_strSkinPath+strImage;
				pBtn->SetImage(strPath);
			}
			else
			{
				strBackground=xml.GetAttrib("Background");
				if(strBackground!="")
				{
					CString strPath=m_strSkinPath+strBackground;
					pBtn->SetBitmap(strPath);
				}
				else
				{
					CString strColor;
					COLORREF bkColor=-1,bkColorFocus=-1,bkColorSelected=-1,bkColorDisabled=-1;
					strColor=xml.GetAttrib("BackColor");
					CAttrib::GetColor(strColor,bkColor);
					strColor=xml.GetAttrib("BackColorFocus");
					CAttrib::GetColor(strColor,bkColorFocus);
					strColor=xml.GetAttrib("BackColorSelected");
					CAttrib::GetColor(strColor,bkColorSelected);
					strColor=xml.GetAttrib("BackColorDisabled");
					CAttrib::GetColor(strColor,bkColorDisabled);

					pBtn->SetBackColor(bkColor,bkColorFocus,bkColorSelected,bkColorDisabled);
				}
			}

			//边框
			BOOL bBorder=FALSE;
			CString strBorder=xml.GetAttrib("Border");
			CAttrib::GetBool(strBorder,bBorder);
			pBtn->SetBorder(bBorder);

			//可见
			BOOL bVisible=TRUE;
			CString strVisible=xml.GetAttrib("Visible");
			CAttrib::GetBool(strVisible,bVisible);
			if(!bVisible) pBtn->ShowWindow(SW_HIDE);
			//可用
			BOOL bEnable=TRUE;
			CString strEnable=xml.GetAttrib("Enable");
			CAttrib::GetBool(strEnable,bEnable);
			if(!bEnable) pBtn->EnableWindow(FALSE);
			//工具提示
			CString strToolTip=xml.GetAttrib("ToolTip");
			if(strToolTip!="") m_toolTip.AddTool(pBtn,strToolTip);
			//按钮样式
			CString strDrawStyle=xml.GetAttrib("DrawStyle");
			strDrawStyle.MakeLower();
			if(strDrawStyle=="press")
				pBtn->SetStyle(BS_PRESS);

			//拷贝全局样式
			STYLE_BUTTON sb;
			memcpy(&sb,&m_styleButton,sizeof(m_styleButton));
			//读取自定义样式
			CString strLabel=xml.GetAttrib("UserStyle");
			if(strLabel!="")
			{
				CMarkup xmlGlb;
				if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleButton(sb,xmlGlb);
			}
			//读取标签样式
			ReadStyleButton(sb,xml);

			//-----设置全局属性-----//
			if(strString!="")
			{
				pBtn->SetForeColor(sb.textColor,sb.textColorFocus,sb.textColorSelected,sb.textColorDisabled);
				pBtn->SetFont(sb.nFontSize,sb.szFontName);
				pBtn->SetAlign(sb.nAlign);
				pBtn->SetBold(sb.bBold,sb.bBoldFocus,sb.bBoldSelected,sb.bBoldDisabled);
				pBtn->SetItalic(sb.bItalic,sb.bItalicFocus,sb.bItalicSelected,sb.bItalicDisabled);
				pBtn->SetUnderline(sb.bUnderline,sb.bUnderlineFocus,sb.bUnderlineSelected,sb.bUnderlineDisabled);
				pBtn->SetStrikeOut(sb.bStrikeOut,sb.bStrikeOutFocus,sb.bStrikeOutSelected,sb.bStrikeOutDisabled);
			}
			pBtn->SetCursor(sb.hCursor);
		}
	}
}

void CMagicWnd::SetPicture(CMarkup xml)
{
	//变量定义
	CString strName,strCmd,strRect,strBackground,strImage;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;

	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicPicture *pPic=new CMagicPicture();
		CRect rc=CRect(pt,sz);
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		if(nCmd==0) nCmd=0xffff;
		pPic->Create(WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_PICTURE;
		ctrlInfo.pWnd=pPic;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);
		
		//-----读取常规样式-----//
		strImage=xml.GetAttrib("Image");
		if(strImage!="")
		{
			CString strPath=m_strSkinPath+strImage;
			pPic->SetImage(strPath);
			pPic->SetStyle(PS_STRETCH);
		}
		else
		{
			strBackground=xml.GetAttrib("Background");
			if(strBackground!="")
			{
				CString strPath=m_strSkinPath+strBackground;
				pPic->SetBitmap(strPath);
			}
		}

		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pPic->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pPic->EnableWindow(FALSE);
		//工具提示
		CString strToolTip=xml.GetAttrib("ToolTip");
		if(strToolTip!="") m_toolTip.AddTool(pPic,strToolTip);
		//显示样式
		UINT nStyle;
		CString strDrawStyle=xml.GetAttrib("DrawStyle");
		strDrawStyle.MakeLower();
		if(strDrawStyle=="autosize")
			nStyle=PS_AUTOSIZE;
		else if(strDrawStyle=="stretch")
			nStyle=PS_STRETCH;
		else
			nStyle=PS_FIXSIZE;

		CString strBorder=xml.GetAttrib("Border");
		BOOL bBorder=FALSE;
		CAttrib::GetBool(strBorder,bBorder);
		if(bBorder)
			nStyle|=PS_BORDER;

		CString strScroll=xml.GetAttrib("Scroll");
		BOOL bScroll=FALSE;
		CAttrib::GetBool(strScroll,bScroll);
		if(bScroll)
			nStyle|=PS_SCROLL;

		pPic->SetStyle(nStyle);
	}
}

void CMagicWnd::SetText(CMarkup xml)
{
	//变量定义
	CString strName,strCmd,strString,strRect,strBackground,strImage;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;
	
	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicText *pTxt=new CMagicText();
		CRect rc=CRect(pt,sz);
		strString=xml.GetAttrib("String");
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		if(nCmd==0) nCmd=0xffff;
		pTxt->Create(strString,WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_TEXT;
		ctrlInfo.pWnd=pTxt;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);
		
		//-----读取常规样式-----//
		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pTxt->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pTxt->EnableWindow(FALSE);
		//工具提示
		CString strToolTip=xml.GetAttrib("ToolTip");
		if(strToolTip!="") m_toolTip.AddTool(pTxt,strToolTip);
		
		//拷贝全局样式
		STYLE_TEXT st;
		memcpy(&st,&m_styleText,sizeof(m_styleText));
		//读取自定义样式
		CString strLabel=xml.GetAttrib("UserStyle");
		if(strLabel!="")
		{
			CMarkup xmlGlb;
			if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleText(st,xmlGlb);
		}
		//读取标签样式
		ReadStyleText(st,xml);
		
		//-----设置全局属性-----//
		pTxt->SetTextColor(st.textColor,st.textColorFocus,st.textColorSelected,st.textColorDisabled);
		pTxt->SetBorderColor(st.borderColor,st.borderColorFocus,st.borderColorSelected,st.borderColorDisabled);
		pTxt->SetFont(st.nFontSize,st.szFontName);
		pTxt->SetAlign(st.nAlign);
		pTxt->SetBold(st.bBold,st.bBoldFocus,st.bBoldSelected,st.bBoldDisabled);
		pTxt->SetItalic(st.bItalic,st.bItalicFocus,st.bItalicSelected,st.bItalicDisabled);
		pTxt->SetUnderline(st.bUnderline,st.bUnderlineFocus,st.bUnderlineSelected,st.bUnderlineDisabled);
		pTxt->SetStrikeOut(st.bStrikeOut,st.bStrikeOutFocus,st.bStrikeOutSelected,st.bStrikeOutDisabled);
		pTxt->SetCursor(st.hCursor);
	}
}

void CMagicWnd::SetEdit(CMarkup xml)
{
	//变量定义
	CString strName,strCmd,strString,strRect,strBackground,strImage;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;
	
	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicEdit *pEdit=new CMagicEdit();
		CRect rc=CRect(pt,sz);
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		pEdit->Create(WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_EDIT;
		ctrlInfo.pWnd=pEdit;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);
		
		//-----读取常规样式-----//
		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pEdit->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pEdit->EnableWindow(FALSE);
		//工具提示
		CString strToolTip=xml.GetAttrib("ToolTip");
		if(strToolTip!="") m_toolTip.AddTool(pEdit,strToolTip);
		//文本内容
		strString=xml.GetAttrib("String");
		if(strString!="") pEdit->SetWindowText(strString);
		
		//拷贝全局样式
		STYLE_EDIT se;
		memcpy(&se,&m_styleEdit,sizeof(m_styleEdit));
		//读取自定义样式
		CString strLabel=xml.GetAttrib("UserStyle");
		if(strLabel!="")
		{
			CMarkup xmlGlb;
			if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleEdit(se,xmlGlb);
		}
		//读取标签样式
		ReadStyleEdit(se,xml);

		//-----设置全局属性-----//
		pEdit->SetTextColor(se.textColor,se.textColorHover,se.textColorFocus,se.textColorDisabled);
		pEdit->SetBackColor(se.backColor,se.backColorHover,se.backColorFocus,se.backColorDisabled);
		pEdit->SetBorderColor(se.borderColor,se.borderColorHover,se.borderColorFocus,se.borderColorDisabled);
		pEdit->SetFont(se.nFontSize,se.szFontName,se.bBold,se.bItalic,se.bUnderline,se.bStrikeOut);
		pEdit->SetAlign(se.nAlign);
		pEdit->SetPassword(se.bPassword);
		pEdit->SetCursor(se.hCursor);
	}
}

void CMagicWnd::SetComboBox(CMarkup xml)
{
	//变量定义
	CString strName,strCmd,strString,strRect,strBackground,strImage;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;
	
	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicCombo *pCmb=new CMagicCombo();
		CRect rc=CRect(pt,sz);
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		pCmb->Create(WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_COMBO;
		ctrlInfo.pWnd=pCmb;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);
		
		//-----读取常规样式-----//
		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pCmb->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pCmb->EnableWindow(FALSE);
		//工具提示
		CString strToolTip=xml.GetAttrib("ToolTip");
		if(strToolTip!="") m_toolTip.AddTool(pCmb,strToolTip);
		//选项内容
		strString=xml.GetAttrib("String");
		if(strString!="")
		{
			CStringArray aryItem;
			aryItem.RemoveAll();
			int nCount=CCommon::SplitString(strString,'|',aryItem);
			for(int i=0;i<nCount;i++)
				pCmb->AddString(aryItem.GetAt(i));
		}
		//当前选项
		int nIndexSel=-1;
		CString strIndexSel=xml.GetAttrib("IndexSel");
		if(strIndexSel!="") nIndexSel=atoi(strIndexSel);
		if(nIndexSel>=0&&nIndexSel<pCmb->GetCount())
			pCmb->SetCurSel(nIndexSel);

		
		//拷贝全局样式
		STYLE_COMBO sc;
		memcpy(&sc,&m_styleCombo,sizeof(m_styleCombo));
		//读取自定义样式
		CString strLabel=xml.GetAttrib("UserStyle");
		if(strLabel!="")
		{
			CMarkup xmlGlb;
			if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleCombo(sc,xmlGlb);
		}
		//读取标签样式
		ReadStyleCombo(sc,xml);
		
		//-----设置全局属性-----//
		pCmb->SetTextColor(sc.textColor,sc.textColorHover,sc.textColorDisabled);
		pCmb->SetBackColor(sc.backColor,sc.backColorHover,sc.backColorDisabled);
		pCmb->SetBorderColor(sc.borderColor);
		pCmb->SetBtnColor(sc.btnColor);
		pCmb->SetFont(sc.nFontSize,sc.szFontName,sc.bBold,sc.bItalic,sc.bUnderline,sc.bStrikeOut);
		pCmb->SetCursor(sc.hCursor);
	}
}

void CMagicWnd::SetCheckBox(CMarkup xml)
{
	//变量定义
	CString strName,strString,strCmd,strRect;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;

	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicCheck *pChk=new CMagicCheck();
		CRect rc=CRect(pt,sz);
		strString=xml.GetAttrib("String");
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		pChk->Create(strString,WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_CHECK;
		ctrlInfo.pWnd=pChk;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);

		//-----读取常规样式-----//
		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pChk->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pChk->EnableWindow(FALSE);
		//工具提示
		CString strToolTip=xml.GetAttrib("ToolTip");
		if(strToolTip!="") m_toolTip.AddTool(pChk,strToolTip);
		//选中
		BOOL bSelected=FALSE;
		CString strSelected=xml.GetAttrib("Selected");
		CAttrib::GetBool(strSelected,bSelected);
		if(bSelected) pChk->SetSelect();

		//拷贝全局样式
		STYLE_CHECK sc;
		memcpy(&sc,&m_styleCheck,sizeof(m_styleCheck));
		//读取自定义样式
		CString strLabel=xml.GetAttrib("UserStyle");
		if(strLabel!="")
		{
			CMarkup xmlGlb;
			if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleCheck(sc,xmlGlb);
		}
		//读取标签样式
		ReadStyleCheck(sc,xml);

		//-----设置全局属性-----//
		if(strlen(sc.szImage)!=0)
		{
			CString strPath=m_strSkinPath+sc.szImage;
			pChk->SetImage(strPath);
		}
		else
		{
			if(strlen(sc.szBackGround)!=0)
			{
				CString strPath=m_strSkinPath+sc.szBackGround;
				pChk->SetBitmap(strPath);
			}
		}

		pChk->SetForeColor(sc.textColor,sc.textColorFocus,sc.textColorSelected,sc.textColorDisabled);
		pChk->SetFont(sc.nFontSize,sc.szFontName,sc.bBold,sc.bItalic,sc.bUnderline,sc.bStrikeOut);
		pChk->SetAlign(sc.nAlign);
		pChk->SetCursor(sc.hCursor);
	}
}

void CMagicWnd::SetRadioBox(CMarkup xml)
{
	//变量定义
	CString strName,strString,strCmd,strRect;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;

	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicRadio *pRad=new CMagicRadio();
		CRect rc=CRect(pt,sz);
		strString=xml.GetAttrib("String");
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		pRad->Create(strString,WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_RADIO;
		ctrlInfo.pWnd=pRad;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);

		//-----读取常规样式-----//
		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pRad->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pRad->EnableWindow(FALSE);
		//工具提示
		CString strToolTip=xml.GetAttrib("ToolTip");
		if(strToolTip!="") m_toolTip.AddTool(pRad,strToolTip);

		//组号
		CString strGroupID=xml.GetAttrib("GroupID");
		UINT nGroupID=atoi(strGroupID);
		pRad->SetGroupID(nGroupID);
		
		//选中
		CString strSelected=xml.GetAttrib("Selected");
		BOOL bSelected=FALSE;
		CAttrib::GetBool(strSelected,bSelected);
		if(bSelected) pRad->SetSelect();

		//-----拷贝全局样式-----//
		STYLE_RADIO sr;
		memcpy(&sr,&m_styleRadio,sizeof(m_styleRadio));
		//读取自定义样式
		CString strLabel=xml.GetAttrib("UserStyle");
		if(strLabel!="")
		{
			CMarkup xmlGlb;
			if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleRadio(sr,xmlGlb);
		}
		//读取标签样式
		ReadStyleRadio(sr,xml);

		//-----设置全局属性-----//
		if(strlen(sr.szImage)!=0)
		{
			CString strPath=m_strSkinPath+sr.szImage;
			pRad->SetImage(strPath);
		}
		else
		{
			if(strlen(sr.szBackGround)!=0)
			{
				CString strPath=m_strSkinPath+sr.szBackGround;
				pRad->SetBitmap(strPath);
			}
		}

		pRad->SetForeColor(sr.textColor,sr.textColorFocus,sr.textColorSelected,sr.textColorDisabled);
		pRad->SetFont(sr.nFontSize,sr.szFontName,sr.bBold,sr.bItalic,sr.bUnderline,sr.bStrikeOut);
		pRad->SetAlign(sr.nAlign);
		pRad->SetCursor(sr.hCursor);
	}
}

void CMagicWnd::SetGroup(CMarkup xml)
{
	//变量定义
	CString strName,strString,strCmd,strRect;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;

	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicGroup *pGrp=new CMagicGroup();
		CRect rc=CRect(pt,sz);
		strString=xml.GetAttrib("String");
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		if(nCmd==0) nCmd=0xffff;
		pGrp->Create(strString,WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_GROUP;
		ctrlInfo.pWnd=pGrp;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);

		//-----读取常规样式-----//
		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pGrp->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pGrp->EnableWindow(FALSE);

		//-----拷贝全局样式-----//
		STYLE_GROUP sg;
		memcpy(&sg,&m_styleGroup,sizeof(m_styleGroup));
		//读取自定义样式
		CString strLabel=xml.GetAttrib("UserStyle");
		if(strLabel!="")
		{
			CMarkup xmlGlb;
			if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleGroup(sg,xmlGlb);
		}
		//读取标签样式
		ReadStyleGroup(sg,xml);

		pGrp->SetTextColor(sg.textColor);
		pGrp->SetFont(sg.nFontSize,sg.szFontName,sg.bBold,sg.bItalic,sg.bUnderline,sg.bStrikeOut);
		pGrp->SetAlign(sg.nAlign);
	}
}

void CMagicWnd::SetRegion(CMarkup xml)
{
	//变量定义
	CString strName,strString,strCmd,strRect;
	CPoint pt;
	CSize sz;

	strName=xml.GetAttrib("Name");
	//if(strName=="") return ;

	strRect=xml.GetAttrib("Rect");
	if(CAttrib::GetRect(strRect,pt,sz))
	{
		//-----创建控件对象-----//
		CMagicFillRegion *pRgn=new CMagicFillRegion();
		CRect rc=CRect(pt,sz);
		strCmd=xml.GetAttrib("Cmd");
		UINT nCmd=atoi(strCmd);
		if(nCmd==0) nCmd=0xffff;
		pRgn->Create(WS_VISIBLE,rc,this,nCmd);

		//-----保存控件信息-----//
		CTRL_INFO ctrlInfo;
		ctrlInfo.strName=strName;
		ctrlInfo.nType=MAGICUI_FILLREGION;
		ctrlInfo.pWnd=pRgn;
		ctrlInfo.nCmd=nCmd;
		m_aryControl.Add(ctrlInfo);

		//-----读取常规样式-----//
		//可见
		BOOL bVisible=TRUE;
		CString strVisible=xml.GetAttrib("Visible");
		CAttrib::GetBool(strVisible,bVisible);
		if(!bVisible) pRgn->ShowWindow(SW_HIDE);
		//可用
		BOOL bEnable=TRUE;
		CString strEnable=xml.GetAttrib("Enable");
		CAttrib::GetBool(strEnable,bEnable);
		if(!bEnable) pRgn->EnableWindow(FALSE);

		//-----拷贝全局样式-----//
		STYLE_FILLREGION sf;
		memcpy(&sf,&m_styleRegion,sizeof(m_styleRegion));
		//读取自定义样式
		CString strLabel=xml.GetAttrib("UserStyle");
		if(strLabel!="")
		{
			CMarkup xmlGlb;
			if(FindUserStyle(strLabel,xmlGlb))
				ReadStyleRegion(sf,xmlGlb);
		}
		//读取标签样式
		ReadStyleRegion(sf,xml);

		pRgn->SetBackColor(sf.backColor);
		pRgn->SetBorderColor(sf.borderColor);
		pRgn->SetBorderWidth(sf.borderWidth);
		pRgn->SetCorner(sf.nCorner);
		pRgn->SetAlpha(sf.nAlpha);
	}
}

void CMagicWnd::ReadStyleButton(STYLE_BUTTON &sb,CMarkup xml)
{
	CString str;
	//文本颜色
	str=xml.GetAttrib("TextColor");
	CAttrib::GetColor(str,sb.textColor);
	str=xml.GetAttrib("TextColorFocus");
	CAttrib::GetColor(str,sb.textColorFocus);
	str=xml.GetAttrib("TextColorSelected");
	CAttrib::GetColor(str,sb.textColorSelected);
	str=xml.GetAttrib("TextColorDisabled");
	CAttrib::GetColor(str,sb.textColorDisabled);
	//文本样式
	str=xml.GetAttrib("FontSize");
	if(str!="") sb.nFontSize=atoi(str);
	str=xml.GetAttrib("FontName");
	if(str!="") strcpy(sb.szFontName,str.GetBuffer(str.GetLength()));

	str=xml.GetAttrib("Bold");
	CAttrib::GetBool(str,sb.bBold);
	str=xml.GetAttrib("BoldFocus");
	CAttrib::GetBool(str,sb.bBoldFocus);
	str=xml.GetAttrib("BoldSelected");
	CAttrib::GetBool(str,sb.bBoldSelected);
	str=xml.GetAttrib("BoldDisabled");
	CAttrib::GetBool(str,sb.bBoldDisabled);

	str=xml.GetAttrib("Italic");
	CAttrib::GetBool(str,sb.bItalic);
	str=xml.GetAttrib("ItalicFocus");
	CAttrib::GetBool(str,sb.bItalicFocus);
	str=xml.GetAttrib("ItalicSelected");
	CAttrib::GetBool(str,sb.bItalicSelected);
	str=xml.GetAttrib("ItalicDisabled");
	CAttrib::GetBool(str,sb.bItalicDisabled);

	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,sb.bUnderline);
	str=xml.GetAttrib("UnderlineFocus");
	CAttrib::GetBool(str,sb.bUnderlineFocus);
	str=xml.GetAttrib("UnderlineSelected");
	CAttrib::GetBool(str,sb.bUnderlineSelected);
	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,sb.bUnderline);

	str=xml.GetAttrib("StrikeOut");
	CAttrib::GetBool(str,sb.bStrikeOut);
	str=xml.GetAttrib("StrikeOutFocus");
	CAttrib::GetBool(str,sb.bStrikeOutFocus);
	str=xml.GetAttrib("StrikeOutSelected");
	CAttrib::GetBool(str,sb.bStrikeOutSelected);
	str=xml.GetAttrib("StrikeOutDisabled");
	CAttrib::GetBool(str,sb.bStrikeOutDisabled);

	//对齐方式
	UINT nAlignH=-1;
	CString strAlignH=xml.GetAttrib("AlignH");
	strAlignH.MakeLower();
	if(strAlignH=="left") nAlignH=DT_LEFT|DT_WORDBREAK;
	else if(strAlignH=="right") nAlignH=DT_RIGHT|DT_WORDBREAK;
	else if(strAlignH=="center") nAlignH=DT_CENTER|DT_WORDBREAK;

	UINT nAlignV=-1;
	CString strAlignV=xml.GetAttrib("AlignV");
	strAlignV.MakeLower();
	if(strAlignV=="top") nAlignV|=DT_TOP|DT_SINGLELINE;
	else if(strAlignV=="center") nAlignV|=DT_VCENTER|DT_SINGLELINE;
	else if(strAlignV=="bottom") nAlignV|=DT_BOTTOM|DT_SINGLELINE;

	if(nAlignH!=-1&&nAlignV!=-1)
		sb.nAlign=nAlignH | nAlignV;
	else if(nAlignH!=-1)
		sb.nAlign=nAlignH;
	else if(nAlignV!=-1)
		sb.nAlign=nAlignV;
	//光标
	HCURSOR hCursor=NULL;
	str=xml.GetAttrib("OutCursor");
	if(str!="") hCursor=LoadCursorFromFile(m_strSkinPath+str);
	if(!hCursor)
	{
		str=xml.GetAttrib("StdCursor");
		hCursor=CAttrib::GetStdCursor(str);
	}
	if(hCursor)
		sb.hCursor=hCursor;
}

void CMagicWnd::ReadStyleCheck(STYLE_CHECK &sc,CMarkup xml)
{
	CString str;
	//文本颜色
	str=xml.GetAttrib("TextColor");
	CAttrib::GetColor(str,sc.textColor);
	str=xml.GetAttrib("TextColorFocus");
	CAttrib::GetColor(str,sc.textColorFocus);
	str=xml.GetAttrib("TextColorSelected");
	CAttrib::GetColor(str,sc.textColorSelected);
	str=xml.GetAttrib("TextColorDisabled");
	CAttrib::GetColor(str,sc.textColorDisabled);
	//文本样式
	str=xml.GetAttrib("FontSize");
	if(str!="") sc.nFontSize=atoi(str);
	str=xml.GetAttrib("FontName");
	if(str!="") strcpy(sc.szFontName,str.GetBuffer(str.GetLength()));
	str=xml.GetAttrib("Bold");
	CAttrib::GetBool(str,sc.bBold);
	str=xml.GetAttrib("Italic");
	CAttrib::GetBool(str,sc.bItalic);
	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,sc.bUnderline);
	str=xml.GetAttrib("StrikeOut");
	CAttrib::GetBool(str,sc.bStrikeOut);

	//对齐方式
	UINT nAlignH=-1;
	CString strAlignH=xml.GetAttrib("AlignH");
	strAlignH.MakeLower();
	if(strAlignH=="left") nAlignH=DT_LEFT|DT_WORDBREAK;
	else if(strAlignH=="right") nAlignH=DT_RIGHT|DT_WORDBREAK;
	else if(strAlignH=="center") nAlignH=DT_CENTER|DT_WORDBREAK;

	UINT nAlignV=-1;
	CString strAlignV=xml.GetAttrib("AlignV");
	strAlignV.MakeLower();
	if(strAlignV=="top") nAlignV|=DT_TOP|DT_SINGLELINE;
	else if(strAlignV=="center") nAlignV|=DT_VCENTER|DT_SINGLELINE;
	else if(strAlignV=="bottom") nAlignV|=DT_BOTTOM|DT_SINGLELINE;

	if(nAlignH!=-1&&nAlignV!=-1)
		sc.nAlign=nAlignH | nAlignV;
	else if(nAlignH!=-1)
		sc.nAlign=nAlignH;
	else if(nAlignV!=-1)
		sc.nAlign=nAlignV;

	//图片路径
	str=xml.GetAttrib("BackGround");
	if(str!="") strcpy(sc.szBackGround,str.GetBuffer(str.GetLength()));
	str=xml.GetAttrib("Image");
	if(str!="") strcpy(sc.szImage,str.GetBuffer(str.GetLength()));
	//光标
	HCURSOR hCursor=NULL;
	str=xml.GetAttrib("OutCursor");
	if(str!="") hCursor=LoadCursorFromFile(m_strSkinPath+str);
	if(!hCursor)
	{
		str=xml.GetAttrib("StdCursor");
		hCursor=CAttrib::GetStdCursor(str);
	}
	if(hCursor)
		sc.hCursor=hCursor;
}

void CMagicWnd::ReadStyleRadio(STYLE_RADIO &sr,CMarkup xml)
{
	CString str;
	//文本颜色
	str=xml.GetAttrib("TextColor");
	CAttrib::GetColor(str,sr.textColor);
	str=xml.GetAttrib("TextColorFocus");
	CAttrib::GetColor(str,sr.textColorFocus);
	str=xml.GetAttrib("TextColorSelected");
	CAttrib::GetColor(str,sr.textColorSelected);
	str=xml.GetAttrib("TextColorDisabled");
	CAttrib::GetColor(str,sr.textColorDisabled);
	//文本样式
	str=xml.GetAttrib("FontSize");
	if(str!="") sr.nFontSize=atoi(str);
	str=xml.GetAttrib("FontName");
	if(str!="") strcpy(sr.szFontName,str.GetBuffer(str.GetLength()));
	str=xml.GetAttrib("Bold");
	CAttrib::GetBool(str,sr.bBold);
	str=xml.GetAttrib("Italic");
	CAttrib::GetBool(str,sr.bItalic);
	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,sr.bUnderline);
	str=xml.GetAttrib("StrikeOut");
	CAttrib::GetBool(str,sr.bStrikeOut);

	//对齐方式
	UINT nAlignH=-1;
	CString strAlignH=xml.GetAttrib("AlignH");
	strAlignH.MakeLower();
	if(strAlignH=="left") nAlignH=DT_LEFT|DT_WORDBREAK;
	else if(strAlignH=="right") nAlignH=DT_RIGHT|DT_WORDBREAK;
	else if(strAlignH=="center") nAlignH=DT_CENTER|DT_WORDBREAK;

	UINT nAlignV=-1;
	CString strAlignV=xml.GetAttrib("AlignV");
	strAlignV.MakeLower();
	if(strAlignV=="top") nAlignV|=DT_TOP|DT_SINGLELINE;
	else if(strAlignV=="center") nAlignV|=DT_VCENTER|DT_SINGLELINE;
	else if(strAlignV=="bottom") nAlignV|=DT_BOTTOM|DT_SINGLELINE;

	if(nAlignH!=-1&&nAlignV!=-1)
		sr.nAlign=nAlignH | nAlignV;
	else if(nAlignH!=-1)
		sr.nAlign=nAlignH;
	else if(nAlignV!=-1)
		sr.nAlign=nAlignV;

	//图片路径
	str=xml.GetAttrib("BackGround");
	if(str!="") strcpy(sr.szBackGround,str.GetBuffer(str.GetLength()));
	str=xml.GetAttrib("Image");
	if(str!="") strcpy(sr.szImage,str.GetBuffer(str.GetLength()));
	//光标
	HCURSOR hCursor=NULL;
	str=xml.GetAttrib("OutCursor");
	if(str!="") hCursor=LoadCursorFromFile(m_strSkinPath+str);
	if(!hCursor)
	{
		str=xml.GetAttrib("StdCursor");
		hCursor=CAttrib::GetStdCursor(str);
	}
	if(hCursor)
		sr.hCursor=hCursor;
}

void CMagicWnd::ReadStyleText(STYLE_TEXT &st,CMarkup xml)
{
	CString str;
	//文本颜色
	str=xml.GetAttrib("TextColor");
	CAttrib::GetColor(str,st.textColor);
	str=xml.GetAttrib("TextColorFocus");
	CAttrib::GetColor(str,st.textColorFocus);
	str=xml.GetAttrib("TextColorSelected");
	CAttrib::GetColor(str,st.textColorSelected);
	str=xml.GetAttrib("TextColorDisabled");
	CAttrib::GetColor(str,st.textColorDisabled);
	//边框颜色
	str=xml.GetAttrib("BorderColor");
	CAttrib::GetColor(str,st.borderColor);
	str=xml.GetAttrib("BorderColorFocus");
	CAttrib::GetColor(str,st.borderColorFocus);
	str=xml.GetAttrib("BorderColorSelected");
	CAttrib::GetColor(str,st.borderColorSelected);
	str=xml.GetAttrib("BorderColorDisabled");
	CAttrib::GetColor(str,st.borderColorDisabled);
	//文本样式
	str=xml.GetAttrib("FontSize");
	if(str!="") st.nFontSize=atoi(str);
	str=xml.GetAttrib("FontName");
	if(str!="") strcpy(st.szFontName,str.GetBuffer(str.GetLength()));
	
	str=xml.GetAttrib("Bold");
	CAttrib::GetBool(str,st.bBold);
	str=xml.GetAttrib("BoldFocus");
	CAttrib::GetBool(str,st.bBoldFocus);
	str=xml.GetAttrib("BoldSelected");
	CAttrib::GetBool(str,st.bBoldSelected);
	str=xml.GetAttrib("BoldDisabled");
	CAttrib::GetBool(str,st.bBoldDisabled);

	str=xml.GetAttrib("Italic");
	CAttrib::GetBool(str,st.bItalic);
	str=xml.GetAttrib("ItalicFocus");
	CAttrib::GetBool(str,st.bItalicFocus);
	str=xml.GetAttrib("ItalicSelected");
	CAttrib::GetBool(str,st.bItalicSelected);
	str=xml.GetAttrib("ItalicDisabled");
	CAttrib::GetBool(str,st.bItalicDisabled);

	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,st.bUnderline);
	str=xml.GetAttrib("UnderlineFocus");
	CAttrib::GetBool(str,st.bUnderlineFocus);
	str=xml.GetAttrib("UnderlineSelected");
	CAttrib::GetBool(str,st.bUnderlineSelected);
	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,st.bUnderline);

	str=xml.GetAttrib("StrikeOut");
	CAttrib::GetBool(str,st.bStrikeOut);
	str=xml.GetAttrib("StrikeOutFocus");
	CAttrib::GetBool(str,st.bStrikeOutFocus);
	str=xml.GetAttrib("StrikeOutSelected");
	CAttrib::GetBool(str,st.bStrikeOutSelected);
	str=xml.GetAttrib("StrikeOutDisabled");
	CAttrib::GetBool(str,st.bStrikeOutDisabled);

	//对齐方式
	UINT nAlignH=-1;
	CString strAlignH=xml.GetAttrib("AlignH");
	strAlignH.MakeLower();
	if(strAlignH=="left") nAlignH=DT_LEFT|DT_WORDBREAK;
	else if(strAlignH=="right") nAlignH=DT_RIGHT|DT_WORDBREAK;
	else if(strAlignH=="center") nAlignH=DT_CENTER|DT_WORDBREAK;

	UINT nAlignV=-1;
	CString strAlignV=xml.GetAttrib("AlignV");
	strAlignV.MakeLower();
	if(strAlignV=="top") nAlignV|=DT_TOP|DT_SINGLELINE;
	else if(strAlignV=="center") nAlignV|=DT_VCENTER|DT_SINGLELINE;
	else if(strAlignV=="bottom") nAlignV|=DT_BOTTOM|DT_SINGLELINE;

	if(nAlignH!=-1&&nAlignV!=-1)
		st.nAlign=nAlignH | nAlignV;
	else if(nAlignH!=-1)
		st.nAlign=nAlignH;
	else if(nAlignV!=-1)
		st.nAlign=nAlignV;
	//光标
	HCURSOR hCursor=NULL;
	str=xml.GetAttrib("OutCursor");
	if(str!="") hCursor=LoadCursorFromFile(m_strSkinPath+str);
	if(!hCursor)
	{
		str=xml.GetAttrib("StdCursor");
		hCursor=CAttrib::GetStdCursor(str);
	}
	if(hCursor)
		st.hCursor=hCursor;
}

void CMagicWnd::ReadStyleEdit(STYLE_EDIT &se,CMarkup xml)
{
	CString str;
	//文本颜色
	str=xml.GetAttrib("TextColor");
	CAttrib::GetColor(str,se.textColor);
	str=xml.GetAttrib("TextColorHover");
	CAttrib::GetColor(str,se.textColorHover);
	str=xml.GetAttrib("TextColorFocus");
	CAttrib::GetColor(str,se.textColorFocus);
	str=xml.GetAttrib("TextColorDisabled");
	CAttrib::GetColor(str,se.textColorDisabled);
	//背景颜色
	str=xml.GetAttrib("BackColor");
	CAttrib::GetColor(str,se.backColor);
	str=xml.GetAttrib("BackColorHover");
	CAttrib::GetColor(str,se.backColorHover);
	str=xml.GetAttrib("BackColorFocus");
	CAttrib::GetColor(str,se.backColorFocus);
	str=xml.GetAttrib("BackColorDisabled");
	CAttrib::GetColor(str,se.backColorDisabled);
	//边框颜色
	str=xml.GetAttrib("BorderColor");
	CAttrib::GetColor(str,se.borderColor);
	str=xml.GetAttrib("BorderColorHover");
	CAttrib::GetColor(str,se.borderColorHover);
	str=xml.GetAttrib("BorderColorFocus");
	CAttrib::GetColor(str,se.borderColorFocus);
	str=xml.GetAttrib("BorderColorDisabled");
	CAttrib::GetColor(str,se.borderColorDisabled);
	//文本样式
	str=xml.GetAttrib("FontSize");
	if(str!="") se.nFontSize=atoi(str);
	str=xml.GetAttrib("FontName");
	if(str!="") strcpy(se.szFontName,str.GetBuffer(str.GetLength()));
	str=xml.GetAttrib("Bold");
	CAttrib::GetBool(str,se.bBold);
	str=xml.GetAttrib("Italic");
	CAttrib::GetBool(str,se.bItalic);
	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,se.bUnderline);
	str=xml.GetAttrib("StrikeOut");
	CAttrib::GetBool(str,se.bStrikeOut);
	//对齐方式
	UINT nAlignH=-1;
	CString strAlignH=xml.GetAttrib("AlignH");
	strAlignH.MakeLower();
	if(strAlignH=="left") nAlignH=ES_LEFT;
	else if(strAlignH=="right") nAlignH=ES_RIGHT;
	else if(strAlignH=="center") nAlignH=ES_CENTER;
	if(nAlignH!=-1) se.nAlign=nAlignH;

	//是否密码框
	str=xml.GetAttrib("IsPassword");
	CAttrib::GetBool(str,se.bPassword);

	//光标
	HCURSOR hCursor=NULL;
	str=xml.GetAttrib("OutCursor");
	if(str!="") hCursor=LoadCursorFromFile(m_strSkinPath+str);
	if(!hCursor)
	{
		str=xml.GetAttrib("StdCursor");
		hCursor=CAttrib::GetStdCursor(str);
	}
	if(hCursor)
		se.hCursor=hCursor;
}

void CMagicWnd::ReadStyleCombo(STYLE_COMBO &sc,CMarkup xml)
{
	CString str;
	//文本颜色
	str=xml.GetAttrib("TextColor");
	CAttrib::GetColor(str,sc.textColor);
	str=xml.GetAttrib("TextColorHover");
	CAttrib::GetColor(str,sc.textColorHover);
	str=xml.GetAttrib("TextColorDisabled");
	CAttrib::GetColor(str,sc.textColorDisabled);
	//背景颜色
	str=xml.GetAttrib("BackColor");
	CAttrib::GetColor(str,sc.backColor);
	str=xml.GetAttrib("BackColorHover");
	CAttrib::GetColor(str,sc.backColorHover);
	str=xml.GetAttrib("BackColorDisabled");
	CAttrib::GetColor(str,sc.backColorDisabled);
	//边框颜色
	str=xml.GetAttrib("BorderColor");
	CAttrib::GetColor(str,sc.borderColor);
	//按钮背景颜色
	str=xml.GetAttrib("BtnColor");
	CAttrib::GetColor(str,sc.btnColor);
	//文本样式
	str=xml.GetAttrib("FontSize");
	if(str!="") sc.nFontSize=atoi(str);
	str=xml.GetAttrib("FontName");
	if(str!="") strcpy(sc.szFontName,str.GetBuffer(str.GetLength()));
	str=xml.GetAttrib("Bold");
	CAttrib::GetBool(str,sc.bBold);
	str=xml.GetAttrib("Italic");
	CAttrib::GetBool(str,sc.bItalic);
	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,sc.bUnderline);
	str=xml.GetAttrib("StrikeOut");
	CAttrib::GetBool(str,sc.bStrikeOut);

	//光标
	HCURSOR hCursor=NULL;
	str=xml.GetAttrib("OutCursor");
	if(str!="") hCursor=LoadCursorFromFile(m_strSkinPath+str);
	if(!hCursor)
	{
		str=xml.GetAttrib("StdCursor");
		hCursor=CAttrib::GetStdCursor(str);
	}
	if(hCursor)
		sc.hCursor=hCursor;
}

void CMagicWnd::ReadStyleGroup(STYLE_GROUP &sg,CMarkup xml)
{
	CString str;
	//文本颜色
	str=xml.GetAttrib("TextColor");
	CAttrib::GetColor(str,sg.textColor);
	//文本样式
	str=xml.GetAttrib("FontSize");
	if(str!="") sg.nFontSize=atoi(str);
	str=xml.GetAttrib("FontName");
	if(str!="") strcpy(sg.szFontName,str.GetBuffer(str.GetLength()));
	str=xml.GetAttrib("Bold");
	CAttrib::GetBool(str,sg.bBold);
	str=xml.GetAttrib("Italic");
	CAttrib::GetBool(str,sg.bItalic);
	str=xml.GetAttrib("Underline");
	CAttrib::GetBool(str,sg.bUnderline);
	str=xml.GetAttrib("StrikeOut");
	CAttrib::GetBool(str,sg.bStrikeOut);
	//对齐方式
	UINT nAlignH=-1;
	CString strAlignH=xml.GetAttrib("AlignH");
	strAlignH.MakeLower();
	if(strAlignH=="left") nAlignH=SS_LEFT;
	else if(strAlignH=="right") nAlignH=SS_RIGHT;
	else if(strAlignH=="center") nAlignH=SS_CENTER;
	if(nAlignH!=-1) sg.nAlign=nAlignH;
}

void CMagicWnd::ReadStyleRegion(STYLE_FILLREGION &sf,CMarkup xml)
{
	CString str;
	//背景颜色
	str=xml.GetAttrib("BackColor");
	CAttrib::GetColor(str,sf.backColor);
	str=xml.GetAttrib("BorderColor");
	CAttrib::GetColor(str,sf.borderColor);
	str=xml.GetAttrib("BorderWidth");
	if(str!="") sf.borderWidth=atoi(str);
	str=xml.GetAttrib("Corner");
	if(str!="") sf.nCorner=atoi(str);
	str=xml.GetAttrib("Alpha");
	if(str!="") sf.nAlpha=atoi(str);
}

BOOL CMagicWnd::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_toolTip.m_hWnd!=NULL)
		m_toolTip.RelayEvent(pMsg);
	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CMagicWnd::OnRadioBox(WPARAM wParam,LPARAM lParam)
{
	for(int i=0;i<m_aryControl.GetSize();i++)
	{
		CTRL_INFO ctrlInfo;
		ctrlInfo=m_aryControl.GetAt(i);
		if(ctrlInfo.nType==MAGICUI_RADIO)
		{
			CMagicRadio *pWnd=(CMagicRadio *)ctrlInfo.pWnd;
			if(pWnd->GetGroupID()==(UINT)lParam)
			{
				if(pWnd->m_hWnd==(HWND)wParam)
					pWnd->SetSelect(TRUE);
				else
					pWnd->SetSelect(FALSE);
			}
		}
	}

	return 0;
}

BOOL CMagicWnd::FindUserStyle(CString strLabel, CMarkup &xml)
{
	//加载xml
	CString strPath(m_strSkinPath+m_strGlobalXml);
	if(!xml.Load(strPath))
		return FALSE;

	//查找根结点
	xml.ResetMainPos();
	if(!xml.FindElem())
		return FALSE;
	xml.IntoElem();

	while(xml.FindElem())
	{
		CString strTagName=xml.GetTagName();
		if(strTagName==strLabel)
			return TRUE;
	}

	return FALSE;
}

CWnd* CMagicWnd::GetWndByName(CString strName)
{
	for(int i=0;i<m_aryControl.GetSize();i++)
	{
		CTRL_INFO ctrlInfo;
		ctrlInfo=m_aryControl.GetAt(i);
		if(ctrlInfo.strName==strName)
			return ctrlInfo.pWnd;
	}

	return NULL;
}
