#include <bits/stdc++.h>
using namespace std;
#define int long long
int ncr[30][30];
int solve() {
	int n;
	cin >> n;
	vector<int> v;
	int t;
	for(t=2; n; t++) {
		v.push_back(n % t);
		n /= t;
	}
	t--;
	sort(v.begin(), v.end(), greater<int>());
	int ans = 1, rmlst = 1;
	for(int i=0, j=0; i<v.size(); i=j) {
		while(j < v.size() && v[i] == v[j])
			j++;
		int place = (int)v.size() - i - max(v[i]-1, 0ll);
		ans *= ncr[place][j-i];
		if(v[i])
			rmlst *= ncr[place-1][j-i];
	}
	return ans - rmlst - 1;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<30; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for(int j=1; j<i; j++) {
			ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
		}
	}
	int T;
	cin >> T;
	for(int t=1; t<=T; t++) {
		cout << solve() << '\n';
	}
}
