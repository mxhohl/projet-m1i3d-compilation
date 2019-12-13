#include <stdio.h>
#include "truc.h"
#define N 16

int main(){
    int i;
    int t[50];
    for(i=0; i<44; i++)
    {
        t[i+5]= 0;
    }
    while(i<1)
        printf("qqch %d", t[i++]);
    
    return 0;
}