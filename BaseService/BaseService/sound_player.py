import os
import logging
import subprocess

from sys import platform

from .config import ROOT_LOGGER_NAME
from .exceptions import MissingAssetException


class SoundPlayer:
    logger = logging.getLogger(ROOT_LOGGER_NAME).getChild("SoundPlayer")
    ASSETS_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "assets")
    DOOR_OPEN_FILE = os.path.join(ASSETS_DIR, "ping.mp3")

    @classmethod
    def play_door_open(cls):
        if not os.path.exists(cls.DOOR_OPEN_FILE):
            raise MissingAssetException(cls.DOOR_OPEN_FILE)
        if platform == "linux" or platform == "linux2":
            popen_kwargs = {'args': ["play", cls.DOOR_OPEN_FILE], 'stdin': subprocess.PIPE, 'stdout': subprocess.PIPE,
                            'stderr': subprocess.PIPE}
            proc = subprocess.Popen(**popen_kwargs)
            return_code = proc.returncode
            proc = subprocess.Popen(**popen_kwargs)
            return_code = return_code or proc.returncode
            if return_code:
                cls.logger.warning(
                    "Error playing sound file: %s\n%s",
                    proc.stdout.read(),
                    proc.stderr.read())
        else:
            cls.logger.warning("Sound is not supported on windows")
