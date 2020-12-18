#pragma once

using namespace std;

extern int findCounter;

class Commands
{
public:
    Commands();
    ~Commands();

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    //static void listProcesses(string& currentPath, string sInput);
    static string getProcessName(const string& processAddress);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void clearScreen();
    void date();

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void cd(string& currentPath, string sInput);
    void goBackwards(string& currentPath);
    void goCurrent(string currentPath);
    void goForward(string& currentPath, string word);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    int absoluteAddress(string&, string);
    int validation(string address);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void dir1(string currentPath);
    void dir2(string currentPath);
    void dir3(string currentPath);
    void dir4(string currentPath);
    void dir5(string currentPath, string sInput);
    void sortByName(char list[][1000], int count);
    void sortByType(char list[][1000], int count);
    void swap(char list[][1000], int i, int j);
    void tolow(string& a);
    string getType(string a);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void chdir(string& currentPath, string sInput);
    void saveCurrentDir(string& currentPath);
    void loadCurrentDir(string& currentPath, string driveName);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void copy(string, string);
    void cut(string, string);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void del(string address);
    void del1(string address);
    void del2(string address);
    void deldir(string address);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void renam(string address1, string address2);

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void help();

    //\//\//\//\\//\\//\\//\\//\\//\\//\\//\\//

    void find(string target, string des);
    bool superMatching(string starFilterdTarget1, string starFilterdTarget2, string fineName);

private:
    string CurrentPath;

};



