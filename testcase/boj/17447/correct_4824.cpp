#include <bits/stdc++.h>

using namespace std;
const int MX = 500;
int lb[MX][MX], lu[MX][MX], ru[MX][MX], rb[MX][MX];
struct Point{
    int x, y;
    Point operator-(Point a) {
        return {x-a.x,y-a.y};
    }
};
int cross(Point p, Point q) {
    return p.x*q.y-p.y*q.x;
}
int ccw(Point A, Point B, Point C) {
    int c = cross(B-A, C-B);
    if(c > 0) return 1; // ccw
    else if(c < 0) return -1; // cw
    else return 0; // colinear
}
Point arr[MX];
int val[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	int total = 0;
	for(int i=0; i<m; i++) {
		cin >> arr[i].x >> arr[i].y >> val[i];
		total += val[i];
	}
	for(int x=1; x<n; x++) {
		for(int y=1; y<n; y++) {
			for(int i=0; i<m; i++) {
				if(ccw({x, 0}, arr[i], {0, y}) == -1)
					lb[x][y] += val[i];
				if(ccw({0, y}, arr[i], {x, n}) == -1)
					lu[x][y] += val[i];
				if(ccw({x, n}, arr[i], {n, y}) == -1)
					ru[x][y] += val[i];
				if(ccw({n, y}, arr[i], {x, 0}) == -1)
					rb[x][y] += val[i];
			}
		}
	}
	int rmmin = INT_MAX;
	for(int l=1; l<n; l++) {
		for(int r=1; r<n; r++) {
			int rm1 = INT_MAX, rm2 = INT_MAX;
			for(int i=1; i<n; i++) {
				rm1 = min(rm1, lu[i][l]+ru[i][r]);
				rm2 = min(rm2, lb[i][l]+rb[i][r]);
			}
			rmmin = min(rmmin, rm1+rm2);
		}
	}
	cout << total - rmmin;
}
