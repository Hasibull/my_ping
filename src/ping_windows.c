#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "../include/my_ping.h"

#pragma comment(lib, "ws2_32.lib")

extern unsigned short calculate_checksum(void *b, int len);

#define ICMP_ECHO       8
#define ICMP_ECHOREPLY  0

int ping(const char *ip_address) 
{
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in dest;
    char send_buf[64];
    char recv_buf[1024];

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) 
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock == INVALID_SOCKET) 
    {
        printf("Raw socket failed (Run as Admin)\n");
        WSACleanup();
        return 1;
    }

    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    if (WSAStringToAddressA((LPSTR)ip_address, AF_INET,
                NULL, (struct sockaddr *)&dest, &(int){ sizeof(dest) }) != 0)
    {
        printf("Invalid IP address\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    icmp_hdr_t *icmp = (icmp_hdr_t *)send_buf;
    memset(send_buf, 0, sizeof(send_buf));

    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->id = (uint16_t)GetCurrentProcessId();
    icmp->sequence = 1;
    icmp->checksum = 0;
    icmp->checksum = calculate_checksum(send_buf, sizeof(send_buf));

    DWORD start = GetTickCount();

    if (sendto(sock, send_buf, sizeof(send_buf), 0,
               (struct sockaddr *)&dest, sizeof(dest)) == SOCKET_ERROR) 
    {
        printf("sendto failed\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    int addr_len = sizeof(dest);
    int bytes = recvfrom(sock, recv_buf, sizeof(recv_buf), 0,
                         (struct sockaddr *)&dest, &addr_len);

    if (bytes == SOCKET_ERROR) 
    {
        printf("recvfrom failed\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    DWORD end = GetTickCount();
    printf("Reply from %s: time=%lums\n", ip_address, end - start);

    closesocket(sock);
    WSACleanup();
    return 0;
}

#endif