#include"stdafx.h"
#include "Window.h"
#include "Clipboard.h"

// Saves old clipboard, copies new, restores old and returns the new copied text
tstring GetHighlightedText()
{
	// Save old
	tstring old_text = Clipboard::GetText();

	// Send a CTRL-C
	INPUT ip[4] = { 0 };
	ip[0].ki.wVk = VK_CONTROL;
	ip[0].ki.dwFlags = 0;
	ip[1].ki.wVk = 'C';
	ip[1].ki.dwFlags = 0;
	ip[2].ki.wVk = 'C';
	ip[2].ki.dwFlags = KEYEVENTF_KEYUP;
	ip[3].ki.wVk = VK_CONTROL;
	ip[3].ki.dwFlags = KEYEVENTF_KEYUP;
	if (4 != SendInput(4, ip, sizeof(ip[0]))) return _T("");

	// Wait a bit for the message to be processed
	Sleep(10);

	// Get this new text
	tstring new_text = Clipboard::GetText();

	// Restore old content
	Clipboard::SetText(old_text);

	return new_text;
}

void HandleHotkey()
{
	tregex youtube_regex(L"^(https?\\:\\/\\/)?(www\\.)?youtube\\.com\\/watch\\?v\\=[A-Za-z0-9_-]{11}$");
	tstring potential_video_id = GetHighlightedText();

	MessageBox(NULL, potential_video_id.c_str(), L"hi", MB_OK);

	if (std::regex_match(potential_video_id, youtube_regex))
	{
 		PROCESS_INFORMATION proc_info = { 0 };
		STARTUPINFO proc_startup_info = { 0 };
		proc_startup_info.cb = sizeof(proc_startup_info);

		// Execute ytdl.py under windowless python
		TCHAR cmdline[] = _T("pythonw ytdl.py");
		if (CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &proc_startup_info, &proc_info))
		{
			CloseHandle(proc_info.hProcess);
			CloseHandle(proc_info.hThread);
		}
	}
}

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
	window.SetHotkeyHandler([](const tstring& url){
		PROCESS_INFORMATION proc_info = { 0 };
		STARTUPINFO proc_startup_info = { 0 };
		proc_startup_info.cb = sizeof(proc_startup_info);
		tstring line = _T("pythonw ytdl.py ") + url;

		if (CreateProcess(NULL, &line[0], NULL, NULL, FALSE, 0, NULL, NULL, &proc_startup_info, &proc_info))
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