//
//  main.cpp
//  main
//
//  Created by 冯文斌 on 16/8/18.
//  Copyright © 2016年 kelvin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include "tcp_server.hpp"
#include "tcp_client.hpp"

#define DEFAULT_PORT 7001

int main() {
    uv_loop_t *loop = uv_default_loop();
    TCPServer server(loop, "0.0.0.0", DEFAULT_PORT);
    server.listen();
    
    TCPClient client(loop, "127.0.0.1", 7000);
    client.connect();
    
    return uv_run(loop, UV_RUN_DEFAULT);
}