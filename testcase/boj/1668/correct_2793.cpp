#include <bits/stdc++.h>
using namespace std;
int n;
int calc(int* a) {
	int mx = 0, cnt = 0;
	for(int i=0; i<n; i++) {
		if(a[i] > mx) {
			cnt++;
			mx = a[i];
		}
	}
	return cnt;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	int a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	cout << calc(a) << '\n';
	reverse(a, a+n);
	cout << calc(a);
}
