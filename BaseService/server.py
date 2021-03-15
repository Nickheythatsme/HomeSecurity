import http.server
import socketserver

from http import HTTPStatus

PORT = 8000

Handler = http.server.SimpleHTTPRequestHandler


class Myhandler(http.server.CGIHTTPRequestHandler):
    def do_POST(self):
        #print('path: ' + self.path)
        #print('requestline: ' + self.requestline)
        rawData = (self.rfile.read(int(self.headers['content-length']))).decode('utf-8')
        print('data: ' + rawData)
        self.send_response(200, "done")
        self.send_header('Connection', 'close')
        body = b"done"
        self.send_header("Content-Type", "text/html;charset=utf-8")
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        self.wfile.write(body)


with socketserver.TCPServer(("", PORT), Myhandler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()