import sys
import os
import subprocess
import re
from functools import partial

# Make pythonw behave without outputs. Replace stdout/err with devnull
sys.stdout = open(os.devnull, 'w')
sys.stderr = sys.stdout

# Install pafy if it doesn't exist on system
try:
	import pafy
except ImportError:
	os.system('pip install pafy')
	import pafy

# List of modifiers to downloaded files' names
NAME_MODIFIERS = [
	partial(re.sub, r'[\\/:*?"<>|]', ''), # Escape illegal windows path chars
	partial(re.sub, r' ?[\(\[\{]Official Video[\]\)\}]', '', flags=re.IGNORECASE) # Remove retarded [Official Video]s. Jesus christ.
]

# Leaves only the "watch?v=" argument in the URL as pafy doesn't work with anything else
def strip_url(url):
	return re.compile('^((https?\\:\\/\\/)?(www\\.)?youtube\\.com\\/watch\\?v\\=[A-Za-z0-9_-]{11})').match(url)[0]

def main(url):
	# try/except block to remove the temporary video file no matter what happens
	try:
		video = pafy.new(strip_url(url))
		stream = video.getbestaudio()

		# Apply name modifiers
		processed_title = video.title
		for mod in NAME_MODIFIERS:
			processed_title = mod(processed_title)

		# Determine output filename
		filepath = 'C:\\Users\\{}\\Music\\{}'.format(os.getenv('username'), processed_title)
		before_conversion = '{}.{}'.format(filepath, stream.extension)
		after_conversion = '{}.{}'.format(filepath, 'mp3')

		# Download and convert to mp3
		stream.download(filepath=before_conversion, quiet=True)
		subprocess.run('ffmpeg -y -i "{}" "{}"'.format(before_conversion, after_conversion), shell=True)
	finally:
		try:
			os.remove(before_conversion)
		except:
			pass

if __name__ == '__main__':
	if len(sys.argv) == 2:
		main(sys.argv[1])
