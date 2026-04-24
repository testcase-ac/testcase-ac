#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 50000;
map<int,int> comp;
pair<int, int> cows[MX];
int cur[MX], nxt, n, cnt, ans = INT_MAX;
void add(int i) {
	cur[cows[i].second]++;
	if(cur[cows[i].second] == 1)
		cnt++;
}
void sub(int i) {
	cur[cows[i].second]--;
	if(!cur[cows[i].second])
		cnt--;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> cows[i].first >> cows[i].second;
		comp[cows[i].second] = 0;
	}
	for(auto& pr: comp)
		pr.second = nxt++;
	sort(cows, cows+n);
	for(int i=0; i<n; i++) {
		cows[i].second = comp[cows[i].second];
	}
	int j = 0;
	for(int i=0; i<n; i++) {
		while(j < n && cnt < nxt) {
			add(j++);
		}
		if(cnt < nxt)
			break;
		//printf("at i=%d, j=%d, set %d\n", i, j, cows[j-1].first - cows[i].first);
		ans = min(ans, cows[j-1].first - cows[i].first);
		sub(i);
	}
	cout << ans;
}
