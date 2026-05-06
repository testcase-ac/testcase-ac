#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
int main() {
	unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);
	int n = rand() % 20 + 1;
	cout << n << endl;
	int last = rand() % 100 + 1;
	cout << last << endl;

	for (int i = 1; i < n; i++) {
		int delta = rand() % (1 << 24);
		last += delta;
		if (last > (1 << 30)) last = (1 << 30);
		cout << last << endl;
	}
}
