#include "honeypot.h"
#include <stdio.h>
#include <stdlib.h>

client init_client(){
    client new_client;
    new_client.state = CLIENT_NORMAL;
    new_client.crashes = 0;
    return new_client;
}

int* init_servers(){
    int* servers = (int*) malloc(MAX_SERVERS * sizeof(int));
    int i;

    for(i = 0; i < MAX_SERVERS; i++){
        if((rand() % 101) < PROB_MALICIOUS){
            servers[i] = MALICIOUS;
            continue;
        }
        servers[i] = BENIGN;
    }

    return servers;
}

int examine_servers_sequentially(){
    int total_time = 0;
    int* servers = init_servers();
    int i;

    for(i = 0; i < MAX_SERVERS; i++){
        total_time += (RESPONSE_TIME + WAIT_TIME);
        if(servers[i] == MALICIOUS)
            total_time += RESET_TIME;

    }

    return total_time;
}

void examine_servers_recursively(int* servers, int* total_time, int start, int end) {

    if(start < end - 1) {
        int middle = (end + start)/2;

        int i;
        int flag_malicious = 0;
        for(i = start; i < end; i++){
            if(servers[i] == MALICIOUS)
                flag_malicious = 1;
        }

        *total_time += RESPONSE_TIME + WAIT_TIME;

        if(flag_malicious) {
            *total_time += RESET_TIME;
            examine_servers_recursively(servers, total_time, start, middle);
            examine_servers_recursively(servers, total_time, middle, end);
        }
    }
}

int divide_and_conquer_servers(){

    int* servers = init_servers();

    int* total_time = malloc(sizeof(int));
    *total_time = 0;

    examine_servers_recursively(servers, total_time, 0, MAX_SERVERS);

    return *total_time;
}
