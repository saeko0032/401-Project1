//
//  main.c
//  substring
//
//  Created by AiYamamoto on 2017-02-03.
//  Copyright © 2017 CICCC. All rights reserved.
//
//memory malloc error!!!!!!!!!!!!!!!!!!!!!!!!
//I want to change to not array[10]!!!!!!!!!!
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
    char** courses;//array of array
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

void PrintMyCourse(struct student* myself,struct courseDetail* course);
void ListAllCourses(struct courseDetail* course);
char* substringSub(char* line, int startIndex, int endIndex);
char** splitString(char* a_str, const char a_delim, int* numberOfComponents);
int strLength(char* line);
void loginUser(void);
int judgeLoginUser(int userName, char* password);
int showMenu(void);
char findChar(char* info);
struct accounts* readAccountsFile(char* fileName1);
struct student* readStudentFile(char* fileName2);
struct studentGrade* readStudentGradeFile(char* fileName3);
struct courseDetail* readCourseDetailFile(char* fileName4);
char* substring(char* info);
struct student getMyStudentDataById(struct student* studentData);

void GPA(struct studentGrade* studentGradeData,struct student* studentData);

int numStudentGradeData;
int myStudentId;
int main(int argc, const char * argv[])
{
//    char* fileName1 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Accounts.txt";
//    char* fileName2 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Students.txt";
//    char* fileName3 = "/Users/yamamotoai/Documents/C/Project1/textfiles/StudentsCourses.txt";
//    char* fileName4 = "/Users/yamamotoai/Documents/C/Project1/textfiles/Courses.txt";

    char* fileName1 = "/Users/yamamotoai/Documents/C/Project1/Alisample/Alisample/Accounts.txt";
    char* fileName2 = "/Users/yamamotoai/Documents/C/Project1/Alisample/Alisample/Students.txt";
    char* fileName3 = "/Users/yamamotoai/Documents/C/Project1/Alisample/Alisample/StudentsCourses.txt";
    char* fileName4 = "/Users/yamamotoai/Documents/C/Project1/Alisample/Alisample/Courses.txt";
    
    
    struct accounts* accountsData = readAccountsFile(fileName1);
    printf("****************************************read accountsData***\n");
    struct student* studentData = readStudentFile(fileName2);
    printf("****************************************readstudentData***\n");
    struct studentGrade* studentGradeData = readStudentGradeFile(fileName3);
    printf("****************************************read studentGradeData***\n");
    struct courseDetail* courseDetailData = readCourseDetailFile(fileName4);
    printf("****************************************read courseDetailData***\n");
    loginUser();
    struct student myself = getMyStudentDataById(studentData);
    
    int intNumber = showMenu();
    switch (intNumber) {
        case 1:
            loginUser();
            break;
        case 2:
            PrintMyCourse(&myself,courseDetailData);
            break;
        case 3:
            loginUser();
            break;
        case 4:
            GPA(studentGradeData,&myself);
            break;
        case 5:
            loginUser();
            break;
        case 6:
            ListAllCourses(courseDetailData);
        case 7:
            loginUser();
            break;
        case 8:
            loginUser();//It is strenge in 2nd time
            break;
            
        default:
            break;
    }
    printf("FIN\n");
    free(accountsData);
    free(studentData);
//    free(studentGradeData);
//    free(courseDetailData);
    
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
    //struct accounts* accountData = (struct accounts*)malloc(sizeof(struct accounts));
    
    //***add
    struct accounts* accountData[10];
    
    if ((fp = fopen(fileName1, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp) != NULL)
    {
//        printf("%s",studentInfo);
        firstChar = findChar(studentInfo);//s
        if(firstChar != '\n'){
            resultSubstring = substring(studentInfo);//7813007
            firstChar = findChar(studentInfo);//s
            if(firstChar == '1')
            {
                //***add
                accountData[count] = (struct accounts*)malloc(sizeof(struct accounts));
                accountData[count]->idNumber = atoi(resultSubstring);
            }
            else if(firstChar == '2')
            {
                accountData[count]->password = resultSubstring;
                count++;
            }
//            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
        }
    }
    fclose(fp);
    return *accountData;
}
////////////////////////////////////////////////////////////
//2student.txt
////////////////////////////////////////////////////////////I can't get data sometimes
struct student* readStudentFile(char* fileName2)
{
    FILE *fp;
    char studentInfo[256];
//    char* resultSubstring;
    char firstChar;
    int count = 0;
    
    char** courses= NULL;
    
    //struct student* studentData = (struct student*)malloc(sizeof(struct student));
    struct student* studentData[10];
    
    if ((fp = fopen(fileName2, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp))
    {
//        printf("%s",studentInfo);
        firstChar = findChar(studentInfo);//s
        if(firstChar != '\n'){
            if(firstChar == '1')
            {
                studentData[count] = (struct student*)malloc(sizeof(struct student));
                studentData[count]->idNumber = atoi(substring(studentInfo));
            }
            else if(firstChar == '2')
            {
                studentData[count]->name = substring(studentInfo);
            }
            else if (firstChar == '3')
            {
                studentData[count]->gender = substring(studentInfo);
            }
            else if (firstChar == '4')
            {
                studentData[count]->grade = atoi(substring(studentInfo));
            }
            else if (firstChar == '5')
            {
                studentData[count]->address = substring(studentInfo);
            }
            else if (firstChar == '6')
            {
                studentData[count]->addmissionYear = atoi(substring(studentInfo));
            }
            else if (firstChar == '7')
            {
                int numberOfComponents = 0;
                int lineLength = strLength(studentInfo);
                char* coursesStr = substringSub(studentInfo, 10, lineLength-2);
                courses = splitString(coursesStr, ',', &numberOfComponents);
                
                studentData[count]->numberOfCourses = numberOfComponents;
                studentData[count]->courses = courses;
                count++;
            }
//            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
        }
    }
    fclose(fp);
    
    return *studentData;
}
char* substringSub(char* line, int startIndex, int endIndex)
{
    int len = (endIndex-startIndex)+1;
    
    char* substring;
    
    //substring = (char*) malloc((len+1)*sizeof(char));
    
    substring = (char*) malloc((len+1)*sizeof(char));
    
    for(int i=0; i<=len; i++)
    {
        substring[i] = '\0';
    }
    
    for(int i=0; i<len; i++)
    {
        substring[i] = *(line+startIndex+i);
        
        substring[i] = line[startIndex+i];
        //*(substring+i) = *(line+startIndex+i);
    }
    
    substring[len+1] = '\0';
    return substring;
    
}

int strLength(char* line)
{
    
    char c = '\n';
    int index = 0;
    
    int numberOfDoubleQuotes = 0;
    
    while(numberOfDoubleQuotes<2)
    {
        
        c = *(line+index);
        index++;
        
        if(c == '"')
        {
            numberOfDoubleQuotes++;
        }
    }
    
    return index;
}

char** splitString(char* a_str, const char a_delim, int* numberOfComponents)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    
    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);
    
    *numberOfComponents = (int)count;
    
    /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
    count++;
    
    result = malloc(sizeof(char*) * count);
    
    char* components[count];
    for(int i=0; i<count; i++)
    {
        components[i] = '\0';
    }
    
    int counter = 0;
    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        
        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
            
            counter++;
            
            components[counter] = token;
        }
        *(result + idx) = 0;
    }
    
    return result;
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
    int numData = 0;
    struct studentGrade studentGradeData[10];
    
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
            numData++;
            resultSubstring = substring(studentInfo);//7813007
            if(firstChar == '1')
            {
                
//                studentGradeData[count] = (struct studentGrade*)malloc(sizeof(struct studentGrade));
                studentGradeData[count].idNumber = atoi(resultSubstring);
            }
            
            else if(firstChar == '2')
            {
                studentGradeData[count].courseId = resultSubstring;
            }
            else if(firstChar == '3')
            {
                studentGradeData[count].mark = atoi(resultSubstring);
                count++;
            }
            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
            numStudentGradeData = count;
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
//    struct courseDetail* courseDetailData = (struct courseDetail*)malloc(sizeof(struct courseDetail));
    struct courseDetail* courseDetailData[10];
    if ((fp = fopen(fileName4, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(studentInfo,256,fp))
    {
//        printf("%s",studentInfo);
        firstChar = findChar(studentInfo);//s
        if(firstChar != '\n'){
            resultSubstring = substring(studentInfo);//7813007
            if(firstChar == '1')
            {
                courseDetailData[count] = (struct courseDetail*)malloc(sizeof(struct courseDetail));
                courseDetailData[count]->courseId = resultSubstring;
            }
            else if(firstChar == '2')
            {
                courseDetailData[count]->courseName = resultSubstring;
                count++;
            }
            printf("result:%s firstChar:%c\n",resultSubstring, firstChar);
        }
    }
    fclose(fp);
    return courseDetailData;
}
////////////////////////////////////////////////////////////
//login
////////////////////////////////////////////////////////////
void loginUser(void)
{
    printf("************************************************************\n");
    printf("Please enter your account to login:\n");
    printf("************************************************************\n");
    printf("Username:");
    
    int userName;
    char password[256];
    scanf("%d",&userName);
//    fgets(userName, 256, stdin);
    
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
        myStudentId = userName; // mystudentId
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

int judgeLoginUser(int userName, char* password)
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
        if(info[length1]=='"')//count till first '\x9d' to get the length
        {
            counter1++;
        }
        length1++;
    }
    while (counter2<2) {//get a string of length when ID is done
        if(info[length2]=='"')//then count before 2nd '\xe2' to get the length
        {
            counter2++;
        }
        length2++;
    }

    int count = 0;
    char* result = (char*) malloc(length2 * sizeof(char));//allocates memory of length//error
    for(int i = length1; i < length2-1; i++)
    {
        result[count] = info[i];//copy 7813007 from "studentID:”7813007”\n"
        count++;
    }

    return result;//return 7813007
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
char findChar(char* info)
{
    return *info;
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
struct student getMyStudentDataById(struct student* studentData)
{
    struct student myself;
    int k = 0;
    int count = 0;
    
    while(k == 0)
    {
        if(myStudentId == studentData[count].idNumber)
        {
            /*
            myself.idNumber = studentData[count].idNumber;
            myself.name = studentData[count].name;
            myself.gender = studentData[count].gender;
            myself.grade = studentData[count].grade;
            myself.address = studentData[count].address;
            myself.addmissionYear = studentData[count].addmissionYear;
            myself.idNumber = studentData[count].idNumber;
            myself.courses = studentData[count].courses;
            myself.numberOfCourses = studentData[count].numberOfCourses;
            k = 1;
            break;
             */
            return studentData[count];
        }
        count++;
    }
    return myself;
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
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void GPA(struct studentGrade* studentGradeData,struct student* myself)
{
    int Mark = 0;
    int count = 0;
    float GPA = 0;
    
    for(int i = 0; i < numStudentGradeData; i++){
        if(myself->idNumber == studentGradeData[i].idNumber)
        {
            Mark = Mark + studentGradeData[i].mark;
            count++;
        }
    }
    GPA = Mark / count;
    
    printf("*********************************************\n");
    //        if(myself->gender == 'm'){//condition is wrong
    printf("Hi. Mr %s,\n",myself->name);
    //        }else{
    //            printf("Hi. Ms. %s,\n",myself->name);
    //        }
    printf("Your GPA is %0.2f\n",GPA);
    printf("*********************************************\n");
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void PrintMyCourse(struct student* myself,struct courseDetail* course)
{
    printf("*********************************************\n");
    if(myself->gender == 'Male'){
        printf("Hi. Mr %s,\n",myself->name);
    }else{
        printf("Hi. Ms. %s,\n",myself->name);
    }
    printf("You have taken the following courses:\n");
    for(int i=0; i<10; i++)
    {
        for(int j=i; j<10; j++)
        {
            if(myself->courses[i] == course[j].courseId)
            printf("%d)%s : %s\n",i+1,myself->courses[i],course[j].courseName);
    }
    printf("*********************************************\n");
    }
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void ListAllCourses(struct courseDetail* course)
{
    printf("*********************************************\n");
    for(int i=0; i<3; i++)//need to change length --> the number of the courses
    {
        printf("%d)%s : %s\n",i+1,course[i].courseId,course[i].courseName);
    }
    printf("*********************************************\n");
}
