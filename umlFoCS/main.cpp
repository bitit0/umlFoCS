#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <functional>

using namespace std;

void generateNthString(vector<int> v, int n);

void genBinString(vector<vector<int>>& layer, int n, vector<int> v);

template<typename State>
class DFA {
public:
	//DFA(bool (*Qp)(State), State q0p, State (*Dp)(State, int), bool (*Fp)(State)): Q(Qp), q0(q0p), D(Dp), F(Fp) {};
	DFA(function<bool(State)> Qp, State q0p, function<State(State, int)> Dp, function<bool(State)> Fp): Q(Qp), q0(q0p), D(Dp), F(Fp) {};
	//bool (*Q)(State); // Set of states
	//State q0; // Start state
	//State (*D)(State, int); // Transition
	//bool (*F)(State); // Accepting states?
	function<bool(State)> Q;
	State q0;
	function<State(State, int)> D;
	function<bool(State)> F;

};

DFA<char> onlyCharDFA(char in);

int main() {

	vector<int> v = {0, 1}; // alphabet

	vector<int> s1; // string

	generateNthString(v, 39);

	DFA<char>* onlyEmptyString = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[](char qi, int c) { return 'b'; },
		[](char qi) { return qi == 'a'; }
	);

	DFA<char>* acceptNoStrings = new DFA<char>(
		[](char x) { return x == 'a'; },
		'a',
		[](char qi, int c) { return 'a'; },
		[](char qi) { return false; }
	);

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

DFA<char> onlyCharDFA(char in) {

	return DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[in](char qi, int c) { if (c == in) return 'b'; },
		[](char qi) { return qi == 'a'; }
		);

}