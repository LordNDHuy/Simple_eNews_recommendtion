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
       char temp = enews[*length][strlen(enews[*length]) -1 ];
            if((compare_string(&temp,"\nx") ==true )||(compare_string(&temp,"\n") == true)){
                 enews[*length][strlen(enews[*length])-1] = 0;  
            } 
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
    char *dir[1000];
    int dir_le= 0;
    while ((entry = readdir(d)) != 0) {
        //printf("%s\n", entry->d_name);
        dir[dir_le] = entry->d_name;  
        if (!(compare_string(dir[dir_le] , ".") == true || compare_string(dir[dir_le] ,"..") == true)){            
            //printf("%s",dir[dir_le]);  
            int length= 0;
            gettaglist(dir[dir_le],enews[*e_num],&length);
            enews_no[*e_num]= length;
            //printf("%i", enews_no[*e_num]);
            *e_num += 1;
        }
        dir_le++;      
    }
    
    closedir(d);
}

// enews and V management

void data_management(){    
    int e_num;
    char *taglist[tag_no] = {"\0"};
    int  tag_num[tag_no] ;
    char * enews[enews_no][tag_no];
    scan_dir(enews,tag_num,&e_num);
    int V_num = 0,check = false; 
    
    for(int i = 0; i< e_num;i++){
        for(int j = 0 ; j< tag_num[i];j++){
            taglist[V_num] = "\0";// declare a \0 value for taglist since, at first it is null or point to 0x0
            for(int k = 0; k < V_num;k++){
                if(compare_string(enews[i][j],taglist[k]) == true ) {
                    check = true;
                    break;
                }
            }
            if(check == false){
                taglist[V_num] = enews[i][j];
                V_num++;
            }else check = false;
        }
    }
    //~~~~
    /*check_similarity_var * check_sim;
    check_sim->enews1[0]= "\0";
    for(int i = 0; i < V_num;i++){
        check_sim->taglist[i]=taglist[i];
    }
    for(int i =0;i < tag_num[0];i++){
        check_sim->enews1[i]=enews[0][i];
    }
    check_sim->enews1_no = tag_num[0];
    for(int i = 0; tag_num[1];i++){
        check_sim->enews2[i]=enews[1][i];
    }
    check_sim->enews2_no = tag_num[1];
    //~~
    check_similarity(check_sim);*/
}

//check similarity

double check_similarity(check_similarity_var * temp){
    int check1[temp->taglist_no], check2[temp->taglist_no];
    memcpy(check1,0,temp->taglist_no);
    for(int i = 0; i < temp->taglist_no;i++){
        for(int j =0 ; j<temp->enews1_no;j++){
            
        }
    }
}