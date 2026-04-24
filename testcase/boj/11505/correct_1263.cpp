#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define deb(v) cout << #v << ':' << v

using namespace std;
#define MAXN 1000000
int n;
ll st[2*MAXN];
void update(int i, ll v) {
	for(st[i+=n] = v; i > 1; i /= 2)
		st[i/2] = (st[i] * st[i^1]) % MOD;
}

ll query(int l, int r) {
	ll ret = 1;
	for(l += n, r += n; l < r; l /= 2, r /= 2) {
		if(l&1) ret = (ret * st[l++]) % MOD;
		if(r&1) ret = (ret * st[--r]) % MOD;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int m, k;
	cin >> n >> m >> k;
	rep(i, n) cin >> st[i+n];
	for(int i=n-1; i>0; i--)
		st[i] = (st[i*2] * st[i*2+1]) % MOD;
	m += k;
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		if(a == 1)
			update(b-1, c);
		else
			cout << query(b-1, c) << '\n';
	}
}
