#include <bits/stdc++.h>
using namespace std;

int a = 1e9+7, b = a, n;
int arr[100000];

void update(int c, int d) {
	if(c == d || !(0 <= c && c < n && 0 <= d && d < n)) return;
	if(abs(arr[c]+arr[d]) < abs(a+b)) {
		tie(a,b) = tie(arr[c],arr[d]);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr+n);
	for(int i=0; i<n; i++) {
		int j = lower_bound(arr, arr+n, -arr[i]) - arr;
		update(i, j);
		update(i, j+1);
		update(i, j-1);
	}
	cout << a << ' ' << b;
}
