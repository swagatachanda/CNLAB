#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main()
{
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ntohs(6011);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == 0 ? printf("Done Binding\n") : printf("Error While Binding\n");
    struct sockaddr_in tempSendAddr;
    int buf[2], msg[5], sum;
    int len = sizeof(struct sockaddr);
    recvfrom(serverSocket, &msg, 5 * sizeof(int), 0, (struct sockaddr *)&tempSendAddr, &len);
    printf("Recieved from Client :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", msg[i]);
    }
    sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum = sum + msg[i];
    }
    buf[0] = sum / 5;
    buf[1] = msg[0];
    for (int i = 1; i < 5; ++i)
    {
        if (buf[1] < msg[i])
        {
            buf[1] = msg[i];
        }
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6009);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendto(serverSocket, buf, 2 * sizeof(int), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));
}