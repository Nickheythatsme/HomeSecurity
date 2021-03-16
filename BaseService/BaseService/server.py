import http.server
import socketserver

from .sensor_handler import SensorHandler

PORT = 8000

Handler = http.server.SimpleHTTPRequestHandler


def serve():
    try:
        with socketserver.TCPServer(("", PORT), SensorHandler) as httpd:
            print("serving at port", PORT)
            httpd.serve_forever()
    except KeyboardInterrupt:
        print('Stopping due to keyboard interrupt')
        pass
