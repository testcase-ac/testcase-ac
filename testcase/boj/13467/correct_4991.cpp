#include <bits/stdc++.h>
using namespace std;
struct rect {
	int x1, y1, x2, y2;
};
int cnt[4000][4000];
#define uize(v) sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
#define compress(v, x) lower_bound(v.begin(), v.end(), x) - v.begin()
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	int N;
	cin >> N;
	vector<rect> rects;
	for(int i=0; i<N; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		int xmin = x - d, xmax = x + d;
		rects.push_back({xmin+y, xmin-y, xmax+y, xmax-y});
	}
	vector<int> xs, ys;
	for(auto r : rects) {
		xs.push_back(r.x1);
		xs.push_back(r.x2);
		ys.push_back(r.y1);
		ys.push_back(r.y2);
	}
	uize(xs);
	uize(ys);
	for(auto &r : rects) {
		r.x1 = compress(xs, r.x1);
		r.x2 = compress(xs, r.x2);
		r.y1 = compress(ys, r.y1);
		r.y2 = compress(ys, r.y2);
	}
	for(auto r : rects) {
		for(int x=r.x1; x<=r.x2; x++) {
			cnt[x][r.y1]++;
			if(r.y1 != r.y2)
				cnt[x][r.y2]++;
		}
		for(int y=r.y1+1; y<r.y2; y++) {
			cnt[r.x1][y]++;
			cnt[r.x2][y]++;
		}
	}
	int ansx = -1, ansy = -1, anscnt = 0;
	for(int x=0; x<xs.size(); x++) {
		for(int y=0; y<ys.size(); y++) {
			if(cnt[x][y] == N) {
				bool valid = 1;
				int oy = xs[x] - ys[y], ox = xs[x] + ys[y];
				if(ox % 2 == 0 && oy % 2 == 0) {
					anscnt++;
					ansx = ox / 2;
					ansy = oy / 2;
				}
			}
		}
	}
	if(anscnt == 1) {
		cout << ansx << ' ' << ansy;
	} else if(anscnt >= 2) {
		cout << "uncertain";
	} else {
		cout << "impossible";
	}
}
