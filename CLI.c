/*
 * CLI.c
 *
 *  Created on: Nov 22, 2017
 *      Author: Tommy
 */

#include "CLI.h"
#include "functionality.h"


//queries definition
struct query{
	word list[20];
	unsigned short quantity;
};
extern struct query queries_arr[20];
extern unsigned short queries_num;

//***************************************************************************************file manipulation

//******************************************************************************e_news

size_t e_news_num;
struct _e_news *E_news_arr;

struct _e_news struct_dissolve(char *input){
	struct _e_news temp;
	for (int i = 0; i < 100; i++){
		temp.tag_list[i] = (word*)malloc(sizeof(word));
	}


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
			ID_position++;
			if (ID_position == 10) temp.ID[ID_position] = '\0';
			break;}
		case 1: {									// category scanning
			temp.category = input[position] - '0';
			break;}
		case 2:{									// day, month, year scanning
			temp.pubDate[date_position] = input[position];
			date_position++;
			if (date_position == 10) temp.ID[date_position] = '\0';
			break;}
		case 3:{									// full content scanning
			temp.full_content[fullcontent_position] = input[position];
			fullcontent_position++; break;}
		case 4:{									//taglist scanning
			if (input[position] == ';') {
				taglistWord_position = 0;
				taglist++;
				continue; }
			(*temp.tag_list[taglist])[taglistWord_position] = input[position];
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
	char * dir = "./e_news.txt";
	file = fopen(dir, "r");
	if (file == NULL) {
		printf("File could not be found! ");
		exit(-1);
	}

	while (getline(&line, &len, file) != EOF) {
		E_news_arr[position] = struct_dissolve(line);
		position++;
	}

	fclose(file);
}

//******************************************************************************queries
struct query queries_arr[20];
unsigned short queries_num = 0;

void queries_dissolve(unsigned short position, char *input){
	queries_num++;
	unsigned short wOrd = 0;
	for (size_t i = 0; input[i] != '\0'; i++){
		if (input[i] == ';') {wOrd = 0; queries_arr[position].quantity++; continue;}
		queries_arr[position].list[queries_arr[position].quantity][wOrd] = input[i];
		wOrd++;
	}
}
void FileReader_queries(){
	FILE *file;
	char * line = NULL;
	size_t len = 0;

	file = fopen("./resources/queries.txt", "r");
	if (file == NULL) {
		printf("File could not be found! ");
		exit(-1);
	}

	while (getline(&line, &len, file) != EOF) {
		queries_dissolve(queries_num, line);
		queries_num++;
	}

	fclose(file);
}

//***************************************************************************************interface
void taglist_inputDissolve(unsigned int posArr,char *input){				//dissolve tagline input line
	unsigned short taglistWord_position = 0;
	size_t taglist = 0;
	for (size_t i = 0; input[i] != '\0'; i++){
		if (input[i] == ';') {taglistWord_position = 0; taglist++; continue;}
		(*E_news_arr[posArr].tag_list[taglist])[taglistWord_position] = input[i];
		taglistWord_position++;
	}
}
void ClearScreen(){
	system("clear");
}
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
void keyboardInput_E_news(){
	ClearScreen();
	header();

	int selMain = -1;
	printf("1.   Create new e-news \n");
	printf("2.   Exit \n");
	while ((selMain != 1)&&(selMain != 2)) 	{printf("Your selection: "); scanf("%d", &selMain);}

	if (selMain == 2) return;

	//begin creating new e-news
	char tmpString[512] = "";
	while (strlen(tmpString) != 10) {printf("1. ID (10 digits): "); scanf("%s", tmpString);}
	strcpy(E_news_arr[e_news_num].ID, tmpString);



	strcpy(tmpString, "");
	while (strlen(tmpString) != 10) {printf("2. Date (dd//mm/yyyy): "); scanf("%s", tmpString);}
	strcpy(E_news_arr[e_news_num].pubDate, tmpString);

	strcpy(tmpString, "");
	printf("3. Full content: "); scanf("%s", tmpString);
	strcpy(E_news_arr[e_news_num].full_content, tmpString);

	unsigned int in;
	printf("4. Category: "); scanf("%ud", &in);
	E_news_arr[e_news_num].category = in;

	strcpy(tmpString, "");
	printf("5. Taglist (type in a line; words separated by semicolon): "); scanf("%s", tmpString);
	taglist_inputDissolve(e_news_num,tmpString);


	e_news_num++;
	printf("Press any number to continue.");
	int x; scanf("%d", &x);

}
void keyboardInput_queries(){
	ClearScreen();
	header();

	char input[2048];
	int selectionMain = -1;
	printf("* Choose the destination you want to search: \n");
	printf("1. Search in TAGLIST \n");
	printf("2. Search in FULL CONTENT \n");
	while ((selectionMain != 1)&&(selectionMain != 2)) {
		printf("Please choose one: "); scanf("%d", &selectionMain);
	}

	if (selectionMain == 1){				//search in TAGLIST and show

	}
	else {								   //search in FULL CONTENT and show

	}

	printf("Press any number to continue.");
	int x; scanf("%d", &x);
}

void interface(){
	E_news_arr = (struct e_news *)malloc(sizeof(struct _e_news) * 100);
	e_news_num = 20;
	//constructor
	FileReader_E_news();
	FileReader_queries();

	return;
	ClearScreen();
	header();
	keyboardInput_E_news();

}
