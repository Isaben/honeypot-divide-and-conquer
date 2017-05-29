#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MALICIOUS 1
#define BENIGN 0
#define WAIT_TIME 15 // Tempo de classificação em segundos. Tw do artigo
#define RESPONSE_TIME 5 // Tempo de resposta dos servidores em segundos. Ti do artigo
#define RESET_TIME 10 // Tempo para reiniciar o servidor ao estado limpo em segundos. Tr do artigo
#define MAX_SERVERS 50 // Quantidade de servidores
#define PROB_MALICIOUS 5 // Probabilidade de servidores maliciosos (0 a 100)

/*  Retorna um vetor de inteiros, cada índice correspondendo a um servidor
    Cada elemento do vetor possui uma flag BENIGN ou MALICIOUS
*/
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

/*  Retorna o tempo necessário para examinar os servidores usando a estratégia
    sequencial, de acordo com os parâmetros definidos nas macros.
*/
int examine_servers_sequentially(int* servers){
    int total_time = 0;
    int i;

    for(i = 0; i < MAX_SERVERS; i++){
        total_time += (RESPONSE_TIME + WAIT_TIME);
        if(servers[i] == MALICIOUS)
            total_time += RESET_TIME;

    }

    return total_time;
}

/* Examina os servidores recursivamente, armazena o tempo no ponteiro total_time
*/
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

/*  Retorna o tempo necessário para examinar os servidores usando a estratégia
    de divisão e conquista, de acordo com os parâmetros definidos nas macros.
*/
int divide_and_conquer_servers(int* servers){

    int* total_time = malloc(sizeof(int));
    *total_time = 0;

    examine_servers_recursively(servers, total_time, 0, MAX_SERVERS);

    return *total_time;
}

int main(){
    srand(time(NULL));
    int* servers = init_servers();
    printf("SEQUENCIALMENTE: %d segundos\n", examine_servers_sequentially(servers));
    printf("DIVISÃO E CONQUISTA: %d segundos\n", divide_and_conquer_servers(servers));
    return 0;
}
