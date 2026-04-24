#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, c;
	cin >> n >> c;
	int a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	int ans = 0;
	for(int i=1; i<=c; i++) {
		for(int j=0; j<n; j++) {
			if(i % a[j] == 0) {
				ans++;
				break;
			}
		}
	}
	cout << ans;
}
