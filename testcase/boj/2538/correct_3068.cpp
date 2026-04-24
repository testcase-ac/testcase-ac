#include <bits/stdc++.h>
using namespace std;
#define int long long
int R, C, n;
vector<pair<int, int>> arr;
bool on_edge(pair<int, int> x) {
	auto [a, b] = x;
	return a == 0 || a == R || b == 0 || b == C;
}
int dist(pair<int, int> a, pair<int, int> b) {
	return abs(a.first-b.first) + abs(a.second - b.second);
}
bool on_same_side(pair<int, int> a, pair<int, int> b) {
	return on_edge(a) && on_edge(b) && ((a.first == R && b.first == R) || (!a.first && !b.first) || (!a.second && !b.second) || (a.second == C && b.second == C));
}
int edge_dist(pair<int, int> lst, pair<int, int> nxt) {
	int sum = 0;
	while(lst != nxt) {
		if(lst.first == R && lst.second) {
			lst.second--;
			sum++;
		} else if(!lst.second && lst.first) {
			lst.first--;
			sum++;
		} else if(!lst.first && lst.second < C) {
			lst.second++;
			sum++;
		} else if(lst.second == C && lst.first < R) {
			lst.first++;
			sum++;
		} else {
			return 0;
		}
	}
	return sum;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> C >> R >> n;
	arr.resize(2*n);
	for(int i=0; i<n; i++) {
		cin >> arr[i].second >> arr[i].first;
		arr[n+i] = arr[i];
	}
	int cnt = 0, ans = 0, allsum = 0;
	for(int i=0; i<n; i++) {
		auto cur = arr[i], nxt = arr[i+1];
		allsum += dist(cur, nxt);
		if(on_edge(cur) && on_edge(nxt) && !on_same_side(cur, nxt)) {
			ans = max(ans, edge_dist(cur, nxt)+dist(cur, nxt));
			cnt++;
		} else if(on_edge(cur) && !on_edge(nxt)) {
			cnt++;
		}
	}
	for(int i=1, j=1; i<2*n; i=j) {
		if(on_edge(arr[j])) {
			j++;
			continue;
		}
		int sum = 0;
		while(j < 2*n && !on_edge(arr[j])) {
			sum += dist(arr[j-1], arr[j]);
			j++;
		}
		sum += dist(arr[j-1], arr[j]);
		if(j < 2*n) {
			//printf("at i=%d, j=%d, sum = %d, edge_dist=%d\n", i, j, sum, edge_dist(arr[i-1], arr[j]));
			sum += edge_dist(arr[i-1], arr[j]);
			ans = max(sum, ans);
		}
	}
	if(!cnt) {
		cout << "1 " << R*2+C*2+allsum;
	} else {
		cout << cnt << ' ' << ans;
	}
}
