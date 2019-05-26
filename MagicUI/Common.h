//////////////////////////////////////////////////////////////////////////////////
//  文件名: Common.h											     	[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 通用类(实现独立功能)
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////
#ifndef _MAGICUI_COMMON_H_
#define _MAGICUI_COMMON_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WS_EX_LAYERED	0x80000  
#define LWA_ALPHA		0x2  
#define LWA_COLORKEY	0x1

class CCommon  
{
public:
	//获取应用程序路径
	static CString GetAppPath();
	//数值转换为字符串
	static CString IntToStr(int nNum,int nSize,BOOL bFull=FALSE);
	//十六进制串转换为数值
	static int HexToInt(CString strHex);
	//判断是否为十六进制字符
	static BOOL IsHexLetter(char ch);
	//判断是否为十六进制数
	static BOOL IsHexNumber(CString str);
	//判断是否为数值
	static BOOL IsNumber(CString str);
	//判断是否为时间格式
	static BOOL IsTimer(CString str);
	//毫秒转换为时间格式
	static CString GetTimeStr(int nTime);
	//数值转换为十六进制串
	static CString IntToHex(int nNum, int nSize, BOOL bFull=FALSE);
	//字符串拆分
	static int SplitString(CString str, char chSplitter, CStringArray& aryItem);
	//设置窗口透明
	static void SetAlpha(HWND hWnd,COLORREF clrMask,int alpha,DWORD dwFlags);//设置窗体透明
	CCommon();
	virtual ~CCommon();

};

#endif //_MAGICUI_COMMON_H_
