/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functionality.h
 * Author: Tommy
 *
 * Created on November 21, 2017, 1:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

//

#define true     1
#define false    0
typedef char word[30];

enum Category {SOCIETY, EDUCATION, SCIENCE, TECHNOLOGY, 
                 FAMILY, HEALTH, JOB, ENTERTAINMENT, OTHERS};
enum some_value {tag_no = 1000, enews_no =1000};
typedef struct _e_news {
    char ID[10];              // ten-digit string
    char pubDate[10];         // partern: dd/mm/yyyy
    char full_content[1000000];
    enum Category category;
    word tag_list[100];
    float appearance;				// store the proposition of appearance of keywords
} e_news;

//Huynguyen đưa thành extern để k bị lỗi multiple definion
extern e_news *E_news_arr; 			//store struct e_news read from file
extern size_t e_news_num;					//store number of e-news

//function
void gettaglist(char*,char **,int *  );
//(taglist(V),no of taglist(|V|),name of enewsfile, enews, no of tag list of enews)

void scan_dir(char*[][tag_no] ,int[],int *);
//(taglist(V),no of taglist(|V|), list of enews, no of enews)

void data_management();
//check similarity
typedef struct _check_similarity_var{
    char *taglist[tag_no];
    char *enews1[enews_no];
    char *enews2[enews_no];
    int enews1_no;
    int enews2_no;
    int taglist_no;

}check_similarity_var;
double check_similarity(check_similarity_var * );
#endif /* FUNCTIONALITY_H */
;
