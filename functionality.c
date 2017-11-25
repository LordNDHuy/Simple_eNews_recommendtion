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
        //  cái khúc này này, tại vì á lúc mà lấy vào thì nó bị dính cái \n mà tao 
        // bị dính cái pointer trong pointer (tức là cái word trong đó là pointer trong cái pointer enews)
        // thành ra tao mới làm dài dòng vậy từng bức này

        // lấy độ dài chuỗi mới lấy
        int len = strlen(news->tag_list[news->no]);
        char temp[30];
        //sao chép hoàn toàn dữ liệu từ chuỗ i mới lấy sang mảng char temp[30]
        strncpy(temp,news->tag_list[news->no],len);
        //cái temp[len-1] == 10 là tại vị trí cuối cùng tức là \n ah 
        //nếu nó bằng 10 (10 trong ascii là \n) thì thay \n băng 0
        if (temp[len-1]==10) temp[len-1] = 0;
        else temp[len] =0;
        //sau đó copy ngược lại . done.
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
            //printf("%s",dir[dir_le]);
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
    e_news **enews_list =malloc(100*sizeof(e_news));
    taglist *list =malloc(100*sizeof(taglist));
    //init 
    for(int i = 0;i<100;i++){
        enews_list[i] = malloc(sizeof(e_news));
    }
    size_t enews_no = scan_dir(enews_list);
    int check = false; 
    for(int j=0;j<enews_no;j++){
        for(int i =0;i<enews_list[j]->no;i++){
            //printf("%s \n",enews_list[j]->tag_list[i]);
    }
    }
    
    for(int i = 0;i < enews_no;i++){
        for(int j =0; j < enews_list[i]->no;j++){
            list->list[list->no] = "\0";
            for(int k = 0; k < list->no;k++){
                if(compare_string(enews_list[i]->tag_list[j],list->list[k]) == true ) {
                    check = true;
                    break;
                }
            }
            if(check == false){
                list->list[list->no] = enews_list[i]->tag_list[j];
                //printf("%s \n", list->list[list->no]);
                list->no++;
            }else check = false;
        }
    }
    check_similarity(enews_list,list,enews_no);
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
    printf("sum =  %i  \n", sum);
    printf("len_a  %.4f   len_b %.4f\n",len_a,len_b);
    len_a = sqrtf(len_a);
    len_b = sqrtf(len_b);

    printf("len_a  %.4f   len_b %.4f\n",len_a,len_b);
    return sum/(len_a*len_b);
}

double check_similarity(e_news **enews_list,taglist *list,size_t enews_no){
    int *check0,*check1;
    check0 = malloc(list->no*sizeof(int));
    check1 = malloc(list->no*sizeof(int));
    memset(check0,false,list->no*sizeof(int));
    memset(check1,false,list->no*sizeof(int));
    // check matching of enews 0
    for(int k = 0;k<list->no;k++){
        for(int i = 0;i<enews_list[0]->no;i++){
            if(compare_string(list->list[k],enews_list[0]->tag_list[i])){
                check0[k]=true;
                //printf("%s        ",enews_list[0]->tag_list[i]);
            }
        }
    }
    //check matching of enews 1
    for(int k = 0;k<list->no;k++){
        for(int i = 0;i<enews_list[1]->no;i++){
            if(compare_string(list->list[k],enews_list[1]->tag_list[i])){
                check1[k]=1;
                //printf("%s        ",enews_list[0]->tag_list[i]);
            }
        }
    }

    ///
    float sim = cal_similarity(check0,check1,list->no);
    printf("%.4f\n",sim);
    for(int i=0;i<list->no;i++){
        printf("%-30s:  %i-5:%i\n",list->list[i],check0[i],check1[i]);
    }


    return 0;
}