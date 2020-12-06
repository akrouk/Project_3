#include "JeopardyData.h"

void JeopardyData::ReadFile()
{
	string filename = "master_season1-36.tsv";
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

	auto start = chrono::high_resolution_clock::now();

	while (getline(file, line))
	{
		//Create JeopardyQ obj and a string of the its category 
		JeopardyQ jq = ParseLine(line);
		string category = jq[3];

		//Add JeopardyQ to maps
		data[category].push_back(jq);

		//Progress bar 
		cout << "Populating Ordered Map... " << (int)progress << "%\r";
		cout.flush();
		progress += progFactor;
	}

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
	cout << "Populating Ordered Map... " << (int)progress << '%' << endl;
	cout << "Populated Ordered Map with Data in: " << duration.count() << " seconds\n"; 

	file.clear();
	file.seekg(0, ios::beg);
	getline(file, line);
	progress = 0.0f; 

	start = chrono::high_resolution_clock::now();

	while (getline(file, line))
	{
		//Create JeopardyQ obj and a string of the its category 
		JeopardyQ jq = ParseLine(line);
		string category = jq[3];

		//Add JeopardyQ to maps
		unorderedData[category].push_back(jq);

		//Progress bar 
		cout << "Populating Unordered Map... " << (int)progress << "%\r";
		cout.flush();
		progress += progFactor;
	}

	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	cout << "Populating Unordered Map... " << (int)progress << '%' << endl;
	cout << "Populated Unordered Map with Data in: " << duration.count() << " seconds\n";

	ShowConsoleCursor(true);
	CleanData();
	file.close();
}

JeopardyQ JeopardyData::ParseLine(string& line)
{
	stringstream ss(line);
	string temp;
	vector<string> v;

	while (getline(ss, temp, '\t'))
	{
		temp.erase(remove(temp.begin(), temp.end(), '\\'), temp.end());
		v.push_back(temp);
	}

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

void JeopardyData::CleanData()
{
	auto iter1 = data.begin();
	auto iter2 = unorderedData.begin();

	//data and unorderedData should ALWAYS be the same size, so there are no edge cases to account for
	//iterate through both at the same time, erasing elements that don't have >= 5 JeopardyQs
	//(this is necessary because Jeopardy boards have 5 questions per category - don't want unusable data)
	//(with the master file, amount of elements left over is > 168,555)
	//(11,121 categories are unusable; ~200,700 remaining in the maps)
	while (iter1 != data.end() && iter2 != unorderedData.end())
	{
		if (iter1->second.size() < 5)
			data.erase(iter1++);
		else
			iter1++;

		if (iter2->second.size() < 5)
			unorderedData.erase(iter2++);
		else
			iter2++;
	}
}

vector<JeopardyQ> JeopardyData::Find(string category)
{
	auto start = chrono::high_resolution_clock::now();
	vector<JeopardyQ> result = this->data[category];
	auto stop = chrono::high_resolution_clock::now();
	if (result.size() == 0)
	{
		cout << "Category not found." << endl;
		return result;
	}
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "Ordered Map: Found category " << category << " in " << duration.count() << " microseconds." << endl;
	start = chrono::high_resolution_clock::now();
	result = this->unorderedData[category];
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "Unordered Map: Found category " << category << " in " << duration.count() << " microseconds." << endl;
	return result;
}

vector<string> JeopardyData::RandCategories()
{
	vector<string> categories; 
	vector<int> indices; 

	//From https://diego.assencio.com/?index=6890b8c50169ef45b74db135063c227c
	random_device device; 
	mt19937 generator(device());
	uniform_int_distribution<int> dist(0, data.size() - 1);

	//Populate indices with 5 random nums between 0 and num of categories
	//Using find function to avoid collisions (no repeat nums)
	for (int i = 0; i < 5; i++)
	{
		int randNum = dist(device);

		if (find(indices.begin(), indices.end(), randNum) != indices.end())
			i--;
		else
			indices.push_back(randNum);
	}
	
	//Populate categories with 5 random categories at the generated indices
	int j = 0; 
	for (auto iter = data.begin(); iter != data.end(); iter++)
	{
		if (find(indices.begin(), indices.end(), j) != indices.end())
			categories.push_back(iter->first);
		
		if (categories.size() == 5)
			break;

		j++;
	}

	return categories;
}
