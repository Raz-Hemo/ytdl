#include "Window.h"

std::function<void()> HandleHotkey;

LRESULT CALLBACK WndProc(
	HWND   hwnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch(uMsg)
	{
	case WM_HOTKEY:
		if (wParam == Constants::HotkeyDownload && HandleHotkey)
			HandleHotkey();
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
}

Window::Window(HINSTANCE hInstance)
{
	WNDCLASS wc = { 0 };
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpszClassName = Constants::ProgramName;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;

	if (!RegisterClass(&wc))
		MessageBox(NULL, _T("Failed registering window class"), _T("Error"), MB_ICONERROR | MB_OK);

	hwnd = CreateWindow(
		Constants::ProgramName,
		Constants::ProgramName,
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// Ctrl-Shift-Alt-D
	RegisterHotKey(hwnd, Constants::HotkeyDownload, MOD_NOREPEAT | MOD_SHIFT | MOD_CONTROL | MOD_ALT, 0x44);
}

Window::~Window()
{
	UnregisterHotKey(hwnd, Constants::HotkeyDownload);
	DestroyWindow(hwnd);
}

void Window::SetHotkeyHandler(const std::function<void()>& func)
{
	HandleHotkey = func;
}