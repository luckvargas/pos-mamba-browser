FROM ubuntu:14.04

WORKDIR /home/build

#Setup
RUN apt-get update && apt-get install -y software-properties-common && \
add-apt-repository ppa:beineri/opt-qt487-trusty -y && \
apt-get update -qq  && \
apt install -y opt-qt4-dev-tools \ 
git \
build-essential \
openssl \
libssl-dev \ 
libsqlite3-dev

# Buildsource /opt/qt*/bin/qt*-env.sh;
ARG CACHEBUST=1
RUN rm -rf pos-mamba-browser && git clone https://github.com/stone-payments/pos-mamba-browser
RUN cd pos-mamba-browser && \
 git checkout add-dockerfile && \
 /opt/qt-4.8/bin/qmake TARGET=browser pos-mamba-browser.pro && make && ls -la

CMD QT_X11_NO_MITSHM=1 /opt/browser/bin/MambaWebBrowser
