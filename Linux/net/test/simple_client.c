#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../wrap.h"

const int   SERVERPORT = 8000;
const char* SERVERIP = "127.0.0.1";
char        buffer[BUFSIZ];

/*
 * tcp客户端
 * 创建套接字 socket
 * 绑定套接字(可有可无) bind
 * 发送连接 connect
 * 处理连接 write read
 * 关闭连接 close
 */

void tcp() {
    int ret;

    int                client_fd;
    struct sockaddr_in server_addr;
    socklen_t          server_addr_length;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == -1) {
        sys_err("socket error");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    server_addr_length = sizeof(server_addr);

    ret = connect(client_fd, (struct sockaddr*)&server_addr, server_addr_length);

    if (ret == -1) {
        sys_err("connect error");
    }

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        write(client_fd, buffer, strlen(buffer));
        int n = read(client_fd, buffer, BUFSIZ);
        write(STDOUT_FILENO, buffer, n);
    }

    close(client_fd);
}

/*
 * tcp客户端
 * 创建套接字 socket
 * 绑定套接字(可有可无) bind
 * 发送连接 connect
 * 处理连接 write read
 * 关闭连接 close
 */

void udp() {
    int                client_fd;
    struct sockaddr_in server_addr;
    socklen_t          server_addr_length;

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (client_fd == -1) {
        sys_err("socket error");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    server_addr_length = sizeof(server_addr);

    while (fgets(buffer, BUFSIZ, stdin) != NULL) {
        int n = sendto(client_fd, buffer, BUFSIZ, 0, (struct sockaddr*)&server_addr,
                       server_addr_length);
        if (n == -1) {
            sys_err("sendto error");
        }
        n = recvfrom(client_fd, buffer, BUFSIZ, 0, NULL, 0);  //不需要服务器的内容
        if (n == -1) {
            sys_err("recvfrom error");
        }
        write(STDOUT_FILENO, buffer, n);
    }

    close(client_fd);
}

int main() {

    udp();
    return 0;
}