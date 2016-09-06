//
//  tcp_server.hpp
//  server
//
//  Created by 冯文斌 on 16/9/5.
//  Copyright © 2016年 冯文斌. All rights reserved.
//

#ifndef tcp_server_hpp
#define tcp_server_hpp

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <unistd.h>
#include <iostream>

#endif /* tcp_server_hpp */


using namespace std;

class TCPServer{
    
public:
    TCPServer(uv_loop_t* loop, const char* ip, int port);
    int listen();
    void write();
    ~TCPServer();
    TCPServer(const TCPServer& TCPServer);
protected:
    static void on_write(uv_write_t *req, int status);
    static void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
    static void echo_write(uv_write_t *req, int status);
    static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
    static void on_new_connection(uv_stream_t *server, int status);
private:
    int _port;
    const char* _ip;
    uv_loop_t* _loop;
    uv_tcp_t _server;
    struct sockaddr_in _addr;
private:
    enum {
        CONNECT_TIMEOUT,
        CONNECT_FINISH,
        CONNECT_ERROR,
        CONNECT_DIS,
    };
};