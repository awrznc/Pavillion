# Pavillion

An experimental text editor.

## Build

### CL

```ps1
# Debug # /std:c++20
CL .\src\pavillion.cxx .\src\window.cxx winmm.lib user32.lib gdi32.lib /link /OUT:lion.exe

# Release
CL .\src\pavillion.cxx .\src\window.cxx winmm.lib user32.lib gdi32.lib /link /OUT:lion.exe /SUBSYSTEM:WINDOWS /entry:mainCRTStartup
```

### g++

```bash
# Debug
g++ src/pavillion.cxx src/window.cxx -o ./lion.exe -lwinmm -lgdi32

# Release
g++ src/pavillion.cxx src/window.cxx -o ./lion.exe -lwinmm -lgdi32 -Wl,-subsystem,windows
```
