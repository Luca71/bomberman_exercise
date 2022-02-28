#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>

typedef struct client_packet {
    int auth;
    float x;
    float y;
} client_packet_t;

/*
 * Create the client socket
 * @return The socked created
*/
int client_init_socket();

/*
 * Set the socket address
 * @param sin The socked socket addres struct
 * @param address The ip address to set
*/
void client_set_socket_address(struct sockaddr_in *sin, char *address);

/*
 * Send packet to server
 * @param _socket The socked
 * @param sin The socked in struct
 * @param player_id The player id
 * @param x The player x position
 * @param y The player y position
 * @param msg_len The total length of message
*/
void client_send_packet(SOCKET _socket, struct sockaddr_in sin, int player_id, float x, float y, int msg_len);

/*
 * Receive packet from server
 * @param _socket The socked
 * @param sin The socked in struct
 * @param msg_len The total length of message
*/
void client_receive_packet(SOCKET _socket, struct sockaddr_in sin, char *msg_content);