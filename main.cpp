#include "stdafx.h"
#include "Window.h"
#include "Clipboard.h"

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
	window.SetHotkeyHandler([](){
		tregex youtube_regex(_T("^(https?\\:\\/\\/)?(www\\.)?youtube\\.com\\/watch\\?v\\=[A-Za-z0-9_-]{11}"));
		tstring potential_video_id = Clipboard::GetText();
		if (std::regex_search(potential_video_id, youtube_regex))
		{
			PROCESS_INFORMATION proc_info = { 0 };
			STARTUPINFO proc_startup_info = { 0 };
			proc_startup_info.cb = sizeof(proc_startup_info);

			// Execute ytdl.py under windowless python
			tstring cmdline = _T("pythonw ytdl.py ") + potential_video_id;
			if (CreateProcess(NULL, &cmdline[0], NULL, NULL, FALSE, 0, NULL, NULL, &proc_startup_info, &proc_info))
			{
				CloseHandle(proc_info.hProcess);
				CloseHandle(proc_info.hThread);
			}
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