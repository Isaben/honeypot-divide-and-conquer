#include <stdio.h>
#include "honeypot.h"
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    printf("SEQUENCIALMENTE: %d segundos", examine_servers_sequentially());
    
    return 0;
}