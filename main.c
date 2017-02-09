#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define CoursesFile "Courses.txt"
#define AccountsFile "Accounts.txt"
#define StudentsFile "Students.txt"
#define StudentsCoursesFile "StudentsCourses.txt"

#define AiFolderPath "/Users/yamamotoai/Documents/C/Project1/Alisample/Alisample/"
#define SaekoFolderPath "/Users/saekof/Github/401-Project1/textfiles/"

struct Account
{
    char* studentID;
    char* password;
};

struct Student {
    
    char* studentID;
    char* name;
    char* gender;
    int grade;
    char* address;
    int admission_year;
    char** courses;
    int numberOfCourses;
};

struct Course
{
    char* courseID;
    char* name;
};

struct StudentsCourse
{
    char* studentID;
    char* courseID;
    int mark;
};

//Global Variables
struct Student* listOfStudents;
struct Account* listOfAccounts;
struct Course* listOfCourses;
struct StudentsCourse* listOfStudentCourses;
static char* myStudentID;

char firstChar(char* line);
int strLength(char* line);
char* substring(char* line, int startIndex, int endIndex);
int getTheStartIndex(char* filename, char firstChar);
char** splitString(char* a_str, const char a_delim, int* numberOfComponents);

char** readFile(char* fileAddress, int* numberOfLines);
int numberOfItemsPerRecordInFile(char* fileName);

int convertToNumber(char *);

void loginUser(void);
int judgeLoginUser(char* userName, char* password);
int showMenu(void);

void printCertificate(struct Student); // menu 1
void printTranscript(struct Student); // menu 3
void printMyRanking(struct Student); // menu 5
void listAllStudents(void); // menu 7
//add
void ListAllCourses(struct Course* listOfCourses,int numberOfCourses);//6
void PrintMyCourse(struct Student myself,struct Course* listOfCourses,int numberOfCourses);//2
void GPA(struct Student myself);//4
void logoutUser(struct Student myself);

struct Student createAStudent(char* studentID, char* name, char* gender, int grade, char* address, int admission_year, char* courses[], int numberOfCourses);
struct Student* getListOfStudentFromFile(char* fileAddress, char* fileName, int* numberOfStudents);
struct Student getMyStudentDataByID(char* studentID);

struct Account createAnAccount(char* studentID, char*password);
struct Account* getListofAccountFromFile(char* fileAddress, char* fileName, int* numberOfAccounts);

struct Course createACourse(char* courseID, char* name);
struct Course* getListOfCourseNameFromFile(char* fileAddress, char* fileName, int* numberOfCourses);

struct StudentsCourse createAStudentCourse(char* studentID, char* courseID, int mark);
struct StudentsCourse* getListOfStudentCourseFromFile(char* fileAddress, char* fileName, int* numberOfCourses);

float getMyGPA(struct Student myself);


int main(int argc, const char * argv[]) {
    int numberOfCourses=0;
    char* CoursesFileName = CoursesFile;
    char* coursesfileAddress = "/Users/saekof/Github/401-Project1/textfiles/Courses.txt";
    
    loginUser();
    struct Student myself = getMyStudentDataByID(myStudentID);
    listOfCourses = getListOfCourseNameFromFile(coursesfileAddress, CoursesFileName, &numberOfCourses);
    
    int exit = 0;
    while(exit == 0){
        int menuNumber = showMenu();
        switch (menuNumber) {
            case 1:
                printCertificate(myself);
                break;
            case 2:
                PrintMyCourse(myself,listOfCourses,numberOfCourses);
                break;
            case 3:
                printTranscript(myself);
                break;
            case 4:
                GPA(myself);
                break;
            case 5:
                printMyRanking(myself);
                break;
            case 6:
                ListAllCourses(listOfCourses,numberOfCourses);
                break;
            case 7:
                listAllStudents();
                break;
            case 8:
                logoutUser(myself);
                break;
            case 9:
                return 0;
        }
    }
    return 0;
}

void loginUser(void)
{
    char userName[256] = {0};
    char password[256] = {0};
    
    printf("************************************************************\n");
    printf("Please enter your account to login:\n");
    printf("************************************************************\n");
    printf("Username:");
    
    fgets(userName, 256, stdin);// after logout auto into userName \n
    if(userName[0] == '\n')
    {
        fgets(userName, 256, stdin);
    }
    userName[strlen(userName) - 1] = '\0';
    
    printf("Password:");
    fgets(password, 256, stdin);
    password[strlen(password) - 1] = '\0';
    
    int loginResult = judgeLoginUser(userName, password);
    if (loginResult == EXIT_SUCCESS)
    {
        // success
        printf("************************************************************\n");
        printf("Welcome to Cornerstone International College of Canada.\n");
        printf("************************************************************\n");
        fflush(stdout);
        sleep(2);
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
    int result = -1;
    
    char* accountsFileName = AccountsFile;
    char* accountsFileAddress = "/Users/saekof/Github/401-Project1/textfiles/Accounts.txt";
    int numberOfAccounts = 0;
    
    listOfAccounts = getListofAccountFromFile(accountsFileAddress, accountsFileName, &numberOfAccounts);
    
    
    //testing
    for(int i=0; i<numberOfAccounts; i++)
    {
        if(strcmp(userName,listOfAccounts[i].studentID) == 0)
        {
            if(strcmp(password,listOfAccounts[i].password) == 0)
            {
                myStudentID = listOfAccounts[i].studentID;
                result = EXIT_SUCCESS;
                
            }
        }
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

// menu1
void printCertificate(struct Student myself)
{
    printf("Dear ");
    strcmp(myself.gender, "male") == 0 ? puts("Sir,") : puts("Madam,");
    printf("\n");
    
    printf("This is to certify that " );
    strcmp(myself.gender, "Male") == 0 ? printf("Mr.") : printf("Ms.");
    printf("%s", myself.name);
    
    printf(" with student id %s",myself.studentID);
    printf(" is a student at grade %d at CICCC. ",myself.grade);
    
    strcmp(myself.gender, "male") == 0 ? printf("He") : printf("She");
    printf(" was admitted to our college in %d ",myself.admission_year);
    
    printf("and has taken %d",myself.numberOfCourses);
    myself.numberOfCourses == 1 ? puts("course.") : puts("courses.");
    
    printf("Currently ");
    strcmp(myself.gender, "male") == 0 ? printf("He") : printf("She");
    printf("resides at %s.",myself.address);
    printf("\n\n");
    printf("If you have any question, please don't hesitate to contact us.\n");
    printf("Thanks,\n");
    printf("William\n");
    fflush(stdout);
    sleep(5);
}

//2
void PrintMyCourse(struct Student myself,struct Course* listOfCourses,int numberOfCourses)
{
    printf("*********************************************\n");
    if(strcmp(myself.gender, "male") == 0){
        printf("Hi. Mr %s,\n",myself.name);
    }else{
        printf("Hi. Ms. %s,\n",myself.name);
    }
    printf("You have taken the following courses:\n");
    for(int i=0; i<numberOfCourses; i++)
    {
        for(int j=i; j<myself.numberOfCourses; j++)
        {
            if(strcmp(listOfCourses[i].courseID, myself.courses[j]) == 0)
                printf("%d)%s : %s\n",i+1,myself.courses[j],listOfCourses[i].name);
        }
    }
    printf("*********************************************\n");
    sleep(2);
}

// menu3
void printTranscript(struct Student myself)
{
    printf("Hi ");
    strcmp(myself.gender, "male") == 0 ? printf("Mr.") : printf("Ms.");
    printf("%s\n", myself.name);
    
    printf("Here is your transcript:\n");
    
    char* coursesFileName = CoursesFile;
    char* coursesFileAddress = "/Users/saekof/Github/401-Project1/textfiles/Courses.txt";
    int numberOfCourses = 0;
    
    listOfCourses = getListOfCourseNameFromFile(coursesFileAddress, coursesFileName, &numberOfCourses);
    
    char* studentsCoursesFileName = StudentsCoursesFile;
    char* studentsCoursesFileAddress = "/Users/saekof/Github/401-Project1/textfiles/StudentsCourses.txt";
    int numberOfStudentsCourses = 0;
    
    listOfStudentCourses = getListOfStudentCourseFromFile(studentsCoursesFileAddress, studentsCoursesFileName, &numberOfStudentsCourses);
    int counter = 1;
    for(int i = 0; i < myself.numberOfCourses; i++)
    {
        for(int j=0; j<4; j++)
        {
            
            if(strcmp(myself.courses[i], listOfCourses[j].courseID) == 0)
            {
                printf("%d) ",counter);
                printf("%s %s",listOfCourses[j].courseID, listOfCourses[j].name);
                if(strcmp(myStudentID, listOfStudentCourses[j].studentID) == 0)
                {
                    printf(" %d\n",listOfStudentCourses[j].mark);
                }
                counter++;
                break;
            }
        }
    }
    float myGPA = getMyGPA(myself);
    printf("YOUR GPA IS:%.2f\n", myGPA);
    fflush(stdout);
    sleep(5);
}
//4
void GPA(struct Student myself)
{
    float GPA = getMyGPA(myself);
    
    printf("*********************************************\n");
    if(strcmp(myself.gender, "male") == 0){
        printf("Hi. Mr %s,\n",myself.name);
    }else{
        printf("Hi. Ms. %s,\n",myself.name);
    }
    printf("Your GPA is %.2f\n",GPA);
    printf("*********************************************\n");
    sleep(2);
}
// menu5
void printMyRanking(struct Student myself)
{
    printf("Hi ");
    strcmp(myself.gender, "male") == 0 ? puts("Sir,") : puts("Madam,");
    printf("\n");
    
    printf("This is to certify that " );
    strcmp(myself.gender, "Male") == 0 ? printf("Mr.") : printf("Ms.");
    printf("%s,\n", myself.name);
    
    float GPA = getMyGPA(myself);
    
    
    printf("Your GPA is %2.f and therefore your rank is",GPA);
    // think about that
    
    fflush(stdout);
    sleep(5);
}

//6
void ListAllCourses(struct Course* listOfCourses,int numberOfCourses)
{
    printf("*********************************************\n");
    printf("The following courses are offered in CICCC\n");
    for(int i=0; i<numberOfCourses; i++)
    {
        printf("%d)%s : %s\n",i+1,listOfCourses[i].courseID,listOfCourses[i].name);
    }
    printf("*********************************************\n");
    sleep(2);
}
// menu 7
void listAllStudents(void)
{
    char* accountsFileName = AccountsFile;
    char* accountsFileAddress = "/Users/saekof/Github/401-Project1/textfiles/Accounts.txt";
    int numberOfAccounts = 0;
    
    listOfAccounts = getListofAccountFromFile(accountsFileAddress, accountsFileName, &numberOfAccounts);
    
    char* studentsFileName = StudentsFile;
    char* studentsfileAddress = "/Users/saekof/Github/401-Project1/textfiles/Students.txt";
    int numberOfStudents = 0;
    
    listOfStudents = getListOfStudentFromFile(studentsfileAddress, studentsFileName, &numberOfStudents);
    
    printf("There are %d students in CICCC as following",numberOfStudents);
    
    for(int i = 0; i< numberOfAccounts; i++)
    {
        for(int j = 0; j < numberOfStudents; j++)
        {
            if(strcmp(listOfAccounts[i].studentID, listOfStudents[j].studentID) == 0)
            {
                printf("%s:%s\n",listOfStudents[j].name, listOfStudents[j].studentID);
            }
        }
        
    }
}

void logoutUser(struct Student myself)
{
    myself.studentID = NULL;
    myself.name = NULL;
    myself.gender = NULL;
    myself.grade = 0;
    myself.address = NULL;
    myself.admission_year = 0;
    myself.courses = NULL;
    myself.numberOfCourses = 0;
    
    myStudentID = NULL;
    sleep(2);
    loginUser();
}

float getMyGPA(struct Student myself)
{
    char* studentsCoursesFileName = StudentsCoursesFile;
    char* studentsCoursesFileAddress = "/Users/saekof/Github/401-Project1/textfiles/StudentsCourses.txt";
    int numberOfStudentsCourses = 0;
    listOfStudentCourses = getListOfStudentCourseFromFile(studentsCoursesFileAddress, studentsCoursesFileName, &numberOfStudentsCourses);
    
    float Mark = 0;
    int count = 0;
    float GPA = 0;
    
    for(int i = 0; i < numberOfStudentsCourses; i++){
        if(strcmp(myself.studentID, listOfStudentCourses[i].studentID) == 0)
        {
            Mark = Mark + listOfStudentCourses[i].mark;
            count++;
        }
    }
    GPA = Mark / count;
    return GPA;
}

/* File */
int getTheStartIndex(char* filename, char firstChar)
{
    
    if(strcmp(filename, AccountsFile)==0 && firstChar=='1')  //1User:”
    {
        return 7;
    }
    else if(strcmp(filename, AccountsFile)==0 && firstChar=='2') //2Pass:”
    {
        return 7;
    }
    if(strcmp(filename, StudentsFile)==0 && firstChar=='1')  //1studentID:”
    {
        return 12;
    }
    else if(strcmp(filename, StudentsFile)==0 && firstChar=='2') //2name:”
    {
        return 7;
    }
    else if(strcmp(filename, StudentsFile)==0 && firstChar=='3') //3gender:”
    {
        return 9;
    }
    else if(strcmp(filename, StudentsFile)==0 && firstChar=='4') //4grade:”
    {
        return 8;
    }
    else if(strcmp(filename, StudentsFile)==0 && firstChar=='5') //5address:“
    {
        return 10;
    }
    else if(strcmp(filename, StudentsFile)==0 && firstChar=='6') //6admission_year:”
    {
        return 17;
    }
    else if(strcmp(filename, StudentsFile)==0 && firstChar=='7') //7courses:”
    {
        return 10;
    }
    
    else if(strcmp(filename, CoursesFile)==0 && firstChar=='1') //courseID
    {
        return 10;
    }//
    else if(strcmp(filename, CoursesFile)==0 && firstChar=='2') //name
    {
        return 6;
    }
    else if(strcmp(filename, StudentsCoursesFile)==0 && firstChar=='1') //1studentID:"
    {
        return 12;
    }
    else if(strcmp(filename, StudentsCoursesFile)==0 && firstChar=='2') //2courseID:"
    {
        return 11;
    }
    else if(strcmp(filename, StudentsCoursesFile)==0 && firstChar=='3') //3mark:"
    {
        return 7;
    }
    
    else
    {
        return 0;
    }
    
    
}

int convertToNumber(char * string)
{
    int number = atoi( string );
    return number;
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

char firstChar(char* line)
{
    return *line;
}


char* substring(char* line, int startIndex, int endIndex)
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

char** readFile(char* fileAddress, int* numberOfLines)

{
    int lines_allocated = 128;
    int max_line_len = 100;
    
    /* Allocate lines of text */
    char **words = (char **)malloc(sizeof(char*)*lines_allocated);
    if (words==NULL)
    {
        fprintf(stderr,"Out of memory (1).\n");
        exit(1);
    }
    
    FILE *fp = fopen(fileAddress, "r");
    if (fp == NULL)
    {
        fprintf(stderr,"Error opening file.\n");
        exit(2);
    }
    
    int i;
    for (i=0;1;i++)
    {
        int j;
        
        /* Have we gone over our line allocation? */
        if (i >= lines_allocated)
        {
            int new_size;
            
            /* Double our allocation and re-allocate */
            new_size = lines_allocated*2;
            words = (char **)realloc(words,sizeof(char*)*new_size);
            if (words==NULL)
            {
                fprintf(stderr,"Out of memory.\n");
                exit(3);
            }
            lines_allocated = new_size;
        }
        /* Allocate space for the next line */
        words[i] = malloc(max_line_len);
        if (words[i]==NULL)
        {
            fprintf(stderr,"Out of memory (3).\n");
            exit(4);
        }
        if (fgets(words[i],max_line_len-1,fp)==NULL)
            break;
        
        /* Get rid of CR or LF at end of line */
        for (j=(int)(strlen(words[i]))-1;j>=0 && (words[i][j]=='\n' || words[i][j]=='\r');j--)
            ;
        words[i][j+1]='\0';
    }
    /* Close file */
    fclose(fp);
    
    
    (*numberOfLines) = i;
    
    
    return words;
}


int numberOfItemsPerRecordInFile(char* fileName)
{
    if(strcmp(fileName, CoursesFile)==0)
    {
        return 2;
    }
    else if(strcmp(fileName, AccountsFile)==0)
    {
        return 2;
    }
    else if(strcmp(fileName, StudentsFile)==0)
    {
        return 7;
    }
    else if(strcmp(fileName, StudentsCoursesFile)==0)
    {
        return 3;
    }
    else
    {
        return 1;
    }
}

/* Student */
struct Student createAStudent(char* studentID, char* name, char* gender, int grade, char* address, int admission_year, char* courses[], int numberOfCourses)
{
    struct Student* student = (struct Student*)malloc(sizeof(struct Student));
    
    (*student).studentID = studentID;
    (*student).name = name;
    (*student).gender = gender;
    (*student).grade = grade;
    (*student).address = address;
    (*student).admission_year = admission_year;
    (*student).courses = courses;
    (*student).numberOfCourses = numberOfCourses;
    
    
    return *student;
}

struct Student* getListOfStudentFromFile(char* fileAddress, char* fileName, int* numberOfStudents)
{
    
    int numberOfStudentsReadFromFileSoFar = 0;
    
    int numberOfLinesInTheFile = 0;
    char** lines = readFile(fileAddress, &numberOfLinesInTheFile);
    
    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);
    
    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;
    
    
    struct Student* listOfStudents = (struct Student*) malloc(numberOfRecords*sizeof(struct Student));
    
    
    for(int k=0; k<numberOfRecords; k++)
    {
        char* studentID = NULL;
        char* name = NULL;
        char* gender = NULL;
        int grade = 0;
        char* address = NULL;
        int admission_year = 0;
        char** courses= NULL;
        
        int numberOfCourses = 0;
        
        
        for(int i=0; i<numberOfLinesPerRecord; i++)
        {
            int indexOfLine = k*numberOfLinesPerRecord+i;
            
            if(lines[indexOfLine]!=NULL)
            {
                //printf("\n%s\n", lines[indexOfLine]);
                char firstCharacter = firstChar(lines[indexOfLine]);
                
                int lineLength = strLength(lines[indexOfLine]);
                
                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));
                
                
                if(firstCharacter=='1')
                {
                    studentID = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
                else if(firstCharacter=='2')
                {
                    name = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
                else if(firstCharacter=='3')
                {
                    gender = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
                else if(firstCharacter=='4')
                {
                    char* gradeStr = substring(lines[indexOfLine], startIndex, lineLength-2);
                    
                    grade = convertToNumber(gradeStr);
                }
                else if(firstCharacter=='5')
                {
                    address = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
                else if(firstCharacter=='6')
                {
                    char* admissionYearStr = substring(lines[indexOfLine], startIndex, lineLength-2);
                    admission_year = convertToNumber(admissionYearStr);
                }
                else if(firstCharacter=='7')
                {
                    int numberOfComponents = 0;
                    char* coursesStr = substring(lines[indexOfLine], startIndex, lineLength-2);
                    courses = splitString(coursesStr, ',', &numberOfComponents);
                    
                    
                    
                    numberOfCourses = numberOfComponents;
                    
                }
            }//end of if
            
            
        }//end of second for
        
        
        struct Student student= createAStudent(studentID, name, gender, grade, address, admission_year, courses, numberOfCourses);
        listOfStudents[numberOfStudentsReadFromFileSoFar] = student;
        
        numberOfStudentsReadFromFileSoFar++;
        
        
    }//end of first for
    
    *numberOfStudents = numberOfStudentsReadFromFileSoFar;
    return listOfStudents;
}

struct Student getMyStudentDataByID(char* studentID)
{
    //Extracting students information from the file
    char* studentsFileName = StudentsFile;
    char* studentsfileAddress = "/Users/saekof/Github/401-Project1/textfiles/Students.txt";
    int numberOfStudents = 0;
    
    listOfStudents = getListOfStudentFromFile(studentsfileAddress, studentsFileName, &numberOfStudents);
    struct Student myInfo ={NULL,NULL,NULL,0,NULL,0,NULL,0};
    for(int i=0; i<10; i++)
    {
        //testing
        for(int i=0; i<numberOfStudents; i++)
        {
            if(strcmp(studentID, listOfStudents[i].studentID) == 0)
            {
                myInfo = createAStudent(listOfStudents[i].studentID, listOfStudents[i].name, listOfStudents[i].gender, listOfStudents[i].grade, listOfStudents[i].address, listOfStudents[i].admission_year, listOfStudents[i].courses, listOfStudents[i].numberOfCourses);
            }
            
        }
    }
    return myInfo;
}

/* Account */
struct Account createAnAccount(char* studentID, char* password)
{
    struct Account* account = (struct Account*)malloc(sizeof(struct Account));
    
    (*account).studentID = studentID;
    (*account).password = password;
    
    return *account;
}

struct Account* getListofAccountFromFile(char* fileAddress, char* fileName, int* numberOfAccounts)
{
    
    int numberOfAccountsReadFromFileSoFar = 0;
    int numberOfLinesInTheFile = 0;
    char** lines = readFile(fileAddress, &numberOfLinesInTheFile);
    
    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);
    
    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;
    
    
    struct Account* listOfAccounts = (struct Account*) malloc(numberOfRecords*sizeof(struct Account));
    
    
    for(int k=0; k<numberOfRecords; k++)
    {
        char* studentId = NULL;
        char* password = NULL;
        
        for(int i=0; i<numberOfLinesPerRecord; i++)
        {
            int indexOfLine = k*numberOfLinesPerRecord+i;
            
            if(lines[indexOfLine]!=NULL)
            {
                char firstCharacter = firstChar(lines[indexOfLine]);
                
                int lineLength = strLength(lines[indexOfLine]);
                
                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));
                
                
                if(firstCharacter=='1')
                {
                    studentId = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
                else if(firstCharacter=='2')
                {
                    password = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
            }//end of if
            
            
        }//end of second for
        
        struct Account account = createAnAccount(studentId, password);
        listOfAccounts[numberOfAccountsReadFromFileSoFar] = account;
        
        numberOfAccountsReadFromFileSoFar++;
        
        
    }//end of first for
    
    *numberOfAccounts = numberOfAccountsReadFromFileSoFar;
    return listOfAccounts;
}

/* Course */
struct Course createACourse(char* courseID, char* name)
{
    struct Course* course = (struct Course*)malloc(sizeof(struct Course));
    
    (*course).courseID = courseID;
    (*course).name = name;
    
    return *course;
}

struct Course* getListOfCourseNameFromFile(char* fileAddress, char* fileName, int* numberOfCourses)
{
    int numberOfStudentsReadFromFileSoFar = 0;
    int numberOfLinesInTheFile = 0;
    char** lines = readFile(fileAddress, &numberOfLinesInTheFile);
    
    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);
    
    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;
    
    
    struct Course* listOfCourses = (struct Course*) malloc(numberOfRecords*sizeof(struct Course));
    
    
    for(int k=0; k<numberOfRecords; k++)
    {
        char* courseID = NULL;
        char* name = NULL;
        
        for(int i=0; i<numberOfLinesPerRecord; i++)
        {
            int indexOfLine = k*numberOfLinesPerRecord+i;
            
            if(lines[indexOfLine]!=NULL)
            {
                //printf("\n%s\n", lines[indexOfLine]);
                char firstCharacter = firstChar(lines[indexOfLine]);
                
                int lineLength = strLength(lines[indexOfLine]);
                
                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));
                
                if(firstCharacter=='1')
                {
                    courseID = substring(lines[indexOfLine], startIndex+1, lineLength-2);
                }
                else if(firstCharacter=='2')
                {
                    name = substring(lines[indexOfLine], startIndex+1, lineLength-2);
                }
            }//end of if
            
            
        }//end of second for
        
        struct Course course = createACourse(courseID, name);
        listOfCourses[numberOfStudentsReadFromFileSoFar] = course;
        
        numberOfStudentsReadFromFileSoFar++;
        
        
    }//end of first for
    
    *numberOfCourses = numberOfStudentsReadFromFileSoFar;
    return listOfCourses;
}

struct StudentsCourse createAStudentCourse(char* studentID, char* courseID, int mark)
{
    struct StudentsCourse* studentCourse = (struct StudentsCourse*)malloc(sizeof(struct StudentsCourse));
    
    (*studentCourse).studentID = studentID;
    (*studentCourse).courseID = courseID;
    (*studentCourse).mark = mark;
    
    return *studentCourse;
}
struct StudentsCourse* getListOfStudentCourseFromFile(char* fileAddress, char* fileName, int* numberOfCourses)
{
    int numberOfStudentCourseReadFromFileSoFar = 0;
    int numberOfLinesInTheFile = 0;
    char** lines = readFile(fileAddress, &numberOfLinesInTheFile);
    
    int numberOfLinesPerRecord = numberOfItemsPerRecordInFile(fileName);
    
    int numberOfRecords = numberOfLinesInTheFile / numberOfLinesPerRecord;
    
    
    struct StudentsCourse* listOfStudentCourses = (struct StudentsCourse*) malloc(numberOfRecords*sizeof(struct StudentsCourse));
    
    
    for(int k=0; k<numberOfRecords; k++)
    {
        char* studentID = NULL;
        char* courseID = NULL;
        int mark = 0;
        
        for(int i=0; i<numberOfLinesPerRecord; i++)
        {
            int indexOfLine = k*numberOfLinesPerRecord+i;
            
            if(lines[indexOfLine]!=NULL)
            {
                //printf("\n%s\n", lines[indexOfLine]);
                char firstCharacter = firstChar(lines[indexOfLine]);
                
                int lineLength = strLength(lines[indexOfLine]);
                
                int startIndex = getTheStartIndex(fileName, firstChar(lines[indexOfLine]));
                
                if(firstCharacter=='1')
                {
                    studentID = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
                else if(firstCharacter=='2')
                {
                    courseID = substring(lines[indexOfLine], startIndex, lineLength-2);
                }
                else if(firstCharacter=='3')
                {
                    char* marks = substring(lines[indexOfLine], startIndex, lineLength-2);
                    mark = convertToNumber(marks);
                }
            }//end of if
            
            
        }//end of second for
        
        struct StudentsCourse studentCourse = createAStudentCourse(studentID, courseID, mark);
        listOfStudentCourses[numberOfStudentCourseReadFromFileSoFar] = studentCourse;
        
        numberOfStudentCourseReadFromFileSoFar++;
        
        
    }//end of first for
    
    *numberOfCourses = numberOfStudentCourseReadFromFileSoFar;
    return listOfStudentCourses;
}
