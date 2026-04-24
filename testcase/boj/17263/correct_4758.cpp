#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	cout << *max_element(v.begin(), v.end());
}
