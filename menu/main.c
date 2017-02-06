//
//  main.c
//  menu
//
//  Created by saekof on 2017-02-02.
//  Copyright © 2017 CICCC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int myStudentId;

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

struct accounts* accounts(char* data);
int showMenu(void);
void loginUser(void);
int judgeLoginUser(char* userName, char* password);
char** readFileData(FILE *fp, char* fileName);
struct student getMyStudentDataById(int studentId, char** data);
void printCertificate(struct student);

struct accounts* accounts(char* data)
{
    // get Data from accounts.txt file
    char* tp;
    struct accounts* tempStruct = NULL;
    tp = strtok( data, "studentID:");
    puts(tp);
    while ( tp != NULL ) {
        tempStruct = (struct accounts*)malloc(sizeof(struct accounts));
        tp = strtok( NULL, " " );
        if(strcmp(tp, "StudentID:")){;}
        else {
            puts( tp );
        }
    }
    return tempStruct;
    
}

int main(int argc, const char * argv[]) {
    
    loginUser();
    int menuNumber = showMenu();
    FILE* fp;
    char** studentData = readFileData(fp, "students.txt");
    struct student myself;
    myself = getMyStudentDataById(myStudentId, studentData);
    switch (menuNumber) {
        case 1:

            printCertificate(myself);
            break;
            
        default:
            break;
    }
    
    return 0;
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
        myStudentId = 7805666; // mystudentId
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

struct student getMyStudentDataById(int studentId, char **buf)
{
    // read the data from file
 //   FILE* fp;
 //   char* fileName = "student.txt";
 //   fp = fopen(fileName,"r");
 //   if(fp == NULL)
 //   {
 //       printf("The file doesn't exist.");
 //   }
 //   while
//    ch = getc(fp);  //1 char
 
    // find the data that related with me by student Id
    struct student myself;
    myself.address = "West Vancouver";
    myself.addmissionYear = 2011;
    myself.courses = "MADP101";// array に変える
    myself.numberOfCourses = 1; // array に変えて、カウント
    myself.firstName = "TARO";
    myself.gender = "Male";
    myself.grade = 1;
    myself.idNumber = studentId;
    myself.lastName = "YAMADA";
    
    return myself;
}

char** readFileData(FILE *inFile, char* fileName)
{
    int lenOfLine = 256; /* 行の長さ（文字列長） */
    int numOfLine = 30; /* 行の個数 */
    char ** buf;
    fileName = "/Users/saekof/Github/401-Project1/menu/menu/menu/Students.txt";
    inFile = fopen(fileName, "r");
    if(inFile == NULL)
    {
        printf("Can't read the file");
    }
    
    /* read the file by line */
    for (int i = 0; i < numOfLine; i ++ ) {
        if ( NULL == fgets( buf[ i ], lenOfLine, inFile ) ) {
            /* error */
            for ( i = 0; i < numOfLine; i ++ ) {
                free( buf[ i ] );
            }
            free( buf );
            fclose( inFile );
            puts( "*** illegal file status." );
            return 0;
        }
    }
    
    /* 資源解放：ファイルをクローズする */
    fclose( inFile );
    
    /* 表示してみる */
    for (int i = 0; i < numOfLine; i ++ ) {
        printf( "%s", buf[ i ] );
    }

    return buf;
}
void printCertificate(struct student myself)
{
    printf("Dear ");
    strcmp(myself.gender, "Male") == 0 ? puts("Sir,") : puts("Madam,");
    printf("\n");
    
    printf("This is to certify that " );
    strcmp(myself.gender, "Male") == 0 ? printf("Mr.") : printf("Ms.");
    printf("%s %s", myself.firstName, myself.lastName);
    
    printf(" with student id %d",myself.idNumber);
    printf(" is a student at grade %d at CICCC. ",myself.grade);
    
    strcmp(myself.gender, "Male") == 0 ? printf("He") : printf("She");
    printf(" was admitted to our college in %d ",myself.addmissionYear);
    
    printf("and has taken %d",myself.numberOfCourses);
    myself.numberOfCourses == 1 ? puts("course.") : puts("courses.");
    
    printf("Currently ");
    strcmp(myself.gender, "Male") == 0 ? printf("He") : printf("She");
    printf("resides at %s.",myself.address);
    printf("\n\n");
    printf("If you have any question, please don't hesitate to contact us.\n");
    printf("Thanks,\n");
    printf("William");
}
