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
    char* courseName;
};

void readFile(char* fileName);
char* substring(char* info);
void PrintMyCourse(struct student myself,struct courseDetail* course);
void ListAllCourses(struct courseDetail* course);
int showMenu(void);
struct student getMyStudentDataById(int studentId);
struct courseDetail* getCousesData(void);
void loginUser(void);
int judgeLoginUser(char* userName, char* password);

int main(int argc, const char * argv[])
{
    char* fileName1 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Accounts.txt";
    char* fileName2 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Courses.txt";
    char* fileName3 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Students.txt";
    char* fileName4 = "/Users/yamamotoai/Documents/C/Project1/textfiles/StudentsCourses.txt";
    
    readFile(fileName1);
    printf("\n*********************************************\n");
    readFile(fileName2);
    printf("\n*********************************************\n");
    readFile(fileName3);
    printf("\n*********************************************\n");
    readFile(fileName4);
    
    int studentID = 7813007;//for text
    loginUser();
    int menuNumber = showMenu();
    
    struct student myself = getMyStudentDataById(studentID);
    struct courseDetail* course = getCousesData();
    
    for(int i=0; i<3; i++)//for test
    {
        printf("corse[%d] = %s\n",i,course[i].courseId);
        printf("corse[%d] = %s\n",i,course[i].courseName);
    }
    
    switch (menuNumber) {
        case 2:
            PrintMyCourse(myself,course);
            break;
        case 6:
            ListAllCourses(course);
            break;
        case 8:
            loginUser();//It is strenge in 2nd time
            break;
        default:
            break;
    }
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
        if(studentInfo[0] != '\n')
        {
            result = substring(studentInfo);
            printf("result:%s\n",result);
        }
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
//(2)
void PrintMyCourse(struct student myself,struct courseDetail* course)
{
    printf("*********************************************\n");
    if(myself.gender == 'Male'){
        printf("Hi. Mr %s,\n",myself.firstName);
    }else{
        printf("Hi. Ms. %s,\n",myself.firstName);
    }
    printf("You have taken the following courses:\n");
    for(int i=0; i<10; i++)
    {
        if(myself.courses == course[i].courseId)
            printf("%d)%s : %s\n",i+1,myself.courses,course[i].courseName);
    }
    printf("*********************************************\n");
}
//(6)
void ListAllCourses(struct courseDetail* course)
{
    printf("*********************************************\n");
    printf("The following courses are offered in CICCC:\n");
    for(int i=0; i<3; i++)//need to change length --> the number of the courses
    {
        printf("%d)%s : %s\n",i+1,course[i].courseId,course[i].courseName);
    }
    printf("*********************************************\n");
}

int showMenu(void)
{
    printf("************************************************************\n");
    printf("Select from the options:\n");
    printf("************************************************************\n");
    printf("\n");
    printf("—-[1] Print myenrolment certificate\n");
    printf("—-[2] Print my courses\n");
    printf("—-[3] Print my transcript\n");
    printf("—-[4] Print my GPA\n");
    printf("—-[5] Print my ranking among all studentsin the college\n");
    printf("—-[6] List all available courses\n");
    printf("—-[7] List all students\n");
    printf("-—[8] Logout\n");
    printf("-—[9] Exit\n");
    printf("************************************************************\n");
    printf("\n");
    printf("Enter the number corresponding to each item to proceed:\n");
    
    char inputNumber[2];
    fgets(inputNumber, 2, stdin);
    int intNumber = atoi(inputNumber);
    
    if(intNumber<0 || 10 <= intNumber)
    {
        printf("You Entered wrong number\nbye\n");
    }
    
    return intNumber;
    
}

struct student getMyStudentDataById(int studentId)
{
    // read the data from file
    // find the data that related with me by student Id
    struct student myself;
    myself.address = "West Vancouver";
    myself.addmissionYear = 2011;
    myself.courses = "MADP101";// array に変える
    myself.numberOfCourses = 1; // array に変えて、カウント
    myself.firstName = "TARO";
    myself.gender = "Mal";
    myself.grade = 1;
    myself.idNumber = studentId;
    myself.lastName = "YAMADA";
    
    return myself;
}

struct courseDetail* getCousesData(void)//for test
{
    // read the data from file
    struct courseDetail* result;
    result = (struct courseDetail*)malloc(sizeof(struct courseDetail));
    if( result == NULL ) {
        printf( "memory cannot alloc!\n" );
    }
    result[0].courseId = "MADP101";
    result[0].courseName = "Objective-C";
    
    result[1].courseId = "MADP301";
    result[1].courseName = "Project Management";
    
    result[2].courseId = "MADP402";
    result[2].courseName = "Android Programming";
    
    free(result);//error
    return result;
}

void loginUser(void)
{
    printf("************************************************************\n");
    printf("Please enter your account to login:\n");
    printf("************************************************************\n");
    printf("Username:");
    
    char userName[256];
    char password[256];
    fgets(userName, 256, stdin);
    
    printf("Password:");
    fgets(password, 256, stdin);
    
    int loginResult = judgeLoginUser(userName, password);
    if (loginResult == EXIT_SUCCESS)
    {
        // success
        printf("************************************************************\n");
        printf("Welcome to Cornerstone International College of Canada.\n");
        printf("************************************************************\n");
        fflush(stdout);
        sleep(2);
//        myStudentId = 7805666; // 自分の学籍番号
    }
    else
    {
        // failure
        printf("************************************************************\n");
        printf("Your account does not exist. Please try again!\n");
        printf("************************************************************\n");
        fflush(stdout);
        sleep(2);
        loginUser();
    }
}

int judgeLoginUser(char* userName, char* password)
{
    int result;
    
    //if(userName == userName && password == password) //from file
    if(1)
    {
        result = EXIT_SUCCESS;
    }
    else
    {
        result = EXIT_FAILURE;
    }
    return result;
}
