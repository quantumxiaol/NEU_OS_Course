#熟悉Linux系统

目的
熟悉和掌握Linux系统基本命令，熟悉Linux编程环境，为以后的实验打下基础。
C语言编辑、编译。

要求
熟练掌握Linux基本文件命令；
掌握Linux编辑程序、对源代码进行编译、连接、运行及调试的过程；
认真做好预习，书写预习报告；
实验完成后要认真总结、完成实验报告。

认识和熟悉linux
什么是Linux
Linux是一种自由和开放源代码的Unix-like操作系统，由Linus Torvalds创建并开发。它是基于内核（kernel）的一组GNU工具和其他开源软件组成的。Linux系统可以运行在各种硬件平台上，包括PC，服务器，移动设备和嵌入式设备等。Linux系统具有多用户和多任务处理的能力，支持分时和实时处理，是一种稳定，高效和安全的操作系统。Linux系统有着丰富的应用程序和工具，支持多种编程语言和平台，包括Java，Python，C++等，也可以在Linux上运行各种桌面环境，如KDE，GNOME等。Linux是一种开发者友好的操作系统，也可以使用轻量级的命令行界面（CLI）进行操作。Linux系统在服务器，云计算，科学研究，网络，嵌入式系统等领域有着广泛的应用。
基于Linux内核的发行版有Debian（ubuntu），Redhat（CentOS）等系统，常用于服务器和个人主机。

##配置linux的几种方法

1 WSL
在windows11后全面支持Windows Subsystem for Linux，使得在Windows系统下可以直接运行linux系统无需虚拟机。
在管理员模式下向powershell中输入dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart安装WSL必备组件，并输入dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart 打开hyper-V虚拟化后即可在应用商店中下载linux系统。

如果出现参考的对象类型不支持尝试的操作，重置网络net winsock reset即可。
缺点是不原生支持GUI界面。

2 安装双系统
以ubuntu为例，在ubuntu官网中下载镜像，使用烧录软件烧录到U盘中制作安装系统的引导盘，在实体机中安装双系统。在重启电脑后进入bios，以引导盘作为优先启动项，在引导系统的指引下安装到硬盘的空闲位置。

也可以使用Ventoy烧录U盘，制作多个启动镜像，甚至可以直接在其中启动虚拟机。Ventoy中可以直接运行vhdx镜像文件，免去了安装虚拟机。

缺点是每次开机时要调整或选择启动项。

3 安装虚拟机
可以使用VMware或VirtualBox安装Linux系统，使用iso文件在虚拟机中安装ubuntu系统。接下来安装过程同在实体机过程基本一致。

特别的，由于hyper-V的存在，虚拟机和WSL（以及WSA）会冲突。

4 购买云服务器
可以在阿里云、腾讯云或华为云中购买云服务器（轻量应用服务器），选定linux系统，购买后，在防火墙中开启22端口后，在本地输入云服务器ip，使用VSCode或XShell等SSH连接到服务器，之后像本地操作一样使用linux系统。如过要GUI，可以开启VNC服务后在本地使用VNC viewer远程连接。使用Xftp或WinSCP上传下载文件。
缺点是带宽昂贵，默认为5M，上传下载文件不方便。

Linux与Windows的文件区别
在Linux中，文件具有的特点是：可通过操作系统或者程序对外提供信息，也能对内输入信息，可以被创建，删除。

Linux中，文件有特别重要的意义，他们为操作系统和设备提供了一个简单而统一的接口。在Linux中，几乎一切都可以看做是文件。普通程序完全可以像使用文件（普通定义）那样使用磁盘文件、串行口、打印机和其他设备。

硬件设备在linux操作系统中也被表示为文件。例如，可以通过mount -t iso9660 /dev/hdc /mnt/cdrom命令把cd-rom驱动器挂载为一个文件，在云服务器中购买并挂载硬盘也是同理。

Linux的目录
/ 这是根目录（文件夹），文件系统树（数据结构 ）的根。

/bin 包含二进制文件，系统启动需要的可执行程序。

/boot 包含机器启动时所需的内核和文件。

/dev包含设备节点，与连接到计算机的物理设备一起使用的指令/接口。

/etc包含系统范围的配置文件（发音为etsy），大型软件包（如gtk，python，X11）一般也在此处存储配置文件。

/home 包含系统用户的目录（每个用户的下载，图片等）。

/lib 包含启动计算机的核心程序所必需的共享库。

/lost+found 包含由于系统崩溃或驱动器错误而放错位置的数据。

/media 包含用于USB，CD和DVD等媒体设备的安装点。

/mnt 是临时文件系统的挂载点（例如用来安装系统的内容）

/opt包含程序的其他程序包。如Edge和Minecraft Launcher将文件保存在此处。

/proc 包含与内核和正在运行的进程有关的文件。

/tmp 包含在执行程序时可能创建的临时文件。

/usr包含一个次要的只读系统树，用于与某些程序共享或用于安装在其他Linux系统上。上面存在许多目录也存在这里，并包含一些其他文件。

/var 包含随时间变化其大小发生变化的文件，例如日志和备份。

Linux的命令

man
访问Linux手册页的命令是man。

pwd 	
显示用户当前所在的目录。

ls
对于目录，该命令列出该目录下的所有子目录与文件。对于文件，将列出文件名以及其他信息。

ls [选项][目录或文件]

-a	查看当前目录下的文件，包括隐藏文件

-l	长格式显示文件

-lh	以方便阅读的长格式显示

cd
改变工作目录。将当前工作目录改变到指定的目录下。

cd 目录名

cd ..	返回上一级目录

cd ../..	返回上两级目录

cd ~	切换到家目录

cd /	切换到根目录

cd /home/lx/linux1/	绝对路径：从家目录出发，直到想要去的目录

cd …/lx/	相对路径：从当前目录出发，直到想去的目录

grep
用于查找文件里符合条件的字符串

grep [选项] '查找字符串' 文件名

-a	将binary文件以text文件的方式查找数据

-c	计算找到 ‘查找字符串’ 的次数

-i	忽略大小写的区别，即把大小写视为相同

-v	反向选择，即显示出没有 ‘查找字符串’ 内容的那一行

find 
用来在指定目录下查找文件

find [路径] [选项] 操作

-name test	查询指定目录下,命名为test的文件

-size +100k	查询指定目录下，文件大于100K的文件

-ctime n	查询指定目录下，在过去n天内被修改过的文件

chmod 
控制用户对文件的权限的命令

chmod [选项] 文件名

-r	赋予读取权限

-w	赋予写入权限

-x	赋予执行权限

777	赋予可读、可写、可执行权限（读：4，写：2，执行：1）

权限说明：（例：-rw-r--r-x 的权限为645）

权限显示位一共为10位，分为四段，从第二位算起，每三个一组

第1位代表文件类型（-表示为普通文件）

第2-4位代表文件所属用户拥有的权限（rw-：4+2=6）

第5-7位代表该用户所属组拥有的权限（-r--：4）

第8-10位代表其他用户拥有的权限（r-x：4+1=5）

ps
用来列出系统中当前正在运行的那些进程，类似于 windows 的任务管理器。

ps [选项]

-A	列出所有的进程 

-ef	查看全格式的全部进程

-w	显示加宽可以显示较多的资讯

-au	显示较详细的资讯

-aux	显示所有包含其他使用者的行程

kill
用于删除执行中的程序或工作

kill [选项]/[信号] 进程号

-l	参数会列出全部的信息名称。

-s	指定要送出的信息。

-1 (HUP)	重新加载进程

-9 (KILL)	杀死一个进程。(重点)

-15 (TERM)	正常停止一个进程。

netstat
查看端口

netstat -anp | grep 端口号

echo 
打印 

选项 -e

打印常量 直接打印

打印变量 变量前加$

打印命令 用反引号把命令引起来

ping
检测是否与主机连通

mkdir
创建空目录

mkdir [选项] [路径] 文件名

-p	层级创建

-v	显示创建顺序

rmdir
删除空目录 不能删除非空目录，不能删除文件

rmdir [-p] [路径] 目录名

-p	当子目录被删除后如果父目录也变成空目录的话，就连带父目录一起删除

touch 
新建空文件

touch [路径] 文件名 （可以多个）

tar
解压及压缩文件

打包压缩

tar -cvf etc.tar /app/etc #打包

tar -Jcvf pack.tar.xz pack/ #打包压缩为一个.xz格式的压缩包

解包解压

tar -xvf pack.tar # 解包pack.tar文件

tar -Jxvf pack.tar.xz /pack #解包解压.xz格式的压缩包到pack文件夹

tar工具本身不具备压缩的功能，需结合压缩工具才可以实现更好压缩。

-j: bzip2

-z: gzip

-J: xz

-c: 打包

-x: 解包


rm 
删除文件或目录

rm [选项] 文件名

-f	强制删除

-r	多级删除

-rf	强制删除给定目录下所有文件和目录

rm 和 rmdir 的区别：
rm 有选项， rmdir 没有选项；rmdir 只能删除空目录，不能删文件；rm 带上选项-r可以删除非空目录

mv 
mv命令是move的缩写，可以用来移动文件或者将文件改名（move(rename)files），是Linux系统下常用的命令，经常用来备份文件或者目录

mv [选项] [路径] 旧文件名 [新路径][新文件名]

-f	force 强制的意思，如果目标文件已经存在，不会询问而直接覆盖

-i	若目标文件 (destination) 已经存在时，就会询问是否覆盖

cp
复制文件或目录

cp指令用于复制文件或目录，如同时指定两个以上的文件或目录，且最后的目的地是一个已经存在的目录，则它会把前面指定的所有文件或目录复制到此目录中。若同时指定多个文件或目录，而最后的目的地并非一个已存在的目录，则会出现错误信息

cp [选项] [路径] 旧文件名 [新路径][新文件名]

-f 或 --force	强行复制文件或目录， 不论目的文件或目录是否已经存在

-i 或 --interactive	覆盖文件之前先询问用户

-r	递归处理，将指定目录下的文件与子目录一并处理。若源文件或目录的形态，不属于目录或符号链接，则一律视为普通文件处理

-R 或 --recursive	递归处理，将指定目录下的文件及子目录一并处理

cat
查看目标文件的内容

cat [选项] 文件名

-b	对非空输出行编号

-n	对输出的所有行编号

-s	不输出多行空行


Vim/vi
Vi是linux中重要的文本编辑器。

输入模式

在命令模式下按下 i 就进入了输入模式。

在输入模式中，可以使用以下按键：

字符按键以及Shift组合：输入字符

ENTER：回车键，换行

BACK SPACE：退格键，删除光标前一个字符

DEL：删除键，删除光标后一个字符

方向键：在文本中移动光标

HOME/END：移动光标到行首/行尾

Page Up/Page Down：/下翻页

Insert：切换光标为输入/替换模式，光标将变成竖线/下划线

ESC：退出输入模式，切换到命令模式

底线命令模式

在命令模式下按下:（英文冒号）就进入了底线命令模式。

底线命令模式可以输入单个或多个字符的命令，可用的命令非常多。

在底线命令模式中，基本的命令有（已经省略了冒号）：

q 退出程序

w 保存文件

按ESC键可退出底线命令模式。

screen
用于多重视窗管理程序。
此处所谓的视窗，是指一个全屏幕的文字模式画面。通常只有在使用telnet登入主机或是使用老式的终端机时，才有可能用到screen程序。

screen -S yourname 建立名字为yourname的会话

Ctrl + A + D 暂时离开当前session，将目前的 screen session (可能含有多个 windows) 丢到后台执行，并会回到还没进 screen 时的状态，此时在 screen session 里，每个 window 内运行的 process (无论是前台/后台)都在继续执行，即使 logout 也不影响
screen -ls或–list 　显示目前所有的screen作业

screen -s 　指定建立新视窗时，所要执行的shell

screen -d <作业名称> 　将指定的screen作业离线

screen -r <作业名称> 　恢复离线的screen作业


文件编译

完整编译流程：

创建一个c语言源文件：

gcc -E hello.c -o hello.i（头文件展开，进行源文件中的宏替换，注释过滤）

gcc -S hello.i -o hello.s（将源文件编译成汇编文件）（这一阶段耗时最大）

gcc -c hello.s -o hello.o（将汇编文件转换成二进制文件）

gcc hello.o -o hello（将二进制文件打包成可执行文件）

简单编译方式：

gcc hello.c -o hello（将hello.c文件直接生成可执行文件hello）

gcc hello.c（默认会将hello.c转换成可执行文件并命名为a.out）

gcc编译中的各种参数：

gcc hello.c -I path -o app（指定头文件路径为path将c语言源文件hello.c编译称为可执行文件app）（低版本gcc中-I和path中不许有空格）（在编译时自己写的有文件路劲要正确包含或者指定头文件目录）

gcc hello.c -o hello -D DEBUG（在编译时加上一个DEBUG宏，可用于测试程序，在程序每一条输出语句用该宏包裹，编译时加宏就不用在文件里加宏）

gcc hello.c -o hello -O1（在生成可执行文件过程中将代码优化）（优化等级为0，1，2，3。其中0为不优化，3为最高优化等级）

gcc hello.c -o hello -Wall（输出可对代码进行优化的提示信息，如某个变量未使用过）

gcc hello.c -o hello -g（在程序中添加一些调试信息）（生成的程序会大一些）（gdb调试的时候必须加此参数）


##我在阿里云服务器上做一些额外的实验。

###1在Linux服务器中搭建Minecraft服务器。

在向服务器使用ftp上传java文件后使用sudo tar -zxvf ./jdk-8u162-linux-x64.tar.gz -C /usr/lib/jvm解压文件。

使用vim ~/.bashrc 打开用户的环境变量配置文件。（在/etc的profile文件也可以）

export JAVA_HOME=/usr/lib/jvm/jdk1.8.0_162

export JRE_HOME=${JAVA_HOME}/jre

export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib

export PATH=${JAVA_HOME}/bin:$PATH

退出保存后使用source ~/.bashrc 使配置生效。

使用 java -version 检查java是否安装成功。

向服务器ftp上传游戏端核心文件，保存至/root/mc下，在mc文件夹里新建空文件，文件名run.sh，内容为java -Xms768m -Xmx1536m -jar /root/mc/minecraft_server.1.15.2.jar nogui，

其中-Xms:初始启动分配的内存， -Xmx:最大分配的内存(按服务器配置来设置)，nogui:用于以基于文本的界面来显示，可减少内存使用。

之后输入 cd /root/mc 定位到mc目录，使用 ./run.sh 启动脚本，此时会启动失败，并产生eula.txt文件。同意最终用户许可协议 EULA及修改服务器配置文件
server.propertices后重启脚本，即可打开服务器端。

断开SSH连接后服务器端自动关闭，因此需要Screen。

输入 screen -S mc 创建Screen，在其中开启脚本。

按Ctrl + A，再按D即可返回终端后台，screen -r mc  screen -D -r mc 可强制进入screen。

###2在Linux服务器搭建种子下载站。

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

遇到的一些问题

尽管Linux有强大的开源生态，但GPU的驱动常常不尽人意，经常出问题，致使系统性能较低或直接崩溃。我在实体机上安装ubuntu22.04，添加了包含驱动软件源，自动更新后芯片组出问题（audio芯片组），表现为系统启动有几率卡死、Minecraft游戏帧数下降。在重启多次后卡入系统，在AMD官网下载GPU驱动，无法直接安装，由于是旧版驱动与较新系统的缘故，依赖关系错综复杂。最后使用aptitude安装降级GPU驱动涉及到的依赖包，在不重装系统的前提下解决了驱动问题。
