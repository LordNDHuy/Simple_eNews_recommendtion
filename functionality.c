#include "functionality.h"

void load_files(e_news *list);


void gettaglist(char *taglist[1000], int *length, char *f){
    FILE *file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char text[100];
    // 
    strcpy(text,"./enews/");
    strcat(text,f);
    //printf("%s  \n",text);
    
    //strcat(text,f);
    file = fopen(text,"r");   
    if(file == NULL) exit(-1);
    while ((read = getline(&taglist[*length], &len, file)) != -1){
        //getrid of \n 
        taglist[*length][strlen(taglist[*length])-1] = 0;  
        *length += 1;
    }

    fclose(file);
}



void scan_dir(){
    struct dirent * entry;
    DIR *d = opendir( "./enews" );

    if (d == 0) {
        perror("opendir");
        return;
    }
    char *list[1000];
    int length = 0 ;
    char *dir[1000];
    int dir_le= 0;
    while ((entry = readdir(d)) != 0) {
        //printf("%s\n", entry->d_name);
        dir[dir_le] = entry->d_name;  
        if ((dir[dir_le] != ".") & (dir[dir_le] != "..")){
        gettaglist(list,&length,dir[dir_le]);
        }
        dir_le++;      
        
        //read your file here
    }
    printf("%i \n",length);
    for(int i = 0; i< length; i++){
        printf("%i %s \n",i, list[i]);
    }    
    closedir(d);
}