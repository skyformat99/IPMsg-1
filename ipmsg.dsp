# Microsoft Developer Studio Project File - Name="ipmsg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ipmsg - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ipmsg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ipmsg.mak" CFG="ipmsg - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ipmsg - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ipmsg - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ipmsg - Win32 Installer" (based on "Win32 (x86) Application")
!MESSAGE "ipmsg - Win32 InstallerDbg" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ipmsg - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\ipmsg___"
# PROP BASE Intermediate_Dir ".\ipmsg___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /O1 /Op /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /W3 /O1 /Op /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MBCS" /D "_MBCS" /FAcs /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib Comctl32.lib imm32.lib wsock32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib Comctl32.lib imm32.lib wsock32.lib /nologo /subsystem:windows /map /machine:I386
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\ipmsg__0"
# PROP BASE Intermediate_Dir ".\ipmsg__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MBCS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib Comctl32.lib /nologo /subsystem:windows /map /debug /machine:I386
# ADD LINK32 winmm.lib Comctl32.lib imm32.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /profile /map:".\debug\ipmsg.map" /debug /machine:I386

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\ipmsg___"
# PROP BASE Intermediate_Dir ".\ipmsg___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Install"
# PROP Intermediate_Dir "Install"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "MBCS" /D "_MBCS" /FAcs /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib Comctl32.lib imm32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Comctl32.lib /nologo /subsystem:windows /machine:I386 /out:".\Release\setup.exe"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\ipmsg___"
# PROP BASE Intermediate_Dir ".\ipmsg___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "InstallDBG"
# PROP Intermediate_Dir "InstallDBG"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MBCS" /D "_MBCS" /Fp".\obj\debug\ipmsg.pch" /YX /Fo".\obj\debug" /Fd".\obj\debug" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /fo".\obj\debug\install.res" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/install.exe"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib Comctl32.lib /nologo /subsystem:windows /incremental:yes /map /debug /machine:I386 /out:".\debug\setup.exe"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "ipmsg - Win32 Release"
# Name "ipmsg - Win32 Debug"
# Name "ipmsg - Win32 Installer"
# Name "ipmsg - Win32 InstallerDbg"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx"
# Begin Source File

SOURCE=.\src\blowfish.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\cfg.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\install\install.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Install\install.rc

!IF  "$(CFG)" == "ipmsg - Win32 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE RSC /l 0x804 /i "Src\Install"
# ADD RSC /l 0x804 /i "Src\Install" /i ".\Src\Install"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD BASE RSC /l 0x804 /i "Src\Install"
# ADD RSC /l 0x804 /i "Src\Install" /i ".\Src\Install"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# ADD BASE RSC /l 0x804 /i "Src\Install"
# ADD RSC /l 0x804 /i "Src\Install" /i ".\Src\Install"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# ADD BASE RSC /l 0x804 /i "Src\Install"
# ADD RSC /l 0x804 /i "Src\Install" /i ".\Src\Install"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Ipmsg.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\ipmsg.rc

!IF  "$(CFG)" == "ipmsg - Win32 Release"

# ADD BASE RSC /l 0x804 /i "Src"
# ADD RSC /l 0x804 /i "Src" /i ".\Src"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

# ADD BASE RSC /l 0x804 /i "Src"
# ADD RSC /l 0x804 /i "Src" /i ".\Src"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1
# ADD BASE RSC /l 0x804 /i "Src"
# ADD RSC /l 0x804 /i "Src" /i ".\Src"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE RSC /l 0x804 /i "Src"
# ADD RSC /l 0x804 /i "Src" /i ".\Src"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Logdlg.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Logmng.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Mainwin.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Miscdlg.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Msgmng.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\plugin.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Recvdlg.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Senddlg.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Setupdlg.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\share.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Tapp.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Tdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\tini.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Tlist.cpp

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\tmisc.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Tregist.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Twin.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\src\blowfish.h
# End Source File
# Begin Source File

SOURCE=.\src\install\install.h
# End Source File
# Begin Source File

SOURCE=.\src\ipmsg.h
# End Source File
# Begin Source File

SOURCE=.\src\plugin.h
# End Source File
# Begin Source File

SOURCE=.\src\resource.h
# End Source File
# Begin Source File

SOURCE=.\src\tlib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\src\absence.ico
# End Source File
# Begin Source File

SOURCE=.\src\file.ico
# End Source File
# Begin Source File

SOURCE=.\src\fileabs.ico
# End Source File
# Begin Source File

SOURCE=.\src\ipmsg.ico
# End Source File
# Begin Source File

SOURCE=.\src\ipmsgrev.ico
# End Source File
# Begin Source File

SOURCE=.\src\install\setup.ico
# End Source File
# Begin Source File

SOURCE=.\src\v1.ico

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\v1abs.ico

!IF  "$(CFG)" == "ipmsg - Win32 Release"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Debug"

!ELSEIF  "$(CFG)" == "ipmsg - Win32 Installer"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ipmsg - Win32 InstallerDbg"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\src\ipmsg.exe.manifest
# End Source File
# End Target
# End Project
