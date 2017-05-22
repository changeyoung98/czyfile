#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

bool solve(int row, int col, vector <vector<int>> &m) {
	int w = m.size() - 1;
	int l = m[0].size() - 1;
	if (row == w&&col == l) {
		return true;
	}
	if (row > w || row < 0 || col>l || col < 0) {
		return false;
	}
	if (m[row][col] != 0) {
		return false;
	}
	m[row][col] = 2;
	if (solve(row - 1, col, m) == true) {
		return true;
	}
	if (solve(row, col + 1, m) == true) {
		return true;
	}
	if (solve(row + 1, col, m) == true) {
		return true;
	}
	if (solve(row, col - 1, m) == true) {
		return true;
	}
	m[row][col] = 3;
	return false;
}


int main() {
	ifstream infile("mg2.txt");
	int w, l;
	string line;
	getline(infile, line);
	stringstream ss;
	ss << line;
	ss >> w >> l;
	vector<vector<int>> maze;
	for (int i = 0; i < w; i++) {
		vector<int> ww;
		getline(infile, line);
		stringstream tt;
		tt << line;
		for (int j = 0; j < l; j++) {
			int ll;
			tt >> ll;
			ww.push_back(ll);
		}
		maze.push_back(ww);
	}

	solve(0, 0, maze);
	maze[w - 1][l - 1] = 2;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < l; j++) {
			if (maze[i][j] == 3) {
				maze[i][j] = 0;
			}
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}