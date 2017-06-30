#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include <thread>
#include<Windows.h>
using namespace std;


void thread1(vector<string> Orderid,vector<string> Side,vector<string> Symbol,vector<double> Price,vector<double> Quantity) {
	cout << "Please enter an order(elements splited by " "): " << endl;
	string order;
	getline(cin, order);
	string id;
	string side;
	string symbol;
	double price;
	double quant;
	stringstream ss;
	ss << order;
	ss >> id >> side >> symbol >> price >> quant;
	Orderid.push_back(id);
	Side.push_back(side);
	Symbol.push_back(symbol);
	Price.push_back(price);
	Quantity.push_back(quant);
}                      //the thread to add orders randomly
int main() {
	// build the containers
	vector<string> Orderid;
	vector<string> Side;
	vector<string> Symbol;
	vector<double> Price;
	vector<double> Quantity;
	map<string,double> Exchange_qty;
	map<string, double> Exchange_prc;
	map<string, double> Order_qty;
	map<string, double> Order_prc;
	map<string, map<string,string>> Ask;
	map<string, map<string, string>> Bid;
	map<string, string> AAPL;
	map<string, string> GOOG;
	thread t(thread1,Orderid, Side, Symbol, Price, Quantity);
	t.detach();
	//deal with the orders
	//store them in containers
	ifstream order("Orders_new.csv");
	string line1;
	getline(order, line1);
	while (!order.eof()) {
		getline(order, line1);
		string orderid;
		string side_o;
		string symbol_o;
		string price_o;
		string quantity_o;
		int pos0 = line1.find(',');
		if (pos0 != -1) {
			orderid = line1.substr(0, pos0);
			Orderid.push_back(orderid);
			int pos1 = line1.substr(pos0 + 1, line1.size() - pos0).find(',');
			side_o = line1.substr(pos0 + 1, pos1);
			Side.push_back(side_o);
			int pos2 = line1.substr(pos0 + pos1 + 2, line1.size() - pos0 - pos1).find(',');
			symbol_o = line1.substr(pos0 + pos1 + 2, pos2);
			Symbol.push_back(symbol_o);
			int pos3 = line1.rfind(',');
			price_o = line1.substr(pos0 + pos1 + pos2 + 3, pos3 - pos2 - pos1 - pos0 - 3);
			quantity_o = line1.substr(pos3 + 1, line1.size() - 1);
			stringstream tt1;
			tt1 << quantity_o;
			double quantity;
			tt1 >> quantity;
			Quantity.push_back(quantity);
			stringstream tt2;
			tt2 << price_o;
			double price_ord;
			tt2 >> price_ord;
			Price.push_back(price_ord);

		}
		else {
			continue;
		}
	}
	//read through the quotes and eat orders
	ifstream quote("Quotes.csv");
	ofstream outfile("show.txt", 'w');
	string line;
	getline(quote, line);
	//deal with quotes
	while (!quote.eof()) {
		getline(quote, line);
		string exchange;
		string side_q;
		string symbol_q;
		string size_q;
		string price_q;
		int pos0 = line.find(',');
		int pos1 = line.find(',');
		int pos2 = line.rfind(',');
		int pos3 = line.rfind(',');
		if (pos0 != -1) {
			exchange = line.substr(0, pos0);
			int pos1 = line.substr(pos0 + 1, line.size() - pos0).find(',');
			side_q = line.substr(pos0 + 1, pos1);
			int pos2 = line.substr(pos0 + pos1 + 2, line.size() - pos0 - pos1 - 1).find(',');
			symbol_q = line.substr(pos0 + pos1 + 2, pos2);
			int pos3 = line.rfind(',');
			size_q = line.substr(pos0 + pos1 + pos2 + 3, pos3 - pos2 - pos1 - pos0 - 3);
			price_q = line.substr(pos3 + 1, line.size() - 1);
			stringstream ss1;
			ss1 << size_q;
			double size;
			ss1 >> size;
			stringstream ss2;
			ss2 << price_q;
			double price_quo;
			ss2 >> price_quo;
			if (side_q == "Ask") {
				for (int i = 0; i < Orderid.size(); i++) {
					if (Side[i] == "Buy" && Symbol[i] == symbol_q && Price[i] >= price_quo && Quantity[i] >= size) {
						Quantity[i] -= size;
						Exchange_qty[exchange] += size;
						Exchange_prc[exchange] += size*price_quo;
						Order_qty[Orderid[i]] += size;
						Order_prc[Orderid[i]] += size*price_quo;
						price_q = "";
					}  //for the successful deal,clear the quotes
				}
				if (price_q != "") {
					Ask[symbol_q][exchange] = size_q + "@" + price_q;
					map<string, map<string, string>>::iterator it;
					for (it = Ask.begin(); it != Ask.end(); it++) {
						outfile << "Ask for " << it->first << endl;
						outfile << "    NYSE    " << "   " << "    NASDAQ    " << "  " << "    IEX    " << endl;
						map<string, string > ::iterator i;
						vector<int> cur;
						int tot_size = 0;
						for (i = it->second.begin(); i != it->second.end(); i++) {
							outfile << i->second << "\t";
							string screen = i->second;
							int posi=screen.find('@');
							string si = screen.substr(0, posi);
							stringstream pp;
							pp << si;
							int siz;
							pp >> siz;
							cur.push_back(siz);
							tot_size += siz;
						}  //for the uncleared quote,print the book
						outfile << "\n" << endl;
						outfile << "Split the orders: " << endl;
						for (int b = 0; b < Quantity.size(); b++) {
							outfile << Orderid[b] << ":  ";
							for (int m = 0; m < cur.size(); m++) {
								outfile << cur[m] / double(tot_size) *Quantity[b] << "   ";
							}
							outfile << '\n' << endl;
						}
					}

				}
			}
			else {    //do the same thing for Bid
				for (int i = 0; i < Orderid.size(); i++) {
					if (Side[i] == "Sell" && Symbol[i] == symbol_q && Price[i] <= price_quo && Quantity[i] >= size) {
						Quantity[i] -= size;
						Exchange_qty[exchange] += size;
						Exchange_prc[exchange] += size*price_quo;
						Order_qty[Orderid[i]] += size;
						Order_prc[Orderid[i]] += size*price_quo;
						price_q = "";
					}
				}
				if (price_q != "") {
					Bid[symbol_q][exchange] = size_q + "@" + price_q;
					map<string, map<string, string>>::iterator it;
					for (it = Bid.begin(); it != Bid.end(); it++) {
						vector<int> curr;
						int tot_size = 0;
						outfile << "Bid for " << it->first << endl;
						outfile << "    NYSE    " << "   " << "    NASDAQ    " << "  " << "    IEX    " << endl;
						map<string, string > ::iterator i;
						for (i = it->second.begin(); i != it->second.end(); i++) {
							outfile << i->second << "\t";
							string screen = i->second;
							int posi = screen.find('@');
							string si = screen.substr(0, posi);
							stringstream pp;
							pp << si;
							int siz;
							pp >> siz;
							curr.push_back(siz);
							tot_size += siz;
						}
						outfile << "\n" << endl;
						outfile << "Split the orders: " << endl;
						for (int b = 0; b < Quantity.size(); b++) {
							outfile << Orderid[b] << ":  ";
							for (int m = 0; m < curr.size(); m++) {
								outfile << curr[m] / double(tot_size) *Quantity[b] << "   ";
							}
							outfile << '\n' << endl;
						}
					}
				}
			}
		}
		else {
			continue;
		}
	}
	//print the final analysis
	cout << "Quantity and average price on each exchange: " << endl;
	map<string, double > ::iterator ite;
	for (ite = Exchange_prc.begin(); ite != Exchange_prc.end(); ite++) {
		cout << ite->first << ":" << Exchange_prc[ite->first] / Exchange_qty[ite->first] << endl;
	}
	cout << "Quantity and average price on orders: " << endl;
	map<string, double > ::iterator iter;
	for (iter = Order_prc.begin(); iter != Order_prc.end(); iter++) {
		cout << iter->first << ":" << Order_prc[iter->first] / Order_qty[iter->first] << endl;
	}
	return 0;
}

