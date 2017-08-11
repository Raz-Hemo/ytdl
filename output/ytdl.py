import youtube_dl
import pyperclip
import re
import os

ydl_opts = {
    'format': 'bestaudio/best',
    'outtmpl': 'C:\\Users\\{}\\Music%(title)s.%(ext)s'.format(os.getenv('username')),
    'postprocessors': [{
        'key': 'FFmpegExtractAudio',
        'preferredcodec': 'mp3',
        'preferredquality': '192',
    }],
}

# Returns true if s is a valid youtube URL
def is_youtube_url(s):
	return len(re.findall('^(https?\:\/\/)?(www\.)?youtube\.com\/watch\?v\=[A-Za-z0-9_-]{11}$', s)) == 1

def get_highlighted_text():
	"""Gets highlighted text in the current active window"""
	shell = win32com.client.Dispatch("WScript.Shell")
	
	# Store old clipboard and copy marked text
	old_clipboard = pyperclip.paste()
	shell.SendKeys('^c')

	# Take the marked text and restore the clipboard
	copied_text = pyperclip.paste().encode('utf-8')
	pyperclip.copy(old_clipboard)

	return copied_text

def main():
	# Is it a youtube URL? if so, download
	text = get_highlighted_text()
	if is_youtube_url(text):
		with youtube_dl.YoutubeDL(ydl_opts) as ydl:
			ydl.download([text])

if __name__ == '__main__':
	main()	
