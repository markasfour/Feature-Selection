#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	cout << "Welcome to Mark Asfour's Feature Selection Algorithm." << endl;
	cout << "Type in the name of the file to test: ";
	string filename;
	cin >> filename;
	
	string line;
	ifstream file(filename.c_str());
	if (file.is_open())
	{
		while (getline(file, line))
		{
			cout << line << endl;
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	return 0;
}
