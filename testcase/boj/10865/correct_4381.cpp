#include <bits/stdc++.h>
using namespace std;

int cnt[100001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		cnt[a]++;
		cnt[b]++;
	}
	for(int i=1; i<=n; i++) {
		cout << cnt[i] << '\n';
	}
}
