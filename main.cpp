#include <iostream>
#include "Link.h"
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
	vector<int> p;
	ifstream infile("file.txt");
	int number;
	while (!infile.eof())
	{
		infile >> number;
		p.push_back(number);
	}
	List list1(p);
	list1.printAll();
	return 0;
}
