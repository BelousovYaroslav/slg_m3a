# Microsoft Developer Studio Project File - Name="slg2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=slg2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "slg2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "slg2.mak" CFG="slg2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "slg2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "slg2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "slg2 - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Od /D "NI_MEASUREMENT_STUDIO" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 NiInterface.lib mfcs42.lib ivi.lib instrsup.lib winmm.lib version.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc" /out:"Release\slg2_viewer.exe"

!ELSEIF  "$(CFG)" == "slg2 - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "NI_MEASUREMENT_STUDIO" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 NiInterfaceD.lib mfcs42d.lib ivi.lib instrsup.lib winmm.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /out:"Debug/slg2_viewer.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "slg2 - Win32 Release"
# Name "slg2 - Win32 Debug"
# Begin Group "Measurement Studio"

# PROP Default_Filter ""
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\Ni4882.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiAll.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiAxes.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiAxes3d.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiAxis.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiAxis3d.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiBinding.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiBindings.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiButton.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiColor.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiCommon.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiComplex.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiComplexMatrix.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiComplexVector.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiContour.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiContours.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiControlMetrics.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiCursor.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiCursors.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiDataSocket.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiDataTypes.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiException.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiFile.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiFont.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiGraph.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiGraph3d.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiImage.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiKnob.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiLabels.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiLabels3d.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiLight.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiLights.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiMath.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiMatrix.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiNumedit.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiPicture.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiPlot.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiPlot3d.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiPlots.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiPlots3d.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiPointer.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiPointers.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiScalarMatrix.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiScalarVector.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiSlide.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiSound.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiString.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiSystem.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiTicks.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiTicks3d.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiTimer.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiUtility.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiValuepair.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiValuepairs.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiVariant.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiVector.h"
# End Source File
# Begin Source File

SOURCE="$(MSTUDIO_CPP_PATH)\Include\NiVisa.h"
# End Source File
# End Group
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgAlanCurve.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExport.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHisto.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainView.cpp
# End Source File
# Begin Source File

SOURCE=.\MyPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenMeasDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Serial.cpp
# End Source File
# Begin Source File

SOURCE=.\slg2.cpp
# End Source File
# Begin Source File

SOURCE=.\slg2.rc
# End Source File
# Begin Source File

SOURCE=.\slg2Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\slg2View.cpp
# End Source File
# Begin Source File

SOURCE=.\SlgCircleBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\SlgMeasurement.cpp
# End Source File
# Begin Source File

SOURCE=.\SlgNewAverager.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WizardSelComPortStep.cpp
# End Source File
# Begin Source File

SOURCE=.\WizardSelRunTypeStep.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgAlanCurve.h
# End Source File
# Begin Source File

SOURCE=.\DlgExport.h
# End Source File
# Begin Source File

SOURCE=.\DlgHisto.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainView.h
# End Source File
# Begin Source File

SOURCE=.\MyPoint.h
# End Source File
# Begin Source File

SOURCE=.\OpenMeasDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Serial.h
# End Source File
# Begin Source File

SOURCE=.\slg2.h
# End Source File
# Begin Source File

SOURCE=.\slg2Doc.h
# End Source File
# Begin Source File

SOURCE=.\slg2View.h
# End Source File
# Begin Source File

SOURCE=.\SlgCircleBuffer.h
# End Source File
# Begin Source File

SOURCE=.\SlgMeasurement.h
# End Source File
# Begin Source File

SOURCE=.\SlgNewAverager.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WizardSelComPortStep.h
# End Source File
# Begin Source File

SOURCE=.\WizardSelRunTypeStep.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\blue.ico
# End Source File
# Begin Source File

SOURCE=.\res\red.ico
# End Source File
# Begin Source File

SOURCE=.\res\slg2.ico
# End Source File
# Begin Source File

SOURCE=.\res\slg2.rc2
# End Source File
# Begin Source File

SOURCE=.\res\slg2Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section slg2 : {B86A73A0-15E3-11D2-A39B-00A024D8325C}
# 	2:5:Class:CNiPlot3D
# 	2:10:HeaderFile:NiPlot3D.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {CA90E9C0-6D11-11CF-A543-0020AF1E73B9}
# 	2:5:Class:CNiPlots
# 	2:10:HeaderFile:NiPlots.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {D940E4C8-6079-11CE-88CB-0020AF6845F6}
# 	2:21:DefaultSinkHeaderFile:NiSlide.h
# 	2:16:DefaultSinkClass:CNiSlide
# End Section
# Section slg2 : {E4012F00-1073-11CF-9617-0020AF6845F6}
# 	2:5:Class:CNiLabels
# 	2:10:HeaderFile:NiLabels.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {E4B1BF00-36CF-11D2-A3A3-00A024D8325C}
# 	2:5:Class:CNiContour
# 	2:10:HeaderFile:NiContour.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {0414ADF0-A0DE-11CE-A870-0020AF6845F6}
# 	2:5:Class:CNiAxis
# 	2:10:HeaderFile:NiAxis.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {FD640FD0-322D-11D2-A3A3-00A024D8325C}
# 	2:5:Class:CNiPlots3D
# 	2:10:HeaderFile:NiPlots3D.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {9A41C7E2-9ACD-11CE-A86E-0020AF6845F6}
# 	2:5:Class:CNiPointer
# 	2:10:HeaderFile:NiPointer.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {6F7EA122-D1A1-11D2-A4EE-00A024D63828}
# 	2:5:Class:CNiBindings
# 	2:10:HeaderFile:NiBindings.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {35575F41-E7AD-11CE-AE6E-0020AF31CEF9}
# 	2:5:Class:CNiCursors
# 	2:10:HeaderFile:NiCursors.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {D940E4BF-6079-11CE-88CB-0020AF6845F6}
# 	2:5:Class:CNiButton
# 	2:10:HeaderFile:NiButton.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {2FB97641-230A-11D2-A253-00A024D8324D}
# 	2:5:Class:CNiLabels3D
# 	2:10:HeaderFile:NiLabels3D.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {D940E4D3-6079-11CE-88CB-0020AF6845F6}
# 	2:5:Class:CNiKnob
# 	2:10:HeaderFile:NiKnob.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {FD641000-322D-11D2-A3A3-00A024D8325C}
# 	2:5:Class:CNiAxes3D
# 	2:10:HeaderFile:NiAxes3D.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {C798BD20-2319-11D2-A253-00A024D8324D}
# 	2:5:Class:CNiAxis3D
# 	2:10:HeaderFile:NiAxis3D.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:CNiFont
# 	2:10:HeaderFile:NiFont.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {D940E4BE-6079-11CE-88CB-0020AF6845F6}
# 	2:21:DefaultSinkHeaderFile:NiButton.h
# 	2:16:DefaultSinkClass:CNiButton
# End Section
# Section slg2 : {17301DA3-C84D-11CF-AE6F-0020AF31CEF9}
# 	2:21:DefaultSinkHeaderFile:NiNumEdit.h
# 	2:16:DefaultSinkClass:CNiNumEdit
# End Section
# Section slg2 : {D940E4D2-6079-11CE-88CB-0020AF6845F6}
# 	2:21:DefaultSinkHeaderFile:NiKnob.h
# 	2:16:DefaultSinkClass:CNiKnob
# End Section
# Section slg2 : {6F7EA121-D1A1-11D2-A4EE-00A024D63828}
# 	2:5:Class:CNiBinding
# 	2:10:HeaderFile:NiBinding.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {B68DBFAC-16A0-11CE-80BF-0020AF31CEF9}
# 	2:5:Class:CNiGraph
# 	2:10:HeaderFile:u
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {0EED9920-0DF3-11CF-9617-0020AF6845F6}
# 	2:5:Class:CNiStatistics
# 	2:10:HeaderFile:NiStatistics.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {37715970-C76B-11CE-A890-0020AF6845F6}
# 	2:5:Class:CNiValuepair
# 	2:10:HeaderFile:NiValuepair.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CNiPicture
# 	2:10:HeaderFile:NiPicture.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {2AFA9F11-0B6A-11D2-A250-00A024D8324D}
# 	2:5:Class:CNiGraph3D
# 	2:10:HeaderFile:NiGraph3D.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {F32E05B0-15B6-11D2-A253-00A024D8324D}
# 	2:5:Class:CNiLights
# 	2:10:HeaderFile:NiLights.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {B1AABB61-15B1-11D2-A253-00A024D8324D}
# 	2:5:Class:CNiLight
# 	2:10:HeaderFile:NiLight.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {B68DBFAB-16A0-11CE-80BF-0020AF31CEF9}
# 	2:21:DefaultSinkHeaderFile:NiGraph.h
# 	2:16:DefaultSinkClass:CNiGraph
# End Section
# Section slg2 : {14AE3BE4-1A81-11CF-AE6F-0020AF31CEF9}
# 	2:5:Class:CNiAxes
# 	2:10:HeaderFile:NiAxes.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {6810EEF1-232D-11D2-BEC7-00A024585300}
# 	2:5:Class:CNiTicks3D
# 	2:10:HeaderFile:NiTicks3D.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {9B41D330-36CF-11D2-A3A3-00A024D8325C}
# 	2:5:Class:CNiContours
# 	2:10:HeaderFile:NiContours.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {2C36E3E8-478D-11D0-A547-0020AF1E73B9}
# 	2:5:Class:CNiImage
# 	2:10:HeaderFile:NiImage.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {2AFA9F10-0B6A-11D2-A250-00A024D8324D}
# 	2:21:DefaultSinkHeaderFile:NiGraph3D.h
# 	2:16:DefaultSinkClass:CNiGraph3D
# End Section
# Section slg2 : {B29D1C40-5270-11D0-A547-0020AF1E73B9}
# 	2:5:Class:CNiPicturedisp
# 	2:10:HeaderFile:NiPicturedisp.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {85041CC0-E78C-11CE-AE6E-0020AF31CEF9}
# 	2:5:Class:CNiCursor
# 	2:10:HeaderFile:NiCursor.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {17301DA1-C84D-11CF-AE6F-0020AF31CEF9}
# 	2:5:Class:CNiNumEdit
# 	2:10:HeaderFile:NiNumEdit.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {65FD2500-C067-11CE-A88D-0020AF6845F6}
# 	2:5:Class:CNiTicks
# 	2:10:HeaderFile:NiTicks.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {E168E231-C75C-11CE-A890-0020AF6845F6}
# 	2:5:Class:CNiValuepairs
# 	2:10:HeaderFile:NiValuepairs.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {D940E4C9-6079-11CE-88CB-0020AF6845F6}
# 	2:5:Class:CNiSlide
# 	2:10:HeaderFile:NiSlide.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {B8ED1000-53EE-11CE-80BF-0020AF31CEF9}
# 	2:5:Class:CNiPlot
# 	2:10:HeaderFile:NiPlot.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
# Section slg2 : {E93425C7-2038-11CF-A543-0020AF1E73B9}
# 	2:5:Class:CNiPointers
# 	2:10:HeaderFile:NiPointers.h
# 	2:8:ImplFile:NiAll.cpp
# End Section
