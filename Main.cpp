#include <iostream>
#include <sstream>
#include <string>
#include "Commands.h"

using namespace std;

void loop();
////
int getInput(string&, string&, string&);
////
void stanCurrentPath(string&);
////
void GeneralStandardizeInput(string&, string);
////
int copyStandardizeInput(string, string&, string&);
////
int dirStandardizeInput(string&);
////
void renameStandardizeInput(string, string&, string&);
////
int deleteStandardizeInput(string&, string);
////
void deleteSpaces(string&, string);
////
void lowerEverything(string&);
////
void getCommand(string, string&);
////
void execute(string&, string, string, int);
////


int main() {
	//
	loop(); //LOOP is required to get multiple commands
	//
	return 0;
}

void loop() {

	int condition = 1; //CONDITION: stands for number of command to be executed - at first ::1(true) to enter while for the first time.
//    string currentPath = "C:\\"; //CURRENT PATH: the address program starts from.
	string currentPath = "C:\\"; //CURRENT PATH: the address program starts from.

	while (condition) //while to execute commands
	{
		////
		string input = "";

		//INPUT: raw characters that user types.

		string sInput = "";
		//
		//S INPUT: preminerly standard type of input for commands
		// spaces from margines will be deleted.
		// all of the characters will be low case.
		//
		string command = "";

		//COMMAND: first word of sInput

		////
		stanCurrentPath(currentPath); //makes sure first letter of each part of address is upper case to look good.
		cout << currentPath << ">";
		////
		condition = getInput(input, sInput, command); //gets a line of input and gives use the condition.
		////
		execute(currentPath, input, sInput, condition); //executes the command that has been entered.
		////
	}
}

//--//
int getInput(string& input, string& sInput, string& command) {
	getline(cin, input); //gets whole line that has been entered by user.

	GeneralStandardizeInput(sInput, input); //        // spaces from margines will be deleted.
									 //      // all of the characters will be low case.

	getCommand(sInput, command); //first word of sInput is determined.

	//exit ::0
	if (command == "exit") {
		return 0;
	}
	else
		//cls ::1
		if (command == "cls") {
			return 1;
		}
		else
			//date ::2
			if (command == "date") {
				return 2;
			}
			else
				//copy ::3
				if (command == "copy") {
					return 3;
				}
				else
					//cd ::4
					if (command == "cd") {
						return 4;
					}
					else
						//dir ::5
						if (command == "dir") {
							return 5;
						}
						else
							//chdir ::6
							if (command == "chdir") {
								return 6;
							}
							else
								//rename ::7
								if (command == "rename") {
									return 7;
								}
								else
									//help ::8
									if (command == "help") {
										return 8;
									}
									else
										//del ::9
										if (command == "del") {
											return 9;
										}
										else
											//find ::10
											if (command == "find") {
												return 10;
											}
											else
												//listProcesses ::11
												if (command == "tasklist") {
													return 11;
												}
												else
													//invalid input ::20
													if (command == "") { //there is no command.
														return 20;
													}
													else
														//invalid input ::20
													{ //there is an invalid command.
														cout << "'" << command << "'" << " is not recognized as an internal or external command," << endl;
														cout << "operable program or batch file." << endl;
														return 20;
													}
}
//--//
void stanCurrentPath(string& str) {
	str[0] = toupper(str[0]);
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == '\\' && str[i + 1] != '\0') {
			str[i + 1] = toupper(str[i + 1]);
		}
		i++;
	}
}
//--//
void GeneralStandardizeInput(string& standard_str, string str) {
	lowerEverything(str);
	deleteSpaces(standard_str, str);
}
//--//
void deleteSpaces(string& standard_str, string str) { //not every space is extra
	int size = str.length();

	int i = 0; //from begining to the first character except ' '
	while (str[i] != '\0') {
		if (str[i] == ' ') {
			str[i] = -1; //a character user can not use we use -1 to delete spaces.
		}
		else break;
		i++;
	}

	int j = size - 1; //from end to the last character except ' '
	while (j > 0)
	{
		if (str[j] == ' ') {
			str[j] = -1; //a character user can not use we use -1 to delete spaces.
		}
		else break;
		j--;
	}

	/*
	int flag = 0;
	int k = 0;
	while (str[k] != '\0')
	{
		if (str[k] == ' ') {
			flag++;                     //deleting spaces between the words would make problems
			if (flag > 1) {             //for example file : a   b    c.txt would be a b c.txt and the system won't find it
				str[k] = -1;
			}
		}
		else flag = 0;
		k++;
	}
	*/

	for (int i = 0; i < size; i++) { //copy everything except -1s (SPACES) to the standard_str
		if (str[i] != -1) {
			standard_str += str[i];

		}
	}

}
//--//
void lowerEverything(string& str) {
	int i = 0;
	while (str[i] != '\0') {
		str[i] = tolower(str[i]); //lower cases each charachter
		i++;
	}
}
//--//
void getCommand(string sInput, string& command) {
	int i = 0;
	while (1) {
		if (sInput[i] == ' ' || sInput[i] == '\0') {
			break;
		}
		command += sInput[i];
		i++;
	}
	command[i] = '\0';
}
//--//

void execute(string& currentPath, string input, string sInput, int condition) {
	Commands commands; //class that every command function is in it.
	//exit ::0
	//to exit the shell
	if (condition == 0) {
		exit(EXIT_FAILURE);
	}
	else
		//cls ::1
		//clears screen
		if (condition == 1) {
			commands.clearScreen();
		}
		else
			//date ::2
			//shows date
			if (condition == 2) {
				commands.date();
			}
			else
				//copy ::3
				//can copy or cut a file.
				if (condition == 3) {
					string address1 = "";
					string address2 = "";
					int check1 = copyStandardizeInput(sInput, address1, address2);

					//check 1 determines copy::1 or cut::2

					int check2 = commands.absoluteAddress(address1, currentPath); //file ::3
					int check3 = commands.absoluteAddress(address2, currentPath); //folder ::2

					//check 2 and 3 determine if the file and folder exist

					if (check1 == 1 && check2 == 3 && check3 == 2) { //normal copy ::3-1
						commands.copy(address1, address2);
					}
					else
						if (check1 == 2 && check2 == 3 && check3 == 2) { //cut ::3-2
							commands.cut(address1, address2);
						}
						else
							if (!(check1 == 1 || check1 == 2)) { //not cut nor coppy
								cout << "The syntax of the command is incorrect." << endl << endl;
							}
							else
								if ((check1 == 1 || check1 == 2) && check2 != 3) { //invalid input ::3-3
									cout << "The system cannot find the file specified." << endl << endl;
								}
								else
									if ((check1 == 1 || check1 == 2) && check2 == 3 && check3 != 2) { //invalid path
										cout << "The system cannot find the path specified." << endl << endl;
									}

				}
				else
					//cd ::4
					//to change directory
					if (condition == 4) {
						commands.cd(currentPath, sInput);
					}
					else
						//dir ::5
						//list of contents
						if (condition == 5) {
							int dirChack = dirStandardizeInput(sInput); //dir check tells what kind of optional funtion is called
							if (dirChack == 1) { //normal dir
								commands.dir1(currentPath);
							}
							else
								if (dirChack == 2) { //sorted dir by name
									commands.dir2(currentPath);
								}
								else
									if (dirChack == 3) { //sorted dir by type
										commands.dir3(currentPath);
									}
									else
										if (dirChack == 4) { //dir for everything
											commands.dir4(currentPath);
										}
										else
											if (dirChack == 5) {//dir put result in file
												commands.dir5(currentPath, sInput);
											}
											else {
												cout << "syntax error" << endl << " Make sure you have used the command proparly." << endl << endl;
											}
						}
						else
							//chdir ::6
							//saves paths you wondered.
							if (condition == 6) {
								commands.chdir(currentPath, sInput);
							}
							else
								//rename ::7
								//changes name of a file.
								if (condition == 7) {
									string address1 = "", address2 = "";
									renameStandardizeInput(sInput, address1, address2);
									int check = commands.absoluteAddress(address1, currentPath); //file ::3
									if (check != 3) {
										cout << "The system cannot find the file specified." << endl << endl;
									}
									else {
										commands.absoluteAddress(address2, currentPath);
										commands.renam(address1, address2);
									}
								}
								else
									//help ::8
									//shows instructions
									if (condition == 8) {
										commands.help();
									}
									else
										//del ::9
										//can delete a file or a folder.
										if (condition == 9) {
											string address = "";
											int check1 = deleteStandardizeInput(address, sInput);
											int check2 = commands.absoluteAddress(address, currentPath);
											if (check1 == 1) {
												if (check2 != 3) { //if it is not a file or does not exist
													if (check2 != 2) {
														cout << "Could Not Find " << address << endl << endl;
													}
													else {
														cout << address << " is not a file please use /F for deleting directories." << endl << endl;
													}
												}
												else {
													commands.del1(address);                             //file ::3
												}                                                       //folder ::2
											}
											else if (check1 == 2) {
												if (check2 != 3) { //if it is not a file or does not exist
													if (check2 != 2) {
														cout << "Could Not Find " << address << endl << endl;
													}
													else {
														cout << address << " is not a file please use /F for deleting directories." << endl << endl;
													}
												}
												else {
													commands.del2(address);
												}
											}
											else if (check1 == 3) {
												if (check2 != 2) { //if it is not a folder or does not exist
													if (check2 != 3) {
														cout << "Could Not Find " << address << endl << endl;
													}
													else {
														cout << address << " is not a directory please do not use /F for deleting files." << endl << endl;
													}
												}
												else {
													commands.deldir(address);
													cout << endl;
												}
											}
										}
										else
											//find ::10
											if (condition == 10) {

												stringstream getin(sInput);
												int countword = 0;
												string word;
												string hold[3];
												while (getin >> word) {
													hold[countword] = word;
													countword++;
												}

												if (countword == 2) {
													commands.find(hold[1], currentPath);
													if (findCounter == 0)
														cout << "No such file matches in this path" << endl;
												}
												else if (countword == 3) {
													commands.find(hold[1], hold[2]);
													if (findCounter == 0)
														cout << "No such file matches in this path" << endl;
												}
												else {
													cout << "make sure you have used the command properly." << endl;
												}

											}
											else
												//list processes ::11
												if (condition == 11) {
													//commands.listProcesses(currentPath, sInput);
												}
												else
													//invalid input ::20
													if (condition == 20) {
														return;
													}
}

int copyStandardizeInput(string sInput, string& address1, string& address2) {
	stringstream in(sInput);
	string command;
	string optional;
	in >> command >> optional; //second word decides if it is a copy or cut.
	if (optional == "/x") { //cut case


		int i = 0; //leads the way through
		int spaceCount = 0; //counts spaces
		bool fill1 = false; //determines if addresss1 should be filled with sInput
		bool fill2 = false; //determines if addresss1 should be filled with sInput

		while (sInput[i] != '\0') {
			if (sInput[i] == '/' && sInput[i + 1] == 'x') { //go forward to see "/x"
				i += 2;
				while (sInput[i] != '\0') {
					if (sInput[i] != ' ' && !fill1 && !fill2) { //first charactar you see start filling address1
						fill1 = true;
					}
					if (sInput[i] == '.' && sInput[i + 1] <= 'z' && sInput[i + 1] >= 'a') { //when you saw '.' with the next ' '(space) start filling address2
						spaceCount = -1000;
					}
					if (sInput[i] == ' ') {
						spaceCount++;
					}
					if (spaceCount == -999 && !fill2) {
						fill1 = false;
						fill2 = true;
						i++;
					}
					if (fill1) {
						address1 += sInput[i];
					}
					if (fill2) {
						address2 += sInput[i];
					}
					i++;
				}
				break;
			}
			i++;
		}
		return 2;
	}
	else
	{ //copy case
		int i = 4; //leads the way after "copy"
		int spaceCount = 0; //counts spaces
		bool fill1 = false; //determines if addresss1 should be filled with sInput
		bool fill2 = false; //determines if addresss1 should be filled with sInput
		while (sInput[i] != '\0') {
			if (sInput[i] != ' ' && !fill1 && !fill2) { //first charactar you see start filling address1
				fill1 = true;
			}
			if (sInput[i] == '.' && sInput[i + 1] <= 'z' && sInput[i + 1] >= 'a') { //when you saw '.' with the next ' '(space) start filling address2
				spaceCount = -1000;
			}
			if (sInput[i] == ' ') {
				spaceCount++;
			}
			if (spaceCount == -999 && !fill2) {
				fill1 = false;
				fill2 = true;
				i++;
			}
			if (fill1) {
				address1 += sInput[i];
			}
			if (fill2) {
				address2 += sInput[i];
			}
			i++;
		}
		return 1;
	}
}
//
int dirStandardizeInput(string& sInput) {
	////
	string str = sInput;
	int flag = 0; //flag is for deleting spaces more than one like a        b to a b
	int k = 0; //we go throw with k
	int countSpace = 0;
	bool core = false; //determines when to save the spaces
	while (str[k] != '\0')
	{

		if (str[k] == ' ' && !core) {
			flag++;
			if (flag > 1) {
				str[k] = -1; //deleting spaces we don't need
			}
		}
		else flag = 0;

		if (str[k] == ' ') countSpace++; //count good and neccessary spaces
		if (countSpace == 2 && str[k] != ' ' && str[k] != -1 && !core) {
			core = true;
		}
		if (core) {
			if (str[k] == ' ') {
				str[k] = -2; //spaces in file address
			}
		}
		k++;
	}

	sInput = "";
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] != -1) { //spaces that are not useful will be gone
			sInput += str[i];
		}
		i++;
	}
	stringstream getin(sInput);
	int countword = 0;
	string word;
	string hold[3];
	while (getin >> word) {
		hold[countword] = word;
		countword++;
	}
	if (countword == 1) {
		if (hold)
			return 1;
	}
	else
		if (countword == 2) {
			if (hold[1] == "/o") {
				return 2;
			}
			else if (hold[1] == "/e") {
				return 3;
			}
			else if (hold[1] == "/s") {
				return 4;
			}
		}
		else if (countword == 3) {
			if (hold[1] == ">") {
				return 5;
			}
			else return 6;
		}
		else return 6;
}
//
void renameStandardizeInput(string sInput, string& address1, string& address2) {
	string address = "";
	int i = 0;
	bool beriz = false;
	while (1) {
		if (sInput[i] == ' ') {
			while (1) {
				if (sInput[i] != ' ' && !beriz) {
					beriz = true;
				}
				if (beriz) {
					address += sInput[i];  //saves both names
				}
				if (sInput[i] == '\0') {
					break;
				}
				i++;
			}
		}
		if (sInput[i] == '\0') {
			break;
		}
		i++;
	}

	int j = 0;
	bool fill = false;
	int countSpace = 0;
	while (address[j] != '\0') {
		if (address[j] == '.' && address[j + 1] <= 'z' && address[j + 1] >= 'a') {
			countSpace = -1000;
		}
		if (address[j] == ' ') {
			countSpace++;
		}
		if (countSpace == -999 && !fill) {
			fill = true;
			j++;
		}
		if (!fill) {
			address1 += address[j]; //first name will be filled until we see a '.' and after that with seeing the first space
		}                           //the second address (address2) will be filled
		else {
			address2 += address[j];
		}
		j++;
	}
}
//
int deleteStandardizeInput(string& address, string sInput) {
	stringstream getin(sInput);
	string command;
	string optional;
	getin >> command >> optional;
	if (optional == "/p") {
		int i = 3;
		bool fill = false;
		while (sInput[i] != '\0') {
			if (sInput[i] == '/' && sInput[i + 1] == 'p') { //when we see "/p" look for a character except ' '(space)
				i += 2;
				while (sInput[i] != '\0') {
					if (sInput[i] != ' ' && !fill) { //when we see a character except ' '(space) start filling address
						fill = true;
					}
					if (fill) {
						address += sInput[i];
					}
					i++;
				}
				break;
			}
			i++;
		}
		return 2;
	}

	else if (optional == "/f") {
		int i = 3;
		bool fill = false;
		while (sInput[i] != '\0') {
			if (sInput[i] == '/' && sInput[i + 1] == 'f') { //when we see "/f" look for a character except ' '(space)
				i += 2;
				while (sInput[i] != '\0') {
					if (sInput[i] != ' ' && !fill) { //when we see a character except ' '(space) start filling address
						fill = true;
					}
					if (fill) {
						address += sInput[i];
					}
					i++;
				}
				break;
			}
			i++;
		}
		return 3;
	}
	else if (optional == "/?") {
		cout << "Deletes one or more files." << endl << endl << "DEL [name or address of the file you want to delete]" << endl << endl << endl;
		cout << "DEL [/P] [/F[:]attributes] names" << endl << endl;
		cout << "DEL [/P]          asks you if you are sure about removing the file" << endl;
		cout << "DEL [/F]          removes a directory for good" << endl << endl << endl;
		return 313;
	}
	else
	{
		int i = 3;
		bool fill = false;
		while (sInput[i] != '\0') {
			if (sInput[i] != ' ' && !fill) { //when we see a character except ' '(space) start filling address
				fill = true;
			}
			if (fill) {
				address += sInput[i];
			}
			i++;
		}
		return 1;
	}
}
//
