#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int a[n+1], ans = 0;
	rep(i,n) cin >> a[i+1];
	bool seen[n+1] = {};
	vector<int> v;
	for(int i=1; i<=n; i++) {
		if(seen[i]) continue;
		int tseen[n+1] = {}, t = i, cnt = 1;
		tseen[i] = 1;
		bool cycle = true;
		while(1) {
			t = a[t];
			cnt++;
			if(seen[t]) {
				cycle = false;
				break;
			}
			if(tseen[t]) {
				ans += cnt - tseen[t];
				break;
			}
			tseen[t] = cnt;
		}
		for(int j=1; j<=n; j++) {
			if(tseen[j]) seen[j] = true; 
			if(cycle && tseen[j] >= tseen[t]) v.push_back(j);
		}
 	}
 	sort(v.begin(), v.end());
 	assert(ans == sz(v));
	cout << ans << '\n';
	for(int t: v) cout << t << '\n';
}
