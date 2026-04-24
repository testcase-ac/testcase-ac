#include <bits/stdc++.h>
using namespace std;
#define int long long
struct rect {
	int x1, x2, y1, y2, i;
};
const int MX = 5e4+2;
rect arr[MX], arrcp[MX];
int area[MX], par[MX], n;
int f(int i){return par[i] == i ? i : par[i] = f(par[i]);}
void add(int a, int b) {
	a = f(a), b = f(b);
	if(a != b) {
		area[a] += area[b];
		par[b] = a;
	}
}
void go() {
	memcpy(arrcp, arr, sizeof arr);
	sort(arr, arr+n, [](auto& a, auto& b){return tie(a.x2, a.y1) < tie(b.x2, b.y1);});
	sort(arrcp, arrcp+n, [](auto &a, auto& b){return tie(a.x1, a.y1) < tie(b.x1, b.y1);});
	int i1 = 0, i2 = 0, j1 = 0, j2 = 0;
	while(i1 = j1, i2 = j2, i1 < n && i2 < n) {
		if(arr[j1].x2 != arrcp[j2].x1) {
			while(j1 < n && arr[j1].x2 < arrcp[j2].x1)
				j1++;
			while(j2 < n && arrcp[j2].x1 < arr[j1].x2)
				j2++;
		} else {
			set<pair<int, int>> st1, st2;
			while(arr[i1].x2 == arr[j1].x2 || arrcp[i2].x1 == arrcp[j2].x1) {
				if(arrcp[i2].x1 != arrcp[j2].x1 || (arr[i1].x2 == arr[j1].x2 && arr[j1].y1 < arrcp[j2].y1)) { // error 1
					while(st2.size() && st2.begin()->first < arr[j1].y1)
						st2.erase(st2.begin());
					for(auto [_, ind]: st2)
						add(ind, arr[j1].i);
					st1.insert({arr[j1].y2, arr[j1].i});
					j1++;
				} else {
					while(st1.size() && st1.begin()->first < arrcp[j2].y1)
						st1.erase(st1.begin());
					for(auto [_, ind]: st1) // error 2
						add(ind, arrcp[j2].i);
					st2.insert({arrcp[j2].y2, arrcp[j2].i});
					j2++;
				}
			}
		}
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		int x,y,w,h;
		cin >> x >> y >> w >> h;
		arr[i].x1 = x;
		arr[i].x2 = x+w;
		arr[i].y1 = y;
		arr[i].y2 = y+h;
		arr[i].i = i;
		area[i] = w*h;
		par[i] = i;
	}
	go();
	for(int i=0; i<n; i++) {
		swap(arr[i].x1, arr[i].y1);
		swap(arr[i].x2, arr[i].y2);
	}
	go();
	int ans = 0;
	for(int i=0; i<n; i++) {
		ans = max(ans, area[i]);
	}
	cout << ans;
}
