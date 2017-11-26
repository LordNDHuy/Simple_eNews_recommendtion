#include "functionality.h"
taglist * search(){
    char *sstr;
    size_t len =0;
    printf("input search string :");
    getline(&sstr,&len,stdin);
    sstr[strlen(sstr)-1] =0;
    taglist * list = malloc(10*sizeof(taglist));
    char * temp0 = sstr,*temp1;
    list->no =0;
    do{
        strtok_r(temp0," ",&temp1);
        list->list[list->no] = temp0;
        list->no++;
        //printf("%s%s\n",temp0,temp1);
        temp0=temp1;
    }while(*temp1 !=0);
    return list;
}
int main(int argc, char ** argv){
    recommendation();
    return 0;
}