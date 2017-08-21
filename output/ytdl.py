import sys
import os
import subprocess
import re

sys.stdout = open(os.devnull, 'w')
sys.stderr = sys.stdout

# Install pafy if it doesn't exist on system
try:
	import pafy
except ImportError:
	os.system('pip install pafy')
	import pafy

# Leaves only the "watch?v=" argument in the URL as pafy doesn't work with anything else
def strip_url(url):
	return '^(https?\\:\\/\\/)?(www\\.)?youtube\\.com\\/watch\\?v\\=[A-Za-z0-9_-]{11}'

def main(url):
	try:
		video = pafy.new(url)
		stream = video.getbestaudio()

		filepath = 'C:\\Users\\{}\\Music\\{}'.format(
			os.getenv('username'),
			''.join(list(filter(lambda x: x not in r'\/:*?"<>|', video.title)))) # remove illegal chars
		before_conversion = '"{}.{}"'.format(filepath, stream.extension)
		after_conversion = '"{}.{}"'.format(filepath, 'mp3')

		# Download and convert to mp3
		stream.download(filepath=before_conversion, quiet=True)
		subprocess.run('ffmpeg -y -i {} {}'.format(before_conversion, after_conversion), shell=True)
	finally:
		try:
			os.remove(before_conversion)
		except:
			pass

if __name__ == '__main__':
	if len(sys.argv) == 2:
		main(sys.argv[1])
