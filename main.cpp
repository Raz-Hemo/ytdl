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
	PROCESS_INFORMATION proc_info = { 0 };
	STARTUPINFO proc_startup_info = { 0 };
	proc_startup_info.cb = sizeof(proc_startup_info);

	Window window(hInstance);

	// Bind the hotkey handler
	window.SetHotkeyHandler([&]() { 
		// Execute ytdl.py under windowless python
		TCHAR cmdline[] = _T("pythonw ytdl.py");
		if (CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &proc_startup_info, &proc_info))
		{
			CloseHandle(proc_info.hProcess);
			CloseHandle(proc_info.hThread);
		}
	});

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