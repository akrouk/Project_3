#include <vector>
#include <set>
#include <unordered_set>
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

private:
	vector<string> jq;
};

struct JeopardyData
{
	JeopardyData() { ReadFile(); }

public:
	set<JeopardyQ*> data;
	unordered_set<JeopardyQ*> unorderedData;

	void ReadFile();
	JeopardyQ* ParseLine(string& line);
	void ShowConsoleCursor(bool showCursor);
};