#include <bits/stdc++.h>
using namespace std;

int n, m, h, ans = 4, perm[10];
bool lines[60000];

void rec(int d, int used) {
	if(d == (n-1)*h) {
		bool ok = true;
		for(int i=0; i<n; i++) {
			if(perm[i] != i) {
				ok = false;
				break;
			}
		}
		if(ok)
			ans = min(ans, used);
		return;
	}
	int b = d%(n-1);
	if(lines[d]) {
		swap(perm[b], perm[b+1]);
		rec(d+1, used);
		swap(perm[b], perm[b+1]);
	} else {
		if(used < 3 && !(lines[d] || (b&&lines[d-1]) || (b<(n-2)&&lines[d+1]))) {
			swap(perm[b], perm[b+1]);
			lines[d] = true;
			rec(d+1, used+1);
			lines[d] = false;
			swap(perm[b], perm[b+1]);
		}
		rec(d+1, used);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m >> h;
	while(m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		lines[a*(n-1)+b] = true;
	}
	for(int i=0; i<n; i++) {
		perm[i] = i;
	}
	rec(0, 0);
	cout << (ans == 4 ? -1 : ans);
}