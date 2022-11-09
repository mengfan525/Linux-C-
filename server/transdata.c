#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "transdata.h"

void initialize_transdata(Trans_data* trans_data){
    memset(trans_data->cmd,0,sizeof(trans_data->cmd));
    memset(trans_data->user_data,0,sizeof(trans_data->user_data));
    memset(trans_data->file_log,0,sizeof(trans_data->file_log));
    memset(trans_data->buff,0,sizeof(trans_data->buff));
}
