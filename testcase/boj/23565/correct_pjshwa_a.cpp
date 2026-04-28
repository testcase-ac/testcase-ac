#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;
using ll = long long;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--) {
		vector<ll> V(5);
		ll SUM = 0;

		for (int i = 1; i <= 4; i++) {
			cin >> V[i];
			SUM += V[i] * i;
		}
		if (V[1] >= 3 ||
			(V[1] >= 1 && V[2] > 0) ||
			(V[1] >= 2 && V[3] > 0) ||
			(V[2] == 0 && V[3] == 0 && V[4] == 0)) {
			cout << SUM+1 << '\n';
			continue;

		}
		if (V[2] > 0) {
			V[2] += V[4] * 2;
			V[4] = 0;
		}

		vector<pair<ll, int>> A;
		vector<pair<ll, int>> B;

		const int ASIZE = 6;
		for (int i = 1; i <= 4; i++) {
			if (V[i] > ASIZE) {
				A.push_back({ ASIZE, i });
				B.push_back({ V[i] - ASIZE, i });
			}
			else if (V[i] > 0) {
				A.push_back({ V[i], i });
			}
		}
		
		vector<int> check(81, 0);
		check[0] = 1;
		for (const auto& Ai : A) {
			vector<int> check_next = check;
			for (int i = 0; i < check.size(); i++) {
				if (check[i] == 0) continue;
				for (int j = 1; j <= Ai.first; j++) {
					if (i + Ai.second * j >= check.size()) continue;
					check_next[i + Ai.second * j] = 1;
				}
			}
			check = check_next;
		}
		while (check.back() == 0) check.pop_back();
		
		long long ans = accumulate(check.begin(), check.end(), 0ll);
		if (B.size() > 1) {
			for (const auto& Bi:B) ans += Bi.first * Bi.second;
		}
		else if (B.size() == 1) {
			int density = 0;
			for (int i = B[0].second * 3; i < B[0].second * 4; i++) {
				density += check[i];
			}
			ans += density * B[0].first;
		}
		cout << ans << '\n';
	}
}