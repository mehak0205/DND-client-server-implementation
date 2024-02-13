
#include "../../hdr/server_header.h"
extern const char *log_levels[];


void handleIncomingCall(int client_id){
        FILE *csv_file;
        csv_file=fopen("data.csv","r+");
        if (csv_file == NULL) {
       // printf("Error opening file!\n");
       LOG(LOG_LEVEL_FATAL,"Error opening file!\n");
        exit(1);
        }
        rewind(csv_file);
        int stored_client_id;
        char stored_choice;
        char line[256]; // Assuming the maximum line length won't exceed 256 characters
        while (fgets(line, sizeof(line), csv_file)) {
                char *token = strtok(line, ",");
                if (token != NULL) {
                // Extract and store client_id
                        stored_client_id = atoi(token);
                        if(stored_client_id==client_id){
                        token = strtok(NULL, ",");
                                if (token != NULL) {
                                        // Extract and store choice
                                        stored_choice = token[0];
                                        if(stored_choice=='A')
                                        {
                                                sendToClient(client_socket,"Client is in DND mode-Calls are Blocked");
                                                return;
                                        }
                                        else if(stored_choice=='D'){
                                                sendToClient(client_socket,"Incoming calls allowed\n");
                                                return;
                                        }
                                }
                        }
                }
        }
        sendToClient(client_socket,"This id is not registered");
}
