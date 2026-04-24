#include <bits/stdc++.h>
using namespace std;
#define int long long
void getpi(string &p, vector<int> &pi) {
    int n = p.size();
    pi.resize(n);
    int j = 0;
    for(int i=1; i<n; i++) {
        while(j && p[j] != p[i])
            j = pi[j-1];
        if(p[j] == p[i])
            j++;
        pi[i] = j;
    }
}

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, ans = 0;
	string s;
	vector<int> v;
	cin >> n >> s;
	getpi(s, v);
	vector<int> dp(n, -1);
	function<int(int)> f = [&](int t) {
		if(dp[t] != -1) return dp[t];
		if(!v[t]) return 0ll;
		if(!v[v[t]-1]) return t-v[t]+1;
		return dp[t] = f(v[t]-1) + (t - v[t] + 1);
	};
	for(int i=0; i<n; i++) {
		if(!v[i]) continue;
		//printf("f(%d) = %d\n", i, f(i));
		ans += f(i);
	}
	cout << ans;
}
