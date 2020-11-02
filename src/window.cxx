#include "window.hxx"

void Window::char_to_tchar(TCHAR* tch, const char* ch) {
    #ifdef UNICODE
    MultiByteToWideChar(CP_OEMCP,MB_PRECOMPOSED,ch,strlen(ch),tch,(sizeof tch)/2);
    #else
    strcpy(tch,ch);
    #endif
}

void Window::draw_character(HWND hwnd, HDC hdc) {
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);

    SelectObject(hdc , CreateSolidBrush(RGB(0, 235, 235)));
    PatBlt(hdc , 0 , 0 , 200 , 100 , PATCOPY);

    SelectObject(hdc , CreateSolidBrush(RGB(255, 0, 100)));
    PatBlt(hdc , 20 , 40 , 200 , 100 , PATCOPY);

    SelectObject(hdc , CreateSolidBrush(RGB(0, 0, 0)));
    PatBlt(hdc , 20 , 40 , 180 , 60 , PATCOPY);

    DeleteObject( SelectObject( hdc , GetStockObject(WHITE_BRUSH) ) );

    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK Window::WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    HDC hdc = NULL;

    switch (uMsg) {
    case WM_PAINT:
        draw_character(hwnd, hdc);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    Device::JoyPad* device = new Device::JoyPad;

    TCHAR szText[256];
    char char_pointer[256];

    switch(uMsg){
    case WM_CREATE:
        if(JOYERR_NOERROR!=joySetCapture(hwnd, JOYSTICKID1, 30, FALSE)){
            device->connect();
        }
        break;

    case MM_JOY1MOVE:
        device->debug_capture(0, char_pointer);
        char_to_tchar(szText, char_pointer);

        hdc = GetDC(hwnd);
        TextOut(hdc, 0, 0, szText, lstrlen(szText));
        ReleaseDC(hwnd , hdc);

        break;

    case WM_CLOSE:
        joyReleaseCapture(JOYSTICKID1);
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(const char* title) {

    nCmdShow=10;
    hInstance = (HINSTANCE)GetModuleHandle(0);

    TCHAR szAppName[256];
    char_to_tchar(szAppName, title);

    window_class.style         = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc   = WndProc;
    window_class.cbClsExtra    = 0;
    window_class.cbWndExtra    = 0;
    window_class.hInstance     = hInstance;
    window_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    window_class.lpszMenuName  = NULL;
    window_class.lpszClassName = szAppName;

    if (!RegisterClass(&window_class)) {
        throw std::runtime_error( INIT_ERROR_STRING );
    }

    hwnd = CreateWindow(
        szAppName, szAppName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 500,
        NULL, NULL,
        hInstance, NULL);

    if (!hwnd) throw std::runtime_error( INIT_ERROR_STRING );
}

int Window::draw() {
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return message.wParam;
}
