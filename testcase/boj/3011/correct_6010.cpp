#include <bits/stdc++.h>
using namespace std;

int n, arr[100], A, B, mx, mxv = 0;
void check(int t) {
	if(!(A <= t && t <= B)) return;
	int dist = INT_MAX;
	for(int i=0; i<n; i++) {
		dist = min(dist, abs(t-arr[i]));
	}
	if(dist > mxv) {
		mx = t;
		mxv = dist;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr+n);
	cin >> A >> B;
	check(A|1);
	check(B%2 ? B : B-1);
	for(int i=0; i<n-1; i++) {
		int c = (arr[i]+arr[i+1])/2;
		check(c|1);
	}
	cout << mx;
}
