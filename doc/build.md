# Building pos-mamba-browser
Pos-mamba-browser was developed using Qt 4.8.7 framework.

## Dependencies
In addition to a working development enviroment for your system you will need the following to build pos-mamba-browser
 - Qt 4.8.7
 - QtWebkit 4.9.4

### Ubuntu trusty
```
$ sudo add-apt-repository ppa:beineri/opt-qt487-trusty -y;
$ sudo apt update -qq
$ sudo apt install opt-qt4-dev-tools -y
```
To build project run:
```
$ qmake pos-mamba-browser.pro
$ make
```
For other Linux distributions visit [Qt download] session.

## For developtment
- Download and install [Qt Creator]
- Check our [CONTRIBUTING]

[Qt download]: https://download.qt.io/archive/qt/4.8/4.8.7/
[Qt Creator]: https://www.qt.io
[CONTRIBUTING]: contrib.md
