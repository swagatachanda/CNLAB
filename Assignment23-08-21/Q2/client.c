#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){ 

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    client_socket < 0 ? printf("Error Making Socket\n") : printf("Socket Successful\n");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int stat = connect(client_socket, (struct sockaddr *) & server_address, sizeof(server_address));
    stat == -1 ? printf("Error During Connect\n") : printf("Connection Working\n");

    int num;
    printf("Enter a 3 digit number : ");
    scanf("%d",&num);
    printf("Sent to server : %d\n",num);
    send(client_socket, &num, sizeof(int), 0);

    int flag;
    recv(client_socket, &flag, sizeof(int), 0);
    //printf("Recieved from server : %s\n", line);
    if(flag==1){
        printf("The given number %d is a palindrome number.\n",num);
    }
    else{
        printf("The given number %d is not a palindrome number.\n",num);
    }
    //printf("Maximum : %d", res[1]);
    
    return 0;
}