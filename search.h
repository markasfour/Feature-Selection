#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
using namespace std;

void feature_search(vector < vector <float> > data)
{
	for (int i = 1; i < data.at(0).size(); i++)
	{
		cout << "On the " << i << "th level of the search tree" << endl;

		for (int j = 1; j < data.at(0).size(); j++)
		{
			cout << "--Considering adding the " << j << " feature" << endl;
		}
	}
}

#endif
