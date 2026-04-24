#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Point{
    ll x, y;
    Point operator-(Point a) {
        return {x-a.x,y-a.y};
    }
    bool operator==(Point a) {
        return tie(x,y) == tie(a.x,a.y);
    }
    ll dist() {
        return x*x+y*y;
    }
};
ll cross(Point p, Point q) {
    return p.x*q.y-p.y*q.x;
}
int ccw(Point A, Point B, Point C) {
    ll c = cross(B-A, C-B);
    if(c > 0) return 1; // ccw
    else if(c < 0) return -1; // cw
    else return 0; // colinear
}
int lieon(Point a, Point b, Point x) { // 0:NO 1:YES, inbetween 2:YES, at endpt
    if(ccw(a,b,x)) return 0;
    if(a == x || b == x) return 2;
    return min(a.x,b.x) <= x.x && x.x <= max(a.x,b.x) 
        && min(a.y,b.y) <= x.y && x.y <= max(a.y,b.y);
}
int intersect(Point A, Point B, Point C, Point D) {
    ll c1 = ccw(A,B,C), c2 = ccw(A,B,D), c3 = ccw(C,D,A), c4 = ccw(C,D,B);
    if(!c1 && !c2 && !c3 && !c4) {
        if(lieon(A,B,C)==1 || lieon(A,B,D) == 1 || lieon(C,D,A) == 1) return 2;
        return 0;
    } else {
        return c1 != c2 && c3 != c4;
    }
}
void build_chull(vector<Point>& arr, vector<Point>& chull) {
	int n = arr.size();
	if(n <= 2) {
		chull = arr;
		return;
	}
	auto it = min_element(arr.begin(), arr.end(), [](Point& a, Point& b){
		return tie(a.y, a.x) < tie(b.y, b.x);
	});
	swap(arr[0], *it);
	sort(arr.begin()+1, arr.end(), [&arr](Point &a, Point &b) {
        ll o = ccw(arr[0], a, b);
        if(o) return o > 0;
        else return (arr[0]-a).dist() < (arr[0]-b).dist();
    });
    chull = {arr[0], arr[1]};
    for(int i=2; i<n; i++) {
        while(chull.size() >= 2 && ccw(chull[chull.size()-2], chull[chull.size()-1], arr[i]) != 1)
            chull.pop_back();
        chull.push_back(arr[i]);
    }
}
bool check_line_ok(vector<Point>& hull, Point& a, Point& b) {
	for(int i=0; i<hull.size(); i++) {
		if(ccw(a, b, hull[i]) != -1)
			return 0;
	}
	return 1;
}
bool solve() {
	int n, m;
	cin >> n >> m;
	vector<Point> a(n), b(m);
	for(int i=0; i<n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	for(int i=0; i<m; i++) {
		cin >> b[i].x >> b[i].y;
	}
	// assume no zero
	if(n == 1 && m == 1)
		return 1;
	vector<Point> cha, chb;
	build_chull(a, cha);
	build_chull(b, chb);
	if(cha.size() < chb.size()) {
		swap(cha, chb);
	}
	if(cha.size() == 2 && chb.size() == 1) {
		return !lieon(cha[0], cha[1], chb[0]);
	}
	if(cha.size() == 2 && chb.size() == 2) {
		if(!ccw(cha[0], cha[1], chb[0]) && !ccw(cha[0], cha[1], chb[1]))
			return !(lieon(cha[0], cha[1], chb[0]) || lieon(cha[0], cha[1], chb[1]) || lieon(chb[0], chb[1], cha[0]));
	}
	for(int i=0; i<(int)cha.size(); i++) {
		if(check_line_ok(chb, cha[i], cha[(i+1)%cha.size()]))
			return 1;
	}
	for(int i=0; i<(int)chb.size(); i++) {
		if(check_line_ok(cha, chb[i], chb[(i+1)%chb.size()]))
			return 1;
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--)
		cout << (solve() ? "YES\n" : "NO\n");
}
