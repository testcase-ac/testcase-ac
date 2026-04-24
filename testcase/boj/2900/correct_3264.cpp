#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MX = 1e6+3;
ll cnt[MX], acc[MX];
ll get(int i) {return i >= 0 ? acc[i] : 0;}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=0; i<k; i++) {
		int t;
		cin >> t;
		cnt[t]++;
	}
	for(int i=1; i<n; i++) {
		if(cnt[i]) {
			int t = 0;
			while(t < n) {
				acc[t] += cnt[i]; 
				t += i;
			}
		}
	}
	for(int i=1; i<n; i++) {
		acc[i] += acc[i-1];
	}
	int q;
	cin >> q;
	while(q--) {
		int l, r;
		cin >> l >> r;
		cout << get(r) - get(l-1) << '\n';
	}
}
