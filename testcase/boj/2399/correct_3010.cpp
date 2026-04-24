#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a, a+n);
	long long ans = 0;
	for(int i=0; i<n-1; i++) {
		int l = i+1, r = n-1-i;
		ans += (long long)l * r * (a[i+1]-a[i]);
	}
	cout << ans*2;
}
