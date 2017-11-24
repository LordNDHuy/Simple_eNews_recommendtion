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

e_news * get_news(char *f){
   
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
    e_news *news = malloc(sizeof(e_news));
    news->no = 0;
    while ((read = getline(&news->tag_list[news->no], &len, file)) != -1){
        int len = strlen(news->tag_list[news->no]);
        char temp[30];
        strncpy(temp,news->tag_list[news->no],len);
        if (temp[len-1]==10) temp[len-1] = 0;
        else temp[len] =0;
        strncpy(news->tag_list[news->no],temp,len);
        news->no +=1;        
    }
    fclose(file);
    return news;
}

int scan_dir(e_news **elist){
    
    //struct dirent * entry;
    DIR *d = opendir( "./enews" );

    if (d == 0) {
        perror("opendir");
        return;
    }
    char *dir[1000];
    int length =0;
    int dir_le= 0;
    while ((dir[dir_le] = readdir(d)->d_name) != 0) {
        //printf("%s\n", entry->d_name);
        //dir[dir_le] = entry->d_name;  
        e_news *temp = malloc(sizeof(e_news));
        if (!(compare_string(dir[dir_le] , ".") == true || compare_string(dir[dir_le] ,"..") == true)){            
            //printf("%s",dir[dir_le]);  
            elist[length] = get_news(dir[dir_le]);
            length++;
            printf("%s",dir[dir_le]);
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
    taglist *list =malloc(100*sizeof(taglist));
    e_news **enews_list =malloc(100*sizeof(e_news));
    //init 
    for(int i = 0;i<100;i++){
        enews_list[i] = malloc(sizeof(e_news));
    }

    size_t enews_no = scan_dir(enews_list);
    int check = false; 
    for(int i =0;i<enews_list[0]->no;i++){
        printf("%s \n",enews_list[0]->tag_list[i]);
    }
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