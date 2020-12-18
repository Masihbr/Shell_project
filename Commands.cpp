#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <process.h>
#include <direct.h>
#include <string.h>
#include "Commands.h"
#include "dirent.h"
/*
#include <libproc.h>
#import <sys/proc_info.h>
*/

#ifdef _WIN32
#define PLATFORM_NAME "windows"
#include <process.h>
#include <direct.h>
#elif defined __unix__
#define PLATFORM_NAME "linux"
#elif defined __APPLE__
#define PLATFORM_NAME "osx"
#endif


#define ERROR 313

using namespace std;


Commands::Commands()
{
    CurrentPath = "C:\\";
}
//
Commands::~Commands()
{
    CurrentPath = "";
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//
/*
void Commands::listProcesses(string& currentPath, string sInput) {
    if (PLATFORM_NAME == "osx")
    {
        stringstream getin(sInput);
        string command;
        string optional;
        string fileName;
        getin >> command >> optional >> fileName;

        ofstream myfile; //file work using ofstream

        int numberOfProcesses = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
        pid_t pids[numberOfProcesses];
        bzero(pids, sizeof(pids));
        proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
        if (optional == ">")
        {
            myfile.open(currentPath + "/" + fileName); //open file
            for (int i = 0; i < numberOfProcesses; ++i)
            {
                if (pids[i] == 0)
                {
                    continue;
                }
                char pathBuffer[PROC_PIDPATHINFO_MAXSIZE];
                bzero(pathBuffer, PROC_PIDPATHINFO_MAXSIZE);
                proc_pidpath(pids[i], pathBuffer, sizeof(pathBuffer));
                if (strlen(pathBuffer) > 0)
                {
                    if (myfile.is_open())
                    {
                        myfile << getProcessName(pathBuffer) << endl; //put the dir out put in there
                    }
                }
            }
            myfile.close();
        }
        else
        {
            for (int i = 0; i < numberOfProcesses; ++i)
            {
                if (pids[i] == 0)
                {
                    continue;
                }
                char pathBuffer[PROC_PIDPATHINFO_MAXSIZE];
                bzero(pathBuffer, PROC_PIDPATHINFO_MAXSIZE);
                proc_pidpath(pids[i], pathBuffer, sizeof(pathBuffer));
                if (strlen(pathBuffer) > 0)
                {
                    cout << getProcessName(pathBuffer) << endl;
                }
            }
        }
    }
    else {
        cout << "this function is not compatible in" << PLATFORM_NAME << "operating system." << endl;
    }
}
*/
string Commands::getProcessName(const string& processAddress) {

    auto pos = processAddress.find_last_of("/");

    string processName = processAddress.substr(pos + 1, processAddress.length());
    return processName;
}

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::clearScreen() {
    cout << "\x1B[2J\x1B[H"; //clears the screen
}
//
void Commands::date() {
    time_t theTime = time(0); //pure time that has passed from a certain date (1970).
    ////
    tm* DATE = localtime(&theTime); //tm is a struct that can give us the date using localtime funtion
    ////
    /*
    struct tm
{
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31] //this ***
    int tm_mon;   // months since January - [0, 11] //this ***
    int tm_year;  // years since 1900 //this ***
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight savings time flag
};
    */
    ////
    string day;
    switch (DATE->tm_wday)
    {
    case 0:
        day = "Sun"; break;
    case 1:
        day = "Mon"; break;
    case 2:
        day = "Tue"; break;
    case 3:
        day = "Wed"; break;
    case 4:
        day = "Thu"; break;
    case 5:
        day = "Fri"; break;
    case 6:
        day = "Sat"; break;
    default:
        day = "someday";
        break;
    }
    cout << "The current date is: " << day;
    printf(" %02d\\%02d\\%04d \n", DATE->tm_mon + 1, DATE->tm_mday, DATE->tm_year + 1900);
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::cd(string& currentPath, string sInput) {
    stringstream getin(sInput);
    string command;
    string optional;
    getin >> command >> optional; //gets the optional to see what to do

    //optiona can only be /d or /?

    if (optional == "/d") {
        string des = "";
        int i = 0;
        int countSpace = 0;
        bool fill = false;
        int sizeDes = 0;
        while (sInput[i] != '\0') {
            if (sInput[i] == '/' && sInput[i + 1] == 'd') { //when you saw /d look for a character
                i += 2;
                while (sInput[i] != '\0') {
                    if (sInput[i] != ' ' && !fill) { //when you saw character start filling des
                        fill = true;
                    }
                    if (fill) {
                        ////
                        if (sInput[i] == '\\' && sizeDes > 0) {
                            if (des[sizeDes - 1] == '\\') {
                                des += "";
                            }
                            else {
                                des += sInput[i]; //this part of code prevents having d:\\\\\\\\\\\\\games as current path
                                sizeDes++;
                            }
                        }
                        else {
                            des += sInput[i];
                            sizeDes++;
                        }
                        ////
                    }
                    i++;
                }
                break;
            }
            i++;
        }
        //exception going to different drive only like cd /d d: will change it to d:\ .
        if (sizeDes > 1) {
            if (des[2] != '\\') {
                des += '\\';
            }
        }

        int valid = validation(des);
        if (valid == 2) {
            currentPath = des;
            saveCurrentDir(currentPath); //for chdir
            cout << endl;
        }
        else {
            if (des == "c:\\" || des == "C:\\" || des == "C:\\users" || des == "c:\\users" || des == "C:\\windows" || des == "c:\\windows" || des == "C:\\program files" || des == "c:\\program files") { //exceptions
                currentPath = des;
                saveCurrentDir(currentPath); //for chdir
                cout << endl;
            }
            else cout << "The system cannot find the path specified." << endl << endl;
            if (valid == 3) {
                cout << "The directory name is invalid." << endl << endl;
            }
        }
    }
    else

        if (optional == "/?") { //explanation
            printf("\nTo change the directory : CD [/D] [drive:][path]\nTo go to the parent folder : CD [..]\nto go to sub folder : CD [name of the folder in this directory]\n");
            printf("\nUse the /D switch to change current drive in addition to changing current\ndirectory for a drive.\n\n");
        }

        else {
            ////
            string des = "";
            int i = 2; //we start after cd and first character we saw we will start filling des
            int countSpace = 0;
            bool fill = false;
            int sizeDes = 0;
            while (sInput[i] != '\0') {
                if (sInput[i] != ' ' && !fill) {
                    fill = true;
                }
                if (fill) {
                    if (sInput[i] == '\\' && sizeDes > 0) {
                        if (des[sizeDes - 1] == '\\') {
                            des += "";
                        }
                        else {
                            des += sInput[i];
                            sizeDes++;
                        }
                    }
                    else {
                        des += sInput[i];
                        sizeDes++;
                    }
                }
                i++;
            }
            ////

            ////
            int j = 0;
            while (des[j] != '\0') {
                if (des[j] == ' ') {
                    des[j] = -1; //to protect spaces in the file name or folder name
                }
                if (des[j] == '\\' || des[j] == '/') {
                    des[j] = ' ';
                }
                j++;
            }
            ////
            string hold = currentPath;
            stringstream getit(des);
            string word;
            while (getit >> word) {
                if (word == "..") {
                    goBackwards(hold);
                }
                else if (word == ".") {
                    goCurrent(hold);
                }
                else
                {
                    goForward(hold, word);
                }
            }
            ////
            int k = 0;
            while (hold[k] != '\0') {
                if (hold[k] == -1) { //to bring back the spaces from protection
                    hold[k] = ' ';
                }
                k++;
            }
            ////
            int valid = validation(hold);
            if (valid == 2) {
                currentPath = hold;
                saveCurrentDir(currentPath); //for chdir
                cout << endl;
            }
            else {
                if (valid == 1) {
                    if (hold == "c:\\" || hold == "C:\\" || hold == "C:\\users" || hold == "c:\\users" || hold == "C:\\windows" || hold == "c:\\windows" || hold == "C:\\program files" || hold == "c:\\program files") { //exceptions //cause there is no premission to make file here
                        currentPath = hold;
                        saveCurrentDir(currentPath); //for chdir
                        cout << endl;
                    }
                    else cout << "The system cannot find the path specified." << endl << endl;
                }
                if (valid == 3) {
                    cout << "The directory name is invalid." << endl << endl;
                }
            }
        }
}
//
void Commands::goBackwards(string& currentPath) {
    int length = currentPath.length();
    int i = length - 1; //start from the end and go back.
    while (1) {
        if (currentPath[i] == ':') { //we have reached the drive name so we should add a '\\'
            currentPath += '\\';
            break;
        }
        if (currentPath[i] == '\\') { //prevents deleting '\\' after drive name
            if (currentPath[i - 1] != ':')
                currentPath.erase(currentPath.end() - 1); //deletes a character from end of the string
            break;
        }
        currentPath.erase(currentPath.end() - 1);
        i--;
    }
}
//
void Commands::goCurrent(string currentPath) {
    currentPath = currentPath;
    //kinda nothing happens
}
//
void Commands::goForward(string& currentPath, string word) {
    if (currentPath[currentPath.length() - 1] != '\\') //if it didn't have '\\' already
        currentPath += '\\' + word;
    else
        currentPath += word; //it has '\\' already
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

int Commands::absoluteAddress(string& address, string currentPath) {
    string hold = currentPath; //keeps current path

    if (address == "") { //checks if it is not empty
        return ERROR;
    }

    if (address[1] == ':') { //checks if the address is absolute
        int valid = validation(address);
        if (valid == 3) { //it is a file

            return 3; //for file
        }
        else {
            if (valid == 2) { //it is a folder
                return 2; //for folder
            }
            return ERROR; //does not exist
        }
    }
    else {

        ////
        int i = 0; //leads the way through address
        while (address[i] != '\0') {
            if (address[i] == ' ') {
                address[i] = -1; //keeps the spaces in file names
            }
            if (address[i] == '\\' || address[i] == '/') { //to work with stringstream uses space to seprate
                address[i] = ' ';
            }
            i++;
        }
        ////


        ////
        stringstream getit(address);
        string word; //each word can be a word, ".." or "." we should add the word(goForward) go one folder upper for ".."(goBackwards) or goCurrent for "."
        while (getit >> word) {
            if (word == "..") {
                goBackwards(hold);
            }
            else if (word == ".") {
                goCurrent(hold);
            }
            else
            {
                goForward(hold, word);
            }
        }
        ////

        ////
        int j = 0;
        while (hold[j] != '\0') {
            if (hold[j] == -1) { //gets us back the spaces in the file names
                hold[j] = ' ';
            }
            j++;
        }
        ////

        ////
        address = hold;
        int valid = validation(address); //check if the address exists
        if (valid == 3) { //it is a file
            return 3; //for file
        }
        else {
            if (valid == 2) {  //it is a folder
                return 2;  //for folder
            }
            return ERROR; //does not exist
        }
        ////
    }
}
//
int Commands::validation(string address) {
    string addressCheck = address + "\\somekindaweirdnameNOhumanbeingwouldeverchoosetonamesomefilewithweirdformatandstuff.ohmygod!";
    const char* address01 = &address[0];
    const char* address02 = &addressCheck[0];
    FILE* file1;
    FILE* file2;
    //for file existence checking
    file1 = fopen(address01, "r");
    //IF IT IS A FILE I SHOULD BE ABLE TO READ IT

    if (file1 == NULL) { //for folder existence checking

        file2 = fopen(address02, "w");
        //IF IT IS A FOLDER I SHOULD BE ABLE TO CREATE FILE IN IT

        if (file2 == NULL) {
            //not a file nor a folder ::1
            return 1;
        }
        else {
            //not a file  but a folder ::2
            fclose(file2);
            del(address02);
            return 2;
        }
    }
    else { //not a folder but a file ::3
        fclose(file1);
        return 3;
    }
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::dir1(string currentPath) {
    int fileNUM = 0;
    int folderNUM = 0;
    string str;

    string identity;
    struct dirent* d1;

    //        struct dirent {
            /* Always zero */
    //    long d_ino;

        /* File position within stream */
    //    long d_off;

        /* Structure size */
    //    unsigned short d_reclen;

        /* Length of name without \0 */
    //    size_t d_namlen;

        /* File type */
    //    int d_type;

        /* File name */                             //we use this
    //    char d_name[PATH_MAX + 1];
    //};
    //typedef struct dirent dirent;

    const char* address = &currentPath[0];
    DIR* d2 = opendir(address);
    if (d2 == NULL)
    {
        printf("Could not open current directory\n");
        return;
    }
    while (1) {
        d1 = readdir(d2);
        if (d1 == NULL) break; //we reached the end
        str = currentPath + '\\' + (d1->d_name);
        if ((validation(str) == 2) || str == currentPath + '\\' + "..") { //folder ::2
            cout << "<DIR>   " << d1->d_name << endl;
            folderNUM++;
        }
        else {
            cout << d1->d_name << endl;
            fileNUM++;
        }
    }
    cout << "                 " << fileNUM << " file(s)" << endl;
    cout << "                 " << folderNUM << " Dir(s)" << endl;
    closedir(d2);
}
//
void Commands::dir2(string currentPath) {
    int fileNUM = 0;
    int folderNUM = 0;
    //
    string str;
    struct dirent* d1;
    const char* a = &currentPath[0];
    DIR* d2 = opendir(a);
    if (d2 == NULL) {
        cout << "Could not open current directory" << endl;
    }
    char list[100][1000];
    int count = 0;
    while (1) {
        d1 = readdir(d2);
        if (d1 == NULL) break; //we reached the end
        strcpy(list[count], d1->d_name); //put the name in list
        count++; //count names
    }
    //
    sortByName(list, count);
    //
    for (int i = 0; i < count; i++) { //print sorted array
        str = currentPath + '\\' + list[i];
        if ((validation(str) == 2) || str == currentPath + '\\' + "..") { //folder ::2
            cout << "<DIR>   " << list[i] << endl;
            folderNUM++;
        }
        else {
            cout << list[i] << endl;
            fileNUM++;
        }
    }
    cout << "                 " << fileNUM << " file(s)" << endl;
    cout << "                 " << folderNUM << " Dir(s)" << endl;
}
//
void Commands::dir3(string currentPath) {
    //
    string address;
    struct dirent* d1;
    const char* a = &currentPath[0];
    DIR* d2 = opendir(a);
    if (d2 == NULL) {
        cout << "Could not open current directory" << endl;
    }
    char list[100][1000];
    int count = 0;
    while (1) {
        d1 = readdir(d2);
        if (d1 == NULL) break;
        int i = 0;
        address = currentPath + '\\' + (d1->d_name);
        if (validation(address) == 3) {
            strcpy(list[count], d1->d_name); //get only file names in list
            count++;
        }
    }
    //
    if (count == 0) {
        cout << "Could Not Find any file" << endl << endl;
    }
    else {
        sortByType(list, count); //sort file names by their extention
        for (int i = 0; i < count; i++) { //print the sorted
            cout << list[i] << endl;
        }
    }
}
//
void Commands::dir4(string currentPath) {
    //same as dir1 but for every thing inside too
    struct dirent* d1;
    const char* address = &currentPath[0];
    DIR* d2 = opendir(address);
    if (d2 == NULL)
    {
        return;
    }
    while (1) {
        d1 = readdir(d2);
        if (d1 == NULL) break;
        string fname = d1->d_name;
        if (fname != "." && fname != "..") {
            cout << currentPath << ":         " << d1->d_name << endl;
            dir4(currentPath + "\\" + d1->d_name); //this makes it recrusivly dir every directory
        }
    }
    closedir(d2);

}
//
void Commands::dir5(string currentPath, string sInput) {
    stringstream getin(sInput);
    string command;
    string optional;
    string fileName;
    getin >> command >> optional >> fileName;

    int i = 0;
    while (fileName[i] != '\0') {
        if (fileName[i] == -2) { //get back the spaces in fileName we protected before
            fileName[i] = ' ';
        }
        i++;
    }


    struct dirent* d1;
    const char* address = &currentPath[0];
    DIR* d2 = opendir(address);
    if (d2 == NULL)
    {
        cout << "Could not open current directory" << endl;
        return;
    }
    ofstream myfile; //file work usig ofstream
    string absolutePath = fileName;
    absoluteAddress(absolutePath, currentPath);
    myfile.open(absolutePath); //open file
    if (myfile.is_open()) {
        while (1) {
            d1 = readdir(d2);
            if (d1 == NULL) break;
            myfile << "<DIR>   " << d1->d_name << endl; //put the dir out put in there
        }
        myfile.close();
    }
    else cout << "Unable to open file" << endl; // file not found
    closedir(d2);
}
//
void Commands::sortByType(char list[][1000], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            string a = list[j];
            string b = list[j + 1];
            a = getType(list[j]); //gets the type
            b = getType(list[j + 1]);
            tolow(a);
            tolow(b);
            char* a1 = &a[0]; //copmpare type
            char* b1 = &b[0]; //copmpare type
            if (strcmp(a1, b1) > 0) {
                swap(list, j, j + 1); //swap happens based on type differences
            }
        }
    }
}
//
string Commands::getType(string str) {
    string type = "";
    int k = str.length() - 1;
    int here = 0;
    while (k != 0) {
        if (str[k] == '.') {
            here = k + 1;
            break;
        }
        k--;
    }
    if (here == 0) {
        type = "";
        return type;
    }
    else {
        while (str[here] != 0) {
            type += str[here];
            here++;
        }
        return type;
    }
}
//
void Commands::sortByName(char list[][1000], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            string a = list[j];
            string b = list[j + 1];
            tolow(a);
            tolow(b);
            char* a1 = &a[0]; //compare names
            char* b1 = &b[0]; //compare names
            if (strcmp(a1, b1) > 0) {
                swap(list, j, j + 1); //a normal swap function
            }
        }
    }
}
//
void Commands::tolow(string& a) { //to compare 2 strings we should first make both lower case in order to do it currectly
    int i = 0;
    while (a[i] != '\0') {
        a[i] = tolower(a[i]);
        i++;
    }
}
//
void Commands::swap(char list[][1000], int i, int j) {
    char hold[1000];
    int c1 = 0;
    while (1) {
        hold[c1] = list[i][c1];
        if (list[i][c1] == '\0') {
            break;
        }
        c1++;
    }
    int c2 = 0;
    while (1) {
        list[i][c2] = list[j][c2];
        if (list[j][c2] == '\0') {
            break;
        }
        c2++;
    }
    int c3 = 0;
    while (1) {
        list[j][c3] = hold[c3];
        if (hold[c3] == '\0') {
            break;
        }
        c3++;
    }
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::chdir(string& currentPath, string sInput) {
    stringstream getin(sInput);
    string command;
    string driveName;
    getin >> command >> driveName;
    if (driveName != "") {
        if (driveName[1] != ':') {
            cout << "The system cannot find the path specified." << endl << endl;
        }
        else if (driveName.length() == 2) {
            loadCurrentDir(currentPath, driveName); //loadCurrent dir by the name of drive name
        }
    }
    else {
        loadCurrentDir(currentPath, driveName); // loadCurrent dir by the current path
    }
}
//
struct driveStruct {
    char driveName = 0;
    string driveDir;  //do you know any PC with more than 28 drives? I don't :]
} currentPathOnDrive[28];
//
void Commands::saveCurrentDir(string& currentPath) { //saves the last path we have been in ,in each drive
    char driveName = tolower(currentPath[0]);
    for (auto& i : currentPathOnDrive) { //check  if the drive already has a value
        if (i.driveName == 0) {
            i.driveName = driveName;
            i.driveDir = currentPath;
            break;
        }
        else if (i.driveName == driveName) { // make a room for this drive for the first time
            i.driveDir = currentPath;
            break;
        }
    }
}
//
void Commands::loadCurrentDir(string& currentPath, string driveName) {
    if (driveName == "") {
        driveName = tolower(currentPath[0]);
    }
    bool isFound = false;
    for (auto& i : currentPathOnDrive) { //search to see if we have been in that drive or not
        if (i.driveName == driveName[0]) {  //if found
            cout << i.driveDir << endl << endl;
            isFound = true;
            break;
        }
    }
    if (!isFound) //if not found we have not been there
        cout << driveName[0] << ":\\" << endl << endl;
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::copy(string address01, string address02) {
    //// code in the specified section would make it possible to copy a file with different name for example copy a.txt and see b.txt in the folder we want
    int leng = address02.length() - 1; //but it is ignored cause we check and only copy in another folder
    bool isFIL = false;
    while (address02[leng] != '\\') {
        if (address02[leng] == '.') {
            isFIL = true;
        }
        leng--;
    }
    ////
    if (!isFIL) { // if isFIL was true we had a different name to copy the file to in destination
        int len = address01.length() - 1;
        bool isFILE = false;
        while (address01[len] != '\\')
        {
            if (address01[len] == '.') {
                isFILE = true;
            }
            len--;
        }

        //get the file name and add it to address02 so we make a file there with that name and start copying

        int i = len + 1;
        string lastword = "";
        if (isFILE) {
            while (address01[i] != '\0') {
                lastword += address01[i];

                i++;
            }
        }
        address02 += "\\" + lastword;
    }
    //copy is done here
    char* address1 = &address01[0];
    char* address2 = &address02[0];
    FILE* source, * destination;
    char c;
    source = fopen(address1, "rb"); //we need to read from address01
    if (source == NULL) {
        cout << "There is no such file in directory" << endl << endl;
    }
    else {
        destination = fopen(address2, "wb"); //we need to write and create address02
        while (!feof(source)) {
            fscanf(source, "%c", &c);
            fprintf(destination, "%c", c);
        }
        fclose(source);
        fclose(destination);
        cout << "        1 file copied." << endl << endl;
    }
}
//
void Commands::cut(string address01, string address02) {
    //// code in the specified section would make it possible to cut a file with different name for exaple copy a.txt and see b.txt in the folder we want
    int leng = address02.length() - 1;  //but it is ignored cause we check and only copy in another folder
    bool isFIL = false;
    while (address02[leng] != '\\') {
        if (address02[leng] == '.') {
            isFIL = true;
        }
        leng--;
    }
    ////
    if (!isFIL) { // if isFIL was true we had a different name to copy the file to in destination
        int len = address01.length() - 1;
        bool isFILE = false;
        while (address01[len] != '\\')
        {
            if (address01[len] == '.') {
                isFILE = true;
            }
            len--;
        }

        //get the file name and add it to address02 so we make a file there with that name and start cutting

        int i = len + 1;
        string lastword = "";
        if (isFILE) {
            while (address01[i] != '\0') {
                lastword += address01[i];

                i++;
            }
        }
        address02 += "\\" + lastword;
    }

    //cut is copy but you delete what you copied in source address

    char* address1 = &address01[0];
    char* address2 = &address02[0];
    FILE* source, * destination;
    char c;
    source = fopen(address1, "rb");
    if (source == NULL) {
        printf("There is no such file in directory");
    }
    destination = fopen(address2, "wb");
    while (!feof(source)) {
        fscanf(source, "%c", &c);
        fprintf(destination, "%c", c);
    }
    fclose(source);
    fclose(destination);
    del(address01);
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::del(string address) { //deletes a file
    const char* add = &address[0];
    remove(add);
}
//
void Commands::del1(string address) {
    const char* add = &address[0];
    if (remove(add) == 0) {
        cout << endl;
    }
    else cout << "there is a problem!" << endl;
}
//
void Commands::del2(string address) {
    char answer;
    cout << endl << "ARE YOU SURE?(Y/N) : ";
    cin >> answer;
    getchar(); //the damaging \n would be terminated
    if (answer == 'y' || answer == 'Y') {
        const char* add = &address[0];
        if (remove(add) == 0) {
            cout << endl;
        }
        else cout << "there is a problem!" << endl;
    }
}
//
void Commands::deldir(string address) {

    const char* add = &address[0];

    struct dirent* entry; /*/*/
    DIR* dir; /*/*/

    dir = opendir(add); //open directory of the address to check directories in it
    while (entry = readdir(dir))
    {
        DIR* subDir;
        FILE* file;
        char a[100] = { 0 };
        if (*(entry->d_name) != '.')
        {
            sprintf(a, "%s\\%s", add, entry->d_name); // a = add \\ entry->name  this can be adress of a directoy or file
            if (subDir = opendir(a)) //checks for being a directory
            {
                closedir(subDir);
                deldir(a); //recrusivly deletes directory
            }
            else
            {
                if (file = fopen(a, "r")) //checks for being a file
                {
                    fclose(file);
                    del(a);
                }
            }
        }
    }
    del(add);
    _rmdir(add); //after deleting everything in it we delete it
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::renam(string address1, string address2) {
    const char* add1 = &address1[0];
    const char* add2 = &address2[0];
    if (rename(add1, add2) == 0) { //gets two addressess and renames add1 one with add2
        cout << endl << endl;
    }
    else cout << "there is a problem!" << endl << endl;
}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

void Commands::help() {
    cout << "Commands" << "\t\t" << "Description" << endl;
    cout << "CD" << "\t\t\t\t" << "Display the name of or changes he current Directory" << endl;
    cout << "DIR" << "\t\t\t\t" << "Displays a list of files and subdirectories in a directory" << endl;
    cout << "CHDIR" << "\t\t\t" << "Display the name of or changes he current Directory" << endl;
    cout << "CLS" << "\t\t\t\t" << "Clears the screen" << endl;
    cout << "COPY" << "\t\t\t" << "Copies files to another location" << endl;
    cout << "DATE" << "\t\t\t" << "Displays the date" << endl;
    cout << "EXIT" << "\t\t\t" << "Close the command prompt" << endl;
    cout << "RENAME" << "\t\t\t" << "Rename the files" << endl;
    cout << "FIND" << "\t\t\t" << "Looks for the specific files in the given path and it's subdirectories" << endl;

}
//

//\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

int findCounter = 0;
void Commands::find(string target, string des) {
    string filterdTarget;
    int length = target.length();
    filterdTarget = target.substr(1, length - 2); //deletes "abc.edf" ---> abc.edf

    int pos = filterdTarget.find("*");

    struct dirent* d1;
    const char* address = &des[0];
    DIR* d2 = opendir(address);
    if (d2 == NULL)
    {
        return;
    }
    while (1) {
        d1 = readdir(d2);
        if (d1 == NULL) break;
        string fname = d1->d_name;
        if (fname != "." && fname != "..") {
            if (pos == -1) { //there is not any star so just find it
                if (filterdTarget == d1->d_name) {
                    findCounter++;
                    cout << des + "\\" + filterdTarget << endl;
                }
                else {
                    if (validation(des + "\\" + d1->d_name) == 2) //folder ::2
                        find(target, des + "\\" + d1->d_name); //search subfolders
                }
            }
            else {
                string starFilterdTarget1 = filterdTarget.substr(0, pos);
                string starFilterdTarget2 = filterdTarget.substr(pos + 1, filterdTarget.length());

                if (superMatching(starFilterdTarget1, starFilterdTarget2, fname))
                {
                    findCounter++;
                    cout << des + "\\" + fname << endl;
                }
            }
        }
    }
    closedir(d2);
}

//
bool Commands::superMatching(string starFilterdTarget1, string starFilterdTarget2, string fileName) {

    int length1 = starFilterdTarget1.length();
    int length2 = starFilterdTarget2.length();

    string fileName1 = fileName.substr(0, length1);
    string fileName2 = fileName.substr(fileName.length() - length2, fileName.length());

    if (starFilterdTarget1 == fileName1 && starFilterdTarget2 == fileName2) {
        return true;
    }
    return false;
}
//
