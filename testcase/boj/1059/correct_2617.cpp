#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr+n);
	int l = 0, t;
	cin >> t;
	for(int r: arr) {
		if(t <= r) {
			if(t == r)
				return !(cout << 0);
			return !(cout << (t-l)*(r-t)-1);
		}
		l = r;
	}
}
