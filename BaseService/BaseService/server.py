import http.server
import socketserver
import logging

from .config import ROOT_LOGGER_NAME
from .sensor_handler import SensorHandler

PORT = 8000
Handler = http.server.SimpleHTTPRequestHandler
logger = logging.getLogger(ROOT_LOGGER_NAME)


def serve():
    with socketserver.TCPServer(("", PORT), SensorHandler) as httpd:
        logger.info("serving at port %s", PORT)
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            logger.warning('Stopping due to keyboard interrupt')
        finally:
            httpd.shutdown()
