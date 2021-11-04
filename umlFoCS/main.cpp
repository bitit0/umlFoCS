#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <functional>
#include <optional>
#include <string>

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

template<typename T>
bool acceptsString(DFA<T> d, list<int> l);

DFA<char> onlyCharDFA(char in);
void trace(DFA<char> automata, list<int> l);

template<typename State>
optional<list<int>> DFAtoString(DFA<State> automata, vector<int> alphabet);

template<typename T>
DFA<T> compDFA(DFA<T> automata);

template<typename A, typename B>
DFA<pair<A, B>> unionDFA(DFA<A> a1, DFA<B> a2);

template<typename A, typename B>
DFA<pair<A, B>> intersectDFA(DFA<A> a1, DFA<B> a2);

template<typename A, typename B>
bool subset(DFA<A> a1, DFA<B> a2, vector<int> alphabet);

template<typename A, typename B>
bool equality(DFA<A> a1, DFA<B> a2, vector<int> alphabet);

void compTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet);
void unionTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet);
void intersectTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet);
void subsetTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet);
void equalityTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet);

int main() {

	vector<int> v = { 0, 1 }; // alphabet

	string DFAnames[12] = { "binaryString", "onlyOnes", "onlyZeros", "alternatingBinary", "evenLength", "oddNum", "evenNum", "containsOne",
		"containsZero", "contains0011", "startsOneEndsZero", "threeConsecutiveZeros" };

	generateNthString(v, 40);

	// DFAs
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

	// acceptsString Tests
	vector<list<int>> accept = { {0, 1}, {0, 1, 1}, {1, 0, 1}, {0, 1, 0, 1}, {1}, {1, 0, 0} };
	vector<list<int>> reject = { {1, 2}, {2, 3}, {4, 5}, {6, 7}, {8, 10}, {89, 91} };

	int total = 0;
	int fails = 0;

	// binary string
	for (auto c : accept) {
		total++;
		if (acceptsString(compDFA(*binaryString), c)) {
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

	if (!acceptsString(*threeConsecutiveZeros, { 0, 0, 0 })) { cout << "HUGE ERROR" << endl; };

	// Task 12 - Tests
	cout << "\nTASK 12 TEST: " << endl << endl;
	vector<DFA<char>> task12test = {*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros };

	for (int i = 0; i < 12; i++) {

		auto str = DFAtoString(task12test[i], v).value_or(list<int>(100));

		cout << DFAnames[i] << ": ";
		for (auto s : str) {
			cout << s;
		}
		cout << endl;

	}

	// Task 14 - Union Tests
	cout << "\nUNION TEST:\n\n";

	unionTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	cout << "\nINTERSECT TEST:\n\n";

	intersectTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	cout << "\nSUBSET TEST:\n\n";

	subsetTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	cout << "\nEQUALITY TEST:\n\n";

	equalityTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	//compTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		//*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	cout << endl;

	//cout << "real test: " << endl;
	////cout << subset(*threeConsecutiveZeros, *onlyOnes, v);
	//auto DStest = DFAtoString(*evenNum, v).value_or(list<int>(100));

	//for (int y : DStest) {

	//	cout << y;

	//}

	cout << endl;

	return 0;
}

void compTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet) {

	auto str = DFAtoString(compDFA(k), alphabet).value_or(list<int>(100));
	cout << "COMP TEST: [";
	for (auto s : str) cout << s;
	cout << "]";
	cout << endl;

}

void unionTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet) {

	vector<string> names{ "binaryString", "onlyOnes", "onlyZeros", "alternatingBinary", "evenLength", "oddNum", "evenNum", "containsOne",
	"containsZero", "contains0011", "startsOneEndsZero", "threeConsecutiveZeros" };

	int count = 0;

	auto test = unionDFA(a, b);
	auto str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(b, c);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(c, d);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(d, e);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(e, f);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(f, g);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(g, h);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(h, i);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(i, j);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(j, k);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(k, l);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[count] << " union " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = unionDFA(a, l);
	str = DFAtoString(test, alphabet).value_or(list<int>(100));

	cout << names[0] << " union " << names[11] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

}

void intersectTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet) {

	vector<string> names{ "binaryString", "onlyOnes", "onlyZeros", "alternatingBinary", "evenLength", "oddNum", "evenNum", "containsOne",
	"containsZero", "contains0011", "startsOneEndsZero", "threeConsecutiveZeros" };

	int count = 0;

	auto test = intersectDFA(a, b);
	auto str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(b, c);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(c, d);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(d, e);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(e, f);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(f, g);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(g, h);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(h, i);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(i, j);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(j, k);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(k, l);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[count] << " intersect " << names[++count] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

	test = intersectDFA(a, l);
	str = DFAtoString(test, alphabet).value_or(list<int>(25));

	cout << names[0] << " intersect " << names[11] << " -> ";
	for (auto s : str) cout << s;
	cout << endl;

}

void subsetTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet) {

	vector<string> names { "binaryString", "onlyOnes", "onlyZeros", "alternatingBinary", "evenLength", "oddNum", "evenNum", "containsOne",
	"containsZero", "contains0011", "startsOneEndsZero", "threeConsecutiveZeros" };

	int count = 0;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(a, b, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(b, c, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(c, d, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(d, e, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(e, f, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(f, g, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(g, h, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(h, i, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(i, j, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(j, k, alphabet) << endl;
	cout << names[count] << " subset " << names[++count] << " -> " << subset(k, l, alphabet) << endl;
	cout << names[2] << " subset " << names[8] << " -> " << subset(c, i, alphabet);
		 
}

void equalityTests(DFA<char> a, DFA<char> b, DFA<char> c, DFA<char> d, DFA<char> e, DFA<char> f, DFA<char> g, DFA<char> h, DFA<char> i, DFA<char> j, DFA<char> k, DFA<char> l, vector<int> alphabet) {

	vector<string> names{ "binaryString", "onlyOnes", "onlyZeros", "alternatingBinary", "evenLength", "oddNum", "evenNum", "containsOne",
	"containsZero", "contains0011", "startsOneEndsZero", "threeConsecutiveZeros" };

	int count = 0;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(a, b, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(b, c, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(c, d, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(d, e, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(e, f, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(f, g, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(g, h, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(h, i, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(i, j, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(j, k, alphabet) << endl;
	cout << names[count] << " equality " << names[++count] << " -> " << equality(k, l, alphabet) << endl;
	cout << names[1] << " subset " << names[1] << " -> " << subset(b, b, alphabet);

}


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

template <typename T>
bool acceptsString(DFA<T> automata, list<int> l) {

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
	cout << automata.q0 << ", ";
	for (int curr : l) {

		qi = automata.D(qi, curr);
		cout << qi << ", ";

	}
	cout << "\b\b \b" << endl;

}

template<typename State>
optional<list<int>> DFAtoString(DFA<State> automata, vector<int> alphabet) {

	list<State> V;
	list<pair<State, list<int>>> H;
	V.push_back(automata.q0);
	pair<State, list<int>> first(automata.q0, list<int>());
	H.push_back(first);


	while (!H.empty()) {

		pair<State, list<int>> temp(H.front());
		H.pop_front();

		if (automata.F(temp.first)) return optional<list<int>>(in_place, temp.second);

		for (auto c : alphabet) {

			auto qj = automata.D(temp.first, c);
			
			bool inV = false;
			for (auto g : V) {
						   
				if (g == qj) inV = true;
						   
			}			   
						   
			if (!inV) {	   
						   
				V.push_back(qj);
						   
				list<int> templist(temp.second);
				templist.push_back(c);
				pair<State, list<int>> push(qj, templist);
						   
				H.push_back(push);
						   
			}			   
						   
		}				   
						   
	};					   

	//cout << "\nreturn nullopt" << endl;

	return nullopt;

}

template <typename T>
DFA<T> compDFA(DFA<T> automata) {

	auto Q = automata.Q;
	auto q0 = automata.q0;
	auto D = automata.D;
	auto F = [=](T qi) { return !(automata.F(qi)); };

	return DFA<T>(Q, q0, D, F);

}

template <typename A, typename B>
DFA<pair<A, B>> unionDFA(DFA<A> a1, DFA<B> a2) {

	function<bool(A)> a1_Q = a1.Q;
	function<bool(B)> a2_Q = a2.Q;

	function<A(A, int)> a1_D = a1.D;
	function<B(B, int)> a2_D = a2.D;

	function<bool(A)> a1_F = a1.F;
	function<bool(B)> a2_F = a2.F;

	return DFA<pair<A, B>>(
		[a1_Q, a2_Q](pair<A, B> p) { return a1_Q(p.first) && a2_Q(p.second); },
		pair<A, B>(a1.q0, a2.q0),
		[a1_D, a2_D](pair<A, B> p, int c) {
			A d1 = a1_D(p.first, c);
			B d2 = a2_D(p.second, c);
		
			return pair<A, B>(d1, d2);
		},
		[a1_F, a2_F](pair<A, B> p) { return a1_F(p.first) || a2_F(p.second); }
		);

}

template <typename A, typename B>
DFA<pair<A, B>> intersectDFA(DFA<A> a1, DFA<B> a2) {

	function<bool(A)> a1_Q = a1.Q;
	function<bool(B)> a2_Q = a2.Q;

	function<A(A, int)> a1_D = a1.D;
	function<B(B, int)> a2_D = a2.D;

	function<bool(A)> a1_F = a1.F;
	function<bool(B)> a2_F = a2.F;

	return DFA<pair<A, B>>(
		[a1_Q, a2_Q](pair<A, B> p) { return a1_Q(p.first) && a2_Q(p.second); },
		pair<A, B>(a1.q0, a2.q0),
		[a1_D, a2_D](pair<A, B> p, int c) {
			A d1 = a1_D(p.first, c);
			B d2 = a2_D(p.second, c);

			return pair<A, B>(d1, d2);
		},
		[a1_F, a2_F](pair<A, B> p) { return a1_F(p.first) && a2_F(p.second); }
		);

}

template <typename A, typename B>
bool subset(DFA<A> a1, DFA<B> a2, vector<int> alphabet) {

	try {

		auto str = DFAtoString(intersectDFA(compDFA(a2), a1), alphabet).value();

		/*cout << "[";
		for (auto s : str) cout << s;
		cout << "]";*/
		return false;

	}
	catch (bad_optional_access x) {

		return true;

	}


}

template<typename A, typename B>
bool equality(DFA<A> a1, DFA<B> a2, vector<int> alphabet) {

	return subset(a1, a2, alphabet) && subset(a2, a1, alphabet);

}

