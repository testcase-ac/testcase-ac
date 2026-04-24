#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point{
    int x, y;
    point operator-(point a) {
        return {x-a.x,y-a.y};
    }
    bool operator== (point a) {
        return tie(x,y) == tie(a.x,a.y);
    }
    int dot(point p) {
        return x*p.x + y*p.y;
    }
    int cross(point p) {
        return x*p.y - y*p.x;
    }
    int distsq(point p) {
        return (x-p.x) * (x-p.x) + (y-p.y) * (y-p.y);
    }
};
int cross(point p, point q) {
    return p.x*q.y-p.y*q.x;
}
int ccw(point A, point B, point C) {
    int c = cross(B-A, C-B);
    if(c > 0) return 1; // ccw
    else if(c < 0) return -1; // cw
    else return 0; // colinear
}
int lieon(point a, point b, point x) { // 0:NO 1:YES, inbetween 2:YES, at endpt
    /*
    return |     state
       0   |   not lying
       1   |  lie inbetween
       2   | lie on endpoint
    */
    if(ccw(a,b,x)) return 0;
    if(a == x || b == x) return 2;
    return min(a.x,b.x) <= x.x && x.x <= max(a.x,b.x) 
        && min(a.y,b.y) <= x.y && x.y <= max(a.y,b.y);
}
int intersect(point a1, point a2, point b1, point b2) {
    /*
    return | eql_line? | intersect_cnt?
       0   |     X     |       0
       1   |     X     |       1
       2   |     O     |       0
       3   |     O     |       1
       4   |     O     |      inf
    */
    if((a2-a1).cross(b2-b1)) { // not equal line
        if(ccw(a1, a2, b1) != ccw(a1, a2, b2) && ccw(b1, b2, a1) != ccw(b1, b2, a2))
            return 1;
        else
            return 0;
    } else { // equal line
        int l1 = lieon(a1, a2, b1), l2 = lieon(a1, a2, b2);
        if(l1 == 1 || l2 == 1)
            return 4;
        if(l1 == 2 || l2 == 2)
            return 3;
        return 2;       
    }
}
struct line {
	point a, b;
	bool intersects(line l) {
		int r = intersect(a, b, l.a, l.b);
		return r == 1 || r >= 3;
	}
	void read() {
		cin >> a.x >> a.y >> b.x >> b.y;
		if(a.x > b.x)
			swap(a, b);
	}
	line lup() {
		return {a, {a.x, 10005}};
	}
	line ldown() {
		return {a, {a.x, -2}};
	}
	line rup() {
		return {b, {b.x, 10005}};
	}
	line rdown() {
		return {b, {b.x, -2}};
	}
};
bool between(int a, int x, int b) {
	return a <= x && x <= b;
}
line arr[5000];
vector<int> adj[5000];
bool seen[5000];
void dfs(int i) {
	if(seen[i])
		return;
	seen[i] = 1;
	for(int t: adj[i])
		dfs(t);
	cout << i+1 << ' ';
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		arr[i].read();
	}
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			line& a = arr[i], b = arr[j];
			if(!between(a.a.x, b.a.x, a.b.x) && !between(a.a.x, b.b.x, a.b.x) && !between(b.a.x, a.a.x, b.b.x))
				continue;
			if(a.lup().intersects(b) || a.rup().intersects(b) || b.ldown().intersects(a) || b.rdown().intersects(a)) {
				adj[j].push_back(i);
				//printf("%d is dependent on %d\n", j+1, i+1);
			} else {
				adj[i].push_back(j);
				//printf("%d is dependent on %d\n", i+1, j+1);
			}
		}
	}
	for(int i=0; i<n; i++) {
		dfs(i);
	}
}
