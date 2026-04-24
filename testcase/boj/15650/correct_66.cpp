#include <bits/stdc++.h>
using namespace std;
int n, m, ans[8];
void rec(int i, int nxt) {
	if(i == m) {
		for(int j=0; j<m; j++) {
			cout << ans[j] << ' ';
		}
		cout << '\n';
		return;
	}
	if(nxt > n) return;
	ans[i] = nxt;
	rec(i+1, nxt+1);
	rec(i, nxt+1);
}
int main() {
	cin >> n >> m;
	rec(0,1);
}
