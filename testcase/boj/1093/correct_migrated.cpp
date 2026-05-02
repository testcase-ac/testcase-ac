#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int N, K, M;
int price[32]{}, value[32]{}, ex[32]{};
vector<pair<int, int>> A;
vector<int> X;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> price[i];
	for (int i = 0; i < N; i++) cin >> value[i];
	for (cin >> K >> M; M--;) {
		int a;
		cin >> a;
		ex[a]++;
	}

	if (N > 16) {
		for (int i = 0; i < (1 << (N - 16)); i++) {
			int p = 0, v = 0;
			for (int k = 0; k < N - 16; k++) {
				if (i & (1 << k)) {
					v += value[k + 16];
					if (!ex[k + 16]) p += price[k + 16];
				}
				else if (ex[k + 16]) p -= price[k + 16];
			}
			A.emplace_back(v, p);
		}
		sort(A.begin(), A.end());
		X.resize(A.size());

		int mn = A.back().second;
		for (int i = A.size() - 1; i >= 0; i--) {
			mn = min(mn, A[i].second);
			X[i] = mn;
		}
	}



	int ans = -2e9;
	for (int i = 0; i < (1 << min(N, 16)); i++) {
		int p = 0, v = 0;
		for (int k = 0; k < min(N, 16); k++) {
			if (i & (1 << k)) {
				v += value[k];
				if (!ex[k]) p += price[k];
			}
			else if (ex[k]) p -= price[k];
		}
		if (N <= 16) {
			if (v >= K) ans = ans == -2e9 ? p : min(p, ans);
		}
		else {
			int j = lower_bound(A.begin(), A.end(), make_pair(K - v, 0)) - A.begin();
			if (j == A.size()) continue;
			ans = ans == -2e9 ? p + X[j] : min(ans, p + X[j]);
		}
	}
	cout << (ans == -2e9 ? -1 : max(0, ans));

}
