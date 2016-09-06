//
//  tcp_client.hpp
//  client
//
//  Created by 冯文斌 on 16/9/5.
//  Copyright © 2016年 kelvin. All rights reserved.
//

#ifndef tcp_client_hpp
#define tcp_client_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <unistd.h>
#include <iostream>

#endif /* tcp_client_hpp */

using namespace std;

class TCPClient{
    
public:
    TCPClient(uv_loop_t* loop, const char* ip, int port);
    void set_loop(uv_loop_t* loop);
    int connect();
    void listen();
    void write();
    int writeToServer(const char* data, std::size_t len);
    int writeToClient(int clientid, const char* data, std::size_t len);
    ~TCPClient();
    TCPClient(const TCPClient& TCPClient);
protected:
    static void on_connect(uv_connect_t *req, int status);
    static void on_write(uv_write_t *req, int status);
    static void echo_read(uv_stream_t *server, ssize_t nread, uv_buf_t buf);
    static void echo_write(uv_write_t *req, int status);
    static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
    static void connect_thread(void* arg);
private:
    int _port;
    const char* _ip;
    uv_loop_t* _loop;
    uv_tcp_t _client;
    int connect_status;
    struct sockaddr_in _dest;
    uv_connect_t _connect_req;
private:
    enum {
        CONNECT_TIMEOUT,
        CONNECT_FINISH,
        CONNECT_ERROR,
        CONNECT_DIS,
    };
};