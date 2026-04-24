#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, ans = 0;
	cin >> n;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		if(t != i+1) ans++;
	}
	cout << ans;
}
