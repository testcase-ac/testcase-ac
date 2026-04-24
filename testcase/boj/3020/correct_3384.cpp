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
	int n, h;
	cin >> n >> h;
	const int n2 = n/2;
	int down[n2], up[n2];
	rep(i, n2) cin >> down[i] >> up[i];
	sort(down, down+n2);
	sort(up, up+n2, [](int i, int j){return i>j;});
	int dptr = 0, uptr = 0, ans = MOD;
	vector<int> v;
	rep(i, h) {
		while(dptr < n2 && down[dptr] <= i) dptr++;
		while(uptr < n2 && up[uptr] >= h-i) uptr++;
		int tans = n2-dptr + uptr;
		if(tans < ans) v = {tans}, ans = tans;
		else if(tans == ans) v.push_back(i+1);
	}
	cout << ans << '\n' << sz(v);
}