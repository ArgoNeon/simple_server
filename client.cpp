#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "errproc.hpp"

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
    write(fd, "Hello\n", 6);
    char buf[256];
    ssize_t nread = read(fd, buf, 256);
    if (nread == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        printf("EOF occured\n");
    }
    write(STDOUT_FILENO, buf, nread);

    sleep(10);

    close(fd);
    return 0;
}