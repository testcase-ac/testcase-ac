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
#define MAXN 100000
int n;
ll bit[MAXN+1], arr[MAXN+1];
ll lsb(ll i) {return i & -i;}

void update(ll i, ll v) {
	while(i <= n) {
		bit[i] += v;
		i += lsb(i);
	}
}

ll query(ll i) {
	ll ret = 0;
	while(i) {
		ret += bit[i];
		i -= lsb(i);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	ll q;
	cin >> n >> q;
	rep(i, n) {
		cin >> arr[i+1];
		update(i+1, arr[i+1]);
	}
	while(q--) {
		ll x, y, a, b;
		cin >> x >> y >> a >> b;
		if(x > y)
			//{cout << "0\n";continue;}
			swap(x, y);
		cout << query(y) - query(x-1) << '\n';
		ll v = b - arr[a];
		arr[a] = b;
		update(a, v);
	}
}
