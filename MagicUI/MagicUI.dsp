# Microsoft Developer Studio Project File - Name="MagicUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MagicUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MagicUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MagicUI.mak" CFG="MagicUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MagicUI - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MagicUI - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MagicUI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "MagicUI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 lib/GdiPlus.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"dll/MagicUI.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MagicUI - Win32 Release"
# Name "MagicUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Attrib.cpp
# End Source File
# Begin Source File

SOURCE=.\Common.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicButton.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicFillRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicRadio.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicText.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicUI.cpp
# End Source File
# Begin Source File

SOURCE=.\MagicUI.def
# End Source File
# Begin Source File

SOURCE=.\MagicUI.rc
# End Source File
# Begin Source File

SOURCE=.\MagicWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Markup.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "GdiPlus"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlus.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusBase.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusBitmap.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusBrush.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusCachedBitmap.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusColor.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusColorMatrix.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusEnums.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusFlat.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusFont.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusFontCollection.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusFontFamily.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusGpStubs.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusGraphics.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusHeaders.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusimageAttributes.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusImageCodec.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusImaging.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusInit.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusLineCaps.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusMatrix.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusMem.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusMetaFile.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusMetaHeader.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusPath.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusPen.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusPixelFormats.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusRegion.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusStringFormat.h
# End Source File
# Begin Source File

SOURCE=.\Include\GdiPlus\GdiPlusTypes.h
# End Source File
# Begin Source File

SOURCE=.\MagicCheck.h
# End Source File
# End Group
# Begin Group "MagicUI"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\Include\MagicUI\DataDefine.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\GUI_Export.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicButton.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicCheck.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicCombo.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicEdit.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicFillRegion.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicGroup.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicPicture.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicRadio.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicText.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicUI.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\MagicWnd.h
# End Source File
# Begin Source File

SOURCE=.\Include\MagicUI\Predefine.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Attrib.h
# End Source File
# Begin Source File

SOURCE=.\Common.h
# End Source File
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MagicUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\MagicUI.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
