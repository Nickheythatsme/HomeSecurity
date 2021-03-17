import os
import logging
import subprocess
from random import choice

from sys import platform

from .config import ROOT_LOGGER_NAME
from .exceptions import MissingAssetException


class SoundPlayer:
    logger = logging.getLogger(ROOT_LOGGER_NAME).getChild("SoundPlayer")
    ASSETS_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "assets")
    DOOR_OPEN_FILE = os.path.join(ASSETS_DIR, "ping.mp3")

    @classmethod
    def play_asset(cls, asset_file: str, repeat: int = 1):
        if platform != "linux" and platform != "linux2":
            cls.logger.warning("Sound is not supported on windows")
            return
        if not os.path.exists(asset_file):
            raise MissingAssetException(asset_file)
        for i in range(0, repeat):
            proc = subprocess.Popen(
                args=["play", cls.DOOR_OPEN_FILE], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )
            if proc.returncode:
                cls.logger.warning(
                    "Error playing sound file: %s\n%s",
                    proc.stdout.read(),
                    proc.stderr.read())

    @classmethod
    def play_door_open(cls):
        cls.play_asset(cls.DOOR_OPEN_FILE)
