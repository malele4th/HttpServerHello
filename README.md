# HttpServerHello

Linux C++ ：a sample http server

参考代码：https://blog.csdn.net/qq_40194498/article/details/80246570

## 运行服务器
```
$ g++ main.cpp -o http
./http
```
## 客服端请求

如果是本地的Ubuntu系统，浏览器地址栏输入：127.0.0.1:8090

如果是远程的服务器，在浏览器地址栏输入：10.173.47.248：8090 【10.173.47.248 改成自己的服务器IP地址，ifconfig -a 查看】

<div align="center">
<img src="https://github.com/malele4th/HttpServerHello/blob/master/1.PNG" />  
</div>

