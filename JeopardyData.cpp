#include "JeopardyData.h"

void JeopardyData::ReadFile()
{
	string filename = "test_file_only_5_per_cat.tsv";
	ifstream file(filename);

	if (file.fail())
	{
		cout << "Error: Failed to read file." << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	float progress = 0.0f, progFactor = 0.000279662403f;
	//progFactor from 100/357574 (num of lines)
	//manual input simplifies time complexity; only iterating through the file once
	//only saves 20 seconds but it's something (from ~160s to ~140s)

	ShowConsoleCursor(false); //removes cursor so it doesn't spaz out while printing the progress
	getline(file, line);
	while (getline(file, line))
	{
		//Create JeopardyQ obj and a string of the its category 
		JeopardyQ jq = ParseLine(line);
		string category = jq[3];

		//Add JeopardyQ to maps
		data[category].push_back(jq);
		unorderedData[category].push_back(jq);

		//Progress bar 
		cout << "Reading File... " << (int)progress << "%\r";
		cout.flush();
		//progress += progFactor;
		progress += 1.0f; 
	}

	ShowConsoleCursor(true);
	cout << "Reading File... " << (int)progress << '%' << endl;
	file.close();
}

JeopardyQ JeopardyData::ParseLine(string& line)
{
	stringstream ss(line);
	string temp;
	vector<string> v;

	while (getline(ss, temp, '\t'))
		v.push_back(temp);

	return JeopardyQ(v);
}

void JeopardyData::ShowConsoleCursor(bool showCursor)
{
	//From https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO	cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showCursor;
	SetConsoleCursorInfo(out, &cursorInfo);
}
