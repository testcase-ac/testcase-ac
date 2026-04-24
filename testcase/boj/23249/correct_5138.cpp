#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
    double x, y;
};

int ccw(point a, point b, point c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1;
    if (v > 0) return +1;
    return 0;
}
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	int N;
	cin >> N;
	vector<point> V(N);
	for(int i=0; i<N; i++) {
		cin >> V[i].x >> V[i].y;
	}
	int ans = 0;
	sort(V.begin(), V.end(), [](auto a, auto b) {
		return tie(a.y, a.x) < tie(b.y, b.x);
	});
	for(int st=0; st<N; st++) {
		vector<point> cur(V.begin() + st +1 , V.end());
		sort(cur.begin(), cur.end(), [&](auto a, auto b) {
			return ccw(V[st], a, b) == 1;
		});
		for(int i=0; i+1<cur.size(); i++) {
			point mn = cur[i+1];
			for(int j=i+2; j<cur.size(); j++) {
				if(ccw(cur[i], mn, cur[j]) == 1)
					mn = cur[j];
				else
					ans++;
			}
		}
	}
	cout << ans;
}
