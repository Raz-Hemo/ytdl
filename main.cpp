#include <tchar.h>
#include <Windows.h>

#include "Window.h"

// Saves old clipboard, copies new, restores old and returns the new copied text
tstring GetHighlightedText()
{
	tstring new_clip_text;

	if (!OpenClipboard(NULL)) return;

	// Get the old content
	HANDLE old_clip = GetClipboardData(CF_UNICODETEXT);
	if (old_clip == NULL)
	{
		CloseClipboard();
		return;
	}

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
	if (4 != SendInput(4, ip, sizeof(ip[0]))) return;

	// Get this new text
	HANDLE new_clip = GetClipboardData(CF_UNICODETEXT);
	if (new_clip == NULL)
	{
		CloseClipboard();
		return;
	}
	new_clip_text = (TCHAR*)GlobalLock(old_clip);

	// Restore old
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, old_clip);

	// Free resources
	GlobalUnlock(new_clip);
	CloseClipboard();

	return new_clip_text;
}

void HandleHotkey()
{
	tregex youtube_regex(L"^(https?\\:\\/\\/)?(www\\.)?youtube\\.com\\/watch\\?v\\=[A-Za-z0-9_-]{11}$");
	tstring potential_video_id = GetHighlightedText();

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
	window.SetHotkeyHandler(HandleHotkey);

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