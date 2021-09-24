#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

using namespace std;

//int layer(int n);

void generateNthString(vector<int> v, int n);

void genBinString(vector<vector<int>>& layer, int n, vector<int> v);

int main() {

	vector<int> v = {0, 1, 2}; // alphabet

	vector<int> s1; // string

	generateNthString(v, 40);

	return 0;
}

// e,
// 0, 1, 
// 00, 01, 10, 11,
// 000, 001, 010, 011, 100, 101, 110, 111,

void genBinString(vector<list<int>>& layer, int n, vector<int> v) {

	if (n == 1) return;

	int layerSize = layer.size();

	for (int i = 0; i < v.size()-1; i++) {

		for (int j = 0; j < layerSize; j++) {

			layer.push_back(layer.at(j));
		}

	}

	layerSize = layer.size();

	for (int i = 0; i < layerSize; i++) {

		layer.at(i).push_front(i / (layerSize / v.size()));

	}

	genBinString(layer, n - 1, v);

}


void generateNthString(vector<int> v, int n) {

	//cout << "vsize: " << v.size() << endl;

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

	//cout << "layer feedback: " << endl;

	while (n >= pow(v.size(), i)) {

		//cout << "n: " << n << "; n >= " << v.size() << "^" << i << "?; " << (n >= pow(v.size(), i));

		n = n - pow(v.size(), i);
		i++;

		//cout << "; new n: " << n << ", new i: " << i << endl;


	}

	vector<list<int>> layer;

	for (int j = 0; j < v.size(); j++) {

		list<int> temp;
		temp.push_back(v.at(j));
		layer.push_back(temp);

	}

	genBinString(layer, i, v);

	list<int> temp;


	int testc = 0;

	for (auto s : layer.at(n)) {

		cout << s << "";
	}
	cout << endl;

	






}