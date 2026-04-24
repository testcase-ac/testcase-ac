#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
struct point {
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
int ccw(point A, point B, point C) {
    int c = (B-A).cross(C-B);
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
int intersect_cnt(pair<point, point> a, pair<point, point> b) {
	int r = intersect(a.first, a.second, b.first, b.second);
	return (r == 1);
}
int intersect_dbl(point A, point X, point B, point Y, pair<double, double>& ts) {
    /*
    Line 1: A+ta, Line 2: B+sb.
    0: Not colinear and does not intersect/1: Not colinear and intersect at one point. ts is t,s.
    2: colinear but not on the same line. ts is nothing.
    3: colinear and on same line, but do not intersect. ts is {B,Y} in terms of t.
    4: colinear and intersect at infinitely many point. ts is {B,Y} in terms of t.
    5: colinear and intersect at exactly one point. ts is t,s.
    */
    point a = X-A, b = Y-B, sub = B-A;
    int det = a.cross(b), tp = sub.cross(b), sp = sub.cross(a);
    if(!det) { // a and b are colinear
        if(tp) {
            return 2;
        } else {
            int d = a.dot(a);
            double t = (double)sub.dot(a)/d, s = t + (double)b.dot(a)/d;
            if(X == B && s > 1) {
                ts = {1,0};
                return 5;
            } else if(X == Y && t > 1) {
                ts = {1,1};
                return 5;
            } else if(A == B && s < 0) {
                ts = {0,0};
                return 5;
            } else if(A == Y && t < 0) {
                ts = {0,1};
                return 5;
            }
            ts = {t,s};
            return ((0 <= t && t <= 1)||(0 <= s && s <= 1)||(t <= 0 && s >= 1)||(s <= 0 && t >= 1))
                            ? 4 : 3;
        }
    } else {
        double t = (double)tp/(double)det, s = (double)sp/(double)det;
        ts = {t,s};
        return (0 <= t && t <= 1 && 0 <= s && s <= 1) ? 1 : 0;
    }
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<pair<point, point>> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i].first.x >> v[i].first.y >> v[i].second.x >> v[i].second.y;
		if(tie(v[i].first.x, v[i].first.y) > tie(v[i].second.x, v[i].second.y)) {
			swap(v[i].first, v[i].second);
		}
	}
	sort(v.begin(), v.end(), [](auto a, auto b){return tie(a.first.x, a.first.y, a.second.x, a.second.y) < tie(b.first.x, b.first.y, b.second.x, b.second.y);});
	bool ok;
	do {
		ok = 1;
		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				if(intersect(v[i].first, v[i].second, v[j].first, v[j].second) >= 3) {
					//printf("merge %d,%d-%d,%d and %d,%d-%d,%d\n", v[i].first.x, v[i].first.y, v[i].second.x, v[i].second.y, v[j].first.x, v[j].first.y, v[j].second.x, v[j].second.y);
					ok = 0;
					v[i].second = v[j].second;
					v.erase(v.begin()+j);
					n--;
					goto end;			
				}
			}
		}
		end:;
	} while(!ok);
	int ans = 0;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			for(int k=j+1; k<n; k++) {
				if(intersect_cnt(v[i], v[j]) && intersect_cnt(v[i], v[k]) && intersect_cnt(v[j], v[k])) {
					pair<double, double> a, b;
					assert(intersect_dbl(v[i].first, v[i].second, v[j].first, v[j].second, a) == 1);
					assert(intersect_dbl(v[i].first, v[i].second, v[k].first, v[k].second, b) == 1);
					double diff = abs(a.first - b.first);
					if(diff <= 1e-6)
						continue;
					ans++;
				}
			}
		}
	}
	cout << ans;
}
