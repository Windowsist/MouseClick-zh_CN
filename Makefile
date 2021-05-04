
SRCS=MouseClick.cpp MouseAction.cpp StringTable.cpp
HEADERS=MouseClick.h MouseAction.h StringTable.h

build:MouseClick.dll MouseClick.exe

MouseClick.exe: pch.pch pch.obj MouseClick_exe.cpp Windowsist.GUI.manifest MouseClick.lib
	$(CPP) $(CPPFLAGS) /Yu"pch.h" /Fp: "pch.pch" MouseClick_exe.cpp /link /ENTRY:MouseClickMain /SUBSYSTEM:WINDOWS /MANIFESTINPUT:Windowsist.GUI.manifest /MANIFEST:EMBED pch.obj MouseClick.lib
	if exist MouseClick.exe del MouseClick.exe
	ren MouseClick_exe.exe MouseClick.exe

MouseClick.dll: pch.pch pch.obj $(SRCS) $(HEADERS) Resource.res
	$(CPP) $(CPPFLAGS) /LD /Yu"pch.h" /Fp: "pch.pch" $(SRCS) /link pch.obj Resource.res kernel32.lib user32.lib WindowsApp.lib

pch.pch: framework.h pch.h pch.cpp
	$(CPP) $(CPPFLAGS) /c /Yc"pch.h" /Fp: "pch.pch" pch.cpp

clean:
	@for %i in (*.obj *.pch *.res *.ilk *.pdb *.exp *.lib *.dll *.exe) do @del "%i"
