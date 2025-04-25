# 在Linux服务器中搭建Minecraft服务器。
有两种安装方式，手动部署不需要GUI和Panel，节省性能；采用MCSManager需要更多性能，但不需要Screen，且管理方便。

## 手动部署方式

### 安装java

在向服务器使用ftp上传java文件后使用sudo tar -zxvf ./jdk-8u162-linux-x64.tar.gz -C /usr/lib/jvm解压文件。

使用vim ~/.bashrc 打开用户的环境变量配置文件。（在/etc的profile文件也可以）

export JAVA_HOME=/usr/lib/jvm/jdk1.8.0_162

export JRE_HOME=${JAVA_HOME}/jre

export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib

export PATH=${JAVA_HOME}/bin:$PATH

退出保存后使用source ~/.bashrc 使配置生效。

使用 java -version 检查java是否安装成功。

### 安装游戏核心

向服务器ftp上传游戏端核心文件，保存至/root/mc下，在mc文件夹里新建空文件，文件名run.sh，内容为java -Xms768m -Xmx1536m -jar /root/mc/minecraft_server.1.15.2.jar nogui，

其中-Xms:初始启动分配的内存， -Xmx:最大分配的内存(按服务器配置来设置)，nogui:用于以基于文本的界面来显示，可减少内存使用。

之后输入 cd /root/mc 定位到mc目录，使用 ./run.sh 启动脚本，此时会启动失败，并产生eula.txt文件。同意最终用户许可协议 EULA及修改服务器配置文件
server.propertices后重启脚本，即可打开服务器端。

### 服务器长时间在线

断开SSH连接后服务器端自动关闭，因此需要Screen。

输入 screen -S mc 创建Screen，在其中开启脚本。

按Ctrl + A，再按D即可返回终端后台，screen -r mc  screen -D -r mc 可强制进入screen。


## 采用MCSManager安装

### 安装MCSManager

首先下载MCSManager。MCSManager可以开启并管理多个实例。

参照 https://docs.mcsmanager.com/zh_cn/安装。

使用 root 账户运行

sudo su -c "wget -qO- https://script.mcsmanager.com/setup_cn.sh | bash"

安装MCSManager。

接着在防火墙中放行23333和24444两个默认端口，25565为MC java默认端口，27015为L4D2默认端口。

在浏览器中输入 服务器公网ip:23333即可进入MCSManager面板控制台。


### 搭建MC服务器

应用实例-新建应用-MC Java服务端，上传服务端，以paper为例，在https://papermc.io/downloads下载得到对应版本的jar文件，上传文件，

启动命令填写

java -Dfile.encoding=UTF-8 -jar "刚刚下载的jar文件名，例如：paper-1.19.4-516.jar"

不过我的服务器曾经开过1.16.5的服务器，当时是java8，1.21需要java17以上。我重装java21并修改环境变量后MCSManager仍然无法启动，提示“检测到进程启动失败，其可能的原因是：

1. 实例启动命令编写错误，请前往实例设置界面检查启动命令与参数。

2. 系统主机环境不正确或缺少环境，比如缺少 Java 环境等。”

我使用XShell直接连接是可以执行命令的，经过一番排查，我显式的指定命令的java解决了这个问题。

/usr/local/java/jdk-21.0.5/bin/java -Dfile.encoding=UTF-8 -Xms1024m -Xmx2560m -jar paper-1.21.1-131.jar

 

### 安装java

Ubuntu可以使用apt-get安装，CentOS太老，需要手动安装。在https://www.oracle.com/downloads/#category-java下载对应的java文件得到一个压缩包，将压缩包解压到/usr/local/java下，现在应该有/usr/local/java/jdk-21这样的路径（版本号可能不同），修改/etc/profile，添加

JAVA_HOME=/usr/local/java/jdk-21 

CLASSPATH=.:$JAVA_HOME/lib.tools.jar 

PATH=$JAVA_HOME/bin:$PATH 

export JAVA_HOME CLASSPATH PATH

，运行source /etc/profile生效配置，运行java -version，有版本信息输出则说明成功安装java。

 

第一次运行后修改eula.txt同意协议，可以通过MCSManager的服务端配置文件直接修改，也可以在文件路径下找到用vim修改。修改server.properties，配置正版验证、白名单一类的。

 

再次启动，等待服务端开启。

进入游戏后可以在服务端输入 op 游戏id给予自己管理员权限。