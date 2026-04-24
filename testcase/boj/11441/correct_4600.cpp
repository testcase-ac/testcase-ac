#include <bits/stdc++.h>
using namespace std;

int a[100001], s[100001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
	}
	for(int i=1; i<=n; i++) {
		s[i] = s[i-1]+a[i];
	}
	int m;
	cin >> m;
	while(m--) {
		int l, r;
		cin >> l >> r;
		cout << s[r] - s[l-1] << '\n';
	}
}
