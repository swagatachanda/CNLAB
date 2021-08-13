#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#define PORT 8081
#define MAXLEN 1024
int main()
{
int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if(sockfd<0){
printf("Socket Failed\n");
exit(EXIT_FAILURE);
}
else{
printf("Socket Created");
}

struct sockaddr_in servaddr;

servaddr.sin_family = AF_INET,
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);

while(1){
char msg[MAXLEN];
printf("Message for Server : ");
fgets(msg, MAXLEN, stdin);
int lenMsg = strlen(msg);
sendto(sockfd, (char*)msg, lenMsg, MSG_CONFIRM, (const struct sockaddr*)&servaddr, sizeof(servaddr));
if(strncmp("exit", msg, 4)==0){
printf("Client Exited");
exit(EXIT_SUCCESS);
}
char buffer[MAXLEN];
int lenServer = sizeof(servaddr);
int n = recvfrom(sockfd, (char*)buffer, MAXLEN, MSG_WAITALL, (struct sockaddr*)&servaddr, &lenServer);
buffer[n] = '\0';
printf("Client : %s",buffer);
if(strncmp("exit", buffer, 4)==0){
printf("Server Exit");
exit(EXIT_SUCCESS);
}
}
close(sockfd);
}
