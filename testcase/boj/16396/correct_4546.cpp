#include <bits/stdc++.h>
using namespace std;
const int MX = 10002;
int arr[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int a, b;
		cin >> a >> b;
		arr[a]++;
		arr[b]--;
	}
	int ans = 0, cur = 0;
	for(int i=1; i<MX; i++) {
		cur += arr[i];
		if(cur)
			ans++;
	}
	cout << ans;
}
