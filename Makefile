
SRCS=MouseClick.cpp MouseAction.cpp StringTable.cpp
HEADERS=MouseClick.h MouseAction.h StringTable.h

build:MouseClick.exe


MouseClick.exe: pch.pch pch.obj $(SRCS) $(HEADERS) Windowsist.GUI.manifest Resource.res
	$(CPP) $(CPPFLAGS) /Yu"pch.h" /Fp: "pch.pch" $(SRCS) /link pch.obj /MANIFESTINPUT:Windowsist.GUI.manifest /MANIFEST:EMBED Resource.res noarg.obj user32.lib

pch.pch: framework.h pch.h pch.cpp
	$(CPP) $(CPPFLAGS) /c /Yc"pch.h" /Fp: "pch.pch" pch.cpp

clean:
	@for %i in (*.obj *.pch *.res *.ilk *.pdb *.exp *.lib *.dll *.exe) do @del "%i"
