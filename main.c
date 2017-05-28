#include <stdio.h>
#include "honeypot.h"
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    printf("SEQUENCIALMENTE: %d segundos\n", examine_servers_sequentially());
    printf("DIVISÃO E CONQUISTA: %d segundos\n", divide_and_conquer_servers());
    return 0;
}
