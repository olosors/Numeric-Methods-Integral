#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <exception>
#include <sstream>

using namespace std;

struct Interval
{
	double start, end;
	double diapason;
};

struct Answer
{
	double J;
	double R;
};

double f(const double& x) {
	return exp(-(x * x)) / x;
}

Answer Simpson(const Interval& I) {
	cout << "enter the n = ";
	int n;
	cin >> n;
	double h = (I.end - I.start) / n, firstx = I.start;
	vector<double> x;
	for (int i = 0; i <= n; ++i) {
		x.push_back(firstx);
		firstx += h;
	}
	double Sum_of_Even = 0;
	for (int i = 2; i <= n - 2; i += 2) {
		Sum_of_Even += f(x[i]);
	}
	double Sum_of_Odd = 0;
	for (int i = 1; i <= n - 1; i += 2) {
		Sum_of_Odd += f(x[i]);
	}
	double M4 = exp(-(x[0] * x[0])) * (16 * x[0] * x[0] * x[0] - 8 * x[0] + 32 / (x[0] * x[0] * x[0]));
	return { h * (f(x[0]) + f(x[n]) + 4 * Sum_of_Odd + 2 * Sum_of_Even) / 3, h * h * h * h * M4 / 180 };
}

Answer LeftP(const Interval& I) {
	cout << "enter the n = ";
	int n;
	cin >> n;
	double h = (I.end - I.start) / n, firstx = I.start;
	vector<double> x;
	for (int i = 0; i <= n; ++i) {
		x.push_back(firstx);
		firstx += h;
	}
	double Sum_of_LP = 0;
	for (int i = 0; i < n; ++i) {
		Sum_of_LP += f(x[i]);
	}
	double M1 = abs(-2 * exp(-(x[0] * x[0])) - exp(-(x[0] * x[0])) / x[0] / x[0]);
	return { h * Sum_of_LP, h * M1 / 2 };
}

Answer Recht(const Interval& I) {
	cout << "enter the n = ";
	int n;
	cin >> n;
	double h = (I.end - I.start) / n, firstx = I.start;
	vector<double> x;
	for (int i = 0; i <= n; ++i) {
		x.push_back(firstx);
		firstx += h;
	}
	double Sum_of_LP = 0;
	for (int i = 1; i <= n; ++i) {
		Sum_of_LP += f(x[i]);
	}
	double M1 = abs(-2 * exp(-(x[0] * x[0])) - exp(-(x[0] * x[0])) / x[0] / x[0]);
	return { h * Sum_of_LP, h * M1 / 2 };
}
 
Answer Middle(const Interval& I) {
	Answer J_l = LeftP(I), J_r = Recht(I);
	return { (J_l.J + J_r.J) / 2, J_l.R };
}

#include "Header.h"
ostream& operator<< (ostream& output, Answer& answer) {
	output << "result: J = " << answer.J << endl;
	output << "Die Deutlichkeit: R = " << answer.R << endl;
	return output;
}


int main() {
	string command;
	cout << "Possible Methodcommands: simpson, leftP, rightP, mitte" << endl;
	cout << "Enter the type of Integral: ";
	while (getline(cin, command)) {
		if (command == "simpson") {
			try {
				Interval interval;
				interval.end = 2;
				interval.start = 1;
				Answer answer = Simpson(interval);
				cout << answer;
			}
			catch (exception& e) {
				cout << "something wrong" << endl;
			}
		}
		else {
			if (command == "leftP") {
				try {
					Interval interval;
					interval.end = 2;
					interval.start = 1;
					Answer answer = Recht(interval);
					cout << answer;
				}
				catch (exception& e) {
					cout << "something wrong" << endl;
				}
			}
			else {
				if (command == "rightP") {
					try {
						Interval interval;
						interval.end = 2;
						interval.start = 1;
						Answer answer = LeftP(interval);
						cout << answer;
					}
					catch (exception& e) {
						cout << "something wrong" << endl;
					}
				}
				else {
					if (command == "mitte") {
						Interval interval;
						interval.end = 2;
						interval.start = 1;
						Answer answer = Middle(interval);
						cout << answer;
					}
					else {
						if (command == "exit") {
							break;
						}
					}
				}
			}
		}
	}
	return 0;
}