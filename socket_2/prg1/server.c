#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ntohs(6011);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == 0 ? printf("Done Binding\n") : printf("Error While Binding\n");
    struct sockaddr_in tempSendAddr;
    char buf[100];
    int len = sizeof(struct sockaddr);
    recvfrom(serverSocket, buf, 100, 0, (struct sockaddr *)&tempSendAddr, &len);
    printf("Recieved from Client : %s\n", buf);
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] >= 'a' && buf[i] <= 'z')
        {
            buf[i] = buf[i] - 32;
        }
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6009);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendto(serverSocket, buf, sizeof(buf), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));
}