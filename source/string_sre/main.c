#include <stdio.h>
#include <string.h>
int main()
{
    printf("Hello World!");
    char input[100];
    size_t size;
    getline(&input,&size,stdin);
    printf("this is %s\n",*input);
    return 0;
}
