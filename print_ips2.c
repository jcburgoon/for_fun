#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    struct ifaddrs *ifaddr, *ifa;
    int count = 0, i = 0, j = 0;

    struct Interface 
    {
        char name[50];
        char ip[INET_ADDRSTRLEN];
        char netmask[INET_ADDRSTRLEN];
        char ipv6[INET6_ADDRSTRLEN];
    } interface[10];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs() error");
        exit(-1);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family == AF_PACKET)
        {
            continue;
        }

        // addl check to prevent results like 1.0.0.0 (from AF_PACKET)
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            // get interface name
            strncpy(interface[count].name, ifa->ifa_name, sizeof(&(ifa->ifa_name)));

            // get ip addr 
            inet_ntop(AF_INET, &(((struct sockaddr_in*)ifa->ifa_addr)->sin_addr), interface[count].ip, INET_ADDRSTRLEN);

            // get netmask
            inet_ntop(AF_INET, &(((struct sockaddr_in*)ifa->ifa_netmask)->sin_addr), interface[count].netmask, INET_ADDRSTRLEN);

            // only increment count for each ipv4 interface
            count++; 
        }

        if (ifa->ifa_addr->sa_family == AF_INET6)
        {
            // find correct struct (assumes that there is a corresponding ipv4 int for each ipv6 int)
            for (j = 0; j < count; j++)
            {
                if (strcmp(ifa->ifa_name, interface[j].name) == 0)
                {
                    // set ipv6 addr
                    inet_ntop(AF_INET6, &(((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr), interface[j].ipv6, INET6_ADDRSTRLEN);
                }

            }

        }
 
    }

    // print out interface info
    // count is set while looping through the interfaces and using it here prevents garbage output
    for (i = 0; i < count; i++)
    {
        printf("Device: %s\n", interface[i].name);
        printf("IP: %s\n", interface[i].ip);
        printf("Netmask: %s\n", interface[i].netmask);
        printf("IPv6: %s\n", interface[i].ipv6);
        printf("\n");
    }

    freeifaddrs(ifaddr);
    exit(0);
}