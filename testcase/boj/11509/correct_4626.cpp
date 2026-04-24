#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6+1;
int arr[MX];
set<int> sts[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		sts[arr[i]].insert(i);
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		if(!sts[arr[i]].count(i)) continue;
		ans++;
		int p = i;
		while(1) {
			sts[arr[p]].erase(p);
			auto it = sts[arr[p]-1].lower_bound(p);
			if(it == sts[arr[p]-1].end())
				break;
			p = *it;
		}
	}
	cout << ans;
}
