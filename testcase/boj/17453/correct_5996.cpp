#include <bits/stdc++.h>
using namespace std;
vector<int> ans[300];
bool ok[300];
char base[101];
char swit[20][101];
vector<int> now;
int n, m;
void f(int t) {
	if(t == m) {
		int cnt = 0;
		for(int i=0; i<n; i++) {
			if(base[i] == 0) {
				cnt--;
			} else {
				cnt++;
			}
		}
		if(!ok[cnt+n]) {
			ok[cnt+n] = 1;
			ans[cnt+n] = now;
		}
		return;
	}
	f(t+1);
	for(int i=0; i<n; i++) {
		if(swit[t][i])
			base[i] ^= 1;
	}
	now.push_back(t+1);
	f(t+1);
	now.pop_back();
	for(int i=0; i<n; i++) {
		if(swit[t][i])
			base[i] ^= 1;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	cin >> base;
	for(int i=0; i<n; i++) {
		base[i] -= '0';
	}
	for(int i=0; i<m; i++) {
		cin >> swit[i];
		for(int j=0; j<n; j++) {
			swit[i][j] -= '0';
		}
	}
	f(0);
	for(int i=-n; i<=n; i++) {
		int t = i+n;
		if(ok[t]) {
			cout << ans[t].size() << ' ';
			for(int a: ans[t])
				cout << a << ' ';
		} else {
			cout << -1;
		}
		cout << '\n';
	}
}
