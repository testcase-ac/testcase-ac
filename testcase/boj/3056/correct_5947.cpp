#include <bits/stdc++.h>
using namespace std;

vector<int> buckets[21];
int arr[20][20];
double dp[1<<20];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=0; i<(1<<n); i++) {
		buckets[__builtin_popcount(i)].push_back(i);
	}
	for(int i=0; i<n; i++) {
		dp[1<<i] = (double)arr[0][i]/100;
	}
	for(int b=1; b<n; b++) {
		for(int bm: buckets[b]) {
			for(int i=0; i<n; i++) {
				if(!(bm&(1<<i))) {
					int nbm = bm | (1<<i);
					dp[nbm] = max(dp[nbm], dp[bm]*arr[b][i]/100);
				}
			}
		}
	}
	cout << fixed << setprecision(9) << dp[(1<<n)-1]*100;
}
