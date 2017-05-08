#include <sstream>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <map>
#include <list>
using namespace std;

int main() {
	map<string, int>::iterator it;
	map<string, int> Suff;
	ifstream infile("dictionary.txt");
	string line;
	int n;
	cout << "Please enter the number: " << endl;
	cin >> n;
	while (!infile.eof()) {
		getline(infile, line);
		//cout << line << endl;
		if (line.size() >= n) {
			int pos = line.size() - n;
			string suf = line.substr(pos, n);
			Suff[suf]++;
		}
	}
	list<map<string, int>> l;
	vector<int> vec;
	for (it = Suff.begin(); it != Suff.end();it++) {
		vec.push_back(it->second);
	}


	string suffix;
	cout << "Please enter the suffix: " << endl;
	cin >> suffix;
	cout << Suff[suffix] << endl;
	stack<string> st;
	ifstream infile2("dictionary.txt");
	string line2;
	while (!infile2.eof()) {
		getline(infile2, line2);
		//cout << line << endl;
		int pos = line2.size() - n;
		if (line2.size() >= n && line2.substr(pos, n) == suffix) {
			st.push(line2);
		}
		}
	for (int i=0;i<=st.size()-1;i++) {
		cout<< st.top() << endl;
		st.pop();
	}
	return 0;
}