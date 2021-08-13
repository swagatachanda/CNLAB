#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = ntohs(6009);
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(clientSocket, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) == 0 ? printf("Binding Done\n") : printf("Error While Binding\n");
    int msg[5];
    printf("Type Message :\n");
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &msg[i]);
    }
    printf("Sent to Server :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", msg[i]);
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6011);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendto(clientSocket, &msg, 5 * sizeof(int), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));
    struct sockaddr_in tempsendaddr;
    int buf[2];
    int len = sizeof(struct sockaddr);
    recvfrom(clientSocket, buf, 2 * sizeof(int), 0, (struct sockaddr *)&tempsendaddr, &len);
    printf("\nReceive from Server : \n");
    printf("Average = %d", buf[0]);
    printf("\nHighest = %d", buf[1]);
}
