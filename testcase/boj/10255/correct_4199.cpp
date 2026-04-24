#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
	/*
	0: Does not intersect.
	1: Is or is not equal straight line and intersect at exactly one point.
	2: Is equal straight line, and intersect at infinitely many point.
	*/
	ll c1 = ccw(A,B,C), c2 = ccw(A,B,D), c3 = ccw(C,D,A), c4 = ccw(C,D,B);
	if(!c1 && !c2 && !c3 && !c4) {
		if(lieon(A,B,C)==1 || lieon(A,B,D) == 1 || lieon(C,D,A) == 1) return 2;
		if(A == C) return ((D-A).dist() < (D-B).dist()) ? 1 : 2;
		if(A == D) return ((C-A).dist() < (C-B).dist()) ? 1 : 2;
		if(B == C) return ((D-A).dist() > (D-B).dist()) ? 1 : 2;
		if(B == D) return ((C-A).dist() > (C-B).dist()) ? 1 : 2;
		return 0;
	} else {
		return c1 != c2 && c3 != c4;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		Point LB, RT, A, X;
		cin >> LB.x >> LB.y >> RT.x >> RT.y >> A.x >> A.y >> X.x >> X.y;
		Point rect[4] = {LB, {RT.x,LB.y}, RT, {LB.x,RT.y}};
		bool corner[4] = {}, inf = false;
		int cnt = 0;
		for(int i=0; i<4; i++) {
			int j = (i+1)%4;
			int res = intersect(rect[i], rect[j], A, X);
			if(res == 1) {
				if(lieon(A,X,rect[i]))
					corner[i] = true;
				else if(lieon(A,X,rect[j]))
					corner[j] = true;
				else
					cnt++;
			} else if(res == 2) {
				inf = true;
				break;
			}
		}
		if(inf) cout << "4\n";
		else {
			for(bool b: corner) cnt += b;
			cout << cnt << '\n';
		}
	}
}
