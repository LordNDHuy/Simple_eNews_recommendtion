/*
 * CLI.c
 *
 *  Created on: Nov 22, 2017
 *      Author: Tommy
 */

#include "CLI.h"
#include "functionality.h"

//interface
void header(){
    printf("******************************************* \n");
    printf("*                                         * \n");
    printf("*    *****       **    * ***** **   **    * \n");
    printf("*    *           * *   * *     * * * *    * \n");
    printf("*    ***** ----  *  *  * ***** *  *  *    * \n");
    printf("*    *           *   * * *     *     *    * \n");
    printf("*    *****       *    ** ***** *     *    * \n");
    printf("*                                         * \n");
    printf("******************************************* \n");
}

//file manipulation
size_t e_news_num = 0;
struct e_news struct_dissolve(char *input){
	struct e_news temp;
								//hold position for line scanning
	short space = 0;

	unsigned short ID_position = 0;					//hold position for ID input
	unsigned short date_position = 0;
	size_t fullcontent_position = 0;
	unsigned short taglistWord_position = 0;
	size_t taglist = 0;

	for (size_t position = 0; input[position] != '\0'; position++){
		if (input[position] == ' ') {space++; continue;}

		switch (space){
		case 0: {									//ID scanning
			temp.ID[ID_position] = input[position];
			ID_position++; break;}
		case 1: {									// category scanning
			temp.category = input[position] - '0';
			break;}
		case 2:{									// day, month, year scanning
			temp.pubDate[date_position] = input[position];
			date_position++; break;}
		case 3:{									// full content scanning
			temp.full_content[fullcontent_position] = input[position];
			fullcontent_position++; break;}
		case 4:{									//taglist scanning
			if (input[position] == ';') {taglistWord_position = 0; taglist++; continue;}
			temp.tag_list[taglist][taglistWord_position] = input[position];
			taglistWord_position++; break;}
		}
	}
	return temp;
}

void FileReader_E_news(){
	FILE *file;
	char * line = NULL;
	size_t len = 0;
	size_t position = 0;

	file = fopen("./resources/text.txt", "r");
	if (file == NULL) {
		printf("File could not be found! ");
		exit(-1);
	}

	while (getline(&line, &len, file) != EOF) {
		if (e_news_num == 0) {
			e_news_num = atoi(line);
			E_news_arr = (struct e_news*) malloc (sizeof(struct e_news)*e_news_num);
			continue;
		}

		E_news_arr[position] = struct_dissolve(line);
		position++;
	}

	fclose(file);
}
