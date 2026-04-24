#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int a[n], l[n], r[n], s[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a, a+n);
	l[0] = 0;
	for(int i=1; i<n; i++)
		l[i] = l[i-1] + (a[i] - a[i-1]) * i;
	r[n-1] = 0;
	for(int i=n-2; i>=0; i--)
		r[i] = r[i+1] + (a[i+1] - a[i]) * (n-1-i);
	int mn = INT_MAX, mi = 0;
	for(int i=0; i<n; i++) {
		if(l[i]+r[i] < mn) {
			mn = l[i]+r[i];
			mi = i;
		}
	}
	cout << a[mi];
}
