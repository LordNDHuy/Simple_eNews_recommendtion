#include "functionality.h"
#include <math.h>
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

e_news get_news(char *f){
   
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
    char *get_row;
    e_news news ;
    news.no = 0;
    while ((read = getline(&get_row, &len, file)) != -1){
        int len = strlen(get_row);
        if(get_row[len-1]==10) get_row[len-1]= 0;
        news.tag_list[news.no] = get_row;
        news.no +=1; 
        get_row =0;       
    }
    fclose(file);
    return news;
}

int scan_dir(e_news *elist){
    
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
        if (!(compare_string(dir[dir_le] , ".") == true || compare_string(dir[dir_le] ,"..") == true)){            
            //printf("%s",dir[dir_le]);  
            elist[length] = get_news(dir[dir_le]);
            length++;
            //printf("%s",dir[dir_le]);
            //printf("%i", enews_no[*e_num]);
        }

        if(compare_string(dir[dir_le] ,"..") == true) break;
        dir_le++;      
    }
    
    closedir(d);
    return length;
}

// enews and V management

int data_management(e_news* enews_list,taglist*list){    
    size_t enews_no = scan_dir(enews_list);
    int check = false; 
    for(int j=0;j<enews_no;j++){
        for(int i =0;i<enews_list[j].no;i++){
            //printf("%s \n",enews_list[j].tag_list[i]);
        }
    }
    
    for(int i = 0;i < enews_no;i++){
        for(int j =0; j < enews_list[i].no;j++){
            list->list[list->no] = "\0";
            for(int k = 0; k < list->no;k++){
                if(compare_string(enews_list[i].tag_list[j],list->list[k]) == true ) {
                    check = true;
                    break;
                }
            }
            if(check == false){
                list->list[list->no] = enews_list[i].tag_list[j];
                //printf("%s \n", list->list[list->no]);
                list->no++;
            }else check = false;
        }
    }
    return enews_no;
}

//check similarity

// sub func for check simi

float cal_similarity(int*a,int*b,int dim){
    float len_a = 0 ,len_b = 0;
    int sum=0;    
    for(int i =0;i<dim;i++){
        sum += a[i]*b[i]; // scalar pro
        len_a += a[i]*a[i];//it is 1 though.~~
        len_b += b[i]*b[i];// same here~~
    }
    len_a = sqrtf(len_a);
    len_b = sqrtf(len_b);
    return sum/(len_a*len_b);
}

float check_similarity(e_news *enews_list,taglist *list,size_t enews_no,int e0,int e1){
    int *check0,*check1;
    check0 = malloc(list->no*sizeof(int));
    check1 = malloc(list->no*sizeof(int));
    memset(check0,false,list->no*sizeof(int));
    memset(check1,false,list->no*sizeof(int));
    // check matching of enews 0
    for(int k = 0;k<list->no;k++){
        for(int i = 0;i<enews_list[e0].no;i++){
            if(compare_string(list->list[k],enews_list[e0].tag_list[i])){
                check0[k]=true;
                //printf("%s        ",enews_list[0]->tag_list[i]);
            }
        }
    }
    //check matching of enews 1
    for(int k = 0;k<list->no;k++){
        for(int i = 0;i<enews_list[e1].no;i++){
            if(compare_string(list->list[k],enews_list[e1].tag_list[i])){
                check1[k]=1;
                //printf("%s        ",enews_list[0]->tag_list[i]);
            }
        }
    }

    ///
    float sim = cal_similarity(check0,check1,list->no);
    //printf("%.4f\n",sim);
    for(int i=0;i<list->no;i++){
        //printf("%-30s:  %-5i:%i\n",list->list[i],check0[i],check1[i]);
    }


    return sim;
}

void recommendation(){
    e_news *enews_list =malloc(100*sizeof(e_news));
    taglist *list =malloc(100*sizeof(taglist));
    int enews_no = data_management(enews_list,list);
    int e0 =0;
    for(int i = 0;i< enews_no;i++){
        if(i != e0){
            float sim = check_similarity(enews_list,list,enews_no,e0,i);
            printf("%i to %i  %0.4f\n",i,e0,sim);
        }
    }

}