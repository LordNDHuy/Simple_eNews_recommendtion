#include "functionality.h"

void load_files(e_news *list);

void gettaglist(char *taglist[1000], int *length){
    FILE *file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    file = fopen("list.txt","r");   
    if(file == NULL) exit(-1);
    while ((read = getline(&taglist[*length], &len, file)) != -1){
        //printf("%s", line);
  
        //taglist[*length] = line;
    
        *length += 1;
    }

    fclose(file);
}