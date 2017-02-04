//
//  main.c
//  how to read textdata
//
//  Created by AiYamamoto on 2017-02-02.
//  Copyright © 2017 CICCC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct accounts
{
    char* idNumber;
    char* password;
};

struct accounts* readFile(char* fileName);
int main(int argc, const char * argv[])
{
    char* fileName;
    fileName = "/Users/yamamotoai/Documents/C/Project1/how to read textdata/Accounts.txt";
    struct accounts* result = readFile(fileName);//takes only last one
    printf("\n");
    printf("result:%s\n",result->idNumber);
    printf("result:%s\n",result->password);
    return 0;
}
struct accounts* readFile(char* fileName)
{
    FILE *fp;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct accounts
{
    char* idNumber;
    char* password;
};

struct accounts* readFile(char* fileName);
//struct accounts student[10];
int main(int argc, const char * argv[])
{
    struct accounts* student;
    char* fileName;
    fileName = "/Users/yamamotoai/Documents/C/Project1/how to read textdata/Accounts.txt";
    student = readFile(fileName);//takes only last one
    printf("\n");
    for(int i=0; i < 10; i++)
    {
    printf("student[%d]:%s\n",i,student[i].idNumber);//<--error
    printf("student[%d]:%s\n",i,student[i].password);
    }
    return 0;
}
//There is a problem--result[0].idNumber and result[0].password are updated in somewhere
struct accounts* readFile(char* fileName)
{
    FILE *fp;
    char AccountInfo[256];
    struct accounts result[10];
    
    char id[256];
    char pw[256];
    char idFind[] = "studentID:";
    char pwFind[] = "Pass:";
    
    int strCountId = 0;
    int strCountPw = 0;

    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(AccountInfo,256,fp) != NULL)
    {
        printf("%s",AccountInfo);
        if (strstr(AccountInfo,idFind) != NULL )//Look for a StudentID
        {
            int i = 0,count=0;
            while(i == 0)
            {
                if(AccountInfo[count+13] == '\xe2')
                {
                    i=1;
                    count = 0;
                    printf("ID:%s\n",id);
                    result[strCountId].idNumber = id;
                    strCountId++;
                    break;
                }
                id[count] = AccountInfo[count+13];
                count++;
            }
        }
        if (strstr(AccountInfo,pwFind) != NULL )//Look for a Password
        {
            int i=0,count=0;
            while(i==0)
            {
                if(AccountInfo[count+8] == '\xe2')
                {
                    i=1;
                    count = 0;
                    printf("PW:%s\n",pw);
                    result[strCountPw].password = pw;
                    printf("result[%d].password:%s\n",strCountPw,result[strCountPw].password);
                    strCountPw++;
                    break;
                }
                pw[count] = AccountInfo[count+8];
                count++;
            }
        }
    }
    fclose(fp);
    
    return result;
}
