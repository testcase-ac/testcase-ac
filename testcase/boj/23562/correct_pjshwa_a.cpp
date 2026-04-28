#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	int cost01, cost10;
	cin >> cost01 >> cost10;
	vector<vector<int>>A(n, vector<int>(m));

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			if (s[j] == '#')
				A[i][j] = 1;
			else
				A[i][j] = 0;
		}
	}

	vector<vector<int>> shape = {
	{ 1, 1, 1},
	{1, 0, 0},
	{1, 1, 1 } };

	int ans = (int)1e9;


	for (int k = 1; 3 * k <= min(n, m); k++) {
		for (int o_i = 0; o_i + 3 * k <= n; o_i++) {
			for (int o_j = 0; o_j + 3 * k <= m; o_j++) {
				vector<vector<int>> target(n, vector<int>(m, 0));
				for (int s_i = 0; s_i < 3; s_i++) {
					for (int s_j = 0; s_j < 3; s_j++) {
						if (shape[s_i][s_j] == 0) continue;
						for (int i = 0; i < k; i++) {
							for (int j = 0; j < k; j++) {
								target[o_i + k * s_i + i][o_j + k * s_j + j] = 1;
							}
						}
					}
				}
				int costsum = 0;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						if (target[i][j] > A[i][j]) costsum += cost01;
						if (target[i][j] < A[i][j]) costsum += cost10;
					}
				}
				if (costsum < ans) {
					ans = costsum;
				}
			}
		}

	}

	cout << ans << '\n';
}