import os
import logging

from .config import ROOT_LOGGER_NAME
from .exceptions import MissingAssetException


class SoundPlayer:
    logger = logging.getLogger(ROOT_LOGGER_NAME).getChild("SoundPlayer")
    ASSETS_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "assets")
    DOOR_OPEN_FILE = os.path.join(ASSETS_DIR, "ping.mp3")

    def __init__(self):
        pass

    @classmethod
    def play_door_open(cls):
        if not os.path.exists(cls.DOOR_OPEN_FILE):
            raise MissingAssetException(cls.DOOR_OPEN_FILE)\
        
