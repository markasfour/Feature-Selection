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
	int x = 0;
	for (int i = 0; i < current_features.size(); i++)
	{
		x += (pow(a.at(current_features.at(i)) - b.at(current_features.at(i)), 2));
	}
	x += (pow(a.at(j) - b.at(j), 2));
	return sqrt(x);
}

float mean(vector <float> x)
{
	float sum = 0;
	for (int i = 0; i < x.size(); i++)
	{
		sum += x.at(i);
	}
	return sum / x.size();
}

float leave_one_out_cross_validation(vector < vector <float> > data, 
									 vector <int> current_features, 
									 int j)
{
	//return rand();
	float correct_classifications = 0;
	vector <float> c1;
	vector <float> c2;
	for (int i = 0; i < data.size(); i++)
	{
		vector <float> test_data = data.at(i);
		for (int k = 0; k < data.size(); k++)
		{
			if(data.at(k) != data.at(i))
			{
				float distance = euclidean_distance(test_data, data.at(k), current_features, j);
				if (data.at(k).at(0) == 1)
				{
					c1.push_back(distance);
				}
				else
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
	return correct_classifications / data.size();
}

#endif
