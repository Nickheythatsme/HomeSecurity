import json
import http.server

from http import HTTPStatus


class SensorHandler(http.server.CGIHTTPRequestHandler):
    def play_sound(self):
        pass

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
        try:
            data = json.loads(raw_data)
            self.send_success()
            if data['data']['door_open']:
                self.play_sound()
        except (KeyError, json.decoder.JSONDecodeError):
            self.send_parse_error()
            return


