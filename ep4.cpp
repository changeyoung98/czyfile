#include <sstream>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <set>
#include <map>
#include <list>
using namespace std;

int main() {
	map<string, int>::iterator it;
	map<string, int>::iterator iter;
	map<string, int> Suff;
	ifstream infile("dictionary.txt");
	string line;
	int n;
	cout << "Please enter the number: " << endl;
	cin >> n;
	while (!infile.eof()) {
		getline(infile, line);
		if (line.size() >= n) {
			int pos = line.size() - n;
			string suf = line.substr(pos, n);
			Suff[suf]++;
		}
	}
	set<int> ss;
	for (it = Suff.begin(); it != Suff.end();it++) {
		ss.insert(it->second);
	}
	set<int>::iterator ite;
	int k = 0;
	stack<string> stac;
	for (ite = ss.begin(); ite != ss.end(); ite++) {
		if (k != ss.size() - 10) {
			k += 1;
		}
		else {
			for (iter = Suff.begin(); iter != Suff.end(); iter++) {
				if (iter->second == *ite) {
					stac.push(iter->first);
				}
			}
		}
	}
	for (int i = 0; i <= 9; i++) {
		cout<< stac.top()<<":"<<Suff[stac.top()] << endl;
		stac.pop();
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
		int pos = line2.size() - n;
		if (line2.size() >= n && line2.substr(pos, n) == suffix) {
			st.push(line2);
		}
		}
	int siz = st.size();
	for (int i=0;i<=siz-1;i++) {
		cout<< st.top() << endl;
		st.pop();
	}
	return 0;
}