# 401 Project1: Basic Educational Portal

## Attachments
 There are 4 text files in addition to this project description. The name of the files are as
 following. These files are sample files and you can use them while you are implementing
 this project.
  
  - Account.txt
  - Students.txt
  - Courses.txt
  - StudentsCourses.txt
  
## Project Description
In this project you are going to implement a basic educational portal. Through this portal the students can login to the portal through a login view and perform some actions that are available to them. In this section we describe the detail of the login feature and other functionalities available on the portal.
Login View: Once you run the program, the following view is shown to the user:
```
************************************************************
Please enter your account to login:
************************************************************
Username:
Password:
```
If the username and password were correct then the program prints the following message and keeps the message on screen for 2 seconds and then prints the main menu. If the username or password was wrong then the program informs the user using the following error message and asks the user to try again.

If username and password were correct:
```
************************************************************
Welcome to Cornerstone International College of Canada. 
************************************************************
```
If the username or password was wrong:
```
************************************************************
Your account does not exist. Please try again! 
************************************************************
```
Once the user successfully entered his/her username and password the program shows the above welcome message for 2 seconds and then prints the following main menu:
```
************************************************************
Select from the options: 
************************************************************
—-[1] Print my enrolment certificate
—-[2] Print my courses
—-[3] Print my transcript
—-[4] Print my GPA
—-[5] Print my ranking among all students in the college
—-[6] List all available courses
—-[7] List all students
-—[8] Logout
-—[9] Exit 
************************************************************
Enter the number corresponding to each item to proceed:
```
The user enters a number between 1 and 9 every time to perform the corresponding functionality.

Print my enrolment certificate: If the user entered `1`, the program prints the following information from the user in the following format. And then prints the main menu again.
```
Dear Sir/Madam,
This is to certify that Mr. Peter Brown with student id 7813007 is a student at grade 1 at CICCC. He was admitted to our college in 2011 and has taken 1 course(s). Currently he resides at 850 West Vancouver, Vancouver.
If you have any question, please don’t hesitate to contact us.
Thanks,
Williams,
```
Print my courses: If the user entered `2`, the program prints all the courses the student has taken in the following format. And then prints the above main menu again.
```
Hi Mr. Peter Brown,
You have taken the following courses:
1) MADP101: Objective-C
2) MADP202: Project Management
3) MADP301: Java Programming
4) MADP401: Android Programming
```
Print my transcript: If the user entered `3`, then the program prints the transcript of the user in the following format and then prints the above menu.
```
Hi Mr. Peter Brown, Here is your transcript:
1) MADP101: Objective-C: 80
2) MADP202: Project Management: 45
3) MADP301: Java Programming: 64
4) MADP401: Android Programming: 70
YOUR GPA IS: 64.75
```
Print my GPA: If the user entered `4`, then the program prints the gpa of the student in the following format and then prints the above main menu.
```
Hi Mr. Peter Brown,
Your GPA is 64.75
```
Print my ranking among all students in the college: If the user enters `5`, the program will find the rank of the student based on his/her gpa and print it and then print the above main menu.
```
Hi Mr. Peter Brown,
Your GPA is 64.75 and therefore your rank is 3.
```
List all available courses: If the user entered `6`, the program will print the list of all available courses in the college in the following format and then print the menu.
```
The following courses are offered in CICCC:
1) MADP101: Objective-C
2) MADP102: Object-Oriented Programming
3) MADP201: Problem Solving
4) MADP202: Project Management
5) MADP301: Java Programming
6) MADP302: Web Development
7) MADP401: Android Programming
5) MADP402: iOS Applications
```
List all students in the college: If the user enters `7`, the program will print the list of all students in the college in the following format and then print the menu.
```
There are 4 students in CICCC as following:
1) Peter Brown: 7813007
2) Joseph Rod: 812345
3) Cristina Li: 8012333
4) Adams Wang: 7812999
```
Logout: If the user entered `8`, the program will print the login menu and let the user login again with the same or different account.

Exit: If the user entered `9`, the program terminates.

## Project Data
The data you need for this project is stored in the 4 text files mentioned in the attachments part. Your program should the data in these files to be able to do the other functionalities. You need to do self-study and learn how to read from a text file. You don’t need to write to or edit the files.
