#include <bits/stdc++.h>
using namespace std;
map<int,int> mpa, mpb;
int a[2000], b[2000];
void f(int *arr, map<int,int>& mp, int n) {
	memcpy(arr+n, arr, sizeof(int)*n);
	mp[0] = 1;
	mp[accumulate(arr, arr+n, 0)] = 1;
	for(int i=0; i<n; i++) {
		int sum = 0;
		for(int j=i; j<i+n-1; j++) {
			sum += arr[j];
			mp[sum]++;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int sz, m, n;
	cin >> sz >> m >> n;
	for(int i=0; i<m; i++) {
		cin >> a[i];
	}
	for(int i=0; i<n; i++) {
		cin >> b[i];
	}
	f(a, mpa, m);
	f(b, mpb, n);
	long long ans = 0;
	for(auto pr: mpa)
		ans += pr.second * mpb[sz-pr.first];
	cout << ans;
}
