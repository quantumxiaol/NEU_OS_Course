# 搭建CodeServer

Code-server是Coder公司基于微软开源的Visual Studio Code开发的一款（VSCode网页版）产品。

可以在https://github.com/coder/code-server查找对应的版本，下载，上传到服务器解压。如果服务器网络比较好，可以直接使用wget来执行。

wget https://github.com/coder/code-server/releases/download/所需版本。

解压

tar -xvzf code-server-4.16.0-linux-amd64.tar.gz

在目录下运行

./bin/code-server/code-server --port 9999 --host 0.0.0.0 --auth password

注意防火墙放行对应端口。

生成的配置文件在~/.config/code-server/config.yaml，可以在其中查看或修改密码。

如果出现glibc版本太低，可以选择较旧的code-server版本。

# 访问CodeServer

接下来在浏览器输入ip:port即可访问CodeServer，可以安装一些Compile和Debug的插件，如果这些插件下载缓慢，可以在其GitHub下载，从vsix手动安装。

如果执行c++文件失败，提示没有gcc，可以手动安装gcc。

g++ --version

sudo yum install gcc-c++