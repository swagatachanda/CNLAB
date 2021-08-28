#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
int sockfd,cnt;
char st1[100],st2[100];
char end_cli[100]="exit\n";
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd>0)printf("Socket creation successful:%d\n",sockfd);
else
{
printf("Socket creation unsuccessful:%d\n",sockfd);
exit(1);
}
struct sockaddr_in server2,client2;
server2.sin_family=AF_INET;
server2.sin_port=htons(8000);
server2.sin_addr.s_addr=inet_addr("127.0.0.1");
cnt=connect(sockfd,(const struct sockaddr *)&server2,sizeof(server2));
if(cnt==0)
printf("connection established:%d\n",cnt);
else
{
printf("connection not established:%d\n",cnt);
exit(1);
}
for(int i=0;;i++)
{
printf("enter a message for server \n");
fgets(st1,200,stdin);
send(sockfd,st1,sizeof(st1),0);
if(strcmp(st1,end_cli)==0)
break;
recv(sockfd,st2,sizeof(st2),0);
printf("Message received from server : \n%s\n",st2);
if(strcmp(st2,end_cli)==0)
break;
}
close(sockfd);
return 0;
}