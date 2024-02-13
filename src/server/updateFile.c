
#include "../../hdr/server_header.h"
extern const char *log_levels[];

void updateFile(FILE *csv_file,int len,int c,int client_id,char choice,int global,char num_groups[]){
        // printf("stored choice is:%c\n",c);
        fseek(csv_file,-len,SEEK_CUR);
        fprintf(csv_file,"%d,%c,%c,%s\n", client_id,choice,global,num_groups);
        fflush(csv_file);
        if(c=='A'){
                LOG(LOG_LEVEL_INFO,"Previously it was activated,now its DEACTIVATED");
                sendToClient(client_socket,"Previously it was activated,now its DEACTIVATED");
        }
        else{
                LOG(LOG_LEVEL_INFO,"Previously it was deactivated,now its ACTIVATED");
                sendToClient(client_socket,"Previously it was deactivated,now its ACTIVATED");
        }
        printf("\n");
}
