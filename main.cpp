#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
using namespace std;

//处理URL
void UrlRouter(int clientSock, string const & url)
{
    string hint;
    if (url == "/")
    {
        cout << url << " 收到信息1\n";
        hint = "haha, this is home page!";
        send(clientSock, hint.c_str(), hint.length(), 0);  //响应头已经发送完了，发送数据
    }
    else if (url == "/hello")
    {
        cout << url << " 收到信息2\n";
        hint = "hello!";
        send(clientSock, hint.c_str(), hint.length(), 0);
    }
    else
    {
        cout << url << " 收到信息3\n";
        hint = "not define URL!";
        send(clientSock, hint.c_str(), hint.length(), 0);
    }

}

int main()
{
	//socket起源于UNIX，Unix一切皆文件的思想，socket是一种"打开、读/写、关闭"模式的实现
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//建立套接字，失败返回-1 
	sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;         //指定地址族
    addr.sin_addr.s_addr = INADDR_ANY; //IP地址
    addr.sin_port = htons(8090);       //端口号初始化

    int rc;
    rc = bind(sock, (sockaddr*)&addr, sizeof(addr)); //将创建的socket绑定到指定的IP地址和端口上
    rc = listen(sock, 0); //设置监,监听服务

    //设置客户端
    sockaddr_in clientAddr;  // 用来存放发起连接请求的客户端的协议地址
    int clientAddrSize = sizeof(clientAddr);
    int clientSock;

	cout<<"wait client request..."<<endl;

    //接受客户端请求
    while (-1 != (clientSock = accept(sock,(sockaddr*)&clientAddr, (socklen_t*)&clientAddrSize)))
    {
		cout<<"====  print clientSock : "<< clientSock <<"  ===="<<endl;
        // 收请求
        string requestStr;
        int bufSize = 4096;
        requestStr.resize(bufSize); 

        //接受数据
        recv(clientSock, &requestStr[0], bufSize, 0);

        //取得第一行
        string firstLine = requestStr.substr(0, requestStr.find("\r\n"));
		cout<<"====get requestStr firstLine : "<< firstLine <<"  ===="<<endl;

        //取得URL
        firstLine = firstLine.substr(firstLine.find(" ") + 1);  //substr，复制函数，参数为起始位置（默认0），复制的字符数目
		cout<<"====get requestStr firstLine : "<< firstLine <<"  ===="<<endl;

        string url = firstLine.substr(0, firstLine.find(" "));  //find返回找到的第一个匹配字符串的位置，而不管其后是否还有相匹配的字符串。
		cout<<"====  print url : "<< url <<"  ===="<<endl;		


        //发送响应头
        string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=gbk\r\n"
            "Connection: close\r\n"
            "\r\n";
        send(clientSock, response.c_str(), response.length(), 0);

        //处理URL
        UrlRouter(clientSock, url);

        close(clientSock);//关闭客户端套接字
    }

    close(sock);//关闭服务器套接字

    return 0;
}
