
#include "../../hdr/server_header.h"

void processCommand(int client_socket) {
    int client_id;
    char choice;
    char num_groups[50]="NA";
    char  global='-';
    //Reading client info-----------
    read(client_socket, &choice, sizeof(choice));
    read(client_socket, &client_id, sizeof(client_id));
    if(choice=='H')
    {
            handleIncomingCall(client_id);
    }
    else
    {
        if(choice=='A'){
                read(client_socket, &global, sizeof(global));
        }
        if (choice == 'A' && global=='S'){
                read(client_socket, &num_groups, sizeof(num_groups));
        }
        openFile(client_id,choice,global,num_groups);
    }
}
