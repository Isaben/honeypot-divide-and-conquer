#include <stdio.h>
#include "honeypot.h"

int main(){

    printf("SEQUENCIALMENTE: %d segundos", examine_servers_sequentially());
    
    return 0;
}