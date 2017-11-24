#include "functionality.h"

//void load_files(e_news *list);
int compare_string(char a[], char b[]){
    int i =0;
    while(a[i] == b[i]){
        if(a[i]== '\0' && b[i] == '\0') break;
        i++;
    }
    if(a[i]== '\0'&& b[i] == '\0') return true;
    else return false;
}

e_news  * get_news(char *f){
    e_news *news = malloc(sizeof(e_news));
    news->no = 0;
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
    char *temp;
    word *temp_word;
        while ((read = getline(&temp_word, &len, file)) != -1){
        //getrid of \n 
        char temp_c = temp_word[strlen(temp_word) -1 ];
            if((compare_string(&temp_c,"\nx") ==true )||(compare_string(&temp_c,"\n") == true)){
                *temp_word[strlen(temp_word)-1] = 0;  
            } 
        //*temp_word = temp;
        news->tag_list[news->no] = temp_word;
        news->no +=1;
        printf("%s",news->tag_list[news->no]);
    }
    fclose(file);
    free(line);
    return news;
}

int scan_dir(e_news *list){
    //struct dirent * entry;
    DIR *d = opendir( "./enews" );

    if (d == 0) {
        perror("opendir");
        return;
    }
    char *dir[1000];
    int dir_le= 0;
    while ((dir[dir_le] = readdir(d)->d_name) != 0) {
        //printf("%s\n", entry->d_name);
        //dir[dir_le] = entry->d_name;  
        if (!(compare_string(dir[dir_le] , ".") == true || compare_string(dir[dir_le] ,"..") == true)){            
            //printf("%s",dir[dir_le]);  
            int length= 0;
            list->tag_list[dir_le] = get_news(dir[dir_le]);
            //printf("%i", enews_no[*e_num]);
        }
        if(compare_string(dir[dir_le] ,"..") == true) break;
        dir_le++;      
    }
    
    closedir(d);
    return dir_le;
}

// enews and V management

void data_management(){    
    /*int e_num;
    char *taglist[tag_no] = {"\0"};
    int  tag_num[tag_no] ;
    char * enews[enews_no][tag_no];*/
    taglist *list = malloc(100*sizeof(taglist));
    e_news *enews_list= malloc(100*sizeof(e_news));
    printf("%i",enews_list[0].no);
    size_t enews_no = scan_dir(enews_list);
    int check = false; 
/*
    for(int i = 0;i < enews_no;i++){
        for(int j =0; j<enews_list[i];i++){
            *list->list[list->no] = "\0";
            for(int k = 0; k < list->no;k++){
                if(compare_string(enews_list[i]->tag_list[j],list->list[k]) == true ) {
                    check = true;
                    break;
                }
            }
            if(check == false){
                *list->list[list->no] = enews_list[i]->tag_list[j];
                printf("%d \n", *list->list[list->no]);
                list->no++;
            }else check = false;
        }
    }*/
}

//check similarity

double check_similarity(){
    
}