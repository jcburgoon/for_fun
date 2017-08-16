#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <arpa/inet.h>

int main(int arg, char *argv[])
{
    char errbuf[PCAP_ERRBUF_SIZE] = {0};
    pcap_if_t *all_interfaces = NULL;
    pcap_if_t *d = NULL;
    pcap_addr_t *a = NULL;
    char ip[INET_ADDRSTRLEN] = {0};
    char netmask[INET_ADDRSTRLEN] = {0};
    char ipv6[INET6_ADDRSTRLEN] = {0};

    if (pcap_findalldevs(&all_interfaces, errbuf) != 0)
    {
        printf("Error: %s\n", errbuf);
        exit(1);
    }

    for (d = all_interfaces; d != NULL; d = d->next)
    {
        for (a = d->addresses; a != NULL; a = a->next)
        {
            if (a->addr->sa_family == AF_INET)
            {
                printf("Device: %s\n", d->name);
                // get IP address
                inet_ntop(AF_INET, &(((struct sockaddr_in*)a->addr)->sin_addr), ip, INET_ADDRSTRLEN);
                printf("IP: %s\n", ip);
                // get netmask
                inet_ntop(AF_INET, &(((struct sockaddr_in*)a->netmask)->sin_addr), netmask, INET_ADDRSTRLEN);
                printf("Netmask: %s\n", netmask);
            }

            if (a->addr->sa_family == AF_INET6)
            {
                // get IPv6 address
                inet_ntop(AF_INET6, &(((struct sockaddr_in6*)a->addr)->sin6_addr), ipv6, INET6_ADDRSTRLEN);
                // extra \n : separate interface data (many assumptions here)
                printf("IPv6: %s\n\n", ipv6);
            }

        }

    }

    pcap_freealldevs(all_interfaces);
    exit(0);
}