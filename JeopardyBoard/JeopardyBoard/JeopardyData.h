#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <Windows.h>
#pragma once
using namespace std;

//This class contains file I/O and stores the data 
//For it to work, make sure the "master_season1-36.tsv" file is in the solution folder
//To read the file, simply create a JeopardyData object in main()
//The data can then be manipulated through that object

/*===============================================
| Index of Components in JeopardyData			|
=================================================
| 0. Round										|
| 1. Value										|
| 2. Double Jeopary (yes/no)					|
| 3. Category									|
| 4. Comments									|
| 5. Clue										|
| 6. Answer										|
| 7. Air Date									|
| 8. Notes										|
===============================================*/

struct JeopardyQ
{
	JeopardyQ() : jq({}) {};
	JeopardyQ(vector<string>& v) : jq(v) {};
	vector<string> jq;

public:
	string operator[](const int& i) const
	{
		if (i < 0 || i > 8)
		{
			cout << "Error: Index out of range." << endl;
			exit(EXIT_FAILURE);
		}
		else return this->jq[i];
	}
};

struct JeopardyData
{
	JeopardyData() { ReadFile(); }
	map<string, vector<JeopardyQ>> data;
	unordered_map<string, vector<JeopardyQ>> unorderedData;

public:
	void ReadFile();
	JeopardyQ ParseLine(string& line);
	void ShowConsoleCursor(bool showCursor);
};
