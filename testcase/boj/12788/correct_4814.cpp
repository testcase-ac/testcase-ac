#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll arr[1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr+n, greater<ll>());
	ll sum = 0;
	for(int i=0; i<n; i++) {
		sum += arr[i];
		if(sum >= m*k) return !(cout << i+1);
	}
	cout << "STRESS";
}
