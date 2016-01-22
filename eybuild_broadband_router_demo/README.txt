1. WINDOWS + VC++ 编译运行方法:
   a. 安装 eybuild 1.0.2, 下载地址: http://www.eybuild.com
   b. 用 VC++ 打开 bbr/win32 中的 bbr.dsw
   c. 编译生成 bbr.cgi
   d. 将 bbr.cgi 拷贝到 web 服务器的 cgi-bin 目录运行

2. Linux 编译运行方法:
   a. 安装 eybuild 1.0.2, 下载地址: http://www.eybuild.com
   b. 进行 bbr/unix 目录, cd bbr/unix
   c. make clean all
   d. 将 bbr.cgi 拷贝到 web 服务器的 cgi-bin 目录运行

3. Boa Web Server 缺陷报告及其修正方法:
   由于 boa Webserver 处理 MIME 头存在缺陷, 导致某些 CGI应答不能被正确发送.
   见: Boa Web Server 缺陷报告及其修正方法
   http://bbs.chinaunix.net/viewthread.php?tid=824840
   
   修正方法: 
   a. 将所附的 boa/cgi_header.c 替换 boa/src/cgi_header.c
   b. 重新编译安装 BOA


更多信息请访问: 
http://www.eybuild.com

newzy
2006.10.10
