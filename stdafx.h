#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <tchar.h>
#include <Windows.h>
#include <functional>

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

namespace Constants
{
	const TCHAR ProgramName[] = _T("ytdl");
	constexpr int HotkeyDownload = 1337;
}
