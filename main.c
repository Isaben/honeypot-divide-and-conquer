#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MALICIOUS 1
#define BENIGN 0
#define WAIT_TIME 15 // 15 segundos, simular tempo de classificação. Tw do artigo
#define RESPONSE_TIME 5 // 5 segundos, simular tempo de resposta dos servidores. Ti do artigo
#define RESET_TIME 10 // 10 segundos, simular tempo de reset do client. Tr do artigo
#define MAX_SERVERS 50 // quantidade de servidores
#define PROB_MALICIOUS 5 // em porcentagem e.g se 20, significa 20% de chance de um servidor ser malicioso. Utilizado na init_servers()

// retorna um vetor de inteiros, cada índice correspondendo a um servidor
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

// retorna o tempo necessário para examinar de acordo com os parâmetros
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

// examina os servidores recursivamente, armazena o tempo no ponteiro total_time
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

// retorna o tempo necessário para examinar os servidores usando divisão e conquista
int divide_and_conquer_servers(){

    int* servers = init_servers();

    int* total_time = malloc(sizeof(int));
    *total_time = 0;

    examine_servers_recursively(servers, total_time, 0, MAX_SERVERS);

    return *total_time;
}

int main(){
    srand(time(NULL));
    printf("SEQUENCIALMENTE: %d segundos\n", examine_servers_sequentially());
    printf("DIVISÃO E CONQUISTA: %d segundos\n", divide_and_conquer_servers());
    return 0;
}
