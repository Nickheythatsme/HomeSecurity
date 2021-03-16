import http.server
import socketserver

from http import HTTPStatus
from 

PORT = 8000

Handler = http.server.SimpleHTTPRequestHandler

def serve():
    try:
        with socketserver.TCPServer(("", PORT), Myhandler) as httpd:
            print("serving at port", PORT)
            httpd.serve_forever()
    except KeyboardInterrupt:
        print('Stopping due to keyboard interrupt')
        pass
