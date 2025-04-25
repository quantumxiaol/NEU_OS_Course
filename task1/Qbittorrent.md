# 在Linux服务器搭建种子下载站。

安装libtorrent（https://github.com/arvidn/libtorrent/releases）

qBittorrent基于libtorrent，所以必须先安装libtorrent。注意：libtorrent最新版已是1.2.x，但qBittorrent不支持，因此请安装1.1.x版本（本文以1.1.12为例）

安装依赖包

yum groupinstall "Development Tools"

yum install qt-devel boost-devel openssl-devel qt5-qtbase-devel qt5-linguist

下载libtorrent

libtorrent从1.1.13开始，将编译时调用的头文件boost-predef改为了boost-endian。因为boost版本问题，此版本并没有boost-endian这个头文件，因此1.1.13以上版本均会编译错误，所以建议安装1.1.12版。

cd ~
wget https://github.com/arvidn/libtorrent/releases/download/libtorrent_1_1_12/libtorrent-rasterbar-1.1.12.tar.gz

tar xf libtorrent-rasterbar-1.1.12.tar.gz

编译安装libtorrent

cd libtorrent-rasterbar-1.1.12

./configure --disable-debug --prefix=/usr CXXFLAGS=-std=c++11

make -j$(nproc)

make install

ln -s /usr/lib/pkgconfig/libtorrent-rasterbar.pc /usr/lib64/pkgconfig/libtorrent-rasterbar.pc

ln -s /usr/lib/libtorrent-rasterbar.so.9 /usr/lib64/libtorrent-rasterbar.so.9

安装qBittorrent（https://github.com/qbittorrent/qBittorrent/releases）

由于qBittorrent-4.2.5需要C++14进行编译，而centos7.x默认自带的gcc只支持C++11，因此我们需要更新gcc版本，为了保护系统环境不被破坏，我们选择使用SCL安装高版本gcc。

通过SCL构建gcc8.2环境

yum install centos-release-scl  

yum install devtoolset-8-gcc*

scl enable devtoolset-8 bash

下载qBittorrent-4.2.5

cd ~
wget https://github.com/qbittorrent/qBittorrent/archive/release-4.2.5.tar.gz
tar xf qBittorrent-release-4.2.5.tar.gz

编译安装qBittorrent-4.2.5

cd qBittorrent-release-4.2.5

./configure --prefix=/usr --disable-gui CPPFLAGS=-I/usr/include/qt5

make -j$(nproc)

make install

退出SCL环境

exit

设置开机自启、

vi /etc/systemd/system/qbittorrent.service

输入以下内容后保存：

[Unit]

Description=qBittorrent Daemon Service

After=network.target

[Service]

LimitNOFILE=512000

User=root

ExecStart=/usr/bin/qbittorrent-nox

ExecStop=/usr/bin/killall -w qbittorrent-nox

[Install]

WantedBy=multi-user.target


重载配置

systemctl enable qbittorrent.service

运行qBittorrent

初次前台运行，输入y同意协议

qbittorrent-nox

Ctrl + C关闭qBittorrent

后台运行qBittorrent

systemctl start qbittorrent.service

相关命令：

systemctl start qbittorrent.service #启动qBittorrent

systemctl stop qbittorrent.service #关闭qBittorrent

systemctl restart qbittorrent.service #重启qBittorrent

firewall-cmd --permanent --add-port=8080/tcp

firewall-cmd --permanent --add-port=8999/tcp

firewall-cmd --reload 