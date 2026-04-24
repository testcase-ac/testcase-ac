#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 10001;
bool dp[100][MX*2];
int prv[100][MX*2];
int arr[100];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, t;
	cin >> n >> t;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	dp[0][arr[0]+MX] = 1;
	for(int i=1; i<n; i++) {
		for(int j=0; j<MX*2; j++) {
			int mj = j - arr[i], pj = j+arr[i];
			if(i > 1 && mj >= 0 && dp[i-1][mj]) {
				dp[i][j] = 1;
				prv[i][j] = mj;
			}
			if(pj < MX*2 && dp[i-1][pj]) {
				dp[i][j] = 1;
				prv[i][j] = pj;
			}
		}
	}
	vector<int> v;
	int i = n-1, j = t+MX;
	while(i > 0) {
		v.push_back(prv[i][j] > j ? -1 : 1);
		j = prv[i][j];
		i--;
	}
	reverse(v.begin(), v.end());
	for(int k=0; k<v.size(); k++) {
		if(v[k] == 1) {
			cout << k+1 << '\n';
			v.erase(v.begin()+k);
			k--;
		}
	}
	for(int j=0; j<v.size(); j++)
		cout << 1 << '\n';
}
