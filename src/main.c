#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../include/my_ping.h"

int main(int argc, char *argv[]) 
{
    int iter = 0, ip_place = -1;
    const char *usage =
        "\n"
        "Usage: my_ping [-t] target_ip\n\n"
        "Options:\n"
        "\t-t\tPing the specified ip address until stoopped.\n"
        "\nExample:\n"
        "\tmy_ping 142.250.193.78\n";

    if (argc < 2) 
    {
        printf("%s\n", usage);
        return MY_PING_FAILED;
    }
    else if (argc == 2)
    {
        ip_place = 1;
        iter = 4;
    }
    else if (argc == 3)
    {
        if (strcmp("-t", argv[1]) == 0)
        {
            iter = -1;
            ip_place = 2;
        }
        else if(strcmp("-t", argv[2]) == 0)
        {
            iter = -1;
            ip_place = 1;
        }
        else
        {
            printf("\nInvalid argument!\n%s\n", usage);
            iter = 0;
            return MY_PING_FAILED;
        }
    }
    
    while (iter != 0)
    {
        ping(argv[ip_place]);
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1000);
#endif
    }

    return MY_PING_SUCCESS;
}
