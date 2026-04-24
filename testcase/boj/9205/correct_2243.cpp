#include <bits/stdc++.h>
using namespace std;

struct Point{
	int x, y;
};
int dist(Point &a, Point &b) {
	return abs(a.x-b.x)+abs(a.y-b.y);
}
int parent[102];
Point pos[102];
int find(int i){return i == parent[i] ? i : parent[i] = find(parent[i]);}
void join(int i, int j){
	parent[find(i)] = find(j);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		cin >> pos[0].x >> pos[0].y;
		for(int i=1; i<=n; i++) {
			cin >> pos[i].x >> pos[i].y;
		}
		cin >> pos[n+1].x >> pos[n+1].y;
		for(int i=0; i<n+2; i++) {
			parent[i] = i;
		}
		for(int i=0; i<n+2; i++) {
			for(int j=i+1; j<n+2; j++) {
				if(dist(pos[i], pos[j]) <= 1000)
					join(i, j);
			}
		}
		cout << (find(0) == find(n+1) ? "happy\n" : "sad\n");
	}
}
