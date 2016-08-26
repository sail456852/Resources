#include <windows.h>
#include <tchar.h>
#include <stdio.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Undefined Symbol in CodeBlocks ,Works well in Visual Studio
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName, // window class name
		TEXT("The Hello Program"), // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT, // initial x position
		CW_USEDEFAULT, // initial y position
		CW_USEDEFAULT, // initial x size
		CW_USEDEFAULT, // initial y size
		NULL, // parent window handle
		NULL, // window menu handle
		hInstance, // program instance handle
		NULL); // creation parameters
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	//HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE("my_icon")); 
	//I think LoadIcon can be used to determine which Window to use this icon by pointing this hInstance 
	//MAKEINTRESOURCE MACRO is absolutely necessary in Visual Studio , but not in Codeblocks 
	//You don't actually need LoadIcon , if your program only has one window . just use resouce.rc and resouce.h 
	while (GetMessage(&msg, NULL, 0, 0))  //That's the heart of the Windows looping 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (message)
	{
	case WM_CREATE:
		// PlaySound(_T("hello.wav"),NULL,SND_FILENAME);
		//PlaySound(TEXT("bison.wav"), NULL, SND_SYNC); //need add lib
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); //HDC gets its initialisation here 
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello wangyuzhen!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:  // When you click the exit button on the windows , will cause Windows to send WM_DESTORY message  here 
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}