#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
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
