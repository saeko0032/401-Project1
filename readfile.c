//
//  main.c
//  substring
//
//  Created by AiYamamoto on 2017-02-03.
//  Copyright © 2017 CICCC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
struct accounts
{
    int idNumber;
    char* password;
};

struct student
{
    int idNumber;
    char* firstName;
    char* lastName;
    char* gender;
    int grade;
    char* address;
    int addmissionYear;
    char* courses;
    int numberOfCourses;
};

struct studentGrade
{
    int* idNumber;
    char* courseId;
    int mark;
};

struct courseDetail
{
    char* courseId;
    char* courseNama;
};
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void readFile(char* fileName);
char* substring(char* info);
int main(int argc, const char * argv[])
{
    char* fileName;

    fileName = "/Users/yamamotoai/Documents/C/Project1/textfiles/Accounts.txt";
//    fileName = "/Users/yamamotoai/Documents/C/Project1/textfiles/Courses.txt";
//    fileName = "/Users/yamamotoai/Documents/C/Project1/textfiles/Students.txt";
//    fileName = "/Users/yamamotoai/Documents/C/Project1/textfiles/StudentsCourses.txt";

    readFile(fileName);
    printf("\n");
    return 0;
}
void readFile(char* fileName)
{
    FILE *fp;
    char studentInfo[256];
    char* result;
    
    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp) != NULL)
    {
        printf("%s",studentInfo);
        result = substring(studentInfo);
        printf("result:%s\n",result);
        
    }
    fclose(fp);
}

//(e.g.)When you get "studentID:”7813007”\n" from Accounts.txt
char* substring(char* info)//info is "studentID:”7813007”\n"
{
    int counter1 = 0;
    int length1 = 0;
    int counter2 = 0;
    int length2 = 0;

//    int endIndex = lemgth
    while (counter1<1) {//get a string of length before ID starts
        if(info[length1]=='\x9d')//count till first '\x9d' to get the length
        {
            counter1++;
        }
        length1++;
    }
    while (counter2<2) {//get a string of length when ID is done
        if(info[length2]=='\xe2')//then count before 2nd '\xe2' to get the length
        {
            counter2++;
        }
        length2++;
    }
    

    int count = 0;
    char* result = (char*) malloc(length2 * sizeof(char));//allocates memory of length
    for(int i = length1; i < length2-1; i++)
    {
        result[count] = info[i];//copy 7813007 from "studentID:”7813007”\n"
        
        count++;
    }
    return result;//return 7813007
}
