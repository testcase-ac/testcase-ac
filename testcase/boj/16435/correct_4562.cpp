#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, l;
	cin >> n >> l;
	vector<int> a(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	for(int t: a) {
		if(t > l)
			break;
		l++;
	}
	cout << l;
}
