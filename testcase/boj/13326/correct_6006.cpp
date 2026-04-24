#include <bits/stdc++.h>
using namespace std;
struct Point{int x,y;};
int sq(int i){return i*i;}
int dist(Point a, Point b) {
	return sq(a.x-b.x)+sq(a.y-b.y);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	Point arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y;
	}
	int mi, mj, md = -1;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			if(dist(arr[i],arr[j]) > md) {
				md = dist(arr[i],arr[j]);
				mi = i;
				mj = j;
			}
		}
	}
	Point p = arr[mi];
	sort(arr, arr+n, [&](Point a, Point b) {return dist(a, p) < dist(b, p);});
	int da[n];
	da[n-1] = 0;
	for(int i=n-2; i>0; i--) {
		da[i] = da[i+1];
		for(int j=i+1; j<n; j++) {
			da[i] = max(da[i], dist(arr[i], arr[j]));
		}
	}
	int a = 0, b = 0;
	double ans = DBL_MAX;
	for(int i=0; i<n-1; i++) {
		for(int j=0; j<i; j++) {
			a = max(a, dist(arr[j], arr[i]));
		}
		ans = min(ans, sqrt(a)+sqrt(da[i+1]));
	}
	cout << fixed << setprecision(10) << ans;
}
