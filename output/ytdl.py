import pafy
import sys
import os
import subprocess

def main(url):
	try:
		video = pafy.new(url)
		stream = video.getbestaudio()

		filepath = 'C:\\Users\\{}\\Music\\{}'.format(
			os.getenv('username'),
			''.join(list(filter(lambda x: x not in r'\/:*?"<>|', video.title)))) # remove illegal chars
		before_conversion = filepath + '.' + stream.extension
		after_conversion = filepath + '.mp3'

		# Download and convert to mp3
		stream.download(filepath=before_conversion)
		subprocess.run('ffmpeg -y -i {} {}'.format(before_conversion, after_conversion), shell=True)
	finally:
		try:
			os.remove(before_conversion)
		except:
			pass

if __name__ == '__main__':
	if len(sys.argv) == 2:
		main(sys.argv[1])
