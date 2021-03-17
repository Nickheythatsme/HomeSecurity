import logging
import os

ROOT_LOGGER_NAME = "BaseService"


def init_logging():
    ch = logging.StreamHandler()
    formatter = logging.Formatter('[%(asctime)s][%(name)s][%(levelname)s]: %(message)s')
    ch.setFormatter(formatter)
    log_level_str = os.getenv("LOG_LEVEL", "INFO").upper()
    log_level = getattr(logging, log_level_str, logging.INFO)
    ch.setLevel(log_level)
    logger = logging.getLogger(ROOT_LOGGER_NAME)
    logger.setLevel(logging.DEBUG)
    logger.addHandler(ch)
    logger.info("Logging level set to \"%s\"", logging.getLevelName(ch.level))


init_logging()
