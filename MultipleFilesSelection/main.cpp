#include <Windows.h>
#define ErrorMessageBox(a,b) MessageBox(a,b,"Error:",MB_ICONWARNING);

bool SetUpWindowClass (char*, int, int, int);
LRESULT CALLBACK WindowProcedure (HWND, unsigned int, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpsCmdLine, int iCmdShow) {
	if (!SetUpWindowClass ("1", 255, 255, 255)) {
		ErrorMessageBox (NULL, "Window class \"1\" failed");
		return 0;
	}
	HWND hWnd = CreateWindow ("1", "Hello World - Win32 API", WS_OVERLAPPEDWINDOW, 315, 115, 700, 480, NULL, NULL, hInstance, NULL);
	if (!hWnd) {
		ErrorMessageBox (NULL, "Window handle = NULL");
		return 0;
	}
	ShowWindow (hWnd, SW_SHOW);
	MSG uMsg;
	while (GetMessage (&uMsg, NULL, 0, 0) > 0) {
		TranslateMessage (&uMsg);
		DispatchMessage (&uMsg);
	}
	return 0;
}

bool SetUpWindowClass (char *cpTitle, int iR, int iG, int iB) {
	WNDCLASSEX WindowClass;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.cbSize = sizeof (WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpszClassName = cpTitle;
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpfnWndProc = WindowProcedure;
	WindowClass.hInstance = GetModuleHandle (NULL);
	WindowClass.hCursor = LoadCursor (NULL, IDC_ARROW);
	WindowClass.hbrBackground = CreateSolidBrush (RGB (iR, iG, iB));
	WindowClass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	WindowClass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	if (RegisterClassEx (&WindowClass)) return true;
	else return false;
}

LRESULT CALLBACK WindowProcedure (HWND hWnd, unsigned int uiMsg, WPARAM wParam, LPARAM lParam) {
	switch (uiMsg) {
		case WM_CLOSE:
			DestroyWindow (hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage (0);
			break;
		case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC hDC = BeginPaint (hWnd, &ps);
				char *cpaText [] = {
					"Hello World!",
					"This is a hello world application made in the Win32 API",
					"This example was made by some random dude, aka -LeetGamer-"
				};
				int iY = 5;
				for (int iLoopCounter = 0; cpaText [iLoopCounter] != '\0'; iLoopCounter++, iY += 20) {
					TextOut (hDC, 5, iY, cpaText [iLoopCounter], strlen (cpaText [iLoopCounter]));				// display Text
				}
				EndPaint (hWnd, &ps);
			}
			break;
	}
	return DefWindowProc (hWnd, uiMsg, wParam, lParam);
}
