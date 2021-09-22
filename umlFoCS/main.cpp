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

	generateNthString(v, 39);

	return 0;
}

//int layer(int n, vector<int> v) {
//
//	int i = 0;
//
//	while (n > pow(i, 2)) {
//
//		if (i == 0) {
//			n = n - 1;
//		} else if (i == 1) {
//			n = n - 2;
//		} else {
//			n = n - pow(i, 2);
//		}
//		i++;
//
//	}
//
//	return i;
//
//}

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

	/*for (int i = 0; i < layer.size(); i++) {

		layer.at(i).push_front( (i/v.size()) % v.size());

	}*/


	//for (int i = 0; i < layerSize; i++) {

	//	for (int j = 0; j < v.size(); j++) {

	//		list<int> temp(layer.at(i));
	//		temp.push_back(v.at(j));
	//		layer.push_back(temp);
	//		//layer.at(i).push_front(v.at(j));
	//		cout << "layer size: " << layerSize;
	//		cout << ", n: " << n << ", i: " << i << ", j: " << j << ", pushing back: " << v.at(j) << endl;

	//	}

	//}

	/*layerSize = layer.size();*/

	/*layerSize = layer.size();*/

	/*int count = 0;
	while (layer.size() < pow(layerSize, 2)) {

		list<int> temp;
		temp.push_back(v.at(count % v.size()));

		cout << "current position: " << count << ", pushing: " << v.at(count % v.size()) << endl;

		layer.push_back(temp);
		count++;

	}

	cout << "layersize wtf: " << layer.size() << endl;

	for (int i = 0; i < layer.size(); i++) {

		int index = (i % (layer.size() / v.size())) % v.size();

		cout << "n: " << n << ", i: " << i << ", index: " << index << ", pushing: " << v.at(index) << endl;

		layer.at(i).push_front(v.at((i / v.size()) % v.size()));

	}*/



	//for (int i = 0; i < layerSize; i++) {

	//	for (int j = 0; j < layerSize; j++) {

	//		layer.push_back(layer.at(j));

	//	}

	//}

	//for (int i = 0; i < layer.size(); i++) {

	//	/*if (i < layer.size() / 2)
	//		layer.at(i).push_front(0);
	//	else
	//		layer.at(i).push_front(1);*/

	//	/*if (i == 0)
	//	{
	//		layer.at(i).push_front(v.at(0));
	//	}
	//	else {

	//		int push = v.at(i/v.size() % v.size());
	//		layer.at(i).push_front(push);
	//	}*/

	//	layer.at(i).push_front(v.at(i/v.size()));

	//}
	
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
	//cout << "i: " << i << endl;

	vector<list<int>> layer;

	/*list<int> f;
	f.push_back(0);
	list<int> s;
	s.push_back(1);*/

	for (int j = 0; j < v.size(); j++) {

		list<int> temp;
		temp.push_back(v.at(j));
		layer.push_back(temp);

	}

	//layer.push_back(f);
	//layer.push_back(s);

	genBinString(layer, i, v);

	list<int> temp;

	//temp = layer.at(n);

	int testc = 0;

	for (auto s : layer.at(n)) {

		cout << s << "";
	}
	cout << endl;

	//cout << "count of elements: " << testc << endl;

	/*cout << "n:" << n;

	for (auto s : layer.at(n)) {

		cout << s;

	}*/
	






}