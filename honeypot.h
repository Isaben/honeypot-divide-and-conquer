#ifndef HONEYPOT
#define HONEYPOT

#define MALICIOUS 1
#define BENIGN 0
#define CLIENT_CRASH 1
#define CLIENT_NORMAL 0
#define WAIT_TIME 15 // 15 segundos, simular tempo de classificação. Tw do artigo
#define RESPONSE_TIME 5 // 5 segundos, simular tempo de resposta dos servidores. Ti do artigo
#define RESET_TIME 10 // 10 segundos, simular tempo de reset do client. Tr do artigo
#define MAX_SERVERS 50 // quantidade de servidores
#define PROB_MALICIOUS 5 // em porcentagem e.g se 20, significa 20% de chance de um servidor ser malicioso. Utilizado na init_servers()

typedef struct client {
    int state;
    int crashes;
}client;

// inicia uma máquina cliente
client init_client();

// retorna um vetor de inteiros, cada índice correspondendo a um servidor
int* init_servers();

// retorna o tempo necessário para examinar de acordo com os parâmetros
int examine_servers_sequentially();

#endif 