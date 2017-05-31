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
int examine_servers_sequentially(int* servers, int* malicious_servers){
    int total_time = 0;
    int i;

    for(i = 0; i < MAX_SERVERS; i++){
        total_time += (RESPONSE_TIME + WAIT_TIME);
        if(servers[i] == MALICIOUS) {
            malicious_servers[i] = 1;
            total_time += RESET_TIME;
        }
    }

    return total_time;
}

/* Examina os servidores recursivamente, armazena o tempo no ponteiro total_time
*/
void examine_servers_recursively(int* servers, int* malicious_servers, int* total_time, int start, int end) {

    if(start < end) {
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
            if(start < end -1 ) {
                examine_servers_recursively(servers, malicious_servers, total_time, start, middle);
                examine_servers_recursively(servers, malicious_servers, total_time, middle, end);
            } else {
                malicious_servers[start] = 1;
            }
        }
    }
}

/*  Retorna o tempo necessário para examinar os servidores usando a estratégia
    de divisão e conquista, de acordo com os parâmetros definidos nas macros.
*/
int divide_and_conquer_servers(int* servers, int* malicious_servers){

    int* total_time = malloc(sizeof(int));
    *total_time = 0;

    examine_servers_recursively(servers, malicious_servers, total_time, 0, MAX_SERVERS);

    return *total_time;
}

/*  Função que verifica se a classificação de servidores maliciosos foi realizada
    com sucesso.
*/
int check(int* servers, int* malicious_servers) {
    int i;
    for(i=0; i < MAX_SERVERS; i++) if(servers[i] != malicious_servers[i]) return 0;
    return 1;
}

int main(){

    int N = 100;
    srand(time(NULL));

    printf("Algoritmos de detecção de servidores maliciosos\n");
    printf("Simulação das estratégias sequencial e divisão e conquista\n\n");

    printf("Parâmetros da simulação:\n");
    printf("Número de servidores: %d\n", MAX_SERVERS);
    printf("Probabilidade de servidores maliciosos: %d%%\n", PROB_MALICIOUS);
    printf("Tempo de resposta dos servidores: %ds\n", RESPONSE_TIME);
    printf("Tempo de classificação: %ds\n", WAIT_TIME);
    printf("Tempo de reinicialização do honeypot a um estado limpo: %ds\n\n", RESET_TIME);

    unsigned long sum_seq = 0;
    unsigned long sum_dav = 0;

    int i;
    for(i=0; i < N; i++) {
        int* servers = init_servers();

        int* malicious_servers = calloc(MAX_SERVERS, sizeof(int));
        sum_seq += examine_servers_sequentially(servers, malicious_servers);
        if(!check(servers, malicious_servers)) {
            printf("Erro na detecção de servidores maliciosos pela estratégia sequencial");
            exit(-1);
        }

        malicious_servers = calloc(MAX_SERVERS, sizeof(int));
        sum_dav += divide_and_conquer_servers(servers, malicious_servers);
        if(!check(servers, malicious_servers)) {
            printf("Erro na detecção de servidores maliciosos pela estratégia de divisão e conquista");
            exit(-1);
        }
    }

    printf("Resultados:\n");
    printf("-------------------------------------------------------\n");
    printf("|  Estratégia   |  Sequencial  |  Divisão e Conquisa  |\n");
    printf("|-------------- |------------- |----------------------|\n");
    printf("|  Tempo médio  |  %6lu s    |      %6lu s        |\n", sum_seq/N, sum_dav/N);
    printf("-------------------------------------------------------\n");

    return 0;
}
