#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include "accuracy.h"
using namespace std;

bool intersect(vector <int> current_set, int j)
{
	for (int i = 0; i < current_set.size(); i++)
	{
		if (current_set.at(i) == j)
		{
			return true;
		}
	}
	return false;
}

void feature_search(vector < vector <float> > data)
{
	vector <int> current_set_of_features;
	
	for (int i = 1; i < data.at(0).size(); i++)
	{
		cout << "On the " << i << "th level of the search tree" << endl;
		int feature_to_add_at_this_level;
		float best_so_far_accuracy = 0;
		
		
		for (int j = 1; j < data.at(0).size(); j++)
		{
			if (!intersect(current_set_of_features, j))
			{
				cout << "--Considering adding the " << j << " feature" << endl;
				float accuracy = leave_one_out_cross_validation(data,
																current_set_of_features,
																j + 1);
				if (accuracy > best_so_far_accuracy)
				{
					best_so_far_accuracy = accuracy;
					feature_to_add_at_this_level = j;
				}
			}
		}
		current_set_of_features.push_back(feature_to_add_at_this_level);
		cout << "On level " << i << " I added feature ";
		cout << feature_to_add_at_this_level << " to current set" << endl;
	}
}

#endif
