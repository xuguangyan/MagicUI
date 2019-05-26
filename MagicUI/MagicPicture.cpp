//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicPicture.cpp											[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库图片实现
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Include/MagicUI/MagicPicture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicPicture,CStatic);

CMagicPicture::CMagicPicture()
{
	m_nStyle=PS_FIXSIZE;
	m_bMask=FALSE;
	m_pWnd=NULL;
	m_xoffset=0;
	m_yoffset=0;
	m_xorign=0;
	m_yorign=0;
	m_xMax=0;
	m_yMax=0;
	
	m_bVisible=TRUE;//控件可视
	m_bEnable=TRUE;//控件可用
	m_bMouseDown=FALSE;
	m_nDrawMode=DRAW_MODE_COLOR;
	m_hCursor=LoadCursor(NULL,IDC_ARROW);//箭头光标
}

CMagicPicture::~CMagicPicture()
{
}


BEGIN_MESSAGE_MAP(CMagicPicture, CStatic)
	//{{AFX_MSG_MAP(CMagicPicture)
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicPicture message handlers

//重载创建函数
BOOL CMagicPicture::Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(dwStyle & WS_DISABLED)
		m_bEnable=FALSE;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD;
	dwStyle|=SS_BITMAP;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create("",dwStyle,rect,pParentWnd,nID);
}

//自动加载
BOOL CMagicPicture::AutoLoad(UINT nID, CWnd* pParent)
{
	m_nID=nID;
	m_pWnd=pParent;
	CStatic* pPic=(CStatic *)pParent->GetDlgItem(nID);
	
	CRect rect;
	pPic->GetClientRect(&rect);
	pPic->ClientToScreen(&rect);
	pParent->ScreenToClient(&rect);
	pPic->ShowWindow(SW_HIDE);

	DWORD dwStyle=WS_CHILD|WS_VISIBLE|SS_BITMAP;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create("",dwStyle,rect,pParent,nID);
}

BOOL CMagicPicture::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(m_hCursor);
	return true;

	//return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CMagicPicture::SetBitmap(CBitmap &bitmap)
{
	if(bitmap.m_hObject)
	{
		if(m_background.m_hObject)
			m_background.DeleteObject();
		if(m_background.Attach(bitmap.m_hObject))
		{
			m_nDrawMode=DRAW_MODE_BITMAP;
			Invalidate();
		}
	}
}

void CMagicPicture::SetBitmap(UINT nResID)
{
	if(m_background.m_hObject)
		m_background.DeleteObject();
	if(m_background.LoadBitmap(nResID))
	{
		m_nDrawMode=DRAW_MODE_BITMAP;
		Invalidate();
	}
}

void CMagicPicture::SetBitmap(LPCTSTR lpszFileName)
{
	HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),lpszFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(hBitmap)
	{
		if(m_background.m_hObject)
			m_background.DeleteObject();
		if(m_background.Attach(hBitmap))
		{
			m_nDrawMode=DRAW_MODE_BITMAP;
			Invalidate();
		}
	}
}

void CMagicPicture::SetBitmap(HBITMAP hBitmap)
{
	if(hBitmap)
	{
		if(m_background.m_hObject)
			m_background.DeleteObject();
		if(m_background.Attach(hBitmap))
		{
			m_nDrawMode=DRAW_MODE_BITMAP;
			Invalidate();
		}
	}
}

void CMagicPicture::SetImage(LPCTSTR lpszFileName)
{
	if(strlen(lpszFileName)<3) return ;
	if(lpszFileName[1]!=':')
	{
		TCHAR szDrive[_MAX_DRIVE];
		TCHAR szDir[_MAX_DIR];
		TCHAR szFullPath[_MAX_PATH];

		::GetModuleFileName(NULL,szFullPath,_MAX_PATH); 
		_tsplitpath(szFullPath,szDrive,szDir,NULL,NULL);
		_tmakepath(m_backgndPath,szDrive,szDir,lpszFileName,NULL);
	}
	else
		strcpy(m_backgndPath,lpszFileName);

	m_nDrawMode=DRAW_MODE_IMAGE;
	Invalidate();
}

void CMagicPicture::SetCursor(HCURSOR hCursor)
{
	m_hCursor=hCursor;
	Invalidate();
}

//获取要创建区域的父窗口背景
void CMagicPicture::GetBackgndMask()
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

//绘透明位图
void CMagicPicture::DrawTransparentBitmap(CDC *pDC,CRect rect,
									  CBitmap &foreBmp,COLORREF maskColor,CRect rc)
{ 
	CDC foreDC,maskDC,tempDC;

	//获取前景信息
	BITMAP bit;
	foreBmp.GetBitmap(&bit);
	//创建临时DC,选入前景位图
	tempDC.CreateCompatibleDC(pDC); 
	tempDC.SelectObject(&foreBmp);
 
	//###前景DC创建###
	//创建临时位图(用来复制前景位图,以便操作后前景不被修改)
	CBitmap tempBmp;
	tempBmp.CreateCompatibleBitmap(&tempDC,bit.bmWidth,bit.bmHeight);
	//创建前景DC,选入临时位图,并将前景位图贴入(即实现前景位图复制)
	foreDC.CreateCompatibleDC(pDC); 
	foreDC.SelectObject(&tempBmp); 
	foreDC.BitBlt(0,0,bit.bmWidth,bit.bmHeight,&tempDC,0,0,SRCCOPY);
	
	//###摭掩DC创建###
	//创建摭掩位图(初始为黑色)
	CBitmap maskBmp;
	maskBmp.CreateBitmap(bit.bmWidth,bit.bmHeight,1,1,NULL);
	//创建摭掩DC
	maskDC.CreateCompatibleDC(pDC); 
	maskDC.SelectObject(&maskBmp); 
	
	//###摭掩DC修改###
	foreDC.SetBkColor(maskColor); 
	maskDC.BitBlt(0,0,bit.bmWidth,bit.bmHeight,&foreDC,0,0,SRCCOPY); 
	
	//###前景DC修改###
	foreDC.SetBkColor(RGB(0,0,0)); 
	foreDC.SetTextColor(RGB(255,255,255)); 
	foreDC.BitBlt(0,0,bit.bmWidth,bit.bmHeight,&maskDC,0,0,SRCAND); 
	
	//(pDC & mask) | fore=>输出
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&maskDC,rc.left,rc.top,rc.Width(),rc.Height(),SRCAND); 
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&foreDC,rc.left,rc.top,rc.Width(),rc.Height(),SRCPAINT);
}

//绘普通位图
void CMagicPicture::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

//绘GDI+图
void CMagicPicture::DrawImage(CDC *pDC,CRect rect,LPCTSTR lpszFileName,CRect rc)
{
	USES_CONVERSION;
	Image img(A2W(lpszFileName));
	if(img.GetLastStatus()!=Ok) return ;

	Graphics graphics(pDC->m_hDC);
	graphics.DrawImage(&img,RectF(0,0,(float)rect.Width(),(float)rect.Height()),
		(float)rc.left,(float)rc.top,(float)rc.Width(),(float)rc.Height(),UnitPixel);
}

void CMagicPicture::SetMaskColor(COLORREF color)
{
	m_bMask=TRUE;
	m_maskColor=color;
}

void CMagicPicture::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	//创建兼容DC
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&m_background);

	//获取图像大小
	int bx=0,by=0;
	if(m_nDrawMode==DRAW_MODE_IMAGE)
	{
		USES_CONVERSION;
		Image img(A2W(m_backgndPath));
		if(img.GetLastStatus()==Ok)
		{
			bx=img.GetWidth();
			by=img.GetHeight();
		}
	}
	else
	{
		if(m_background.m_hObject)
		{
			BITMAP bit;
			m_background.GetBitmap(&bit);
			bx=bit.bmWidth;
			by=bit.bmHeight;
		}
	}

	//调整窗口大小
	if(m_nStyle & PS_AUTOSIZE)
		SetWindowPos(NULL,0,0,bx,by,SWP_NOZORDER|SWP_NOMOVE);
	//获取窗口大小
	CRect rect;
	GetClientRect(&rect);
	int cx=rect.Width();
	int cy=rect.Height();

	//绘图过程

	//绘背景
	DrawOriginalBitmap(&dc,rect,m_backgndMask);
	if(!m_bVisible) return;

	//给PS_FIXSIZE样式,添加滚动条
	if(m_nStyle & PS_FIXSIZE && m_nStyle & PS_SCROLL)
	{
		if((bx>cx||by>cy) && cy>10 && cx>10)
		{
			cx-=10;cy-=10;
			if(!m_HScroll.m_hWnd)
				m_HScroll.Create(WS_CHILD|WS_VISIBLE|SBS_HORZ,CRect(0,cy,cx,cy+10),this,998);
			if(!m_VScroll.m_hWnd)
				m_VScroll.Create(WS_CHILD|WS_VISIBLE|SBS_VERT,CRect(cx,0,cx+10,cy),this,999);
			if(bx>cx)
			{
				m_xMax=bx-cx;
				m_HScroll.SetScrollRange(0,m_xMax);
			}
			else
				m_HScroll.EnableWindow(FALSE);
			if(by>cy)
			{
				m_yMax=by-cy;
				m_VScroll.SetScrollRange(0,m_yMax);
			}
			else
				m_VScroll.EnableWindow(FALSE);
		}
	}

	CRect rc(0,0,bx,by);
	if(m_nStyle & PS_FIXSIZE)
		rc=CRect(m_xoffset,m_yoffset,m_xoffset+cx,m_yoffset+cy);

	if(m_nDrawMode==DRAW_MODE_IMAGE)
		DrawImage(&dc,rect,m_backgndPath,rc);
	else
	{
		if(m_bMask)
			DrawTransparentBitmap(&dc,rect,m_background,m_maskColor,rc);
		else
			dc.StretchBlt(0,0,cx,cy,&memDC,rc.left,rc.top,rc.Width(),rc.Height(),SRCCOPY);
	}

	//添加边框
	if(m_nStyle & PS_BORDER)
		dc.Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));

	if(m_nStyle & PS_FIXSIZE && m_nStyle & PS_SCROLL)
	{
		CRect rc=CRect(cx,cy,cx+10,cy+10);
		CBrush brush;
		brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
		dc.FillRect(rc,&brush);
		dc.Draw3dRect(rc,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
	}
	// Do not call CStatic::OnPaint() for painting messages
}

void CMagicPicture::SetStyle(UINT nStyle)
{
	m_nStyle=nStyle;
	Invalidate();
}

void CMagicPicture::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nSBCode)
	{
	case SB_THUMBPOSITION:
		m_xoffset=nPos;
		pScrollBar->SetScrollPos(nPos);
		Invalidate();
		break;
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		m_xoffset+=5;
		if(m_xoffset>m_xMax) m_xoffset=m_xMax;
		pScrollBar->SetScrollPos(m_xoffset);
		Invalidate();
		break;
	case SB_LINELEFT:
	case SB_PAGELEFT:
		m_xoffset-=5;
		if(m_xoffset<0) m_xoffset=0;
		pScrollBar->SetScrollPos(m_xoffset);
		Invalidate();
		break;
	}
	CStatic::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMagicPicture::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nSBCode)
	{
	case SB_THUMBPOSITION:
		m_yoffset=nPos;
		pScrollBar->SetScrollPos(nPos);
		Invalidate();
		break;
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		m_yoffset+=5;
		if(m_yoffset>m_yMax) m_yoffset=m_yMax;
		pScrollBar->SetScrollPos(m_yoffset);
		Invalidate();
		break;
	case SB_LINELEFT:
	case SB_PAGELEFT:
		m_yoffset-=5;
		if(m_yoffset<0) m_yoffset=0;
		pScrollBar->SetScrollPos(m_yoffset);
		Invalidate();
		break;
	}
	CStatic::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMagicPicture::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_nStyle & PS_FIXSIZE && m_nStyle & PS_SCROLL)
	{
		m_bMouseDown=TRUE;
		m_xorign=m_xoffset+point.x;
		m_yorign=m_yoffset+point.y;

		//捕捉鼠标
		TRACKMOUSEEVENT tme;   
		tme.cbSize=sizeof(tme);   
		tme.hwndTrack=m_hWnd;   
		tme.dwFlags=TME_LEAVE;   
		_TrackMouseEvent(&tme);
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CMagicPicture::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bMouseDown)
	{
		m_xoffset=(m_xorign-point.x);
		m_yoffset=(m_yorign-point.y);
		if(m_xoffset<0) m_xoffset=0;
		if(m_xoffset>m_xMax) m_xoffset=m_xMax;
		if(m_yoffset<0) m_yoffset=0;
		if(m_yoffset>m_yMax) m_yoffset=m_yMax;
		m_HScroll.SetScrollPos(m_xoffset);
		m_VScroll.SetScrollPos(m_yoffset);

		CRect rc;
		GetClientRect(&rc);
		InvalidateRect(CRect(0,0,rc.right-10,rc.bottom-10));
	}
	CStatic::OnMouseMove(nFlags, point);
}

void CMagicPicture::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseDown=FALSE;
	CStatic::OnLButtonUp(nFlags, point);
}

LRESULT CMagicPicture::OnMouseLeave(WPARAM wParam,LPARAM lParam)   
{
	m_bMouseDown=FALSE;
	return TRUE;
}

BOOL CMagicPicture::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();
	return TRUE;
}

BOOL CMagicPicture::EnableWindow(BOOL bEnable)
{
	m_bEnable=bEnable;
	Invalidate();

	if(m_bEnable)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return TRUE;
}

BOOL CMagicPicture::GetEnable()
{
	return m_bEnable;
}

BOOL CMagicPicture::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
	{
		m_bVisible=FALSE;

		BOOL m_bOldVisible=m_bEnable;
		EnableWindow(FALSE);
		m_bEnable=m_bOldVisible;
	}
	else
	{
		m_bVisible=TRUE;
		EnableWindow(m_bEnable);
	}

	Invalidate();

	return TRUE;
}

BOOL CMagicPicture::GetVisible()
{
	return m_bVisible;
}