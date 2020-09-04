FROM python:3.8 

WORKDIR /srv

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update \
    && apt install -y build-essential sox libsox-fmt-mp3 cmake ninja-build

COPY . .

RUN mkdir build \
    && cd build \
    && cmake -GNinja .. \
    && ninja \
    && cd /srv/TestModule \
    && python3 setup.py build \
    && python3 setup.py install

CMD ["/usr/local/bin/python3", "/srv/TestModule/scratch.py"]
