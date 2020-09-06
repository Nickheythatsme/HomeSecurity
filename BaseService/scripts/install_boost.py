#!/usr/bin/env python3
"""
Nicholas Grout 9/5/2020

Download and install Boost for unix
"""
import os
import tarfile
import subprocess
from requests import get as rget

BOOST_DOWNLOAD_URL_UNIX = 'https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz'
BOOST_ZIP_FILENAME = 'boost.tar.gz'


class Context(dict):
    def __init__(self):
        super().__init__()


def download_boost_zip():
    req = rget(BOOST_DOWNLOAD_URL_UNIX, allow_redirects=True, stream=True)
    with open(BOOST_ZIP_FILENAME, 'wb') as fout:
        for chunk in req.iter_content(chunk_size=2048):
            fout.write(chunk)


def unzip_boost(boost_zip_filename: str=BOOST_ZIP_FILENAME) -> str:
    tar = tarfile.open(boost_zip_filename)
    boost_unzip_dir = tar.getmembers()[0]
    print('boost_unzip_dir: ' + boost_unzip_dir.path)
    tar.extractall()
    tar.close()


def boostrap_boost(boost_dir: str):
    pass



if __name__ == "__main__":
    download_boost_zip()
    unzip_boost()
