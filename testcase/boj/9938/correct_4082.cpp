#include <bits/stdc++.h>
using namespace std;
const int MX = 3e5+2;
int par[MX];
bool has[MX];
int f(int i) {return par[i] == i ? i : par[i] = f(par[i]);}
int join(int a, int b) {
	if(!has[a]) {
		has[a] = 1;
		par[a] = f(b);
	}
	else if(!has[b]) {
		has[b] = 1;
		par[b] = f(a);
	}
	else if(!has[f(a)]) {
		has[f(a)] = 1;
		par[f(a)] = f(b);
	} else if (!has[f(b)]) {
		has[f(b)] = 1;
		par[f(b)] = f(a);
	} else return 0;
	return 1;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, l;
	cin >> n >> l;
	for(int i=1; i<=l; i++) {
		par[i] = i;
	}
	for(int i=0; i<n; i++) {
		int a, b;
		cin >> a >> b;
		cout << (join(a, b) ? "LADICA\n" : "SMECE\n");
	}
}
