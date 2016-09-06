//
//  tcp_server.cpp
//  server
//
//  Created by 冯文斌 on 16/9/5.
//  Copyright © 2016年 冯文斌. All rights reserved.
//

#include "tcp_server.hpp"

TCPServer::TCPServer(uv_loop_t* loop, const char* ip, int port)
{
    _ip = ip;
    _port = port;
    _loop = loop;
    
    uv_tcp_init(loop, &_server);
    
    uv_ip4_addr(ip, _port, &_addr);
    
    uv_tcp_bind(&_server, (const struct sockaddr*)&_addr, 0);
}

TCPServer::~TCPServer()
{
    
}

void TCPServer::alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void TCPServer::echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
    
    cout << "nread: " << nread << endl;
    cout << "read: " << buf->base << endl;
    
    if (buf->base)
        free(buf->base);
}

void TCPServer::on_new_connection(uv_stream_t *server, int status)
{
    cout << "server accept connection: " << status << endl;
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }
    
    uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}

int TCPServer::listen()
{
    int r = uv_listen((uv_stream_t*) &_server, 128, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 0;
    }
    
    cout << "server listen: " << _ip << ":" << _port << endl;
    return 1;
}

