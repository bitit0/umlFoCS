#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <functional>
#include <optional>

using namespace std;

void generateNthString(vector<int> v, int n);
void genBinString(vector<list<int>>& layer, int n, vector<int> v);

template<typename State>
class DFA {
public:
	DFA(function<bool(State)> Qp, State q0p, function<State(State, int)> Dp, function<bool(State)> Fp) : Q(Qp), q0(q0p), D(Dp), F(Fp) {};
	function<bool(State)> Q; // Set of states 
	State q0; // Start state
	function<State(State, int)> D; // Transition
	function<bool(State)> F; // Set of states 

};

bool acceptsString(DFA<char> d, list<int> l);
DFA<char> onlyCharDFA(char in);
void trace(DFA<char> automata, list<int> l);
optional<list<int>> DFAtoString(DFA<char> automata, vector<int> alphabet);
DFA<char> compDFA(DFA<char> automata);
//DFA<char> unionDFA(DFA<char> a1, DFA<char> a2);

int main() {

	vector<int> v = { 0, 1}; // alphabet

	generateNthString(v, 40);

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
				return c == 1 ? 'd' : 'c';
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
				//return c == 1 ? 'a' : 'b';
				if (c == 1) return 'a';
				if (c == 0) return 'b';
			}
			if (qi == 'b') {
				//return c == 1 ? 'a' : 'c';
				if (c == 1) return 'a';
				if (c == 0) return 'c';
			}
			if (qi == 'c') {
				//return c == 1 ? 'a' : 'd';
				if (c == 1) return 'a';
				if (c == 0) return 'd';
			}
			if (qi == 'd') return 'd';
			return 'a';
		},
		[](char qi) { return (qi == 'd'); }
		);

	/// //////////////////////// start of tests
	//////////////////////////////////////////////

	vector<list<int>> accept = { {0, 1}, {0, 1, 1}, {1, 0, 1}, {0, 1, 0, 1}, {1}, {1, 0, 0} };
	vector<list<int>> reject = { {1, 2}, {2, 3}, {4, 5}, {6, 7}, {8, 10}, {89, 91} };

	int total = 0;
	int fails = 0;

	// binary string
	for (auto c : accept) {
		total++;
		if (!acceptsString(*binaryString, c)) {
			fails++;
			cout << "binaryString accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*binaryString, c)) {
			fails++;
			cout << "binaryString reject fail." << endl;
		}
	}
	// only ones

	accept = { {1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1, 1}, {1}, {1, 1, 1} };
	reject = { {1, 0}, {0, 0}, {2, 0}, {0, 7}, {8, 10}, {89, 91} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*onlyOnes, c)) {
			fails++;
			cout << "onlyOnes accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*onlyOnes, c)) {
			fails++;
			cout << "onlyOnes reject fail." << endl;
		}
	}

	// only zeros
	accept = { {0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0, 0}, {0}, {0, 0, 0} };
	reject = { {1, 0}, {3, 0}, {2, 0}, {0, 7}, {8, 10}, {89, 91} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*onlyZeros, c)) {
			fails++;
			cout << "onlyZeros accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*onlyZeros, c)) {
			fails++;
			cout << "onlyZeros reject fail." << endl;
		}
	}
	// alternatingBinary

	accept = { {1, 0}, {1, 0, 1}, {0, 1, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}, {0, 1} };
	reject = { {1, 2}, {3, 0}, {2, 0}, {0, 7}, {8, 10}, {89, 91} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*alternatingBinary, c)) {
			fails++;
			cout << "alternatingBinary accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*alternatingBinary, c)) {
			fails++;
			cout << "alternatingBinary reject fail." << endl;
		}
	}

	// even length
	accept = { {1, 0}, {1, 0, 0, 0}, {0, 1, 0, 0, 1, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}, {0, 1} };
	reject = { {1, 2, 3}, {3, 0, 2}, {2, 8, 0}, {0, 7, 3, 9, 5}, {8, 10, 11}, {89, 91, 23, 85, 19, 12, 102} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*evenLength, c)) {
			fails++;
			cout << "evenLength accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*evenLength, c)) {
			fails++;
			cout << "evenLength reject fail." << endl;
		}
	}

	// contains one
	accept = { {1, 0}, {1, 0, 0, 0}, {0, 1, 0, 0, 1, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}, {0, 1} };
	reject = { {2, 2, 3}, {3, 0, 2}, {2, 8, 0}, {0, 7, 3, 9, 5}, {8, 10, 11}, {89, 91, 23, 85, 19, 12, 102} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*containsOne, c)) {
			fails++;
			cout << "containsOne accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*containsOne, c)) {
			fails++;
			cout << "containsOne reject fail." << endl;
		}
	}

	// contains zero
	accept = { {1, 0}, {1, 0, 0, 0}, {0, 1, 0, 0, 1, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}, {0, 1} };
	reject = { {2, 2, 3}, {3, 3, 2}, {2, 8, 3}, {3, 7, 3, 9, 5}, {8, 10, 11}, {89, 91, 23, 85, 19, 12, 102} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*containsZero, c)) {
			fails++;
			cout << "containsZero accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*containsZero, c)) {
			fails++;
			cout << "containsZero reject fail." << endl;
		}
	}

	// contains 0011
	accept = { {0, 0, 1, 1}, {1, 0, 0, 1, 1}, {1, 0, 0, 1, 1, 1}, {1, 0, 1, 0, 0, 1, 1}, {0, 1, 0, 1, 0, 0, 1, 1}, {0, 1, 0, 1, 1, 0, 0, 0, 1, 1} };
	reject = { {2, 2, 3}, {3, 0, 2}, {2, 8, 0}, {0, 7, 3, 9, 5}, {8, 10, 11}, {89, 91, 23, 85, 19, 12, 102} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*contains0011, c)) {
			fails++;
			cout << "contains0011 accept fail on ";
			for (auto w : c) {
				cout << w;
			}
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*contains0011, c)) {
			fails++;
			cout << "contains0011 reject fail." << endl;
		}
	}

	// starts one ends zero
	accept = { {1, 0}, {1, 0, 0, 0}, {1, 1, 0, 0, 1, 0}, {1, 0, 1, 0}, {1, 1, 0, 0}, {1, 0, 0, 0, 0} };
	reject = { {2, 2, 3}, {3, 0, 2}, {2, 8, 0}, {0, 7, 3, 9, 5}, {8, 10, 11}, {89, 91, 23, 85, 19, 12, 102} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*startsOneEndsZero, c)) {
			fails++;
			cout << "startsOneEndsZero accept fail on ";
			for (auto w : c) {
				cout << w;
			}
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*startsOneEndsZero, c)) {
			fails++;
			cout << "startsOneEndsZero reject fail." << endl;
		}
	}

	// three consecutive zeros
	accept = { {0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 0, 0, 0, 1}, {1, 1, 1, 0, 0, 0} };
	reject = { {2, 2, 3}, {3, 0, 2}, {2, 8, 0}, {0, 7, 3, 9, 5}, {8, 10, 11}, {89, 91, 23, 85, 19, 12, 102} };

	for (auto c : accept) {
		total++;
		if (!acceptsString(*threeConsecutiveZeros, c)) {
			fails++;
			cout << "threeConsecutiveZeros accept fail." << endl;
		}
	}

	for (auto c : reject) {
		total++;
		if (acceptsString(*threeConsecutiveZeros, c)) {
			fails++;
			cout << "threeConsecutiveZeros reject fail on ";
			for (auto w : c) {
				cout << w;
			}
			cout << endl;
		}
	}

	list<int> traceTest = { 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0 };

	trace(*startsOneEndsZero, traceTest);

	auto str = DFAtoString(*threeConsecutiveZeros, v).value_or(list<int>(7));

	for (auto s : str) {

		cout << s;

	}

	cout << endl;

	return 0;
}

// e,
// 0, 1, 
// 00, 01, 10, 11,
// 000, 001, 010, 011, 100, 101, 110, 111,

void genBinString(vector<list<int>>& layer, int n, vector<int> v) {

	if (n == 1) return;

	int layerSize = layer.size();

	for (int i = 0; i < v.size() - 1; i++) {

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

	int count = 0;

	return DFA<char>(
		[](char x) { return (x == 'a') || (x == 'b'); },
		'a',
		[in, &count](char qi, int c) { if (c == in && count == 0) { count++; return 'b'; } return 'a'; },
		[](char qi) { return qi == 'b'; }
	);

}

bool acceptsString(DFA<char> automata, list<int> l) {

	char qi = automata.q0;
	for (int curr : l) {

		qi = automata.D(qi, curr);

	}

	return automata.F(qi);
}

void trace(DFA<char> automata, list<int> l) {

	char qi = automata.q0;
	cout << "String: ";
	for (auto c : l) {

		cout << c;
	}
	cout << " -> ";
	for (int curr : l) {

		qi = automata.D(qi, curr);
		cout << qi << ", ";

	}
	cout << "\b\b \b" << endl;

}

optional<list<int>> DFAtoString(DFA<char> automata, vector<int> alphabet) {

	list<int> V;
	list<pair<char, list<int>>> H;
	V.push_back(automata.q0);
	pair<char, list<int>> first(automata.q0, list<int>());
	H.push_back(first);


	while (!H.empty()) {

		cout << "inside h empty loop" << endl;

		pair<char, list<int>> temp(H.front());
		H.pop_front();

		if (automata.F(temp.first)) return temp.second;

		cout << "temp.first: " << temp.first << endl << endl;


		for (auto c : alphabet) {

			//cout << "temp.first: " << temp.first << " -> ";
			cout << temp.first << "," << c << " -> ";

			auto qj = automata.D(temp.first, c);

			//cout << "qj: " << qj;;
			//cout << " c: " << c << endl << endl;
			cout << qj << "," << c << endl << endl;
			

			bool inV = false;
			for (auto g : V) {

				if (g == qj) inV = true;

			}

			if (!inV) {

				V.push_back(qj);

				list<int> templist(temp.second);
				templist.push_back(c);
				pair<char, list<int>> push(qj, templist);
				
				H.push_back(push);

			}

		}

	};

	cout << "return nullopt" << endl;

	return nullopt;

}

DFA<char> compDFA(DFA<char> automata) {

	auto Q = automata.Q;
	auto q0 = automata.q0;
	auto D = automata.D;
	auto F = [=](char qi) { return !(automata.F); };

	return DFA<char>(
		Q,
		q0,
		D,
		F
		);

}

//DFA<char> unionDFA(DFA<char> a1, DFA<char> a2) {}

