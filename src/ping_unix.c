#ifndef _WIN32

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>
#include "ping.h"

extern unsigned short calculate_checksum(void *b, int len);

int my_ping(const char *ip_address) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    struct sockaddr_in addr;
    char packet[64] = {0};
    struct icmphdr *icmp = (struct icmphdr *)packet;
    struct timeval start, end;
    char buffer[1024];
    double rtt;

    if (sockfd < 0) 
    {
        perror("socket");
        return 1;
    }

    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip_address, &addr.sin_addr);

    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid() & 0xFFFF;
    icmp->un.echo.sequence = 1;
    icmp->checksum = calculate_checksum(packet, sizeof(packet));

    gettimeofday(&start, NULL);
    sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&addr, sizeof(addr));

    recv(sockfd, buffer, sizeof(buffer), 0);
    gettimeofday(&end, NULL);

    rtt = (end.tv_sec - start.tv_sec) * 1000.0 +
                 (end.tv_usec - start.tv_usec) / 1000.0;

    printf("Reply from %s: time=%.2fms\n", ip_address, rtt);
    close(sockfd);
    return 0;
}

#endif
