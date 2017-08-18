#include "Clipboard.h"

#ifdef UNICODE
#define CF_TTEXT CF_UNICODETEXT
#else
#define CF_TTEXT CF_TEXT
#endif

tstring Clipboard::GetText()
{
	tstring result;

	if (OpenClipboard(NULL))
	{
		HANDLE cb_data = GetClipboardData(CF_TTEXT);

		// Convert to a c++ string if the clipboard is text. otherwise just leave the result empty
		if (NULL != cb_data)
		{
			result = (TCHAR*)GlobalLock(cb_data);
			GlobalUnlock(cb_data);
		}

		CloseClipboard();
	}

	return result;
}