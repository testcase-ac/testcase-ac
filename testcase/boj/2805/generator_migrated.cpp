#include <iostream>
#include <random>
using namespace std;

int main() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> n_dist(1, 1000000);
	uniform_int_distribution<long long> m_dist(1, 2000000000);
	uniform_int_distribution<int> h_dist(0, 1000000000);

	int n = n_dist(gen);
	long long m = m_dist(gen);

	cout << n << " " << m << "\n";
	long long sum = 0;
	int heights[n];
	for (int i = 0; i < n; i++) {
		heights[i] = h_dist(gen);
		sum += heights[i];
	}
	while (sum < m) {
		int idx = gen() % n;
		int add = h_dist(gen) % (m - sum + 1);
		sum += add;
		heights[idx] += add;
	}
	for (int i = 0; i < n; i++) {
		cout << heights[i];
		if (i < n - 1) cout << " ";
	}
	return 0;
}
