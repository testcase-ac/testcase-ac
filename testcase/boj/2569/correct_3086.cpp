#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> arr(n), sarr, sortpos(10001), seen(n);
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	int gmin = *min_element(arr.begin(), arr.end());
	sarr = arr;
	sort(sarr.begin(), sarr.end());
	for(int i=0; i<n; i++) {
		sortpos[sarr[i]] = i;
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		if(seen[i]) continue;
		if(i == sortpos[arr[i]]) continue;
		int cur = i;
		vector<int> v;
		while(1) {
			v.push_back(arr[cur]);
			seen[cur] = 1;
			cur = sortpos[arr[cur]];
			if(seen[cur])
				break;
		}
		sort(v.begin(), v.end());
		assert(v.size() >= 2);
		int add = accumulate(v.begin(), v.end(), 0) + ((int)v.size()-2)*v[0];
		add = min(add, accumulate(v.begin()+1, v.end(), 0ll)+(v[0]+gmin)*2+gmin*((int)v.size()-1));
		ans += add;
	}
	cout << ans;
}
