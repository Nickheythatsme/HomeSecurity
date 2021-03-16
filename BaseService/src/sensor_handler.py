

class SensorHandler(http.server.CGIHTTPRequestHandler):
    def play_sound(self):

    def do_POST(self):
        rawData = (self.rfile.read(int(self.headers['content-length']))).decode('utf-8')
        print('data: ' + rawData)
        self.send_response(200, "done")
        self.send_header('Connection', 'close')
        body = b"done"
        self.send_header("Content-Type", "text/html;charset=utf-8")
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        self.wfile.write(body)

