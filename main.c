#include "functionality.h"

int main(){
    char *list[1000];
    int length = 0 ;
    gettaglist(list,&length);
    printf("%i",length);
    for(int i =0;i <length; i++){
        printf("%s ",list[i]);
    }

    return 0;
}