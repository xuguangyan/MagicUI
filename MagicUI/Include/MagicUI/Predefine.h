///////////////////////////////////////////////////////////////////////////////////
//  文件名: Predefine.h												[Magic UI]		
///////////////////////////////////////////////////////////////////////////////////
//																				
//  描述:
//
//		Magic 用户界面库预定义
//
//  创建日期: 2008-12-3
///////////////////////////////////////////////////////////////////////////////////
// 			Magic UI Workstation reserved all rights. 2008 - 2009			 
///////////////////////////////////////////////////////////////////////////////////

#ifndef _GUI_PREDEFINE_INCLUDE_H_
#define _GUI_PREDEFINE_INCLUDE_H_

#if (_MSC_VER >= 1300)
#pragma once
#endif

#include <afxtempl.h>

#define _GUI_NAME					_T("MagicUI")
#define _GUI_LIB_NAME				_T("MagicUI.lib")
#define _GUI_MODULE_NAME			_T("MagicUI.dll")

#ifdef  _GUI_MAKE_DLL
		#define GUI_EXT_CLASS	_declspec(dllexport)
#else
		#define GUI_EXT_CLASS	_declspec(dllimport)
		//#pragma comment( lib, _GUI_LIB_NAME) 
#endif // end of _GUI_MAKE_DLL

#endif // end of _GUI_PREDEFINE_INCLUDE_H_