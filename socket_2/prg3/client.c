#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
void gets(char *);
int main()
{
    int fd, bdl, len, i;
    char msg[100];
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in r1, r2;
    r1.sin_family = AF_INET;
    r1.sin_port = htons(3031);
    r1.sin_addr.s_addr = inet_addr("127.0.0.8");
    i = bind(fd, (struct sockaddr *)&r1, sizeof(r1));
    printf("Socket return value and Bind value: %d and %d\n", fd, i);
    struct sockaddr_in x1;
    x1.sin_family = AF_INET;
    x1.sin_port = htons(3030);
    x1.sin_addr.s_addr = inet_addr("127.0.0.8");
    while (1)
    {
        memset(msg, '\0', 100 * sizeof(char));
        //sender
        printf("Enter Message: ");
        gets(msg);
        len = strlen(msg);
        sendto(fd, msg, len, 0, (struct sockaddr *)&x1, sizeof(x1));
        //receiver
        if (!strcmp(msg, "EXIT"))
        {
            close(fd);
            break;
        }
        len = sizeof(r2);
        memset(msg, '\0', 100 * sizeof(char));
        int k = recvfrom(fd, msg, 100, 0, (struct sockaddr *)&r2, &len);
        msg[k + 1] = '\0';
        len = strlen(msg);
        if (!strcmp(msg, "EXIT"))
        {
            close(fd);
            break;
        }
        printf("Chat 2: %s\n", msg);
    }
    close(fd);
    return 0;
}