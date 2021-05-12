#include <string.h>
#include <signal.h>

#include "event2/event.h"
#include "event2/listener.h"
#include "event2/bufferevent.h"


#include <iostream>

#define SPORT 5001
using namespace std;
//错误，超时，连接断开进入
void event_cb(bufferevent *be, short events, void *arg)
{
    cout << "[E]" << endl;
    //超时时间发送后，数据读取停止
    if(events & BEV_EVENT_TIMEOUT && events & BEV_EVENT_READING)
    {
        cout << "BEV_EVENT_TIMEOUT" << endl;
        //bufferevent_enable(be, EV_READ);
        bufferevent_free(be);
    }
    else if(events & BEV_EVENT_ERROR)
    {
        bufferevent_free(be);
    }
    else
    {
        cout << "OTHERS" << endl;
    }
}
void write_cb(bufferevent *be, void *arg)
{
    cout << "[W]" << endl;
}
void read_cb(bufferevent *be, void *arg)
{
    cout << "[R]" << endl;
    char data[1024] = {0};
    int len = bufferevent_read(be, data, sizeof(data) - 1);
    cout << "[" << data << "]" << endl;
    if(len <= 0) return;
    if(strstr(data, "quit") != NULL)
    {
        cout << "quit" << endl;
        //退出，并关闭socket
        bufferevent_free(be);
    }
    //发送数据，写入数据
    bufferevent_write(be, "OK", 3);
}

void listen_cb(struct evconnlistener *e, evutil_socket_t s, struct sockaddr *a, int socklen, void *arg)
{
    cout << "listen cb" << endl;
    event_base *base = (event_base *)arg;

    //创建bufferevent上下文
    bufferevent *bev = bufferevent_socket_new(base, s, BEV_OPT_CLOSE_ON_FREE);
    //添加监控事件
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    //设置水位
    
    //读取水位
    bufferevent_setwatermark(bev, EV_READ,
        5,//低水位0,就是无限制，默认0
        10   //高水位0就是无限制，默认0
        );
    bufferevent_setwatermark(bev, EV_WRITE,
        5,//低水位0,就是无限制，默认0 缓冲数据低于5的时候被调用
        0   //高水未无效
        );

    //超时时间的设置
    timeval t1 = {3,0};
    bufferevent_set_timeouts(bev, &t1, 0);
    //设置回调函数
    bufferevent_setcb(bev, read_cb, write_cb, event_cb, base);

}
int main()
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        return 1;
    std::cout << "first libevent " << std::endl;
    //创建libevent上下文
    event_base *base = event_base_new();
    if(base)
    {
        cout << "event_base_new succes" << endl;
    }
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SPORT);
 
    //监听端口
    //socket, bind,listen
    evconnlistener *ev = evconnlistener_new_bind(base,   //libevent的上下文
            listen_cb,              //接收连接的回调函数
            base,                   //回调函数获取的参数arg
            LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,//地址重用，listen关闭的时候同时关闭sozket
            10,                     //连接的队列大小，对应的listen函数
            (sockaddr*)&sin,        //绑定的地址端口
            sizeof(sin)
            );
    //事件分发处理
    if(base)
        event_base_dispatch(base);
    if(ev)
        evconnlistener_free(ev);
    if(base)
    {
        event_base_free(base);
    }
    
    return 0;
}