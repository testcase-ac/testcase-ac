#include <bits/stdc++.h>
using namespace std;

struct Intv{
	int l, r;
};

const int MX = 1e5+3, MXL = 1e6+3;
Intv arr[MX];
int stree[MXL*2], n, dp[MX], prv[MX];
int larger(int i, int j) {
	if(i == -1)
		return j;
	if(j == -1)
		return i;
	return dp[i] < dp[j] ? j : i;
}
void update(int i, int v) {
	dp[i] = v;
	int l = arr[i].l+MXL;
	stree[l] = larger(i, stree[l]);
	while(l/=2)
		stree[l] = larger(stree[l*2], stree[l*2+1]);
}
int query(int l, int r) { // [l, r)
	l += MXL, r += MXL;
	int ret = -1;
	while(l < r) {
		if(l&1) ret = larger(stree[l++], ret);
		if(r&1) ret = larger(stree[--r], ret);
		l /= 2, r /= 2;
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> arr[i].l >> arr[i].r;
	sort(arr, arr+n, [](Intv &a, Intv &b){return a.r == b.r ? a.l > b.l : a.r < b.r;});
	memset(stree, -1, sizeof stree);
	memset(prv, -1, sizeof prv);
	update(0, 1);
	prv[0] = -1;
	int curr = 0;
	for(int i=1; i<n; i++) {
		int q = query(arr[i].l, arr[i].r);
		update(i, q == -1 ? 1 : dp[q]+1);
		prv[i] = q;
		if(dp[i] > dp[curr])
			curr = i;
	}
	cout << dp[curr] << '\n';
	while(curr != -1) {
		cout << arr[curr].l << ' ' << arr[curr].r << '\n';
		curr = prv[curr];
	}
}
