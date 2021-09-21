#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

using namespace std;

int layer(int n);

void generateNthString(vector<int> v, int n);

void genBinString(vector<vector<int>>& layer, int n);

int main() {

	vector<int> v = {0, 1}; // alphabet

	vector<int> s1; // string

	generateNthString(v, 3);

	return 0;
}

int layer(int n) {

	int i = 0;

	while (n > pow(i, 2)) {

		if (i == 0) {
			n = n - 1;
		} else if (i == 1) {
			n = n - 2;
		} else {
			n = n - pow(i, 2);
		}
		i++;

	}

	return i;

}

// e,
// 0, 1, 
// 00, 01, 10, 11,
// 000, 001, 010, 011, 100, 101, 110, 111,

void genBinString(vector<list<int>>& layer, int n) {

	if (n == 1) return;

	int layerSize = layer.size();


	for (int i = 0; i < layerSize; i++) {

		layer.push_back(layer.at(i));

	}

	for (int i = 0; i < layer.size(); i++) {

		if (i < layer.size() / 2)
			layer.at(i).push_front(0);
		else
			layer.at(i).push_front(1);

	}
	
	genBinString(layer, n - 1);


}


void generateNthString(vector<int> v, int n) {

	if (n == 0) {

		cout << "e";
		return;
	}

	//cout << "n: " << n << endl;

	if (n <= v.size()) {

		cout << v[--n];
		return;
	}

	// get layer

	int i = 0; // layer count

	while (n >= pow(2, i)) {

		n = n - pow(2, i);
		i++;

	}
	//cout << "i: " << i << endl;

	vector<list<int>> layer;

	list<int> f;
	f.push_back(0);
	list<int> s;
	s.push_back(1);
	
	layer.push_back(f);
	layer.push_back(s);

	genBinString(layer, i);

	list<int> temp;

	temp = layer.at(n);

	for (auto s : temp) {

		cout << s;

	}
	






}