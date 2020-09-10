// https://www.codeproject.com/Articles/215690/Minimal-WinApi-Window
// gcc -mwindows hello-triangle.c 

#include <windows.h>

POINT *p_tri_points;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            Polygon(GetDC(hWnd), p_tri_points, 3);
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow) {
    MSG msg          = {0};
    WNDCLASS wc      = {0}; 
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = "minwindowsapp";
    if (!RegisterClass(&wc))
        return 1;

    if(!CreateWindow(wc.lpszClassName, "Minimal Windows Application",
                     WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
                     CW_USEDEFAULT, 640, 360, NULL, NULL, hInstance, NULL))
        return 2;

    p_tri_points = malloc(sizeof(POINT)*8);
    p_tri_points[0].x = p_tri_points[0].y = p_tri_points[1].y = 10;
    p_tri_points[1].x = p_tri_points[2].y = 110;
    p_tri_points[2].x = 60;

    while(GetMessage(&msg, NULL, 0, 0 ) > 0)
        DispatchMessage(&msg);

    free(p_tri_points);

    return 0;
}
