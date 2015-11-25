#ifndef ACCURACY_H
#define ACCURACY_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
using namespace std;

float minimum(vector <float> x)
{
	if (x.size() == 0)
		return 9999;
	float m = x.at(0);
	for (int i = 0; i < x.size(); i++)
	{
		if (x.at(i) < m)
		{
			m = x.at(i);
		}
	}
	return m;
}

float euclidean_distance(vector <float> a, 
						 vector <float> b,
						 vector <int> current_features,
						 int j)
{
	//cout << a.at(1) << " , " << b.at(1) << endl;
	float x = 0;
	for (int i = 0; i < current_features.size(); i++)
	{
		x += (pow(a.at(current_features.at(i)) - b.at(current_features.at(i)), 2));
	}
	x += (pow(a.at(j) - b.at(j), 2));
	//cout << x << " , " << sqrt(x) << endl;
	return sqrt(x);
}

float mean(vector <float> x)
{
	float sum = 0;
	for (int i = 0; i < x.size(); i++)
	{
		sum += x.at(i);
	}
	if (sum == 0)
	{
		return 0;
	}
	return sum / (float)x.size();
}

float leave_one_out_cross_validation(vector < vector <float> > data, 
									 vector <int> current_features, 
									 int j)
{
	//cout << endl;
	float correct_classifications = 0;
		
	for (int i = 0; i < data.size(); i++)				//iterate through all data
	{
		vector <float> test_data = data.at(i);			//set the leave-one-out test data
		float min_dist = 9999;
		vector <float> min_neighbor;

		for (int k = 0; k < data.size(); k++)			//iterate through all data to get 1 nearest neighbor
		{
			if(k != i)									//get distance between current data & test
			{
				float distance = euclidean_distance(test_data, data.at(k), current_features, j);
				//cout << k << " -> " << distance << endl << endl;
				if (distance < min_dist)				//get min distance
				{
					min_dist = distance;
					min_neighbor = data.at(k);
				}
			}	
		}	
		if (min_neighbor.at(0) == 1 && test_data.at(0) == 1)
		{
			correct_classifications++;
		}
		else if (min_neighbor.at(0) == 2 && test_data.at(0) == 2)
		{
			correct_classifications++;
		}
	}
	//cout << correct_classifications << endl << endl;
	return correct_classifications / (float)data.size();
}

#endif
