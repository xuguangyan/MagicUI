//////////////////////////////////////////////////////////////////////////////////
//  文件名: Attrib.h											     	[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 实现xml标签属性解析
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_ATTRIB_H_
#define _MAGICUI_ATTRIB_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if(WINVER < 0x0500)
#define IDC_HAND            MAKEINTRESOURCE(32649)
#endif

#include "Common.h"

class CAttrib  
{
public:
	static BOOL GetPoint(CString strPoint,CPoint &pt);
	static BOOL GetSize(CString strSize,CSize &sz);
	static BOOL GetBool(CString strBool,BOOL &bBool);
	static BOOL GetColor(CString strColor,COLORREF &color);
	static BOOL GetRect(CString strRect,CPoint &pt,CSize &sz);
	static BOOL GetRect(CString strRect,CRect &rect);
	static HCURSOR GetStdCursor(CString strName);
	CAttrib();
	virtual ~CAttrib();

};

#endif //_MAGICUI_ATTRIB_H_
