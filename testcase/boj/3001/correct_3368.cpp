#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll dp[16][200], A, B;
int S;

ll query(ll x) {
	string str = to_string(x);
	int n = str.size();
	int curr = S;
	ll ret = 0;
	for(int i=n; i>=1; i--) {
		int d = str[n-i]-'0';
		for(int j=0; j<d; j++) {
			if(curr-j<0) break;
			ret += dp[i-1][curr-j];
		}
		curr -= d;
		if(curr < 0) break;
		if(i == 1 && !curr) ret++;
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> A >> B >> S;
	dp[0][0] = 1;
	for(int i=0; i<=9; i++) {
		dp[1][i] = 1;
	}
	for(int d=1; d<15; d++) {
		for(int s=0; s<=135; s++) {
			if(!dp[d][s]) continue;
			for(int i=0; i<=9; i++) {
				dp[d+1][s+i] += dp[d][s];
			}
		}
	}
	ll aqry = query(A-1), bqry = query(B);
	cout << bqry - aqry << '\n';
	ll l = A, r = B, mid;
	while(l < r) {
		mid = (l+r)/2;
		if(query(mid) > aqry)
			r = mid;
		else
			l = mid+1;
	}
	cout << l << '\n';
}
