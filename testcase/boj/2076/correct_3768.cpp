#include <bits/stdc++.h>
using namespace std;
#define int long long
struct pnt {
	int x, y;
	pnt operator-(pnt a) {
	    return {x-a.x,y-a.y};
	}
};

int cross(pnt p, pnt q) {
    return p.x*q.y-p.y*q.x;
}
int ccw(pnt A, pnt B) {
    int c = cross(A, B);
    if(c > 0) return 1; // ccw
    else if(c < 0) return -1; // cw
    else return 0; // colinear
}
int dot(pnt x, pnt y) {
	return x.x*y.x+x.y*y.y;
}
const int MX = 3e4+2;
#define pi pair<int, int>
int hypot(auto x) {
	return x.x*x.x + x.y*x.y;
}
pnt arr[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int all_x = 0, all_y = 0;
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y;
		all_x += arr[i].x;
		all_y += arr[i].y;
	}
	// Angle sorting reference: https://koosaga.com/97
	sort(arr, arr+n, [&](const pnt &a, const pnt &b){
		if((pi(a.x, a.y) > pi(0, 0)) ^ (pi(b.x, b.y) > pi(0, 0))) return pi(a.x, a.y) > pi(b.x, b.y);
		if(ccw(a, b) != 0) return ccw(a, b) > 0;
		return hypot(a) < hypot(b);
	});
	int xsum = 0, ysum = 0, ans = 0;
	int j = 0;
	// for(int i=0; i<n; i++) {
	// 	printf("(%d, %d)\n", arr[i].x, arr[i].y);
	// }
	for(int i=0; i<n; xsum -= arr[i].x, ysum -= arr[i].y, i++) {

		while(j < i+n && ((cross(arr[i], arr[j%n]) > 0) || (cross(arr[i], arr[j%n]) == 0 && dot(arr[i], arr[j%n]) > 0))) {
			//printf("cross %d, %d -> %d\n", i, j, cross(arr[i], arr[j]));
			xsum += arr[j%n].x;
			ysum += arr[j%n].y;
			j++;
		}
		//printf("cross %d, %d -> %d\n", i, j, cross(arr[i], arr[j]));
		//printf("at i=%d, j=%d. xsum = %d, ysum = %d\n", i, j, xsum, ysum);
		int v1 = xsum*xsum+ysum*ysum, v2 = (all_x-xsum)*(all_x-xsum) + (all_y-ysum)*(all_y-ysum);
		ans = max({ans, v1, v2});
	}
	cout << ans;
}
