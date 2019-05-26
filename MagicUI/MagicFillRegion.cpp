//////////////////////////////////////////////////////////////////////////////////
//  文件名: MagicFillRegion.cpp											[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库填充区实现
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Include/MagicUI/MagicFillRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
using namespace GUI;

IMPLEMENT_DYNAMIC(CMagicFillRegion,CStatic);

CMagicFillRegion::CMagicFillRegion()
{
	m_bVisible=TRUE;//控件可视
	m_nAlpha=0;//透明度
	m_backColor=RGB(236,243,246);//背景色
	m_borderColor=RGB(0,136,228);//边框色
	m_borderWidth=2;//边框宽
	m_nCorner=10;//圆角大小
}

CMagicFillRegion::~CMagicFillRegion()
{
}


BEGIN_MESSAGE_MAP(CMagicFillRegion, CStatic)
	//{{AFX_MSG_MAP(CMagicFillRegion)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicFillRegion message handlers

//重载创建函数
BOOL CMagicFillRegion::Create(DWORD dwStyle,const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_nID=nID;
	m_pWnd=pParentWnd;

	if(!(dwStyle & WS_VISIBLE))
		m_bVisible=FALSE;

	dwStyle|=WS_CHILD|SS_USERITEM;
	if(nID!=0xffff)
		dwStyle|=SS_NOTIFY;

	return CStatic::Create("",dwStyle,rect,pParentWnd,nID);
}
HBRUSH CMagicFillRegion::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	CRect rc;
	GetClientRect(&rc);
	if(!m_bVisible)
	{
		//绘背景
		DrawOriginalBitmap(pDC,rc,m_backgndMask);
		return NULL;
	}

	int clr=(int)(2.55*m_nAlpha);

	//不透明DC
	CDC alphaNDC;
	alphaNDC.CreateCompatibleDC(pDC);
	//黑色位图
	CBitmap bmpAlphaN;
	bmpAlphaN.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
	alphaNDC.SelectObject(&bmpAlphaN);
	//完成灰度图
	alphaNDC.FillSolidRect(rc,RGB(255-clr,255-clr,255-clr));

	//背景图DC
	CDC backDC;
	backDC.CreateCompatibleDC(&alphaNDC);
	//完成背景图
	backDC.SelectObject(&m_backgndMask);

	//透明DC
	CDC alphaDC;
	alphaDC.CreateCompatibleDC(pDC);
	//黑色位图
	CBitmap bmpAlpha;
	bmpAlpha.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
	alphaDC.SelectObject(&bmpAlpha);
	//完成灰度图
	alphaDC.FillSolidRect(rc,RGB(clr,clr,clr));

	//原图DC
	CDC srcDC;
	srcDC.CreateCompatibleDC(&alphaDC);
	//黑色位图
	CBitmap bmpSrc;
	bmpSrc.CreateCompatibleBitmap(&alphaDC,rc.Width(),rc.Height());
	srcDC.SelectObject(&bmpSrc);
	//原图画刷
	CBrush brSrc;
	brSrc.CreateSolidBrush(m_backColor);
	srcDC.SelectObject(&brSrc);
	//原图画笔
	CPen penSrc;
	penSrc.CreatePen(PS_SOLID,m_borderWidth,m_borderColor);
	srcDC.SelectObject(&penSrc);
	//完成原图
	srcDC.RoundRect(rc,CPoint(m_nCorner,m_nCorner));

	//DC运算=>(alphaNDC OR backDC) AND (alphaDC OR srcDC)
	alphaNDC.BitBlt(0,0,rc.Width(),rc.Height(),&backDC,0,0,SRCPAINT);
	alphaDC.BitBlt(0,0,rc.Width(),rc.Height(),&srcDC,0,0,SRCPAINT);

	pDC->BeginPath();
	pDC->RoundRect(rc,CPoint(m_nCorner,m_nCorner));
	pDC->EndPath();
	pDC->SelectClipPath(RGN_AND);

	pDC->BitBlt(0,0,rc.Width(),rc.Height(),&alphaNDC,0,0,SRCCOPY);
	pDC->BitBlt(0,0,rc.Width(),rc.Height(),&alphaDC,0,0,SRCAND);
	
	return NULL;
}

//获取要创建区域的父窗口背景
void CMagicFillRegion::GetBackgndMask()
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
void CMagicFillRegion::DrawOriginalBitmap(CDC *pDC, CRect rect,CBitmap &foreBmp)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&foreBmp);

	BITMAP bit;
	foreBmp.GetBitmap(&bit);

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
}

BOOL CMagicFillRegion::OnEraseBkgnd(CDC* pDC)
{
	if(!m_backgndMask.m_hObject)
		GetBackgndMask();

	return TRUE;
}

BOOL CMagicFillRegion::ShowWindow(int nCmdShow)
{
	if(nCmdShow==SW_HIDE)
		m_bVisible=FALSE;
	else
		m_bVisible=TRUE;

	Invalidate();

	return TRUE;
}

BOOL CMagicFillRegion::GetVisible()
{
	return m_bVisible;
}

//设背景颜色
void CMagicFillRegion::SetBackColor(COLORREF backColor)
{
	m_backColor=backColor;
	Invalidate();
}

//设边框颜色
void CMagicFillRegion::SetBorderColor(COLORREF borderColor)
{
	m_borderColor=borderColor;
	Invalidate();
}

//设边框宽度
void CMagicFillRegion::SetBorderWidth(int nWidth)
{
	m_borderWidth=nWidth;
	Invalidate();
}

//设圆角大小
void CMagicFillRegion::SetCorner(int nSize)
{
	m_nCorner=nSize;
	Invalidate();
}

//设透明度
void CMagicFillRegion::SetAlpha(int nAlpha)
{
	m_nAlpha=nAlpha;
	Invalidate();
}