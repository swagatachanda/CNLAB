#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
int sockfd,bnd,li,l1,acpt;
char s1[100];
char s2[100];
char end_ser[100]="exit\n";
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd>0)
printf("Socket creation successful:%d\n",sockfd);
else
{
printf("Socket creation unsuccessful:%d\n",sockfd);exit(1);
}
struct sockaddr_in server2,client2;
server2.sin_family=AF_INET;
server2.sin_port=htons(8000);
server2.sin_addr.s_addr=inet_addr("127.0.0.1");
bnd=bind(sockfd, (const struct sockaddr *)&server2,sizeof(server2));
if(bnd==0)
printf("bind successful\n");
else
{
printf("bind unsuccessful\n");
exit(1);
}
int lstn= listen(sockfd, 5);
if(lstn==0)
printf("Successful");
else
printf(" un Successful");
int t=sizeof(server2);
acpt= accept(sockfd, (struct sockaddr *) &server2, &t);
if(acpt>0)
printf("Accept Successful");
else
printf("Accept Not Successful");
for(int i=0;;i++)
{
recv(acpt,s1,sizeof(s1),0);
printf("\nMessage received from Client : %s",s1);
if(strcmp(s1,end_ser)==0)
break;
printf("Enter message for client \n");
fgets(s2,100,stdin);
send(acpt,s2,sizeof(s2),0);
if(strcmp(s2,end_ser)==0)
break;
}
close(sockfd);
close(acpt);
return 0;
}