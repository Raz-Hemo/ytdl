#
# Installer for ytdl
#
import os
import sys # for argv
import ctypes # for admin check
from win32com.client import Dispatch # for shortcut creation

STARTUP_PATH = 'C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Startup'
PROGRAM_PATH = 'ytdl'
SHORTCUT_PATH = os.path.join(STARTUP_PATH, '{}.lnk'.format(PROGRAM_PATH))

def install():
	# Create a startup shortcut to ytdl.exe
	print('\nAdding startup entry...\n')
	shell = Dispatch('WScript.Shell')
	shortcut = shell.CreateShortCut(SHORTCUT_PATH)
	shortcut.Targetpath = os.path.join(os.getcwd(), '{}.exe'.format(PROGRAM_PATH))
	shortcut.WorkingDirectory = os.getcwd()
	shortcut.save()

	# Install the youtube-dl and pyperclip packages for the python part
	print('\nInstalling dependencies...\n')
	os.system("pip install pyperclip")
	os.system("pip install youtube-dl")

	print("Installed successfully.")

def uninstall():
	# Remove the program from startup
	try:
		os.remove(SHORTCUT_PATH)
	except:
		print("No installation exists.")
	else:
		print("Uninstalled successfully.")

if __name__ == '__main__':
	if ctypes.windll.shell32.IsUserAnAdmin() != 1:
		print('Run this script as admin please.')
	elif len(sys.argv) != 2:
		print('Usage: ytdl_installer.py [-i|-u] - install/uninstall')
	else:
		if sys.argv[1] == '-i':
			install()
		elif sys.argv[1] == '-u':
			uninstall()