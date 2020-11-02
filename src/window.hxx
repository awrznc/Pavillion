#include <windows.h>
#include <iostream>
#include <tchar.h>

#include "device.hxx"

#define INIT_ERROR_STRING "Window initialize error"


class Window {

private:
    static void char_to_tchar( TCHAR* tch, const char* ch );
    static void draw_character( HWND hwnd, HDC hdc );
    static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

public:
    WNDCLASS window_class;
    HWND hwnd;
    MSG message;
    HINSTANCE hInstance;
    int nCmdShow;
    Window( const char* title );
    ~Window();
    int draw();
};
