#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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
	
	cout << endl;
	cout << "This dataset has " << data.at(0).size() - 1;
	cout << " features (not including the class attribute), ";
	cout << "with " << data.size() << " instances." << endl;
	cout << endl;

	cout << "Please wait while I normalize the data...";
	normalize(data);
	cout << endl;

	cout << "Beginning search" << endl;
	cout << endl;
	
	if (algorithm == 1)
		forward_search(data);
	else if (algorithm == 2)
		backwards_elimination(data);
	else if (algorithm == 3)
	{
		vector < vector<float> > data1;
		vector < vector<float> > data2;
		vector < vector<float> > data3;
		vector < vector<float> > data4;
		for (int i = 0; i < data.size(); i++)
		{
			if (i < (data.size() / 4))
				data1.push_back(data.at(i));
			else if (i < (2 * data.size() / 4))
				data2.push_back(data.at(i));
			else if (i < (3 * data.size() / 4))
				data3.push_back(data.at(i));
			else 
				data4.push_back(data.at(i));
		}
		vector <int> best1;
		vector <int> best2;
		vector <int> best3;
		vector <int> best4;

		best1 = forward_search(data1);
		best2 = forward_search(data2);
		best3 = forward_search(data3);
		best4 = forward_search(data4);

		vector <int> best;
		best.insert(best.end(), best1.begin(), best1.end());
		best.insert(best.end(), best2.begin(), best2.end());
		best.insert(best.end(), best3.begin(), best3.end());
		best.insert(best.end(), best4.begin(), best4.end());

		sort(best.begin(), best.end());
		for (int i = 0; i < best.size(); i++)
		{
			cout << best.at(i) << ", ";
		}
		cout << endl;
	}
	return 0;
}
