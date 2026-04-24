#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
typedef long long ll;
ll arr[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	ll l = *max_element(arr, arr+n), r = l*n;
	while(l < r) {
		ll mid = (l+r)/2;
		int cnt = 0;
		ll amount = 0;
		for(int i=0; i<n; i++) {
			if(amount < arr[i]) {
				cnt++;
				amount = mid;
			}
			amount -= arr[i];
		}
		if(cnt <= m)
			r = mid;
		else
			l = mid+1;
	}
	cout << l;
}
