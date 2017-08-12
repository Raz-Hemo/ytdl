#pragma once
#include <tchar.h>
#include <Windows.h>
#include <string>
#include <functional>
#include <regex>

#ifdef UNICODE
typedef std::wstring tstring;
typedef std::wregex tregex;
#else
typedef std::string tstring;
typedef std::regex tregex;
#endif

namespace Constants
{
	const TCHAR ProgramName[] = _T("ytdl");
	constexpr int HotkeyDownload = 1337;
}
