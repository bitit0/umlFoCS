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

template<typename State>
class NFA {
public:
	NFA(function<bool(State)> Qp, State q0p, function<vector<State>(State, int)> Dp, function<vector<State>(State)> epTp, function<bool(State)> Fp) : Q(Qp), q0(q0p), epsilonTransition(epTp), D(Dp), F(Fp) {};
	function<bool(State)> Q; // Set of states 
	State q0; // Start state
	function<vector<State>(State, int)> D; // Transition
	function<vector<State>(State)> epsilonTransition;
	function<bool(State)> F; // Set of states
};

template<typename State>
class traceTree {
public:

	traceTree(vector<traceTree<State>> branchPass, bool acceptedPass, State qiPass) : branch(branchPass), accepted(acceptedPass), qi(qiPass) {};
	traceTree(vector<traceTree<State>> branchPass, bool acceptedPass, State qiPass, int cPass) : branch(branchPass), accepted(acceptedPass), qi(qiPass), c(cPass) {};

	vector<traceTree<State>> branch; // branch state (tt ...)
	bool accepted; // yes or no

	State qi; // "State that we started in"
	int c;
};

class Regex {
public:
	Regex(char type) : type(type) {};							// epsilon, null
	Regex(char type, int c) : type(type), c(c) {};					// singleton
	Regex(char type, Regex* lhs, Regex* rhs) : type(type), lhs(lhs), rhs(rhs) {};	// union, concat
	Regex(char type, Regex* operand) : type(type), lhs(operand) {};			// Kleene star

	char type;
	int c;
	Regex* lhs;
	Regex* rhs;
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

template<typename T>
bool oracle(NFA<T> n, vector<int> w, vector<pair<T, vector<int>>> trace, bool accepted);

template<typename T>
bool oracleHelper(NFA<T> n, T qi, vector<int> w, vector<pair<T, vector<int>>> trace);

template<typename T>
traceTree<T> explore(NFA<T> n, vector<int> w);

template<typename T>
traceTree<T> exploreHelper(NFA<T> n, T qi, vector<int> w);

template<typename T>
void printTraceTree(traceTree<T> tree, int count);

template<typename T>
bool backtracking(NFA<T> n, vector<int> w);

template<typename T>
bool backtrackingHelper(NFA<T> n, vector<int> w, T qi);

template<typename A, typename B>
NFA< pair< int, pair< optional<A>, optional<B> > > > unionNFA(NFA<A> a, NFA<B> b);

template<typename A, typename B>
NFA< pair< int, pair< optional<A>, optional<B> > > > concatenateNFA(NFA<A> a, NFA<B> b);

template<typename T>
void concatTests(vector<NFA<T>> NFApt, vector<string> listOfNFAs);

template<typename T>
NFA<T> kleeneStar(NFA<T> n);

template<typename T>
DFA<vector<T>> NFAtoDFA(NFA<T> n);

void printRegex(Regex r);

int main() {

	vector<int> v = { 0, 1 }; // alphabet

	string DFAnames[12] = { "binaryString", "onlyOnes", "onlyZeros", "alternatingBinary", "evenLength", "oddNum", "evenNum", "containsOne",
		"containsZero", "contains0011", "startsOneEndsZero", "threeConsecutiveZeros" };

	//generateNthString(v, 40);

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

	/*list<int> traceTest = { 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0 };

	trace(*startsOneEndsZero, traceTest);*/

	if (!acceptsString(*threeConsecutiveZeros, { 0, 0, 0 })) { cout << "HUGE ERROR" << endl; };

	// Task 12 - Tests
	/*cout << "\nTASK 12 TEST: " << endl << endl;
	vector<DFA<char>> task12test = { *binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros };

	for (int i = 0; i < 12; i++) {

		auto str = DFAtoString(task12test[i], v).value_or(list<int>(100));

		cout << DFAnames[i] << ": ";
		for (auto s : str) {
			cout << s;
		}
		cout << endl;

	}*/

	// Union, Intersect, Subset, Equality Test
	/*cout << "\nUNION TEST:\n\n";

	unionTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	cout << "\nINTERSECT TEST:\n\n";

	intersectTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	cout << "\nSUBSET TEST:\n\n";

	subsetTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);*/

	/*cout << "\nEQUALITY TEST:\n\n";

	equalityTests(*binaryString, *onlyOnes, *onlyZeros, *alternatingBinary, *evenLength, *oddNum, *evenNum, *containsOne,
		*containsZero, *contains0011, *startsOneEndsZero, *threeConsecutiveZeros, v);

	cout << endl;
	cout << endl;
	
	cout << "Complement Test (should work) [startsOneEndsZero == comp(comp(startsOneEndsZero))]: ";
	cout << equality(*startsOneEndsZero, compDFA(compDFA(*startsOneEndsZero)), v);

	cout << "\nUnion Test (should work) [containsZero == containsZero union threeConseuctiveZeros]: ";
	cout << equality(*containsZero, unionDFA(*containsZero, *threeConsecutiveZeros), v);

	cout << "\nIntersect Test (shouldn't work) [evenNum != onlyOnes intersect onlyZeros]: ";
	cout << equality(*evenNum, intersectDFA(*onlyOnes, *onlyZeros), v);
	cout << endl;*/

	// NFAs
	NFA<char>* thirdFromEndIsOne = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a'};
				if (c == 1) return vector<char>{'a', 'b'};
			}
			if (qi == 'b') {
				if (c == 0 || c == 1) return vector<char>{'c'};
			}
			if (qi == 'c') {
				if (c == 0 || c == 1) return vector<char>{'d'};
			}
			if (qi == 'd') { return vector<char>{}; }
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
			[](char qi) { return qi == 'd'; }
		);

	NFA<char>* thirdFromEndIsZero = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a', 'b'};
				if (c == 1) return vector<char>{'a'};
			}
			if (qi == 'b') {
				if (c == 0 || c == 1) return vector<char>{'c'};
			}
			if (qi == 'c') {
				if (c == 0 || c == 1) return vector<char>{'d'};
			}
			if (qi == 'd') { return vector<char>{}; }
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
			[](char qi) { return qi == 'd'; }
		);

	NFA<char>* substring101or11 = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a'};
				if (c == 0 || c == 1) return vector<char>{'a', 'b'};
			}
			if (qi == 'b') {
				if (c == 0) return vector<char>{'c'};
			}
			if (qi == 'c') {
				if (c == 1) return vector<char>{'d'};
			}
			if (qi == 'd') { return vector<char>{}; }
			return vector<char>{};
		},
		[](char qi) {
			if (qi == 'b') return vector<char>{'c'};
			return vector<char>();
		},
		[](char qi) { return qi == 'd'; }
		);

	NFA<char>* endsIn01 = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a', 'b'};
				if (c == 1) return vector<char>{'a'};
			}
			if (qi == 'b') {
				if (c == 1) return vector<char>{'c'};
			}
			if (qi == 'c') return vector<char>{};
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
		[](char qi) { return qi == 'c'; }
		);

	NFA<char>* endsIn10 = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a'};
				if (c == 1) return vector<char>{'a', 'b'};
			}
			if (qi == 'b') {
				if (c == 0) return vector<char>{'c'};
			}
			if (qi == 'c') return vector<char>{};
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
			[](char qi) { return qi == 'c'; }

		);

	NFA<char>* secondFromEndIsOne = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a'};
				if (c == 1) return vector<char>{'a', 'b'};
			}
			if (qi == 'b') {
				if (c == 0 || c == 1) return vector<char>{'c'};
			}
			if (qi == 'c') { return vector<char>{}; }
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
		[](char qi) { return qi == 'c'; }
		);

	NFA<char>* secondFromEndIsZero = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a', 'b'};
				if (c == 1) return vector<char>{'a'};
			}
			if (qi == 'b') {
				if (c == 0 || c == 1) return vector<char>{'c'};
			}
			if (qi == 'c') { return vector<char>{}; }
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
			[](char qi) { return qi == 'c'; }
		);

	NFA<char>* alphabetIs10and101 = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'f'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 1) return vector<char>{'b'};
				return vector<char>{'f'};
			}
			if (qi == 'b') {
				if (c == 0) return vector<char>{'a', 'c'};
			}
			if (qi == 'c') {
				if (c == 1) return vector<char>{'a'};
			}
			return vector<char>{'f'};
		},
		[](char qi) { return vector<char>{}; },
		[](char qi) { return qi == 'a'; }
		);

	NFA<char>* substring00or11 = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a', 'b'};
				if (c == 1) return vector<char>{'a', 'c'};
			}
			if (qi == 'b') {
				if (c == 0) return vector<char>{'d'};
			}
			if (qi == 'c') {
				if (c == 1) return vector<char>{'d'};
			}
			if (qi == 'd') {
				return vector<char>{'d'};
			}
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
		[](char qi) { return qi == 'd'; }
		);

	NFA<char>* endsIn101 = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a'};
				if (c == 1) return vector<char>{'a', 'b'};
			}
			if (qi == 'b') {
				if (c == 0) return vector<char>{'c'};
			}
			if (qi == 'c') {
				if (c == 1) return vector<char>{'d'};
			}
			if (qi == 'd') {
				return vector<char>{'d'};
			}
			return vector<char>{};
		},
		[](char qi) { return vector<char>{}; },
			[](char qi) { return qi == 'd'; }
		);

	NFA<char>* lastCharIsZeroOrContainsOnlyOnes = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'b',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 1) return vector<char>{'a'};
			}
			if (qi == 'c') {
				if (c == 0) return vector<char>{'c', 'd'};
				if (c == 1) return vector<char>{'c'};
			}
			return vector<char>{};
		},
		[](char qi) {
			if (qi == 'b') return vector<char>{'a', 'c'};
		},
		[](char qi) { return (qi == 'a') || (qi == 'd'); }
		);

	NFA<char>* oneAtThirdOrSecondFromEnd = new NFA<char>(
		[](char x) { return (x == 'a') || (x == 'b') || (x == 'c') || (x == 'd'); },
		'a',
		[](char qi, int c) {
			if (qi == 'a') {
				if (c == 0) return vector<char>{'a'};
				if (c == 1) return vector<char>{'a', 'b'};
			}
			if (qi == 'b') {
				if (c == 0 || c == 1) return vector<char>{'c'};
			}
			if (qi == 'c') {
				if (c == 0 || c == 1) return vector<char>{'d'};
			}
			if (qi == 'd') { return vector<char>{}; };
			return vector<char>{};
		},
		[](char qi) {
			if (qi == 'b') return vector<char>{'c'};
		},
			[](char qi) { return (qi == 'd'); }
		);

	vector<string> listOfNFAs = {"thirdFromEndIsOne", "thirdFromEndIsZero", "substring101or11", "endsIn01", "endsIn10", "secondFromEndIsOne", 
		"secondFromEndIsZero", "alphabetIs10and101", "substring00or11", "endsIn101", "lastCharIsZeroOrContainsOnlyOnes", "oneAtThirdOrSecondFromEnd"};

	vector<NFA<char>> NFApt = { *thirdFromEndIsOne, *thirdFromEndIsZero, *substring101or11, *endsIn01, *endsIn10, *secondFromEndIsOne,
		*secondFromEndIsZero, *alphabetIs10and101, *substring00or11, *endsIn101, *lastCharIsZeroOrContainsOnlyOnes, *oneAtThirdOrSecondFromEnd };

	//cout << "\n\NFA Concatenate Tests:\n\n";
	//concatTests(NFApt, listOfNFAs);
	//cout << "\n\n";

	////template<typename T>
	////bool oracle(NFA<T> n, vector<T> w, vector<pair<T, vector<int>>> trace, bool accepted);

	//cout << "\nOracle Test:\n";
	//vector<int> oracleTestString = { 1,0,0 };
	//vector<pair<char, vector<int>>> oracleTestTrace = { {'a', {1,0,0}}, {'b', {0,0}}, {'c', {0}} };
	//cout << oracle(*thirdFromEndIsOne, oracleTestString, oracleTestTrace, true);


	vector<int> tfeioTest = { 0,0,0,1,0,1 };
	//traceTree<char> printableTraceTree = explore(*thirdFromEndIsOne, tfeioTest);

	vector<int> ss101or11 = { 0,1,0,1,0,0 };
	/*cout << "\nTrace Tree of substring101or11 & \"010100\"" << endl;
	traceTree<char> printableTraceTree = explore(*substring101or11, ss101or11);
	printTraceTree(printableTraceTree, 0);*/

	//cout << backtracking(*substring101or11, ss101or11);
	//backtracking(*substring101or11, ss101or11);

	cout << "\nBacktracking Test: " << backtracking(*endsIn01, tfeioTest);

	//vector<int> teststr = { 0,0,0,1,0,1 };
	//vector<int> teststr2 = { 1,1,0,1,0,1 };
	//auto finishunion = unionNFA(*endsIn01, *thirdFromEndIsOne);
	////traceTree<T> printed = explore(finishunion, teststr);
	////auto finishconcat = concatenateNFA(*substring00or11, *endsIn101);
	//cout << "\n\nUnion Test (endsIn01 union thirdFromEndIsOne) [0,0,0,1,0,1]: " << backtracking(finishunion, teststr);
	////cout << "\nConcat Test (substring00or11 concat endsIn101) [1,1,0,1,0,1]: " << backtracking(finishconcat, teststr2);

	////vector<pair<T, list<int>>> trace
	//
	//vector ksTest = { 1, 0, 0 };

	//cout << backtracking(kleeneStar(*thirdFromEndIsOne), ksTest);

	//auto nfaConvertTest1 = NFAtoDFA(*thirdFromEndIsOne);

	/*Regex lhs('s', 5);
	Regex rhs('s', 6);

	Regex un('u', &lhs, &rhs);
	Regex st('k', &lhs);
	printRegex(un); cout << "\n";
	printRegex(st);*/


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
	cout << names[1] << " equality " << names[1] << " -> " << subset(b, b, alphabet);

}

template<typename T>
void NFATraces(vector<NFA<T>> NFApt, vector<string> listOfNFAs) { //BRUH

	// vector<NFA<char>> NFApt = { *thirdFromEndIsOne, *thirdFromEndIsZero, *substring101or11, *endsIn01, *endsIn10, *secondFromEndIsOne,
	//*secondFromEndIsZero, * alphabetIs10and101, * substring00or11, * endsIn101, * lastCharIsZeroOrContainsOnlyOnes, * oneAtThirdOrSecondFromEnd

	vector<pair<char, vector<int>>> accepted;

	// thirdFromEndIsOne
	accepted = { {'a', {1,0,0}}, {'b', {0,0}}, {'c', {0}} };



}

template<typename T>
void concatTests(vector<NFA<T>> NFApt, vector<string> listOfNFAs) {

	// vector<NFA<char>> NFApt = { *thirdFromEndIsOne, *thirdFromEndIsZero, *substring101or11, *endsIn01, *endsIn10, *secondFromEndIsOne,
	//*secondFromEndIsZero, * alphabetIs10and101, * substring00or11, * endsIn101, * lastCharIsZeroOrContainsOnlyOnes, * oneAtThirdOrSecondFromEnd

	vector<vector<int>> testString = { {0}, {1,0,1,0,0,0}, {1,1,0,1}, {0}, {1,0}, {0}, {1,0,1,0,1}, {1,0,1,1,1}, {1,1,0,1}, {1,0,1,0}, {1,1,1} };

	for (int i = 0; i < testString.size(); i++) {

		auto concatenated = concatenateNFA(NFApt[i], NFApt[i + 1]);
		cout << listOfNFAs[i] << " concat " << listOfNFAs[i + 1] << " on [";

		for (int j = 0; j < testString[i].size(); j++) {

			cout << testString[i][j];

		}
		cout << "] -> ";

		cout << backtracking(concatenated, testString[i]) << endl;

	}



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

template<typename T>
NFA<T> convert(DFA<T> dfaToConvert) {

	auto newDelta = [=](T qi, int c) {

		return vector<T>{dfaToConvert.D(qi, c)};

	};

	auto epT = [=](T qi) {

		return vector<T>{};

	};

	return NFA<T>(dfaToConvert.Q, dfaToConvert.q0, dfaToConvert.D, epT, dfaToConvert.F);

}

// A configuration follows the following format: { {qi}, {w} }
// For example: { {'a'}, {1, 0, 1, 0, 0} }
// Then trace would follow this: { { {qi}, {w} }, { {qj}, {wprime} }}

template<typename T>
bool oracle(NFA<T> n, vector<int> w, vector<pair<T, vector<int>>> trace, bool accepted) {

	return accepted == oracleHelper(n, n.q0, w, trace);

}

template<typename T>
bool oracleHelper(NFA<T> n, T qi, vector<int> w, vector<pair<T, vector<int>>> trace) {

	if (trace.empty() && w.empty()) return true;

	if (!trace.empty() && !w.empty()) {

		// Get qj and w-prime

		vector<int> temp;
		for (int i = 1; i < w.size(); i++) {

			temp.push_back(w.at(i));

		}
		/*cout << "w:\n";
		for (int i = 0; i < w.size(); i++) {
			cout << w[i];
		}
		cout << "\ntemp:" << temp.size() << endl;
		for (int i = 0; i < temp.size(); i++) {
			cout << temp[i];
		}
		cout << "\ntrace[0]:";
		for (int i = 0; i < trace[0].second.size(); i++) {
			cout << trace[0].second[i];
		}
		cout << "\ntrace[1]:" << trace[1].second.size() << endl;
		for (int i = 0; i < trace[1].second.size(); i++) {
			cout << trace[1].second[i];
		}
		cout << "\n";*/


		if (w == trace[0].second) { // epsilon transition

			auto prime = n.epsilonTransition(qi);

			auto validTransition = find(prime.begin(), prime.end(), trace[1].first);
			trace.erase(trace.begin());

			if (validTransition != prime.end()) {

				//cout << "wha";
				return oracleHelper(n, prime.at(0), w, trace);

			}

		}
		else if (temp == trace[1].second) {

			//cout << "im in second loop!!!!!!!!!!!!";

			T popped = w.front();
			auto prime = n.D(qi, popped);

			//cout << "prime:" << prime.size() << endl;
			//for (int i = 0; i < prime.size(); i++) cout << prime[i];
			//cout << "\n";

			auto validTransition = find(prime.begin(), prime.end(), trace[1].first);
			trace.erase(trace.begin());

			if (validTransition != prime.end()) {

				//cout << "ooga";
				return oracleHelper(n, prime.at(0), w, trace);
			}

		} else {
			
			//cout << "wtf";
			return false;

		}

	}
	return true;
}

template<typename T>
traceTree<T> explore(NFA<T> n, vector<int> w) {

	return exploreHelper(n, n.q0, w);

}

template<typename T>
traceTree<T> exploreHelper(NFA<T> n, T qi, vector<int> w) {
	
	// traceTree(vector<traceTree<State>> branchPass, bool acceptedPass, State qiPass, int cPass) : branch(branchPass), accepted(acceptedPass), qi(qiPass), c(cPass) {};

	if (w.empty()) {

		if (n.F(qi)) {

			traceTree<T> rettrue( vector<traceTree<T>>{}, true, qi, 99 );
			return rettrue;

		} else {

			traceTree<T> retfalse( vector<traceTree<T>>{}, false, qi, -99 );
			return retfalse;

		}

	}

	vector<traceTree<T>> opts;

	int c = w.at(0);
	vector<int> wPrime(w);			// cw
	wPrime.erase(wPrime.begin());

	vector<T> epsilonQjs = n.epsilonTransition(qi);

	for (auto item : epsilonQjs) {

		opts.push_back(traceTree<T>(exploreHelper(n, item, w)));

	}

	vector<T> deltaQjs = n.D(qi, c);
	
	for (auto item : deltaQjs) {

		opts.push_back(traceTree<T>(exploreHelper(n, item, wPrime)));

	}

	// traceTree(vector<traceTree<State>> branchPass, bool acceptedPass, State qiPass)
	// traceTree(vector<traceTree<State>> branchPass, bool acceptedPass, State qiPass, int cPass) 

	return traceTree<T>(opts, n.F(qi), qi, w.at(0));
	
}

template<typename T>
void printTraceTree(traceTree<T> tree, int tabc) {

	cout << endl;

	for (int i = 0; i < tabc; i++) cout << "\t";

	tabc++; // increase tabc for every recursive call

	cout << "{ " << tree.qi << ", " << tree.c;

	for (auto i : tree.branch) printTraceTree(i, tabc);

	cout << endl;

	for (int i = 0; i < tabc; i++) cout << "\t";

	cout << "}";

}

template<typename T>
bool backtracking(NFA<T> n, vector<int> w) {

	vector<pair<T, vector<int>>> visited;
	vector<pair<T, vector<int>>> pending;
	pending.push_back(pair<T, vector<int>>(n.q0, w));

	while (!pending.empty()) {

		pair<T, vector<int>> qi = pending.front();
		pending.erase(pending.begin());

		if (qi.second.empty() && n.F(qi.first)) {

			return true;

		}

		auto epsilonQjs = n.epsilonTransition(qi.first);
		for (int i = 0; i < epsilonQjs.size(); i++) {

			pair<T, vector<int>> temp(epsilonQjs.at(i), w);

			if (find(visited.begin(), visited.end(), temp) == visited.end()) {

				cout << "e";
				pending.push_back(temp);
				visited.push_back(temp);

			}

		}

		vector<int> wPrime(w);
		int c = w.at(0);
		wPrime.erase(wPrime.begin());

		auto deltaQjs = n.D(qi.first, c);
		
		for (int i = 0; i < deltaQjs.size(); i++) {

			pair<T, vector<int>> temp(deltaQjs.at(i), wPrime);

			if (find(visited.begin(), visited.end(), temp) == visited.end()) {

				pending.push_back(temp);
				visited.push_back(temp);

			}

		}

	}

	return false;
}

//template<typename T>
//bool backtracking(NFA<T> n, vector<int> w) {
//
//	return backtrackingHelper(n, w, n.q0);
//
//}
//
//template<typename T>
//bool backtrackingHelper(NFA<T> n, vector<int> w, T qi) {
//
//	vector<T> epsilonQjs = n.epsilonTransition(qi);
//
//	for (auto item : epsilonQjs) {
//
//		if (backtrackingHelper(n, w, item)) return true;
//
//	}
//
//	if (!w.empty()) {
//
//		int c = w.at(0);
//
//		vector<T> deltaQjs = n.D(qi, c);
//		w.erase(w.begin());
//
//		for (auto item : deltaQjs) {
//
//			if (backtrackingHelper(n, w, item)) return true;
//
//		}
//
//	}
//	else {
//
//		return n.F(qi);
//
//	}
//
//	return false;
//
//}

template<typename A, typename B>
NFA<pair<int, pair<optional<A>, optional<B>>>> unionNFA(NFA<A> a, NFA<B> b) {

	function<bool(A)> a_Q = a.Q;
	function<bool(B)> b_Q = b.Q;

	function<vector<A>(A, int)> a_D = a.D;
	function<vector<B>(B, int)> b_D = b.D;

	function<vector<A>(A)> a_epT = a.epsilonTransition;
	function<vector<B>(B)> b_epT = b.epsilonTransition;

	function<bool(A)> a_F = a.F;
	function<bool(B)> b_F = b.F;

	pair< int, pair< optional<A>, optional<B> > > q0c{ 0, {nullopt, nullopt} };

	// Q function
	function<bool(pair< int, pair< optional<A>, optional<B> > >)> Qc = [=](pair< int, pair< optional<A>, optional<B> > > p) {

		if (p == q0c) {												// start state is a valid state

			return true;

		}
		else if (p.first == 0 && p.second.first != nullopt) {		// NFA a

			return a_Q(p.second.first.value());								// check if in NFA a

		}
		else if (p.first == 1 && p.second.second != nullopt) {		// if not in NFA a, then check NFA b

			return b_Q(p.second.second.value());							// check if in NFA b

		}

		return false;												// not a state in any NFA or start/end

	};

	// Delta function
	function< vector< pair< int, pair< optional<A>, optional<B> > > >(pair< int, pair< optional<A>, optional<B> > >, int) > Dc = [=](pair< int, pair< optional<A>, optional<B> > > p, int c) {

		vector< pair< int, pair< optional<A>, optional<B> > > > opts;	// list of options for where to proceed next

		if (p.first == 0 && p.second.first.value()) {				// NFA a

			vector<A> deltaQjs = a.D(p.second.first.value(), c);			// get all of the possible delta transitions from the current state

			for (auto item : deltaQjs) {							// loop thru and add to the list of possible options

				opts.push_back({ 0, {item, nullopt} });

			}

		}
		else if (p.first == 1 && p.second.second) {		// NFA b

			vector<B> deltaQjs = b.D(p.second.second.value(), c);

			for (auto item : deltaQjs) {

				opts.push_back({ 1, {nullopt, item} });

			}

		}
		return opts;
	};

	// example of pair: { 0, {a.q0, nullopt} }
	// "0" is which NFA (a or b)
	// "a.q0" is a state in the NFA
	// nullopt would be a state in the NFA if we were talking about B

	// Epsilon Transition function
	function< vector< pair< int, pair< optional<A>, optional<B> > > >(pair< int, pair< optional<A>, optional<B> > >) > epTc = [=](pair< int, pair< optional<A>, optional<B> > > p) {

		vector< pair< int, pair< optional<A>, optional<B> > > > opts;

		if (p == q0c) {

			opts.push_back({ 0, { a.q0, nullopt } });
			opts.push_back({ 1, { nullopt, b.q0 } });

		}
		else if (p.first == 0 && p.second.first.value()) {			// NFA a

			vector<A> epsilonQjs = a.epsilonTransition(p.second.first.value());

			for (auto item : epsilonQjs) {

				opts.push_back({ 0, {item, nullopt} });

			}

		}
		else if (p.first == 1 && p.second.second.value()) {			// NFA b

			vector<B> epsilonQjs = b.epsilonTransition(p.second.second.value());

			for (auto item : epsilonQjs) {

				opts.push_back({ 1, {nullopt, item} });

			}

		}
		return opts;
	};

	function<bool(pair< int, pair< optional<A>, optional<B> > >)> Fc = [=](pair< int, pair< optional<A>, optional<B> > > p) {

		if (p.first == 0 && p.second.first != nullopt) {

			return a.F(p.second.first.value());

		}
		else if (p.first == 1 && p.second.second != nullopt) {

			return b.F(p.second.second.value());

		}
		return false;
	};

	return NFA<pair<int, pair<optional<A>, optional<B>>>>(Qc, q0c, Dc, epTc, Fc);
}

template<typename A, typename B>
NFA< pair< int, pair< optional<A>, optional<B> > > > concatenateNFA(NFA<A> a, NFA<B> b) {

	pair< int, pair< optional<A>, optional<B> > > q0c = { 0, {nullopt, nullopt} };

	function<bool(pair< int, pair< optional<A>, optional<B> > >)> Qc = [=](pair< int, pair< optional<A>, optional<B> > > p) {

		if (p == q0c) {

			return true;

		}
		else if (p.first == 0 && p.second.first != nullopt) {

			return a.Q(p.second.first.value());

		}
		else if (p.first == 1 && p.second.second != nullopt) {

			return b.Q(p.second.second.value());

		}

		return false;
	};

	function< vector< pair< int, pair< optional<A>, optional<B> > > >(pair< int, pair< optional<A>, optional<B> > >, int) > Dc = [=](pair< int, pair< optional<A>, optional<B> > > p, int c) {

		vector< pair< int, pair< optional<A>, optional<B> > > > opts;

		if (p.first == 0 && p.second.first) {

			vector<A> deltaQjs = a.D(p.second.first.value(), c);

			for (auto item : deltaQjs) {

				opts.push_back({ 0, {item, nullopt} });

				if (a.F(item)) {

					opts.push_back({ 1, {nullopt, b.q0} });

				}

			}


		}
		else if (p.first == 1 && p.second.second) {

			vector<B> deltaQjs = b.D(p.second.second.value(), c);

			for (auto item : deltaQjs) {

				opts.push_back({ 1, {nullopt, item} });

			}

		}
		return opts;
	};

	function< vector< pair< int, pair< optional<A>, optional<B> > > >(pair< int, pair< optional<A>, optional<B> > >) > epTc = [=](pair< int, pair< optional<A>, optional<B> > > p) {

		vector< pair< int, pair< optional<A>, optional<B> > > > opts;

		if (p == q0c) {

			opts.push_back({ 0, {a.q0, nullopt} });

		}
		else if (p.first == 0 && p.second.first) {

			vector<A> epsilonQjs = a.epsilonTransition(p.second.first.value());

			for (auto item : epsilonQjs) {
				//cout << "ept first " << endl;
				opts.push_back({ 0, {item, nullopt} });

				if (a.F(item)) {

					opts.push_back({ 1, {nullopt, b.q0} });

				}

			}

		}
		else if (p.first == 1 && p.second.second) {

			vector<B> epsilonQjs = b.epsilonTransition(p.second.second.value());

			for (auto item : epsilonQjs) {

				opts.push_back({ 1, {nullopt, item} });

			}

		}
		return opts;
	};

	function< bool(pair< int, pair< optional<A>, optional<B> > >)> Fc = [=](pair< int, pair< optional<A>, optional<B> > > p) {

		if (p.first == 1 && p.second.second != nullopt) {

			return b.F(p.second.second.value());

		}
		return false;
	};


	return NFA<pair<int, pair<optional<A>, optional<B>>>>(Qc, q0c, Dc, epTc, Fc);
}

template<typename T>
NFA<T> kleeneStar(NFA<T> n) {

	// new start state
	T k_q0 = 'a';

	function<bool(T)> k_Q = [=](T qi) { return n.Q(qi) || qi == k_q0; }; // check if state is a state of the NFA, or if it's the new start state

	// new delta transitions
	function<vector<T>(T, int)> k_D = [=](T qi, int c) {

		vector<T> k_transitions;
		k_transitions = n.D(qi, c);

		return k_transitions;
	};

	// new epsilon transitions
	function<vector<T>(T)> k_epT = [=](T qi) {

		vector<T> k_transitions;
		k_transitions = n.epsilonTransition(qi);

		if (qi == k_q0) {				// new epsilon transitions

			k_transitions.push_back(n.q0);	// if at q0, go to the machine N

		}
		else {

			k_transitions.push_back(k_q0);	// if at machine N, then go to q0

		}
		return k_transitions;
	};

	function<bool(T)> k_F = [=](T qi) { return (n.F(qi) || qi == k_q0); };

	return NFA<T>(k_Q, k_q0, k_D, k_epT, k_F);

}

template<typename T>
DFA<vector<T>> NFAtoDFA(NFA<T> n) {

	// set of states
	auto qd = [=](vector<T> stateSet) {

		vector<T> pset;

		for (int i = 0; i < stateSet.size(); i++) {

			if (n.Q(stateSet.at(i))) {

				for (int j = 0; j < pset.size(); j++) {

					if (pset.at(j) == stateSet.at(i)) return false;

				}

				pset.push_back(stateSet.at(i));

			}
			else {
				return false;
			}
		}
		return true;
	};

	// epsilon transitions
	auto E = [=](vector<T> X) {

		bool changed = true;

		while (changed) {

			changed = false;

			for (int i = 0; i < X.size(); i++) {

				vector<T> epT_list = n.epsilonTransition(X.at(i));

				for (int j = 0; j < epT_list.size(); j++) {

					if (find(X.begin(), X.end(), epT_list.at(j)) == X.end()) {

						changed = true;
						X.push_back(epT_list.at(j));

					}

				}

			}

		}
		return X;
	};

	// initial state, just intital state of q0, but have to apply E function
	vector<T> q0d = { n.q0 };
	q0d = E(q0d);

	// delta function
	auto dd = [=](vector<T> qis, int c) {

		vector<T> possible;
		for (int i = 0; i < qis.size(); i++) {						// for every state

			vector<T> deltaTransitions = n.D(qis.at(i), c);			// get delta transitions

			for (int j = 0; j < deltaTransitions.size(); j++) {

				possible.push_back(deltaTransitions.at(i));			// unioning

			}

		}

		for (int i = 0; i < possible.size(); i++) {					// erase duplicates

			for (int j = 0; j < possible.size(); j++) {

				if (i != j && possible.at(i) == possible.at(j)) {

					possible.erase(possible.begin() + j);

				}

			}

		}
		return E(possible);
	};

	// new set of accepted states
	auto fd = [=](vector<T> qis) {

		for (int i = 0; i < qis.size(); i++) {

			if (n.F(qis.at(i))) return true;		// if accepted, return true

		}
		return false;								// if not inside n.F, then return false because it's not accepted
	};

	return DFA<vector<T>>(qd, q0d, dd, fd);
}

void printRegex(Regex r) {

	if (r.type == 'n') cout << "";	// null/empty
	if (r.type == 'e') cout << "";	// epsilon
	if (r.type == 's') cout << r.c;	// singleton/character

	if (r.type == 'u') {			// union

		cout << "(";
		printRegex(*(r.lhs));
		cout << " u ";
		printRegex(*(r.rhs));
		cout << ")";

	}

	if (r.type == 'k') {			// kleene

		cout << "(";
		printRegex(*r.lhs);
		cout << ")*";

	}

	if (r.type == 'c') {			// concat

		cout << "(";
		printRegex(*(r.lhs));
		cout << " o ";
		printRegex(*(r.rhs));
		cout << ")";

	}

}

optional<vector<int>> generate(Regex r) {

	if (r.type == 'n') return nullopt;
	if (r.type == 'e') return vector<int>{};
	if (r.type == 's') return vector<int>{r.c};

	if (r.type == 'u') {

		auto gx = generate(*r.lhs);
		if (gx != nullopt) return gx;
		return generate(*r.rhs);

	}

	if (r.type == 'k') {

		Regex lhs('e');
		Regex rhs( 'c', r.lhs, new Regex('k', r.lhs) );

		return generate(Regex('u', &lhs, &rhs));

	}

	if (r.type == 'c') {

		auto gx = generate(*r.lhs);
		auto gy = generate(*r.rhs);

		if (gx != nullopt && gy != nullopt) {

			gx.value().insert( gx.value().end(), gy.value().begin(), gy.value().end() );	// gx circ gy
			return gx;

		}

		return nullopt;

	}

}