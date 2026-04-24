#include <bits/stdc++.h>
using namespace std;
const int MX = 1e3+2;
int par[MX];
int f(int i) {return par[i] == i ? i : par[i] = f(par[i]);}
struct point {
	int x, y;
	int dist(point i) {
		return (x-i.x)*(x-i.x)+(y-i.y)*(y-i.y);
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<point> arr(n);
	for(int i=0; i<n; i++) {
		cin >> arr[i].x >> arr[i].y;
	}
	for(int i=0; i<n; i++) {
		par[i] = i;
	}
	vector<point> order;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			order.push_back({i,j});
		}
	}
	sort(order.begin(), order.end(), [&](point i, point j){
		return arr[i.x].dist(arr[i.y]) < arr[j.x].dist(arr[j.y]);
	});
	int cnt = n;
	for(auto [a,b]: order) {
		if(f(a) != f(b)) {
			cnt--;
			if(cnt == 1)
				return !(cout << arr[a].dist(arr[b]));
			par[f(a)] = f(b);
		}
	}
}
