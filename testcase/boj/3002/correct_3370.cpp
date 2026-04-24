#include <bits/stdc++.h>
using namespace std;
// Iterative lazy segment tree implementation adapted for this solution.
// Reference: https://codeforces.com/blog/entry/18051
const int MX = 2.5e5+2;
int tree[2*MX][10], delay[MX], n, h;
int sumat(int i) {
	int s = 0;
	for(int j=0; j<10; j++)
		s += tree[i][j] * j;
	return s;
}
void rotateby(int i, int d) {
	d %= 10;
	if(!d) return;
	rotate(tree[i], tree[i]+(10-d), tree[i]+10);
	if(i < n)
		delay[i] += d;
}
void pull(int p) {
	for(int i=h; i; i--) {
		int j = p >> i;
		rotateby(2*j, delay[j]);
		rotateby(2*j+1, delay[j]);
		delay[j] = 0;
	}
}
void buildat(int p) {
	for(int i=0; i<10; i++)
		tree[p][i] = tree[p*2][i] + tree[p*2+1][i];
}
void build(int p) {
	while((p /= 2) >= 1) {
		buildat(p);
		int d = delay[p];
		delay[p] = 0;
		rotateby(p, d);
	}
}
int rotate_query(int l, int r) {
	l += n, r += n;
	int l0 = l, r0 = r;
	pull(l);
	pull(r-1);
	int res = 0;
	while(l < r) {
		if(l&1) {
			res += sumat(l);
			rotateby(l, 1);
			l++;
		}
		if(r&1) {
			r--;
			res += sumat(r);
			rotateby(r, 1);
		}
		l /= 2, r /= 2;
	}
	build(l0);
	build(r0-1);
	return res;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m;
	string s;
	cin >> n >> m >> s;
	h = 32 - __builtin_clz(n);
	for(int i=0; i<n; i++) {
		tree[n+i][s[i]-'0'] = 1;
	}
	for(int i=n-1; i; i--)
		buildat(i);
	while(m--) {
		int l, r;
		cin >> l >> r;
		cout << rotate_query(l-1, r) << '\n';
	}
}
