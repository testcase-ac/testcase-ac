#include <bits/stdc++.h>
using namespace std;
struct line {
	int xi, yi, xe, ye, w;
};
const int MX = 3e5, BUK = 550;
vector<int> buk_x[BUK], buk_y[BUK];
line arr[MX];
pair<int, int> qry[MX];
bool deleted[MX];
int n, k, l;
void init() {
	cin >> n >> k >> l;
	map<int,int> x, y;
	for(int i=0; i<k; i++) {
		cin >> arr[i].xi >> arr[i].yi >> arr[i].xe >> arr[i].ye >> arr[i].w;
		x[arr[i].xi] = 0;
		x[arr[i].xe] = 0;
		y[arr[i].yi] = 0;
		y[arr[i].ye] = 0;
		deleted[i] = 0;
	}
	for(int i=0; i<l; i++) {
		cin >> qry[i].first >> qry[i].second;
		if(qry[i].second) {
			x[qry[i].first] = 0;
		} else {
			y[qry[i].first] = 0;
		}
	}
	int p = 0;
	for(auto& pr: x)
		pr.second = p++;
	p = 0;
	for(auto& pr: y)
		pr.second = p++;
	for(int i=0; i<k; i++) {
		arr[i].xi = x[arr[i].xi];
		arr[i].xe = x[arr[i].xe];
		arr[i].yi = y[arr[i].yi];
		arr[i].ye = y[arr[i].ye];
		if(arr[i].xi > arr[i].xe)
			swap(arr[i].xi, arr[i].xe);
		if(arr[i].yi > arr[i].ye)
			swap(arr[i].yi, arr[i].ye);
	}
	for(int i=0; i<l; i++) {
		if(qry[i].second)
			qry[i].first = x[qry[i].first];
		else
			qry[i].first = y[qry[i].first];
	}
}
void build() {
	for(int i=0; i<BUK; i++) {
		buk_x[i].clear();
		buk_y[i].clear();
	}
	for(int i=0; i<k; i++) {
		if(deleted[i]) continue;
		buk_x[arr[i].xi/BUK].push_back(i);
		buk_y[arr[i].yi/BUK].push_back(i);
	}
	for(int i=0; i<BUK; i++) {
		sort(buk_x[i].begin(), buk_x[i].end(), [&](int a, int b){
			return arr[a].xe > arr[b].xe;
		});
		sort(buk_y[i].begin(), buk_y[i].end(), [&](int a, int b){
			return arr[a].ye > arr[b].ye;
		});
	}
}
int rmcnt;
void solve() {
	init();
	build();
	rmcnt = 0;
	for(int t=0; t<l; t++) {
		auto [a,b] = qry[t];
		int ans = 0;
		if(b) {
			for(int i=0; i<a/BUK; i++) {
				for(int j: buk_x[i]) {
					if(arr[j].xe < a) break;
					if(deleted[j]) continue;
					ans = max(ans, arr[j].w);
					deleted[j] = 1;
					rmcnt++;
				}
			}
			for(int j: buk_x[a/BUK]) {
				if(deleted[j]) continue;
				if(arr[j].xi <= a && a <= arr[j].xe) {
					ans = max(ans, arr[j].w);
					deleted[j] = 1;
					rmcnt++;
				}
			}
		} else {
			for(int i=0; i<a/BUK; i++) {
				for(int j: buk_y[i]) {
					if(arr[j].ye < a) break;
					if(deleted[j]) continue;
					ans = max(ans, arr[j].w);
					deleted[j] = 1;
					rmcnt++;
				}
			}
			for(int j: buk_y[a/BUK]) {
				if(deleted[j]) continue;
				if(arr[j].yi <= a && a <= arr[j].ye) {
					ans = max(ans, arr[j].w);
					deleted[j] = 1;
					rmcnt++;
				}
			}
		}
		cout << ans << '\n';
		if(rmcnt > BUK) {
			build();
			rmcnt = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		solve();
}
