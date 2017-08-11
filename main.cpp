#include <tchar.h>
#include <Windows.h>

#include "Window.h"

int WINAPI _tWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	MSG msg = { 0 };
	Window window(hInstance);
	
	// Bind the hotkey handler
	window.SetHotkeyHandler([]() { MessageBox(NULL, _T("hi"), _T("heya"), MB_OK); });

	while (true)
	{
		WaitMessage();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}