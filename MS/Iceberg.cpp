#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

int main() {
	cout << "Please enter the amount of the order: ";  //receive a large order
	int order_amount;
	cin >> order_amount;
	cout << endl;
    //build some containers 
	//split the time every 15 minutes so the size is 28
	int period_amt[28] = { 0 };
	double period_price[28] = { 0 };
	int number[28] = { 0 };
	int ex_amount = 0;
	ifstream infile("600690.iceberg.csv");
	string line;
	string date;
	getline(infile, line);
	//deal with the data
	while (!infile.eof()) {
		getline(infile,line);
		string day;
		string time;
		string price;
		string amount;
		int pos0 = line.find(' ');
		int pos1 = line.find(',');
		int pos2 = line.rfind(',');
		if (pos1 != -1) {
			day = line.substr(0, pos0);
			time = line.substr(pos0+1, pos1-pos0-1);
			price = line.substr(pos1+1, pos2-pos1-1);
			amount = line.substr(pos2+1 , line.size() - 1);
		}
		else {
			continue;
		}
		if (day != date) {
			ex_amount = 0;  //if the day changes, the amount goes back to 0
		}
		date = day;
		stringstream ss;
		ss << time;
		int hour;
		char mark;
		int minute;
		int second;
		ss >> hour >> mark >> minute >> mark >> second;
		int index = (hour - 9) * 4 + minute / 15;
		stringstream tt;
		tt << amount;
		int num;
		int cur_amount;
		tt >> cur_amount;
		num = cur_amount - ex_amount;  //the amount for the day 
		period_amt[index] += num;    //add together
		ex_amount = cur_amount;
		stringstream uu;
		uu << price;
		double cur_price;
		uu >> cur_price;
		period_price[index] += cur_price;
		number[index] += 1;
	}
	int total_amount = 0;
	//print the results
	for (int i = 0; i <= 27; i++) {
		total_amount+= period_amt[i];
	}
	int total_price = 0;
	cout << "Method for splitting: " << endl;
	for (int i = 0; i <= 27; i++) {
		int h = i / 4 + 9;
		int min = (i % 4)*15;
		string time;
		stringstream ss;
		ss << h;
		string hr;
		ss >> hr;
		if (min == 0) {
			time = hr + ":00";
		}
		else {
			stringstream tt;
			tt << min;
			string mt;
			tt >> mt;
			time = hr + ":" + mt;
		}
		double piece = double(period_amt[i]) / total_amount*order_amount;
		double piece_price = period_price[i] / number[i];
		total_price += piece*piece_price;
		cout << time << "   "<< piece << "   " << piece_price << endl;
	}
	cout << "Total price: " << total_price << "   " << "Average_price: " << double(total_price)/order_amount << endl;


	return 0;
}