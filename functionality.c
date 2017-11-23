#include "functionality.h"

void load_files(e_news *list);


void gettaglist(char *f,char * enews[tag_no],int * length){
    FILE *file;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char text[100];
    // 
    strcpy(text,"./enews/");
    strcat(text,f);    
    //strcat(text,f);
    file = fopen(text,"r");   
    if(file == NULL) exit(-1);
    while ((read = getline(&enews[*length], &len, file)) != -1){
        //getrid of \n 
        enews[*length][strlen(enews[*length])-1] = 0;  
        *length += 1;
    }
    fclose(file);
}

void scan_dir(char * enews[][tag_no],int enews_no[],int * e_num){
    struct dirent * entry;
    DIR *d = opendir( "./enews" );

    if (d == 0) {
        perror("opendir");
        return;
    }
    //char *list[1000];

    char *dir[1000];
    int dir_le= 0;
    while ((entry = readdir(d)) != 0) {
        //printf("%s\n", entry->d_name);
        dir[dir_le] = entry->d_name;  
        if (!(strcmp(dir[dir_le] , ".") == 0 || strcmp(dir[dir_le] ,"..") == 0)){            
            //printf("%s",dir[dir_le]);  
            int length= 0;
            gettaglist(dir[dir_le],enews[*e_num],&length);
            enews_no[*e_num]= length;
            //printf("%i", enews_no[*e_num]);
            *e_num += 1;
        }
        dir_le++;      
        //read your file here
    }
    
    closedir(d);
}

// enews and V management

void data_management(){

    //e_news * enews = malloc(1000*sizeof(e_news));
    //e_news *enews[1000];
    int e_num;
    char * taglist[tag_no];
    int  tag_num[tag_no] ;
    tag_num[0]=10;
    tag_num[1]= 22;
    char * enews[enews_no][tag_no];
    scan_dir(enews,tag_num,&e_num);
    for(int i = 0; i< e_num;i++){
        for(int j = 0 ; j< tag_num[i];j++){
            printf("%s \n",enews[i][j]);
        }
    }

}