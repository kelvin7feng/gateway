//
//  tcp_client.cpp
//  client
//
//  Created by 冯文斌 on 16/8/18.
//  Copyright © 2016年 kelvin. All rights reserved.
//

#include "tcp_client.hpp"

TCPClient::TCPClient(uv_loop_t* loop, const char* ip, int port){
    _ip = ip;
    _port = port;
    
    _loop = loop;
    uv_tcp_init(_loop, &_client);
    uv_ip4_addr(_ip, _port, &_dest);
}

TCPClient::TCPClient(const TCPClient& TCPClient){
    
}

void TCPClient::set_loop(uv_loop_t* loop)
{
    _loop = loop;
}

void TCPClient::alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void TCPClient::echo_read(uv_stream_t *client, ssize_t nread, uv_buf_t buf) {
    printf("echo_read\r\n");
    /*if (nread < 0) {
     if (nread != UV_EOF)
     fprintf(stderr, "Read error %s\n", uv_err_name((int)nread));
     uv_close((uv_handle_t*) client, NULL);
     } else if (nread > 0) {
     
     }
     
     if (buf.base)
     free(buf.base);
     */
}

void TCPClient::on_write(uv_write_t *req, int status){
    if (status == -1) {
        fprintf(stderr, "error on_write");
        return;
    }
    printf("on_write\r\n");
    uv_stream_t* client = req->handle;
    uv_read_start(client, (uv_alloc_cb)alloc_buffer, (uv_read_cb)echo_read);
}

void TCPClient::on_connect(uv_connect_t *req, int status) {
    
    if (status == -1) {
        fprintf(stderr, "error on_write_end");
        return;
    }
    
    printf("on_connect,status:%d\r\n", status);
    
    string input = "hello";
    while(cin >> input)
    {
    int len = (int)input.length();
    
    char buffer[100];
    uv_buf_t buf = uv_buf_init(buffer, sizeof(buffer));
    
    buf.len = len;
    buf.base = (char*)input.c_str();
    
    uv_stream_t* tcp = req->handle;
    
    uv_write_t write_req;
    
    int buf_count = 1;
    
    int ret = uv_write(&write_req, tcp, &buf, buf_count, on_write);
    cout << "ret: " << ret << endl;
    }
}

void TCPClient::write(){
    char message[] = "hullo world1";
    int len = (int)strlen(message);
    printf("write:%s\r\n", message);
    
    char buffer[100];
    uv_buf_t buf = uv_buf_init(buffer, sizeof(buffer));
    
    buf.len = len;
    buf.base = message;
    
    uv_write_t write_req;
    
    int buf_count = 1;
    
    int ret = uv_write(&write_req, _connect_req.handle, &buf, buf_count, on_write);
    cout << "ret:" << ret << endl;
}

int TCPClient::connect(){
    uv_tcp_connect(&_connect_req, &_client, (const struct sockaddr*)&_dest, this->on_connect);
    cout << "client connect to " << _ip << ":" << _port << endl;
    return uv_run(_loop, UV_RUN_DEFAULT);
}


TCPClient::~TCPClient(){
    //delete _loop;
}