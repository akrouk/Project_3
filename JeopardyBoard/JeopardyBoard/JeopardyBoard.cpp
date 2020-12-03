#include "JeopardyData.h"
#include <string>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main()
{
	auto start = system_clock::now();

	JeopardyData data;

	auto end = system_clock::now();
	auto elapsed = duration_cast<milliseconds>(end - start);
	cout << "Time elapsed: " << elapsed.count() << "ms\n";
}
