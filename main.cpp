#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "normalize.h"
#include "search.h"
using namespace std;

int main(int argc, char* argv[])
{
	cout << "Welcome to Mark Asfour's Feature Selection Algorithm." << endl;
	cout << "Type in the name of the file to test: ";
	string filename;
	cin >> filename;
	
	string line;
	vector < vector<float> > data;
	ifstream file(filename.c_str());
	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector <float> lineData;
			stringstream lineStream(line);

			float value;
			while (lineStream >> value)
			{
				lineData.push_back(value);
			}
			data.push_back(lineData);
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	int algorithm = 0;
	cout << "Type the number of the algorithm you want to run. " << endl;
	cout << "1) Forward Selection" << endl;
	cout << "2) Backward Elimination" << endl;
	cout << "3) Custom Algorithm" << endl;
	while (algorithm < 1 || algorithm > 3)
	{
		cin >> algorithm;
	}

	cout << "This dataset has " << data.at(0).size() - 1;
	cout << " features (not including the class attribute), ";
	cout << "with " << data.size() << " instances." << endl;

	cout << "Please wait while I normalize the data...";
	normalize(data);
	
	feature_search(data);
	return 0;
}
