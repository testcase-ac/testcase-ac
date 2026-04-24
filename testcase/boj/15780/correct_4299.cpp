#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k, acc = 0;
	cin >> n >> k;
	for(int i=0; i<k; i++) {
		int t;
		cin >> t;
		acc += (t+1)/2;
	}
	cout << (acc >= n ? "YES" : "NO");
}
