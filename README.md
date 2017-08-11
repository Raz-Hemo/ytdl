# ytdl
Utility for downloading youtube songs


Uses the hotkey combination Ctrl+Shift+Alt+D to dispatch a python script. It gets whatever highlighted text the user has in the active window, checks if the string is a youtube URL, and if it is, it uses [youtube-dl](https://github.com/rg3/youtube-dl/) to download the video as mp3 straight into the user's music folder.

Potentially the C++ part can be used to execute any function based on any hotkey.
