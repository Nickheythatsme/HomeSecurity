import json
import logging
import http.server

from http import HTTPStatus
from .config import ROOT_LOGGER_NAME
from .sound_player import SoundPlayer


class SensorHandler(http.server.CGIHTTPRequestHandler):
    logger = logging.getLogger(ROOT_LOGGER_NAME).getChild("SoundPlayer")

    @classmethod
    def play_sound(cls):
        SoundPlayer.play_door_open()

    def send_success(self):
        self.send_response(HTTPStatus.OK)
        self.send_header('Connection', 'close')
        body = b"done"
        self.send_header("Content-Type", "text/html;charset=utf-8")
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def send_parse_error(self):
        self.send_response(HTTPStatus.BAD_REQUEST)
        self.send_header('Connection', 'close')
        body = b"error parsing json data"
        self.send_header("Content-Type", "text/html;charset=utf-8")
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_POST(self):
        raw_data = (self.rfile.read(int(self.headers['content-length']))).decode('utf-8')
        self.logger.info('Received data from node: %s', raw_data)
        try:
            data = json.loads(raw_data)
            self.send_success()
            if data['data']['door_open']:
                self.logger.info('Door has been opened')
                self.play_sound()
        except (KeyError, json.decoder.JSONDecodeError):
            self.logger.info('Error reading door state')
            self.send_parse_error()
            return


