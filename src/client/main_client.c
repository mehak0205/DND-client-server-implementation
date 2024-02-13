#include "../../hdr/client_header.h"

const char *log_levels[] = {
    "FATAL",
    "INFO",
    "WARNING",
    "DEBUG"
};
int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
       // perror("socket creation failed");
        LOG(LOG_LEVEL_FATAL,"Socket Creation Failed!\n");


        exit(EXIT_FAILURE);
    }

    // Initialize server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
       // perror("connection failed");
        LOG(LOG_LEVEL_FATAL,"Connection failed!\n");

        exit(EXIT_FAILURE);
    }
    int client_id;// choice;
    //int global;
    char choice,global;
    char num_groups[50];

    LOG(LOG_LEVEL_INFO, "Connection established.");

    printf("Enter choice\nA: Activate DND\nD: Deactivate DND\nH: Handle incoming call:\n");
    scanf("%c",&choice);
    getchar();
    if(choice=='H'){
    printf("Enter client ID you want to call:");
    scanf("%d", &client_id);
    getchar();
    write(client_socket,&choice,sizeof(choice));
    write(client_socket, &client_id, sizeof(client_id));
    }
    else{
        printf("Enter client ID:");
        scanf("%d", &client_id);
        getchar();
        if (choice =='A'){
        printf("Enter S for selective & G for global:\n");
        scanf("%c",&global);
        getchar();
                if (global=='S') {
                        printf("Enter comma seperated numbers you want to block: ");
                        scanf("%49s",num_groups); // Limit the number of characters read
                        while ((getchar()) != '\n'); // Clear input buffer
                }
        }
    // Send data to server
        write(client_socket, &choice, sizeof(choice));
        write(client_socket, &client_id, sizeof(client_id));
        if(choice=='A'){
                write(client_socket, &global, sizeof(global));
        }
        if (choice == 'A' && global=='S') {
                write(client_socket, &num_groups, sizeof(num_groups));
        }
    }
    // Receive and print messages from the server
    char buffer[1024];
    ssize_t bytes_received;
    while ((bytes_received = read(client_socket, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_received); // Print to standard output (console)
    printf("\n");
    }


    // Close socket
    close(client_socket);

    return 0;
}
