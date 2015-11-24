#ifndef ACCURACY_H
#define ACCURACY_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
using namespace std;

float euclidean_distance(vector <float> a, 
						 vector <float> b,
						 vector <int> current_features,
						 int j)
{
	float x = 0;
	for (int i = 0; i < current_features.size(); i++)
	{
		//cout << pow(a.at(current_features.at(i)) - b.at(current_features.at(i)), 2) << endl;
		x += (pow(a.at(current_features.at(i)) - b.at(current_features.at(i)), 2));
	}
	x += (pow(a.at(j) - b.at(j), 2));
	//cout << "X = " << x << " sqrt(X) = " << sqrt(x) << endl;
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
	float correct_classifications = 0;
	vector <float> c1;
	vector <float> c2;
	for (int i = 0; i < data.size(); i++)				//iterate through all data
	{
		vector <float> test_data = data.at(i);			//set the leave-one-out test data
		for (int k = 0; k < data.size(); k++)			//iterate through all data
		{
			if(data.at(k) != data.at(i))				//get distance between current data & test
			{
				float distance = euclidean_distance(test_data, data.at(k), current_features, j);
				if (data.at(k).at(0) == 1)				//if current data is class 1, record distance in class 1 distance bin
				{
					c1.push_back(distance);
				}
				else									//if current data is class 2, record distance in class 2 distance bin
				{
					c2.push_back(distance);
				}
			}
		}
		if ((mean(c1) < mean(c2)) && (test_data.at(0) == 1))
		{
			correct_classifications++;
		}
		else if ((mean(c2) < mean(c1)) && (test_data.at(0) == 2))
		{
			correct_classifications++;
		}
		c1.clear();
		c2.clear();
	}
	return correct_classifications / (float)data.size();
}

#endif
