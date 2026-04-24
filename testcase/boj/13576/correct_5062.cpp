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
	string s;
	cin >> s;
	vector<int> pi;
	getpi(s, pi);
	int t = pi.back(), n = s.size();
	vector<int> cnt(n), v(n);
	for(int k: pi)
		cnt[k]++;
	for(int i=n-1; i; i--) {
		v[i] += cnt[i];
		cnt[pi[i-1]] += cnt[i];
	}
	vector<int> ans;
	while(t) {
		ans.push_back(t);
		t = pi[t-1];
	}
	sort(ans.begin(), ans.end());
	cout << ans.size()+1 << '\n';
	for(int k: ans) {
		cout << k << ' ' << v[k]+1 << '\n';
	}
	cout << n << " 1\n";
}
