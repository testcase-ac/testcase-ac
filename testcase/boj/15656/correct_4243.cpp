#include <bits/stdc++.h>
using namespace std;
int n, m, arr[7];
vector<int> v;
void f(int d) {
	if(d == m) {
		for(int t: v) cout << t << ' ';
		cout << '\n';
		return;
	}
	for(int i=0; i<n; i++) {
		v.push_back(arr[i]);
		f(d+1);
		v.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr+n);
	f(0);
}
