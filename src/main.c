#include <stdio.h>
#include "../include/my_ping.h"

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <ip_address>\n", argv[0]);
        return 1;
    }

    return 0;
}
