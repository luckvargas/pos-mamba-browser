FROM ubuntu:14.04

WORKDIR /home/build

#Setup
RUN apt-get install -y software-properties-common && \
add-apt-repository ppa:beineri/opt-qt487-trusty -y && \
apt-get update -qq  && \
apt install -y opt-qt4-dev-tools \ 
git \
build-essential \
openssl \
libssl-dev \ 
libsqlite3-dev

# Build
# ARG CACHEBUST=1
RUN rm -rf test-qt4-travis && git clone https://github.com/stone-payments/pos-mamba-browser
RUN cd pos-mamba-browser && qmake pos-mamba-browser.pro && make && make install && ls

CMD QT_X11_NO_MITSHM=1 /opt/browser/bin/MambaWebBrowser
