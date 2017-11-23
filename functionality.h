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

typedef char word[30];
enum Category {SOCIETY, EDUCATION, SCIENCE, TECHNOLOGY, 
                 FAMILY, HEALTH, JOB, ENTERTAINMENT, OTHERS};
enum some_value {tag_no = 1000, enews_no =1000};
struct {
    char ID[10];              // ten-digit string
    char pubDate[10];         // partern: dd/mm/yyyy
    char full_content[1000000];
    enum Category category;
    word tag_list[100];
} e_news;

//function
void gettaglist(char*,char **,int *  );
//(taglist(V),no of taglist(|V|),name of enewsfile, enews, no of tag list of enews)

void scan_dir(char*** ,int*,int *);
//(taglist(V),no of taglist(|V|), list of enews, no of enews)

void data_management();
#endif /* FUNCTIONALITY_H */
;
