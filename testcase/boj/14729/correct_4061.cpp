#include <bits/stdc++.h>
using namespace std;
const int MX = 1e7;
int arr[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		double d;
		cin >> d;
		arr[i] = (int)(d*1000);
	}
	make_heap(arr, arr+n, greater<int>());
	int t = 7;
	cout << fixed << setprecision(3);
	while(t--) {
		cout << ((double)arr[0])/1000 << '\n';
		pop_heap(arr, arr+n, greater<int>());
		n--;
	}
}
