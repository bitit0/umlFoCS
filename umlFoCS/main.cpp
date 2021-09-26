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

	// Dozen Example DFAs

	DFA<char>* binaryString = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'f'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a' || qi == 'b')
				if (c == 0 || c == 1) return 'b';
			return 'f';
		},
		[](char qi) { return (qi == 'b'); }
	);
	DFA<char>* onlyOnes = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'f'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a' || qi == 'b')
				if (c == 1) return 'b';
			return 'f';
		},
		[](char qi) { return (qi == 'b'); }
		);

	DFA<char>* onlyZeros = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'f'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a' || qi == 'b')
				if (c == 0) return 'b';
			return 'f';
		},
		[](char qi) { return (qi == 'b'); }
		);
		
	DFA<char>* alternatingBinary = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'f'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return 'b';
				if (c == 1) return 'c';
				return 'f';
			}
			if (qi == 'b') {
				if (c == 1) return 'c';
				return 'f';
			}
			if (qi == 'c') {
				if (c == 0) return 'b';
				return 'f';
			}
		},
		[](char qi) { return (qi == 'b') || (qi == 'c'); }
		);

	DFA<char>* evenLength = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				return 'b';
			}
			else {
				return 'a';
			}
		},
		[](char qi) { return (qi == 'a'); }
		);

	DFA<char>* oddNum = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return 'a';
				if (c == 1) return 'b';
			}
			if (qi == 'b') {
				if (c == 0) return 'a';
				if (c == 1) return 'b';
			}
		},
		[](char qi) { return (qi == 'b'); }
		);
	DFA<char>* evenNum = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return 'a';
				if (c == 1) return 'b';
			}
			if (qi == 'b') {
				if (c == 0) return 'a';
				if (c == 1) return 'b';
			}
		},
		[](char qi) { return (qi == 'a'); }
		);
	DFA<char>* containsOne = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return 'a';
				if (c == 1) return 'b';
			}
			if (qi == 'b') {
				if (c == 0 || c == 1) return 'b';
			}
		},
		[](char qi) { return (qi == 'b'); }
		);

	// 4 more

	DFA<char>* containsZero = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return 'b';
				if (c == 1) return 'a';
			}
			if (qi == 'b') {
				if (c == 0 || c == 1) return 'b';
			}
		},
		[](char qi) { return (qi == 'b'); }
		);
	DFA<char>* contains0011 = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd') || (x == 'e'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				return c == 1 ? 'a' : 'b';
			}
			if (qi == 'b') {
				return c == 1 ? 'a' : 'c';
			}
			if (qi == 'c') {
				return c == 1 ? 'd' : 'b';
			}
			if (qi == 'd') {
				return c == 1 ? 'e' : 'a';
			}
			if (qi == 'e') {
				return 'e';
			}
		},
		[](char qi) { return (qi == 'e'); }
		);

	// 2 more
	DFA<char>* startsOneEndsZero = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'f'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				return c == 1 ? 'b' : 'f';
			}
			if (qi == 'b') {
				return c == 1 ? 'b' : 'c';
			}
			if (qi == 'c') {
				return c == 1 ? 'b' : 'c';
			}
			if (qi == 'f') return 'f';
		},
		[](char qi) { return (qi == 'c'); }
		);
	DFA<char>* threeConsecutiveZeros = new DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				return c == 1 ? 'a' : 'b';
			}
			if (qi == 'b') {
				return c == 1 ? 'a' : 'c';
			}
			if (qi == 'c') {
				return c == 1 ? 'a' : 'd';
			}
			if (qi == 'd') return 'd';
		},
		[](char qi) { return (qi == 'd'); }
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