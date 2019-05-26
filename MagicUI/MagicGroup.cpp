//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicGroup.cpp												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库群组框实现
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Include/MagicUI/MagicGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicGroup,CStatic);

CMagicGroup::CMagicGroup()
{
	m_textColor=GetSysColor(COLOR_BTNTEXT);
	m_nAlign=SS_LEFT;
	m_bVisible=TRUE;//控件可视
	m_bEnable=TRUE;//控件可用
}

CMagicGroup::~CMagicGroup()
{
}


BEGIN_MESSAGE_MAP(CMagicGroup, CStatic)
	//{{AFX_MSG_MAP(CMagicGroup)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicGroup message handlers

//重载创建函数
BOOL CMagicGroup::Create(LPCTSTR lpszCaption, DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(dwStyle & WS_DISABLED)
		m_bEnable=FALSE;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD|SS_USERITEM;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create(lpszCaption,dwStyle,rect,pParentWnd,nID);
}

//自动加载
BOOL CMagicGroup::AutoLoad(UINT nID, CWnd* pParent)
{
	m_nID=nID;
	m_pWnd=pParent;
	CStatic* pPic=(CStatic *)pParent->GetDlgItem(nID);
	
	CRect rect;
	pPic->GetClientRect(&rect);
	pPic->ClientToScreen(&rect);
	pParent->ScreenToClient(&rect);

	CString str;
	pPic->GetWindowText(str);
	pPic->ShowWindow(SW_HIDE);

	DWORD dwStyle=WS_CHILD|WS_VISIBLE|SS_USERITEM;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create(str,dwStyle,rect,pParent,nID);
}
HBRUSH CMagicGroup::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	CRect rc;
	GetClientRect(&rc);
	//绘背景
	DrawOriginalBitmap(pDC,rc,m_backgndMask);
	if(!m_bVisible)
		return NULL;

	int y;
	switch(m_nAlign)
	{
	case SS_LEFT:
		y=5;
		break;
	case SS_RIGHT:
		y=rc.Width()-m_szText.cx-5;
		break;
	case SS_CENTER:
		y=(rc.Width()-m_szText.cx)/2;
		break;
	}
	CRect rcText=CRect(CPoint(y,0),m_szText);
	CRect rcBox=rc+CRect(0,-m_szText.cy/2,0,0);

	CString str;
	GetWindowText(str);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_textColor);
	pDC->DrawText(str,rcText,DT_LEFT|DT_TOP);
	pDC->BeginPath();
	pDC->Rectangle(rcText);
	pDC->EndPath();
	pDC->SelectClipPath(RGN_DIFF);
	pDC->DrawEdge(rcBox,EDGE_ETCHED,BF_RECT);
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}

//设字体颜色
void CMagicGroup::SetTextColor(COLORREF textColor)
{
	m_textColor=textColor;

	Invalidate();
}

//对齐方式
void CMagicGroup::SetAlign(UINT nAlign)
{
	m_nAlign=nAlign;

	Invalidate();
}

//设置字体
void CMagicGroup::SetFont(int nFontSize,CString strFontName,BOOL bBold,BOOL bItalic,
					BOOL bUnderline,BOOL bStrikeOut)
{
	CClientDC dc(this);
	int nHeight=MulDiv(nFontSize,GetDeviceCaps(dc.m_hDC,LOGPIXELSY),72);

	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfWidth=0;//字体宽度(默认)
	lf.lfHeight=nHeight;//字体高度
	strcpy(lf.lfFaceName,strFontName.GetBuffer(strFontName.GetLength()));//字体名称
	lf.lfWeight=bBold?FW_BOLD:FW_NORMAL;//粗体
	lf.lfItalic=bItalic;//斜体
	lf.lfUnderline=bUnderline;//下划线
	lf.lfStrikeOut=bStrikeOut;//删除线

	if(m_font.m_hObject)
		m_font.DeleteObject();
	m_font.CreateFontIndirect(&lf);

	Invalidate();
}

//获取要创建区域的父窗口背景
void CMagicGroup::GetBackgndMask()
{
		CWnd *pParentWnd=GetParent();
		CClientDC pdc(pParentWnd);

		CRect rc;
		GetClientRect(&rc);
		ClientToScreen(&rc);
		pParentWnd->ScreenToClient(&rc);

		CClientDC dc(this);
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		if(m_backgndMask.m_hObject)
			m_backgndMask.DeleteObject();
		m_backgndMask.CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
		memDC.SelectObject(&m_backgndMask);
		memDC.BitBlt(0,0,rc.Width(),rc.Height(),&pdc,rc.left,rc.top,SRCCOPY);
}

//绘普通位图
void CMagicGroup::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

BOOL CMagicGroup::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();

	CString str;
	GetWindowText(str);
	pDC->SelectObject(&m_font);
	m_szText=pDC->GetTextExtent(str);

	return TRUE;
}

BOOL CMagicGroup::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
		m_bVisible=FALSE;
	else
		m_bVisible=TRUE;

	Invalidate();

	return TRUE;
}

BOOL CMagicGroup::GetVisible()
{
	return m_bVisible;
}
