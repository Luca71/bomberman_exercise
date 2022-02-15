#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include "client.h"

int client_init_socket()
{
#ifdef _WIN32
    // this part is only required on Windows: it initializes the Winsock2 dll
    WSADATA wsa_data;
    if (WSAStartup(0x0202, &wsa_data))
    {
        printf("unable to initialize winsock2\n");
        return -1;
    }
#endif

    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0)
    {
        printf("unable to initialize the UDP socket\n");
        return -1;
    }
    return s;
}

void client_set_socket_address(struct sockaddr_in *sin, char *address)
{
    inet_pton(AF_INET, address, &sin->sin_addr); // this will create a big entian 32 bit address
    sin->sin_family = AF_INET;
    sin->sin_port = htons(9999); // converts 9999 to big endian
}

void client_send_packet(SOCKET _socket, struct sockaddr_in sin, int player_id, float x, float y, int msg_len)
{
    int id = player_id;
    float coordX = x;
    float coordY = y;
    char transform[12];
    sprintf(transform, "%d%.2f%.2f", id, coordX, coordY); // convert numbers to string and return value in transform

    int sent_bytes = sendto(_socket, transform, msg_len, 0, (struct sockaddr*)&sin, sizeof(sin));
    printf("sent %d bytes via UDP\n", sent_bytes);

    printf("%s\n", transform);
}