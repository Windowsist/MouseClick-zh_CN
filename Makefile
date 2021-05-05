# MSVC NMake Makefile

# to build this project, do the following steps:
# 1.open Visual Studio Developer Command Prompt (for example: open "x64 Native Tools Command Prompt for VS 2019")
# 2.change the working directory to the project directory 
# 3.type "nmake build"
#
# if you whant to edit the source code, you can use Visual Studio Code.
#
# you can also create a project from Visual Studio IDE add the source files.

# default libraries replacements:
# vcruntime.lib -> api-ms-win-crt-private-l1-1-0.lib (extracted from api-ms-win-crt-private-l1-1-0.dll)
# msvcprt.lib -> msvcp_win.lib (extracted from msvcp_win.dll)

# Debug:
# CPPFLAGS=/nologo /D "_UNICODE" /D "UNICODE" /MD /std:c++17 /EHsc /await /bigobj /utf-8 /Zi
# Release:
# CPPFLAGS=/nologo /D "_UNICODE" /D "UNICODE" /MD /std:c++17 /EHsc /await /bigobj /utf-8 /O2 /Ob2 /GL

SRCS=MouseClick.cpp MouseAction.cpp StringTable.cpp
HEADERS=MouseClick.h MouseAction.h StringTable.h

build:MouseClick.exe


MouseClick.exe: pch.pch pch.obj $(SRCS) $(HEADERS) Windowsist.GUI.manifest Resource.res
	$(CPP) $(CPPFLAGS) /Yu"pch.h" /Fp: "pch.pch" $(SRCS) /link pch.obj /MANIFESTINPUT:Windowsist.GUI.manifest /MANIFEST:EMBED Resource.res noarg.obj

pch.pch: framework.h pch.h pch.cpp
	$(CPP) $(CPPFLAGS) /c /Yc"pch.h" /Fp: "pch.pch" pch.cpp

clean:
	@for %i in (*.obj *.pch *.res *.ilk *.pdb *.exp *.lib *.dll *.exe) do @del "%i"
