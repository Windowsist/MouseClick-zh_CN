
SRCS=MouseClick.cpp MouseAction.cpp StringTable.cpp
HEADERS=MouseClick.h MouseAction.h StringTable.h

build:MouseClick.dll MouseClick.exe

MouseClick.exe: MouseClick_exe.cpp Windowsist.GUI.manifest Resource_exe.res MouseClick.lib
	$(CPP) $(CPPFLAGS) /Fe: MouseClick.exe MouseClick_exe.cpp /link /ENTRY:wWinMainCRTStartup /SUBSYSTEM:WINDOWS /MANIFESTINPUT:Windowsist.GUI.manifest /MANIFEST:EMBED Resource_exe.res pch.obj MouseClick.lib /NODEFAULTLIB

MouseClick.dll: pch.pch pch.obj $(SRCS) $(HEADERS) MouseAction.def Resource.res
	$(CPP) $(CPPFLAGS) /LD /Yu"pch.h" /Fp: "pch.pch" $(SRCS) /link /DEF:MouseAction.def pch.obj Resource.res noarg.obj user32.lib

pch.pch: framework.h pch.h pch.cpp
	$(CPP) $(CPPFLAGS) /c /Yc"pch.h" /Fp: "pch.pch" pch.cpp

clean:
	@for %i in (*.obj *.pch *.res *.ilk *.pdb *.exp *.lib *.dll *.exe) do @del "%i"
