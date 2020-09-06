FROM python:3.8 

WORKDIR /srv

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update \
    && apt install -y build-essential g++ python-dev autotools-dev \
    libicu-dev libbz2-dev

# Install required python files
COPY requirements.txt .
RUN python3 -m pip install -r requirements.txt


# Build and Install boost
COPY scripts ./scripts
RUN ./scripts/install_boost

COPY . .

RUN cd /srv \
    && python3 setup.py build \
    && python3 setup.py install

EXPOSE 8000

CMD ["/usr/local/bin/python3", "/srv/scratch.py"]
