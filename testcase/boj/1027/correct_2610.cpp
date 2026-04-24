#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	ll arr[n];
	int cnt[n] = {};
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			ll d = arr[j] - arr[i];
			bool ok = 1;
			for(int k=i+1; k<j; k++) {
				ll a = d*(k-i), b = j-i;
				if(arr[i]*b+a <= arr[k]*b) {
					ok = 0;
					break;
				}
			}
			if(ok)
				cnt[i]++, cnt[j]++;
		}
	}
	cout << *max_element(cnt, cnt+n) << '\n';
}
