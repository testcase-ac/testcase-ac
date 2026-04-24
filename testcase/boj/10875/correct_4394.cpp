#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Pt {
	ll x, y;
	Pt operator-(Pt &a) {
		return {x-a.x, y-a.y};
	}
};
ll cross(Pt p, Pt q) {
    return p.x*q.y-p.y*q.x;
}
int ccw(Pt A, Pt B, Pt C) {
    ll c = cross(B-A, C-B);
    if(c > 0) return 1;
    else if(c < 0) return -1;
    else return 0;
}
bool on(Pt a, Pt b, Pt x) {
    return min(a.x,b.x) <= x.x && x.x <= max(a.x,b.x) && min(a.y,b.y) <= x.y && x.y <= max(a.y,b.y);
}
struct Line {
	Pt a, b;
	bool intersect(Line l) {
		int o1 = ccw(a, b, l.a), o2 = ccw(a, b, l.b), o3 = ccw(l.a, l.b, a), o4 = ccw(l.a, l.b, b);
		if(!o1 && !o2 && !o3 && !o4)
			return on(a, b, l.a) || on(a, b, l.b) || on(l.a, l.b, a);
		else
			return o1 != o2 && o3 != o4;
	}
};
vector<Line> v;
vector<pair<int, char>> arr;
int dy[] = {0,-1,0,1}, dx[] = {1,0,-1,0};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int L, n;
	cin >> L >> n;
	L++;
	v.push_back({{L,L}, {L, -L}});
	v.push_back({{-L,L}, {-L, -L}});
	v.push_back({{L, L}, {-L, L}});
	v.push_back({{L, -L}, {-L, -L}});
	int dir = 0, x = 0, y = 0;
	ll acc = 0;
	for(int i=0; i<=n; i++) {
		int t = 3e8;
		char c;
		if(i < n) {
			cin >> t >> c;
		}
		int l = 1, r = t+1, mid;
		while(l < r) {
			mid = (l+r)/2;
			int tx = x+dx[dir]*mid, ty = y+dy[dir]*mid;
			bool ok = 1;
			for(int j=0; j<max(4, (int)v.size()-1); j++) {
				Line& ln = v[j];
				if(ln.intersect({{x,y},{tx, ty}})) {
					ok = 0;
					break;
				}
			}
			if(ok)
				l = mid+1;
			else
				r = mid;
		}
		if(l > t) {
			acc += t;
			int tx = x+dx[dir]*t, ty = y+dy[dir]*t;
			v.push_back({{x,y},{tx, ty}});
			x = tx;
			y = ty;
			if(c == 'L') dir = (dir+3)%4;
			else dir = (dir+1)%4;
			//printf("i=%d, no collision. now at %d,%d\n", i, x, y);
		} else {
			//printf("i=%d, collision at %d\n", i, l);
			return !(cout << acc+l);
		}
	}
}
