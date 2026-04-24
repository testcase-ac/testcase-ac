#include <bits/stdc++.h>
using namespace std;
const int MX = 1003;
int preorder[MX], node2in[MX];
void traverse(int prel, int inl, int d) {
	if(d == 1) {
		cout << preorder[prel] << ' ';
		return;
	}
	int root = preorder[prel], rootat = node2in[root], cf = rootat-inl, cb = inl+d-rootat-1;
	if(cf)
		traverse(prel+1, inl, cf);
	if(cb)
		traverse(prel+1+cf, rootat+1, cb);
	cout << root << ' ';
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			cin >> preorder[i];
		}
		for(int i=0; i<n; i++) {
			int t;
			cin >> t;
			node2in[t] = i;
		}
		traverse(0, 0, n);
		cout << '\n';
	}
}
