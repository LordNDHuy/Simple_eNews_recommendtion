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
#include <math.h>
#include <regex.h>

#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

//// define section

#define true     1
#define false    0
#define PERCENTAGE 0.8
typedef char word[30];

enum Category {SOCIETY, EDUCATION, SCIENCE, TECHNOLOGY, 
                 FAMILY, HEALTH, JOB, ENTERTAINMENT, OTHERS};
enum some_value {tag_no = 1000, enews_no =1000};

typedef struct _e_news {
    char ID[10];              // ten-digit string
    char pubDate[10];         // partern: dd/mm/yyyy
    char full_content[10000];
    enum Category category;
    word *tag_list[100];
    int no;
    float appearance;				// store the proposition of appearance of keywords
} e_news;

typedef struct _taglist{
    word *list[100];
    int no;
} taglist;



////end define section


extern e_news *E_news_arr; 			//store struct e_news read from file
extern size_t e_news_num;					//store number of e-news

////function section
e_news get_news(char *);

int scan_dir(e_news *);

int data_management(e_news*,taglist*);
//check similarity

float *check_similarity(e_news *, taglist *,size_t,int);

void recommendation();

////end function section


#endif /* FUNCTIONALITY_H */
;
