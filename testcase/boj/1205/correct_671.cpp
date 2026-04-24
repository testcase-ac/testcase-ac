#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, sc, p;
	cin >> n >> sc >> p;
	if(!n) return !(cout << 1);
	int arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	auto pr = equal_range(arr, arr+n, sc, [](int a, int b) {return a>b;});
	int l = pr.first - arr, r = pr.second - arr;
	if(r < p) cout << l+1;
	else cout << -1;
}
