#pragma once
#include "stdafx.h"

class Window
{
	HWND hwnd;

public:
	Window(HINSTANCE hInstance);
	~Window();

	static void SetHotkeyHandler(const std::function<void()>& func);
};

