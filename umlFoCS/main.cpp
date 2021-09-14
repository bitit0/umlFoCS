#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int generateNthString(vector<int> v, int n);

int main(int argc, char argv[]) {

	vector<int> v = {0, 1}; // alphabet

	vector<int> s1; // string

	generateNthString(v, 5);

	return 0;
}

int generateNthString(vector<int> v, int n) {

	if (n == 1) return -1;

	if (n > 1 && n < v.size()) return v[n];

	



}