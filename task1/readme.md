# 熟悉Linux系统

## 目的
熟悉和掌握Linux系统基本命令，熟悉Linux编程环境，为以后的实验打下基础。

C语言编辑、编译。

## 要求
熟练掌握Linux基本文件命令；

掌握Linux编辑程序、对源代码进行编译、连接、运行及调试的过程；

认真做好预习，书写预习报告；

实验完成后要认真总结、完成实验报告。

# 认识和熟悉linux

## 什么是Linux
Linux是一种自由和开放源代码的Unix-like操作系统，由Linus Torvalds创建并开发。它是基于内核（kernel）的一组GNU工具和其他开源软件组成的。Linux系统可以运行在各种硬件平台上，包括PC，服务器，移动设备和嵌入式设备等。Linux系统具有多用户和多任务处理的能力，支持分时和实时处理，是一种稳定，高效和安全的操作系统。Linux系统有着丰富的应用程序和工具，支持多种编程语言和平台，包括Java，Python，C++等，也可以在Linux上运行各种桌面环境，如KDE，GNOME等。Linux是一种开发者友好的操作系统，也可以使用轻量级的命令行界面（CLI）进行操作。Linux系统在服务器，云计算，科学研究，网络，嵌入式系统等领域有着广泛的应用。
基于Linux内核的发行版有Debian（ubuntu），Redhat（CentOS）等系统，常用于服务器和个人主机。

## 配置linux的几种方法

### 1 WSL
在windows11后全面支持Windows Subsystem for Linux，使得在Windows系统下可以直接运行linux系统无需虚拟机。
在管理员模式下向powershell中输入dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart安装WSL必备组件，并输入dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart 打开hyper-V虚拟化后即可在应用商店中下载linux系统。

如果出现参考的对象类型不支持尝试的操作，重置网络net winsock reset即可。
缺点是不原生支持GUI界面。

### 2 安装双系统
以ubuntu为例，在ubuntu官网中下载镜像，使用烧录软件烧录到U盘中制作安装系统的引导盘，在实体机中安装双系统。在重启电脑后进入bios，以引导盘作为优先启动项，在引导系统的指引下安装到硬盘的空闲位置。

也可以使用Ventoy烧录U盘，制作多个启动镜像，甚至可以直接在其中启动虚拟机。Ventoy中可以直接运行vhdx镜像文件，免去了安装虚拟机。

缺点是每次开机时要调整或选择启动项。

### 3 安装虚拟机
可以使用VMware或VirtualBox安装Linux系统，使用iso文件在虚拟机中安装ubuntu系统。接下来安装过程同在实体机过程基本一致。

特别的，由于hyper-V的存在，虚拟机和WSL（以及WSA）会冲突。

### 4 购买云服务器
可以在阿里云、腾讯云或华为云中购买云服务器（轻量应用服务器），选定linux系统，购买后，在防火墙中开启22端口后，在本地输入云服务器ip，使用VSCode或XShell等SSH连接到服务器，之后像本地操作一样使用linux系统。如过要GUI，可以开启VNC服务后在本地使用VNC viewer远程连接。使用Xftp或WinSCP上传下载文件。
缺点是带宽昂贵，默认为5M，上传下载文件不方便。

## Linux与Windows的文件区别
在Linux中，文件具有的特点是：可通过操作系统或者程序对外提供信息，也能对内输入信息，可以被创建，删除。

Linux中，文件有特别重要的意义，他们为操作系统和设备提供了一个简单而统一的接口。在Linux中，几乎一切都可以看做是文件。普通程序完全可以像使用文件（普通定义）那样使用磁盘文件、串行口、打印机和其他设备。

硬件设备在linux操作系统中也被表示为文件。例如，可以通过mount -t iso9660 /dev/hdc /mnt/cdrom命令把cd-rom驱动器挂载为一个文件，在云服务器中购买并挂载硬盘也是同理。

## Linux的目录
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

## [Linux的命令](LinuxCommand.md)


## Vim/vi
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

## screen
用于多重视窗管理程序。
此处所谓的视窗，是指一个全屏幕的文字模式画面。通常只有在使用telnet登入主机或是使用老式的终端机时，才有可能用到screen程序。

screen -S yourname 建立名字为yourname的会话

Ctrl + A + D 暂时离开当前session，将目前的 screen session (可能含有多个 windows) 丢到后台执行，并会回到还没进 screen 时的状态，此时在 screen session 里，每个 window 内运行的 process (无论是前台/后台)都在继续执行，即使 logout 也不影响
screen -ls或–list 　显示目前所有的screen作业

screen -s 　指定建立新视窗时，所要执行的shell

screen -d <作业名称> 　将指定的screen作业离线

screen -r <作业名称> 　恢复离线的screen作业


## 文件编译

### 完整编译流程：

创建一个c语言源文件：

gcc -E hello.c -o hello.i（头文件展开，进行源文件中的宏替换，注释过滤）

gcc -S hello.i -o hello.s（将源文件编译成汇编文件）（这一阶段耗时最大）

gcc -c hello.s -o hello.o（将汇编文件转换成二进制文件）

gcc hello.o -o hello（将二进制文件打包成可执行文件）


### 简单编译方式：

gcc hello.c -o hello（将hello.c文件直接生成可执行文件hello）

gcc hello.c（默认会将hello.c转换成可执行文件并命名为a.out）

gcc编译中的各种参数：

gcc hello.c -I path -o app（指定头文件路径为path将c语言源文件hello.c编译称为可执行文件app）（低版本gcc中-I和path中不许有空格）（在编译时自己写的有文件路劲要正确包含或者指定头文件目录）

gcc hello.c -o hello -D DEBUG（在编译时加上一个DEBUG宏，可用于测试程序，在程序每一条输出语句用该宏包裹，编译时加宏就不用在文件里加宏）

gcc hello.c -o hello -O1（在生成可执行文件过程中将代码优化）（优化等级为0，1，2，3。其中0为不优化，3为最高优化等级）

gcc hello.c -o hello -Wall（输出可对代码进行优化的提示信息，如某个变量未使用过）

gcc hello.c -o hello -g（在程序中添加一些调试信息）（生成的程序会大一些）（gdb调试的时候必须加此参数）


# 我在阿里云服务器上做一些额外的实验

## 1.[在Linux服务器中搭建Minecraft服务器](MCServer.md)

## 2.[在Linux服务器搭建种子下载站](Qbittorrent.md)

## 3.[在服务器上部署VSCodeServer](VSCodeServer.md)


# 遇到的一些问题

尽管Linux有强大的开源生态，但GPU的驱动常常不尽人意，经常出问题，致使系统性能较低或直接崩溃。我在实体机上安装ubuntu22.04，添加了包含驱动软件源，自动更新后芯片组出问题（audio芯片组），表现为系统启动有几率卡死、Minecraft游戏帧数下降。在重启多次后卡入系统，在AMD官网下载GPU驱动，无法直接安装，由于是旧版驱动与较新系统的缘故，依赖关系错综复杂。最后使用aptitude安装降级GPU驱动涉及到的依赖包，在不重装系统的前提下解决了驱动问题。

Cuda安装也是比较麻烦的。
