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

struct accounts
{
    int idNumber;
    char* password;
};

struct students
{
    int* idNumber;
    char* firstName;
    char* lastName;
    char* gender;
    char* grade;
    char* address;
    int addmissionYear;
    char* courses;
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


struct accounts* accounts(char* data)
{
    // get Data from accounts.txt file
   /* char* tp;
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
    */
}

int main(int argc, const char * argv[]) {
    
    loginUser();
    int number = showMenu();
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
        // message
        printf("************************************************************\n");
        printf("Welcome to Cornerstone International College of Canada.\n");
        printf("************************************************************\n");
        fflush(stdout);
        sleep(2);
    }
    else
    {
        // message
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
