#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>



int main(){

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_socket < 0 ? printf("Error Opening Socket\n") : printf("Socket Working\n");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(server_socket, 100);
    int client_socket = accept(server_socket, NULL, NULL);

    int num;
    recv(client_socket, &num, sizeof(int), 0);

    printf("Recieved from Client : %d\n", num);

    int rev_num = 0, n = num, flag=0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    if (rev_num==n){
        flag=1;
    }
    
    
    send(client_socket, &flag, sizeof(int), 0);

    return 0;
}