import sys
import os
import subprocess

# Install pafy if it doesn't exist on system
try:
	import pafy
except ImportError:
	os.system('pip install pafy')
	import pafy

def main(url):
	try:
		sys.stdout = open(os.devnull, 'w')
		sys.stderr = sys.stdout
		video = pafy.new(url)
		stream = video.getbestaudio()

		filepath = 'C:\\Users\\{}\\Music\\{}'.format(
			os.getenv('username'),
			''.join(list(filter(lambda x: x not in r'\/:*?"<>|', video.title)))) # remove illegal chars
		before_conversion = filepath + '.' + stream.extension
		after_conversion = filepath + '.mp3'

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
