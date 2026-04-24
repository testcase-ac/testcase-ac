#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
struct info {
	int w, a, b;
	bool operator< (info i) {
		return w > i.w;
	}
};
info arr[MX], qry[MX];
int ans[MX], par[MX], sz[MX];
int f(int i){return i == par[i] ? i : par[i] = f(par[i]);}
void join(int i, int j) {
	i = f(i);
	j = f(j);
	if(i != j) {
		par[i] = j;
		sz[j] += sz[i];
	}
}
int main() {
	int n, q;
	cin >> n >> q;
	for(int i=0; i<n-1; i++) {
		int u,v,w;
		cin >> u >> v >> w;
		arr[i] = {w, u, v};
	}
	for(int i=1; i<=n; i++) {
		par[i] = i;
		sz[i] = 1;
	}
	sort(arr, arr+n-1);
	for(int i=0; i<q; i++) {
		int k, v;
		cin >> k >> v;
		qry[i] = {k, v, i};
	}
	sort(qry, qry+q);
	int ptr = 0;
	for(int i=0; i<q; i++) {
		while(ptr < n-1 && arr[ptr].w >= qry[i].w) {
			join(arr[ptr].a, arr[ptr].b);
			ptr++;
		}
		ans[qry[i].b] = sz[f(qry[i].a)];
	}
	for(int i=0; i<q; i++)
		cout << ans[i]-1 << '\n';
}
