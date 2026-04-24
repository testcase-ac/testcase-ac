#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	list<int> ls;
	list<int>::iterator itarr[n+1];
	for(int i=1; i<=n; i++) {
		ls.push_back(i);
		itarr[i] = prev(ls.end());
	}
	while(m--) {
		char c;
		int a, b;
		cin >> c >> a >> b;
		ls.splice(c == 'A' ? itarr[b] : next(itarr[b]), ls, itarr[a]);
	}
	vector<int> dp(n, INT_MAX), pre(n+1, -1);
	int lis = 0;
	for(int v: ls) {
		auto it = lower_bound(dp.begin(), dp.end(), v);
		*it = min(*it, v);
		if(it != dp.begin())
			pre[v] = *prev(it);
		lis = max(lis, (int)(it-dp.begin()+1));
	}
	printf("%d\n", n-lis);
	bool inlis[n+1] = {};
	int curr = dp[lis-1];
	while(curr != -1) {
		inlis[curr] = 1;
		curr = pre[curr];
	}
	if(!inlis[1])
		printf("A 1 %d\n", ls.front());
	for(int i=2; i<=n; i++) {
		if(!inlis[i])
			printf("B %d %d\n", i, i-1);
	}
}
