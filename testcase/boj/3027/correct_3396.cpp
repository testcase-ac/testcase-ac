#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Rect {
	int x1, y1, z1, x2, y2, z2;
	void swp() {
		swap(x1, y1);
		swap(y1, z1);
		swap(x2, y2);
		swap(y2, z2);
	}
	void read() {
		cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
	}
	void reg() {
		if(x1 > x2)
			swap(x1, x2);
		if(y1 > y2)
			swap(y1, y2);
		if(z1 > z2)
			swap(z1, z2);
	}
	bool operator<(const Rect& r) const {
		return z2 > r.z2;
	}
};
int n;
vector<Rect> arr;
int ans;
int lsb(int i) {return i&(-i);}
const int N = 1000;
struct Fenwick2D {
	int arr[N][N];
	void init() {
		memset(arr, 0, sizeof arr);
	}
	void update(int r, int c, int t) {
		for(int i=r; i<N; i+=lsb(i)) {
			for(int j=c; j<N; j+=lsb(j)) {
				arr[i][j] += t;
			}
		}
	}
	int query(int r, int c) {
		int ret = 0;
		for(int i=r; i; i-=lsb(i)) {
			for(int j=c; j; j-=lsb(j)) {
				ret += arr[i][j];
			}
		}
		return ret;
	}

};
Fenwick2D st, ed;
void solve() {
	vector<Rect> yfix, zfix;
	for(int i=0; i<n; i++) {
		if(arr[i].y1 == arr[i].y2) {
			yfix.push_back(arr[i]);
			yfix.back().reg();
		} else if(arr[i].z1 == arr[i].z2) {
			zfix.push_back(arr[i]);
			zfix.back().reg();
		}
	}
	//printf("yfix.size() = %u, zfix.size() = %u\n", yfix.size(), zfix.size());
	sort(yfix.begin(), yfix.end(), [](Rect a, Rect b){return a.z1 > b.z1;});
	sort(zfix.begin(), zfix.end(), [](Rect a, Rect b){return a.z1 > b.z1;});
	priority_queue<Rect> pq;
	st.init();
	ed.init();
	int tans = 0;
	auto query = [&](Rect p) {
		return st.query(p.y2, p.x2) - st.query(p.y1-1, p.x2) - ed.query(p.y2, p.x1-1) + ed.query(p.y1-1, p.x1-1);
	};
	for(int z=1; z<=999; z++) {
		while(yfix.size() && yfix.back().z1 == z) {
			Rect p = yfix.back();
			yfix.pop_back();
			tans += query(p);
			st.update(p.y1, p.x1, 1);
			ed.update(p.y1, p.x2, 1);
			pq.push(p);
		}
		while(zfix.size() && zfix.back().z1 == z) {
			Rect p = zfix.back();
			zfix.pop_back();
			tans += query(p);
		}
		while(pq.size() && pq.top().z2 == z) {
			Rect p = pq.top();
			pq.pop();
			st.update(p.y1, p.x1, -1);
			ed.update(p.y1, p.x2, -1);
		}
	}
	ans += tans;
}
void swp() {
	for(int i=0; i<n; i++) arr[i].swp();
}
int32_t main() {
	cin >> n;
	arr.resize(n);
	for(int i=0; i<n; i++) {
		arr[i].read();
	}
	solve();
	swp();
	solve();
	swp();
	solve();
	cout << ans;
}
