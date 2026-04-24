#include <bits/stdc++.h>
using namespace std;
struct Node {
	int v, l, r;
	bool operator< (const Node &a) const {
		return v < a.v;
	}
};
Node a[10000];

void setv(int l, int r) {  // set [l,r]
	if(l == r) return;
	int val = a[l].v;
	Node ref = {val,0,0};
	int pos = lower_bound(a+l+1, a+r+1, ref) - a;
	if(pos > l+1) {
		a[l].l = l+1;
		setv(l+1, pos-1);	
	}
	if(pos <= r) {
		a[l].r = pos;
		setv(pos, r);
	}
}
void ppost(int i) {
	if(a[i].l != -1) ppost(a[i].l);
	if(a[i].r != -1) ppost(a[i].r);
	cout << a[i].v << '\n';
}

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t, n = 0;
	while(!(cin >> t).eof())
		a[n++] = {t, -1, -1};
	setv(0, n-1);
	ppost(0);
}
