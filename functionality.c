#include "functionality.h"
#include <math.h>

enum search_choice {SEARCH_CONTENT =0, SEARCH_TAG };

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
            //printf("%i", e_news_num[*e_num]);
        }

        if(compare_string(dir[dir_le] ,"..") == true) break;
        dir_le++;      
    }
    
    closedir(d);
    return length;
}

// enews and V management

void data_management(e_news* enews_list,taglist*list,int e_news_num){    
    int check = false; 
    for(int i = 0;i < e_news_num;i++){
        for(int j =0; j < enews_list[i].no;j++){
            list->list[list->no] = "\0";
            for(int k = 0; k < list->no;k++){
                if(compare_string(enews_list[i].tag_list[j],list->list[k]) == true ) {
                    check = true;
                    break;
                }
            }
            if(check == true){
                list->list[list->no] = enews_list[i].tag_list[j];
                //printf("%s \n", list->list[list->no]);
                list->no++;
            }else check = false;
        }
    }
}

//check similarity

//some subfunctions
    //calculate the similarity 
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
//sort int
int fcomp(float a,float b){
    float diff = a-b;

}
void fsort(float * arr,int * check,int e_news_num){
    int i =1;
    while(i < e_news_num){
        int j = i;
        while(j>0 & arr[j-1]<=arr[j]){
            float temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            int temp_count = check[j];
                check[j] = check[j-1];
                check[j-1] =temp_count;
            j--;
        }
        i++;
    }
}
//string separating function
taglist * str_sep(int search_choice){
    size_t len =0;
    char *sstr;
    printf("input search string :");
    getline(&sstr,&len,stdin);
    sstr[strlen(sstr)-1] ='\000';
    int i =0;
    taglist * list = malloc(10*sizeof(taglist));
    char * temp0 = sstr,*temp1;
    char temp[30];
    list->no =0;
    if(search_choice == SEARCH_CONTENT){
        strncpy(temp,sstr,30*sizeof(char));
        list->list[list->no] =malloc(30*sizeof(char));
        strcpy(list->list[list->no],temp);
        list->no++;
    }
    do{
        strtok_r(temp0," ",&temp1);
        list->list[list->no] = temp0;
        list->no++;
        //printf("%s%s\n",temp0,temp1);
        temp0=temp1;
    }while(*temp1 !=0);
    return list;
}

void print_debug(enews_return*list_re,int *check,int max_re){
    for(int j = 0; j< max_re;j++){
        for(int i = 0; i< list_re->list[j].no;i++){
            printf("%i%s\n",check[j],*list_re->list[j].tag_list[i]);
        }
    }
}
//
enews_return *check_similarity(taglist *list,int e0){
    int *check0,*check1;
    float *sim = malloc((e_news_num-1)*sizeof(float));
    int *check = malloc((e_news_num-1)*sizeof(int));
    for(int i = 0;i<e_news_num-1;i++){
        sim[i] = -1;
        check[0] =0;
    }

    check0 = malloc(list->no*sizeof(int));
    check1 = malloc(list->no*sizeof(int));
    for(int i=0;i<list->no;i++){
        check0[i]=false;
    } // check matching of enews 0

    for(int k = 0;k<list->no;k++){
        for(int i = 0;i<E_news_arr[e0].no;i++){
            if(compare_string(list->list[k],E_news_arr[e0].tag_list[i])){
                check0[k]=true;
                //printf("%s        ",E_news_arr[0]->tag_list[i]);
            }
        }
    }
        //check matching of (e_news_num -1) E_news.
    //print_debug(list_re,check,max_re);
        int c = 0;
    for(int j = 0;j< e_news_num;j++){
        if(j != e0){
        for(int i=0;i<list->no;i++){
            check1[i]=false;
        }  
                  //check matching of enews i
        for(int k = 0;k<list->no;k++){
                for(int i = 0;i<E_news_arr[j].no;i++){
                    if(compare_string(list->list[k],E_news_arr[j].tag_list[i])){
                        check1[k]=1;
                        //printf("%s        ",E_news_arr[0]->tag_list[i]);
                    }
                }
            }
            ///
            sim[c] = cal_similarity(check0,check1,list->no);
            check[c] = j;
            c++;
            //printf("%.4f\n",sim);
        } 
    }   
    check[e_news_num-1] = e0;
    // sort
    fsort(sim,check,e_news_num);
    int max_re = 0;
    for(int i=0;i<e_news_num;i++){
        //printf debug
        if(check[i]!=e0){
            printf("enews %i to %i  %0.5f\n",check[i],e0,sim[i]);            
            //printf("%-30s:  %-5i:%i\n",list->list[i],check0[i],check1[i]);
            if(sim[i]>PERCENTAGE) max_re++;
        }
    }
    printf("the number of enews match more thanf %0.3f %:%i\n",PERCENTAGE,max_re);
    enews_return *list_re = malloc(sizeof(enews_return));
    if(max_re >0){
        list_re->list= malloc(max_re*sizeof(e_news));
        list_re->no = max_re;

        for(int i =0;i<max_re;i++){
            list_re->list[i] = E_news_arr[check[i]];
        }
    }
    //printf debug
    //print_debug(list_re,check,max_re);
    
    return list_re;
}   

//search tag
enews_return *search_tag(){
    float * search_re = malloc(e_news_num*sizeof(float));
    int *check = malloc((e_news_num)*sizeof(int));
    for(int i = 0;i<e_news_num;i++){
        search_re[i]=0;
        check[i]=0;
    }

    taglist *list = str_sep(SEARCH_TAG);
    for(int i = 0;i<list->no;i++){
        //printf("%s \n",list->list[i]);
    }
    for(int k = 0;k<list->no;k++){
        for(int i = 0;i<e_news_num;i++){
            for(int j = 0;j<E_news_arr[i].no;j++){
                if(compare_string(list->list[k],E_news_arr[i].tag_list[j]) == true){
                    search_re[i]++;
                    //printf("%s\n",news[i].tag_list[j]);
                    break;
                }
            }
        }
    }
    for(int i = 0; i< e_news_num;i++){
        check[i] = i;
        search_re[i] = search_re[i] / list->no;
    }
    fsort(search_re,check,e_news_num);
    for(int i =0;i<e_news_num;i++){
        printf("in enews %i has %0.5f percent match\n",check[i],search_re[i]);
    }
    
    int max_re = 0;
    for(int i = 0;i<e_news_num;i++){
        if(search_re[i]>PERCENTAGE) max_re++;
    }
    printf("%i\n",max_re);    
    enews_return * list_re = malloc(sizeof(enews_return));
    list_re->no=0;
    if(max_re>0){
        list_re->list = malloc(max_re*sizeof(e_news));
        list_re->no = max_re;
        for(int i = 0;i<max_re;i++){
            list_re->list[i] = E_news_arr[check[i]];
        }
    }
    //print_debug(list_re,check,max_re);
    return list_re;
}


//search content
enews_return * search_content(){
    taglist * list = str_sep(SEARCH_CONTENT);
    float * search_re = malloc(e_news_num*sizeof(float));
    int *check = malloc((e_news_num)*sizeof(int));
    for(int i = 0;i<e_news_num;i++){
        search_re[i]=0;
    }
    for(int j =0;j<e_news_num;j++){
        for(int i =0;i<list->no;i++){
            e_news temp_news = E_news_arr[j];
            int k =0;
            while(temp_news.full_content[k]){
                if(temp_news.full_content[k] >= 65 && temp_news.full_content[k] <=90){
                    temp_news.full_content[k] +=32;
                }
                k++;
            }
            char * temp =strstr(temp_news.full_content,list->list[i]);
                if( temp!= NULL){
                    search_re[j]++;
                }
        }
    }

    int list_no = list->no;
    for(int i=0;i<e_news_num;i++){
        check[i] = i;
        //search_re[i] = search_re[i] / list_no;
    }
    fsort(search_re,check,e_news_num);
    int max_re=0;
    for(int i =0;i<e_news_num;i++){
        search_re[i] > PERCENTAGE ? max_re++:false;
    }
    enews_return *list_re = malloc(sizeof(enews_return));
    if(max_re > 0){
        list_re->list= malloc(max_re*sizeof(e_news));
        for(int i =0;i<max_re;i++){
            list_re->list[i] = E_news_arr[check[i]];
        }
    }
    list_re->no = max_re;
    //print_debug(list_re,check,max_re);
    for(int i =0;i<e_news_num;i++){
        printf("in enews %i has  %0.5f percent match\n",check[i],search_re[i]);
    }
        printf("%i\n",max_re);

    return list_re;
}
taglist* get_tag_list(){
    taglist *list =malloc(100*sizeof(taglist));
    int check = false; 
    list->no =0;
    //print_debug(list_re,check,max_re);

    for(int i = 0;i<e_news_num;i++){
        for(int j = 0; j<E_news_arr[i].no;j++){
            list->list[list->no] = " ";
            for(int k = 0;k <list->no;k++){
                if(compare_string(E_news_arr[i].tag_list[j],list->list[list->no]) == true){
                    check =true;
                    break;
                } else check = false;
            }
            if(check ==false){
                list->list[list->no] = E_news_arr[i].tag_list[j];
                //printf("%s\n",list->list[list->no]);
                list->no++;
            }
        }
        
    }

    return list;
}
void recommendation(){
    taglist *list =get_tag_list();
    if(e_news_num != 0){
        int e0 = 19;//e0 is the current enews 
        printf("        THIS IS THE SIMILAR RESULT\n\n");
        enews_return * similar = check_similarity(list,e0);

        printf("\n                  THIS IS CONTENT SEARCH\n\n");
        enews_return * search_cont = search_content();

        printf("\n                  THIS IS TAG SEARCH\n");
        enews_return * searchtag = search_tag();
    } else printf("no news loaded XD");
}
    