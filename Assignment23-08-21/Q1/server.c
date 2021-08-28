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

    char line[100];
    recv(client_socket, &line, sizeof(line), 0);

    printf("Recieved from Client : %s\n", line);

    for (int i = 0; line[i]!='\0'; i++) {
        if(line[i] >= 'a' && line[i] <= 'z'){
            line[i] = line[i] - 32;
        }
    }
    
    
    send(client_socket, &line, sizeof(line), 0);

    return 0;
}