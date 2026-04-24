#include <bits/stdc++.h>
using namespace std;
struct Point{
	int i, x, y, z;
};
struct Edge {
	int u, v, dist;
};
const int MX = 100000;
Point arr[MX], arrx[MX], arry[MX], arrz[MX];
int parent[MX];
int findp(int i) {return i == parent[i] ? i : parent[i] = findp(parent[i]);}
void join(int i, int j) {
	i = findp(i), j = findp(j);
	parent[i] = j;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		arr[i].i = i;
		cin >> arr[i].x >> arr[i].y >> arr[i].z;
	}
	memcpy(arrx, arr, sizeof arr);
	memcpy(arry, arr, sizeof arr);
	memcpy(arrz, arr, sizeof arr);
	sort(arrx, arrx+n, [](Point &a, Point &b){return a.x < b.x;});
	sort(arry, arry+n, [](Point &a, Point &b){return a.y < b.y;});
	sort(arrz, arrz+n, [](Point &a, Point &b){return a.z < b.z;});
	vector<Edge> edges;
	for(int i=1; i<n; i++) {
		edges.push_back({arrx[i].i, arrx[i-1].i, arrx[i].x-arrx[i-1].x});
		edges.push_back({arry[i].i, arry[i-1].i, arry[i].y-arry[i-1].y});
		edges.push_back({arrz[i].i, arrz[i-1].i, arrz[i].z-arrz[i-1].z});
	}
	long long ans = 0;
	int edgecnt = 0;
	sort(edges.begin(), edges.end(), [](Edge &a, Edge &b){return a.dist < b.dist;});
	for(int i=0; i<n; i++) parent[i] = i;
	for(Edge &e: edges) {
		if(findp(e.u) != findp(e.v)) {
			join(e.u, e.v);
			edgecnt++;
			ans += e.dist;
		}
		if(edgecnt == n-1) return !(cout << ans);
	}
}
