/*--------------------------------------------------
Hellow-World.cpp - minimalistic program
--------------------------------------------------*/
#include <windows.h>

	//Not to use std:: to use standard C++ library of classes etc
using namespace std;	

	//CALLBACK means that it will be called by the operating system
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	
int WINAPI WinMain(HINSTANCE hCurrInstance,																						//A handle of the current instance of our program.
    HINSTANCE hPreviousInstance,																								//A previous instance of our program if one exists.
    PSTR szCommandLine,																											//The pointer to null terminated string with command line without the program name.
    int nStartShow)																												//How to show our window at start: SW_HIDE, SW_MAXIMIZE, SW_SHOWMAXIMIZED, SW_SHOW etc
	{
		// Start of Main Program
		MessageBeep(MB_OK);
		static char szOurProgramName[] = "Our C++ Hellow Programming World program"; 											//Program title to be displayed on the top of the window.
		HWND hMainWindow;																										//Letter h in the beginning of hMainWindow means that it's a handle to handle this window, the main window of our program or whatever.
		MSG WindowsMessageStruct;
	 
		WNDCLASSEX MainWindowStruc;																								//This structure describes the main window of our program, its size etc. Then we fill this structure with our values or use default values.
		MainWindowStruc.cbSize = sizeof(MainWindowStruc);
		MainWindowStruc.style = CS_HREDRAW | CS_VREDRAW;
		MainWindowStruc.lpfnWndProc = WndProc;																					//The second main function of our program to be called when operating system is sending a message to our program or its windows.
		MainWindowStruc.cbClsExtra = 0;																							//Bytes we may need to place after this structure. In the name starting cb means count of bytes, number of bytes.
		MainWindowStruc.cbWndExtra = 0;																							//Bytes to be used for creation of a dialog after the program instance.
		MainWindowStruc.hInstance = hCurrInstance;																				//Handle to our current program.
		MainWindowStruc.hIcon = LoadIcon(NULL, IDI_APPLICATION);																//Default big Alt-Tab icon.
		//  MainWindowStruc.hIcon = LoadIcon(hCurrInstance, "Icon"); 															//If we want to use our big Alt-Tab icon.
		MainWindowStruc.hCursor = LoadCursor(NULL, IDC_ARROW);																	//We use the default cursor here in order to not mess with resources.
		MainWindowStruc.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH); 													//Background color of the main window. Can be WHITE_BRUSH, BLACK_BRUSH, GRAY_BRUSH and several other values.
		MainWindowStruc.lpszMenuName = NULL;																					//This is a pointer to the name of our menue if we use one.
		MainWindowStruc.lpszClassName = szOurProgramName;																		//This string will be displayed at the top of our main window.
		MainWindowStruc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);																//A small icon in the top left corner of the main window.
		//  MainWindowStruc.hIconSm = LoadIcon(hCurrInstance, "Icon");//This line will help us to have our own icon in the future.
	 
		RegisterClassEx(&MainWindowStruc);																						//After making WNDCLASSEX structure to create an actual window we muct use this function.
		hMainWindow = CreateWindow(																								//Actual creation of our program's main window.
			szOurProgramName, 																									// window class name
			"The Hello Windows world Program", 																					// The inscription at the top of the main window.
			WS_OVERLAPPEDWINDOW, 																								// style switches
			CW_USEDEFAULT, 																										// initial horizontal position
			CW_USEDEFAULT, 																										// initial vertical position
			CW_USEDEFAULT, 																										// initial horizontal size
			CW_USEDEFAULT, 																										// initial vertical size
			NULL, 																												//the handle of parent window
			NULL, 																												// the handle of the window menu
			hCurrInstance, 																										//the handle of this program instance
			NULL); 																												// creation parameters
			
		ShowWindow(hMainWindow, nStartShow);																					//Without it will not see our window.
		UpdateWindow(hMainWindow);																								//Kind of reset the window.
		while(GetMessage(&WindowsMessageStruct, NULL, 0, 0))
		{
			TranslateMessage(&WindowsMessageStruct);
			DispatchMessage(&WindowsMessageStruct);
		}
		return WindowsMessageStruct.wParam;
}

LRESULT CALLBACK WndProc(HWND hOurWindowHandle,																					//Again a handle to handle whatever we do with our window.
    UINT iMessageToProcess, WPARAM wMessageParameterNr32bits,																	//Message parameter, may contain 2 numbers, unsigned.
    LPARAM wMessageParameterLong)																								//Second message parameter, signed.
	{
		HDC hDeviceContextHandle;																								//A handle to a device context structure which has all the information needed in our window paiting operations.
		PAINTSTRUCT OurPaintStructure;
		RECT ClientRectangle;
		switch(iMessageToProcess)
		{
			case WM_CREATE:																										//This message is sent to our program in the very beginning.
				return 0;																										//Means no error.
			case WM_PAINT:																										//Operating system wants to repaint our program window.
				hDeviceContextHandle = BeginPaint(hOurWindowHandle, &OurPaintStructure);										//Based  hOurWindowHandle this function fills OurPaintStructure.
				GetClientRect(hOurWindowHandle, &ClientRectangle);																//Fills ClientRectangle of hOurWindowHandle window.
				DrawText(hDeviceContextHandle, "Hello, programming world!", -1,													//Will type Hello world programming world in the middle of found ClientRectangle.
					&ClientRectangle, DT_SINGLELINE | DT_CENTER | DT_VCENTER);													//These flags center our text.
				EndPaint(hOurWindowHandle, &OurPaintStructure);																	//The end of repainting.
	 
	//          FlashWindow(hOurWindowHandle, TRUE); // invert the title bar 
	//          MessageBox(hOurWindowHandle,"First","Second",MB_OK);
	//          MessageBeep(MB_ICONEXCLAMATION);//MB_OK, MB_ICONSTOP, MB_ICONASTERISK, MB_ICONEXCLAMATION
	//          Sleep(1000);              // A pause of 1 second.
	//          FlashWindow(hOurWindowHandle, TRUE); // invert again 
	 
				return 0;
			case WM_DESTROY:																									//The end of our program work, close everything.
				PostQuitMessage(0);																								//Game is over.
				return 0;																										//All is fine.
		}
		return DefWindowProc(hOurWindowHandle,iMessageToProcess, wMessageParameterNr32bits, wMessageParameterLong);				//We have to return this standard MS Windows function to let Window to do whatever it usually does here.
			
	}
