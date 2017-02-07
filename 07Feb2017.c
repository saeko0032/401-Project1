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
#include <unistd.h>

struct accounts
{
    int idNumber;
    char* password;
};

struct student
{
    int idNumber;
    char* name;
    char* gender;
    int grade;
    char* address;
    int addmissionYear;
    char* courses;
    int numberOfCourses;
};

struct studentGrade
{
    int idNumber;
    char* courseId;
    int mark;
};

struct courseDetail
{
    char* courseId;
    char* courseName;
};

void ListAllCourses(struct courseDetail school);
void PrintMyCourse(struct student myself);
int showMenu(void);
char findChar(char* info);
struct accounts* readAccountsFile(char* fileName1);
struct student* readStudentFile(char* fileName2);
struct studentGrade* readStudentGradeFile(char* fileName3);
struct courseDetail* readCourseDetailFile(char* fileName4);
char* substring(char* info);

int main(int argc, const char * argv[])
{
    char* fileName1 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Accounts.txt";
    char* fileName2 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Students.txt";
    char* fileName3 = "/Users/yamamotoai/Documents/C/Project1/textfiles/StudentsCourses.txt";
    char* fileName4 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Courses.txt";

    struct accounts* accountsData = readAccountsFile(fileName1);
    printf("****************************************accountsData***\n");
    struct student* studentData = readStudentFile(fileName2);
    printf("****************************************studentData***\n");
    struct studentGrade* studentGradeData = readStudentGradeFile(fileName3);
    printf("****************************************studentGradeData***\n");
    struct courseDetail* courseDetailData = readCourseDetailFile(fileName4);
    printf("****************************************courseDetailData***\n");
    
    return 0;
}
////////////////////////////////////////////////////////////
//1accounts.txt
////////////////////////////////////////////////////////////
struct accounts* readAccountsFile(char* fileName1)
{
    FILE *fp;
    char studentInfo[256];
    char* resultSubstring;
    char firstChar;
    int count = 0;
    struct accounts* accountData = (struct accounts*)malloc(sizeof(struct accounts));
    
    if ((fp = fopen(fileName1, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp) != NULL)
    {
        printf("%s",studentInfo);
        firstChar = findChar(studentInfo);//s
        if(firstChar != '\n'){
            resultSubstring = substring(studentInfo);//7813007
            firstChar = findChar(studentInfo);//s
            if(firstChar == 's')
            {
                accountData[count].idNumber = atoi(resultSubstring);
            }
            else if(firstChar == 'P')
            {
                accountData[count].password = resultSubstring;
                count++;
            }
            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
        }
    }
    fclose(fp);
    return accountData;
}
////////////////////////////////////////////////////////////
//2student.txt
////////////////////////////////////////////////////////////
struct student* readStudentFile(char* fileName2)
{
    FILE *fp;
    char studentInfo[256];
    char* resultSubstring;
    char firstChar;
    int count = 0;
    struct student* studentData = (struct student*)malloc(sizeof(struct student));
    
    if ((fp = fopen(fileName2, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp))
    {
        printf("%s",studentInfo);
        firstChar = findChar(studentInfo);//s
        if(firstChar != '\n'){
            resultSubstring = substring(studentInfo);//7813007
            firstChar = findChar(studentInfo);//s
            if(firstChar == '1')
            {
                studentData[count].idNumber = atoi(resultSubstring);
            }
            else if(firstChar == '2')
            {
                studentData[count].name = resultSubstring;
            }
            else if (firstChar == '3')
            {
                studentData[count].gender = resultSubstring;
            }
            else if (firstChar == '4')
            {
                studentData[count].grade = atoi(resultSubstring);
            }
            else if (firstChar == '5')
            {
                studentData[count].address = resultSubstring;
            }
            else if (firstChar == '6')
            {
                studentData[count].addmissionYear = atoi(resultSubstring);
            }
            else if (firstChar == '7')
            {
                studentData[count].courses = resultSubstring;
            }
            else//I need to change here
            {
                studentData[count].numberOfCourses = 3;
                count++;
            }
            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
        }
    }
    fclose(fp);
    return studentData;
}
//////////////////////////////////////////////////////////////
////3studentGrade.txt
//////////////////////////////////////////////////////////////
struct studentGrade* readStudentGradeFile(char* fileName3)
{
    FILE *fp;
    char studentInfo[256];
    char* resultSubstring;
    char firstChar;
    int count = 0;
    struct studentGrade* studentGradeData = (struct studentGrade*)malloc(sizeof(struct studentGrade));
    
    if ((fp = fopen(fileName3, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp))
    {
        printf("%s",studentInfo);
        firstChar = findChar(studentInfo);//s
        if(firstChar != '\n'){
            resultSubstring = substring(studentInfo);//7813007
            if(firstChar == 's')
            {
                studentGradeData[count].idNumber = atoi(resultSubstring);
            }
            else if(firstChar == 'c')
            {
                studentGradeData[count].courseId = resultSubstring;
            }
            else if(firstChar == 'm')
            {
                studentGradeData[count].mark = atoi(resultSubstring);
                count++;
            }
            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
        }
    }
    fclose(fp);
    return studentGradeData;
}

//////////////////////////////////////////////////////////////
////4courseDetail.txt
//////////////////////////////////////////////////////////////
struct courseDetail* readCourseDetailFile(char* fileName4)
{
    FILE *fp;
    char studentInfo[256];
    char* resultSubstring;
    char firstChar;
    int count = 0;
    struct courseDetail* courseDetailData = (struct courseDetail*)malloc(sizeof(struct courseDetail));
    
    if ((fp = fopen(fileName4, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp))
    {
        printf("%s",studentInfo);
        firstChar = findChar(studentInfo);//s
        if(firstChar != '\n'){
            resultSubstring = substring(studentInfo);//7813007
            if(firstChar == 'c')
            {
                courseDetailData[count].courseId = resultSubstring;
            }
            else if(firstChar == 'n')
            {
                courseDetailData[count].courseName = resultSubstring;
                count++;
            }
            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
        }
    }
    fclose(fp);
    return courseDetailData;
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//(e.g.)When you get "studentID:”7813007”\n" from Accounts.txt
char* substring(char* info)//info is "studentID:”7813007”\n"
{
    int counter1 = 0;
    int length1 = 0;
    int counter2 = 0;
    int length2 = 0;

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
    char* result = (char*) malloc(length2 * sizeof(char)*2);//allocates memory of length
    for(int i = length1; i < length2-1; i++)
    {
        result[count] = info[i];//copy 7813007 from "studentID:”7813007”\n"
        
        count++;
    }
//    free(result);
    return result;//return 7813007
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
char findChar(char* info)
{
    return *info;
}

