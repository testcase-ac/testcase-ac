#include <iostream>
#include <vector>
#include <random>
#include <set>
using namespace std;

int main() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> d1(1, 15);
	uniform_int_distribution<int> d2(1, 1000000);
	uniform_int_distribution<int> d3(0, 2); 

	int n = d1(gen), m = d1(gen);
	cout << n << ' ' << m << '\n';

	vector<int> common;
	set<int> a, b;

	while (a.size() < n) {
		int v = d2(gen);
		if (!common.empty() && d3(gen) == 0) v = common[d3(gen) % common.size()];
		a.insert(v);
		common.push_back(v);
	}

	while (b.size() < m) {
		int v = d2(gen);
		if (!common.empty() && d3(gen) == 0) v = common[d3(gen) % common.size()];
		b.insert(v);
	}

	for (int v : a) cout << v << ' ';
	cout << '\n';
	for (int v : b) cout << v << ' ';
}
