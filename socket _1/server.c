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
printf("Socket Created\n");
}

struct sockaddr_in servaddr, cliaddr;

servaddr.sin_family = AF_INET,
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);

int status = bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr));
if(status<0){
printf("Binding Failed");
exit(EXIT_FAILURE);
}

char exitStr[] = "exit";

while(1){
char buffer[MAXLEN];
int lenClient = sizeof(cliaddr);
int n = recvfrom(sockfd, (char*)buffer, MAXLEN, MSG_WAITALL, (struct sockaddr*)&cliaddr, &lenClient);
buffer[n] = '\0';
printf("Reply : %s", buffer);
if(strncmp("exit", buffer, 4)==0){
printf("Server exit");
exit(EXIT_SUCCESS);
}
char msg[MAXLEN];
printf("Message for client : ");
fgets(msg, MAXLEN, stdin);
int lenMsg = strlen(msg);
sendto(sockfd, (char*)msg, lenMsg, MSG_CONFIRM, (const struct sockaddr*)&cliaddr, sizeof(cliaddr));
if(strncmp("exit", msg, 4)==0){
printf("Client exited");
exit(EXIT_SUCCESS);
}
}
close(sockfd);
}
