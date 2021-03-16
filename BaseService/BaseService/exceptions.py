from typing import Optional


class MissingAssetException(Exception):
    def __init__(self, filename: str):
        self.filename: str = filename
        message = f"Missing asset \"{self.filename}\""
        super().__init__(message)


