#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <string.h>

typedef int BOOL;

#define TRUE 1
#define FALSE 0

BOOL simple_func(int in_num)
{
    return (in_num == 0) ? TRUE : FALSE;
}
typedef struct test_data {
    char name[128];
    int num;
    int val;
} TestData;
void ParseData()
{
    FILE* fp;
    int idx = 0;
    TestData td[3];
    memset(&td, 0x00, sizeof(TestData));
    fp = fopen("test_ddd.txt", "r");

    for (idx = 0; idx <3; idx++) {
        fscanf(fp, "%s\t%d\t%d", td[idx].name, &td[idx].num, &td[idx].val);
        printf("%s %d %d\n", td[idx].name, td[idx].num, td[idx].val);
    }
    fclose(fp);

/*
    char* token;
    char* token2;
    char strline[100];    // one line sentence
    while(fgets(strline, sizeof(strline), fp)) 
    {     
        // interfaces File 내에 특정 키워드 찾기
        if(strncmp(strline, word, strlen(word) ) == 0)
        {
            // address
            fgets(strline, sizeof(strline), fp);
            
            token = strtok(strline, " "); 
            token = strtok(NULL, " "); 
            token[strlen(token)-1] = '\0';    // gets 함수는 마지막에 \n이 들어가므로 이를 제거하기 위해 널값 삽입
            printf("%s\n", token);
*/
}

int main()
{
    if (TRUE == simple_func(0))
        printf("TEST \n");

    ParseData();
    return 0;
}
