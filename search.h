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
	float total_accuracy = 0;
	vector <int> best_features;

	for (int i = 1; i < data.at(0).size(); i++)
	{
		int feature_to_add_at_this_level;
		float best_so_far_accuracy = 0;
		for (int j = 1; j < data.at(0).size(); j++)
		{
			if (!intersect(current_set_of_features, j))
			{
				cout << "Using feature(s) {";
				for (int p = 0; p < current_set_of_features.size(); p++)
				{
					cout << current_set_of_features.at(p) << ",";
				}
				cout << j << "} accuracy is ";
				float accuracy = leave_one_out_cross_validation(data,
																current_set_of_features,
																j);
				cout << accuracy << endl;
				if (accuracy > best_so_far_accuracy)
				{
					best_so_far_accuracy = accuracy;
					feature_to_add_at_this_level = j;
				}
			}
		}

		current_set_of_features.push_back(feature_to_add_at_this_level);
		if (best_so_far_accuracy > total_accuracy)
		{
			total_accuracy = best_so_far_accuracy;
			best_features = current_set_of_features;
		}
		else
		{
			cout << "(Warning, accuracy, has decreased! Continuing search in case of local maxima)" << endl;
		}
		cout << "Feature set {";
		for (int p = 0; p < current_set_of_features.size() - 1; p++)
		{
			cout << current_set_of_features.at(p) << ",";
		}
		cout << current_set_of_features.at(current_set_of_features.size() - 1);
		cout <<"} was best, accuracy is ";
		cout << best_so_far_accuracy * 100 << "%" << endl;
		cout << endl;
	}
	cout << "Finished search!! The best feature subset is {";
	for (int p = 0; p < best_features.size() - 1; p++)
	{
		cout << best_features.at(p) << ",";
	}
	cout << best_features.at(best_features.size() - 1);
	cout << "}, which has an accuracy of " << total_accuracy * 100 << "%";
	cout << endl;
}

#endif
