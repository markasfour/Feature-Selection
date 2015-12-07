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

vector <int> forward_search(vector < vector <float> > data)
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
																j,
																true);
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
	return best_features;
}

vector <int> remove_feature(vector <int> f, int x)
{
	for (int i = 0; i < f.size(); i++)
	{
		if (f.at(i) == x)
		{
			f.erase(f.begin() + i);
			return f;
		}
	}
	return f;
}

void backwards_elimination(vector < vector <float> > data)
{
	vector <int> current_set_of_features;
	for (int i = 1; i < data.at(0).size(); i++)
	{
		current_set_of_features.push_back(i);
	}
	float total_accuracy = 0;
	vector <int> best_features;

	for (int i = 1; i < data.at(0).size() - 1; i++)
	{
		int feature_to_remove_at_this_level;
		float best_so_far_accuracy = 0;
		for (int j = 1; j < data.at(0).size(); j++)
		{
			if (intersect(current_set_of_features, j))
			{
				vector <int> temp_curr = remove_feature(current_set_of_features, j);
				cout << "Using feature(s) {";
				for (int p = 0; p < temp_curr.size() - 1; p++)
				{
					cout << temp_curr.at(p) << ",";
				}
				cout << temp_curr.at(temp_curr.size() - 1) << "} accuracy is ";
				float accuracy = leave_one_out_cross_validation(data,
																temp_curr,
																j,
																false);
				cout << accuracy << endl;
				if (accuracy > best_so_far_accuracy)
				{
					best_so_far_accuracy = accuracy;
					feature_to_remove_at_this_level = j;
				}
			}
		}

		current_set_of_features = remove_feature(current_set_of_features, feature_to_remove_at_this_level);
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
