#include <windows.h>

const char g_szClassName[] = "myWindowClass";


// **************************************************************************
// *			the Window Procedure (Controls Window)						*
// **************************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, 									// handle of your window, the one that the message applies to; Acttually defines Window (if you have more then one window)
						 UINT msg, 
						 WPARAM wParam, 
						 LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:													// CLOSE Button pressed or Alt+F4
            DestroyWindow(hwnd);										// Sends WM_DESTROY which destroys window and any child
        break;
        case WM_DESTROY:
            PostQuitMessage(0);											// We are done and program wantsa to exit; This posts WM_QUIT to message loop
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


// **************************************************************************
// *			Main Function												*
// **************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    
   //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);								// The size of the structure
    wc.style         = 0;												// Class Styles (CS_*), not to be confused with Window Styles (WS_*) This can usually be set to 0
    wc.lpfnWndProc   = WndProc;											// Pointer to the window procedure for this window class
    wc.cbClsExtra    = 0;												// Amount of extra data allocated for this class in memory. Usually 0
    wc.cbWndExtra    = 0;												// Amount of extra data allocated in memory per window of this type. Usually 0
    wc.hInstance     = hInstance;										// Handle to application instance (that we got in the first parameter of WinMain())
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);					// Large (usually 32x32) icon shown when the user presses Alt+Tab
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);						// Cursor that will be displayed over our window
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);						// Background Brush to set the color of our window
    wc.lpszMenuName  = NULL;											// Name of a menu resource to use for the windows with this class
    wc.lpszClassName = g_szClassName;									// Name to identify the class with
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);					// Small (usually 16x16) icon to show in the taskbar and in the top left corner of the window
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Step 2: Creating the Window; Once the class is registered with
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,												// Extended Windows Style (inst and you can change numbers)
        g_szClassName,													// from Which Class create window (class we created and registered)
        "The title of my window",										// Window Title
        WS_OVERLAPPEDWINDOW,											// Window Style parameter
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,							// X and Y co-ordinates for the top left corner of your window, and the width and height of the window; in pixels
        NULL, NULL, hInstance, NULL);									// the Parent Window handle, the menu handle, the application instance handle, and a pointer to window creation data
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop (Heart of the program)
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
